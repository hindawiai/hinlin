<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Hotplug Driver क्रम PowerPC PowerNV platक्रमm.
 *
 * Copyright Gavin Shan, IBM Corporation 2016.
 */

#समावेश <linux/libfdt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/ppc-pci.h>

#घोषणा DRIVER_VERSION	"0.1"
#घोषणा DRIVER_AUTHOR	"Gavin Shan, IBM Corporation"
#घोषणा DRIVER_DESC	"PowerPC PowerNV PCI Hotplug Driver"

#घोषणा SLOT_WARN(sl, x...) \
	((sl)->pdev ? pci_warn((sl)->pdev, x) : dev_warn(&(sl)->bus->dev, x))

काष्ठा pnv_php_event अणु
	bool			added;
	काष्ठा pnv_php_slot	*php_slot;
	काष्ठा work_काष्ठा	work;
पूर्ण;

अटल LIST_HEAD(pnv_php_slot_list);
अटल DEFINE_SPINLOCK(pnv_php_lock);

अटल व्योम pnv_php_रेजिस्टर(काष्ठा device_node *dn);
अटल व्योम pnv_php_unरेजिस्टर_one(काष्ठा device_node *dn);
अटल व्योम pnv_php_unरेजिस्टर(काष्ठा device_node *dn);

अटल व्योम pnv_php_disable_irq(काष्ठा pnv_php_slot *php_slot,
				bool disable_device)
अणु
	काष्ठा pci_dev *pdev = php_slot->pdev;
	पूर्णांक irq = php_slot->irq;
	u16 ctrl;

	अगर (php_slot->irq > 0) अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &ctrl);
		ctrl &= ~(PCI_EXP_SLTCTL_HPIE |
			  PCI_EXP_SLTCTL_PDCE |
			  PCI_EXP_SLTCTL_DLLSCE);
		pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTCTL, ctrl);

		मुक्त_irq(php_slot->irq, php_slot);
		php_slot->irq = 0;
	पूर्ण

	अगर (php_slot->wq) अणु
		destroy_workqueue(php_slot->wq);
		php_slot->wq = शून्य;
	पूर्ण

	अगर (disable_device || irq > 0) अणु
		अगर (pdev->msix_enabled)
			pci_disable_msix(pdev);
		अन्यथा अगर (pdev->msi_enabled)
			pci_disable_msi(pdev);

		pci_disable_device(pdev);
	पूर्ण
पूर्ण

अटल व्योम pnv_php_मुक्त_slot(काष्ठा kref *kref)
अणु
	काष्ठा pnv_php_slot *php_slot = container_of(kref,
					काष्ठा pnv_php_slot, kref);

	WARN_ON(!list_empty(&php_slot->children));
	pnv_php_disable_irq(php_slot, false);
	kमुक्त(php_slot->name);
	kमुक्त(php_slot);
पूर्ण

अटल अंतरभूत व्योम pnv_php_put_slot(काष्ठा pnv_php_slot *php_slot)
अणु

	अगर (!php_slot)
		वापस;

	kref_put(&php_slot->kref, pnv_php_मुक्त_slot);
पूर्ण

अटल काष्ठा pnv_php_slot *pnv_php_match(काष्ठा device_node *dn,
					  काष्ठा pnv_php_slot *php_slot)
अणु
	काष्ठा pnv_php_slot *target, *पंचांगp;

	अगर (php_slot->dn == dn) अणु
		kref_get(&php_slot->kref);
		वापस php_slot;
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &php_slot->children, link) अणु
		target = pnv_php_match(dn, पंचांगp);
		अगर (target)
			वापस target;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा pnv_php_slot *pnv_php_find_slot(काष्ठा device_node *dn)
अणु
	काष्ठा pnv_php_slot *php_slot, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pnv_php_lock, flags);
	list_क्रम_each_entry(पंचांगp, &pnv_php_slot_list, link) अणु
		php_slot = pnv_php_match(dn, पंचांगp);
		अगर (php_slot) अणु
			spin_unlock_irqrestore(&pnv_php_lock, flags);
			वापस php_slot;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pnv_php_lock, flags);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_php_find_slot);

/*
 * Remove pdn क्रम all children of the indicated device node.
 * The function should हटाओ pdn in a depth-first manner.
 */
अटल व्योम pnv_php_rmv_pdns(काष्ठा device_node *dn)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(dn, child) अणु
		pnv_php_rmv_pdns(child);

		pci_हटाओ_device_node_info(child);
	पूर्ण
