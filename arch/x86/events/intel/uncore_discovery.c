<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Support Intel uncore PerfMon discovery mechanism.
 * Copyright(c) 2021 Intel Corporation.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "uncore.h"
#समावेश "uncore_discovery.h"

अटल काष्ठा rb_root discovery_tables = RB_ROOT;
अटल पूर्णांक num_discovered_types[UNCORE_ACCESS_MAX];

अटल bool has_generic_discovery_table(व्योम)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक dvsec;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL, UNCORE_DISCOVERY_TABLE_DEVICE, शून्य);
	अगर (!dev)
		वापस false;

	/* A discovery table device has the unique capability ID. */
	dvsec = pci_find_next_ext_capability(dev, 0, UNCORE_EXT_CAP_ID_DISCOVERY);
	pci_dev_put(dev);
	अगर (dvsec)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक logical_die_id;

अटल पूर्णांक get_device_die_id(काष्ठा pci_dev *dev)
अणु
	पूर्णांक cpu, node = pcibus_to_node(dev->bus);

	/*
	 * If the NUMA info is not available, assume that the logical die id is
	 * continuous in the order in which the discovery table devices are
	 * detected.
	 */
	अगर (node < 0)
		वापस logical_die_id++;

	क्रम_each_cpu(cpu, cpumask_of_node(node)) अणु
		काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

		अगर (c->initialized && cpu_to_node(cpu) == node)
			वापस c->logical_die_id;
	पूर्ण

	/*
	 * All CPUs of a node may be offlined. For this हाल,
	 * the PCI and MMIO type of uncore blocks which are
	 * क्रमागतerated by the device will be unavailable.
	 */
	वापस -1;
पूर्ण

#घोषणा __node_2_type(cur)	\
	rb_entry((cur), काष्ठा पूर्णांकel_uncore_discovery_type, node)

अटल अंतरभूत पूर्णांक __type_cmp(स्थिर व्योम *key, स्थिर काष्ठा rb_node *b)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type_b = __node_2_type(b);
	स्थिर u16 *type_id = key;

	अगर (type_b->type > *type_id)
		वापस -1;
	अन्यथा अगर (type_b->type < *type_id)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_uncore_discovery_type *
search_uncore_discovery_type(u16 type_id)
अणु
	काष्ठा rb_node *node = rb_find(&type_id, &discovery_tables, __type_cmp);

	वापस (node) ? __node_2_type(node) : शून्य;
पूर्ण

अटल अंतरभूत bool __type_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस (__node_2_type(a)->type < __node_2_type(b)->type);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_discovery_type *
add_uncore_discovery_type(काष्ठा uncore_unit_discovery *unit)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type;

	अगर (unit->access_type >= UNCORE_ACCESS_MAX) अणु
		pr_warn("Unsupported access type %d\n", unit->access_type);
		वापस शून्य;
	पूर्ण

	type = kzalloc(माप(काष्ठा पूर्णांकel_uncore_discovery_type), GFP_KERNEL);
	अगर (!type)
		वापस शून्य;

	type->box_ctrl_die = kसुस्मृति(__uncore_max_dies, माप(u64), GFP_KERNEL);
	अगर (!type->box_ctrl_die)
		जाओ मुक्त_type;

	type->access_type = unit->access_type;
	num_discovered_types[type->access_type]++;
	type->type = unit->box_type;

	rb_add(&type->node, &discovery_tables, __type_less);

	वापस type;

मुक्त_type:
	kमुक्त(type);

	वापस शून्य;

पूर्ण

अटल काष्ठा पूर्णांकel_uncore_discovery_type *
get_uncore_discovery_type(काष्ठा uncore_unit_discovery *unit)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type;

	type = search_uncore_discovery_type(unit->box_type);
	अगर (type)
		वापस type;

	वापस add_uncore_discovery_type(unit);
पूर्ण

