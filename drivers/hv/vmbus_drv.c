<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/completion.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/efi.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscore_ops.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश "hyperv_vmbus.h"

काष्ठा vmbus_dynid अणु
	काष्ठा list_head node;
	काष्ठा hv_vmbus_device_id id;
पूर्ण;

अटल काष्ठा acpi_device  *hv_acpi_dev;

अटल काष्ठा completion probe_event;

अटल पूर्णांक hyperv_cpuhp_online;

अटल व्योम *hv_panic_page;

अटल दीर्घ __percpu *vmbus_evt;

/* Values parsed from ACPI DSDT */
पूर्णांक vmbus_irq;
पूर्णांक vmbus_पूर्णांकerrupt;

/*
 * Boolean to control whether to report panic messages over Hyper-V.
 *
 * It can be set via /proc/sys/kernel/hyperv_record_panic_msg
 */
अटल पूर्णांक sysctl_record_panic_msg = 1;

अटल पूर्णांक hyperv_report_reg(व्योम)
अणु
	वापस !sysctl_record_panic_msg || !hv_panic_page;
पूर्ण

अटल पूर्णांक hyperv_panic_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *args)
अणु
	काष्ठा pt_regs *regs;

	vmbus_initiate_unload(true);

	/*
	 * Hyper-V should be notअगरied only once about a panic.  If we will be
	 * करोing hyperv_report_panic_msg() later with kmsg data, करोn't करो
	 * the notअगरication here.
	 */
	अगर (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE
	    && hyperv_report_reg()) अणु
		regs = current_pt_regs();
		hyperv_report_panic(regs, val, false);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक hyperv_die_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			    व्योम *args)
अणु
	काष्ठा die_args *die = args;
	काष्ठा pt_regs *regs = die->regs;

	/* Don't notअगरy Hyper-V अगर the die event is other than oops */
	अगर (val != DIE_OOPS)
		वापस NOTIFY_DONE;

	/*
	 * Hyper-V should be notअगरied only once about a panic.  If we will be
	 * करोing hyperv_report_panic_msg() later with kmsg data, करोn't करो
	 * the notअगरication here.
	 */
	अगर (hyperv_report_reg())
		hyperv_report_panic(regs, val, true);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block hyperv_die_block = अणु
	.notअगरier_call = hyperv_die_event,
पूर्ण;
अटल काष्ठा notअगरier_block hyperv_panic_block = अणु
	.notअगरier_call = hyperv_panic_event,
पूर्ण;

अटल स्थिर अक्षर *fb_mmio_name = "fb_range";
अटल काष्ठा resource *fb_mmio;
अटल काष्ठा resource *hyperv_mmio;
अटल DEFINE_MUTEX(hyperv_mmio_lock);

अटल पूर्णांक vmbus_exists(व्योम)
अणु
	अगर (hv_acpi_dev == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल u8 channel_monitor_group(स्थिर काष्ठा vmbus_channel *channel)
अणु
	वापस (u8)channel->offermsg.monitorid / 32;
पूर्ण

अटल u8 channel_monitor_offset(स्थिर काष्ठा vmbus_channel *channel)
अणु
	वापस (u8)channel->offermsg.monitorid % 32;
पूर्ण

अटल u32 channel_pending(स्थिर काष्ठा vmbus_channel *channel,
			   स्थिर काष्ठा hv_monitor_page *monitor_page)
अणु
	u8 monitor_group = channel_monitor_group(channel);

	वापस monitor_page->trigger_group[monitor_group].pending;
पूर्ण

अटल u32 channel_latency(स्थिर काष्ठा vmbus_channel *channel,
			   स्थिर काष्ठा hv_monitor_page *monitor_page)
अणु
	u8 monitor_group = channel_monitor_group(channel);
	u8 monitor_offset = channel_monitor_offset(channel);

	वापस monitor_page->latency[monitor_group][monitor_offset];
पूर्ण

अटल u32 channel_conn_id(काष्ठा vmbus_channel *channel,
			   काष्ठा hv_monitor_page *monitor_page)
अणु
	u8 monitor_group = channel_monitor_group(channel);
	u8 monitor_offset = channel_monitor_offset(channel);

	वापस monitor_page->parameter[monitor_group][monitor_offset].connectionid.u.id;
पूर्ण

अटल sमाप_प्रकार id_show(काष्ठा device *dev, काष्ठा device_attribute *dev_attr,
		       अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", hv_dev->channel->offermsg.child_relid);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *dev_attr,
			  अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", hv_dev->channel->state);
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार monitor_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n", hv_dev->channel->offermsg.monitorid);
पूर्ण
अटल DEVICE_ATTR_RO(monitor_id);

अटल sमाप_प्रकार class_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "{%pUl}\n",
		       &hv_dev->channel->offermsg.offer.अगर_type);
पूर्ण
अटल DEVICE_ATTR_RO(class_id);

अटल sमाप_प्रकार device_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "{%pUl}\n",
		       &hv_dev->channel->offermsg.offer.अगर_instance);
पूर्ण
अटल DEVICE_ATTR_RO(device_id);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	वापस प्र_लिखो(buf, "vmbus:%*phN\n", UUID_SIZE, &hv_dev->dev_type);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

#अगर_घोषित CONFIG_NUMA
अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%d\n", cpu_to_node(hv_dev->channel->target_cpu));
पूर्ण
अटल DEVICE_ATTR_RO(numa_node);
#पूर्ण_अगर

अटल sमाप_प्रकार server_monitor_pending_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_pending(hv_dev->channel,
				       vmbus_connection.monitor_pages[0]));
पूर्ण
अटल DEVICE_ATTR_RO(server_monitor_pending);

अटल sमाप_प्रकार client_monitor_pending_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_pending(hv_dev->channel,
				       vmbus_connection.monitor_pages[1]));
पूर्ण
अटल DEVICE_ATTR_RO(client_monitor_pending);

अटल sमाप_प्रकार server_monitor_latency_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_latency(hv_dev->channel,
				       vmbus_connection.monitor_pages[0]));
पूर्ण
अटल DEVICE_ATTR_RO(server_monitor_latency);

अटल sमाप_प्रकार client_monitor_latency_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_latency(hv_dev->channel,
				       vmbus_connection.monitor_pages[1]));
पूर्ण
अटल DEVICE_ATTR_RO(client_monitor_latency);

अटल sमाप_प्रकार server_monitor_conn_id_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_conn_id(hv_dev->channel,
				       vmbus_connection.monitor_pages[0]));
पूर्ण
अटल DEVICE_ATTR_RO(server_monitor_conn_id);

अटल sमाप_प्रकार client_monitor_conn_id_show(काष्ठा device *dev,
					   काष्ठा device_attribute *dev_attr,
					   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	अगर (!hv_dev->channel)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%d\n",
		       channel_conn_id(hv_dev->channel,
				       vmbus_connection.monitor_pages[1]));
पूर्ण
अटल DEVICE_ATTR_RO(client_monitor_conn_id);

अटल sमाप_प्रकार out_पूर्णांकr_mask_show(काष्ठा device *dev,
				  काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info outbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->outbound,
					  &outbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", outbound.current_पूर्णांकerrupt_mask);
पूर्ण
अटल DEVICE_ATTR_RO(out_पूर्णांकr_mask);

अटल sमाप_प्रकार out_पढ़ो_index_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info outbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->outbound,
					  &outbound);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", outbound.current_पढ़ो_index);
पूर्ण
अटल DEVICE_ATTR_RO(out_पढ़ो_index);

अटल sमाप_प्रकार out_ग_लिखो_index_show(काष्ठा device *dev,
				    काष्ठा device_attribute *dev_attr,
				    अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info outbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->outbound,
					  &outbound);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", outbound.current_ग_लिखो_index);
पूर्ण
अटल DEVICE_ATTR_RO(out_ग_लिखो_index);

अटल sमाप_प्रकार out_पढ़ो_bytes_avail_show(काष्ठा device *dev,
					 काष्ठा device_attribute *dev_attr,
					 अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info outbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->outbound,
					  &outbound);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", outbound.bytes_avail_toपढ़ो);
पूर्ण
अटल DEVICE_ATTR_RO(out_पढ़ो_bytes_avail);

अटल sमाप_प्रकार out_ग_लिखो_bytes_avail_show(काष्ठा device *dev,
					  काष्ठा device_attribute *dev_attr,
					  अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info outbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->outbound,
					  &outbound);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", outbound.bytes_avail_toग_लिखो);
पूर्ण
अटल DEVICE_ATTR_RO(out_ग_लिखो_bytes_avail);