पूर्ण

/*
 * Detach all child nodes of the indicated device nodes. The
 * function should handle device nodes in depth-first manner.
 *
 * We should not invoke of_node_release() as the memory क्रम
 * inभागidual device node is part of large memory block. The
 * large block is allocated from memblock (प्रणाली bootup) or
 * kदो_स्मृति() when unflattening the device tree by OF changeset.
 * We can not मुक्त the large block allocated from memblock. For
 * later हाल, it should be released at once.
 */
अटल व्योम pnv_php_detach_device_nodes(काष्ठा device_node *parent)
अणु
	काष्ठा device_node *dn;

	क्रम_each_child_of_node(parent, dn) अणु
		pnv_php_detach_device_nodes(dn);

		of_node_put(dn);
		of_detach_node(dn);
	पूर्ण
पूर्ण

अटल व्योम pnv_php_rmv_devtree(काष्ठा pnv_php_slot *php_slot)
अणु
	pnv_php_rmv_pdns(php_slot->dn);

	/*
	 * Decrease the refcount अगर the device nodes were created
	 * through OF changeset beक्रमe detaching them.
	 */
	अगर (php_slot->fdt)
		of_changeset_destroy(&php_slot->ocs);
	pnv_php_detach_device_nodes(php_slot->dn);

	अगर (php_slot->fdt) अणु
		kमुक्त(php_slot->dt);
		kमुक्त(php_slot->fdt);
		php_slot->dt        = शून्य;
		php_slot->dn->child = शून्य;
		php_slot->fdt       = शून्य;
	पूर्ण
पूर्ण

/*
 * As the nodes in OF changeset are applied in reverse order, we
 * need revert the nodes in advance so that we have correct node
 * order after the changeset is applied.
 */
अटल व्योम pnv_php_reverse_nodes(काष्ठा device_node *parent)
अणु
	काष्ठा device_node *child, *next;

	/* In-depth first */
	क्रम_each_child_of_node(parent, child)
		pnv_php_reverse_nodes(child);

	/* Reverse the nodes in the child list */
	child = parent->child;
	parent->child = शून्य;
	जबतक (child) अणु
		next = child->sibling;

		child->sibling = parent->child;
		parent->child = child;
		child = next;
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_php_populate_changeset(काष्ठा of_changeset *ocs,
				      काष्ठा device_node *dn)
अणु
	काष्ठा device_node *child;
	पूर्णांक ret = 0;

	क्रम_each_child_of_node(dn, child) अणु
		ret = of_changeset_attach_node(ocs, child);
		अगर (ret) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण

		ret = pnv_php_populate_changeset(ocs, child);
		अगर (ret) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम *pnv_php_add_one_pdn(काष्ठा device_node *dn, व्योम *data)
अणु
	काष्ठा pci_controller *hose = (काष्ठा pci_controller *)data;
	काष्ठा pci_dn *pdn;

	pdn = pci_add_device_node_info(hose, dn);
	अगर (!pdn)
		वापस ERR_PTR(-ENOMEM);

	वापस शून्य;
पूर्ण

अटल व्योम pnv_php_add_pdns(काष्ठा pnv_php_slot *slot)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(slot->bus);

	pci_traverse_device_nodes(slot->dn, pnv_php_add_one_pdn, hose);
पूर्ण

अटल पूर्णांक pnv_php_add_devtree(काष्ठा pnv_php_slot *php_slot)
अणु
	व्योम *fdt, *fdt1, *dt;
	पूर्णांक ret;

	/* We करोn't know the FDT blob size. We try to get it through
	 * maximal memory chunk and then copy it to another chunk that
	 * fits the real size.
	 */
	fdt1 = kzalloc(0x10000, GFP_KERNEL);
	अगर (!fdt1) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = pnv_pci_get_device_tree(php_slot->dn->phandle, fdt1, 0x10000);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d getting FDT blob\n", ret);
		जाओ मुक्त_fdt1;
	पूर्ण

	fdt = kmemdup(fdt1, fdt_totalsize(fdt1), GFP_KERNEL);
	अगर (!fdt) अणु
		ret = -ENOMEM;
		जाओ मुक्त_fdt1;
	पूर्ण

	/* Unflatten device tree blob */
	dt = of_fdt_unflatten_tree(fdt, php_slot->dn, शून्य);
	अगर (!dt) अणु
		ret = -EINVAL;
		SLOT_WARN(php_slot, "Cannot unflatten FDT\n");
		जाओ मुक्त_fdt;
	पूर्ण

	/* Initialize and apply the changeset */
	of_changeset_init(&php_slot->ocs);
	pnv_php_reverse_nodes(php_slot->dn);
	ret = pnv_php_populate_changeset(&php_slot->ocs, php_slot->dn);
	अगर (ret) अणु
		pnv_php_reverse_nodes(php_slot->dn);
		SLOT_WARN(php_slot, "Error %d populating changeset\n",
			  ret);
		जाओ मुक्त_dt;
	पूर्ण

	php_slot->dn->child = शून्य;
	ret = of_changeset_apply(&php_slot->ocs);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d applying changeset\n", ret);
		जाओ destroy_changeset;
	पूर्ण

	/* Add device node firmware data */
	pnv_php_add_pdns(php_slot);
	php_slot->fdt = fdt;
	php_slot->dt  = dt;
	kमुक्त(fdt1);
	जाओ out;

