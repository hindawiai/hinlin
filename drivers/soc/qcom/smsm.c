<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>

/*
 * This driver implements the Qualcomm Shared Memory State Machine, a mechanism
 * क्रम communicating single bit state inक्रमmation to remote processors.
 *
 * The implementation is based on two sections of shared memory; the first
 * holding the state bits and the second holding a matrix of subscription bits.
 *
 * The state bits are काष्ठाured in entries of 32 bits, each beदीर्घing to one
 * प्रणाली in the SoC. The entry beदीर्घing to the local प्रणाली is considered
 * पढ़ो-ग_लिखो, जबतक the rest should be considered पढ़ो-only.
 *
 * The subscription matrix consists of N biपंचांगaps per entry, denoting पूर्णांकerest
 * in updates of the entry क्रम each of the N hosts. Upon updating a state bit
 * each host's subscription biपंचांगap should be queried and the remote प्रणाली
 * should be पूर्णांकerrupted अगर they request so.
 *
 * The subscription matrix is laid out in entry-major order:
 * entry0: [host0 ... hostN]
 *	.
 *	.
 * entryM: [host0 ... hostN]
 *
 * A third, optional, shared memory region might contain inक्रमmation regarding
 * the number of entries in the state biपंचांगap as well as number of columns in
 * the subscription matrix.
 */

/*
 * Shared memory identअगरiers, used to acquire handles to respective memory
 * region.
 */
#घोषणा SMEM_SMSM_SHARED_STATE		85
#घोषणा SMEM_SMSM_CPU_INTR_MASK		333
#घोषणा SMEM_SMSM_SIZE_INFO		419

/*
 * Default sizes, in हाल SMEM_SMSM_SIZE_INFO is not found.
 */
#घोषणा SMSM_DEFAULT_NUM_ENTRIES	8
#घोषणा SMSM_DEFAULT_NUM_HOSTS		3

काष्ठा smsm_entry;
काष्ठा smsm_host;

/**
 * काष्ठा qcom_smsm - smsm driver context
 * @dev:	smsm device poपूर्णांकer
 * @local_host:	column in the subscription matrix representing this प्रणाली
 * @num_hosts:	number of columns in the subscription matrix
 * @num_entries: number of entries in the state map and rows in the subscription
 *		matrix
 * @local_state: poपूर्णांकer to the local processor's state bits
 * @subscription: poपूर्णांकer to local processor's row in subscription matrix
 * @state:	smem state handle
 * @lock:	spinlock क्रम पढ़ो-modअगरy-ग_लिखो of the outgoing state
 * @entries:	context क्रम each of the entries
 * @hosts:	context क्रम each of the hosts
 */
काष्ठा qcom_smsm अणु
	काष्ठा device *dev;

	u32 local_host;

	u32 num_hosts;
	u32 num_entries;

	u32 *local_state;
	u32 *subscription;
	काष्ठा qcom_smem_state *state;

	spinlock_t lock;

	काष्ठा smsm_entry *entries;
	काष्ठा smsm_host *hosts;
पूर्ण;

/**
 * काष्ठा smsm_entry - per remote processor entry context
 * @smsm:	back-reference to driver context
 * @करोमुख्य:	IRQ करोमुख्य क्रम this entry, अगर representing a remote प्रणाली
 * @irq_enabled: biपंचांगap of which state bits IRQs are enabled
 * @irq_rising:	biपंचांगap tracking अगर rising bits should be propagated
 * @irq_falling: biपंचांगap tracking अगर falling bits should be propagated
 * @last_value:	snapshot of state bits last समय the पूर्णांकerrupts where propagated
 * @remote_state: poपूर्णांकer to this entry's state bits
 * @subscription: poपूर्णांकer to a row in the subscription matrix representing this
 *		entry
 */
काष्ठा smsm_entry अणु
	काष्ठा qcom_smsm *smsm;

	काष्ठा irq_करोमुख्य *करोमुख्य;
	DECLARE_BITMAP(irq_enabled, 32);
	DECLARE_BITMAP(irq_rising, 32);
	DECLARE_BITMAP(irq_falling, 32);
	u32 last_value;

	u32 *remote_state;
	u32 *subscription;
पूर्ण;