अटल sमाप_प्रकार in_पूर्णांकr_mask_show(काष्ठा device *dev,
				 काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info inbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", inbound.current_पूर्णांकerrupt_mask);
पूर्ण
अटल DEVICE_ATTR_RO(in_पूर्णांकr_mask);

अटल sमाप_प्रकार in_पढ़ो_index_show(काष्ठा device *dev,
				  काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info inbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", inbound.current_पढ़ो_index);
पूर्ण
अटल DEVICE_ATTR_RO(in_पढ़ो_index);

अटल sमाप_प्रकार in_ग_लिखो_index_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info inbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", inbound.current_ग_लिखो_index);
पूर्ण
अटल DEVICE_ATTR_RO(in_ग_लिखो_index);

अटल sमाप_प्रकार in_पढ़ो_bytes_avail_show(काष्ठा device *dev,
					काष्ठा device_attribute *dev_attr,
					अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info inbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", inbound.bytes_avail_toपढ़ो);
पूर्ण
अटल DEVICE_ATTR_RO(in_पढ़ो_bytes_avail);

अटल sमाप_प्रकार in_ग_लिखो_bytes_avail_show(काष्ठा device *dev,
					 काष्ठा device_attribute *dev_attr,
					 अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा hv_ring_buffer_debug_info inbound;
	पूर्णांक ret;

	अगर (!hv_dev->channel)
		वापस -ENODEV;

	ret = hv_ringbuffer_get_debuginfo(&hv_dev->channel->inbound, &inbound);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", inbound.bytes_avail_toग_लिखो);
पूर्ण
अटल DEVICE_ATTR_RO(in_ग_लिखो_bytes_avail);

अटल sमाप_प्रकार channel_vp_mapping_show(काष्ठा device *dev,
				       काष्ठा device_attribute *dev_attr,
				       अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	काष्ठा vmbus_channel *channel = hv_dev->channel, *cur_sc;
	पूर्णांक buf_size = PAGE_SIZE, n_written, tot_written;
	काष्ठा list_head *cur;

	अगर (!channel)
		वापस -ENODEV;

	mutex_lock(&vmbus_connection.channel_mutex);

	tot_written = snम_लिखो(buf, buf_size, "%u:%u\n",
		channel->offermsg.child_relid, channel->target_cpu);

	list_क्रम_each(cur, &channel->sc_list) अणु
		अगर (tot_written >= buf_size - 1)
			अवरोध;

		cur_sc = list_entry(cur, काष्ठा vmbus_channel, sc_list);
		n_written = scnम_लिखो(buf + tot_written,
				     buf_size - tot_written,
				     "%u:%u\n",
				     cur_sc->offermsg.child_relid,
				     cur_sc->target_cpu);
		tot_written += n_written;
	पूर्ण

	mutex_unlock(&vmbus_connection.channel_mutex);

	वापस tot_written;
पूर्ण
अटल DEVICE_ATTR_RO(channel_vp_mapping);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev,
			   काष्ठा device_attribute *dev_attr,
			   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	वापस प्र_लिखो(buf, "0x%x\n", hv_dev->venकरोr_id);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार device_show(काष्ठा device *dev,
			   काष्ठा device_attribute *dev_attr,
			   अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	वापस प्र_लिखो(buf, "0x%x\n", hv_dev->device_id);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	अक्षर *driver_override, *old, *cp;

	/* We need to keep extra room क्रम a newline */
	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	device_lock(dev);
	old = hv_dev->driver_override;
	अगर (म_माप(driver_override)) अणु
		hv_dev->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		hv_dev->driver_override = शून्य;
	पूर्ण
	device_unlock(dev);

	kमुक्त(old);

	वापस count;
पूर्ण

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(dev);
	sमाप_प्रकार len;

	device_lock(dev);
	len = snम_लिखो(buf, PAGE_SIZE, "%s\n", hv_dev->driver_override);
	device_unlock(dev);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

/* Set up per device attributes in /sys/bus/vmbus/devices/<bus device> */
अटल काष्ठा attribute *vmbus_dev_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_state.attr,
	&dev_attr_monitor_id.attr,
	&dev_attr_class_id.attr,
	&dev_attr_device_id.attr,
	&dev_attr_modalias.attr,
#अगर_घोषित CONFIG_NUMA
	&dev_attr_numa_node.attr,
#पूर्ण_अगर
	&dev_attr_server_monitor_pending.attr,
	&dev_attr_client_monitor_pending.attr,
	&dev_attr_server_monitor_latency.attr,
	&dev_attr_client_monitor_latency.attr,
	&dev_attr_server_monitor_conn_id.attr,
	&dev_attr_client_monitor_conn_id.attr,
	&dev_attr_out_पूर्णांकr_mask.attr,
	&dev_attr_out_पढ़ो_index.attr,
	&dev_attr_out_ग_लिखो_index.attr,
	&dev_attr_out_पढ़ो_bytes_avail.attr,
	&dev_attr_out_ग_लिखो_bytes_avail.attr,
	&dev_attr_in_पूर्णांकr_mask.attr,
	&dev_attr_in_पढ़ो_index.attr,
	&dev_attr_in_ग_लिखो_index.attr,
	&dev_attr_in_पढ़ो_bytes_avail.attr,
	&dev_attr_in_ग_लिखो_bytes_avail.attr,
	&dev_attr_channel_vp_mapping.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;

/*
 * Device-level attribute_group callback function. Returns the permission क्रम
 * each attribute, and वापसs 0 अगर an attribute is not visible.
 */
अटल umode_t vmbus_dev_attr_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	स्थिर काष्ठा hv_device *hv_dev = device_to_hv_device(dev);

	/* Hide the monitor attributes अगर the monitor mechanism is not used. */
	अगर (!hv_dev->channel->offermsg.monitor_allocated &&
	    (attr == &dev_attr_monitor_id.attr ||
	     attr == &dev_attr_server_monitor_pending.attr ||
	     attr == &dev_attr_client_monitor_pending.attr ||
	     attr == &dev_attr_server_monitor_latency.attr ||
	     attr == &dev_attr_client_monitor_latency.attr ||
	     attr == &dev_attr_server_monitor_conn_id.attr ||
	     attr == &dev_attr_client_monitor_conn_id.attr))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group vmbus_dev_group = अणु
	.attrs = vmbus_dev_attrs,
	.is_visible = vmbus_dev_attr_is_visible
पूर्ण;
__ATTRIBUTE_GROUPS(vmbus_dev);

/* Set up the attribute क्रम /sys/bus/vmbus/hibernation */
अटल sमाप_प्रकार hibernation_show(काष्ठा bus_type *bus, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", !!hv_is_hibernation_supported());
पूर्ण

अटल BUS_ATTR_RO(hibernation);

अटल काष्ठा attribute *vmbus_bus_attrs[] = अणु
	&bus_attr_hibernation.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group vmbus_bus_group = अणु
	.attrs = vmbus_bus_attrs,
पूर्ण;
__ATTRIBUTE_GROUPS(vmbus_bus);

/*
 * vmbus_uevent - add uevent क्रम our device
 *
 * This routine is invoked when a device is added or हटाओd on the vmbus to
 * generate a uevent to udev in the userspace. The udev will then look at its
 * rule and the uevent generated here to load the appropriate driver
 *
 * The alias string will be of the क्रमm vmbus:guid where guid is the string
 * representation of the device guid (each byte of the guid will be
 * represented with two hex अक्षरacters.
 */
अटल पूर्णांक vmbus_uevent(काष्ठा device *device, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा hv_device *dev = device_to_hv_device(device);
	स्थिर अक्षर *क्रमmat = "MODALIAS=vmbus:%*phN";

	वापस add_uevent_var(env, क्रमmat, UUID_SIZE, &dev->dev_type);
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id *
hv_vmbus_dev_match(स्थिर काष्ठा hv_vmbus_device_id *id, स्थिर guid_t *guid)
अणु
	अगर (id == शून्य)
		वापस शून्य; /* empty device table */

	क्रम (; !guid_is_null(&id->guid); id++)
		अगर (guid_equal(&id->guid, guid))
			वापस id;

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id *
hv_vmbus_dynid_match(काष्ठा hv_driver *drv, स्थिर guid_t *guid)
अणु
	स्थिर काष्ठा hv_vmbus_device_id *id = शून्य;
	काष्ठा vmbus_dynid *dynid;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry(dynid, &drv->dynids.list, node) अणु
		अगर (guid_equal(&dynid->id.guid, guid)) अणु
			id = &dynid->id;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&drv->dynids.lock);

	वापस id;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id vmbus_device_null;

/*
 * Return a matching hv_vmbus_device_id poपूर्णांकer.
 * If there is no match, वापस शून्य.
 */
अटल स्थिर काष्ठा hv_vmbus_device_id *hv_vmbus_get_id(काष्ठा hv_driver *drv,
							काष्ठा hv_device *dev)
अणु
	स्थिर guid_t *guid = &dev->dev_type;
	स्थिर काष्ठा hv_vmbus_device_id *id;

	/* When driver_override is set, only bind to the matching driver */
	अगर (dev->driver_override && म_भेद(dev->driver_override, drv->name))
		वापस शून्य;

	/* Look at the dynamic ids first, beक्रमe the अटल ones */
	id = hv_vmbus_dynid_match(drv, guid);
	अगर (!id)
		id = hv_vmbus_dev_match(drv->id_table, guid);

	/* driver_override will always match, send a dummy id */
	अगर (!id && dev->driver_override)
		id = &vmbus_device_null;

	वापस id;
पूर्ण

/* vmbus_add_dynid - add a new device ID to this driver and re-probe devices */
अटल पूर्णांक vmbus_add_dynid(काष्ठा hv_driver *drv, guid_t *guid)
अणु
	काष्ठा vmbus_dynid *dynid;

	dynid = kzalloc(माप(*dynid), GFP_KERNEL);
	अगर (!dynid)
		वापस -ENOMEM;

	dynid->id.guid = *guid;

	spin_lock(&drv->dynids.lock);
	list_add_tail(&dynid->node, &drv->dynids.list);
	spin_unlock(&drv->dynids.lock);

	वापस driver_attach(&drv->driver);
पूर्ण

अटल व्योम vmbus_मुक्त_dynids(काष्ठा hv_driver *drv)
अणु
	काष्ठा vmbus_dynid *dynid, *n;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &drv->dynids.list, node) अणु
		list_del(&dynid->node);
		kमुक्त(dynid);
	पूर्ण
	spin_unlock(&drv->dynids.lock);
पूर्ण

/*
 * store_new_id - sysfs frontend to vmbus_add_dynid()
 *
 * Allow GUIDs to be added to an existing driver via sysfs.
 */
अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा hv_driver *drv = drv_to_hv_drv(driver);
	guid_t guid;
	sमाप_प्रकार retval;

	retval = guid_parse(buf, &guid);
	अगर (retval)
		वापस retval;

	अगर (hv_vmbus_dynid_match(drv, &guid))
		वापस -EEXIST;

	retval = vmbus_add_dynid(drv, &guid);
	अगर (retval)
		वापस retval;
	वापस count;
पूर्ण
अटल DRIVER_ATTR_WO(new_id);

/*
 * store_हटाओ_id - हटाओ a PCI device ID from this driver
 *
 * Removes a dynamic pci device ID to this driver.
 */
अटल sमाप_प्रकार हटाओ_id_store(काष्ठा device_driver *driver, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा hv_driver *drv = drv_to_hv_drv(driver);
	काष्ठा vmbus_dynid *dynid, *n;
	guid_t guid;
	sमाप_प्रकार retval;

	retval = guid_parse(buf, &guid);
	अगर (retval)
		वापस retval;

	retval = -ENODEV;
	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &drv->dynids.list, node) अणु
		काष्ठा hv_vmbus_device_id *id = &dynid->id;

		अगर (guid_equal(&id->guid, &guid)) अणु
			list_del(&dynid->node);
			kमुक्त(dynid);
			retval = count;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&drv->dynids.lock);

	वापस retval;
पूर्ण
अटल DRIVER_ATTR_WO(हटाओ_id);

अटल काष्ठा attribute *vmbus_drv_attrs[] = अणु
	&driver_attr_new_id.attr,
	&driver_attr_हटाओ_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vmbus_drv);


/*
 * vmbus_match - Attempt to match the specअगरied device to the specअगरied driver
 */
अटल पूर्णांक vmbus_match(काष्ठा device *device, काष्ठा device_driver *driver)
अणु
	काष्ठा hv_driver *drv = drv_to_hv_drv(driver);
	काष्ठा hv_device *hv_dev = device_to_hv_device(device);

	/* The hv_sock driver handles all hv_sock offers. */
	अगर (is_hvsock_channel(hv_dev->channel))
		वापस drv->hvsock;

	अगर (hv_vmbus_get_id(drv, hv_dev))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * vmbus_probe - Add the new vmbus's child device
 */
अटल पूर्णांक vmbus_probe(काष्ठा device *child_device)
अणु
	पूर्णांक ret = 0;
	काष्ठा hv_driver *drv =
			drv_to_hv_drv(child_device->driver);
	काष्ठा hv_device *dev = device_to_hv_device(child_device);
	स्थिर काष्ठा hv_vmbus_device_id *dev_id;

	dev_id = hv_vmbus_get_id(drv, dev);
	अगर (drv->probe) अणु
		ret = drv->probe(dev, dev_id);
		अगर (ret != 0)
			pr_err("probe failed for device %s (%d)\n",
			       dev_name(child_device), ret);

	पूर्ण अन्यथा अणु
		pr_err("probe not set for driver %s\n",
		       dev_name(child_device));
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * vmbus_हटाओ - Remove a vmbus device
 */
अटल पूर्णांक vmbus_हटाओ(काष्ठा device *child_device)
अणु
	काष्ठा hv_driver *drv;
	काष्ठा hv_device *dev = device_to_hv_device(child_device);

	अगर (child_device->driver) अणु
		drv = drv_to_hv_drv(child_device->driver);
		अगर (drv->हटाओ)
			drv->हटाओ(dev);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * vmbus_shutकरोwn - Shutकरोwn a vmbus device
 */
अटल व्योम vmbus_shutकरोwn(काष्ठा device *child_device)
अणु
	काष्ठा hv_driver *drv;
	काष्ठा hv_device *dev = device_to_hv_device(child_device);


	/* The device may not be attached yet */
	अगर (!child_device->driver)
		वापस;

	drv = drv_to_hv_drv(child_device->driver);

	अगर (drv->shutकरोwn)
		drv->shutकरोwn(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * vmbus_suspend - Suspend a vmbus device
 */
अटल पूर्णांक vmbus_suspend(काष्ठा device *child_device)
अणु
	काष्ठा hv_driver *drv;
	काष्ठा hv_device *dev = device_to_hv_device(child_device);

	/* The device may not be attached yet */
	अगर (!child_device->driver)
		वापस 0;

	drv = drv_to_hv_drv(child_device->driver);
	अगर (!drv->suspend)
		वापस -EOPNOTSUPP;

	वापस drv->suspend(dev);
पूर्ण

/*
 * vmbus_resume - Resume a vmbus device
 */
अटल पूर्णांक vmbus_resume(काष्ठा device *child_device)
अणु
	काष्ठा hv_driver *drv;
	काष्ठा hv_device *dev = device_to_hv_device(child_device);

	/* The device may not be attached yet */
	अगर (!child_device->driver)
		वापस 0;

	drv = drv_to_hv_drv(child_device->driver);
	अगर (!drv->resume)
		वापस -EOPNOTSUPP;

	वापस drv->resume(dev);
पूर्ण
#अन्यथा
#घोषणा vmbus_suspend शून्य
#घोषणा vmbus_resume शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/*
 * vmbus_device_release - Final callback release of the vmbus child device
 */
अटल व्योम vmbus_device_release(काष्ठा device *device)
अणु
	काष्ठा hv_device *hv_dev = device_to_hv_device(device);
	काष्ठा vmbus_channel *channel = hv_dev->channel;

	hv_debug_rm_dev_dir(hv_dev);

	mutex_lock(&vmbus_connection.channel_mutex);
	hv_process_channel_removal(channel);
	mutex_unlock(&vmbus_connection.channel_mutex);
	kमुक्त(hv_dev);
पूर्ण

/*
 * Note: we must use the "noirq" ops: see the comment beक्रमe vmbus_bus_pm.
 *
 * suspend_noirq/resume_noirq are set to शून्य to support Suspend-to-Idle: we
 * shouldn't suspend the vmbus devices upon Suspend-to-Idle, otherwise there
 * is no way to wake up a Generation-2 VM.
 *
 * The other 4 ops are क्रम hibernation.
 */

अटल स्थिर काष्ठा dev_pm_ops vmbus_pm = अणु
	.suspend_noirq	= शून्य,
	.resume_noirq	= शून्य,
	.मुक्तze_noirq	= vmbus_suspend,
	.thaw_noirq	= vmbus_resume,
	.घातeroff_noirq	= vmbus_suspend,
	.restore_noirq	= vmbus_resume,
पूर्ण;

/* The one and only one */
अटल काष्ठा bus_type  hv_bus = अणु
	.name =		"vmbus",
	.match =		vmbus_match,
	.shutकरोwn =		vmbus_shutकरोwn,
	.हटाओ =		vmbus_हटाओ,
	.probe =		vmbus_probe,
	.uevent =		vmbus_uevent,
	.dev_groups =		vmbus_dev_groups,
	.drv_groups =		vmbus_drv_groups,
	.bus_groups =		vmbus_bus_groups,
	.pm =			&vmbus_pm,
पूर्ण;

काष्ठा onmessage_work_context अणु
	काष्ठा work_काष्ठा work;
	काष्ठा अणु
		काष्ठा hv_message_header header;
		u8 payload[];
	पूर्ण msg;
पूर्ण;

अटल व्योम vmbus_onmessage_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा onmessage_work_context *ctx;

	/* Do not process messages अगर we're in DISCONNECTED state */
	अगर (vmbus_connection.conn_state == DISCONNECTED)
		वापस;

	ctx = container_of(work, काष्ठा onmessage_work_context,
			   work);
	vmbus_onmessage((काष्ठा vmbus_channel_message_header *)
			&ctx->msg.payload);
	kमुक्त(ctx);
पूर्ण

व्योम vmbus_on_msg_dpc(अचिन्हित दीर्घ data)
अणु
	काष्ठा hv_per_cpu_context *hv_cpu = (व्योम *)data;
	व्योम *page_addr = hv_cpu->synic_message_page;
	काष्ठा hv_message msg_copy, *msg = (काष्ठा hv_message *)page_addr +
				  VMBUS_MESSAGE_SINT;
	काष्ठा vmbus_channel_message_header *hdr;
	क्रमागत vmbus_channel_message_type msgtype;
	स्थिर काष्ठा vmbus_channel_message_table_entry *entry;
	काष्ठा onmessage_work_context *ctx;
	__u8 payload_size;
	u32 message_type;

	/*
	 * 'enum vmbus_channel_message_type' is supposed to always be 'u32' as
	 * it is being used in 'struct vmbus_channel_message_header' definition
	 * which is supposed to match hypervisor ABI.
	 */
	BUILD_BUG_ON(माप(क्रमागत vmbus_channel_message_type) != माप(u32));

	/*
	 * Since the message is in memory shared with the host, an erroneous or
	 * malicious Hyper-V could modअगरy the message जबतक vmbus_on_msg_dpc()
	 * or inभागidual message handlers are executing; to prevent this, copy
	 * the message पूर्णांकo निजी memory.
	 */
	स_नकल(&msg_copy, msg, माप(काष्ठा hv_message));

	message_type = msg_copy.header.message_type;
	अगर (message_type == HVMSG_NONE)
		/* no msg */
		वापस;

	hdr = (काष्ठा vmbus_channel_message_header *)msg_copy.u.payload;
	msgtype = hdr->msgtype;

	trace_vmbus_on_msg_dpc(hdr);

	अगर (msgtype >= CHANNELMSG_COUNT) अणु
		WARN_ONCE(1, "unknown msgtype=%d\n", msgtype);
		जाओ msg_handled;
	पूर्ण

	payload_size = msg_copy.header.payload_size;
	अगर (payload_size > HV_MESSAGE_PAYLOAD_BYTE_COUNT) अणु
		WARN_ONCE(1, "payload size is too large (%d)\n", payload_size);
		जाओ msg_handled;
	पूर्ण

	entry = &channel_message_table[msgtype];

	अगर (!entry->message_handler)
		जाओ msg_handled;

	अगर (payload_size < entry->min_payload_len) अणु
		WARN_ONCE(1, "message too short: msgtype=%d len=%d\n", msgtype, payload_size);
		जाओ msg_handled;
	पूर्ण

	अगर (entry->handler_type	== VMHT_BLOCKING) अणु
		ctx = kदो_स्मृति(माप(*ctx) + payload_size, GFP_ATOMIC);
		अगर (ctx == शून्य)
			वापस;

		INIT_WORK(&ctx->work, vmbus_onmessage_work);
		स_नकल(&ctx->msg, &msg_copy, माप(msg->header) + payload_size);

		/*
		 * The host can generate a rescind message जबतक we
		 * may still be handling the original offer. We deal with
		 * this condition by relying on the synchronization provided
		 * by offer_in_progress and by channel_mutex.  See also the
		 * अंतरभूत comments in vmbus_onoffer_rescind().
		 */
		चयन (msgtype) अणु
		हाल CHANNELMSG_RESCIND_CHANNELOFFER:
			/*
			 * If we are handling the rescind message;
			 * schedule the work on the global work queue.
			 *
			 * The OFFER message and the RESCIND message should
			 * not be handled by the same serialized work queue,
			 * because the OFFER handler may call vmbus_खोलो(),
			 * which tries to खोलो the channel by sending an
			 * OPEN_CHANNEL message to the host and रुकोs क्रम
			 * the host's response; however, अगर the host has
			 * rescinded the channel beक्रमe it receives the
			 * OPEN_CHANNEL message, the host just silently
			 * ignores the OPEN_CHANNEL message; as a result,
			 * the guest's OFFER handler hangs क्रम ever, अगर we
			 * handle the RESCIND message in the same serialized
			 * work queue: the RESCIND handler can not start to
			 * run beक्रमe the OFFER handler finishes.
			 */
			schedule_work(&ctx->work);
			अवरोध;

		हाल CHANNELMSG_OFFERCHANNEL:
			/*
			 * The host sends the offer message of a given channel
			 * beक्रमe sending the rescind message of the same
			 * channel.  These messages are sent to the guest's
			 * connect CPU; the guest then starts processing them
			 * in the tasklet handler on this CPU:
			 *
			 * VMBUS_CONNECT_CPU
			 *
			 * [vmbus_on_msg_dpc()]
			 * atomic_inc()  // CHANNELMSG_OFFERCHANNEL
			 * queue_work()
			 * ...
			 * [vmbus_on_msg_dpc()]
			 * schedule_work()  // CHANNELMSG_RESCIND_CHANNELOFFER
			 *
			 * We rely on the memory-ordering properties of the
			 * queue_work() and schedule_work() primitives, which
			 * guarantee that the atomic increment will be visible
			 * to the CPUs which will execute the offer & rescind
			 * works by the समय these works will start execution.
			 */
			atomic_inc(&vmbus_connection.offer_in_progress);
			fallthrough;

		शेष:
			queue_work(vmbus_connection.work_queue, &ctx->work);
		पूर्ण
	पूर्ण अन्यथा
		entry->message_handler(hdr);

msg_handled:
	vmbus_संकेत_eom(msg, message_type);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * Fake RESCIND_CHANNEL messages to clean up hv_sock channels by क्रमce क्रम
 * hibernation, because hv_sock connections can not persist across hibernation.
 */
अटल व्योम vmbus_क्रमce_channel_rescinded(काष्ठा vmbus_channel *channel)
अणु
	काष्ठा onmessage_work_context *ctx;
	काष्ठा vmbus_channel_rescind_offer *rescind;

	WARN_ON(!is_hvsock_channel(channel));

	/*
	 * Allocation size is small and the allocation should really not fail,
	 * otherwise the state of the hv_sock connections ends up in limbo.
	 */
	ctx = kzalloc(माप(*ctx) + माप(*rescind),
		      GFP_KERNEL | __GFP_NOFAIL);

	/*
	 * So far, these are not really used by Linux. Just set them to the
	 * reasonable values conक्रमming to the definitions of the fields.
	 */
	ctx->msg.header.message_type = 1;
	ctx->msg.header.payload_size = माप(*rescind);

	/* These values are actually used by Linux. */
	rescind = (काष्ठा vmbus_channel_rescind_offer *)ctx->msg.payload;
	rescind->header.msgtype = CHANNELMSG_RESCIND_CHANNELOFFER;
	rescind->child_relid = channel->offermsg.child_relid;

	INIT_WORK(&ctx->work, vmbus_onmessage_work);

	queue_work(vmbus_connection.work_queue, &ctx->work);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/*
 * Schedule all channels with events pending
 */
अटल व्योम vmbus_chan_sched(काष्ठा hv_per_cpu_context *hv_cpu)
अणु
	अचिन्हित दीर्घ *recv_पूर्णांक_page;
	u32 maxbits, relid;

	अगर (vmbus_proto_version < VERSION_WIN8) अणु
		maxbits = MAX_NUM_CHANNELS_SUPPORTED;
		recv_पूर्णांक_page = vmbus_connection.recv_पूर्णांक_page;
	पूर्ण अन्यथा अणु
		/*
		 * When the host is win8 and beyond, the event page
		 * can be directly checked to get the id of the channel
		 * that has the पूर्णांकerrupt pending.
		 */
		व्योम *page_addr = hv_cpu->synic_event_page;
		जोड़ hv_synic_event_flags *event
			= (जोड़ hv_synic_event_flags *)page_addr +
						 VMBUS_MESSAGE_SINT;

		maxbits = HV_EVENT_FLAGS_COUNT;
		recv_पूर्णांक_page = event->flags;
	पूर्ण

	अगर (unlikely(!recv_पूर्णांक_page))
		वापस;

	क्रम_each_set_bit(relid, recv_पूर्णांक_page, maxbits) अणु
		व्योम (*callback_fn)(व्योम *context);
		काष्ठा vmbus_channel *channel;

		अगर (!sync_test_and_clear_bit(relid, recv_पूर्णांक_page))
			जारी;

		/* Special हाल - vmbus channel protocol msg */
		अगर (relid == 0)
			जारी;

		/*
		 * Pairs with the kमुक्त_rcu() in vmbus_chan_release().
		 * Guarantees that the channel data काष्ठाure करोesn't
		 * get मुक्तd जबतक the channel poपूर्णांकer below is being
		 * dereferenced.
		 */
		rcu_पढ़ो_lock();

		/* Find channel based on relid */
		channel = relid2channel(relid);
		अगर (channel == शून्य)
			जाओ sched_unlock_rcu;

		अगर (channel->rescind)
			जाओ sched_unlock_rcu;

		/*
		 * Make sure that the ring buffer data काष्ठाure करोesn't get
		 * मुक्तd जबतक we dereference the ring buffer poपूर्णांकer.  Test
		 * क्रम the channel's onchannel_callback being शून्य within a
		 * sched_lock critical section.  See also the अंतरभूत comments
		 * in vmbus_reset_channel_cb().
		 */
		spin_lock(&channel->sched_lock);

		callback_fn = channel->onchannel_callback;
		अगर (unlikely(callback_fn == शून्य))
			जाओ sched_unlock;

		trace_vmbus_chan_sched(channel);

		++channel->पूर्णांकerrupts;

		चयन (channel->callback_mode) अणु
		हाल HV_CALL_ISR:
			(*callback_fn)(channel->channel_callback_context);
			अवरोध;

		हाल HV_CALL_BATCHED:
			hv_begin_पढ़ो(&channel->inbound);
			fallthrough;
		हाल HV_CALL_सूचीECT:
			tasklet_schedule(&channel->callback_event);
		पूर्ण

sched_unlock:
		spin_unlock(&channel->sched_lock);
sched_unlock_rcu:
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम vmbus_isr(व्योम)
अणु
	काष्ठा hv_per_cpu_context *hv_cpu
		= this_cpu_ptr(hv_context.cpu_context);
	व्योम *page_addr = hv_cpu->synic_event_page;
	काष्ठा hv_message *msg;
	जोड़ hv_synic_event_flags *event;
	bool handled = false;

	अगर (unlikely(page_addr == शून्य))
		वापस;

	event = (जोड़ hv_synic_event_flags *)page_addr +
					 VMBUS_MESSAGE_SINT;
	/*
	 * Check क्रम events beक्रमe checking क्रम messages. This is the order
	 * in which events and messages are checked in Winकरोws guests on
	 * Hyper-V, and the Winकरोws team suggested we करो the same.
	 */

	अगर ((vmbus_proto_version == VERSION_WS2008) ||
		(vmbus_proto_version == VERSION_WIN7)) अणु

		/* Since we are a child, we only need to check bit 0 */
		अगर (sync_test_and_clear_bit(0, event->flags))
			handled = true;
	पूर्ण अन्यथा अणु
		/*
		 * Our host is win8 or above. The संकेतing mechanism
		 * has changed and we can directly look at the event page.
		 * If bit n is set then we have an पूर्णांकerrup on the channel
		 * whose id is n.
		 */
		handled = true;
	पूर्ण

	अगर (handled)
		vmbus_chan_sched(hv_cpu);

	page_addr = hv_cpu->synic_message_page;
	msg = (काष्ठा hv_message *)page_addr + VMBUS_MESSAGE_SINT;

	/* Check अगर there are actual msgs to be processed */
	अगर (msg->header.message_type != HVMSG_NONE) अणु
		अगर (msg->header.message_type == HVMSG_TIMER_EXPIRED) अणु
			hv_sसमयr0_isr();
			vmbus_संकेत_eom(msg, HVMSG_TIMER_EXPIRED);
		पूर्ण अन्यथा
			tasklet_schedule(&hv_cpu->msg_dpc);
	पूर्ण

	add_पूर्णांकerrupt_अक्रमomness(vmbus_पूर्णांकerrupt, 0);
पूर्ण

अटल irqवापस_t vmbus_percpu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	vmbus_isr();
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Callback from kmsg_dump. Grab as much as possible from the end of the kmsg
 * buffer and call पूर्णांकo Hyper-V to transfer the data.
 */
अटल व्योम hv_kmsg_dump(काष्ठा kmsg_dumper *dumper,
			 क्रमागत kmsg_dump_reason reason)
अणु
	काष्ठा kmsg_dump_iter iter;
	माप_प्रकार bytes_written;

	/* We are only पूर्णांकerested in panics. */
	अगर ((reason != KMSG_DUMP_PANIC) || (!sysctl_record_panic_msg))
		वापस;

	/*
	 * Write dump contents to the page. No need to synchronize; panic should
	 * be single-thपढ़ोed.
	 */
	kmsg_dump_शुरुआत(&iter);
	kmsg_dump_get_buffer(&iter, false, hv_panic_page, HV_HYP_PAGE_SIZE,
			     &bytes_written);
	अगर (!bytes_written)
		वापस;
	/*
	 * P3 to contain the physical address of the panic page & P4 to
	 * contain the size of the panic data in that page. Rest of the
	 * रेजिस्टरs are no-op when the NOTIFY_MSG flag is set.
	 */
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_P0, 0);
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_P1, 0);
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_P2, 0);
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_P3, virt_to_phys(hv_panic_page));
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_P4, bytes_written);

	/*
	 * Let Hyper-V know there is crash data available aदीर्घ with
	 * the panic message.
	 */
	hv_set_रेजिस्टर(HV_REGISTER_CRASH_CTL,
	       (HV_CRASH_CTL_CRASH_NOTIFY | HV_CRASH_CTL_CRASH_NOTIFY_MSG));
