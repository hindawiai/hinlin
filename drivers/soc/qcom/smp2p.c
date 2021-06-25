<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Sony Mobile Communications AB.
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>
#समावेश <linux/spinlock.h>

/*
 * The Shared Memory Poपूर्णांक to Poपूर्णांक (SMP2P) protocol facilitates communication
 * of a single 32-bit value between two processors.  Each value has a single
 * ग_लिखोr (the local side) and a single पढ़ोer (the remote side). Values are
 * uniquely identअगरied in the प्रणाली by the directed edge (local processor ID
 * to remote processor ID) and a string identअगरier.
 *
 * Each processor is responsible क्रम creating the outgoing SMEM items and each
 * item is writable by the local processor and पढ़ोable by the remote
 * processor.  By using two separate SMEM items that are single-पढ़ोer and
 * single-ग_लिखोr, SMP2P करोes not require any remote locking mechanisms.
 *
 * The driver uses the Linux GPIO and पूर्णांकerrupt framework to expose a भव
 * GPIO क्रम each outbound entry and a भव पूर्णांकerrupt controller क्रम each
 * inbound entry.
 */

#घोषणा SMP2P_MAX_ENTRY 16
#घोषणा SMP2P_MAX_ENTRY_NAME 16

#घोषणा SMP2P_FEATURE_SSR_ACK 0x1

#घोषणा SMP2P_MAGIC 0x504d5324

/**
 * काष्ठा smp2p_smem_item - in memory communication काष्ठाure
 * @magic:		magic number
 * @version:		version - must be 1
 * @features:		features flag - currently unused
 * @local_pid:		processor id of sending end
 * @remote_pid:		processor id of receiving end
 * @total_entries:	number of entries - always SMP2P_MAX_ENTRY
 * @valid_entries:	number of allocated entries
 * @flags:
 * @entries:		inभागidual communication entries
 *     @name:		name of the entry
 *     @value:		content of the entry
 */
काष्ठा smp2p_smem_item अणु
	u32 magic;
	u8 version;
	अचिन्हित features:24;
	u16 local_pid;
	u16 remote_pid;
	u16 total_entries;
	u16 valid_entries;
	u32 flags;

	काष्ठा अणु
		u8 name[SMP2P_MAX_ENTRY_NAME];
		u32 value;
	पूर्ण entries[SMP2P_MAX_ENTRY];
पूर्ण __packed;

/**
 * काष्ठा smp2p_entry - driver context matching one entry
 * @node:	list entry to keep track of allocated entries
 * @smp2p:	reference to the device driver context
 * @name:	name of the entry, to match against smp2p_smem_item
 * @value:	poपूर्णांकer to smp2p_smem_item entry value
 * @last_value:	last handled value
 * @करोमुख्य:	irq_करोमुख्य क्रम inbound entries
 * @irq_enabled:biपंचांगap to track enabled irq bits
 * @irq_rising:	biपंचांगap to mark irq bits क्रम rising detection
 * @irq_falling:biपंचांगap to mark irq bits क्रम falling detection
 * @state:	smem state handle
 * @lock:	spinlock to protect पढ़ो-modअगरy-ग_लिखो of the value
 */
काष्ठा smp2p_entry अणु
	काष्ठा list_head node;
	काष्ठा qcom_smp2p *smp2p;

	स्थिर अक्षर *name;
	u32 *value;
	u32 last_value;

	काष्ठा irq_करोमुख्य *करोमुख्य;
	DECLARE_BITMAP(irq_enabled, 32);
	DECLARE_BITMAP(irq_rising, 32);
	DECLARE_BITMAP(irq_falling, 32);

	काष्ठा qcom_smem_state *state;

	spinlock_t lock;
पूर्ण;

#घोषणा SMP2P_INBOUND	0
#घोषणा SMP2P_OUTBOUND	1

