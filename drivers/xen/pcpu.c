<शैली गुरु>
/******************************************************************************
 * pcpu.c
 * Management physical cpu in करोm0, get pcpu info and provide sys पूर्णांकerface
 *
 * Copyright (c) 2012 Intel Corporation
 * Author: Liu, Jinsong <jinsong.liu@पूर्णांकel.com>
 * Author: Jiang, Yunhong <yunhong.jiang@पूर्णांकel.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen_cpu: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/cpu.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/capability.h>

#समावेश <xen/xen.h>
#समावेश <xen/acpi.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>


/*
 * @cpu_id: Xen physical cpu logic number
 * @flags: Xen physical cpu status flag
 * - XEN_PCPU_FLAGS_ONLINE: cpu is online
 * - XEN_PCPU_FLAGS_INVALID: cpu is not present
 */
काष्ठा pcpu अणु
	काष्ठा list_head list;
	काष्ठा device dev;
	uपूर्णांक32_t cpu_id;
	uपूर्णांक32_t flags;
पूर्ण;

अटल काष्ठा bus_type xen_pcpu_subsys = अणु
	.name = "xen_cpu",
	.dev_name = "xen_cpu",
पूर्ण;

अटल DEFINE_MUTEX(xen_pcpu_lock);

अटल LIST_HEAD(xen_pcpus);

अटल पूर्णांक xen_pcpu_करोwn(uपूर्णांक32_t cpu_id)
अणु
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd			= XENPF_cpu_offline,
		.पूर्णांकerface_version	= XENPF_INTERFACE_VERSION,
		.u.cpu_ol.cpuid		= cpu_id,
	पूर्ण;

	वापस HYPERVISOR_platक्रमm_op(&op);
पूर्ण

अटल पूर्णांक xen_pcpu_up(uपूर्णांक32_t cpu_id)
अणु
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd			= XENPF_cpu_online,
		.पूर्णांकerface_version	= XENPF_INTERFACE_VERSION,
		.u.cpu_ol.cpuid		= cpu_id,
	पूर्ण;

	वापस HYPERVISOR_platक्रमm_op(&op);
पूर्ण