पूर्ण

अटल काष्ठा kmsg_dumper hv_kmsg_dumper = अणु
	.dump = hv_kmsg_dump,
पूर्ण;

अटल व्योम hv_kmsg_dump_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret;

	hv_panic_page = hv_alloc_hyperv_zeroed_page();
	अगर (!hv_panic_page) अणु
		pr_err("Hyper-V: panic message page memory allocation failed\n");
		वापस;
	पूर्ण

	ret = kmsg_dump_रेजिस्टर(&hv_kmsg_dumper);
	अगर (ret) अणु
		pr_err("Hyper-V: kmsg dump register error 0x%x\n", ret);
		hv_मुक्त_hyperv_page((अचिन्हित दीर्घ)hv_panic_page);
		hv_panic_page = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा ctl_table_header *hv_ctl_table_hdr;

/*
 * sysctl option to allow the user to control whether kmsg data should be
 * reported to Hyper-V on panic.
 */
अटल काष्ठा ctl_table hv_ctl_table[] = अणु
	अणु
		.procname       = "hyperv_record_panic_msg",
		.data           = &sysctl_record_panic_msg,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table hv_root_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= hv_ctl_table
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * vmbus_bus_init -Main vmbus driver initialization routine.
 *
 * Here, we
 *	- initialize the vmbus driver context
 *	- invoke the vmbus hv मुख्य init routine
 *	- retrieve the channel offers
 */
