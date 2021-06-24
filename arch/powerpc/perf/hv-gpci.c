<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hypervisor supplied "gpci" ("get performance counter info") perक्रमmance
 * counter support
 *
 * Author: Cody P Schafer <cody@linux.vnet.ibm.com>
 * Copyright 2014 IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "hv-gpci: " fmt

#समावेश <linux/init.h>
#समावेश <linux/perf_event.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/पन.स>

#समावेश "hv-gpci.h"
#समावेश "hv-common.h"

/*
 * Example usage:
 *  perf stat -e 'hv_gpci/counter_info_version=3,offset=0,length=8,
 *		  secondary_index=0,starting_index=0xffffffff,request=0x10/' ...
 */

/* u32 */
EVENT_DEFINE_RANGE_FORMAT(request, config, 0, 31);
/* u32 */
/*
 * Note that starting_index, phys_processor_idx, sibling_part_id,
 * hw_chip_id, partition_id all refer to the same bit range. They
 * are basically aliases क्रम the starting_index. The specअगरic alias
 * used depends on the event. See REQUEST_IDX_KIND in hv-gpci-requests.h
 */
EVENT_DEFINE_RANGE_FORMAT(starting_index, config, 32, 63);
EVENT_DEFINE_RANGE_FORMAT_LITE(phys_processor_idx, config, 32, 63);
EVENT_DEFINE_RANGE_FORMAT_LITE(sibling_part_id, config, 32, 63);
EVENT_DEFINE_RANGE_FORMAT_LITE(hw_chip_id, config, 32, 63);
EVENT_DEFINE_RANGE_FORMAT_LITE(partition_id, config, 32, 63);

/* u16 */
EVENT_DEFINE_RANGE_FORMAT(secondary_index, config1, 0, 15);
/* u8 */
EVENT_DEFINE_RANGE_FORMAT(counter_info_version, config1, 16, 23);
/* u8, bytes of data (1-8) */
EVENT_DEFINE_RANGE_FORMAT(length, config1, 24, 31);
/* u32, byte offset */
EVENT_DEFINE_RANGE_FORMAT(offset, config1, 32, 63);

अटल cpumask_t hv_gpci_cpumask;

अटल काष्ठा attribute *क्रमmat_attrs[] = अणु
	&क्रमmat_attr_request.attr,
	&क्रमmat_attr_starting_index.attr,
	&क्रमmat_attr_phys_processor_idx.attr,
	&क्रमmat_attr_sibling_part_id.attr,
	&क्रमmat_attr_hw_chip_id.attr,
	&क्रमmat_attr_partition_id.attr,
	&क्रमmat_attr_secondary_index.attr,
	&क्रमmat_attr_counter_info_version.attr,

	&क्रमmat_attr_offset.attr,
	&क्रमmat_attr_length.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group क्रमmat_group = अणु
	.name = "format",
	.attrs = क्रमmat_attrs,
पूर्ण;

अटल काष्ठा attribute_group event_group = अणु
	.name  = "events",
	.attrs = hv_gpci_event_attrs,
पूर्ण;

#घोषणा HV_CAPS_ATTR(_name, _क्रमmat)				\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,	\
			    अक्षर *page)				\
अणु								\
	काष्ठा hv_perf_caps caps;				\
	अचिन्हित दीर्घ hret = hv_perf_caps_get(&caps);		\
	अगर (hret)						\
		वापस -EIO;					\
								\
	वापस प्र_लिखो(page, _क्रमmat, caps._name);		\
पूर्ण								\
अटल काष्ठा device_attribute hv_caps_attr_##_name = __ATTR_RO(_name)

अटल sमाप_प्रकार kernel_version_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *page)
अणु
	वापस प्र_लिखो(page, "0x%x\n", COUNTER_INFO_VERSION_CURRENT);
पूर्ण

अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &hv_gpci_cpumask);
पूर्ण

अटल DEVICE_ATTR_RO(kernel_version);
अटल DEVICE_ATTR_RO(cpumask);

HV_CAPS_ATTR(version, "0x%x\n");
HV_CAPS_ATTR(ga, "%d\n");
HV_CAPS_ATTR(expanded, "%d\n");
HV_CAPS_ATTR(lab, "%d\n");
HV_CAPS_ATTR(collect_privileged, "%d\n");

अटल काष्ठा attribute *पूर्णांकerface_attrs[] = अणु
	&dev_attr_kernel_version.attr,
	&hv_caps_attr_version.attr,
	&hv_caps_attr_ga.attr,
	&hv_caps_attr_expanded.attr,
	&hv_caps_attr_lab.attr,
	&hv_caps_attr_collect_privileged.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpumask_attr_group = अणु
	.attrs = cpumask_attrs,
पूर्ण;

अटल काष्ठा attribute_group पूर्णांकerface_group = अणु
	.name = "interface",
	.attrs = पूर्णांकerface_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&क्रमmat_group,
	&event_group,
	&पूर्णांकerface_group,
	&cpumask_attr_group,
	शून्य,
पूर्ण;

अटल DEFINE_PER_CPU(अक्षर, hv_gpci_reqb[HGPCI_REQ_BUFFER_SIZE]) __aligned(माप(uपूर्णांक64_t));

अटल अचिन्हित दीर्घ single_gpci_request(u32 req, u32 starting_index,
		u16 secondary_index, u8 version_in, u32 offset, u8 length,
		u64 *value)
