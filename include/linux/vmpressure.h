<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_VMPRESSURE_H
#घोषणा __LINUX_VMPRESSURE_H

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/gfp.h>
#समावेश <linux/types.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/eventfd.h>

काष्ठा vmpressure अणु
	अचिन्हित दीर्घ scanned;
	अचिन्हित दीर्घ reclaimed;

	अचिन्हित दीर्घ tree_scanned;
	अचिन्हित दीर्घ tree_reclaimed;
	/* The lock is used to keep the scanned/reclaimed above in sync. */
	spinlock_t sr_lock;

	/* The list of vmpressure_event काष्ठाs. */
	काष्ठा list_head events;
	/* Have to grab the lock on events traversal or modअगरications. */
	काष्ठा mutex events_lock;

	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा mem_cgroup;

#अगर_घोषित CONFIG_MEMCG
बाह्य व्योम vmpressure(gfp_t gfp, काष्ठा mem_cgroup *memcg, bool tree,
		       अचिन्हित दीर्घ scanned, अचिन्हित दीर्घ reclaimed);
बाह्य व्योम vmpressure_prio(gfp_t gfp, काष्ठा mem_cgroup *memcg, पूर्णांक prio);

बाह्य व्योम vmpressure_init(काष्ठा vmpressure *vmpr);
बाह्य व्योम vmpressure_cleanup(काष्ठा vmpressure *vmpr);
बाह्य काष्ठा vmpressure *memcg_to_vmpressure(काष्ठा mem_cgroup *memcg);
बाह्य काष्ठा cgroup_subsys_state *vmpressure_to_css(काष्ठा vmpressure *vmpr);
बाह्य पूर्णांक vmpressure_रेजिस्टर_event(काष्ठा mem_cgroup *memcg,
				     काष्ठा eventfd_ctx *eventfd,
				     स्थिर अक्षर *args);
बाह्य व्योम vmpressure_unरेजिस्टर_event(काष्ठा mem_cgroup *memcg,
					काष्ठा eventfd_ctx *eventfd);
#अन्यथा
अटल अंतरभूत व्योम vmpressure(gfp_t gfp, काष्ठा mem_cgroup *memcg, bool tree,
			      अचिन्हित दीर्घ scanned, अचिन्हित दीर्घ reclaimed) अणुपूर्ण
अटल अंतरभूत व्योम vmpressure_prio(gfp_t gfp, काष्ठा mem_cgroup *memcg,
				   पूर्णांक prio) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG */
#पूर्ण_अगर /* __LINUX_VMPRESSURE_H */