destroy_changeset:
	of_changeset_destroy(&php_slot->ocs);
मुक्त_dt:
	kमुक्त(dt);
	php_slot->dn->child = शून्य;
मुक्त_fdt:
	kमुक्त(fdt);
मुक्त_fdt1:
	kमुक्त(fdt1);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा pnv_php_slot *to_pnv_php_slot(काष्ठा hotplug_slot *slot)
अणु
	वापस container_of(slot, काष्ठा pnv_php_slot, slot);
पूर्ण

पूर्णांक pnv_php_set_slot_घातer_state(काष्ठा hotplug_slot *slot,
				 uपूर्णांक8_t state)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	काष्ठा opal_msg msg;
	पूर्णांक ret;

	ret = pnv_pci_set_घातer_state(php_slot->id, state, &msg);
	अगर (ret > 0) अणु
		अगर (be64_to_cpu(msg.params[1]) != php_slot->dn->phandle	||
		    be64_to_cpu(msg.params[2]) != state) अणु
			SLOT_WARN(php_slot, "Wrong msg (%lld, %lld, %lld)\n",
				  be64_to_cpu(msg.params[1]),
				  be64_to_cpu(msg.params[2]),
				  be64_to_cpu(msg.params[3]));
			वापस -ENOMSG;
		पूर्ण
		अगर (be64_to_cpu(msg.params[3]) != OPAL_SUCCESS) अणु
			ret = -ENODEV;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अगर (ret < 0) अणु
		जाओ error;
	पूर्ण

	अगर (state == OPAL_PCI_SLOT_POWER_OFF || state == OPAL_PCI_SLOT_OFFLINE)
		pnv_php_rmv_devtree(php_slot);
	अन्यथा
		ret = pnv_php_add_devtree(php_slot);

	वापस ret;

error:
	SLOT_WARN(php_slot, "Error %d powering %s\n",
		  ret, (state == OPAL_PCI_SLOT_POWER_ON) ? "on" : "off");
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_php_set_slot_घातer_state);