अटल पूर्णांक vmbus_bus_init(व्योम)
अणु
	पूर्णांक ret;

	ret = hv_init();
	अगर (ret != 0) अणु
		pr_err("Unable to initialize the hypervisor - 0x%x\n", ret);
		वापस ret;
	पूर्ण

	ret = bus_रेजिस्टर(&hv_bus);
	अगर (ret)
		वापस ret;

	/*
	 * VMbus पूर्णांकerrupts are best modeled as per-cpu पूर्णांकerrupts. If
	 * on an architecture with support क्रम per-cpu IRQs (e.g. ARM64),
	 * allocate a per-cpu IRQ using standard Linux kernel functionality.
	 * If not on such an architecture (e.g., x86/x64), then rely on
	 * code in the arch-specअगरic portion of the code tree to connect
	 * the VMbus पूर्णांकerrupt handler.
	 */

	अगर (vmbus_irq == -1) अणु
		hv_setup_vmbus_handler(vmbus_isr);
	पूर्ण अन्यथा अणु
		vmbus_evt = alloc_percpu(दीर्घ);
		ret = request_percpu_irq(vmbus_irq, vmbus_percpu_isr,
				"Hyper-V VMbus", vmbus_evt);
		अगर (ret) अणु
			pr_err("Can't request Hyper-V VMbus IRQ %d, Err %d",
					vmbus_irq, ret);
			मुक्त_percpu(vmbus_evt);
			जाओ err_setup;
		पूर्ण
	पूर्ण

	ret = hv_synic_alloc();
	अगर (ret)
		जाओ err_alloc;

	/*
	 * Initialize the per-cpu पूर्णांकerrupt state and sसमयr state.
	 * Then connect to the host.
	 */
	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "hyperv/vmbus:online",
				hv_synic_init, hv_synic_cleanup);
	अगर (ret < 0)
		जाओ err_cpuhp;
	hyperv_cpuhp_online = ret;

	ret = vmbus_connect();
	अगर (ret)
		जाओ err_connect;

	/*
	 * Only रेजिस्टर अगर the crash MSRs are available
	 */
	अगर (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE) अणु
		u64 hyperv_crash_ctl;
		/*
		 * Sysctl registration is not fatal, since by शेष
		 * reporting is enabled.
		 */
		hv_ctl_table_hdr = रेजिस्टर_sysctl_table(hv_root_table);
		अगर (!hv_ctl_table_hdr)
			pr_err("Hyper-V: sysctl table register error");

		/*
		 * Register क्रम panic kmsg callback only अगर the right
		 * capability is supported by the hypervisor.
		 */
		hyperv_crash_ctl = hv_get_रेजिस्टर(HV_REGISTER_CRASH_CTL);
		अगर (hyperv_crash_ctl & HV_CRASH_CTL_CRASH_NOTIFY_MSG)
			hv_kmsg_dump_रेजिस्टर();

		रेजिस्टर_die_notअगरier(&hyperv_die_block);
	पूर्ण

	/*
	 * Always रेजिस्टर the panic notअगरier because we need to unload
	 * the VMbus channel connection to prevent any VMbus
	 * activity after the VM panics.
	 */
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
			       &hyperv_panic_block);

	vmbus_request_offers();

	वापस 0;