अटल व्योम
uncore_insert_box_info(काष्ठा uncore_unit_discovery *unit,
		       पूर्णांक die, bool parsed)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type;
	अचिन्हित पूर्णांक *box_offset, *ids;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!unit->ctl || !unit->ctl_offset || !unit->ctr_offset))
		वापस;

	अगर (parsed) अणु
		type = search_uncore_discovery_type(unit->box_type);
		अगर (WARN_ON_ONCE(!type))
			वापस;
		/* Store the first box of each die */
		अगर (!type->box_ctrl_die[die])
			type->box_ctrl_die[die] = unit->ctl;
		वापस;
	पूर्ण

	type = get_uncore_discovery_type(unit);
	अगर (!type)
		वापस;

	box_offset = kसुस्मृति(type->num_boxes + 1, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!box_offset)
		वापस;

	ids = kसुस्मृति(type->num_boxes + 1, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (!ids)
		जाओ मुक्त_box_offset;

	/* Store generic inक्रमmation क्रम the first box */
	अगर (!type->num_boxes) अणु
		type->box_ctrl = unit->ctl;
		type->box_ctrl_die[die] = unit->ctl;
		type->num_counters = unit->num_regs;
		type->counter_width = unit->bit_width;
		type->ctl_offset = unit->ctl_offset;
		type->ctr_offset = unit->ctr_offset;
		*ids = unit->box_id;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < type->num_boxes; i++) अणु
		ids[i] = type->ids[i];
		box_offset[i] = type->box_offset[i];

		अगर (WARN_ON_ONCE(unit->box_id == ids[i]))
			जाओ मुक्त_ids;
	पूर्ण
	ids[i] = unit->box_id;
	box_offset[i] = unit->ctl - type->box_ctrl;
	kमुक्त(type->ids);
	kमुक्त(type->box_offset);
end:
	type->ids = ids;
	type->box_offset = box_offset;
	type->num_boxes++;
	वापस;

मुक्त_ids:
	kमुक्त(ids);

मुक्त_box_offset:
	kमुक्त(box_offset);

पूर्ण

अटल पूर्णांक parse_discovery_table(काष्ठा pci_dev *dev, पूर्णांक die,
				 u32 bar_offset, bool *parsed)
अणु
	काष्ठा uncore_global_discovery global;
	काष्ठा uncore_unit_discovery unit;
	व्योम __iomem *io_addr;
	resource_माप_प्रकार addr;
	अचिन्हित दीर्घ size;
	u32 val;
	पूर्णांक i;

	pci_पढ़ो_config_dword(dev, bar_offset, &val);

	अगर (val & UNCORE_DISCOVERY_MASK)
		वापस -EINVAL;

	addr = (resource_माप_प्रकार)(val & ~UNCORE_DISCOVERY_MASK);
	size = UNCORE_DISCOVERY_GLOBAL_MAP_SIZE;
	io_addr = ioremap(addr, size);
	अगर (!io_addr)
		वापस -ENOMEM;

	/* Read Global Discovery State */
	स_नकल_fromio(&global, io_addr, माप(काष्ठा uncore_global_discovery));
	अगर (uncore_discovery_invalid_unit(global)) अणु
		pr_info("Invalid Global Discovery State: 0x%llx 0x%llx 0x%llx\n",
			global.table1, global.ctl, global.table3);
		iounmap(io_addr);
		वापस -EINVAL;
	पूर्ण
	iounmap(io_addr);

	size = (1 + global.max_units) * global.stride * 8;
	io_addr = ioremap(addr, size);
	अगर (!io_addr)
		वापस -ENOMEM;

	/* Parsing Unit Discovery State */
	क्रम (i = 0; i < global.max_units; i++) अणु
		स_नकल_fromio(&unit, io_addr + (i + 1) * (global.stride * 8),
			      माप(काष्ठा uncore_unit_discovery));

		अगर (uncore_discovery_invalid_unit(unit))
			जारी;

		अगर (unit.access_type >= UNCORE_ACCESS_MAX)
			जारी;

		uncore_insert_box_info(&unit, die, *parsed);
	पूर्ण

	*parsed = true;
	iounmap(io_addr);
	वापस 0;