अटल पूर्णांक pnv_php_get_घातer_state(काष्ठा hotplug_slot *slot, u8 *state)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	uपूर्णांक8_t घातer_state = OPAL_PCI_SLOT_POWER_ON;
	पूर्णांक ret;

	/*
	 * Retrieve घातer status from firmware. If we fail
	 * getting that, the घातer status fails back to
	 * be on.
	 */
	ret = pnv_pci_get_घातer_state(php_slot->id, &घातer_state);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d getting power status\n",
			  ret);
	पूर्ण अन्यथा अणु
		*state = घातer_state;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_get_adapter_state(काष्ठा hotplug_slot *slot, u8 *state)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	uपूर्णांक8_t presence = OPAL_PCI_SLOT_EMPTY;
	पूर्णांक ret;

	/*
	 * Retrieve presence status from firmware. If we can't
	 * get that, it will fail back to be empty.
	 */
	ret = pnv_pci_get_presence_state(php_slot->id, &presence);
	अगर (ret >= 0) अणु
		*state = presence;
		ret = 0;
	पूर्ण अन्यथा अणु
		SLOT_WARN(php_slot, "Error %d getting presence\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pnv_php_get_attention_state(काष्ठा hotplug_slot *slot, u8 *state)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);

	*state = php_slot->attention_state;
	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_set_attention_state(काष्ठा hotplug_slot *slot, u8 state)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	काष्ठा pci_dev *bridge = php_slot->pdev;
	u16 new, mask;

	php_slot->attention_state = state;
	अगर (!bridge)
		वापस 0;

	mask = PCI_EXP_SLTCTL_AIC;

	अगर (state)
		new = PCI_EXP_SLTCTL_ATTN_IND_ON;
	अन्यथा
		new = PCI_EXP_SLTCTL_ATTN_IND_OFF;

	pcie_capability_clear_and_set_word(bridge, PCI_EXP_SLTCTL, mask, new);

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_enable(काष्ठा pnv_php_slot *php_slot, bool rescan)
अणु
	काष्ठा hotplug_slot *slot = &php_slot->slot;
	uपूर्णांक8_t presence = OPAL_PCI_SLOT_EMPTY;
	uपूर्णांक8_t घातer_status = OPAL_PCI_SLOT_POWER_ON;
	पूर्णांक ret;

	/* Check अगर the slot has been configured */
	अगर (php_slot->state != PNV_PHP_STATE_REGISTERED)
		वापस 0;

	/* Retrieve slot presence status */
	ret = pnv_php_get_adapter_state(slot, &presence);
	अगर (ret)
		वापस ret;

	/*
	 * Proceed अगर there have nothing behind the slot. However,
	 * we should leave the slot in रेजिस्टरed state at the
	 * beginning. Otherwise, the PCI devices inserted afterwards
	 * won't be probed and populated.
	 */
	अगर (presence == OPAL_PCI_SLOT_EMPTY) अणु
		अगर (!php_slot->घातer_state_check) अणु
			php_slot->घातer_state_check = true;

			वापस 0;
		पूर्ण

		जाओ scan;
	पूर्ण

	/*
	 * If the घातer supply to the slot is off, we can't detect
	 * adapter presence state. That means we have to turn the
	 * slot on beक्रमe going to probe slot's presence state.
	 *
	 * On the first समय, we करोn't change the घातer status to
	 * boost प्रणाली boot with assumption that the firmware
	 * supplies consistent slot घातer status: empty slot always
	 * has its घातer off and non-empty slot has its घातer on.
	 */
	अगर (!php_slot->घातer_state_check) अणु
		php_slot->घातer_state_check = true;

		ret = pnv_php_get_घातer_state(slot, &घातer_status);
		अगर (ret)
			वापस ret;

		अगर (घातer_status != OPAL_PCI_SLOT_POWER_ON)
			वापस 0;
	पूर्ण

	/* Check the घातer status. Scan the slot अगर it is alपढ़ोy on */
	ret = pnv_php_get_घातer_state(slot, &घातer_status);
	अगर (ret)
		वापस ret;

	अगर (घातer_status == OPAL_PCI_SLOT_POWER_ON)
		जाओ scan;

	/* Power is off, turn it on and then scan the slot */
	ret = pnv_php_set_slot_घातer_state(slot, OPAL_PCI_SLOT_POWER_ON);
	अगर (ret)
		वापस ret;

scan:
	अगर (presence == OPAL_PCI_SLOT_PRESENT) अणु
		अगर (rescan) अणु
			pci_lock_rescan_हटाओ();
			pci_hp_add_devices(php_slot->bus);
			pci_unlock_rescan_हटाओ();
		पूर्ण

		/* Rescan क्रम child hotpluggable slots */
		php_slot->state = PNV_PHP_STATE_POPULATED;
		अगर (rescan)
			pnv_php_रेजिस्टर(php_slot->dn);
	पूर्ण अन्यथा अणु
		php_slot->state = PNV_PHP_STATE_POPULATED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_reset_slot(काष्ठा hotplug_slot *slot, पूर्णांक probe)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	काष्ठा pci_dev *bridge = php_slot->pdev;
	uपूर्णांक16_t sts;

	/*
	 * The CAPI folks want pnv_php to drive OpenCAPI slots
	 * which करोn't have a bridge. Only claim to support
	 * reset_slot() अगर we have a bridge device (क्रम now...)
	 */
	अगर (probe)
		वापस !bridge;

	/* mask our पूर्णांकerrupt जबतक resetting the bridge */
	अगर (php_slot->irq > 0)
		disable_irq(php_slot->irq);

	pci_bridge_secondary_bus_reset(bridge);

	/* clear any state changes that happened due to the reset */
	pcie_capability_पढ़ो_word(php_slot->pdev, PCI_EXP_SLTSTA, &sts);
	sts &= (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
	pcie_capability_ग_लिखो_word(php_slot->pdev, PCI_EXP_SLTSTA, sts);

	अगर (php_slot->irq > 0)
		enable_irq(php_slot->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_enable_slot(काष्ठा hotplug_slot *slot)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);

	वापस pnv_php_enable(php_slot, true);
पूर्ण

अटल पूर्णांक pnv_php_disable_slot(काष्ठा hotplug_slot *slot)
अणु
	काष्ठा pnv_php_slot *php_slot = to_pnv_php_slot(slot);
	पूर्णांक ret;

	/*
	 * Allow to disable a slot alपढ़ोy in the रेजिस्टरed state to
	 * cover हालs where the slot couldn't be enabled and never
	 * reached the populated state
	 */
	अगर (php_slot->state != PNV_PHP_STATE_POPULATED &&
	    php_slot->state != PNV_PHP_STATE_REGISTERED)
		वापस 0;

	/* Remove all devices behind the slot */
	pci_lock_rescan_हटाओ();
	pci_hp_हटाओ_devices(php_slot->bus);
	pci_unlock_rescan_हटाओ();

	/* Detach the child hotpluggable slots */
	pnv_php_unरेजिस्टर(php_slot->dn);

	/* Notअगरy firmware and हटाओ device nodes */
	ret = pnv_php_set_slot_घातer_state(slot, OPAL_PCI_SLOT_POWER_OFF);

	php_slot->state = PNV_PHP_STATE_REGISTERED;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hotplug_slot_ops php_slot_ops = अणु
	.get_घातer_status	= pnv_php_get_घातer_state,
	.get_adapter_status	= pnv_php_get_adapter_state,
	.get_attention_status	= pnv_php_get_attention_state,
	.set_attention_status	= pnv_php_set_attention_state,
	.enable_slot		= pnv_php_enable_slot,
	.disable_slot		= pnv_php_disable_slot,
	.reset_slot		= pnv_php_reset_slot,
पूर्ण;

अटल व्योम pnv_php_release(काष्ठा pnv_php_slot *php_slot)
अणु
	अचिन्हित दीर्घ flags;

	/* Remove from global or child list */
	spin_lock_irqsave(&pnv_php_lock, flags);
	list_del(&php_slot->link);
	spin_unlock_irqrestore(&pnv_php_lock, flags);

	/* Detach from parent */
	pnv_php_put_slot(php_slot);
	pnv_php_put_slot(php_slot->parent);
पूर्ण

अटल काष्ठा pnv_php_slot *pnv_php_alloc_slot(काष्ठा device_node *dn)
अणु
	काष्ठा pnv_php_slot *php_slot;
	काष्ठा pci_bus *bus;
	स्थिर अक्षर *label;
	uपूर्णांक64_t id;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(dn, "ibm,slot-label", &label);
	अगर (ret)
		वापस शून्य;

	अगर (pnv_pci_get_slot_id(dn, &id))
		वापस शून्य;

	bus = pci_find_bus_by_node(dn);
	अगर (!bus)
		वापस शून्य;

	php_slot = kzalloc(माप(*php_slot), GFP_KERNEL);
	अगर (!php_slot)
		वापस शून्य;

	php_slot->name = kstrdup(label, GFP_KERNEL);
	अगर (!php_slot->name) अणु
		kमुक्त(php_slot);
		वापस शून्य;
	पूर्ण

	अगर (dn->child && PCI_DN(dn->child))
		php_slot->slot_no = PCI_SLOT(PCI_DN(dn->child)->devfn);
	अन्यथा
		php_slot->slot_no = -1;   /* Placeholder slot */

	kref_init(&php_slot->kref);
	php_slot->state	                = PNV_PHP_STATE_INITIALIZED;
	php_slot->dn	                = dn;
	php_slot->pdev	                = bus->self;
	php_slot->bus	                = bus;
	php_slot->id	                = id;
	php_slot->घातer_state_check     = false;
	php_slot->slot.ops              = &php_slot_ops;

	INIT_LIST_HEAD(&php_slot->children);
	INIT_LIST_HEAD(&php_slot->link);

	वापस php_slot;
पूर्ण

अटल पूर्णांक pnv_php_रेजिस्टर_slot(काष्ठा pnv_php_slot *php_slot)
अणु
	काष्ठा pnv_php_slot *parent;
	काष्ठा device_node *dn = php_slot->dn;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Check अगर the slot is रेजिस्टरed or not */
	parent = pnv_php_find_slot(php_slot->dn);
	अगर (parent) अणु
		pnv_php_put_slot(parent);
		वापस -EEXIST;
	पूर्ण

	/* Register PCI slot */
	ret = pci_hp_रेजिस्टर(&php_slot->slot, php_slot->bus,
			      php_slot->slot_no, php_slot->name);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d registering slot\n", ret);
		वापस ret;
	पूर्ण

	/* Attach to the parent's child list or global list */
	जबतक ((dn = of_get_parent(dn))) अणु
		अगर (!PCI_DN(dn)) अणु
			of_node_put(dn);
			अवरोध;
		पूर्ण

		parent = pnv_php_find_slot(dn);
		अगर (parent) अणु
			of_node_put(dn);
			अवरोध;
		पूर्ण

		of_node_put(dn);
	पूर्ण

	spin_lock_irqsave(&pnv_php_lock, flags);
	php_slot->parent = parent;
	अगर (parent)
		list_add_tail(&php_slot->link, &parent->children);
	अन्यथा
		list_add_tail(&php_slot->link, &pnv_php_slot_list);
	spin_unlock_irqrestore(&pnv_php_lock, flags);

	php_slot->state = PNV_PHP_STATE_REGISTERED;
	वापस 0;
पूर्ण

अटल पूर्णांक pnv_php_enable_msix(काष्ठा pnv_php_slot *php_slot)
अणु
	काष्ठा pci_dev *pdev = php_slot->pdev;
	काष्ठा msix_entry entry;
	पूर्णांक nr_entries, ret;
	u16 pcie_flag;

	/* Get total number of MSIx entries */
	nr_entries = pci_msix_vec_count(pdev);
	अगर (nr_entries < 0)
		वापस nr_entries;

	/* Check hotplug MSIx entry is in range */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_FLAGS, &pcie_flag);
	entry.entry = (pcie_flag & PCI_EXP_FLAGS_IRQ) >> 9;
	अगर (entry.entry >= nr_entries)
		वापस -दुस्फल;

	/* Enable MSIx */
	ret = pci_enable_msix_exact(pdev, &entry, 1);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d enabling MSIx\n", ret);
		वापस ret;
	पूर्ण

	वापस entry.vector;
पूर्ण

अटल व्योम pnv_php_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pnv_php_event *event =
		container_of(work, काष्ठा pnv_php_event, work);
	काष्ठा pnv_php_slot *php_slot = event->php_slot;

	अगर (event->added)
		pnv_php_enable_slot(&php_slot->slot);
	अन्यथा
		pnv_php_disable_slot(&php_slot->slot);

	kमुक्त(event);
पूर्ण

अटल irqवापस_t pnv_php_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pnv_php_slot *php_slot = data;
	काष्ठा pci_dev *pchild, *pdev = php_slot->pdev;
	काष्ठा eeh_dev *edev;
	काष्ठा eeh_pe *pe;
	काष्ठा pnv_php_event *event;
	u16 sts, lsts;
	u8 presence;
	bool added;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &sts);
	sts &= (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA, sts);

	pci_dbg(pdev, "PCI slot [%s]: HP int! DLAct: %d, PresDet: %d\n",
			php_slot->name,
			!!(sts & PCI_EXP_SLTSTA_DLLSC),
			!!(sts & PCI_EXP_SLTSTA_PDC));

	अगर (sts & PCI_EXP_SLTSTA_DLLSC) अणु
		pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKSTA, &lsts);
		added = !!(lsts & PCI_EXP_LNKSTA_DLLLA);
	पूर्ण अन्यथा अगर (!(php_slot->flags & PNV_PHP_FLAG_BROKEN_PDC) &&
		   (sts & PCI_EXP_SLTSTA_PDC)) अणु
		ret = pnv_pci_get_presence_state(php_slot->id, &presence);
		अगर (ret) अणु
			SLOT_WARN(php_slot,
				  "PCI slot [%s] error %d getting presence (0x%04x), to retry the operation.\n",
				  php_slot->name, ret, sts);
			वापस IRQ_HANDLED;
		पूर्ण

		added = !!(presence == OPAL_PCI_SLOT_PRESENT);
	पूर्ण अन्यथा अणु
		pci_dbg(pdev, "PCI slot [%s]: Spurious IRQ?\n", php_slot->name);
		वापस IRQ_NONE;
	पूर्ण

	/* Freeze the हटाओd PE to aव्योम unexpected error reporting */
	अगर (!added) अणु
		pchild = list_first_entry_or_null(&php_slot->bus->devices,
						  काष्ठा pci_dev, bus_list);
		edev = pchild ? pci_dev_to_eeh_dev(pchild) : शून्य;
		pe = edev ? edev->pe : शून्य;
		अगर (pe) अणु
			eeh_serialize_lock(&flags);
			eeh_pe_mark_isolated(pe);
			eeh_serialize_unlock(flags);
			eeh_pe_set_option(pe, EEH_OPT_FREEZE_PE);
		पूर्ण
	पूर्ण

	/*
	 * The PE is left in frozen state अगर the event is missed. It's
	 * fine as the PCI devices (PE) aren't functional any more.
	 */
	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event) अणु
		SLOT_WARN(php_slot,
			  "PCI slot [%s] missed hotplug event 0x%04x\n",
			  php_slot->name, sts);
		वापस IRQ_HANDLED;
	पूर्ण

	pci_info(pdev, "PCI slot [%s] %s (IRQ: %d)\n",
		 php_slot->name, added ? "added" : "removed", irq);
	INIT_WORK(&event->work, pnv_php_event_handler);
	event->added = added;
	event->php_slot = php_slot;
	queue_work(php_slot->wq, &event->work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pnv_php_init_irq(काष्ठा pnv_php_slot *php_slot, पूर्णांक irq)
अणु
	काष्ठा pci_dev *pdev = php_slot->pdev;
	u32 broken_pdc = 0;
	u16 sts, ctrl;
	पूर्णांक ret;

	/* Allocate workqueue */
	php_slot->wq = alloc_workqueue("pciehp-%s", 0, 0, php_slot->name);
	अगर (!php_slot->wq) अणु
		SLOT_WARN(php_slot, "Cannot alloc workqueue\n");
		pnv_php_disable_irq(php_slot, true);
		वापस;
	पूर्ण

	/* Check PDC (Presence Detection Change) is broken or not */
	ret = of_property_पढ़ो_u32(php_slot->dn, "ibm,slot-broken-pdc",
				   &broken_pdc);
	अगर (!ret && broken_pdc)
		php_slot->flags |= PNV_PHP_FLAG_BROKEN_PDC;

	/* Clear pending पूर्णांकerrupts */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTSTA, &sts);
	अगर (php_slot->flags & PNV_PHP_FLAG_BROKEN_PDC)
		sts |= PCI_EXP_SLTSTA_DLLSC;
	अन्यथा
		sts |= (PCI_EXP_SLTSTA_PDC | PCI_EXP_SLTSTA_DLLSC);
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTSTA, sts);

	/* Request the पूर्णांकerrupt */
	ret = request_irq(irq, pnv_php_पूर्णांकerrupt, IRQF_SHARED,
			  php_slot->name, php_slot);
	अगर (ret) अणु
		pnv_php_disable_irq(php_slot, true);
		SLOT_WARN(php_slot, "Error %d enabling IRQ %d\n", ret, irq);
		वापस;
	पूर्ण

	/* Enable the पूर्णांकerrupts */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_SLTCTL, &ctrl);
	अगर (php_slot->flags & PNV_PHP_FLAG_BROKEN_PDC) अणु
		ctrl &= ~PCI_EXP_SLTCTL_PDCE;
		ctrl |= (PCI_EXP_SLTCTL_HPIE |
			 PCI_EXP_SLTCTL_DLLSCE);
	पूर्ण अन्यथा अणु
		ctrl |= (PCI_EXP_SLTCTL_HPIE |
			 PCI_EXP_SLTCTL_PDCE |
			 PCI_EXP_SLTCTL_DLLSCE);
	पूर्ण
	pcie_capability_ग_लिखो_word(pdev, PCI_EXP_SLTCTL, ctrl);

	/* The पूर्णांकerrupt is initialized successfully when @irq is valid */
	php_slot->irq = irq;