/**
 * काष्ठा qcom_smp2p - device driver context
 * @dev:	device driver handle
 * @in:		poपूर्णांकer to the inbound smem item
 * @out:	poपूर्णांकer to the outbound smem item
 * @smem_items:	ids of the two smem items
 * @valid_entries: alपढ़ोy scanned inbound entries
 * @local_pid:	processor id of the inbound edge
 * @remote_pid:	processor id of the outbound edge
 * @ipc_regmap:	regmap क्रम the outbound ipc
 * @ipc_offset:	offset within the regmap
 * @ipc_bit:	bit in regmap@offset to kick to संकेत remote processor
 * @mbox_client: mailbox client handle
 * @mbox_chan:	apcs ipc mailbox channel handle
 * @inbound:	list of inbound entries
 * @outbound:	list of outbound entries
 */
काष्ठा qcom_smp2p अणु
	काष्ठा device *dev;

	काष्ठा smp2p_smem_item *in;
	काष्ठा smp2p_smem_item *out;

	अचिन्हित smem_items[SMP2P_OUTBOUND + 1];

	अचिन्हित valid_entries;

	अचिन्हित local_pid;
	अचिन्हित remote_pid;

	काष्ठा regmap *ipc_regmap;
	पूर्णांक ipc_offset;
	पूर्णांक ipc_bit;

	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox_chan;

	काष्ठा list_head inbound;
	काष्ठा list_head outbound;
पूर्ण;

अटल व्योम qcom_smp2p_kick(काष्ठा qcom_smp2p *smp2p)
अणु
	/* Make sure any updated data is written beक्रमe the kick */
	wmb();

	अगर (smp2p->mbox_chan) अणु
		mbox_send_message(smp2p->mbox_chan, शून्य);
		mbox_client_txकरोne(smp2p->mbox_chan, 0);
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(smp2p->ipc_regmap, smp2p->ipc_offset, BIT(smp2p->ipc_bit));
	पूर्ण
पूर्ण

/**
 * qcom_smp2p_पूर्णांकr() - पूर्णांकerrupt handler क्रम incoming notअगरications
 * @irq:	unused
 * @data:	smp2p driver context
 *
 * Handle notअगरications from the remote side to handle newly allocated entries
 * or any changes to the state bits of existing entries.
 */
अटल irqवापस_t qcom_smp2p_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smp2p_smem_item *in;
	काष्ठा smp2p_entry *entry;
	काष्ठा qcom_smp2p *smp2p = data;
	अचिन्हित smem_id = smp2p->smem_items[SMP2P_INBOUND];
	अचिन्हित pid = smp2p->remote_pid;
	माप_प्रकार size;
	पूर्णांक irq_pin;
	u32 status;
	अक्षर buf[SMP2P_MAX_ENTRY_NAME];
	u32 val;
	पूर्णांक i;

	in = smp2p->in;

	/* Acquire smem item, अगर not alपढ़ोy found */
	अगर (!in) अणु
		in = qcom_smem_get(pid, smem_id, &size);
		अगर (IS_ERR(in)) अणु
			dev_err(smp2p->dev,
				"Unable to acquire remote smp2p item\n");
			वापस IRQ_HANDLED;
		पूर्ण

		smp2p->in = in;
	पूर्ण

	/* Match newly created entries */
	क्रम (i = smp2p->valid_entries; i < in->valid_entries; i++) अणु
		list_क्रम_each_entry(entry, &smp2p->inbound, node) अणु
			स_नकल(buf, in->entries[i].name, माप(buf));
			अगर (!म_भेद(buf, entry->name)) अणु
				entry->value = &in->entries[i].value;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	smp2p->valid_entries = i;

	/* Fire पूर्णांकerrupts based on any value changes */
	list_क्रम_each_entry(entry, &smp2p->inbound, node) अणु
		/* Ignore entries not yet allocated by the remote side */
		अगर (!entry->value)
			जारी;

		val = पढ़ोl(entry->value);

		status = val ^ entry->last_value;
		entry->last_value = val;

		/* No changes of this entry? */
		अगर (!status)
			जारी;

		क्रम_each_set_bit(i, entry->irq_enabled, 32) अणु
			अगर (!(status & BIT(i)))
				जारी;

			अगर ((val & BIT(i) && test_bit(i, entry->irq_rising)) ||
			    (!(val & BIT(i)) && test_bit(i, entry->irq_falling))) अणु
				irq_pin = irq_find_mapping(entry->करोमुख्य, i);
				handle_nested_irq(irq_pin);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smp2p_mask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा smp2p_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);

	clear_bit(irq, entry->irq_enabled);
