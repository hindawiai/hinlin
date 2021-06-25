<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2013 Imagination Technologies Ltd.
 */
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/mips_mt.h>
#समावेश <यंत्र/vpe.h>
#समावेश <यंत्र/rtlx.h>

अटल पूर्णांक major;

अटल व्योम rtlx_dispatch(व्योम)
अणु
	अगर (पढ़ो_c0_cause() & पढ़ो_c0_status() & C_SW0)
		करो_IRQ(MIPS_CPU_IRQ_BASE + MIPS_CPU_RTLX_IRQ);
पूर्ण

/*
 * Interrupt handler may be called beक्रमe rtlx_init has otherwise had
 * a chance to run.
 */
अटल irqवापस_t rtlx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक vpeflags;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	local_irq_save(flags);
	vpeflags = dvpe();
	set_c0_status(0x100 << MIPS_CPU_RTLX_IRQ);
	irq_enable_hazard();
	evpe(vpeflags);
	local_irq_restore(flags);

	क्रम (i = 0; i < RTLX_CHANNELS; i++) अणु
		wake_up(&channel_wqs[i].lx_queue);
		wake_up(&channel_wqs[i].rt_queue);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rtlx_irq_num = MIPS_CPU_IRQ_BASE + MIPS_CPU_RTLX_IRQ;

व्योम _पूर्णांकerrupt_sp(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	dvpe();
	settc(1);
	ग_लिखो_vpe_c0_cause(पढ़ो_vpe_c0_cause() | C_SW0);
	evpe(EVPE_ENABLE);
	local_irq_restore(flags);
पूर्ण

पूर्णांक __init rtlx_module_init(व्योम)
अणु
	काष्ठा device *dev;
	पूर्णांक i, err;

	अगर (!cpu_has_mipsmt) अणु
		pr_warn("VPE loader: not a MIPS MT capable processor\n");
		वापस -ENODEV;
	पूर्ण

	अगर (aprp_cpu_index() == 0) अणु
		pr_warn("No TCs reserved for AP/SP, not initializing RTLX.\n"
			"Pass maxtcs=<n> argument as kernel argument\n");

		वापस -ENODEV;
	पूर्ण

	major = रेजिस्टर_chrdev(0, RTLX_MODULE_NAME, &rtlx_fops);
	अगर (major < 0) अणु
		pr_err("rtlx_module_init: unable to register device\n");
		वापस major;
	पूर्ण

	/* initialise the रुको queues */
	क्रम (i = 0; i < RTLX_CHANNELS; i++) अणु
		init_रुकोqueue_head(&channel_wqs[i].rt_queue);
		init_रुकोqueue_head(&channel_wqs[i].lx_queue);
		atomic_set(&channel_wqs[i].in_खोलो, 0);
		mutex_init(&channel_wqs[i].mutex);

		dev = device_create(mt_class, शून्य, MKDEV(major, i), शून्य,
				    "%s%d", RTLX_MODULE_NAME, i);
		अगर (IS_ERR(dev)) अणु
			जबतक (i--)
				device_destroy(mt_class, MKDEV(major, i));

			err = PTR_ERR(dev);
			जाओ out_chrdev;
		पूर्ण
	पूर्ण

	/* set up notअगरiers */
	rtlx_notअगरy.start = rtlx_starting;
	rtlx_notअगरy.stop = rtlx_stopping;
	vpe_notअगरy(aprp_cpu_index(), &rtlx_notअगरy);

	अगर (cpu_has_vपूर्णांक) अणु
		aprp_hook = rtlx_dispatch;
	पूर्ण अन्यथा अणु
		pr_err("APRP RTLX init on non-vectored-interrupt processor\n");
		err = -ENODEV;
		जाओ out_class;
	पूर्ण

	err = request_irq(rtlx_irq_num, rtlx_पूर्णांकerrupt, 0, "RTLX", rtlx);
	अगर (err)
		जाओ out_class;

	वापस 0;

out_class:
	क्रम (i = 0; i < RTLX_CHANNELS; i++)
		device_destroy(mt_class, MKDEV(major, i));
out_chrdev:
	unरेजिस्टर_chrdev(major, RTLX_MODULE_NAME);

	वापस err;
पूर्ण

व्योम __निकास rtlx_module_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RTLX_CHANNELS; i++)
		device_destroy(mt_class, MKDEV(major, i));

	unरेजिस्टर_chrdev(major, RTLX_MODULE_NAME);

	aprp_hook = शून्य;
पूर्ण