/**
 * काष्ठा smsm_host - representation of a remote host
 * @ipc_regmap:	regmap क्रम outgoing पूर्णांकerrupt
 * @ipc_offset:	offset in @ipc_regmap क्रम outgoing पूर्णांकerrupt
 * @ipc_bit:	bit in @ipc_regmap + @ipc_offset क्रम outgoing पूर्णांकerrupt
 */
काष्ठा smsm_host अणु
	काष्ठा regmap *ipc_regmap;
	पूर्णांक ipc_offset;
	पूर्णांक ipc_bit;
पूर्ण;

/**
 * smsm_update_bits() - change bit in outgoing entry and inक्रमm subscribers
 * @data:	smsm context poपूर्णांकer
 * @mask:	value mask
 * @value:	new value
 *
 * Used to set and clear the bits in the outgoing/local entry and inक्रमm
 * subscribers about the change.
 */
अटल पूर्णांक smsm_update_bits(व्योम *data, u32 mask, u32 value)
अणु
	काष्ठा qcom_smsm *smsm = data;
	काष्ठा smsm_host *hostp;
	अचिन्हित दीर्घ flags;
	u32 changes;
	u32 host;
	u32 orig;
	u32 val;

	spin_lock_irqsave(&smsm->lock, flags);

	/* Update the entry */
	val = orig = पढ़ोl(smsm->local_state);
	val &= ~mask;
	val |= value;

	/* Don't signal if we didn't change the value */
	changes = val ^ orig;
	अगर (!changes) अणु
		spin_unlock_irqrestore(&smsm->lock, flags);
		जाओ करोne;
	पूर्ण

	/* Write out the new value */
	ग_लिखोl(val, smsm->local_state);
	spin_unlock_irqrestore(&smsm->lock, flags);

	/* Make sure the value update is ordered beक्रमe any kicks */
	wmb();

	/* Iterate over all hosts to check whom wants a kick */
	क्रम (host = 0; host < smsm->num_hosts; host++) अणु
		hostp = &smsm->hosts[host];

		val = पढ़ोl(smsm->subscription + host);
		अगर (val & changes && hostp->ipc_regmap) अणु
			regmap_ग_लिखो(hostp->ipc_regmap,
				     hostp->ipc_offset,
				     BIT(hostp->ipc_bit));
		पूर्ण
	पूर्ण

करोne:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qcom_smem_state_ops smsm_state_ops = अणु
	.update_bits = smsm_update_bits,
पूर्ण;

/**
 * smsm_पूर्णांकr() - cascading IRQ handler क्रम SMSM
 * @irq:	unused
 * @data:	entry related to this IRQ
 *
 * This function cascades an incoming पूर्णांकerrupt from a remote प्रणाली, based on
 * the state bits and configuration.
 */
अटल irqवापस_t smsm_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smsm_entry *entry = data;
	अचिन्हित i;
	पूर्णांक irq_pin;
	u32 changed;
	u32 val;

	val = पढ़ोl(entry->remote_state);
	changed = val ^ entry->last_value;
	entry->last_value = val;

	क्रम_each_set_bit(i, entry->irq_enabled, 32) अणु
		अगर (!(changed & BIT(i)))
			जारी;

		अगर (val & BIT(i)) अणु
			अगर (test_bit(i, entry->irq_rising)) अणु
				irq_pin = irq_find_mapping(entry->करोमुख्य, i);
				handle_nested_irq(irq_pin);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (test_bit(i, entry->irq_falling)) अणु
				irq_pin = irq_find_mapping(entry->करोमुख्य, i);
				handle_nested_irq(irq_pin);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * smsm_mask_irq() - un-subscribe from cascades of IRQs of a certain staus bit
 * @irqd:	IRQ handle to be masked
 *
 * This un-subscribes the local CPU from पूर्णांकerrupts upon changes to the defines
 * status bit. The bit is also cleared from cascading.
 */
अटल व्योम smsm_mask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा smsm_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);
	काष्ठा qcom_smsm *smsm = entry->smsm;
	u32 val;

	अगर (entry->subscription) अणु
		val = पढ़ोl(entry->subscription + smsm->local_host);
		val &= ~BIT(irq);
		ग_लिखोl(val, entry->subscription + smsm->local_host);
	पूर्ण

	clear_bit(irq, entry->irq_enabled);
