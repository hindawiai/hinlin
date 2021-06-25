<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Interface क्रम घातer-management क्रम ppc64 compliant platक्रमm
 *
 *  Manish Ahuja <mahuja@us.ibm.com>
 *
 *  Feb 2007
 *
 *  Copyright (C) 2007 IBM Corporation.
 */

#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <यंत्र/machdep.h>

#समावेश "pseries.h"

अचिन्हित दीर्घ rtas_घातeron_स्वतः; /* शेष and normal state is 0 */

अटल sमाप_प्रकार स्वतः_घातeron_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
        वापस प्र_लिखो(buf, "%lu\n", rtas_घातeron_स्वतः);
पूर्ण

अटल sमाप_प्रकार स्वतः_घातeron_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ ups_restart;
	ret = माला_पूछो(buf, "%lu", &ups_restart);

	अगर ((ret == 1) && ((ups_restart == 1) || (ups_restart == 0)))अणु
		rtas_घातeron_स्वतः = ups_restart;
		वापस n;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल काष्ठा kobj_attribute स्वतः_घातeron_attr =
	__ATTR(स्वतः_घातeron, 0644, स्वतः_घातeron_show, स्वतः_घातeron_store);

#अगर_अघोषित CONFIG_PM
काष्ठा kobject *घातer_kobj;

अटल काष्ठा attribute *g[] = अणु
        &स्वतः_घातeron_attr.attr,
        शून्य,
पूर्ण;

अटल काष्ठा attribute_group attr_group = अणु
        .attrs = g,
पूर्ण;

अटल पूर्णांक __init pm_init(व्योम)
अणु
	घातer_kobj = kobject_create_and_add("power", शून्य);
	अगर (!घातer_kobj)
		वापस -ENOMEM;
	वापस sysfs_create_group(घातer_kobj, &attr_group);
पूर्ण
machine_core_initcall(pseries, pm_init);
#अन्यथा
अटल पूर्णांक __init apo_pm_init(व्योम)
अणु
	वापस (sysfs_create_file(घातer_kobj, &स्वतः_घातeron_attr.attr));
पूर्ण
machine_device_initcall(pseries, apo_pm_init);
#पूर्ण_अगर
