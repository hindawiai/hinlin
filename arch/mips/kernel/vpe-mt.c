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

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/vpe.h>

अटल पूर्णांक major;

/* The number of TCs and VPEs physically available on the core */
अटल पूर्णांक hw_tcs, hw_vpes;

/* We are prepared so configure and start the VPE... */
पूर्णांक vpe_run(काष्ठा vpe *v)
अणु
	अचिन्हित दीर्घ flags, val, dmt_flag;
	काष्ठा vpe_notअगरications *notअगरier;
	अचिन्हित पूर्णांक vpeflags;
	काष्ठा tc *t;

	/* check we are the Master VPE */
	local_irq_save(flags);
	val = पढ़ो_c0_vpeconf0();
	अगर (!(val & VPECONF0_MVP)) अणु
		pr_warn("VPE loader: only Master VPE's are able to config MT\n");
		local_irq_restore(flags);

		वापस -1;
	पूर्ण

	dmt_flag = dmt();
	vpeflags = dvpe();

	अगर (list_empty(&v->tc)) अणु
		evpe(vpeflags);
		emt(dmt_flag);
		local_irq_restore(flags);

		pr_warn("VPE loader: No TC's associated with VPE %d\n",
			v->minor);

		वापस -ENOEXEC;
	पूर्ण

	t = list_first_entry(&v->tc, काष्ठा tc, tc);

	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	settc(t->index);

	/* should check it is halted, and not activated */
	अगर ((पढ़ो_tc_c0_tcstatus() & TCSTATUS_A) ||
	   !(पढ़ो_tc_c0_tchalt() & TCHALT_H)) अणु
		evpe(vpeflags);
		emt(dmt_flag);
		local_irq_restore(flags);

		pr_warn("VPE loader: TC %d is already active!\n",
			t->index);

		वापस -ENOEXEC;
	पूर्ण

	/*
	 * Write the address we want it to start running from in the TCPC
	 * रेजिस्टर.
	 */
	ग_लिखो_tc_c0_tcrestart((अचिन्हित दीर्घ)v->__start);
	ग_लिखो_tc_c0_tccontext((अचिन्हित दीर्घ)0);

	/*
	 * Mark the TC as activated, not पूर्णांकerrupt exempt and not dynamically
	 * allocatable
	 */
	val = पढ़ो_tc_c0_tcstatus();
	val = (val & ~(TCSTATUS_DA | TCSTATUS_IXMT)) | TCSTATUS_A;
	ग_लिखो_tc_c0_tcstatus(val);

	ग_लिखो_tc_c0_tchalt(पढ़ो_tc_c0_tchalt() & ~TCHALT_H);

	/*
	 * The sde-kit passes 'memsize' to __start in $a3, so set something
	 * here...  Or set $a3 to zero and define DFLT_STACK_SIZE and
	 * DFLT_HEAP_SIZE when you compile your program
	 */
	mttgpr(6, v->ntcs);
	mttgpr(7, physical_memsize);

	/* set up VPE1 */
	/*
	 * bind the TC to VPE 1 as late as possible so we only have the final
	 * VPE रेजिस्टरs to set up, and so an EJTAG probe can trigger on it
	 */
	ग_लिखो_tc_c0_tcbind((पढ़ो_tc_c0_tcbind() & ~TCBIND_CURVPE) | 1);

	ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() & ~(VPECONF0_VPA));

	back_to_back_c0_hazard();

	/* Set up the XTC bit in vpeconf0 to poपूर्णांक at our tc */
	ग_लिखो_vpe_c0_vpeconf0((पढ़ो_vpe_c0_vpeconf0() & ~(VPECONF0_XTC))
			      | (t->index << VPECONF0_XTC_SHIFT));

	back_to_back_c0_hazard();

	/* enable this VPE */
	ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() | VPECONF0_VPA);

	/* clear out any left overs from a previous program */
	ग_लिखो_vpe_c0_status(0);
	ग_लिखो_vpe_c0_cause(0);

	/* take प्रणाली out of configuration state */
	clear_c0_mvpcontrol(MVPCONTROL_VPC);

	/*
	 * SMVP kernels manage VPE enable independently, but uniprocessor
	 * kernels need to turn it on, even अगर that wasn't the pre-dvpe() state.
	 */
#अगर_घोषित CONFIG_SMP
	evpe(vpeflags);
#अन्यथा
	evpe(EVPE_ENABLE);
#पूर्ण_अगर
	emt(dmt_flag);
	local_irq_restore(flags);

	list_क्रम_each_entry(notअगरier, &v->notअगरy, list)
		notअगरier->start(VPE_MODULE_MINOR);

	वापस 0;
पूर्ण

