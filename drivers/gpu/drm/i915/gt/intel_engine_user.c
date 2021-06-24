<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/list.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/llist.h>

#समावेश "i915_drv.h"
#समावेश "intel_engine.h"
#समावेश "intel_engine_user.h"
#समावेश "intel_gt.h"

काष्ठा पूर्णांकel_engine_cs *
पूर्णांकel_engine_lookup_user(काष्ठा drm_i915_निजी *i915, u8 class, u8 instance)
अणु
	काष्ठा rb_node *p = i915->uabi_engines.rb_node;

	जबतक (p) अणु
		काष्ठा पूर्णांकel_engine_cs *it =
			rb_entry(p, typeof(*it), uabi_node);

		अगर (class < it->uabi_class)
			p = p->rb_left;
		अन्यथा अगर (class > it->uabi_class ||
			 instance > it->uabi_instance)
			p = p->rb_right;
		अन्यथा अगर (instance < it->uabi_instance)
			p = p->rb_left;
		अन्यथा
			वापस it;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम पूर्णांकel_engine_add_user(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	llist_add((काष्ठा llist_node *)&engine->uabi_node,
		  (काष्ठा llist_head *)&engine->i915->uabi_engines);
पूर्ण

अटल स्थिर u8 uabi_classes[] = अणु
	[RENDER_CLASS] = I915_ENGINE_CLASS_RENDER,
	[COPY_ENGINE_CLASS] = I915_ENGINE_CLASS_COPY,
	[VIDEO_DECODE_CLASS] = I915_ENGINE_CLASS_VIDEO,
	[VIDEO_ENHANCEMENT_CLASS] = I915_ENGINE_CLASS_VIDEO_ENHANCE,
पूर्ण;

अटल पूर्णांक engine_cmp(व्योम *priv, स्थिर काष्ठा list_head *A,
		      स्थिर काष्ठा list_head *B)
अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *a =
		container_of((काष्ठा rb_node *)A, typeof(*a), uabi_node);
	स्थिर काष्ठा पूर्णांकel_engine_cs *b =
		container_of((काष्ठा rb_node *)B, typeof(*b), uabi_node);

	अगर (uabi_classes[a->class] < uabi_classes[b->class])
		वापस -1;
	अगर (uabi_classes[a->class] > uabi_classes[b->class])
		वापस 1;

	अगर (a->instance < b->instance)
		वापस -1;
	अगर (a->instance > b->instance)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा llist_node *get_engines(काष्ठा drm_i915_निजी *i915)
अणु
	वापस llist_del_all((काष्ठा llist_head *)&i915->uabi_engines);
पूर्ण

अटल व्योम sort_engines(काष्ठा drm_i915_निजी *i915,
			 काष्ठा list_head *engines)
अणु
	काष्ठा llist_node *pos, *next;

	llist_क्रम_each_safe(pos, next, get_engines(i915)) अणु
		काष्ठा पूर्णांकel_engine_cs *engine =
			container_of((काष्ठा rb_node *)pos, typeof(*engine),
				     uabi_node);
		list_add((काष्ठा list_head *)&engine->uabi_node, engines);
	पूर्ण
	list_sort(शून्य, engines, engine_cmp);
पूर्ण

अटल व्योम set_scheduler_caps(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा अणु
		u8 engine;
		u8 sched;
	पूर्ण map[] = अणु
#घोषणा MAP(x, y) अणु ilog2(I915_ENGINE_##x), ilog2(I915_SCHEDULER_CAP_##y) पूर्ण
		MAP(HAS_PREEMPTION, PREEMPTION),
		MAP(HAS_SEMAPHORES, SEMAPHORES),
		MAP(SUPPORTS_STATS, ENGINE_BUSY_STATS),
#अघोषित MAP
	पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine;
	u32 enabled, disabled;

	enabled = 0;
	disabled = 0;
	क्रम_each_uabi_engine(engine, i915) अणु /* all engines must agree! */
		पूर्णांक i;

		अगर (engine->schedule)
			enabled |= (I915_SCHEDULER_CAP_ENABLED |
				    I915_SCHEDULER_CAP_PRIORITY);
		अन्यथा
			disabled |= (I915_SCHEDULER_CAP_ENABLED |
				     I915_SCHEDULER_CAP_PRIORITY);

		क्रम (i = 0; i < ARRAY_SIZE(map); i++) अणु
			अगर (engine->flags & BIT(map[i].engine))
				enabled |= BIT(map[i].sched);
			अन्यथा
				disabled |= BIT(map[i].sched);
		पूर्ण
	पूर्ण

	i915->caps.scheduler = enabled & ~disabled;
	अगर (!(i915->caps.scheduler & I915_SCHEDULER_CAP_ENABLED))
		i915->caps.scheduler = 0;
पूर्ण

स्थिर अक्षर *पूर्णांकel_engine_class_repr(u8 class)
अणु
	अटल स्थिर अक्षर * स्थिर uabi_names[] = अणु
		[RENDER_CLASS] = "rcs",
		[COPY_ENGINE_CLASS] = "bcs",
		[VIDEO_DECODE_CLASS] = "vcs",
		[VIDEO_ENHANCEMENT_CLASS] = "vecs",
	पूर्ण;

	अगर (class >= ARRAY_SIZE(uabi_names) || !uabi_names[class])
		वापस "xxx";

	वापस uabi_names[class];
पूर्ण

काष्ठा legacy_ring अणु
	काष्ठा पूर्णांकel_gt *gt;
	u8 class;
	u8 instance;
पूर्ण;

अटल पूर्णांक legacy_ring_idx(स्थिर काष्ठा legacy_ring *ring)
अणु
	अटल स्थिर काष्ठा अणु
		u8 base, max;
	पूर्ण map[] = अणु
		[RENDER_CLASS] = अणु RCS0, 1 पूर्ण,
		[COPY_ENGINE_CLASS] = अणु BCS0, 1 पूर्ण,
		[VIDEO_DECODE_CLASS] = अणु VCS0, I915_MAX_VCS पूर्ण,
		[VIDEO_ENHANCEMENT_CLASS] = अणु VECS0, I915_MAX_VECS पूर्ण,
	पूर्ण;

	अगर (GEM_DEBUG_WARN_ON(ring->class >= ARRAY_SIZE(map)))
		वापस INVALID_ENGINE;

	अगर (GEM_DEBUG_WARN_ON(ring->instance >= map[ring->class].max))
		वापस INVALID_ENGINE;

	वापस map[ring->class].base + ring->instance;
पूर्ण

अटल व्योम add_legacy_ring(काष्ठा legacy_ring *ring,
			    काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->gt != ring->gt || engine->class != ring->class) अणु
		ring->gt = engine->gt;
		ring->class = engine->class;
		ring->instance = 0;
	पूर्ण

	engine->legacy_idx = legacy_ring_idx(ring);
	अगर (engine->legacy_idx != INVALID_ENGINE)
		ring->instance++;
पूर्ण

व्योम पूर्णांकel_engines_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा legacy_ring ring = अणुपूर्ण;
	u8 uabi_instances[4] = अणुपूर्ण;
	काष्ठा list_head *it, *next;
	काष्ठा rb_node **p, *prev;
	LIST_HEAD(engines);

	sort_engines(i915, &engines);

	prev = शून्य;
	p = &i915->uabi_engines.rb_node;
	list_क्रम_each_safe(it, next, &engines) अणु
		काष्ठा पूर्णांकel_engine_cs *engine =
			container_of((काष्ठा rb_node *)it, typeof(*engine),
				     uabi_node);
		अक्षर old[माप(engine->name)];

		अगर (पूर्णांकel_gt_has_unrecoverable_error(engine->gt))
			जारी; /* ignore incomplete engines */

		GEM_BUG_ON(engine->class >= ARRAY_SIZE(uabi_classes));
		engine->uabi_class = uabi_classes[engine->class];

		GEM_BUG_ON(engine->uabi_class >= ARRAY_SIZE(uabi_instances));
		engine->uabi_instance = uabi_instances[engine->uabi_class]++;

		/* Replace the पूर्णांकernal name with the final user facing name */
		स_नकल(old, engine->name, माप(engine->name));
		scnम_लिखो(engine->name, माप(engine->name), "%s%u",
			  पूर्णांकel_engine_class_repr(engine->class),
			  engine->uabi_instance);
		DRM_DEBUG_DRIVER("renamed %s to %s\n", old, engine->name);

		rb_link_node(&engine->uabi_node, prev, p);
		rb_insert_color(&engine->uabi_node, &i915->uabi_engines);

		GEM_BUG_ON(पूर्णांकel_engine_lookup_user(i915,
						    engine->uabi_class,
						    engine->uabi_instance) != engine);

		/* Fix up the mapping to match शेष execbuf::user_map[] */
		add_legacy_ring(&ring, engine);

		prev = &engine->uabi_node;
		p = &prev->rb_right;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DRM_I915_SELFTESTS) &&
	    IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		अचिन्हित पूर्णांक isolation;
		पूर्णांक class, inst;
		पूर्णांक errors = 0;

		क्रम (class = 0; class < ARRAY_SIZE(uabi_instances); class++) अणु
			क्रम (inst = 0; inst < uabi_instances[class]; inst++) अणु
				engine = पूर्णांकel_engine_lookup_user(i915,
								  class, inst);
				अगर (!engine) अणु
					pr_err("UABI engine not found for { class:%d, instance:%d }\n",
					       class, inst);
					errors++;
					जारी;
				पूर्ण

				अगर (engine->uabi_class != class ||
				    engine->uabi_instance != inst) अणु
					pr_err("Wrong UABI engine:%s { class:%d, instance:%d } found for { class:%d, instance:%d }\n",
					       engine->name,
					       engine->uabi_class,
					       engine->uabi_instance,
					       class, inst);
					errors++;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * Make sure that classes with multiple engine instances all
		 * share the same basic configuration.
		 */
		isolation = पूर्णांकel_engines_has_context_isolation(i915);
		क्रम_each_uabi_engine(engine, i915) अणु
			अचिन्हित पूर्णांक bit = BIT(engine->uabi_class);
			अचिन्हित पूर्णांक expected = engine->शेष_state ? bit : 0;

			अगर ((isolation & bit) != expected) अणु
				pr_err("mismatching default context state for class %d on engine %s\n",
				       engine->uabi_class, engine->name);
				errors++;
			पूर्ण
		पूर्ण

		अगर (drm_WARN(&i915->drm, errors,
			     "Invalid UABI engine mapping found"))
			i915->uabi_engines = RB_ROOT;
	पूर्ण

	set_scheduler_caps(i915);
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_engines_has_context_isolation(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक which;

	which = 0;
	क्रम_each_uabi_engine(engine, i915)
		अगर (engine->शेष_state)
			which |= BIT(engine->uabi_class);

	वापस which;
पूर्ण
