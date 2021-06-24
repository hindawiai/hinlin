<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe AER software error injection support.
 *
 * Debugging PCIe AER code is quite dअगरficult because it is hard to
 * trigger various real hardware errors. Software based error
 * injection can fake almost all kinds of errors with the help of a
 * user space helper tool aer-inject, which can be gotten from:
 *   https://www.kernel.org/pub/linux/utils/pci/aer-inject/
 *
 * Copyright 2009 Intel Corporation.
 *     Huang Ying <ying.huang@पूर्णांकel.com>
 */

#घोषणा dev_fmt(fmt) "aer_inject: " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/device.h>

#समावेश "portdrv.h"

/* Override the existing corrected and uncorrected error masks */
अटल bool aer_mask_override;
module_param(aer_mask_override, bool, 0);

काष्ठा aer_error_inj अणु
	u8 bus;
	u8 dev;
	u8 fn;
	u32 uncor_status;
	u32 cor_status;
	u32 header_log0;
	u32 header_log1;
	u32 header_log2;
	u32 header_log3;
	u32 करोमुख्य;
पूर्ण;

काष्ठा aer_error अणु
	काष्ठा list_head list;
	u32 करोमुख्य;
	अचिन्हित पूर्णांक bus;
	अचिन्हित पूर्णांक devfn;
	पूर्णांक pos_cap_err;

	u32 uncor_status;
	u32 cor_status;
	u32 header_log0;
	u32 header_log1;
	u32 header_log2;
	u32 header_log3;
	u32 root_status;
	u32 source_id;
पूर्ण;

काष्ठा pci_bus_ops अणु
	काष्ठा list_head list;
	काष्ठा pci_bus *bus;
	काष्ठा pci_ops *ops;
पूर्ण;

अटल LIST_HEAD(einjected);

अटल LIST_HEAD(pci_bus_ops_list);

/* Protect einjected and pci_bus_ops_list */
अटल DEFINE_SPINLOCK(inject_lock);

अटल व्योम aer_error_init(काष्ठा aer_error *err, u32 करोमुख्य,
			   अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक pos_cap_err)
अणु
	INIT_LIST_HEAD(&err->list);
	err->करोमुख्य = करोमुख्य;
	err->bus = bus;
	err->devfn = devfn;
	err->pos_cap_err = pos_cap_err;
पूर्ण

