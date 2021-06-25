<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004, 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/vpe.h>

अटल पूर्णांक major;

व्योम cleanup_tc(काष्ठा tc *tc)
अणु

पूर्ण

अटल sमाप_प्रकार store_समाप्त(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा vpe *vpe = get_vpe(aprp_cpu_index());
	काष्ठा vpe_notअगरications *notअगरier;

	list_क्रम_each_entry(notअगरier, &vpe->notअगरy, list)
		notअगरier->stop(aprp_cpu_index());

	release_progmem(vpe->load_addr);
	vpe->state = VPE_STATE_UNUSED;

	वापस len;
पूर्ण
अटल DEVICE_ATTR(समाप्त, S_IWUSR, शून्य, store_समाप्त);

अटल sमाप_प्रकार ntcs_show(काष्ठा device *cd, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा vpe *vpe = get_vpe(aprp_cpu_index());

	वापस प्र_लिखो(buf, "%d\n", vpe->ntcs);
पूर्ण

अटल sमाप_प्रकार ntcs_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा vpe *vpe = get_vpe(aprp_cpu_index());
	अचिन्हित दीर्घ new;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &new);
	अगर (ret < 0)
		वापस ret;

	/* APRP can only reserve one TC in a VPE and no more. */
	अगर (new != 1)
		वापस -EINVAL;

	vpe->ntcs = new;

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(ntcs);

अटल काष्ठा attribute *vpe_attrs[] = अणु
	&dev_attr_समाप्त.attr,
	&dev_attr_ntcs.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vpe);

अटल व्योम vpe_device_release(काष्ठा device *cd)
अणु
	kमुक्त(cd);
पूर्ण

अटल काष्ठा class vpe_class = अणु
	.name = "vpe",
	.owner = THIS_MODULE,
	.dev_release = vpe_device_release,
	.dev_groups = vpe_groups,
पूर्ण;

अटल काष्ठा device vpe_device;

पूर्णांक __init vpe_module_init(व्योम)
अणु
	काष्ठा vpe *v = शून्य;
	काष्ठा tc *t;
	पूर्णांक err;

	अगर (!cpu_has_mipsmt) अणु
		pr_warn("VPE loader: not a MIPS MT capable processor\n");
		वापस -ENODEV;
	पूर्ण

	अगर (num_possible_cpus() - aprp_cpu_index() < 1) अणु
		pr_warn("No VPEs reserved for AP/SP, not initialize VPE loader\n"
			"Pass maxcpus=<n> argument as kernel argument\n");
		वापस -ENODEV;
	पूर्ण

	major = रेजिस्टर_chrdev(0, VPE_MODULE_NAME, &vpe_fops);
	अगर (major < 0) अणु
		pr_warn("VPE loader: unable to register character device\n");
		वापस major;
	पूर्ण

	err = class_रेजिस्टर(&vpe_class);
	अगर (err) अणु
		pr_err("vpe_class registration failed\n");
		जाओ out_chrdev;
	पूर्ण

	device_initialize(&vpe_device);
	vpe_device.class	= &vpe_class;
	vpe_device.parent	= शून्य;
	dev_set_name(&vpe_device, "vpe_sp");
	vpe_device.devt = MKDEV(major, VPE_MODULE_MINOR);
	err = device_add(&vpe_device);
	अगर (err) अणु
		pr_err("Adding vpe_device failed\n");
		जाओ out_class;
	पूर्ण

	t = alloc_tc(aprp_cpu_index());
	अगर (!t) अणु
		pr_warn("VPE: unable to allocate TC\n");
		err = -ENOMEM;
		जाओ out_dev;
	पूर्ण

	/* VPE */
	v = alloc_vpe(aprp_cpu_index());
	अगर (v == शून्य) अणु
		pr_warn("VPE: unable to allocate VPE\n");
		kमुक्त(t);
		err = -ENOMEM;
		जाओ out_dev;
	पूर्ण

	v->ntcs = 1;

	/* add the tc to the list of this vpe's tc's. */
	list_add(&t->tc, &v->tc);

	/* TC */
	t->pvpe = v;	/* set the parent vpe */

	वापस 0;

out_dev:
	device_del(&vpe_device);

out_class:
	class_unरेजिस्टर(&vpe_class);

out_chrdev:
	unरेजिस्टर_chrdev(major, VPE_MODULE_NAME);

	वापस err;
पूर्ण

व्योम __निकास vpe_module_निकास(व्योम)
अणु
	काष्ठा vpe *v, *n;

	device_del(&vpe_device);
	class_unरेजिस्टर(&vpe_class);
	unरेजिस्टर_chrdev(major, VPE_MODULE_NAME);

	/* No locking needed here */
	list_क्रम_each_entry_safe(v, n, &vpecontrol.vpe_list, list)
		अगर (v->state != VPE_STATE_UNUSED)
			release_vpe(v);
पूर्ण