पूर्ण

/**
 * smsm_unmask_irq() - subscribe to cascades of IRQs of a certain status bit
 * @irqd:	IRQ handle to be unmasked
 *
 * This subscribes the local CPU to पूर्णांकerrupts upon changes to the defined
 * status bit. The bit is also marked क्रम cascading.
 */
अटल व्योम smsm_unmask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा smsm_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);
	काष्ठा qcom_smsm *smsm = entry->smsm;
	u32 val;

	set_bit(irq, entry->irq_enabled);

	अगर (entry->subscription) अणु
		val = पढ़ोl(entry->subscription + smsm->local_host);
		val |= BIT(irq);
		ग_लिखोl(val, entry->subscription + smsm->local_host);
	पूर्ण
पूर्ण

/**
 * smsm_set_irq_type() - updates the requested IRQ type क्रम the cascading
 * @irqd:	consumer पूर्णांकerrupt handle
 * @type:	requested flags
 */
अटल पूर्णांक smsm_set_irq_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा smsm_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);

	अगर (!(type & IRQ_TYPE_EDGE_BOTH))
		वापस -EINVAL;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		set_bit(irq, entry->irq_rising);
	अन्यथा
		clear_bit(irq, entry->irq_rising);

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		set_bit(irq, entry->irq_falling);
	अन्यथा
		clear_bit(irq, entry->irq_falling);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip smsm_irq_chip = अणु
	.name           = "smsm",
	.irq_mask       = smsm_mask_irq,
	.irq_unmask     = smsm_unmask_irq,
	.irq_set_type	= smsm_set_irq_type,
पूर्ण;

/**
 * smsm_irq_map() - sets up a mapping क्रम a cascaded IRQ
 * @d:		IRQ करोमुख्य representing an entry
 * @irq:	IRQ to set up
 * @hw:		unused
 */
अटल पूर्णांक smsm_irq_map(काष्ठा irq_करोमुख्य *d,
			अचिन्हित पूर्णांक irq,
			irq_hw_number_t hw)