पूर्ण

bool पूर्णांकel_uncore_has_discovery_tables(व्योम)
अणु
	u32 device, val, entry_id, bar_offset;
	पूर्णांक die, dvsec = 0, ret = true;
	काष्ठा pci_dev *dev = शून्य;
	bool parsed = false;

	अगर (has_generic_discovery_table())
		device = UNCORE_DISCOVERY_TABLE_DEVICE;
	अन्यथा
		device = PCI_ANY_ID;

	/*
	 * Start a new search and iterates through the list of
	 * the discovery table devices.
	 */
	जबतक ((dev = pci_get_device(PCI_VENDOR_ID_INTEL, device, dev)) != शून्य) अणु
		जबतक ((dvsec = pci_find_next_ext_capability(dev, dvsec, UNCORE_EXT_CAP_ID_DISCOVERY))) अणु
			pci_पढ़ो_config_dword(dev, dvsec + UNCORE_DISCOVERY_DVSEC_OFFSET, &val);
			entry_id = val & UNCORE_DISCOVERY_DVSEC_ID_MASK;
			अगर (entry_id != UNCORE_DISCOVERY_DVSEC_ID_PMON)
				जारी;

			pci_पढ़ो_config_dword(dev, dvsec + UNCORE_DISCOVERY_DVSEC2_OFFSET, &val);

			अगर (val & ~UNCORE_DISCOVERY_DVSEC2_BIR_MASK) अणु
				ret = false;
				जाओ err;
			पूर्ण
			bar_offset = UNCORE_DISCOVERY_BIR_BASE +
				     (val & UNCORE_DISCOVERY_DVSEC2_BIR_MASK) * UNCORE_DISCOVERY_BIR_STEP;

			die = get_device_die_id(dev);
			अगर (die < 0)
				जारी;

			parse_discovery_table(dev, die, bar_offset, &parsed);
		पूर्ण
	पूर्ण

	/* None of the discovery tables are available */
	अगर (!parsed)
		ret = false;
err:
	pci_dev_put(dev);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_uncore_clear_discovery_tables(व्योम)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type, *next;

	rbtree_postorder_क्रम_each_entry_safe(type, next, &discovery_tables, node) अणु
		kमुक्त(type->box_ctrl_die);
		kमुक्त(type);
	पूर्ण
पूर्ण

DEFINE_UNCORE_FORMAT_ATTR(event, event, "config:0-7");
DEFINE_UNCORE_FORMAT_ATTR(umask, umask, "config:8-15");
DEFINE_UNCORE_FORMAT_ATTR(edge, edge, "config:18");
DEFINE_UNCORE_FORMAT_ATTR(inv, inv, "config:23");
DEFINE_UNCORE_FORMAT_ATTR(thresh, thresh, "config:24-31");

अटल काष्ठा attribute *generic_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group generic_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = generic_uncore_क्रमmats_attr,
पूर्ण;

अटल व्योम पूर्णांकel_generic_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(uncore_msr_box_ctl(box), GENERIC_PMON_BOX_CTL_INT);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_msr_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(uncore_msr_box_ctl(box), GENERIC_PMON_BOX_CTL_FRZ);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(uncore_msr_box_ctl(box), 0);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
					    काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, hwc->config);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_msr_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
					     काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, 0);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops generic_uncore_msr_ops = अणु
	.init_box		= पूर्णांकel_generic_uncore_msr_init_box,
	.disable_box		= पूर्णांकel_generic_uncore_msr_disable_box,
	.enable_box		= पूर्णांकel_generic_uncore_msr_enable_box,
	.disable_event		= पूर्णांकel_generic_uncore_msr_disable_event,
	.enable_event		= पूर्णांकel_generic_uncore_msr_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल व्योम पूर्णांकel_generic_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	__set_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags);
	pci_ग_लिखो_config_dword(pdev, box_ctl, GENERIC_PMON_BOX_CTL_INT);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_pci_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	pci_ग_लिखो_config_dword(pdev, box_ctl, GENERIC_PMON_BOX_CTL_FRZ);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_pci_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	pci_ग_लिखो_config_dword(pdev, box_ctl, 0);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_pci_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
					    काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, hwc->config);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_pci_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
					     काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, 0);