व्योम cleanup_tc(काष्ठा tc *tc)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mtflags, vpflags;
	पूर्णांक पंचांगp;

	local_irq_save(flags);
	mtflags = dmt();
	vpflags = dvpe();
	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	settc(tc->index);
	पंचांगp = पढ़ो_tc_c0_tcstatus();

	/* mark not allocated and not dynamically allocatable */
	पंचांगp &= ~(TCSTATUS_A | TCSTATUS_DA);
	पंचांगp |= TCSTATUS_IXMT;	/* पूर्णांकerrupt exempt */
	ग_लिखो_tc_c0_tcstatus(पंचांगp);

	ग_लिखो_tc_c0_tchalt(TCHALT_H);
	mips_ihb();

	clear_c0_mvpcontrol(MVPCONTROL_VPC);
	evpe(vpflags);
	emt(mtflags);
	local_irq_restore(flags);
पूर्ण

/* module wrapper entry poपूर्णांकs */
/* give me a vpe */
व्योम *vpe_alloc(व्योम)
अणु
	पूर्णांक i;
	काष्ठा vpe *v;

	/* find a vpe */
	क्रम (i = 1; i < MAX_VPES; i++) अणु
		v = get_vpe(i);
		अगर (v != शून्य) अणु
			v->state = VPE_STATE_INUSE;
			वापस v;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vpe_alloc);

/* start running from here */
पूर्णांक vpe_start(व्योम *vpe, अचिन्हित दीर्घ start)
अणु
	काष्ठा vpe *v = vpe;

	v->__start = start;
	वापस vpe_run(v);
पूर्ण
EXPORT_SYMBOL(vpe_start);

/* halt it क्रम now */
पूर्णांक vpe_stop(व्योम *vpe)
अणु
	काष्ठा vpe *v = vpe;
	काष्ठा tc *t;
	अचिन्हित पूर्णांक evpe_flags;

	evpe_flags = dvpe();

	t = list_entry(v->tc.next, काष्ठा tc, tc);
	अगर (t != शून्य) अणु
		settc(t->index);
		ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() & ~VPECONF0_VPA);
	पूर्ण

	evpe(evpe_flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpe_stop);

/* I've करोne with it thank you */
पूर्णांक vpe_मुक्त(व्योम *vpe)
अणु
	काष्ठा vpe *v = vpe;
	काष्ठा tc *t;
	अचिन्हित पूर्णांक evpe_flags;

	t = list_entry(v->tc.next, काष्ठा tc, tc);
	अगर (t == शून्य)
		वापस -ENOEXEC;

	evpe_flags = dvpe();

	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	settc(t->index);
	ग_लिखो_vpe_c0_vpeconf0(पढ़ो_vpe_c0_vpeconf0() & ~VPECONF0_VPA);

	/* halt the TC */
	ग_लिखो_tc_c0_tchalt(TCHALT_H);
	mips_ihb();

	/* mark the TC unallocated */
	ग_लिखो_tc_c0_tcstatus(पढ़ो_tc_c0_tcstatus() & ~TCSTATUS_A);

	v->state = VPE_STATE_UNUSED;

	clear_c0_mvpcontrol(MVPCONTROL_VPC);
	evpe(evpe_flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vpe_मुक्त);