पूर्ण

अटल व्योम smp2p_unmask_irq(काष्ठा irq_data *irqd)
अणु
	काष्ठा smp2p_entry *entry = irq_data_get_irq_chip_data(irqd);
	irq_hw_number_t irq = irqd_to_hwirq(irqd);

	set_bit(irq, entry->irq_enabled);
पूर्ण

अटल पूर्णांक smp2p_set_irq_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा smp2p_entry *entry = irq_data_get_irq_chip_data(irqd);
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

अटल काष्ठा irq_chip smp2p_irq_chip = अणु
	.name           = "smp2p",
	.irq_mask       = smp2p_mask_irq,
	.irq_unmask     = smp2p_unmask_irq,
	.irq_set_type	= smp2p_set_irq_type,
पूर्ण;

अटल पूर्णांक smp2p_irq_map(काष्ठा irq_करोमुख्य *d,
			 अचिन्हित पूर्णांक irq,
			 irq_hw_number_t hw)
अणु
	काष्ठा smp2p_entry *entry = d->host_data;

	irq_set_chip_and_handler(irq, &smp2p_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, entry);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops smp2p_irq_ops = अणु
	.map = smp2p_irq_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक qcom_smp2p_inbound_entry(काष्ठा qcom_smp2p *smp2p,
				    काष्ठा smp2p_entry *entry,
				    काष्ठा device_node *node)