पूर्ण

अटल u64 पूर्णांकel_generic_uncore_pci_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box,
					   काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 count = 0;

	pci_पढ़ो_config_dword(pdev, hwc->event_base, (u32 *)&count);
	pci_पढ़ो_config_dword(pdev, hwc->event_base + 4, (u32 *)&count + 1);

	वापस count;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops generic_uncore_pci_ops = अणु
	.init_box	= पूर्णांकel_generic_uncore_pci_init_box,
	.disable_box	= पूर्णांकel_generic_uncore_pci_disable_box,
	.enable_box	= पूर्णांकel_generic_uncore_pci_enable_box,
	.disable_event	= पूर्णांकel_generic_uncore_pci_disable_event,
	.enable_event	= पूर्णांकel_generic_uncore_pci_enable_event,
	.पढ़ो_counter	= पूर्णांकel_generic_uncore_pci_पढ़ो_counter,
पूर्ण;

#घोषणा UNCORE_GENERIC_MMIO_SIZE		0x4000

अटल अचिन्हित पूर्णांक generic_uncore_mmio_box_ctl(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;

	अगर (!type->box_ctls || !type->box_ctls[box->dieid] || !type->mmio_offsets)
		वापस 0;

	वापस type->box_ctls[box->dieid] + type->mmio_offsets[box->pmu->pmu_idx];
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_mmio_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित पूर्णांक box_ctl = generic_uncore_mmio_box_ctl(box);
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;
	resource_माप_प्रकार addr;

	अगर (!box_ctl) अणु
		pr_warn("Uncore type %d box %d: Invalid box control address.\n",
			type->type_id, type->box_ids[box->pmu->pmu_idx]);
		वापस;
	पूर्ण

	addr = box_ctl;
	box->io_addr = ioremap(addr, UNCORE_GENERIC_MMIO_SIZE);
	अगर (!box->io_addr) अणु
		pr_warn("Uncore type %d box %d: ioremap error for 0x%llx.\n",
			type->type_id, type->box_ids[box->pmu->pmu_idx],
			(अचिन्हित दीर्घ दीर्घ)addr);
		वापस;
	पूर्ण

	ग_लिखोl(GENERIC_PMON_BOX_CTL_INT, box->io_addr);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_mmio_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (!box->io_addr)
		वापस;

	ग_लिखोl(GENERIC_PMON_BOX_CTL_FRZ, box->io_addr);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_mmio_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (!box->io_addr)
		वापस;

	ग_लिखोl(0, box->io_addr);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_mmio_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
					     काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!box->io_addr)
		वापस;

	ग_लिखोl(hwc->config, box->io_addr + hwc->config_base);
पूर्ण

अटल व्योम पूर्णांकel_generic_uncore_mmio_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
					      काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!box->io_addr)
		वापस;

	ग_लिखोl(0, box->io_addr + hwc->config_base);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops generic_uncore_mmio_ops = अणु
	.init_box	= पूर्णांकel_generic_uncore_mmio_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.disable_box	= पूर्णांकel_generic_uncore_mmio_disable_box,
	.enable_box	= पूर्णांकel_generic_uncore_mmio_enable_box,
	.disable_event	= पूर्णांकel_generic_uncore_mmio_disable_event,
	.enable_event	= पूर्णांकel_generic_uncore_mmio_enable_event,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
पूर्ण;

अटल bool uncore_update_uncore_type(क्रमागत uncore_access_type type_id,
				      काष्ठा पूर्णांकel_uncore_type *uncore,
				      काष्ठा पूर्णांकel_uncore_discovery_type *type)
