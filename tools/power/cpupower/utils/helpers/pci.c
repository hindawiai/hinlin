<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर defined(__i386__) || defined(__x86_64__)

#समावेश <helpers/helpers.h>

/*
 * pci_acc_init
 *
 * PCI access helper function depending on libpci
 *
 * **pacc : अगर a valid pci_dev is वापसed
 *         *pacc must be passed to pci_acc_cleanup to मुक्त it
 *
 * करोमुख्य: करोमुख्य
 * bus:    bus
 * slot:   slot
 * func:   func
 * venकरोr: venकरोr
 * device: device
 * Pass -1 क्रम one of the six above to match any
 *
 * Returns :
 * काष्ठा pci_dev which can be used with pci_अणुपढ़ो,ग_लिखोपूर्ण_* functions
 *                to access the PCI config space of matching pci devices
 */
काष्ठा pci_dev *pci_acc_init(काष्ठा pci_access **pacc, पूर्णांक करोमुख्य, पूर्णांक bus,
			     पूर्णांक slot, पूर्णांक func, पूर्णांक venकरोr, पूर्णांक dev)
अणु
	काष्ठा pci_filter filter_nb_link;
	काष्ठा pci_dev *device;

	*pacc = pci_alloc();
	अगर (*pacc == शून्य)
		वापस शून्य;

	pci_filter_init(*pacc, &filter_nb_link);
	filter_nb_link.करोमुख्य	= करोमुख्य;
	filter_nb_link.bus	= bus;
	filter_nb_link.slot	= slot;
	filter_nb_link.func	= func;
	filter_nb_link.venकरोr	= venकरोr;
	filter_nb_link.device	= dev;

	pci_init(*pacc);
	pci_scan_bus(*pacc);

	क्रम (device = (*pacc)->devices; device; device = device->next) अणु
		अगर (pci_filter_match(&filter_nb_link, device))
			वापस device;
	पूर्ण
	pci_cleanup(*pacc);
	वापस शून्य;
पूर्ण

/* Typically one wants to get a specअगरic slot(device)/func of the root करोमुख्य
   and bus */
काष्ठा pci_dev *pci_slot_func_init(काष्ठा pci_access **pacc, पूर्णांक slot,
				       पूर्णांक func)
अणु
	वापस pci_acc_init(pacc, 0, 0, slot, func, -1, -1);
पूर्ण

#पूर्ण_अगर /* defined(__i386__) || defined(__x86_64__) */