अणु
	entry->करोमुख्य = irq_करोमुख्य_add_linear(node, 32, &smp2p_irq_ops, entry);
	अगर (!entry->करोमुख्य) अणु
		dev_err(smp2p->dev, "failed to add irq_domain\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smp2p_update_bits(व्योम *data, u32 mask, u32 value)
अणु
	काष्ठा smp2p_entry *entry = data;
	अचिन्हित दीर्घ flags;
	u32 orig;
	u32 val;

	spin_lock_irqsave(&entry->lock, flags);
	val = orig = पढ़ोl(entry->value);
	val &= ~mask;
	val |= value;
	ग_लिखोl(val, entry->value);
	spin_unlock_irqrestore(&entry->lock, flags);

	अगर (val != orig)
		qcom_smp2p_kick(entry->smp2p);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा qcom_smem_state_ops smp2p_state_ops = अणु
	.update_bits = smp2p_update_bits,
पूर्ण;

अटल पूर्णांक qcom_smp2p_outbound_entry(काष्ठा qcom_smp2p *smp2p,
				     काष्ठा smp2p_entry *entry,
				     काष्ठा device_node *node)
अणु
	काष्ठा smp2p_smem_item *out = smp2p->out;
	अक्षर buf[SMP2P_MAX_ENTRY_NAME] = अणुपूर्ण;

	/* Allocate an entry from the smem item */
	strlcpy(buf, entry->name, SMP2P_MAX_ENTRY_NAME);
	स_नकल(out->entries[out->valid_entries].name, buf, SMP2P_MAX_ENTRY_NAME);

	/* Make the logical entry reference the physical value */
	entry->value = &out->entries[out->valid_entries].value;

	out->valid_entries++;

	entry->state = qcom_smem_state_रेजिस्टर(node, &smp2p_state_ops, entry);
	अगर (IS_ERR(entry->state)) अणु
		dev_err(smp2p->dev, "failed to register qcom_smem_state\n");
		वापस PTR_ERR(entry->state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smp2p_alloc_outbound_item(काष्ठा qcom_smp2p *smp2p)
अणु
	काष्ठा smp2p_smem_item *out;
	अचिन्हित smem_id = smp2p->smem_items[SMP2P_OUTBOUND];
	अचिन्हित pid = smp2p->remote_pid;
	पूर्णांक ret;

	ret = qcom_smem_alloc(pid, smem_id, माप(*out));
	अगर (ret < 0 && ret != -EEXIST) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(smp2p->dev,
				"unable to allocate local smp2p item\n");
		वापस ret;
	पूर्ण

	out = qcom_smem_get(pid, smem_id, शून्य);
	अगर (IS_ERR(out)) अणु
		dev_err(smp2p->dev, "Unable to acquire local smp2p item\n");
		वापस PTR_ERR(out);
	पूर्ण

	स_रखो(out, 0, माप(*out));
	out->magic = SMP2P_MAGIC;
	out->local_pid = smp2p->local_pid;
	out->remote_pid = smp2p->remote_pid;
	out->total_entries = SMP2P_MAX_ENTRY;
	out->valid_entries = 0;

	/*
	 * Make sure the rest of the header is written beक्रमe we validate the
	 * item by writing a valid version number.
	 */
	wmb();
	out->version = 1;

	qcom_smp2p_kick(smp2p);

	smp2p->out = out;

	वापस 0;
पूर्ण

अटल पूर्णांक smp2p_parse_ipc(काष्ठा qcom_smp2p *smp2p)
अणु
	काष्ठा device_node *syscon;
	काष्ठा device *dev = smp2p->dev;
	स्थिर अक्षर *key;
	पूर्णांक ret;

	syscon = of_parse_phandle(dev->of_node, "qcom,ipc", 0);
	अगर (!syscon) अणु
		dev_err(dev, "no qcom,ipc node\n");
		वापस -ENODEV;
	पूर्ण

	smp2p->ipc_regmap = syscon_node_to_regmap(syscon);
	अगर (IS_ERR(smp2p->ipc_regmap))
		वापस PTR_ERR(smp2p->ipc_regmap);

	key = "qcom,ipc";
	ret = of_property_पढ़ो_u32_index(dev->of_node, key, 1, &smp2p->ipc_offset);
	अगर (ret < 0) अणु
		dev_err(dev, "no offset in %s\n", key);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(dev->of_node, key, 2, &smp2p->ipc_bit);
	अगर (ret < 0) अणु
		dev_err(dev, "no bit in %s\n", key);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_smp2p_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smp2p_entry *entry;
	काष्ठा device_node *node;
	काष्ठा qcom_smp2p *smp2p;
	स्थिर अक्षर *key;
	पूर्णांक irq;
	पूर्णांक ret;

	smp2p = devm_kzalloc(&pdev->dev, माप(*smp2p), GFP_KERNEL);
	अगर (!smp2p)
		वापस -ENOMEM;

	smp2p->dev = &pdev->dev;
	INIT_LIST_HEAD(&smp2p->inbound);
	INIT_LIST_HEAD(&smp2p->outbound);

	platक्रमm_set_drvdata(pdev, smp2p);

	key = "qcom,smem";
	ret = of_property_पढ़ो_u32_array(pdev->dev.of_node, key,
					 smp2p->smem_items, 2);
	अगर (ret)
		वापस ret;

	key = "qcom,local-pid";
	ret = of_property_पढ़ो_u32(pdev->dev.of_node, key, &smp2p->local_pid);
	अगर (ret)
		जाओ report_पढ़ो_failure;

	key = "qcom,remote-pid";
	ret = of_property_पढ़ो_u32(pdev->dev.of_node, key, &smp2p->remote_pid);
	अगर (ret)
		जाओ report_पढ़ो_failure;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	smp2p->mbox_client.dev = &pdev->dev;
	smp2p->mbox_client.knows_txकरोne = true;
	smp2p->mbox_chan = mbox_request_channel(&smp2p->mbox_client, 0);
	अगर (IS_ERR(smp2p->mbox_chan)) अणु
		अगर (PTR_ERR(smp2p->mbox_chan) != -ENODEV)
			वापस PTR_ERR(smp2p->mbox_chan);

		smp2p->mbox_chan = शून्य;

		ret = smp2p_parse_ipc(smp2p);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = qcom_smp2p_alloc_outbound_item(smp2p);
	अगर (ret < 0)
		जाओ release_mbox;

	क्रम_each_available_child_of_node(pdev->dev.of_node, node) अणु
		entry = devm_kzalloc(&pdev->dev, माप(*entry), GFP_KERNEL);
		अगर (!entry) अणु
			ret = -ENOMEM;
			जाओ unwind_पूर्णांकerfaces;
		पूर्ण

		entry->smp2p = smp2p;
		spin_lock_init(&entry->lock);

		ret = of_property_पढ़ो_string(node, "qcom,entry-name", &entry->name);
		अगर (ret < 0)
			जाओ unwind_पूर्णांकerfaces;

		अगर (of_property_पढ़ो_bool(node, "interrupt-controller")) अणु
			ret = qcom_smp2p_inbound_entry(smp2p, entry, node);
			अगर (ret < 0)
				जाओ unwind_पूर्णांकerfaces;

			list_add(&entry->node, &smp2p->inbound);
		पूर्ण अन्यथा  अणु
			ret = qcom_smp2p_outbound_entry(smp2p, entry, node);
			अगर (ret < 0)
				जाओ unwind_पूर्णांकerfaces;

			list_add(&entry->node, &smp2p->outbound);
		पूर्ण
	पूर्ण

	/* Kick the outgoing edge after allocating entries */
	qcom_smp2p_kick(smp2p);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					शून्य, qcom_smp2p_पूर्णांकr,
					IRQF_ONESHOT,
					"smp2p", (व्योम *)smp2p);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request interrupt\n");
		जाओ unwind_पूर्णांकerfaces;
	पूर्ण


	वापस 0;

unwind_पूर्णांकerfaces:
	list_क्रम_each_entry(entry, &smp2p->inbound, node)
		irq_करोमुख्य_हटाओ(entry->करोमुख्य);

	list_क्रम_each_entry(entry, &smp2p->outbound, node)
		qcom_smem_state_unरेजिस्टर(entry->state);

	smp2p->out->valid_entries = 0;

release_mbox:
	mbox_मुक्त_channel(smp2p->mbox_chan);

	वापस ret;

report_पढ़ो_failure:
	dev_err(&pdev->dev, "failed to read %s\n", key);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qcom_smp2p_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_smp2p *smp2p = platक्रमm_get_drvdata(pdev);
	काष्ठा smp2p_entry *entry;

	list_क्रम_each_entry(entry, &smp2p->inbound, node)
		irq_करोमुख्य_हटाओ(entry->करोमुख्य);

	list_क्रम_each_entry(entry, &smp2p->outbound, node)
		qcom_smem_state_unरेजिस्टर(entry->state);

	mbox_मुक्त_channel(smp2p->mbox_chan);

	smp2p->out->valid_entries = 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_smp2p_of_match[] = अणु
	अणु .compatible = "qcom,smp2p" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_smp2p_of_match);

अटल काष्ठा platक्रमm_driver qcom_smp2p_driver = अणु
	.probe = qcom_smp2p_probe,
	.हटाओ = qcom_smp2p_हटाओ,
	.driver  = अणु
		.name  = "qcom_smp2p",
		.of_match_table = qcom_smp2p_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_smp2p_driver);

MODULE_DESCRIPTION("Qualcomm Shared Memory Point to Point driver");
MODULE_LICENSE("GPL v2");