अणु
	uncore->type_id = type->type;
	uncore->num_boxes = type->num_boxes;
	uncore->num_counters = type->num_counters;
	uncore->perf_ctr_bits = type->counter_width;
	uncore->box_ids = type->ids;

	चयन (type_id) अणु
	हाल UNCORE_ACCESS_MSR:
		uncore->ops = &generic_uncore_msr_ops;
		uncore->perf_ctr = (अचिन्हित पूर्णांक)type->box_ctrl + type->ctr_offset;
		uncore->event_ctl = (अचिन्हित पूर्णांक)type->box_ctrl + type->ctl_offset;
		uncore->box_ctl = (अचिन्हित पूर्णांक)type->box_ctrl;
		uncore->msr_offsets = type->box_offset;
		अवरोध;
	हाल UNCORE_ACCESS_PCI:
		uncore->ops = &generic_uncore_pci_ops;
		uncore->perf_ctr = (अचिन्हित पूर्णांक)UNCORE_DISCOVERY_PCI_BOX_CTRL(type->box_ctrl) + type->ctr_offset;
		uncore->event_ctl = (अचिन्हित पूर्णांक)UNCORE_DISCOVERY_PCI_BOX_CTRL(type->box_ctrl) + type->ctl_offset;
		uncore->box_ctl = (अचिन्हित पूर्णांक)UNCORE_DISCOVERY_PCI_BOX_CTRL(type->box_ctrl);
		uncore->box_ctls = type->box_ctrl_die;
		uncore->pci_offsets = type->box_offset;
		अवरोध;
	हाल UNCORE_ACCESS_MMIO:
		uncore->ops = &generic_uncore_mmio_ops;
		uncore->perf_ctr = (अचिन्हित पूर्णांक)type->ctr_offset;
		uncore->event_ctl = (अचिन्हित पूर्णांक)type->ctl_offset;
		uncore->box_ctl = (अचिन्हित पूर्णांक)type->box_ctrl;
		uncore->box_ctls = type->box_ctrl_die;
		uncore->mmio_offsets = type->box_offset;
		uncore->mmio_map_size = UNCORE_GENERIC_MMIO_SIZE;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type **
पूर्णांकel_uncore_generic_init_uncores(क्रमागत uncore_access_type type_id)
अणु
	काष्ठा पूर्णांकel_uncore_discovery_type *type;
	काष्ठा पूर्णांकel_uncore_type **uncores;
	काष्ठा पूर्णांकel_uncore_type *uncore;
	काष्ठा rb_node *node;
	पूर्णांक i = 0;

	uncores = kसुस्मृति(num_discovered_types[type_id] + 1,
			  माप(काष्ठा पूर्णांकel_uncore_type *), GFP_KERNEL);
	अगर (!uncores)
		वापस empty_uncore;

	क्रम (node = rb_first(&discovery_tables); node; node = rb_next(node)) अणु
		type = rb_entry(node, काष्ठा पूर्णांकel_uncore_discovery_type, node);
		अगर (type->access_type != type_id)
			जारी;

		uncore = kzalloc(माप(काष्ठा पूर्णांकel_uncore_type), GFP_KERNEL);
		अगर (!uncore)
			अवरोध;

		uncore->event_mask = GENERIC_PMON_RAW_EVENT_MASK;
		uncore->क्रमmat_group = &generic_uncore_क्रमmat_group;

		अगर (!uncore_update_uncore_type(type_id, uncore, type)) अणु
			kमुक्त(uncore);
			जारी;
		पूर्ण
		uncores[i++] = uncore;
	पूर्ण

	वापस uncores;
पूर्ण

व्योम पूर्णांकel_uncore_generic_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = पूर्णांकel_uncore_generic_init_uncores(UNCORE_ACCESS_MSR);
पूर्ण

पूर्णांक पूर्णांकel_uncore_generic_uncore_pci_init(व्योम)
अणु
	uncore_pci_uncores = पूर्णांकel_uncore_generic_init_uncores(UNCORE_ACCESS_PCI);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_uncore_generic_uncore_mmio_init(व्योम)
अणु
	uncore_mmio_uncores = पूर्णांकel_uncore_generic_init_uncores(UNCORE_ACCESS_MMIO);
पूर्ण
