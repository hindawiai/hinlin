<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SMPBOOT_H
#घोषणा _LINUX_SMPBOOT_H

#समावेश <linux/types.h>

काष्ठा task_काष्ठा;
/* Cookie handed to the thपढ़ो_fn*/
काष्ठा smpboot_thपढ़ो_data;

/**
 * काष्ठा smp_hotplug_thपढ़ो - CPU hotplug related thपढ़ो descriptor
 * @store:		Poपूर्णांकer to per cpu storage क्रम the task poपूर्णांकers
 * @list:		List head क्रम core management
 * @thपढ़ो_should_run:	Check whether the thपढ़ो should run or not. Called with
 *			preemption disabled.
 * @thपढ़ो_fn:		The associated thपढ़ो function
 * @create:		Optional setup function, called when the thपढ़ो माला_लो
 *			created (Not called from the thपढ़ो context)
 * @setup:		Optional setup function, called when the thपढ़ो माला_लो
 *			operational the first समय
 * @cleanup:		Optional cleanup function, called when the thपढ़ो
 *			should stop (module निकास)
 * @park:		Optional park function, called when the thपढ़ो is
 *			parked (cpu offline)
 * @unpark:		Optional unpark function, called when the thपढ़ो is
 *			unparked (cpu online)
 * @selfparking:	Thपढ़ो is not parked by the park function.
 * @thपढ़ो_comm:	The base name of the thपढ़ो
 */
काष्ठा smp_hotplug_thपढ़ो अणु
	काष्ठा task_काष्ठा		* __percpu *store;
	काष्ठा list_head		list;
	पूर्णांक				(*thपढ़ो_should_run)(अचिन्हित पूर्णांक cpu);
	व्योम				(*thपढ़ो_fn)(अचिन्हित पूर्णांक cpu);
	व्योम				(*create)(अचिन्हित पूर्णांक cpu);
	व्योम				(*setup)(अचिन्हित पूर्णांक cpu);
	व्योम				(*cleanup)(अचिन्हित पूर्णांक cpu, bool online);
	व्योम				(*park)(अचिन्हित पूर्णांक cpu);
	व्योम				(*unpark)(अचिन्हित पूर्णांक cpu);
	bool				selfparking;
	स्थिर अक्षर			*thपढ़ो_comm;
पूर्ण;

पूर्णांक smpboot_रेजिस्टर_percpu_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *plug_thपढ़ो);

व्योम smpboot_unरेजिस्टर_percpu_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *plug_thपढ़ो);

#पूर्ण_अगर