err_connect:
	cpuhp_हटाओ_state(hyperv_cpuhp_online);
err_cpuhp:
	hv_synic_मुक्त();
err_alloc:
	अगर (vmbus_irq == -1) अणु
		hv_हटाओ_vmbus_handler();
	पूर्ण अन्यथा अणु
		मुक्त_percpu_irq(vmbus_irq, vmbus_evt);
		मुक्त_percpu(vmbus_evt);
	पूर्ण
err_setup:
	bus_unरेजिस्टर(&hv_bus);
	unरेजिस्टर_sysctl_table(hv_ctl_table_hdr);
	hv_ctl_table_hdr = शून्य;
	वापस ret;
पूर्ण

/**
 * __vmbus_child_driver_रेजिस्टर() - Register a vmbus's driver
 * @hv_driver: Poपूर्णांकer to driver काष्ठाure you want to रेजिस्टर
 * @owner: owner module of the drv
 * @mod_name: module name string
 *
 * Registers the given driver with Linux through the 'driver_register()' call
 * and sets up the hyper-v vmbus handling क्रम this driver.
 * It will वापस the state of the 'driver_register()' call.
 *
 */
पूर्णांक __vmbus_driver_रेजिस्टर(काष्ठा hv_driver *hv_driver, काष्ठा module *owner, स्थिर अक्षर *mod_name)
अणु
	पूर्णांक ret;

	pr_info("registering driver %s\n", hv_driver->name);

	ret = vmbus_exists();
	अगर (ret < 0)
		वापस ret;

	hv_driver->driver.name = hv_driver->name;
	hv_driver->driver.owner = owner;
	hv_driver->driver.mod_name = mod_name;
	hv_driver->driver.bus = &hv_bus;

	spin_lock_init(&hv_driver->dynids.lock);
	INIT_LIST_HEAD(&hv_driver->dynids.list);

	ret = driver_रेजिस्टर(&hv_driver->driver);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__vmbus_driver_रेजिस्टर);

/**
 * vmbus_driver_unरेजिस्टर() - Unरेजिस्टर a vmbus's driver
 * @hv_driver: Poपूर्णांकer to driver काष्ठाure you want to
 *             un-रेजिस्टर
 *
 * Un-रेजिस्टर the given driver that was previous रेजिस्टरed with a call to
 * vmbus_driver_रेजिस्टर()
 */
व्योम vmbus_driver_unरेजिस्टर(काष्ठा hv_driver *hv_driver)
अणु
	pr_info("unregistering driver %s\n", hv_driver->name);

	अगर (!vmbus_exists()) अणु
		driver_unरेजिस्टर(&hv_driver->driver);
		vmbus_मुक्त_dynids(hv_driver);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_driver_unरेजिस्टर);


/*
 * Called when last reference to channel is gone.
 */
अटल व्योम vmbus_chan_release(काष्ठा kobject *kobj)
अणु
	काष्ठा vmbus_channel *channel
		= container_of(kobj, काष्ठा vmbus_channel, kobj);

	kमुक्त_rcu(channel, rcu);
पूर्ण

काष्ठा vmbus_chan_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा vmbus_channel *chan, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा vmbus_channel *chan,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;
#घोषणा VMBUS_CHAN_ATTR(_name, _mode, _show, _store) \
	काष्ठा vmbus_chan_attribute chan_attr_##_name \
		= __ATTR(_name, _mode, _show, _store)
#घोषणा VMBUS_CHAN_ATTR_RW(_name) \
	काष्ठा vmbus_chan_attribute chan_attr_##_name = __ATTR_RW(_name)
#घोषणा VMBUS_CHAN_ATTR_RO(_name) \
	काष्ठा vmbus_chan_attribute chan_attr_##_name = __ATTR_RO(_name)
#घोषणा VMBUS_CHAN_ATTR_WO(_name) \
	काष्ठा vmbus_chan_attribute chan_attr_##_name = __ATTR_WO(_name)

