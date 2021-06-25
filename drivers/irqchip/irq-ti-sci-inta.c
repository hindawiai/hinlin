<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments' K3 Interrupt Aggregator irqchip driver
 *
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - https://www.ti.com/
 *	Lokesh Vutla <lokeshvutla@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/soc/ti/ti_sci_पूर्णांकa_msi.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <यंत्र-generic/msi.h>

#घोषणा TI_SCI_DEV_ID_MASK	0xffff
#घोषणा TI_SCI_DEV_ID_SHIFT	16
#घोषणा TI_SCI_IRQ_ID_MASK	0xffff
#घोषणा TI_SCI_IRQ_ID_SHIFT	0
#घोषणा HWIRQ_TO_DEVID(hwirq)	(((hwirq) >> (TI_SCI_DEV_ID_SHIFT)) & \
				 (TI_SCI_DEV_ID_MASK))
#घोषणा HWIRQ_TO_IRQID(hwirq)	((hwirq) & (TI_SCI_IRQ_ID_MASK))
#घोषणा TO_HWIRQ(dev, index)	((((dev) & TI_SCI_DEV_ID_MASK) << \
				 TI_SCI_DEV_ID_SHIFT) | \
				((index) & TI_SCI_IRQ_ID_MASK))

#घोषणा MAX_EVENTS_PER_VINT	64
#घोषणा VINT_ENABLE_SET_OFFSET	0x0
#घोषणा VINT_ENABLE_CLR_OFFSET	0x8
#घोषणा VINT_STATUS_OFFSET	0x18
#घोषणा VINT_STATUS_MASKED_OFFSET	0x20

/**
 * काष्ठा ti_sci_पूर्णांकa_event_desc - Description of an event coming to
 *				   Interrupt Aggregator. This serves
 *				   as a mapping table क्रम global event,
 *				   hwirq and vपूर्णांक bit.
 * @global_event:	Global event number corresponding to this event
 * @hwirq:		Hwirq of the incoming पूर्णांकerrupt
 * @vपूर्णांक_bit:		Corresponding vपूर्णांक bit to which this event is attached.
 */
काष्ठा ti_sci_पूर्णांकa_event_desc अणु
	u16 global_event;
	u32 hwirq;
	u8 vपूर्णांक_bit;
पूर्ण;

/**
 * काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc - Description of a भव पूर्णांकerrupt coming out
 *				  of Interrupt Aggregator.
 * @करोमुख्य:		Poपूर्णांकer to IRQ करोमुख्य to which this vपूर्णांक beदीर्घs.
 * @list:		List entry क्रम the vपूर्णांक list
 * @event_map:		Biपंचांगap to manage the allocation of events to vपूर्णांक.
 * @events:		Array of event descriptors asचिन्हित to this vपूर्णांक.
 * @parent_virq:	Linux IRQ number that माला_लो attached to parent
 * @vपूर्णांक_id:		TISCI vपूर्णांक ID
 */
काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा list_head list;
	DECLARE_BITMAP(event_map, MAX_EVENTS_PER_VINT);
	काष्ठा ti_sci_पूर्णांकa_event_desc events[MAX_EVENTS_PER_VINT];
	अचिन्हित पूर्णांक parent_virq;
	u16 vपूर्णांक_id;
पूर्ण;

/**
 * काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य - Structure representing a TISCI based
 *				   Interrupt Aggregator IRQ करोमुख्य.
 * @sci:		Poपूर्णांकer to TISCI handle
 * @vपूर्णांक:		TISCI resource poपूर्णांकer representing IA पूर्णांकerrupts.
 * @global_event:	TISCI resource poपूर्णांकer representing global events.
 * @vपूर्णांक_list:		List of the vपूर्णांकs active in the प्रणाली
 * @vपूर्णांक_mutex:		Mutex to protect vपूर्णांक_list
 * @base:		Base address of the memory mapped IO रेजिस्टरs
 * @pdev:		Poपूर्णांकer to platक्रमm device.
 * @ti_sci_id:		TI-SCI device identअगरier
 * @unmapped_cnt:	Number of @unmapped_dev_ids entries
 * @unmapped_dev_ids:	Poपूर्णांकer to an array of TI-SCI device identअगरiers of
 *			unmapped event sources.
 *			Unmapped Events are not part of the Global Event Map and
 *			they are converted to Global event within INTA to be
 *			received by the same INTA to generate an पूर्णांकerrupt.
 *			In हाल an पूर्णांकerrupt request comes क्रम a device which is
 *			generating Unmapped Event, we must use the INTA's TI-SCI
 *			device identअगरier in place of the source device
 *			identअगरier to let sysfw know where it has to program the
 *			Global Event number.
 */
काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य अणु
	स्थिर काष्ठा ti_sci_handle *sci;
	काष्ठा ti_sci_resource *vपूर्णांक;
	काष्ठा ti_sci_resource *global_event;
	काष्ठा list_head vपूर्णांक_list;
	/* Mutex to protect vपूर्णांक list */
	काष्ठा mutex vपूर्णांक_mutex;
	व्योम __iomem *base;
	काष्ठा platक्रमm_device *pdev;
	u32 ti_sci_id;

	पूर्णांक unmapped_cnt;
	u16 *unmapped_dev_ids;
पूर्ण;

#घोषणा to_vपूर्णांक_desc(e, i) container_of(e, काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc, \
					events[i])

अटल u16 ti_sci_पूर्णांकa_get_dev_id(काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa, u32 hwirq)
अणु
	u16 dev_id = HWIRQ_TO_DEVID(hwirq);
	पूर्णांक i;

	अगर (पूर्णांकa->unmapped_cnt == 0)
		वापस dev_id;

	/*
	 * For devices sending Unmapped Events we must use the INTA's TI-SCI
	 * device identअगरier number to be able to convert it to a Global Event
	 * and map it to an पूर्णांकerrupt.
	 */
	क्रम (i = 0; i < पूर्णांकa->unmapped_cnt; i++) अणु
		अगर (dev_id == पूर्णांकa->unmapped_dev_ids[i]) अणु
			dev_id = पूर्णांकa->ti_sci_id;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस dev_id;
पूर्ण

/**
 * ti_sci_पूर्णांकa_irq_handler() - Chained IRQ handler क्रम the vपूर्णांक irqs
 * @desc:	Poपूर्णांकer to irq_desc corresponding to the irq
 */
अटल व्योम ti_sci_पूर्णांकa_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc;
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक virq, bit;
	अचिन्हित दीर्घ val;

	vपूर्णांक_desc = irq_desc_get_handler_data(desc);
	करोमुख्य = vपूर्णांक_desc->करोमुख्य;
	पूर्णांकa = करोमुख्य->host_data;

	chained_irq_enter(irq_desc_get_chip(desc), desc);

	val = पढ़ोq_relaxed(पूर्णांकa->base + vपूर्णांक_desc->vपूर्णांक_id * 0x1000 +
			    VINT_STATUS_MASKED_OFFSET);

	क्रम_each_set_bit(bit, &val, MAX_EVENTS_PER_VINT) अणु
		virq = irq_find_mapping(करोमुख्य, vपूर्णांक_desc->events[bit].hwirq);
		अगर (virq)
			generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(irq_desc_get_chip(desc), desc);
पूर्ण

/**
 * ti_sci_पूर्णांकa_xlate_irq() - Translate hwirq to parent's hwirq.
 * @पूर्णांकa:	IRQ करोमुख्य corresponding to Interrupt Aggregator
 * @irq:	Hardware irq corresponding to the above irq करोमुख्य
 *
 * Return parent irq number अगर translation is available अन्यथा -ENOENT.
 */
अटल पूर्णांक ti_sci_पूर्णांकa_xlate_irq(काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa,
				 u16 vपूर्णांक_id)
अणु
	काष्ठा device_node *np = dev_of_node(&पूर्णांकa->pdev->dev);
	u32 base, parent_base, size;
	स्थिर __be32 *range;
	पूर्णांक len;

	range = of_get_property(np, "ti,interrupt-ranges", &len);
	अगर (!range)
		वापस vपूर्णांक_id;

	क्रम (len /= माप(*range); len >= 3; len -= 3) अणु
		base = be32_to_cpu(*range++);
		parent_base = be32_to_cpu(*range++);
		size = be32_to_cpu(*range++);

		अगर (base <= vपूर्णांक_id && vपूर्णांक_id < base + size)
			वापस vपूर्णांक_id - base + parent_base;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * ti_sci_पूर्णांकa_alloc_parent_irq() - Allocate parent irq to Interrupt aggregator
 * @करोमुख्य:	IRQ करोमुख्य corresponding to Interrupt Aggregator
 *
 * Return 0 अगर all went well अन्यथा corresponding error value.
 */
