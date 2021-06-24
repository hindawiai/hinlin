<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <दो_स्मृति.h>
#समावेश <pthपढ़ो.h>
#समावेश <unistd.h>
#समावेश <निश्चित.स>

#समावेश <linux/gfp.h>
#समावेश <linux/poison.h>
#समावेश <linux/slab.h>
#समावेश <linux/radix-tree.h>
#समावेश <urcu/uatomic.h>

पूर्णांक nr_allocated;
पूर्णांक preempt_count;
पूर्णांक kदो_स्मृति_verbose;
पूर्णांक test_verbose;

काष्ठा kmem_cache अणु
	pthपढ़ो_mutex_t lock;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक align;
	पूर्णांक nr_objs;
	व्योम *objs;
	व्योम (*ctor)(व्योम *);
पूर्ण;

व्योम *kmem_cache_alloc(काष्ठा kmem_cache *cachep, पूर्णांक gfp)
अणु
	व्योम *p;

	अगर (!(gfp & __GFP_सूचीECT_RECLAIM))
		वापस शून्य;

	pthपढ़ो_mutex_lock(&cachep->lock);
	अगर (cachep->nr_objs) अणु
		काष्ठा radix_tree_node *node = cachep->objs;
		cachep->nr_objs--;
		cachep->objs = node->parent;
		pthपढ़ो_mutex_unlock(&cachep->lock);
		node->parent = शून्य;
		p = node;
	पूर्ण अन्यथा अणु
		pthपढ़ो_mutex_unlock(&cachep->lock);
		अगर (cachep->align)
			posix_memalign(&p, cachep->align, cachep->size);
		अन्यथा
			p = दो_स्मृति(cachep->size);
		अगर (cachep->ctor)
			cachep->ctor(p);
		अन्यथा अगर (gfp & __GFP_ZERO)
			स_रखो(p, 0, cachep->size);
	पूर्ण

	uatomic_inc(&nr_allocated);
	अगर (kदो_स्मृति_verbose)
		म_लिखो("Allocating %p from slab\n", p);
	वापस p;
पूर्ण

व्योम kmem_cache_मुक्त(काष्ठा kmem_cache *cachep, व्योम *objp)
अणु
	निश्चित(objp);
	uatomic_dec(&nr_allocated);
	अगर (kदो_स्मृति_verbose)
		म_लिखो("Freeing %p to slab\n", objp);
	pthपढ़ो_mutex_lock(&cachep->lock);
	अगर (cachep->nr_objs > 10 || cachep->align) अणु
		स_रखो(objp, POISON_FREE, cachep->size);
		मुक्त(objp);
	पूर्ण अन्यथा अणु
		काष्ठा radix_tree_node *node = objp;
		cachep->nr_objs++;
		node->parent = cachep->objs;
		cachep->objs = node;
	पूर्ण
	pthपढ़ो_mutex_unlock(&cachep->lock);
पूर्ण

व्योम *kदो_स्मृति(माप_प्रकार size, gfp_t gfp)
अणु
	व्योम *ret;

	अगर (!(gfp & __GFP_सूचीECT_RECLAIM))
		वापस शून्य;

	ret = दो_स्मृति(size);
	uatomic_inc(&nr_allocated);
	अगर (kदो_स्मृति_verbose)
		म_लिखो("Allocating %p from malloc\n", ret);
	अगर (gfp & __GFP_ZERO)
		स_रखो(ret, 0, size);
	वापस ret;
पूर्ण

व्योम kमुक्त(व्योम *p)
अणु
	अगर (!p)
		वापस;
	uatomic_dec(&nr_allocated);
	अगर (kदो_स्मृति_verbose)
		म_लिखो("Freeing %p to malloc\n", p);
	मुक्त(p);
पूर्ण

काष्ठा kmem_cache *
kmem_cache_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक align,
		अचिन्हित पूर्णांक flags, व्योम (*ctor)(व्योम *))
अणु
	काष्ठा kmem_cache *ret = दो_स्मृति(माप(*ret));

	pthपढ़ो_mutex_init(&ret->lock, शून्य);
	ret->size = size;
	ret->align = align;
	ret->nr_objs = 0;
	ret->objs = शून्य;
	ret->ctor = ctor;
	वापस ret;
पूर्ण
