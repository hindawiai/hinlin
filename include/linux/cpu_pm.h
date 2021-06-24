<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@android.com>
 */

#अगर_अघोषित _LINUX_CPU_PM_H
#घोषणा _LINUX_CPU_PM_H

#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>

/*
 * When a CPU goes to a low घातer state that turns off घातer to the CPU's
 * घातer करोमुख्य, the contents of some blocks (भग्नing poपूर्णांक coprocessors,
 * पूर्णांकerrupt controllers, caches, समयrs) in the same घातer करोमुख्य can
 * be lost.  The cpm_pm notअगरiers provide a method क्रम platक्रमm idle, suspend,
 * and hotplug implementations to notअगरy the drivers क्रम these blocks that
 * they may be reset.
 *
 * All cpu_pm notअगरications must be called with पूर्णांकerrupts disabled.
 *
 * The notअगरications are split पूर्णांकo two classes: CPU notअगरications and CPU
 * cluster notअगरications.
 *
 * CPU notअगरications apply to a single CPU and must be called on the affected
 * CPU.  They are used to save per-cpu context क्रम affected blocks.
 *
 * CPU cluster notअगरications apply to all CPUs in a single घातer करोमुख्य. They
 * are used to save any global context क्रम affected blocks, and must be called
 * after all the CPUs in the घातer करोमुख्य have been notअगरied of the low घातer
 * state.
 */

/*
 * Event codes passed as अचिन्हित दीर्घ val to notअगरier calls
 */
क्रमागत cpu_pm_event अणु
	/* A single cpu is entering a low घातer state */
	CPU_PM_ENTER,

	/* A single cpu failed to enter a low घातer state */
	CPU_PM_ENTER_FAILED,

	/* A single cpu is निकासing a low घातer state */
	CPU_PM_EXIT,

	/* A cpu घातer करोमुख्य is entering a low घातer state */
	CPU_CLUSTER_PM_ENTER,

	/* A cpu घातer करोमुख्य failed to enter a low घातer state */
	CPU_CLUSTER_PM_ENTER_FAILED,

	/* A cpu घातer करोमुख्य is निकासing a low घातer state */
	CPU_CLUSTER_PM_EXIT,
पूर्ण;

#अगर_घोषित CONFIG_CPU_PM
पूर्णांक cpu_pm_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक cpu_pm_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक cpu_pm_enter(व्योम);
पूर्णांक cpu_pm_निकास(व्योम);
पूर्णांक cpu_cluster_pm_enter(व्योम);
पूर्णांक cpu_cluster_pm_निकास(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक cpu_pm_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_pm_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_pm_enter(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_pm_निकास(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_cluster_pm_enter(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_cluster_pm_निकास(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
