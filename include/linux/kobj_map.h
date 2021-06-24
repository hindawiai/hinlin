<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * kobj_map.h
 */

#अगर_अघोषित _KOBJ_MAP_H_
#घोषणा _KOBJ_MAP_H_

#समावेश <linux/mutex.h>

प्रकार काष्ठा kobject *kobj_probe_t(dev_t, पूर्णांक *, व्योम *);
काष्ठा kobj_map;

पूर्णांक kobj_map(काष्ठा kobj_map *, dev_t, अचिन्हित दीर्घ, काष्ठा module *,
	     kobj_probe_t *, पूर्णांक (*)(dev_t, व्योम *), व्योम *);
व्योम kobj_unmap(काष्ठा kobj_map *, dev_t, अचिन्हित दीर्घ);
काष्ठा kobject *kobj_lookup(काष्ठा kobj_map *, dev_t, पूर्णांक *);
काष्ठा kobj_map *kobj_map_init(kobj_probe_t *, काष्ठा mutex *);

#पूर्ण_अगर /* _KOBJ_MAP_H_ */
