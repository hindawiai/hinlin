<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/rcupdate.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <misc/cxl-base.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश "cxl.h"

/* रक्षित by rcu */
अटल काष्ठा cxl_calls *cxl_calls;

atomic_t cxl_use_count = ATOMIC_INIT(0);
EXPORT_SYMBOL(cxl_use_count);

#अगर_घोषित CONFIG_CXL_MODULE

अटल अंतरभूत काष्ठा cxl_calls *cxl_calls_get(व्योम)
अणु
	काष्ठा cxl_calls *calls = शून्य;

	rcu_पढ़ो_lock();
	calls = rcu_dereference(cxl_calls);
	अगर (calls && !try_module_get(calls->owner))
		calls = शून्य;
	rcu_पढ़ो_unlock();

	वापस calls;
पूर्ण

अटल अंतरभूत व्योम cxl_calls_put(काष्ठा cxl_calls *calls)
अणु
	BUG_ON(calls != cxl_calls);

	/* we करोn't need to rcu this, as we hold a reference to the module */
	module_put(cxl_calls->owner);
पूर्ण

#अन्यथा /* !defined CONFIG_CXL_MODULE */

अटल अंतरभूत काष्ठा cxl_calls *cxl_calls_get(व्योम)
अणु
	वापस cxl_calls;
पूर्ण

अटल अंतरभूत व्योम cxl_calls_put(काष्ठा cxl_calls *calls) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_CXL_MODULE */

/* AFU refcount management */
काष्ठा cxl_afu *cxl_afu_get(काष्ठा cxl_afu *afu)
अणु
	वापस (get_device(&afu->dev) == शून्य) ? शून्य : afu;
पूर्ण
EXPORT_SYMBOL_GPL(cxl_afu_get);

व्योम cxl_afu_put(काष्ठा cxl_afu *afu)
अणु
	put_device(&afu->dev);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_afu_put);

व्योम cxl_slbia(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा cxl_calls *calls;

	calls = cxl_calls_get();
	अगर (!calls)
		वापस;

	अगर (cxl_ctx_in_use())
	    calls->cxl_slbia(mm);

	cxl_calls_put(calls);
पूर्ण

पूर्णांक रेजिस्टर_cxl_calls(काष्ठा cxl_calls *calls)
अणु
	अगर (cxl_calls)
		वापस -EBUSY;

	rcu_assign_poपूर्णांकer(cxl_calls, calls);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_cxl_calls);

व्योम unरेजिस्टर_cxl_calls(काष्ठा cxl_calls *calls)
अणु
	BUG_ON(cxl_calls->owner != calls->owner);
	RCU_INIT_POINTER(cxl_calls, शून्य);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_cxl_calls);

पूर्णांक cxl_update_properties(काष्ठा device_node *dn,
			  काष्ठा property *new_prop)
अणु
	वापस of_update_property(dn, new_prop);
पूर्ण
EXPORT_SYMBOL_GPL(cxl_update_properties);

अटल पूर्णांक __init cxl_base_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *dev;
	पूर्णांक count = 0;

	/*
	 * Scan क्रम compatible devices in guest only
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		वापस 0;

	क्रम_each_compatible_node(np, शून्य, "ibm,coherent-platform-facility") अणु
		dev = of_platक्रमm_device_create(np, शून्य, शून्य);
		अगर (dev)
			count++;
	पूर्ण
	pr_devel("Found %d cxl device(s)\n", count);
	वापस 0;
पूर्ण
device_initcall(cxl_base_init);