अणु
	काष्ठा smsm_entry *entry = d->host_data;

	irq_set_chip_and_handler(irq, &smsm_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, entry);
	irq_set_nested_thपढ़ो(irq, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops smsm_irq_ops = अणु
	.map = smsm_irq_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

/**
 * smsm_parse_ipc() - parses a qcom,ipc-%d device tree property
 * @smsm:	smsm driver context
 * @host_id:	index of the remote host to be resolved
 *
 * Parses device tree to acquire the inक्रमmation needed क्रम sending the
 * outgoing पूर्णांकerrupts to a remote host - identअगरied by @host_id.
 */
अटल पूर्णांक smsm_parse_ipc(काष्ठा qcom_smsm *smsm, अचिन्हित host_id)
अणु
	काष्ठा device_node *syscon;
	काष्ठा device_node *node = smsm->dev->of_node;
	काष्ठा smsm_host *host = &smsm->hosts[host_id];
	अक्षर key[16];
	पूर्णांक ret;

	snम_लिखो(key, माप(key), "qcom,ipc-%d", host_id);
	syscon = of_parse_phandle(node, key, 0);
	अगर (!syscon)
		वापस 0;

	host->ipc_regmap = syscon_node_to_regmap(syscon);
	अगर (IS_ERR(host->ipc_regmap))
		वापस PTR_ERR(host->ipc_regmap);

	ret = of_property_पढ़ो_u32_index(node, key, 1, &host->ipc_offset);
	अगर (ret < 0) अणु
		dev_err(smsm->dev, "no offset in %s\n", key);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(node, key, 2, &host->ipc_bit);
	अगर (ret < 0) अणु
		dev_err(smsm->dev, "no bit in %s\n", key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smsm_inbound_entry() - parse DT and set up an entry representing a remote प्रणाली
 * @smsm:	smsm driver context
 * @entry:	entry context to be set up
 * @node:	dt node containing the entry's properties
 */
अटल पूर्णांक smsm_inbound_entry(काष्ठा qcom_smsm *smsm,
			      काष्ठा smsm_entry *entry,
			      काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	पूर्णांक irq;

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq) अणु
		dev_err(smsm->dev, "failed to parse smsm interrupt\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(smsm->dev, irq,
					शून्य, smsm_पूर्णांकr,
					IRQF_ONESHOT,
					"smsm", (व्योम *)entry);
	अगर (ret) अणु
		dev_err(smsm->dev, "failed to request interrupt\n");
		वापस ret;
	पूर्ण

	entry->करोमुख्य = irq_करोमुख्य_add_linear(node, 32, &smsm_irq_ops, entry);
	अगर (!entry->करोमुख्य) अणु
		dev_err(smsm->dev, "failed to add irq_domain\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smsm_get_size_info() - parse the optional memory segment क्रम sizes
 * @smsm:	smsm driver context
 *
 * Attempt to acquire the number of hosts and entries from the optional shared
 * memory location. Not being able to find this segment should indicate that
 * we're on a older प्रणाली where these values was hard coded to
 * SMSM_DEFAULT_NUM_ENTRIES and SMSM_DEFAULT_NUM_HOSTS.
 *
 * Returns 0 on success, negative त्रुटि_सं on failure.
 */
अटल पूर्णांक smsm_get_size_info(काष्ठा qcom_smsm *smsm)
अणु
	माप_प्रकार size;
	काष्ठा अणु
		u32 num_hosts;
		u32 num_entries;
		u32 reserved0;
		u32 reserved1;
	पूर्ण *info;

	info = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SIZE_INFO, &size);
	अगर (IS_ERR(info) && PTR_ERR(info) != -ENOENT) अणु
		अगर (PTR_ERR(info) != -EPROBE_DEFER)
			dev_err(smsm->dev, "unable to retrieve smsm size info\n");
		वापस PTR_ERR(info);
	पूर्ण अन्यथा अगर (IS_ERR(info) || size != माप(*info)) अणु
		dev_warn(smsm->dev, "no smsm size info, using defaults\n");
		smsm->num_entries = SMSM_DEFAULT_NUM_ENTRIES;
		smsm->num_hosts = SMSM_DEFAULT_NUM_HOSTS;
		वापस 0;
	पूर्ण

	smsm->num_entries = info->num_entries;
	smsm->num_hosts = info->num_hosts;

	dev_dbg(smsm->dev,
		"found custom size of smsm: %d entries %d hosts\n",
		smsm->num_entries, smsm->num_hosts);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smsm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *local_node;
	काष्ठा device_node *node;
	काष्ठा smsm_entry *entry;
	काष्ठा qcom_smsm *smsm;
	u32 *पूर्णांकr_mask;
	माप_प्रकार size;
	u32 *states;
	u32 id;
	पूर्णांक ret;

	smsm = devm_kzalloc(&pdev->dev, माप(*smsm), GFP_KERNEL);
	अगर (!smsm)
		वापस -ENOMEM;
	smsm->dev = &pdev->dev;
	spin_lock_init(&smsm->lock);

	ret = smsm_get_size_info(smsm);
	अगर (ret)
		वापस ret;

	smsm->entries = devm_kसुस्मृति(&pdev->dev,
				     smsm->num_entries,
				     माप(काष्ठा smsm_entry),
				     GFP_KERNEL);
	अगर (!smsm->entries)
		वापस -ENOMEM;

	smsm->hosts = devm_kसुस्मृति(&pdev->dev,
				   smsm->num_hosts,
				   माप(काष्ठा smsm_host),
				   GFP_KERNEL);
	अगर (!smsm->hosts)
		वापस -ENOMEM;

	क्रम_each_child_of_node(pdev->dev.of_node, local_node) अणु
		अगर (of_find_property(local_node, "#qcom,smem-state-cells", शून्य))
			अवरोध;
	पूर्ण
	अगर (!local_node) अणु
		dev_err(&pdev->dev, "no state entry\n");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32(pdev->dev.of_node,
			     "qcom,local-host",
			     &smsm->local_host);

	/* Parse the host properties */
	क्रम (id = 0; id < smsm->num_hosts; id++) अणु
		ret = smsm_parse_ipc(smsm, id);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Acquire the मुख्य SMSM state vector */
	ret = qcom_smem_alloc(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SHARED_STATE,
			      smsm->num_entries * माप(u32));
	अगर (ret < 0 && ret != -EEXIST) अणु
		dev_err(&pdev->dev, "unable to allocate shared state entry\n");
		वापस ret;
	पूर्ण

	states = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_SHARED_STATE, शून्य);
	अगर (IS_ERR(states)) अणु
		dev_err(&pdev->dev, "Unable to acquire shared state entry\n");
		वापस PTR_ERR(states);
	पूर्ण

	/* Acquire the list of पूर्णांकerrupt mask vectors */
	size = smsm->num_entries * smsm->num_hosts * माप(u32);
	ret = qcom_smem_alloc(QCOM_SMEM_HOST_ANY, SMEM_SMSM_CPU_INTR_MASK, size);
	अगर (ret < 0 && ret != -EEXIST) अणु
		dev_err(&pdev->dev, "unable to allocate smsm interrupt mask\n");
		वापस ret;
	पूर्ण

	पूर्णांकr_mask = qcom_smem_get(QCOM_SMEM_HOST_ANY, SMEM_SMSM_CPU_INTR_MASK, शून्य);
	अगर (IS_ERR(पूर्णांकr_mask)) अणु
		dev_err(&pdev->dev, "unable to acquire shared memory interrupt mask\n");
		वापस PTR_ERR(पूर्णांकr_mask);
	पूर्ण

	/* Setup the reference to the local state bits */
	smsm->local_state = states + smsm->local_host;
	smsm->subscription = पूर्णांकr_mask + smsm->local_host * smsm->num_hosts;

	/* Register the outgoing state */
	smsm->state = qcom_smem_state_रेजिस्टर(local_node, &smsm_state_ops, smsm);
	अगर (IS_ERR(smsm->state)) अणु
		dev_err(smsm->dev, "failed to register qcom_smem_state\n");
		वापस PTR_ERR(smsm->state);
	पूर्ण

	/* Register handlers क्रम remote processor entries of पूर्णांकerest. */
	क्रम_each_available_child_of_node(pdev->dev.of_node, node) अणु
		अगर (!of_property_पढ़ो_bool(node, "interrupt-controller"))
			जारी;

		ret = of_property_पढ़ो_u32(node, "reg", &id);
		अगर (ret || id >= smsm->num_entries) अणु
			dev_err(&pdev->dev, "invalid reg of entry\n");
			अगर (!ret)
				ret = -EINVAL;
			जाओ unwind_पूर्णांकerfaces;
		पूर्ण
		entry = &smsm->entries[id];

		entry->smsm = smsm;
		entry->remote_state = states + id;

		/* Setup subscription poपूर्णांकers and unsubscribe to any kicks */
		entry->subscription = पूर्णांकr_mask + id * smsm->num_hosts;
		ग_लिखोl(0, entry->subscription + smsm->local_host);

		ret = smsm_inbound_entry(smsm, entry, node);
		अगर (ret < 0)
			जाओ unwind_पूर्णांकerfaces;
	पूर्ण

	platक्रमm_set_drvdata(pdev, smsm);

	वापस 0;

unwind_पूर्णांकerfaces:
	क्रम (id = 0; id < smsm->num_entries; id++)
		अगर (smsm->entries[id].करोमुख्य)
			irq_करोमुख्य_हटाओ(smsm->entries[id].करोमुख्य);

	qcom_smem_state_unरेजिस्टर(smsm->state);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_smsm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_smsm *smsm = platक्रमm_get_drvdata(pdev);
	अचिन्हित id;

	क्रम (id = 0; id < smsm->num_entries; id++)
		अगर (smsm->entries[id].करोमुख्य)
			irq_करोमुख्य_हटाओ(smsm->entries[id].करोमुख्य);

	qcom_smem_state_unरेजिस्टर(smsm->state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smsm_of_match[] = अणु
	अणु .compatible = "qcom,smsm" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_smsm_of_match);

अटल काष्ठा platक्रमm_driver qcom_smsm_driver = अणु
	.probe = qcom_smsm_probe,
	.हटाओ = qcom_smsm_हटाओ,
	.driver  = अणु
		.name  = "qcom-smsm",
		.of_match_table = qcom_smsm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_smsm_driver);

MODULE_DESCRIPTION("Qualcomm Shared Memory State Machine driver");
MODULE_LICENSE("GPL v2");