अटल काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *ti_sci_पूर्णांकa_alloc_parent_irq(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa = करोमुख्य->host_data;
	काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc;
	काष्ठा irq_fwspec parent_fwspec;
	काष्ठा device_node *parent_node;
	अचिन्हित पूर्णांक parent_virq;
	पूर्णांक p_hwirq, ret;
	u16 vपूर्णांक_id;

	vपूर्णांक_id = ti_sci_get_मुक्त_resource(पूर्णांकa->vपूर्णांक);
	अगर (vपूर्णांक_id == TI_SCI_RESOURCE_शून्य)
		वापस ERR_PTR(-EINVAL);

	p_hwirq = ti_sci_पूर्णांकa_xlate_irq(पूर्णांकa, vपूर्णांक_id);
	अगर (p_hwirq < 0) अणु
		ret = p_hwirq;
		जाओ मुक्त_vपूर्णांक;
	पूर्ण

	vपूर्णांक_desc = kzalloc(माप(*vपूर्णांक_desc), GFP_KERNEL);
	अगर (!vपूर्णांक_desc) अणु
		ret = -ENOMEM;
		जाओ मुक्त_vपूर्णांक;
	पूर्ण

	vपूर्णांक_desc->करोमुख्य = करोमुख्य;
	vपूर्णांक_desc->vपूर्णांक_id = vपूर्णांक_id;
	INIT_LIST_HEAD(&vपूर्णांक_desc->list);

	parent_node = of_irq_find_parent(dev_of_node(&पूर्णांकa->pdev->dev));
	parent_fwspec.fwnode = of_node_to_fwnode(parent_node);

	अगर (of_device_is_compatible(parent_node, "arm,gic-v3")) अणु
		/* Parent is GIC */
		parent_fwspec.param_count = 3;
		parent_fwspec.param[0] = 0;
		parent_fwspec.param[1] = p_hwirq - 32;
		parent_fwspec.param[2] = IRQ_TYPE_LEVEL_HIGH;
	पूर्ण अन्यथा अणु
		/* Parent is Interrupt Router */
		parent_fwspec.param_count = 1;
		parent_fwspec.param[0] = p_hwirq;
	पूर्ण

	parent_virq = irq_create_fwspec_mapping(&parent_fwspec);
	अगर (parent_virq == 0) अणु
		dev_err(&पूर्णांकa->pdev->dev, "Parent IRQ allocation failed\n");
		ret = -EINVAL;
		जाओ मुक्त_vपूर्णांक_desc;

	पूर्ण
	vपूर्णांक_desc->parent_virq = parent_virq;

	list_add_tail(&vपूर्णांक_desc->list, &पूर्णांकa->vपूर्णांक_list);
	irq_set_chained_handler_and_data(vपूर्णांक_desc->parent_virq,
					 ti_sci_पूर्णांकa_irq_handler, vपूर्णांक_desc);

	वापस vपूर्णांक_desc;
मुक्त_vपूर्णांक_desc:
	kमुक्त(vपूर्णांक_desc);
मुक्त_vपूर्णांक:
	ti_sci_release_resource(पूर्णांकa->vपूर्णांक, vपूर्णांक_id);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * ti_sci_पूर्णांकa_alloc_event() - Attach an event to a IA vपूर्णांक.
 * @vपूर्णांक_desc:	Poपूर्णांकer to vपूर्णांक_desc to which the event माला_लो attached
 * @मुक्त_bit:	Bit inside vपूर्णांक to which event माला_लो attached
 * @hwirq:	hwirq of the input event
 *
 * Return event_desc poपूर्णांकer अगर all went ok अन्यथा appropriate error value.
 */
अटल काष्ठा ti_sci_पूर्णांकa_event_desc *ti_sci_पूर्णांकa_alloc_event(काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc,
							      u16 मुक्त_bit,
							      u32 hwirq)
अणु
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa = vपूर्णांक_desc->करोमुख्य->host_data;
	काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc;
	u16 dev_id, dev_index;
	पूर्णांक err;

	dev_id = ti_sci_पूर्णांकa_get_dev_id(पूर्णांकa, hwirq);
	dev_index = HWIRQ_TO_IRQID(hwirq);

	event_desc = &vपूर्णांक_desc->events[मुक्त_bit];
	event_desc->hwirq = hwirq;
	event_desc->vपूर्णांक_bit = मुक्त_bit;
	event_desc->global_event = ti_sci_get_मुक्त_resource(पूर्णांकa->global_event);
	अगर (event_desc->global_event == TI_SCI_RESOURCE_शून्य)
		वापस ERR_PTR(-EINVAL);

	err = पूर्णांकa->sci->ops.rm_irq_ops.set_event_map(पूर्णांकa->sci,
						      dev_id, dev_index,
						      पूर्णांकa->ti_sci_id,
						      vपूर्णांक_desc->vपूर्णांक_id,
						      event_desc->global_event,
						      मुक्त_bit);
	अगर (err)
		जाओ मुक्त_global_event;

	वापस event_desc;
मुक्त_global_event:
	ti_sci_release_resource(पूर्णांकa->global_event, event_desc->global_event);
	वापस ERR_PTR(err);
पूर्ण

/**
 * ti_sci_पूर्णांकa_alloc_irq() -  Allocate an irq within INTA करोमुख्य
 * @करोमुख्य:	irq_करोमुख्य poपूर्णांकer corresponding to INTA
 * @hwirq:	hwirq of the input event
 *
 * Note: Allocation happens in the following manner:
 *	- Find a मुक्त bit available in any of the vपूर्णांकs available in the list.
 *	- If not found, allocate a vपूर्णांक from the vपूर्णांक pool
 *	- Attach the मुक्त bit to input hwirq.
 * Return event_desc अगर all went ok अन्यथा appropriate error value.
 */
अटल काष्ठा ti_sci_पूर्णांकa_event_desc *ti_sci_पूर्णांकa_alloc_irq(काष्ठा irq_करोमुख्य *करोमुख्य,
							    u32 hwirq)
अणु
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa = करोमुख्य->host_data;
	काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc = शून्य;
	काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc;
	u16 मुक्त_bit;

	mutex_lock(&पूर्णांकa->vपूर्णांक_mutex);
	list_क्रम_each_entry(vपूर्णांक_desc, &पूर्णांकa->vपूर्णांक_list, list) अणु
		मुक्त_bit = find_first_zero_bit(vपूर्णांक_desc->event_map,
					       MAX_EVENTS_PER_VINT);
		अगर (मुक्त_bit != MAX_EVENTS_PER_VINT) अणु
			set_bit(मुक्त_bit, vपूर्णांक_desc->event_map);
			जाओ alloc_event;
		पूर्ण
	पूर्ण

	/* No मुक्त bits available. Allocate a new vपूर्णांक */
	vपूर्णांक_desc = ti_sci_पूर्णांकa_alloc_parent_irq(करोमुख्य);
	अगर (IS_ERR(vपूर्णांक_desc)) अणु
		event_desc = ERR_CAST(vपूर्णांक_desc);
		जाओ unlock;
	पूर्ण

	मुक्त_bit = find_first_zero_bit(vपूर्णांक_desc->event_map,
				       MAX_EVENTS_PER_VINT);
	set_bit(मुक्त_bit, vपूर्णांक_desc->event_map);

alloc_event:
	event_desc = ti_sci_पूर्णांकa_alloc_event(vपूर्णांक_desc, मुक्त_bit, hwirq);
	अगर (IS_ERR(event_desc))
		clear_bit(मुक्त_bit, vपूर्णांक_desc->event_map);

unlock:
	mutex_unlock(&पूर्णांकa->vपूर्णांक_mutex);
	वापस event_desc;
पूर्ण

/**
 * ti_sci_पूर्णांकa_मुक्त_parent_irq() - Free a parent irq to INTA
 * @पूर्णांकa:	Poपूर्णांकer to पूर्णांकa करोमुख्य.
 * @vपूर्णांक_desc:	Poपूर्णांकer to vपूर्णांक_desc that needs to be मुक्तd.
 */
अटल व्योम ti_sci_पूर्णांकa_मुक्त_parent_irq(काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa,
					काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc)
अणु
	अगर (find_first_bit(vपूर्णांक_desc->event_map, MAX_EVENTS_PER_VINT) == MAX_EVENTS_PER_VINT) अणु
		list_del(&vपूर्णांक_desc->list);
		ti_sci_release_resource(पूर्णांकa->vपूर्णांक, vपूर्णांक_desc->vपूर्णांक_id);
		irq_dispose_mapping(vपूर्णांक_desc->parent_virq);
		kमुक्त(vपूर्णांक_desc);
	पूर्ण
पूर्ण

/**
 * ti_sci_पूर्णांकa_मुक्त_irq() - Free an IRQ within INTA करोमुख्य
 * @event_desc:	Poपूर्णांकer to event_desc that needs to be मुक्तd.
 * @hwirq:	Hwirq number within INTA करोमुख्य that needs to be मुक्तd
 */
अटल व्योम ti_sci_पूर्णांकa_मुक्त_irq(काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc,
				 u32 hwirq)
अणु
	काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc;
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa;
	u16 dev_id;

	vपूर्णांक_desc = to_vपूर्णांक_desc(event_desc, event_desc->vपूर्णांक_bit);
	पूर्णांकa = vपूर्णांक_desc->करोमुख्य->host_data;
	dev_id = ti_sci_पूर्णांकa_get_dev_id(पूर्णांकa, hwirq);
	/* मुक्त event irq */
	mutex_lock(&पूर्णांकa->vपूर्णांक_mutex);
	पूर्णांकa->sci->ops.rm_irq_ops.मुक्त_event_map(पूर्णांकa->sci,
						 dev_id, HWIRQ_TO_IRQID(hwirq),
						 पूर्णांकa->ti_sci_id,
						 vपूर्णांक_desc->vपूर्णांक_id,
						 event_desc->global_event,
						 event_desc->vपूर्णांक_bit);

	clear_bit(event_desc->vपूर्णांक_bit, vपूर्णांक_desc->event_map);
	ti_sci_release_resource(पूर्णांकa->global_event, event_desc->global_event);
	event_desc->global_event = TI_SCI_RESOURCE_शून्य;
	event_desc->hwirq = 0;

	ti_sci_पूर्णांकa_मुक्त_parent_irq(पूर्णांकa, vपूर्णांक_desc);
	mutex_unlock(&पूर्णांकa->vपूर्णांक_mutex);
पूर्ण

/**
 * ti_sci_पूर्णांकa_request_resources() - Allocate resources क्रम input irq
 * @data: Poपूर्णांकer to corresponding irq_data
 *
 * Note: This is the core api where the actual allocation happens क्रम input
 *	 hwirq. This allocation involves creating a parent irq क्रम vपूर्णांक.
 *	 If this is करोne in irq_करोमुख्य_ops.alloc() then a deadlock is reached
 *	 क्रम allocation. So this allocation is being करोne in request_resources()
 *
 * Return: 0 अगर all went well अन्यथा corresponding error.
 */
अटल पूर्णांक ti_sci_पूर्णांकa_request_resources(काष्ठा irq_data *data)
अणु
	काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc;

	event_desc = ti_sci_पूर्णांकa_alloc_irq(data->करोमुख्य, data->hwirq);
	अगर (IS_ERR(event_desc))
		वापस PTR_ERR(event_desc);

	data->chip_data = event_desc;

	वापस 0;
पूर्ण

/**
 * ti_sci_पूर्णांकa_release_resources - Release resources क्रम input irq
 * @data: Poपूर्णांकer to corresponding irq_data
 *
 * Note: Corresponding to request_resources(), all the unmapping and deletion
 *	 of parent vपूर्णांक irqs happens in this api.
 */
अटल व्योम ti_sci_पूर्णांकa_release_resources(काष्ठा irq_data *data)
अणु
	काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc;

	event_desc = irq_data_get_irq_chip_data(data);
	ti_sci_पूर्णांकa_मुक्त_irq(event_desc, data->hwirq);
पूर्ण

/**
 * ti_sci_पूर्णांकa_manage_event() - Control the event based on the offset
 * @data:	Poपूर्णांकer to corresponding irq_data
 * @offset:	रेजिस्टर offset using which event is controlled.
 */
अटल व्योम ti_sci_पूर्णांकa_manage_event(काष्ठा irq_data *data, u32 offset)
अणु
	काष्ठा ti_sci_पूर्णांकa_event_desc *event_desc;
	काष्ठा ti_sci_पूर्णांकa_vपूर्णांक_desc *vपूर्णांक_desc;
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa;

	event_desc = irq_data_get_irq_chip_data(data);
	vपूर्णांक_desc = to_vपूर्णांक_desc(event_desc, event_desc->vपूर्णांक_bit);
	पूर्णांकa = data->करोमुख्य->host_data;

	ग_लिखोq_relaxed(BIT(event_desc->vपूर्णांक_bit),
		       पूर्णांकa->base + vपूर्णांक_desc->vपूर्णांक_id * 0x1000 + offset);
पूर्ण

/**
 * ti_sci_पूर्णांकa_mask_irq() - Mask an event
 * @data:	Poपूर्णांकer to corresponding irq_data
 */
अटल व्योम ti_sci_पूर्णांकa_mask_irq(काष्ठा irq_data *data)
अणु
	ti_sci_पूर्णांकa_manage_event(data, VINT_ENABLE_CLR_OFFSET);
पूर्ण

/**
 * ti_sci_पूर्णांकa_unmask_irq() - Unmask an event
 * @data:	Poपूर्णांकer to corresponding irq_data
 */
अटल व्योम ti_sci_पूर्णांकa_unmask_irq(काष्ठा irq_data *data)
अणु
	ti_sci_पूर्णांकa_manage_event(data, VINT_ENABLE_SET_OFFSET);
पूर्ण

/**
 * ti_sci_पूर्णांकa_ack_irq() - Ack an event
 * @data:	Poपूर्णांकer to corresponding irq_data
 */
अटल व्योम ti_sci_पूर्णांकa_ack_irq(काष्ठा irq_data *data)
अणु
	/*
	 * Do not clear the event अगर hardware is capable of sending
	 * a करोwn event.
	 */
	अगर (irqd_get_trigger_type(data) != IRQF_TRIGGER_HIGH)
		ti_sci_पूर्णांकa_manage_event(data, VINT_STATUS_OFFSET);
पूर्ण

अटल पूर्णांक ti_sci_पूर्णांकa_set_affinity(काष्ठा irq_data *d,
				    स्थिर काष्ठा cpumask *mask_val, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * ti_sci_पूर्णांकa_set_type() - Update the trigger type of the irq.
 * @data:	Poपूर्णांकer to corresponding irq_data
 * @type:	Trigger type as specअगरied by user
 *
 * Note: This updates the handle_irq callback क्रम level msi.
 *
 * Return 0 अगर all went well अन्यथा appropriate error.
 */
अटल पूर्णांक ti_sci_पूर्णांकa_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	/*
	 * .alloc शेष sets handle_edge_irq. But अगर the user specअगरies
	 * that IRQ is level MSI, then update the handle to handle_level_irq
	 */
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQF_TRIGGER_HIGH:
		irq_set_handler_locked(data, handle_level_irq);
		वापस 0;
	हाल IRQF_TRIGGER_RISING:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip ti_sci_पूर्णांकa_irq_chip = अणु
	.name			= "INTA",
	.irq_ack		= ti_sci_पूर्णांकa_ack_irq,
	.irq_mask		= ti_sci_पूर्णांकa_mask_irq,
	.irq_set_type		= ti_sci_पूर्णांकa_set_type,
	.irq_unmask		= ti_sci_पूर्णांकa_unmask_irq,
	.irq_set_affinity	= ti_sci_पूर्णांकa_set_affinity,
	.irq_request_resources	= ti_sci_पूर्णांकa_request_resources,
	.irq_release_resources	= ti_sci_पूर्णांकa_release_resources,
पूर्ण;

/**
 * ti_sci_पूर्णांकa_irq_करोमुख्य_मुक्त() - Free an IRQ from the IRQ करोमुख्य
 * @करोमुख्य:	Doमुख्य to which the irqs beदीर्घ
 * @virq:	base linux भव IRQ to be मुक्तd.
 * @nr_irqs:	Number of continuous irqs to be मुक्तd
 */
अटल व्योम ti_sci_पूर्णांकa_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	irq_करोमुख्य_reset_irq_data(data);
पूर्ण

/**
 * ti_sci_पूर्णांकa_irq_करोमुख्य_alloc() - Allocate Interrupt aggregator IRQs
 * @करोमुख्य:	Poपूर्णांक to the पूर्णांकerrupt aggregator IRQ करोमुख्य
 * @virq:	Corresponding Linux भव IRQ number
 * @nr_irqs:	Continuous irqs to be allocated
 * @data:	Poपूर्णांकer to firmware specअगरier
 *
 * No actual allocation happens here.
 *
 * Return 0 अगर all went well अन्यथा appropriate error value.
 */
अटल पूर्णांक ti_sci_पूर्णांकa_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs,
					व्योम *data)
अणु
	msi_alloc_info_t *arg = data;

	irq_करोमुख्य_set_info(करोमुख्य, virq, arg->hwirq, &ti_sci_पूर्णांकa_irq_chip,
			    शून्य, handle_edge_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ti_sci_पूर्णांकa_irq_करोमुख्य_ops = अणु
	.मुक्त		= ti_sci_पूर्णांकa_irq_करोमुख्य_मुक्त,
	.alloc		= ti_sci_पूर्णांकa_irq_करोमुख्य_alloc,
पूर्ण;

अटल काष्ठा irq_chip ti_sci_पूर्णांकa_msi_irq_chip = अणु
	.name			= "MSI-INTA",
	.flags			= IRQCHIP_SUPPORTS_LEVEL_MSI,
पूर्ण;

अटल व्योम ti_sci_पूर्णांकa_msi_set_desc(msi_alloc_info_t *arg,
				     काष्ठा msi_desc *desc)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(desc->dev);

	arg->desc = desc;
	arg->hwirq = TO_HWIRQ(pdev->id, desc->पूर्णांकa.dev_index);
पूर्ण

अटल काष्ठा msi_करोमुख्य_ops ti_sci_पूर्णांकa_msi_ops = अणु
	.set_desc	= ti_sci_पूर्णांकa_msi_set_desc,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info ti_sci_पूर्णांकa_msi_करोमुख्य_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_LEVEL_CAPABLE),
	.ops	= &ti_sci_पूर्णांकa_msi_ops,
	.chip	= &ti_sci_पूर्णांकa_msi_irq_chip,
पूर्ण;

अटल पूर्णांक ti_sci_पूर्णांकa_get_unmapped_sources(काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa)
अणु
	काष्ठा device *dev = &पूर्णांकa->pdev->dev;
	काष्ठा device_node *node = dev_of_node(dev);
	काष्ठा of_phandle_iterator it;
	पूर्णांक count, err, ret, i;

	count = of_count_phandle_with_args(node, "ti,unmapped-event-sources", शून्य);
	अगर (count <= 0)
		वापस 0;

	पूर्णांकa->unmapped_dev_ids = devm_kसुस्मृति(dev, count,
					      माप(*पूर्णांकa->unmapped_dev_ids),
					      GFP_KERNEL);
	अगर (!पूर्णांकa->unmapped_dev_ids)
		वापस -ENOMEM;

	i = 0;
	of_क्रम_each_phandle(&it, err, node, "ti,unmapped-event-sources", शून्य, 0) अणु
		u32 dev_id;

		ret = of_property_पढ़ो_u32(it.node, "ti,sci-dev-id", &dev_id);
		अगर (ret) अणु
			dev_err(dev, "ti,sci-dev-id read failure for %pOFf\n", it.node);
			of_node_put(it.node);
			वापस ret;
		पूर्ण
		पूर्णांकa->unmapped_dev_ids[i++] = dev_id;
	पूर्ण

	पूर्णांकa->unmapped_cnt = count;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_sci_पूर्णांकa_irq_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा irq_करोमुख्य *parent_करोमुख्य, *करोमुख्य, *msi_करोमुख्य;
	काष्ठा device_node *parent_node, *node;
	काष्ठा ti_sci_पूर्णांकa_irq_करोमुख्य *पूर्णांकa;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	node = dev_of_node(dev);
	parent_node = of_irq_find_parent(node);
	अगर (!parent_node) अणु
		dev_err(dev, "Failed to get IRQ parent node\n");
		वापस -ENODEV;
	पूर्ण

	parent_करोमुख्य = irq_find_host(parent_node);
	अगर (!parent_करोमुख्य)
		वापस -EPROBE_DEFER;

	पूर्णांकa = devm_kzalloc(dev, माप(*पूर्णांकa), GFP_KERNEL);
	अगर (!पूर्णांकa)
		वापस -ENOMEM;

	पूर्णांकa->pdev = pdev;
	पूर्णांकa->sci = devm_ti_sci_get_by_phandle(dev, "ti,sci");
	अगर (IS_ERR(पूर्णांकa->sci))
		वापस dev_err_probe(dev, PTR_ERR(पूर्णांकa->sci),
				     "ti,sci read fail\n");

	ret = of_property_पढ़ो_u32(dev->of_node, "ti,sci-dev-id", &पूर्णांकa->ti_sci_id);
	अगर (ret) अणु
		dev_err(dev, "missing 'ti,sci-dev-id' property\n");
		वापस -EINVAL;
	पूर्ण

	पूर्णांकa->vपूर्णांक = devm_ti_sci_get_resource(पूर्णांकa->sci, dev, पूर्णांकa->ti_sci_id,
					      TI_SCI_RESASG_SUBTYPE_IA_VINT);
	अगर (IS_ERR(पूर्णांकa->vपूर्णांक)) अणु
		dev_err(dev, "VINT resource allocation failed\n");
		वापस PTR_ERR(पूर्णांकa->vपूर्णांक);
	पूर्ण

	पूर्णांकa->global_event = devm_ti_sci_get_resource(पूर्णांकa->sci, dev, पूर्णांकa->ti_sci_id,
						      TI_SCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT);
	अगर (IS_ERR(पूर्णांकa->global_event)) अणु
		dev_err(dev, "Global event resource allocation failed\n");
		वापस PTR_ERR(पूर्णांकa->global_event);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	पूर्णांकa->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(पूर्णांकa->base))
		वापस PTR_ERR(पूर्णांकa->base);

	ret = ti_sci_पूर्णांकa_get_unmapped_sources(पूर्णांकa);
	अगर (ret)
		वापस ret;

	करोमुख्य = irq_करोमुख्य_add_linear(dev_of_node(dev),
				       ti_sci_get_num_resources(पूर्णांकa->vपूर्णांक),
				       &ti_sci_पूर्णांकa_irq_करोमुख्य_ops, पूर्णांकa);
	अगर (!करोमुख्य) अणु
		dev_err(dev, "Failed to allocate IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi_करोमुख्य = ti_sci_पूर्णांकa_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
						&ti_sci_पूर्णांकa_msi_करोमुख्य_info,
						करोमुख्य);
	अगर (!msi_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(करोमुख्य);
		dev_err(dev, "Failed to allocate msi domain\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&पूर्णांकa->vपूर्णांक_list);
	mutex_init(&पूर्णांकa->vपूर्णांक_mutex);

	dev_info(dev, "Interrupt Aggregator domain %d created\n", पूर्णांकa->ti_sci_id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_sci_पूर्णांकa_irq_करोमुख्य_of_match[] = अणु
	अणु .compatible = "ti,sci-inta", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sci_पूर्णांकa_irq_करोमुख्य_of_match);

अटल काष्ठा platक्रमm_driver ti_sci_पूर्णांकa_irq_करोमुख्य_driver = अणु
	.probe = ti_sci_पूर्णांकa_irq_करोमुख्य_probe,
	.driver = अणु
		.name = "ti-sci-inta",
		.of_match_table = ti_sci_पूर्णांकa_irq_करोमुख्य_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_sci_पूर्णांकa_irq_करोमुख्य_driver);

MODULE_AUTHOR("Lokesh Vutla <lokeshvutla@ti.com>");
MODULE_DESCRIPTION("K3 Interrupt Aggregator driver over TI SCI protocol");
MODULE_LICENSE("GPL v2");