अणु
	अचिन्हित दीर्घ ret;
	माप_प्रकार i;
	u64 count;
	काष्ठा hv_gpci_request_buffer *arg;

	arg = (व्योम *)get_cpu_var(hv_gpci_reqb);
	स_रखो(arg, 0, HGPCI_REQ_BUFFER_SIZE);

	arg->params.counter_request = cpu_to_be32(req);
	arg->params.starting_index = cpu_to_be32(starting_index);
	arg->params.secondary_index = cpu_to_be16(secondary_index);
	arg->params.counter_info_version_in = version_in;

	ret = plpar_hcall_norets(H_GET_PERF_COUNTER_INFO,
			virt_to_phys(arg), HGPCI_REQ_BUFFER_SIZE);
	अगर (ret) अणु
		pr_devel("hcall failed: 0x%lx\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * we verअगरy offset and length are within the zeroed buffer at event
	 * init.
	 */
	count = 0;
	क्रम (i = offset; i < offset + length; i++)
		count |= arg->bytes[i] << (i - offset);

	*value = count;
out:
	put_cpu_var(hv_gpci_reqb);
	वापस ret;
पूर्ण

अटल u64 h_gpci_get_value(काष्ठा perf_event *event)
अणु
	u64 count;
	अचिन्हित दीर्घ ret = single_gpci_request(event_get_request(event),
					event_get_starting_index(event),
					event_get_secondary_index(event),
					event_get_counter_info_version(event),
					event_get_offset(event),
					event_get_length(event),
					&count);
	अगर (ret)
		वापस 0;
	वापस count;
पूर्ण

अटल व्योम h_gpci_event_update(काष्ठा perf_event *event)
अणु
	s64 prev;
	u64 now = h_gpci_get_value(event);
	prev = local64_xchg(&event->hw.prev_count, now);
	local64_add(now - prev, &event->count);
पूर्ण

अटल व्योम h_gpci_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	local64_set(&event->hw.prev_count, h_gpci_get_value(event));
पूर्ण

अटल व्योम h_gpci_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	h_gpci_event_update(event);
पूर्ण

अटल पूर्णांक h_gpci_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		h_gpci_event_start(event, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक h_gpci_event_init(काष्ठा perf_event *event)
अणु
	u64 count;
	u8 length;

	/* Not our event */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* config2 is unused */
	अगर (event->attr.config2) अणु
		pr_devel("config2 set when reserved\n");
		वापस -EINVAL;
	पूर्ण

	/* no branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	length = event_get_length(event);
	अगर (length < 1 || length > 8) अणु
		pr_devel("length invalid\n");
		वापस -EINVAL;
	पूर्ण

	/* last byte within the buffer? */
	अगर ((event_get_offset(event) + length) > HGPCI_MAX_DATA_BYTES) अणु
		pr_devel("request outside of buffer: %zu > %zu\n",
				(माप_प्रकार)event_get_offset(event) + length,
				HGPCI_MAX_DATA_BYTES);
		वापस -EINVAL;
	पूर्ण

	/* check अगर the request works... */
	अगर (single_gpci_request(event_get_request(event),
				event_get_starting_index(event),
				event_get_secondary_index(event),
				event_get_counter_info_version(event),
				event_get_offset(event),
				length,
				&count)) अणु
		pr_devel("gpci hcall failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pmu h_gpci_pmu = अणु
	.task_ctx_nr = perf_invalid_context,

	.name = "hv_gpci",
	.attr_groups = attr_groups,
	.event_init  = h_gpci_event_init,
	.add         = h_gpci_event_add,
	.del         = h_gpci_event_stop,
	.start       = h_gpci_event_start,
	.stop        = h_gpci_event_stop,
	.पढ़ो        = h_gpci_event_update,
	.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;

अटल पूर्णांक ppc_hv_gpci_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_empty(&hv_gpci_cpumask))
		cpumask_set_cpu(cpu, &hv_gpci_cpumask);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_hv_gpci_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	/* Check अगर निकासing cpu is used क्रम collecting gpci events */
	अगर (!cpumask_test_and_clear_cpu(cpu, &hv_gpci_cpumask))
		वापस 0;

	/* Find a new cpu to collect gpci events */
	target = cpumask_last(cpu_active_mask);

	अगर (target < 0 || target >= nr_cpu_ids) अणु
		pr_err("hv_gpci: CPU hotplug init failed\n");
		वापस -1;
	पूर्ण

	/* Migrate gpci events to the new target */
	cpumask_set_cpu(target, &hv_gpci_cpumask);
	perf_pmu_migrate_context(&h_gpci_pmu, cpu, target);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_gpci_cpu_hotplug_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_HV_GPCI_ONLINE,
			  "perf/powerpc/hv_gcpi:online",
			  ppc_hv_gpci_cpu_online,
			  ppc_hv_gpci_cpu_offline);
पूर्ण

अटल पूर्णांक hv_gpci_init(व्योम)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ hret;
	काष्ठा hv_perf_caps caps;

	hv_gpci_निश्चित_offsets_correct();

	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		pr_debug("not a virtualized system, not enabling\n");
		वापस -ENODEV;
	पूर्ण

	hret = hv_perf_caps_get(&caps);
	अगर (hret) अणु
		pr_debug("could not obtain capabilities, not enabling, rc=%ld\n",
				hret);
		वापस -ENODEV;
	पूर्ण

	/* init cpuhotplug */
	r = hv_gpci_cpu_hotplug_init();
	अगर (r)
		वापस r;

	/* sampling not supported */
	h_gpci_pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	r = perf_pmu_रेजिस्टर(&h_gpci_pmu, h_gpci_pmu.name, -1);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

device_initcall(hv_gpci_init);
