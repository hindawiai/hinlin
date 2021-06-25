<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/drivers/base/map.c
 *
 * (C) Copyright Al Viro 2002,2003
 *
 * NOTE: data काष्ठाure needs to be changed.  It works, but क्रम large dev_t
 * it will be too slow.  It is isolated, though, so these changes will be
 * local to that file.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kobj_map.h>

काष्ठा kobj_map अणु
	काष्ठा probe अणु
		काष्ठा probe *next;
		dev_t dev;
		अचिन्हित दीर्घ range;
		काष्ठा module *owner;
		kobj_probe_t *get;
		पूर्णांक (*lock)(dev_t, व्योम *);
		व्योम *data;
	पूर्ण *probes[255];
	काष्ठा mutex *lock;
पूर्ण;

पूर्णांक kobj_map(काष्ठा kobj_map *करोमुख्य, dev_t dev, अचिन्हित दीर्घ range,
	     काष्ठा module *module, kobj_probe_t *probe,
	     पूर्णांक (*lock)(dev_t, व्योम *), व्योम *data)
अणु
	अचिन्हित n = MAJOR(dev + range - 1) - MAJOR(dev) + 1;
	अचिन्हित index = MAJOR(dev);
	अचिन्हित i;
	काष्ठा probe *p;

	अगर (n > 255)
		n = 255;

	p = kदो_स्मृति_array(n, माप(काष्ठा probe), GFP_KERNEL);
	अगर (p == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++, p++) अणु
		p->owner = module;
		p->get = probe;
		p->lock = lock;
		p->dev = dev;
		p->range = range;
		p->data = data;
	पूर्ण
	mutex_lock(करोमुख्य->lock);
	क्रम (i = 0, p -= n; i < n; i++, p++, index++) अणु
		काष्ठा probe **s = &करोमुख्य->probes[index % 255];
		जबतक (*s && (*s)->range < range)
			s = &(*s)->next;
		p->next = *s;
		*s = p;
	पूर्ण
	mutex_unlock(करोमुख्य->lock);
	वापस 0;
पूर्ण

व्योम kobj_unmap(काष्ठा kobj_map *करोमुख्य, dev_t dev, अचिन्हित दीर्घ range)
अणु
	अचिन्हित n = MAJOR(dev + range - 1) - MAJOR(dev) + 1;
	अचिन्हित index = MAJOR(dev);
	अचिन्हित i;
	काष्ठा probe *found = शून्य;

	अगर (n > 255)
		n = 255;

	mutex_lock(करोमुख्य->lock);
	क्रम (i = 0; i < n; i++, index++) अणु
		काष्ठा probe **s;
		क्रम (s = &करोमुख्य->probes[index % 255]; *s; s = &(*s)->next) अणु
			काष्ठा probe *p = *s;
			अगर (p->dev == dev && p->range == range) अणु
				*s = p->next;
				अगर (!found)
					found = p;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(करोमुख्य->lock);
	kमुक्त(found);
पूर्ण

काष्ठा kobject *kobj_lookup(काष्ठा kobj_map *करोमुख्य, dev_t dev, पूर्णांक *index)
अणु
	काष्ठा kobject *kobj;
	काष्ठा probe *p;
	अचिन्हित दीर्घ best = ~0UL;

retry:
	mutex_lock(करोमुख्य->lock);
	क्रम (p = करोमुख्य->probes[MAJOR(dev) % 255]; p; p = p->next) अणु
		काष्ठा kobject *(*probe)(dev_t, पूर्णांक *, व्योम *);
		काष्ठा module *owner;
		व्योम *data;

		अगर (p->dev > dev || p->dev + p->range - 1 < dev)
			जारी;
		अगर (p->range - 1 >= best)
			अवरोध;
		अगर (!try_module_get(p->owner))
			जारी;
		owner = p->owner;
		data = p->data;
		probe = p->get;
		best = p->range - 1;
		*index = dev - p->dev;
		अगर (p->lock && p->lock(dev, data) < 0) अणु
			module_put(owner);
			जारी;
		पूर्ण
		mutex_unlock(करोमुख्य->lock);
		kobj = probe(dev, index, data);
		/* Currently ->owner protects _only_ ->probe() itself. */
		module_put(owner);
		अगर (kobj)
			वापस kobj;
		जाओ retry;
	पूर्ण
	mutex_unlock(करोमुख्य->lock);
	वापस शून्य;
पूर्ण

काष्ठा kobj_map *kobj_map_init(kobj_probe_t *base_probe, काष्ठा mutex *lock)
अणु
	काष्ठा kobj_map *p = kदो_स्मृति(माप(काष्ठा kobj_map), GFP_KERNEL);
	काष्ठा probe *base = kzalloc(माप(*base), GFP_KERNEL);
	पूर्णांक i;

	अगर ((p == शून्य) || (base == शून्य)) अणु
		kमुक्त(p);
		kमुक्त(base);
		वापस शून्य;
	पूर्ण

	base->dev = 1;
	base->range = ~0;
	base->get = base_probe;
	क्रम (i = 0; i < 255; i++)
		p->probes[i] = base;
	p->lock = lock;
	वापस p;
पूर्ण
