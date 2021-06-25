<शैली गुरु>
/*
 * Support क्रम hardware-assisted userspace पूर्णांकerrupt masking.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#घोषणा pr_fmt(fmt) "intc: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sizes.h>
#समावेश "internals.h"

अटल व्योम __iomem *uimask;

अटल sमाप_प्रकार
show_पूर्णांकc_userimask(काष्ठा device *dev,
		    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", (__raw_पढ़ोl(uimask) >> 4) & 0xf);
पूर्ण

अटल sमाप_प्रकार
store_पूर्णांकc_userimask(काष्ठा device *dev,
		     काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ level;

	level = simple_म_से_अदीर्घ(buf, शून्य, 10);

	/*
	 * Minimal acceptable IRQ levels are in the 2 - 16 range, but
	 * these are chomped so as to not पूर्णांकerfere with normal IRQs.
	 *
	 * Level 1 is a special हाल on some CPUs in that it's not
	 * directly settable, but given that USERIMASK cuts off below a
	 * certain level, we करोn't care about this limitation here.
	 * Level 0 on the other hand equates to user masking disabled.
	 *
	 * We use the शेष priority level as a cut off so that only
	 * special हाल opt-in IRQs can be mangled.
	 */
	अगर (level >= पूर्णांकc_get_dfl_prio_level())
		वापस -EINVAL;

	__raw_ग_लिखोl(0xa5 << 24 | level << 4, uimask);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(userimask, S_IRUSR | S_IWUSR,
		   show_पूर्णांकc_userimask, store_पूर्णांकc_userimask);


अटल पूर्णांक __init userimask_sysdev_init(व्योम)
अणु
	अगर (unlikely(!uimask))
		वापस -ENXIO;

	वापस device_create_file(पूर्णांकc_subsys.dev_root, &dev_attr_userimask);
पूर्ण
late_initcall(userimask_sysdev_init);

पूर्णांक रेजिस्टर_पूर्णांकc_userimask(अचिन्हित दीर्घ addr)
अणु
	अगर (unlikely(uimask))
		वापस -EBUSY;

	uimask = ioremap(addr, SZ_4K);
	अगर (unlikely(!uimask))
		वापस -ENOMEM;

	pr_info("userimask support registered for levels 0 -> %d\n",
		पूर्णांकc_get_dfl_prio_level() - 1);

	वापस 0;
पूर्ण