अटल sमाप_प्रकार store_समाप्त(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा vpe *vpe = get_vpe(aprp_cpu_index());
	काष्ठा vpe_notअगरications *notअगरier;

	list_क्रम_each_entry(notअगरier, &vpe->notअगरy, list)
		notअगरier->stop(aprp_cpu_index());

	release_progmem(vpe->load_addr);
	cleanup_tc(get_tc(aprp_cpu_index()));
	vpe_stop(vpe);
	vpe_मुक्त(vpe);

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

	अगर (new == 0 || new > (hw_tcs - aprp_cpu_index()))
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
	अचिन्हित पूर्णांक mtflags, vpflags;
	अचिन्हित दीर्घ flags, val;
	काष्ठा vpe *v = शून्य;
	काष्ठा tc *t;
	पूर्णांक tc, err;

	अगर (!cpu_has_mipsmt) अणु
		pr_warn("VPE loader: not a MIPS MT capable processor\n");
		वापस -ENODEV;
	पूर्ण

	अगर (vpelimit == 0) अणु
		pr_warn("No VPEs reserved for AP/SP, not initialize VPE loader\n"
			"Pass maxvpes=<n> argument as kernel argument\n");

		वापस -ENODEV;
	पूर्ण

	अगर (aprp_cpu_index() == 0) अणु
		pr_warn("No TCs reserved for AP/SP, not initialize VPE loader\n"
			"Pass maxtcs=<n> argument as kernel argument\n");

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
	dev_set_name(&vpe_device, "vpe1");
	vpe_device.devt = MKDEV(major, VPE_MODULE_MINOR);
	err = device_add(&vpe_device);
	अगर (err) अणु
		pr_err("Adding vpe_device failed\n");
		जाओ out_class;
	पूर्ण

	local_irq_save(flags);
	mtflags = dmt();
	vpflags = dvpe();

	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	val = पढ़ो_c0_mvpconf0();
	hw_tcs = (val & MVPCONF0_PTC) + 1;
	hw_vpes = ((val & MVPCONF0_PVPE) >> MVPCONF0_PVPE_SHIFT) + 1;

	क्रम (tc = aprp_cpu_index(); tc < hw_tcs; tc++) अणु
		/*
		 * Must re-enable multithपढ़ोing temporarily or in हाल we
		 * reschedule send IPIs or similar we might hang.
		 */
		clear_c0_mvpcontrol(MVPCONTROL_VPC);
		evpe(vpflags);
		emt(mtflags);
		local_irq_restore(flags);
		t = alloc_tc(tc);
		अगर (!t) अणु
			err = -ENOMEM;
			जाओ out_dev;
		पूर्ण

		local_irq_save(flags);
		mtflags = dmt();
		vpflags = dvpe();
		set_c0_mvpcontrol(MVPCONTROL_VPC);

		/* VPE's */
		अगर (tc < hw_tcs) अणु
			settc(tc);

			v = alloc_vpe(tc);
			अगर (v == शून्य) अणु
				pr_warn("VPE: unable to allocate VPE\n");
				जाओ out_reenable;
			पूर्ण

			v->ntcs = hw_tcs - aprp_cpu_index();

			/* add the tc to the list of this vpe's tc's. */
			list_add(&t->tc, &v->tc);

			/* deactivate all but vpe0 */
			अगर (tc >= aprp_cpu_index()) अणु
				अचिन्हित दीर्घ पंचांगp = पढ़ो_vpe_c0_vpeconf0();

				पंचांगp &= ~VPECONF0_VPA;

				/* master VPE */
				पंचांगp |= VPECONF0_MVP;
				ग_लिखो_vpe_c0_vpeconf0(पंचांगp);
			पूर्ण

			/* disable multi-thपढ़ोing with TC's */
			ग_लिखो_vpe_c0_vpecontrol(पढ़ो_vpe_c0_vpecontrol() &
						~VPECONTROL_TE);

			अगर (tc >= vpelimit) अणु
				/*
				 * Set config to be the same as vpe0,
				 * particularly kseg0 coherency alg
				 */
				ग_लिखो_vpe_c0_config(पढ़ो_c0_config());
			पूर्ण
		पूर्ण

		/* TC's */
		t->pvpe = v;	/* set the parent vpe */

		अगर (tc >= aprp_cpu_index()) अणु
			अचिन्हित दीर्घ पंचांगp;

			settc(tc);

			/*
			 * A TC that is bound to any other VPE माला_लो bound to
			 * VPE0, ideally I'd like to make it homeless but it
			 * करोesn't appear to let me bind a TC to a non-existent
			 * VPE. Which is perfectly reasonable.
			 *
			 * The (un)bound state is visible to an EJTAG probe so
			 * may notअगरy GDB...
			 */
			पंचांगp = पढ़ो_tc_c0_tcbind();
			अगर (पंचांगp & TCBIND_CURVPE) अणु
				/* tc is bound >vpe0 */
				ग_लिखो_tc_c0_tcbind(पंचांगp & ~TCBIND_CURVPE);

				t->pvpe = get_vpe(0);	/* set the parent vpe */
			पूर्ण

			/* halt the TC */
			ग_लिखो_tc_c0_tchalt(TCHALT_H);
			mips_ihb();

			पंचांगp = पढ़ो_tc_c0_tcstatus();

			/* mark not activated and not dynamically allocatable */
			पंचांगp &= ~(TCSTATUS_A | TCSTATUS_DA);
			पंचांगp |= TCSTATUS_IXMT;	/* पूर्णांकerrupt exempt */
			ग_लिखो_tc_c0_tcstatus(पंचांगp);
		पूर्ण
	पूर्ण

out_reenable:
	/* release config state */
	clear_c0_mvpcontrol(MVPCONTROL_VPC);

	evpe(vpflags);
	emt(mtflags);
	local_irq_restore(flags);

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
	list_क्रम_each_entry_safe(v, n, &vpecontrol.vpe_list, list) अणु
		अगर (v->state != VPE_STATE_UNUSED)
			release_vpe(v);
	पूर्ण
पूर्ण