/* inject_lock must be held beक्रमe calling */
अटल काष्ठा aer_error *__find_aer_error(u32 करोमुख्य, अचिन्हित पूर्णांक bus,
					  अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा aer_error *err;

	list_क्रम_each_entry(err, &einjected, list) अणु
		अगर (करोमुख्य == err->करोमुख्य &&
		    bus == err->bus &&
		    devfn == err->devfn)
			वापस err;
	पूर्ण
	वापस शून्य;
पूर्ण

/* inject_lock must be held beक्रमe calling */
अटल काष्ठा aer_error *__find_aer_error_by_dev(काष्ठा pci_dev *dev)
अणु
	पूर्णांक करोमुख्य = pci_करोमुख्य_nr(dev->bus);
	अगर (करोमुख्य < 0)
		वापस शून्य;
	वापस __find_aer_error(करोमुख्य, dev->bus->number, dev->devfn);
पूर्ण

/* inject_lock must be held beक्रमe calling */
अटल काष्ठा pci_ops *__find_pci_bus_ops(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus_ops *bus_ops;

	list_क्रम_each_entry(bus_ops, &pci_bus_ops_list, list) अणु
		अगर (bus_ops->bus == bus)
			वापस bus_ops->ops;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा pci_bus_ops *pci_bus_ops_pop(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pci_bus_ops *bus_ops;

	spin_lock_irqsave(&inject_lock, flags);
	bus_ops = list_first_entry_or_null(&pci_bus_ops_list,
					   काष्ठा pci_bus_ops, list);
	अगर (bus_ops)
		list_del(&bus_ops->list);
	spin_unlock_irqrestore(&inject_lock, flags);
	वापस bus_ops;
पूर्ण

अटल u32 *find_pci_config_dword(काष्ठा aer_error *err, पूर्णांक where,
				  पूर्णांक *prw1cs)
अणु
	पूर्णांक rw1cs = 0;
	u32 *target = शून्य;

	अगर (err->pos_cap_err == -1)
		वापस शून्य;

	चयन (where - err->pos_cap_err) अणु
	हाल PCI_ERR_UNCOR_STATUS:
		target = &err->uncor_status;
		rw1cs = 1;
		अवरोध;
	हाल PCI_ERR_COR_STATUS:
		target = &err->cor_status;
		rw1cs = 1;
		अवरोध;
	हाल PCI_ERR_HEADER_LOG:
		target = &err->header_log0;
		अवरोध;
	हाल PCI_ERR_HEADER_LOG+4:
		target = &err->header_log1;
		अवरोध;
	हाल PCI_ERR_HEADER_LOG+8:
		target = &err->header_log2;
		अवरोध;
	हाल PCI_ERR_HEADER_LOG+12:
		target = &err->header_log3;
		अवरोध;
	हाल PCI_ERR_ROOT_STATUS:
		target = &err->root_status;
		rw1cs = 1;
		अवरोध;
	हाल PCI_ERR_ROOT_ERR_SRC:
		target = &err->source_id;
		अवरोध;
	पूर्ण
	अगर (prw1cs)
		*prw1cs = rw1cs;
	वापस target;
पूर्ण

अटल पूर्णांक aer_inj_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_ops *ops, *my_ops;
	पूर्णांक rv;

	ops = __find_pci_bus_ops(bus);
	अगर (!ops)
		वापस -1;

	my_ops = bus->ops;
	bus->ops = ops;
	rv = ops->पढ़ो(bus, devfn, where, size, val);
	bus->ops = my_ops;

	वापस rv;
पूर्ण

अटल पूर्णांक aer_inj_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			 पूर्णांक size, u32 val)
अणु
	काष्ठा pci_ops *ops, *my_ops;
	पूर्णांक rv;

	ops = __find_pci_bus_ops(bus);
	अगर (!ops)
		वापस -1;

	my_ops = bus->ops;
	bus->ops = ops;
	rv = ops->ग_लिखो(bus, devfn, where, size, val);
	bus->ops = my_ops;

	वापस rv;
पूर्ण

अटल पूर्णांक aer_inj_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 *sim;
	काष्ठा aer_error *err;
	अचिन्हित दीर्घ flags;
	पूर्णांक करोमुख्य;
	पूर्णांक rv;

	spin_lock_irqsave(&inject_lock, flags);
	अगर (size != माप(u32))
		जाओ out;
	करोमुख्य = pci_करोमुख्य_nr(bus);
	अगर (करोमुख्य < 0)
		जाओ out;
	err = __find_aer_error(करोमुख्य, bus->number, devfn);
	अगर (!err)
		जाओ out;

	sim = find_pci_config_dword(err, where, शून्य);
	अगर (sim) अणु
		*val = *sim;
		spin_unlock_irqrestore(&inject_lock, flags);
		वापस 0;
	पूर्ण
out:
	rv = aer_inj_पढ़ो(bus, devfn, where, size, val);
	spin_unlock_irqrestore(&inject_lock, flags);
	वापस rv;
पूर्ण

अटल पूर्णांक aer_inj_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 *sim;
	काष्ठा aer_error *err;
	अचिन्हित दीर्घ flags;
	पूर्णांक rw1cs;
	पूर्णांक करोमुख्य;
	पूर्णांक rv;

	spin_lock_irqsave(&inject_lock, flags);
	अगर (size != माप(u32))
		जाओ out;
	करोमुख्य = pci_करोमुख्य_nr(bus);
	अगर (करोमुख्य < 0)
		जाओ out;
	err = __find_aer_error(करोमुख्य, bus->number, devfn);
	अगर (!err)
		जाओ out;

	sim = find_pci_config_dword(err, where, &rw1cs);
	अगर (sim) अणु
		अगर (rw1cs)
			*sim ^= val;
		अन्यथा
			*sim = val;
		spin_unlock_irqrestore(&inject_lock, flags);
		वापस 0;
	पूर्ण
out:
	rv = aer_inj_ग_लिखो(bus, devfn, where, size, val);
	spin_unlock_irqrestore(&inject_lock, flags);
	वापस rv;
पूर्ण

अटल काष्ठा pci_ops aer_inj_pci_ops = अणु
	.पढ़ो = aer_inj_पढ़ो_config,
	.ग_लिखो = aer_inj_ग_लिखो_config,
पूर्ण;

अटल व्योम pci_bus_ops_init(काष्ठा pci_bus_ops *bus_ops,
			     काष्ठा pci_bus *bus,
			     काष्ठा pci_ops *ops)
अणु
	INIT_LIST_HEAD(&bus_ops->list);
	bus_ops->bus = bus;
	bus_ops->ops = ops;
पूर्ण

अटल पूर्णांक pci_bus_set_aer_ops(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_ops *ops;
	काष्ठा pci_bus_ops *bus_ops;
	अचिन्हित दीर्घ flags;

	bus_ops = kदो_स्मृति(माप(*bus_ops), GFP_KERNEL);
	अगर (!bus_ops)
		वापस -ENOMEM;
	ops = pci_bus_set_ops(bus, &aer_inj_pci_ops);
	spin_lock_irqsave(&inject_lock, flags);
	अगर (ops == &aer_inj_pci_ops)
		जाओ out;
	pci_bus_ops_init(bus_ops, bus, ops);
	list_add(&bus_ops->list, &pci_bus_ops_list);
	bus_ops = शून्य;
out:
	spin_unlock_irqrestore(&inject_lock, flags);
	kमुक्त(bus_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक aer_inject(काष्ठा aer_error_inj *einj)
अणु
	काष्ठा aer_error *err, *rperr;
	काष्ठा aer_error *err_alloc = शून्य, *rperr_alloc = शून्य;
	काष्ठा pci_dev *dev, *rpdev;
	काष्ठा pcie_device *edev;
	काष्ठा device *device;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक devfn = PCI_DEVFN(einj->dev, einj->fn);
	पूर्णांक pos_cap_err, rp_pos_cap_err;
	u32 sever, cor_mask, uncor_mask, cor_mask_orig = 0, uncor_mask_orig = 0;
	पूर्णांक ret = 0;

	dev = pci_get_करोमुख्य_bus_and_slot(einj->करोमुख्य, einj->bus, devfn);
	अगर (!dev)
		वापस -ENODEV;
	rpdev = pcie_find_root_port(dev);
	/* If Root Port not found, try to find an RCEC */
	अगर (!rpdev)
		rpdev = dev->rcec;
	अगर (!rpdev) अणु
		pci_err(dev, "Neither Root Port nor RCEC found\n");
		ret = -ENODEV;
		जाओ out_put;
	पूर्ण

	pos_cap_err = dev->aer_cap;
	अगर (!pos_cap_err) अणु
		pci_err(dev, "Device doesn't support AER\n");
		ret = -EPROTONOSUPPORT;
		जाओ out_put;
	पूर्ण
	pci_पढ़ो_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_SEVER, &sever);
	pci_पढ़ो_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK, &cor_mask);
	pci_पढ़ो_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
			      &uncor_mask);

	rp_pos_cap_err = rpdev->aer_cap;
	अगर (!rp_pos_cap_err) अणु
		pci_err(rpdev, "Root port doesn't support AER\n");
		ret = -EPROTONOSUPPORT;
		जाओ out_put;
	पूर्ण

	err_alloc =  kzalloc(माप(काष्ठा aer_error), GFP_KERNEL);
	अगर (!err_alloc) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण
	rperr_alloc =  kzalloc(माप(काष्ठा aer_error), GFP_KERNEL);
	अगर (!rperr_alloc) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	अगर (aer_mask_override) अणु
		cor_mask_orig = cor_mask;
		cor_mask &= !(einj->cor_status);
		pci_ग_लिखो_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK,
				       cor_mask);

		uncor_mask_orig = uncor_mask;
		uncor_mask &= !(einj->uncor_status);
		pci_ग_लिखो_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
				       uncor_mask);
	पूर्ण

	spin_lock_irqsave(&inject_lock, flags);

	err = __find_aer_error_by_dev(dev);
	अगर (!err) अणु
		err = err_alloc;
		err_alloc = शून्य;
		aer_error_init(err, einj->करोमुख्य, einj->bus, devfn,
			       pos_cap_err);
		list_add(&err->list, &einjected);
	पूर्ण
	err->uncor_status |= einj->uncor_status;
	err->cor_status |= einj->cor_status;
	err->header_log0 = einj->header_log0;
	err->header_log1 = einj->header_log1;
	err->header_log2 = einj->header_log2;
	err->header_log3 = einj->header_log3;

	अगर (!aer_mask_override && einj->cor_status &&
	    !(einj->cor_status & ~cor_mask)) अणु
		ret = -EINVAL;
		pci_warn(dev, "The correctable error(s) is masked by device\n");
		spin_unlock_irqrestore(&inject_lock, flags);
		जाओ out_put;
	पूर्ण
	अगर (!aer_mask_override && einj->uncor_status &&
	    !(einj->uncor_status & ~uncor_mask)) अणु
		ret = -EINVAL;
		pci_warn(dev, "The uncorrectable error(s) is masked by device\n");
		spin_unlock_irqrestore(&inject_lock, flags);
		जाओ out_put;
	पूर्ण

	rperr = __find_aer_error_by_dev(rpdev);
	अगर (!rperr) अणु
		rperr = rperr_alloc;
		rperr_alloc = शून्य;
		aer_error_init(rperr, pci_करोमुख्य_nr(rpdev->bus),
			       rpdev->bus->number, rpdev->devfn,
			       rp_pos_cap_err);
		list_add(&rperr->list, &einjected);
	पूर्ण
	अगर (einj->cor_status) अणु
		अगर (rperr->root_status & PCI_ERR_ROOT_COR_RCV)
			rperr->root_status |= PCI_ERR_ROOT_MULTI_COR_RCV;
		अन्यथा
			rperr->root_status |= PCI_ERR_ROOT_COR_RCV;
		rperr->source_id &= 0xffff0000;
		rperr->source_id |= (einj->bus << 8) | devfn;
	पूर्ण
	अगर (einj->uncor_status) अणु
		अगर (rperr->root_status & PCI_ERR_ROOT_UNCOR_RCV)
			rperr->root_status |= PCI_ERR_ROOT_MULTI_UNCOR_RCV;
		अगर (sever & einj->uncor_status) अणु
			rperr->root_status |= PCI_ERR_ROOT_FATAL_RCV;
			अगर (!(rperr->root_status & PCI_ERR_ROOT_UNCOR_RCV))
				rperr->root_status |= PCI_ERR_ROOT_FIRST_FATAL;
		पूर्ण अन्यथा
			rperr->root_status |= PCI_ERR_ROOT_NONFATAL_RCV;
		rperr->root_status |= PCI_ERR_ROOT_UNCOR_RCV;
		rperr->source_id &= 0x0000ffff;
		rperr->source_id |= ((einj->bus << 8) | devfn) << 16;
	पूर्ण
	spin_unlock_irqrestore(&inject_lock, flags);

	अगर (aer_mask_override) अणु
		pci_ग_लिखो_config_dword(dev, pos_cap_err + PCI_ERR_COR_MASK,
				       cor_mask_orig);
		pci_ग_लिखो_config_dword(dev, pos_cap_err + PCI_ERR_UNCOR_MASK,
				       uncor_mask_orig);
	पूर्ण

	ret = pci_bus_set_aer_ops(dev->bus);
	अगर (ret)
		जाओ out_put;
	ret = pci_bus_set_aer_ops(rpdev->bus);
	अगर (ret)
		जाओ out_put;

	device = pcie_port_find_device(rpdev, PCIE_PORT_SERVICE_AER);
	अगर (device) अणु
		edev = to_pcie_device(device);
		अगर (!get_service_data(edev)) अणु
			pci_warn(edev->port, "AER service is not initialized\n");
			ret = -EPROTONOSUPPORT;
			जाओ out_put;
		पूर्ण
		pci_info(edev->port, "Injecting errors %08x/%08x into device %s\n",
			 einj->cor_status, einj->uncor_status, pci_name(dev));
		ret = irq_inject_पूर्णांकerrupt(edev->irq);
	पूर्ण अन्यथा अणु
		pci_err(rpdev, "AER device not found\n");
		ret = -ENODEV;
	पूर्ण