पूर्ण

अटल व्योम pnv_php_enable_irq(काष्ठा pnv_php_slot *php_slot)
अणु
	काष्ठा pci_dev *pdev = php_slot->pdev;
	पूर्णांक irq, ret;

	/*
	 * The MSI/MSIx पूर्णांकerrupt might have been occupied by other
	 * drivers. Don't populate the surprise hotplug capability
	 * in that हाल.
	 */
	अगर (pci_dev_msi_enabled(pdev))
		वापस;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		SLOT_WARN(php_slot, "Error %d enabling device\n", ret);
		वापस;
	पूर्ण

	pci_set_master(pdev);

	/* Enable MSIx पूर्णांकerrupt */
	irq = pnv_php_enable_msix(php_slot);
	अगर (irq > 0) अणु
		pnv_php_init_irq(php_slot, irq);
		वापस;
	पूर्ण

	/*
	 * Use MSI अगर MSIx करोesn't work. Fail back to legacy INTx
	 * अगर MSI करोesn't work either
	 */
	ret = pci_enable_msi(pdev);
	अगर (!ret || pdev->irq) अणु
		irq = pdev->irq;
		pnv_php_init_irq(php_slot, irq);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_php_रेजिस्टर_one(काष्ठा device_node *dn)
अणु
	काष्ठा pnv_php_slot *php_slot;
	u32 prop32;
	पूर्णांक ret;

	/* Check अगर it's hotpluggable slot */
	ret = of_property_पढ़ो_u32(dn, "ibm,slot-pluggable", &prop32);
	अगर (ret || !prop32)
		वापस -ENXIO;

	ret = of_property_पढ़ो_u32(dn, "ibm,reset-by-firmware", &prop32);
	अगर (ret || !prop32)
		वापस -ENXIO;

	php_slot = pnv_php_alloc_slot(dn);
	अगर (!php_slot)
		वापस -ENODEV;

	ret = pnv_php_रेजिस्टर_slot(php_slot);
	अगर (ret)
		जाओ मुक्त_slot;

	ret = pnv_php_enable(php_slot, false);
	अगर (ret)
		जाओ unरेजिस्टर_slot;

	/* Enable पूर्णांकerrupt अगर the slot supports surprise hotplug */
	ret = of_property_पढ़ो_u32(dn, "ibm,slot-surprise-pluggable", &prop32);
	अगर (!ret && prop32)
		pnv_php_enable_irq(php_slot);

	वापस 0;