अटल sमाप_प्रकार vmbus_chan_attr_show(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा vmbus_chan_attribute *attribute
		= container_of(attr, काष्ठा vmbus_chan_attribute, attr);
	काष्ठा vmbus_channel *chan
		= container_of(kobj, काष्ठा vmbus_channel, kobj);

	अगर (!attribute->show)
		वापस -EIO;

	वापस attribute->show(chan, buf);
पूर्ण

अटल sमाप_प्रकार vmbus_chan_attr_store(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, स्थिर अक्षर *buf,
				     माप_प्रकार count)
अणु
	स्थिर काष्ठा vmbus_chan_attribute *attribute
		= container_of(attr, काष्ठा vmbus_chan_attribute, attr);
	काष्ठा vmbus_channel *chan
		= container_of(kobj, काष्ठा vmbus_channel, kobj);

	अगर (!attribute->store)
		वापस -EIO;

	वापस attribute->store(chan, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops vmbus_chan_sysfs_ops = अणु
	.show = vmbus_chan_attr_show,
	.store = vmbus_chan_attr_store,
पूर्ण;

अटल sमाप_प्रकार out_mask_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->outbound;
	sमाप_प्रकार ret;

	mutex_lock(&rbi->ring_buffer_mutex);
	अगर (!rbi->ring_buffer) अणु
		mutex_unlock(&rbi->ring_buffer_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = प्र_लिखो(buf, "%u\n", rbi->ring_buffer->पूर्णांकerrupt_mask);
	mutex_unlock(&rbi->ring_buffer_mutex);
	वापस ret;
पूर्ण
अटल VMBUS_CHAN_ATTR_RO(out_mask);

अटल sमाप_प्रकार in_mask_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;
	sमाप_प्रकार ret;

	mutex_lock(&rbi->ring_buffer_mutex);
	अगर (!rbi->ring_buffer) अणु
		mutex_unlock(&rbi->ring_buffer_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = प्र_लिखो(buf, "%u\n", rbi->ring_buffer->पूर्णांकerrupt_mask);
	mutex_unlock(&rbi->ring_buffer_mutex);
	वापस ret;
पूर्ण
अटल VMBUS_CHAN_ATTR_RO(in_mask);

अटल sमाप_प्रकार पढ़ो_avail_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->inbound;
	sमाप_प्रकार ret;

	mutex_lock(&rbi->ring_buffer_mutex);
	अगर (!rbi->ring_buffer) अणु
		mutex_unlock(&rbi->ring_buffer_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = प्र_लिखो(buf, "%u\n", hv_get_bytes_to_पढ़ो(rbi));
	mutex_unlock(&rbi->ring_buffer_mutex);
	वापस ret;
पूर्ण
अटल VMBUS_CHAN_ATTR_RO(पढ़ो_avail);

अटल sमाप_प्रकार ग_लिखो_avail_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	काष्ठा hv_ring_buffer_info *rbi = &channel->outbound;
	sमाप_प्रकार ret;

	mutex_lock(&rbi->ring_buffer_mutex);
	अगर (!rbi->ring_buffer) अणु
		mutex_unlock(&rbi->ring_buffer_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = प्र_लिखो(buf, "%u\n", hv_get_bytes_to_ग_लिखो(rbi));
	mutex_unlock(&rbi->ring_buffer_mutex);
	वापस ret;
पूर्ण
अटल VMBUS_CHAN_ATTR_RO(ग_लिखो_avail);

अटल sमाप_प्रकार target_cpu_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", channel->target_cpu);
पूर्ण
अटल sमाप_प्रकार target_cpu_store(काष्ठा vmbus_channel *channel,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u32 target_cpu, origin_cpu;
	sमाप_प्रकार ret = count;

	अगर (vmbus_proto_version < VERSION_WIN10_V4_1)
		वापस -EIO;

	अगर (माला_पूछो(buf, "%uu", &target_cpu) != 1)
		वापस -EIO;

	/* Validate target_cpu क्रम the cpumask_test_cpu() operation below. */
	अगर (target_cpu >= nr_cpumask_bits)
		वापस -EINVAL;

	/* No CPUs should come up or करोwn during this. */
	cpus_पढ़ो_lock();

	अगर (!cpu_online(target_cpu)) अणु
		cpus_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	/*
	 * Synchronizes target_cpu_store() and channel closure:
	 *
	 * अणु Initially: state = CHANNEL_OPENED पूर्ण
	 *
	 * CPU1				CPU2
	 *
	 * [target_cpu_store()]		[vmbus_disconnect_ring()]
	 *
	 * LOCK channel_mutex		LOCK channel_mutex
	 * LOAD r1 = state		LOAD r2 = state
	 * IF (r1 == CHANNEL_OPENED)	IF (r2 == CHANNEL_OPENED)
	 *   SEND MODIFYCHANNEL		  STORE state = CHANNEL_OPEN
	 *   [...]			  SEND CLOSECHANNEL
	 * UNLOCK channel_mutex		UNLOCK channel_mutex
	 *
	 * Forbids: r1 == r2 == CHANNEL_OPENED (i.e., CPU1's LOCK precedes
	 * 		CPU2's LOCK) && CPU2's SEND precedes CPU1's SEND
	 *
	 * Note.  The host processes the channel messages "sequentially", in
	 * the order in which they are received on a per-partition basis.
	 */
	mutex_lock(&vmbus_connection.channel_mutex);

	/*
	 * Hyper-V will ignore MODIFYCHANNEL messages क्रम "non-open" channels;
	 * aव्योम sending the message and fail here क्रम such channels.
	 */
	अगर (channel->state != CHANNEL_OPENED_STATE) अणु
		ret = -EIO;
		जाओ cpu_store_unlock;
	पूर्ण

	origin_cpu = channel->target_cpu;
	अगर (target_cpu == origin_cpu)
		जाओ cpu_store_unlock;

	अगर (vmbus_send_modअगरychannel(channel,
				     hv_cpu_number_to_vp_number(target_cpu))) अणु
		ret = -EIO;
		जाओ cpu_store_unlock;
	पूर्ण

	/*
	 * For version beक्रमe VERSION_WIN10_V5_3, the following warning holds:
	 *
	 * Warning.  At this poपूर्णांक, there is *no* guarantee that the host will
	 * have successfully processed the vmbus_send_modअगरychannel() request.
	 * See the header comment of vmbus_send_modअगरychannel() क्रम more info.
	 *
	 * Lags in the processing of the above vmbus_send_modअगरychannel() can
	 * result in missed पूर्णांकerrupts अगर the "old" target CPU is taken offline
	 * beक्रमe Hyper-V starts sending पूर्णांकerrupts to the "new" target CPU.
	 * But apart from this offlining scenario, the code tolerates such
	 * lags.  It will function correctly even अगर a channel पूर्णांकerrupt comes
	 * in on a CPU that is dअगरferent from the channel target_cpu value.
	 */

	channel->target_cpu = target_cpu;

	/* See init_vp_index(). */
	अगर (hv_is_perf_channel(channel))
		hv_update_alloced_cpus(origin_cpu, target_cpu);

	/* Currently set only क्रम storvsc channels. */
	अगर (channel->change_target_cpu_callback) अणु
		(*channel->change_target_cpu_callback)(channel,
				origin_cpu, target_cpu);
	पूर्ण

cpu_store_unlock:
	mutex_unlock(&vmbus_connection.channel_mutex);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण
अटल VMBUS_CHAN_ATTR(cpu, 0644, target_cpu_show, target_cpu_store);

अटल sमाप_प्रकार channel_pending_show(काष्ठा vmbus_channel *channel,
				    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n",
		       channel_pending(channel,
				       vmbus_connection.monitor_pages[1]));
पूर्ण
अटल VMBUS_CHAN_ATTR(pending, 0444, channel_pending_show, शून्य);

अटल sमाप_प्रकार channel_latency_show(काष्ठा vmbus_channel *channel,
				    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n",
		       channel_latency(channel,
				       vmbus_connection.monitor_pages[1]));
पूर्ण
अटल VMBUS_CHAN_ATTR(latency, 0444, channel_latency_show, शून्य);

अटल sमाप_प्रकार channel_पूर्णांकerrupts_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", channel->पूर्णांकerrupts);
पूर्ण
अटल VMBUS_CHAN_ATTR(पूर्णांकerrupts, 0444, channel_पूर्णांकerrupts_show, शून्य);

अटल sमाप_प्रकार channel_events_show(काष्ठा vmbus_channel *channel, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", channel->sig_events);
पूर्ण
अटल VMBUS_CHAN_ATTR(events, 0444, channel_events_show, शून्य);

अटल sमाप_प्रकार channel_पूर्णांकr_in_full_show(काष्ठा vmbus_channel *channel,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)channel->पूर्णांकr_in_full);
पूर्ण
अटल VMBUS_CHAN_ATTR(पूर्णांकr_in_full, 0444, channel_पूर्णांकr_in_full_show, शून्य);

अटल sमाप_प्रकार channel_पूर्णांकr_out_empty_show(काष्ठा vmbus_channel *channel,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)channel->पूर्णांकr_out_empty);
पूर्ण
अटल VMBUS_CHAN_ATTR(पूर्णांकr_out_empty, 0444, channel_पूर्णांकr_out_empty_show, शून्य);

अटल sमाप_प्रकार channel_out_full_first_show(काष्ठा vmbus_channel *channel,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)channel->out_full_first);
पूर्ण
अटल VMBUS_CHAN_ATTR(out_full_first, 0444, channel_out_full_first_show, शून्य);

अटल sमाप_प्रकार channel_out_full_total_show(काष्ठा vmbus_channel *channel,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)channel->out_full_total);
पूर्ण
अटल VMBUS_CHAN_ATTR(out_full_total, 0444, channel_out_full_total_show, शून्य);

अटल sमाप_प्रकार subchannel_monitor_id_show(काष्ठा vmbus_channel *channel,
					  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", channel->offermsg.monitorid);
पूर्ण
अटल VMBUS_CHAN_ATTR(monitor_id, 0444, subchannel_monitor_id_show, शून्य);

अटल sमाप_प्रकार subchannel_id_show(काष्ठा vmbus_channel *channel,
				  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n",
		       channel->offermsg.offer.sub_channel_index);
पूर्ण
अटल VMBUS_CHAN_ATTR_RO(subchannel_id);

अटल काष्ठा attribute *vmbus_chan_attrs[] = अणु
	&chan_attr_out_mask.attr,
	&chan_attr_in_mask.attr,
	&chan_attr_पढ़ो_avail.attr,
	&chan_attr_ग_लिखो_avail.attr,
	&chan_attr_cpu.attr,
	&chan_attr_pending.attr,
	&chan_attr_latency.attr,
	&chan_attr_पूर्णांकerrupts.attr,
	&chan_attr_events.attr,
	&chan_attr_पूर्णांकr_in_full.attr,
	&chan_attr_पूर्णांकr_out_empty.attr,
	&chan_attr_out_full_first.attr,
	&chan_attr_out_full_total.attr,
	&chan_attr_monitor_id.attr,
	&chan_attr_subchannel_id.attr,
	शून्य
पूर्ण;

/*
 * Channel-level attribute_group callback function. Returns the permission क्रम
 * each attribute, and वापसs 0 अगर an attribute is not visible.
 */
अटल umode_t vmbus_chan_attr_is_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक idx)
अणु
	स्थिर काष्ठा vmbus_channel *channel =
		container_of(kobj, काष्ठा vmbus_channel, kobj);

	/* Hide the monitor attributes अगर the monitor mechanism is not used. */
	अगर (!channel->offermsg.monitor_allocated &&
	    (attr == &chan_attr_pending.attr ||
	     attr == &chan_attr_latency.attr ||
	     attr == &chan_attr_monitor_id.attr))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute_group vmbus_chan_group = अणु
	.attrs = vmbus_chan_attrs,
	.is_visible = vmbus_chan_attr_is_visible
पूर्ण;

अटल काष्ठा kobj_type vmbus_chan_ktype = अणु
	.sysfs_ops = &vmbus_chan_sysfs_ops,
	.release = vmbus_chan_release,
पूर्ण;

/*
 * vmbus_add_channel_kobj - setup a sub-directory under device/channels
 */
पूर्णांक vmbus_add_channel_kobj(काष्ठा hv_device *dev, काष्ठा vmbus_channel *channel)
अणु
	स्थिर काष्ठा device *device = &dev->device;
	काष्ठा kobject *kobj = &channel->kobj;
	u32 relid = channel->offermsg.child_relid;
	पूर्णांक ret;

	kobj->kset = dev->channels_kset;
	ret = kobject_init_and_add(kobj, &vmbus_chan_ktype, शून्य,
				   "%u", relid);
	अगर (ret)
		वापस ret;

	ret = sysfs_create_group(kobj, &vmbus_chan_group);

	अगर (ret) अणु
		/*
		 * The calling functions' error handling paths will cleanup the
		 * empty channel directory.
		 */
		dev_err(device, "Unable to set up channel sysfs files\n");
		वापस ret;
	पूर्ण

	kobject_uevent(kobj, KOBJ_ADD);

	वापस 0;
पूर्ण

/*
 * vmbus_हटाओ_channel_attr_group - हटाओ the channel's attribute group
 */
व्योम vmbus_हटाओ_channel_attr_group(काष्ठा vmbus_channel *channel)
अणु
	sysfs_हटाओ_group(&channel->kobj, &vmbus_chan_group);
पूर्ण

/*
 * vmbus_device_create - Creates and रेजिस्टरs a new child device
 * on the vmbus.
 */
काष्ठा hv_device *vmbus_device_create(स्थिर guid_t *type,
				      स्थिर guid_t *instance,
				      काष्ठा vmbus_channel *channel)
अणु
	काष्ठा hv_device *child_device_obj;

	child_device_obj = kzalloc(माप(काष्ठा hv_device), GFP_KERNEL);
	अगर (!child_device_obj) अणु
		pr_err("Unable to allocate device object for child device\n");
		वापस शून्य;
	पूर्ण

	child_device_obj->channel = channel;
	guid_copy(&child_device_obj->dev_type, type);
	guid_copy(&child_device_obj->dev_instance, instance);
	child_device_obj->venकरोr_id = 0x1414; /* MSFT venकरोr ID */

	वापस child_device_obj;
पूर्ण

/*
 * vmbus_device_रेजिस्टर - Register the child device
 */
पूर्णांक vmbus_device_रेजिस्टर(काष्ठा hv_device *child_device_obj)
अणु
	काष्ठा kobject *kobj = &child_device_obj->device.kobj;
	पूर्णांक ret;

	dev_set_name(&child_device_obj->device, "%pUl",
		     &child_device_obj->channel->offermsg.offer.अगर_instance);

	child_device_obj->device.bus = &hv_bus;
	child_device_obj->device.parent = &hv_acpi_dev->dev;
	child_device_obj->device.release = vmbus_device_release;

	/*
	 * Register with the LDM. This will kick off the driver/device
	 * binding...which will eventually call vmbus_match() and vmbus_probe()
	 */
	ret = device_रेजिस्टर(&child_device_obj->device);
	अगर (ret) अणु
		pr_err("Unable to register child device\n");
		वापस ret;
	पूर्ण

	child_device_obj->channels_kset = kset_create_and_add("channels",
							      शून्य, kobj);
	अगर (!child_device_obj->channels_kset) अणु
		ret = -ENOMEM;
		जाओ err_dev_unरेजिस्टर;
	पूर्ण

	ret = vmbus_add_channel_kobj(child_device_obj,
				     child_device_obj->channel);
	अगर (ret) अणु
		pr_err("Unable to register primary channeln");
		जाओ err_kset_unरेजिस्टर;
	पूर्ण
	hv_debug_add_dev_dir(child_device_obj);

	वापस 0;

err_kset_unरेजिस्टर:
	kset_unरेजिस्टर(child_device_obj->channels_kset);

err_dev_unरेजिस्टर:
	device_unरेजिस्टर(&child_device_obj->device);
	वापस ret;
पूर्ण

/*
 * vmbus_device_unरेजिस्टर - Remove the specअगरied child device
 * from the vmbus.
 */
व्योम vmbus_device_unरेजिस्टर(काष्ठा hv_device *device_obj)
अणु
	pr_debug("child device %s unregistered\n",
		dev_name(&device_obj->device));

	kset_unरेजिस्टर(device_obj->channels_kset);

	/*
	 * Kick off the process of unरेजिस्टरing the device.
	 * This will call vmbus_हटाओ() and eventually vmbus_device_release()
	 */
	device_unरेजिस्टर(&device_obj->device);
पूर्ण


/*
 * VMBUS is an acpi क्रमागतerated device. Get the inक्रमmation we
 * need from DSDT.
 */
#घोषणा VTPM_BASE_ADDRESS 0xfed40000
अटल acpi_status vmbus_walk_resources(काष्ठा acpi_resource *res, व्योम *ctx)
अणु
	resource_माप_प्रकार start = 0;
	resource_माप_प्रकार end = 0;
	काष्ठा resource *new_res;
	काष्ठा resource **old_res = &hyperv_mmio;
	काष्ठा resource **prev_res = शून्य;
	काष्ठा resource r;

	चयन (res->type) अणु

	/*
	 * "Address" descriptors are क्रम bus winकरोws. Ignore
	 * "memory" descriptors, which are क्रम रेजिस्टरs on
	 * devices.
	 */
	हाल ACPI_RESOURCE_TYPE_ADDRESS32:
		start = res->data.address32.address.minimum;
		end = res->data.address32.address.maximum;
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_ADDRESS64:
		start = res->data.address64.address.minimum;
		end = res->data.address64.address.maximum;
		अवरोध;

	/*
	 * The IRQ inक्रमmation is needed only on ARM64, which Hyper-V
	 * sets up in the extended क्रमmat. IRQ inक्रमmation is present
	 * on x86/x64 in the non-extended क्रमmat but it is not used by
	 * Linux. So करोn't bother checking क्रम the non-extended क्रमmat.
	 */
	हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
		अगर (!acpi_dev_resource_पूर्णांकerrupt(res, 0, &r)) अणु
			pr_err("Unable to parse Hyper-V ACPI interrupt\n");
			वापस AE_ERROR;
		पूर्ण
		/* ARM64 INTID क्रम VMbus */
		vmbus_पूर्णांकerrupt = res->data.extended_irq.पूर्णांकerrupts[0];
		/* Linux IRQ number */
		vmbus_irq = r.start;
		वापस AE_OK;

	शेष:
		/* Unused resource type */
		वापस AE_OK;

	पूर्ण
	/*
	 * Ignore ranges that are below 1MB, as they're not
	 * necessary or useful here.
	 */
	अगर (end < 0x100000)
		वापस AE_OK;

	new_res = kzalloc(माप(*new_res), GFP_ATOMIC);
	अगर (!new_res)
		वापस AE_NO_MEMORY;

	/* If this range overlaps the भव TPM, truncate it. */
	अगर (end > VTPM_BASE_ADDRESS && start < VTPM_BASE_ADDRESS)
		end = VTPM_BASE_ADDRESS;

	new_res->name = "hyperv mmio";
	new_res->flags = IORESOURCE_MEM;
	new_res->start = start;
	new_res->end = end;

	/*
	 * If two ranges are adjacent, merge them.
	 */
	करो अणु
		अगर (!*old_res) अणु
			*old_res = new_res;
			अवरोध;
		पूर्ण

		अगर (((*old_res)->end + 1) == new_res->start) अणु
			(*old_res)->end = new_res->end;
			kमुक्त(new_res);
			अवरोध;
		पूर्ण

		अगर ((*old_res)->start == new_res->end + 1) अणु
			(*old_res)->start = new_res->start;
			kमुक्त(new_res);
			अवरोध;
		पूर्ण

		अगर ((*old_res)->start > new_res->end) अणु
			new_res->sibling = *old_res;
			अगर (prev_res)
				(*prev_res)->sibling = new_res;
			*old_res = new_res;
			अवरोध;
		पूर्ण

		prev_res = old_res;
		old_res = &(*old_res)->sibling;

	पूर्ण जबतक (1);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक vmbus_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा resource *cur_res;
	काष्ठा resource *next_res;

	अगर (hyperv_mmio) अणु
		अगर (fb_mmio) अणु
			__release_region(hyperv_mmio, fb_mmio->start,
					 resource_size(fb_mmio));
			fb_mmio = शून्य;
		पूर्ण

		क्रम (cur_res = hyperv_mmio; cur_res; cur_res = next_res) अणु
			next_res = cur_res->sibling;
			kमुक्त(cur_res);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vmbus_reserve_fb(व्योम)
अणु
	पूर्णांक size;
	/*
	 * Make a claim क्रम the frame buffer in the resource tree under the
	 * first node, which will be the one below 4GB.  The length seems to
	 * be underreported, particularly in a Generation 1 VM.  So start out
	 * reserving a larger area and make it smaller until it succeeds.
	 */

	अगर (screen_info.lfb_base) अणु
		अगर (efi_enabled(EFI_BOOT))
			size = max_t(__u32, screen_info.lfb_size, 0x800000);
		अन्यथा
			size = max_t(__u32, screen_info.lfb_size, 0x4000000);

		क्रम (; !fb_mmio && (size >= 0x100000); size >>= 1) अणु
			fb_mmio = __request_region(hyperv_mmio,
						   screen_info.lfb_base, size,
						   fb_mmio_name, 0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmbus_allocate_mmio() - Pick a memory-mapped I/O range.
 * @new:		If successful, supplied a poपूर्णांकer to the
 *			allocated MMIO space.
 * @device_obj:		Identअगरies the caller
 * @min:		Minimum guest physical address of the
 *			allocation
 * @max:		Maximum guest physical address
 * @size:		Size of the range to be allocated
 * @align:		Alignment of the range to be allocated
 * @fb_overlap_ok:	Whether this allocation can be allowed
 *			to overlap the video frame buffer.
 *
 * This function walks the resources granted to VMBus by the
 * _CRS object in the ACPI namespace underneath the parent
 * "bridge" whether that's a root PCI bus in the Generation 1
 * हाल or a Module Device in the Generation 2 हाल.  It then
 * attempts to allocate from the global MMIO pool in a way that
 * matches the स्थिरraपूर्णांकs supplied in these parameters and by
 * that _CRS.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक vmbus_allocate_mmio(काष्ठा resource **new, काष्ठा hv_device *device_obj,
			resource_माप_प्रकार min, resource_माप_प्रकार max,
			resource_माप_प्रकार size, resource_माप_प्रकार align,
			bool fb_overlap_ok)
अणु
	काष्ठा resource *iter, *shaकरोw;
	resource_माप_प्रकार range_min, range_max, start;
	स्थिर अक्षर *dev_n = dev_name(&device_obj->device);
	पूर्णांक retval;

	retval = -ENXIO;
	mutex_lock(&hyperv_mmio_lock);

	/*
	 * If overlaps with frame buffers are allowed, then first attempt to
	 * make the allocation from within the reserved region.  Because it
	 * is alपढ़ोy reserved, no shaकरोw allocation is necessary.
	 */
	अगर (fb_overlap_ok && fb_mmio && !(min > fb_mmio->end) &&
	    !(max < fb_mmio->start)) अणु

		range_min = fb_mmio->start;
		range_max = fb_mmio->end;
		start = (range_min + align - 1) & ~(align - 1);
		क्रम (; start + size - 1 <= range_max; start += align) अणु
			*new = request_mem_region_exclusive(start, size, dev_n);
			अगर (*new) अणु
				retval = 0;
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (iter = hyperv_mmio; iter; iter = iter->sibling) अणु
		अगर ((iter->start >= max) || (iter->end <= min))
			जारी;

		range_min = iter->start;
		range_max = iter->end;
		start = (range_min + align - 1) & ~(align - 1);
		क्रम (; start + size - 1 <= range_max; start += align) अणु
			shaकरोw = __request_region(iter, start, size, शून्य,
						  IORESOURCE_BUSY);
			अगर (!shaकरोw)
				जारी;

			*new = request_mem_region_exclusive(start, size, dev_n);
			अगर (*new) अणु
				shaकरोw->name = (अक्षर *)*new;
				retval = 0;
				जाओ निकास;
			पूर्ण

			__release_region(iter, start, size);
		पूर्ण
	पूर्ण

निकास:
	mutex_unlock(&hyperv_mmio_lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(vmbus_allocate_mmio);

/**
 * vmbus_मुक्त_mmio() - Free a memory-mapped I/O range.
 * @start:		Base address of region to release.
 * @size:		Size of the range to be allocated
 *
 * This function releases anything requested by
 * vmbus_mmio_allocate().
 */
व्योम vmbus_मुक्त_mmio(resource_माप_प्रकार start, resource_माप_प्रकार size)
अणु
	काष्ठा resource *iter;

	mutex_lock(&hyperv_mmio_lock);
	क्रम (iter = hyperv_mmio; iter; iter = iter->sibling) अणु
		अगर ((iter->start >= start + size) || (iter->end <= start))
			जारी;

		__release_region(iter, start, size);
	पूर्ण
	release_mem_region(start, size);
	mutex_unlock(&hyperv_mmio_lock);

पूर्ण
EXPORT_SYMBOL_GPL(vmbus_मुक्त_mmio);

अटल पूर्णांक vmbus_acpi_add(काष्ठा acpi_device *device)
अणु
	acpi_status result;
	पूर्णांक ret_val = -ENODEV;
	काष्ठा acpi_device *ancestor;

	hv_acpi_dev = device;

	result = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
					vmbus_walk_resources, शून्य);

	अगर (ACPI_FAILURE(result))
		जाओ acpi_walk_err;
	/*
	 * Some ancestor of the vmbus acpi device (Gen1 or Gen2
	 * firmware) is the VMOD that has the mmio ranges. Get that.
	 */
	क्रम (ancestor = device->parent; ancestor; ancestor = ancestor->parent) अणु
		result = acpi_walk_resources(ancestor->handle, METHOD_NAME__CRS,
					     vmbus_walk_resources, शून्य);

		अगर (ACPI_FAILURE(result))
			जारी;
		अगर (hyperv_mmio) अणु
			vmbus_reserve_fb();
			अवरोध;
		पूर्ण
	पूर्ण
	ret_val = 0;

acpi_walk_err:
	complete(&probe_event);
	अगर (ret_val)
		vmbus_acpi_हटाओ(device);
	वापस ret_val;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vmbus_bus_suspend(काष्ठा device *dev)
अणु
	काष्ठा vmbus_channel *channel, *sc;

	जबतक (atomic_पढ़ो(&vmbus_connection.offer_in_progress) != 0) अणु
		/*
		 * We रुको here until the completion of any channel
		 * offers that are currently in progress.
		 */
		usleep_range(1000, 2000);
	पूर्ण

	mutex_lock(&vmbus_connection.channel_mutex);
	list_क्रम_each_entry(channel, &vmbus_connection.chn_list, listentry) अणु
		अगर (!is_hvsock_channel(channel))
			जारी;

		vmbus_क्रमce_channel_rescinded(channel);
	पूर्ण
	mutex_unlock(&vmbus_connection.channel_mutex);

	/*
	 * Wait until all the sub-channels and hv_sock channels have been
	 * cleaned up. Sub-channels should be destroyed upon suspend, otherwise
	 * they would conflict with the new sub-channels that will be created
	 * in the resume path. hv_sock channels should also be destroyed, but
	 * a hv_sock channel of an established hv_sock connection can not be
	 * really destroyed since it may still be referenced by the userspace
	 * application, so we just क्रमce the hv_sock channel to be rescinded
	 * by vmbus_क्रमce_channel_rescinded(), and the userspace application
	 * will thoroughly destroy the channel after hibernation.
	 *
	 * Note: the counter nr_chan_बंद_on_suspend may never go above 0 अगर
	 * the VM has no sub-channel and hv_sock channel, e.g. a 1-vCPU VM.
	 */
	अगर (atomic_पढ़ो(&vmbus_connection.nr_chan_बंद_on_suspend) > 0)
		रुको_क्रम_completion(&vmbus_connection.पढ़ोy_क्रम_suspend_event);

	अगर (atomic_पढ़ो(&vmbus_connection.nr_chan_fixup_on_resume) != 0) अणु
		pr_err("Can not suspend due to a previous failed resuming\n");
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&vmbus_connection.channel_mutex);

	list_क्रम_each_entry(channel, &vmbus_connection.chn_list, listentry) अणु
		/*
		 * Remove the channel from the array of channels and invalidate
		 * the channel's relid.  Upon resume, vmbus_onoffer() will fix
		 * up the relid (and other fields, अगर necessary) and add the
		 * channel back to the array.
		 */
		vmbus_channel_unmap_relid(channel);
		channel->offermsg.child_relid = INVALID_RELID;

		अगर (is_hvsock_channel(channel)) अणु
			अगर (!channel->rescind) अणु
				pr_err("hv_sock channel not rescinded!\n");
				WARN_ON_ONCE(1);
			पूर्ण
			जारी;
		पूर्ण

		list_क्रम_each_entry(sc, &channel->sc_list, sc_list) अणु
			pr_err("Sub-channel not deleted!\n");
			WARN_ON_ONCE(1);
		पूर्ण

		atomic_inc(&vmbus_connection.nr_chan_fixup_on_resume);
	पूर्ण

	mutex_unlock(&vmbus_connection.channel_mutex);

	vmbus_initiate_unload(false);

	/* Reset the event क्रम the next resume. */
	reinit_completion(&vmbus_connection.पढ़ोy_क्रम_resume_event);

	वापस 0;
पूर्ण

अटल पूर्णांक vmbus_bus_resume(काष्ठा device *dev)
अणु
	काष्ठा vmbus_channel_msginfo *msginfo;
	माप_प्रकार msgsize;
	पूर्णांक ret;

	/*
	 * We only use the 'vmbus_proto_version', which was in use beक्रमe
	 * hibernation, to re-negotiate with the host.
	 */
	अगर (!vmbus_proto_version) अणु
		pr_err("Invalid proto version = 0x%x\n", vmbus_proto_version);
		वापस -EINVAL;
	पूर्ण

	msgsize = माप(*msginfo) +
		  माप(काष्ठा vmbus_channel_initiate_contact);

	msginfo = kzalloc(msgsize, GFP_KERNEL);

	अगर (msginfo == शून्य)
		वापस -ENOMEM;

	ret = vmbus_negotiate_version(msginfo, vmbus_proto_version);

	kमुक्त(msginfo);

	अगर (ret != 0)
		वापस ret;

	WARN_ON(atomic_पढ़ो(&vmbus_connection.nr_chan_fixup_on_resume) == 0);

	vmbus_request_offers();

	अगर (रुको_क्रम_completion_समयout(
		&vmbus_connection.पढ़ोy_क्रम_resume_event, 10 * HZ) == 0)
		pr_err("Some vmbus device is missing after suspending?\n");

	/* Reset the event क्रम the next suspend. */
	reinit_completion(&vmbus_connection.पढ़ोy_क्रम_suspend_event);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा vmbus_bus_suspend शून्य
#घोषणा vmbus_bus_resume शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा acpi_device_id vmbus_acpi_device_ids[] = अणु
	अणु"VMBUS", 0पूर्ण,
	अणु"VMBus", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, vmbus_acpi_device_ids);

/*
 * Note: we must use the "no_irq" ops, otherwise hibernation can not work with
 * PCI device assignment, because "pci_dev_pm_ops" uses the "noirq" ops: in
 * the resume path, the pci "noirq" restore op runs beक्रमe "non-noirq" op (see
 * resume_target_kernel() -> dpm_resume_start(), and hibernation_restore() ->
 * dpm_resume_end()). This means vmbus_bus_resume() and the pci-hyperv's
 * resume callback must also run via the "noirq" ops.
 *
 * Set suspend_noirq/resume_noirq to शून्य क्रम Suspend-to-Idle: see the comment
 * earlier in this file beक्रमe vmbus_pm.
 */

अटल स्थिर काष्ठा dev_pm_ops vmbus_bus_pm = अणु
	.suspend_noirq	= शून्य,
	.resume_noirq	= शून्य,
	.मुक्तze_noirq	= vmbus_bus_suspend,
	.thaw_noirq	= vmbus_bus_resume,
	.घातeroff_noirq	= vmbus_bus_suspend,
	.restore_noirq	= vmbus_bus_resume
पूर्ण;

अटल काष्ठा acpi_driver vmbus_acpi_driver = अणु
	.name = "vmbus",
	.ids = vmbus_acpi_device_ids,
	.ops = अणु
		.add = vmbus_acpi_add,
		.हटाओ = vmbus_acpi_हटाओ,
	पूर्ण,
	.drv.pm = &vmbus_bus_pm,
पूर्ण;

अटल व्योम hv_kexec_handler(व्योम)
अणु
	hv_sसमयr_global_cleanup();
	vmbus_initiate_unload(false);
	/* Make sure conn_state is set as hv_synic_cleanup checks क्रम it */
	mb();
	cpuhp_हटाओ_state(hyperv_cpuhp_online);
पूर्ण;

अटल व्योम hv_crash_handler(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu;

	vmbus_initiate_unload(true);
	/*
	 * In crash handler we can't schedule synic cleanup क्रम all CPUs,
	 * करोing the cleanup क्रम current CPU only. This should be sufficient
	 * क्रम kdump.
	 */
	cpu = smp_processor_id();
	hv_sसमयr_cleanup(cpu);
	hv_synic_disable_regs(cpu);
पूर्ण;

अटल पूर्णांक hv_synic_suspend(व्योम)
अणु
	/*
	 * When we reach here, all the non-boot CPUs have been offlined.
	 * If we're in a legacy configuration where sसमयr Direct Mode is
	 * not enabled, the sसमयrs on the non-boot CPUs have been unbound
	 * in hv_synic_cleanup() -> hv_sसमयr_legacy_cleanup() ->
	 * hv_sसमयr_cleanup() -> घड़ीevents_unbind_device().
	 *
	 * hv_synic_suspend() only runs on CPU0 with पूर्णांकerrupts disabled.
	 * Here we करो not call hv_sसमयr_legacy_cleanup() on CPU0 because:
	 * 1) it's unnecessary as पूर्णांकerrupts reमुख्य disabled between
	 * syscore_suspend() and syscore_resume(): see create_image() and
	 * resume_target_kernel()
	 * 2) the sसमयr on CPU0 is स्वतःmatically disabled later by
	 * syscore_suspend() -> समयkeeping_suspend() -> tick_suspend() -> ...
	 * -> घड़ीevents_shutकरोwn() -> ... -> hv_ce_shutकरोwn()
	 * 3) a warning would be triggered अगर we call
	 * घड़ीevents_unbind_device(), which may sleep, in an
	 * पूर्णांकerrupts-disabled context.
	 */

	hv_synic_disable_regs(0);

	वापस 0;
पूर्ण

अटल व्योम hv_synic_resume(व्योम)
अणु
	hv_synic_enable_regs(0);

	/*
	 * Note: we करोn't need to call hv_sसमयr_init(0), because the समयr
	 * on CPU0 is not unbound in hv_synic_suspend(), and the समयr is
	 * स्वतःmatically re-enabled in समयkeeping_resume().
	 */
पूर्ण

/* The callbacks run only on CPU0, with irqs_disabled. */
अटल काष्ठा syscore_ops hv_synic_syscore_ops = अणु
	.suspend = hv_synic_suspend,
	.resume = hv_synic_resume,
पूर्ण;

अटल पूर्णांक __init hv_acpi_init(व्योम)
अणु
	पूर्णांक ret, t;

	अगर (!hv_is_hyperv_initialized())
		वापस -ENODEV;

	अगर (hv_root_partition)
		वापस 0;

	init_completion(&probe_event);

	/*
	 * Get ACPI resources first.
	 */
	ret = acpi_bus_रेजिस्टर_driver(&vmbus_acpi_driver);

	अगर (ret)
		वापस ret;

	t = रुको_क्रम_completion_समयout(&probe_event, 5*HZ);
	अगर (t == 0) अणु
		ret = -ETIMEDOUT;
		जाओ cleanup;
	पूर्ण

	/*
	 * If we're on an architecture with a hardcoded hypervisor
	 * vector (i.e. x86/x64), override the VMbus पूर्णांकerrupt found
	 * in the ACPI tables. Ensure vmbus_irq is not set since the
	 * normal Linux IRQ mechanism is not used in this हाल.
	 */
#अगर_घोषित HYPERVISOR_CALLBACK_VECTOR
	vmbus_पूर्णांकerrupt = HYPERVISOR_CALLBACK_VECTOR;
	vmbus_irq = -1;
#पूर्ण_अगर

	hv_debug_init();

	ret = vmbus_bus_init();
	अगर (ret)
		जाओ cleanup;

	hv_setup_kexec_handler(hv_kexec_handler);
	hv_setup_crash_handler(hv_crash_handler);

	रेजिस्टर_syscore_ops(&hv_synic_syscore_ops);

	वापस 0;

cleanup:
	acpi_bus_unरेजिस्टर_driver(&vmbus_acpi_driver);
	hv_acpi_dev = शून्य;
	वापस ret;
पूर्ण

अटल व्योम __निकास vmbus_निकास(व्योम)
अणु
	पूर्णांक cpu;

	unरेजिस्टर_syscore_ops(&hv_synic_syscore_ops);

	hv_हटाओ_kexec_handler();
	hv_हटाओ_crash_handler();
	vmbus_connection.conn_state = DISCONNECTED;
	hv_sसमयr_global_cleanup();
	vmbus_disconnect();
	अगर (vmbus_irq == -1) अणु
		hv_हटाओ_vmbus_handler();
	पूर्ण अन्यथा अणु
		मुक्त_percpu_irq(vmbus_irq, vmbus_evt);
		मुक्त_percpu(vmbus_evt);
	पूर्ण
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा hv_per_cpu_context *hv_cpu
			= per_cpu_ptr(hv_context.cpu_context, cpu);

		tasklet_समाप्त(&hv_cpu->msg_dpc);
	पूर्ण
	hv_debug_rm_all_dir();

	vmbus_मुक्त_channels();
	kमुक्त(vmbus_connection.channels);

	अगर (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE) अणु
		kmsg_dump_unरेजिस्टर(&hv_kmsg_dumper);
		unरेजिस्टर_die_notअगरier(&hyperv_die_block);
		atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
						 &hyperv_panic_block);
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)hv_panic_page);
	unरेजिस्टर_sysctl_table(hv_ctl_table_hdr);
	hv_ctl_table_hdr = शून्य;
	bus_unरेजिस्टर(&hv_bus);

	cpuhp_हटाओ_state(hyperv_cpuhp_online);
	hv_synic_मुक्त();
	acpi_bus_unरेजिस्टर_driver(&vmbus_acpi_driver);
पूर्ण


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V VMBus Driver");

subsys_initcall(hv_acpi_init);
module_निकास(vmbus_निकास);