out_put:
	kमुक्त(err_alloc);
	kमुक्त(rperr_alloc);
	pci_dev_put(dev);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार aer_inject_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार usize, loff_t *off)
अणु
	काष्ठा aer_error_inj einj;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (usize < दुरत्व(काष्ठा aer_error_inj, करोमुख्य) ||
	    usize > माप(einj))
		वापस -EINVAL;

	स_रखो(&einj, 0, माप(einj));
	अगर (copy_from_user(&einj, ubuf, usize))
		वापस -EFAULT;

	ret = aer_inject(&einj);
	वापस ret ? ret : usize;
पूर्ण

अटल स्थिर काष्ठा file_operations aer_inject_fops = अणु
	.ग_लिखो = aer_inject_ग_लिखो,
	.owner = THIS_MODULE,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice aer_inject_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "aer_inject",
	.fops = &aer_inject_fops,
पूर्ण;

अटल पूर्णांक __init aer_inject_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&aer_inject_device);
पूर्ण

अटल व्योम __निकास aer_inject_निकास(व्योम)
अणु
	काष्ठा aer_error *err, *err_next;
	अचिन्हित दीर्घ flags;
	काष्ठा pci_bus_ops *bus_ops;

	misc_deरेजिस्टर(&aer_inject_device);

	जबतक ((bus_ops = pci_bus_ops_pop())) अणु
		pci_bus_set_ops(bus_ops->bus, bus_ops->ops);
		kमुक्त(bus_ops);
	पूर्ण

	spin_lock_irqsave(&inject_lock, flags);
	list_क्रम_each_entry_safe(err, err_next, &einjected, list) अणु
		list_del(&err->list);
		kमुक्त(err);
	पूर्ण
	spin_unlock_irqrestore(&inject_lock, flags);
पूर्ण

module_init(aer_inject_init);
module_निकास(aer_inject_निकास);

MODULE_DESCRIPTION("PCIe AER software error injector");
MODULE_LICENSE("GPL");