unरेजिस्टर_slot:
	pnv_php_unरेजिस्टर_one(php_slot->dn);
मुक्त_slot:
	pnv_php_put_slot(php_slot);
	वापस ret;
पूर्ण

अटल व्योम pnv_php_रेजिस्टर(काष्ठा device_node *dn)
अणु
	काष्ठा device_node *child;

	/*
	 * The parent slots should be रेजिस्टरed beक्रमe their
	 * child slots.
	 */
	क्रम_each_child_of_node(dn, child) अणु
		pnv_php_रेजिस्टर_one(child);
		pnv_php_रेजिस्टर(child);
	पूर्ण
पूर्ण

अटल व्योम pnv_php_unरेजिस्टर_one(काष्ठा device_node *dn)
अणु
	काष्ठा pnv_php_slot *php_slot;

	php_slot = pnv_php_find_slot(dn);
	अगर (!php_slot)
		वापस;

	php_slot->state = PNV_PHP_STATE_OFFLINE;
	pci_hp_deरेजिस्टर(&php_slot->slot);
	pnv_php_release(php_slot);
	pnv_php_put_slot(php_slot);
पूर्ण

अटल व्योम pnv_php_unरेजिस्टर(काष्ठा device_node *dn)
अणु
	काष्ठा device_node *child;

	/* The child slots should go beक्रमe their parent slots */
	क्रम_each_child_of_node(dn, child) अणु
		pnv_php_unरेजिस्टर(child);
		pnv_php_unरेजिस्टर_one(child);
	पूर्ण
पूर्ण

अटल पूर्णांक __init pnv_php_init(व्योम)
अणु
	काष्ठा device_node *dn;

	pr_info(DRIVER_DESC " version: " DRIVER_VERSION "\n");
	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda2-phb")
		pnv_php_रेजिस्टर(dn);

	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda3-phb")
		pnv_php_रेजिस्टर(dn);

	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda2-npu2-opencapi-phb")
		pnv_php_रेजिस्टर_one(dn); /* slot directly under the PHB */
	वापस 0;
पूर्ण

अटल व्योम __निकास pnv_php_निकास(व्योम)
अणु
	काष्ठा device_node *dn;

	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda2-phb")
		pnv_php_unरेजिस्टर(dn);

	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda3-phb")
		pnv_php_unरेजिस्टर(dn);

	क्रम_each_compatible_node(dn, शून्य, "ibm,ioda2-npu2-opencapi-phb")
		pnv_php_unरेजिस्टर_one(dn); /* slot directly under the PHB */
पूर्ण

module_init(pnv_php_init);
module_निकास(pnv_php_निकास);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