अटल sमाप_प्रकार show_online(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा pcpu *cpu = container_of(dev, काष्ठा pcpu, dev);

	वापस प्र_लिखो(buf, "%u\n", !!(cpu->flags & XEN_PCPU_FLAGS_ONLINE));
पूर्ण

अटल sमाप_प्रकार __ref store_online(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcpu *pcpu = container_of(dev, काष्ठा pcpu, dev);
	अचिन्हित दीर्घ दीर्घ val;
	sमाप_प्रकार ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (kम_से_अदीर्घl(buf, 0, &val) < 0)
		वापस -EINVAL;

	चयन (val) अणु
	हाल 0:
		ret = xen_pcpu_करोwn(pcpu->cpu_id);
		अवरोध;
	हाल 1:
		ret = xen_pcpu_up(pcpu->cpu_id);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret >= 0)
		ret = count;
	वापस ret;
पूर्ण
अटल DEVICE_ATTR(online, S_IRUGO | S_IWUSR, show_online, store_online);

अटल काष्ठा attribute *pcpu_dev_attrs[] = अणु
	&dev_attr_online.attr,
	शून्य
पूर्ण;

अटल umode_t pcpu_dev_is_visible(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	/*
	 * Xen never offline cpu0 due to several restrictions
	 * and assumptions. This basically करोesn't add a sys control
	 * to user, one cannot attempt to offline BSP.
	 */
	वापस dev->id ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group pcpu_dev_group = अणु
	.attrs = pcpu_dev_attrs,
	.is_visible = pcpu_dev_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pcpu_dev_groups[] = अणु
	&pcpu_dev_group,
	शून्य
पूर्ण;

अटल bool xen_pcpu_online(uपूर्णांक32_t flags)
अणु
	वापस !!(flags & XEN_PCPU_FLAGS_ONLINE);
पूर्ण

अटल व्योम pcpu_online_status(काष्ठा xenpf_pcpuinfo *info,
			       काष्ठा pcpu *pcpu)
अणु
	अगर (xen_pcpu_online(info->flags) &&
	   !xen_pcpu_online(pcpu->flags)) अणु
		/* the pcpu is onlined */
		pcpu->flags |= XEN_PCPU_FLAGS_ONLINE;
		kobject_uevent(&pcpu->dev.kobj, KOBJ_ONLINE);
	पूर्ण अन्यथा अगर (!xen_pcpu_online(info->flags) &&
		    xen_pcpu_online(pcpu->flags)) अणु
		/* The pcpu is offlined */
		pcpu->flags &= ~XEN_PCPU_FLAGS_ONLINE;
		kobject_uevent(&pcpu->dev.kobj, KOBJ_OFFLINE);
	पूर्ण
पूर्ण

अटल काष्ठा pcpu *get_pcpu(uपूर्णांक32_t cpu_id)
अणु
	काष्ठा pcpu *pcpu;

	list_क्रम_each_entry(pcpu, &xen_pcpus, list) अणु
		अगर (pcpu->cpu_id == cpu_id)
			वापस pcpu;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम pcpu_release(काष्ठा device *dev)
अणु
	काष्ठा pcpu *pcpu = container_of(dev, काष्ठा pcpu, dev);

	list_del(&pcpu->list);
	kमुक्त(pcpu);
पूर्ण

अटल व्योम unरेजिस्टर_and_हटाओ_pcpu(काष्ठा pcpu *pcpu)
अणु
	काष्ठा device *dev;

	अगर (!pcpu)
		वापस;

	dev = &pcpu->dev;
	/* pcpu हटाओ would be implicitly करोne */
	device_unरेजिस्टर(dev);
पूर्ण

अटल पूर्णांक रेजिस्टर_pcpu(काष्ठा pcpu *pcpu)
अणु
	काष्ठा device *dev;
	पूर्णांक err = -EINVAL;

	अगर (!pcpu)
		वापस err;

	dev = &pcpu->dev;
	dev->bus = &xen_pcpu_subsys;
	dev->id = pcpu->cpu_id;
	dev->release = pcpu_release;
	dev->groups = pcpu_dev_groups;

	err = device_रेजिस्टर(dev);
	अगर (err) अणु
		pcpu_release(dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pcpu *create_and_रेजिस्टर_pcpu(काष्ठा xenpf_pcpuinfo *info)
अणु
	काष्ठा pcpu *pcpu;
	पूर्णांक err;

	अगर (info->flags & XEN_PCPU_FLAGS_INVALID)
		वापस ERR_PTR(-ENODEV);

	pcpu = kzalloc(माप(काष्ठा pcpu), GFP_KERNEL);
	अगर (!pcpu)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&pcpu->list);
	pcpu->cpu_id = info->xen_cpuid;
	pcpu->flags = info->flags;

	/* Need hold on xen_pcpu_lock beक्रमe pcpu list manipulations */
	list_add_tail(&pcpu->list, &xen_pcpus);

	err = रेजिस्टर_pcpu(pcpu);
	अगर (err) अणु
		pr_warn("Failed to register pcpu%u\n", info->xen_cpuid);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस pcpu;
पूर्ण

/*
 * Caller should hold the xen_pcpu_lock
 */
अटल पूर्णांक sync_pcpu(uपूर्णांक32_t cpu, uपूर्णांक32_t *max_cpu)
अणु
	पूर्णांक ret;
	काष्ठा pcpu *pcpu = शून्य;
	काष्ठा xenpf_pcpuinfo *info;
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd                   = XENPF_get_cpuinfo,
		.पूर्णांकerface_version     = XENPF_INTERFACE_VERSION,
		.u.pcpu_info.xen_cpuid = cpu,
	पूर्ण;

	ret = HYPERVISOR_platक्रमm_op(&op);
	अगर (ret)
		वापस ret;

	info = &op.u.pcpu_info;
	अगर (max_cpu)
		*max_cpu = info->max_present;

	pcpu = get_pcpu(cpu);

	/*
	 * Only those at cpu present map has its sys पूर्णांकerface.
	 */
	अगर (info->flags & XEN_PCPU_FLAGS_INVALID) अणु
		unरेजिस्टर_and_हटाओ_pcpu(pcpu);
		वापस 0;
	पूर्ण

	अगर (!pcpu) अणु
		pcpu = create_and_रेजिस्टर_pcpu(info);
		अगर (IS_ERR_OR_शून्य(pcpu))
			वापस -ENODEV;
	पूर्ण अन्यथा
		pcpu_online_status(info, pcpu);

	वापस 0;
पूर्ण

/*
 * Sync करोm0's pcpu information with xen hypervisor's
 */
अटल पूर्णांक xen_sync_pcpus(व्योम)
अणु
	/*
	 * Boot cpu always have cpu_id 0 in xen
	 */
	uपूर्णांक32_t cpu = 0, max_cpu = 0;
	पूर्णांक err = 0;
	काष्ठा pcpu *pcpu, *पंचांगp;

	mutex_lock(&xen_pcpu_lock);

	जबतक (!err && (cpu <= max_cpu)) अणु
		err = sync_pcpu(cpu, &max_cpu);
		cpu++;
	पूर्ण

	अगर (err)
		list_क्रम_each_entry_safe(pcpu, पंचांगp, &xen_pcpus, list)
			unरेजिस्टर_and_हटाओ_pcpu(pcpu);

	mutex_unlock(&xen_pcpu_lock);

	वापस err;
पूर्ण

अटल व्योम xen_pcpu_work_fn(काष्ठा work_काष्ठा *work)
अणु
	xen_sync_pcpus();
पूर्ण
अटल DECLARE_WORK(xen_pcpu_work, xen_pcpu_work_fn);

अटल irqवापस_t xen_pcpu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	schedule_work(&xen_pcpu_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init xen_pcpu_init(व्योम)
अणु
	पूर्णांक irq, ret;

	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	irq = bind_virq_to_irqhandler(VIRQ_PCPU_STATE, 0,
				      xen_pcpu_पूर्णांकerrupt, 0,
				      "xen-pcpu", शून्य);
	अगर (irq < 0) अणु
		pr_warn("Failed to bind pcpu virq\n");
		वापस irq;
	पूर्ण

	ret = subsys_प्रणाली_रेजिस्टर(&xen_pcpu_subsys, शून्य);
	अगर (ret) अणु
		pr_warn("Failed to register pcpu subsys\n");
		जाओ err1;
	पूर्ण

	ret = xen_sync_pcpus();
	अगर (ret) अणु
		pr_warn("Failed to sync pcpu info\n");
		जाओ err2;
	पूर्ण

	वापस 0;

err2:
	bus_unरेजिस्टर(&xen_pcpu_subsys);
err1:
	unbind_from_irqhandler(irq, शून्य);
	वापस ret;
पूर्ण
arch_initcall(xen_pcpu_init);
