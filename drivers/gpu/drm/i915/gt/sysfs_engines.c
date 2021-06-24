<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>

#समावेश "i915_drv.h"
#समावेश "intel_engine.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "sysfs_engines.h"

काष्ठा kobj_engine अणु
	काष्ठा kobject base;
	काष्ठा पूर्णांकel_engine_cs *engine;
पूर्ण;

अटल काष्ठा पूर्णांकel_engine_cs *kobj_to_engine(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा kobj_engine, base)->engine;
पूर्ण

अटल sमाप_प्रकार
name_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", kobj_to_engine(kobj)->name);
पूर्ण

अटल काष्ठा kobj_attribute name_attr =
__ATTR(name, 0444, name_show, शून्य);

अटल sमाप_प्रकार
class_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", kobj_to_engine(kobj)->uabi_class);
पूर्ण

अटल काष्ठा kobj_attribute class_attr =
__ATTR(class, 0444, class_show, शून्य);

अटल sमाप_प्रकार
inst_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", kobj_to_engine(kobj)->uabi_instance);
पूर्ण

अटल काष्ठा kobj_attribute inst_attr =
__ATTR(instance, 0444, inst_show, शून्य);

अटल sमाप_प्रकार
mmio_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%x\n", kobj_to_engine(kobj)->mmio_base);
पूर्ण

अटल काष्ठा kobj_attribute mmio_attr =
__ATTR(mmio_base, 0444, mmio_show, शून्य);

अटल स्थिर अक्षर * स्थिर vcs_caps[] = अणु
	[ilog2(I915_VIDEO_CLASS_CAPABILITY_HEVC)] = "hevc",
	[ilog2(I915_VIDEO_AND_ENHANCE_CLASS_CAPABILITY_SFC)] = "sfc",
पूर्ण;

अटल स्थिर अक्षर * स्थिर vecs_caps[] = अणु
	[ilog2(I915_VIDEO_AND_ENHANCE_CLASS_CAPABILITY_SFC)] = "sfc",
पूर्ण;

अटल sमाप_प्रकार repr_trim(अक्षर *buf, sमाप_प्रकार len)
अणु
	/* Trim off the trailing space and replace with a newline */
	अगर (len > PAGE_SIZE)
		len = PAGE_SIZE;
	अगर (len > 0)
		buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार
__caps_show(काष्ठा पूर्णांकel_engine_cs *engine,
	    अचिन्हित दीर्घ caps, अक्षर *buf, bool show_unknown)
अणु
	स्थिर अक्षर * स्थिर *repr;
	पूर्णांक count, n;
	sमाप_प्रकार len;

	चयन (engine->class) अणु
	हाल VIDEO_DECODE_CLASS:
		repr = vcs_caps;
		count = ARRAY_SIZE(vcs_caps);
		अवरोध;

	हाल VIDEO_ENHANCEMENT_CLASS:
		repr = vecs_caps;
		count = ARRAY_SIZE(vecs_caps);
		अवरोध;

	शेष:
		repr = शून्य;
		count = 0;
		अवरोध;
	पूर्ण
	GEM_BUG_ON(count > BITS_PER_LONG);

	len = 0;
	क्रम_each_set_bit(n, &caps, show_unknown ? BITS_PER_LONG : count) अणु
		अगर (n >= count || !repr[n]) अणु
			अगर (GEM_WARN_ON(show_unknown))
				len += snम_लिखो(buf + len, PAGE_SIZE - len,
						"[%x] ", n);
		पूर्ण अन्यथा अणु
			len += snम_लिखो(buf + len, PAGE_SIZE - len,
					"%s ", repr[n]);
		पूर्ण
		अगर (GEM_WARN_ON(len >= PAGE_SIZE))
			अवरोध;
	पूर्ण
	वापस repr_trim(buf, len);
पूर्ण

अटल sमाप_प्रकार
caps_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस __caps_show(engine, engine->uabi_capabilities, buf, true);
पूर्ण

अटल काष्ठा kobj_attribute caps_attr =
__ATTR(capabilities, 0444, caps_show, शून्य);

अटल sमाप_प्रकार
all_caps_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस __caps_show(kobj_to_engine(kobj), -1, buf, false);
पूर्ण

अटल काष्ठा kobj_attribute all_caps_attr =
__ATTR(known_capabilities, 0444, all_caps_show, शून्य);

अटल sमाप_प्रकार
max_spin_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	/*
	 * When रुकोing क्रम a request, अगर is it currently being executed
	 * on the GPU, we busyरुको क्रम a लघु जबतक beक्रमe sleeping. The
	 * premise is that most requests are लघु, and अगर it is alपढ़ोy
	 * executing then there is a good chance that it will complete
	 * beक्रमe we can setup the पूर्णांकerrupt handler and go to sleep.
	 * We try to offset the cost of going to sleep, by first spinning
	 * on the request -- अगर it completed in less समय than it would take
	 * to go sleep, process the पूर्णांकerrupt and वापस back to the client,
	 * then we have saved the client some latency, albeit at the cost
	 * of spinning on an expensive CPU core.
	 *
	 * While we try to aव्योम रुकोing at all क्रम a request that is unlikely
	 * to complete, deciding how दीर्घ it is worth spinning is क्रम is an
	 * arbitrary decision: trading off घातer vs latency.
	 */

	err = kम_से_अदीर्घl(buf, 0, &duration);
	अगर (err)
		वापस err;

	अगर (duration > jअगरfies_to_nsecs(2))
		वापस -EINVAL;

	WRITE_ONCE(engine->props.max_busyरुको_duration_ns, duration);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
max_spin_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->props.max_busyरुको_duration_ns);
पूर्ण

अटल काष्ठा kobj_attribute max_spin_attr =
__ATTR(max_busyरुको_duration_ns, 0644, max_spin_show, max_spin_store);

अटल sमाप_प्रकार
max_spin_शेष(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->शेषs.max_busyरुको_duration_ns);
पूर्ण

अटल काष्ठा kobj_attribute max_spin_def =
__ATTR(max_busyरुको_duration_ns, 0444, max_spin_शेष, शून्य);

अटल sमाप_प्रकार
बारlice_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	/*
	 * Execlists uses a scheduling quantum (a बारlice) to alternate
	 * execution between पढ़ोy-to-run contexts of equal priority. This
	 * ensures that all users (though only अगर they of equal importance)
	 * have the opportunity to run and prevents livelocks where contexts
	 * may have implicit ordering due to userspace semaphores.
	 */

	err = kम_से_अदीर्घl(buf, 0, &duration);
	अगर (err)
		वापस err;

	अगर (duration > jअगरfies_to_msecs(MAX_SCHEDULE_TIMEOUT))
		वापस -EINVAL;

	WRITE_ONCE(engine->props.बारlice_duration_ms, duration);

	अगर (execlists_active(&engine->execlists))
		set_समयr_ms(&engine->execlists.समयr, duration);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
बारlice_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->props.बारlice_duration_ms);
पूर्ण

अटल काष्ठा kobj_attribute बारlice_duration_attr =
__ATTR(बारlice_duration_ms, 0644, बारlice_show, बारlice_store);

अटल sमाप_प्रकार
बारlice_शेष(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->शेषs.बारlice_duration_ms);
पूर्ण

अटल काष्ठा kobj_attribute बारlice_duration_def =
__ATTR(बारlice_duration_ms, 0444, बारlice_शेष, शून्य);

अटल sमाप_प्रकार
stop_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);
	अचिन्हित दीर्घ दीर्घ duration;
	पूर्णांक err;

	/*
	 * When we allow ourselves to sleep beक्रमe a GPU reset after disabling
	 * submission, even क्रम a few milliseconds, gives an innocent context
	 * the opportunity to clear the GPU beक्रमe the reset occurs. However,
	 * how दीर्घ to sleep depends on the typical non-preemptible duration
	 * (a similar problem to determining the ideal preempt-reset समयout
	 * or even the heartbeat पूर्णांकerval).
	 */

	err = kम_से_अदीर्घl(buf, 0, &duration);
	अगर (err)
		वापस err;

	अगर (duration > jअगरfies_to_msecs(MAX_SCHEDULE_TIMEOUT))
		वापस -EINVAL;

	WRITE_ONCE(engine->props.stop_समयout_ms, duration);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
stop_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->props.stop_समयout_ms);
पूर्ण

अटल काष्ठा kobj_attribute stop_समयout_attr =
__ATTR(stop_समयout_ms, 0644, stop_show, stop_store);

अटल sमाप_प्रकार
stop_शेष(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->शेषs.stop_समयout_ms);
पूर्ण

अटल काष्ठा kobj_attribute stop_समयout_def =
__ATTR(stop_समयout_ms, 0444, stop_शेष, शून्य);

अटल sमाप_प्रकार
preempt_समयout_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);
	अचिन्हित दीर्घ दीर्घ समयout;
	पूर्णांक err;

	/*
	 * After initialising a preemption request, we give the current
	 * resident a small amount of समय to vacate the GPU. The preemption
	 * request is क्रम a higher priority context and should be immediate to
	 * मुख्यtain high quality of service (and aव्योम priority inversion).
	 * However, the preemption granularity of the GPU can be quite coarse
	 * and so we need a compromise.
	 */

	err = kम_से_अदीर्घl(buf, 0, &समयout);
	अगर (err)
		वापस err;

	अगर (समयout > jअगरfies_to_msecs(MAX_SCHEDULE_TIMEOUT))
		वापस -EINVAL;

	WRITE_ONCE(engine->props.preempt_समयout_ms, समयout);

	अगर (READ_ONCE(engine->execlists.pending[0]))
		set_समयr_ms(&engine->execlists.preempt, समयout);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
preempt_समयout_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->props.preempt_समयout_ms);
पूर्ण

अटल काष्ठा kobj_attribute preempt_समयout_attr =
__ATTR(preempt_समयout_ms, 0644, preempt_समयout_show, preempt_समयout_store);

अटल sमाप_प्रकार
preempt_समयout_शेष(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->शेषs.preempt_समयout_ms);
पूर्ण

अटल काष्ठा kobj_attribute preempt_समयout_def =
__ATTR(preempt_समयout_ms, 0444, preempt_समयout_शेष, शून्य);

अटल sमाप_प्रकार
heartbeat_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);
	अचिन्हित दीर्घ दीर्घ delay;
	पूर्णांक err;

	/*
	 * We monitor the health of the प्रणाली via periodic heartbeat pulses.
	 * The pulses also provide the opportunity to perक्रमm garbage
	 * collection.  However, we पूर्णांकerpret an incomplete pulse (a missed
	 * heartbeat) as an indication that the प्रणाली is no दीर्घer responsive,
	 * i.e. hung, and perक्रमm an engine or full GPU reset. Given that the
	 * preemption granularity can be very coarse on a प्रणाली, the optimal
	 * value क्रम any workload is unknowable!
	 */

	err = kम_से_अदीर्घl(buf, 0, &delay);
	अगर (err)
		वापस err;

	अगर (delay >= jअगरfies_to_msecs(MAX_SCHEDULE_TIMEOUT))
		वापस -EINVAL;

	err = पूर्णांकel_engine_set_heartbeat(engine, delay);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
heartbeat_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->props.heartbeat_पूर्णांकerval_ms);
पूर्ण

अटल काष्ठा kobj_attribute heartbeat_पूर्णांकerval_attr =
__ATTR(heartbeat_पूर्णांकerval_ms, 0644, heartbeat_show, heartbeat_store);

अटल sमाप_प्रकार
heartbeat_शेष(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = kobj_to_engine(kobj);

	वापस प्र_लिखो(buf, "%lu\n", engine->शेषs.heartbeat_पूर्णांकerval_ms);
पूर्ण

अटल काष्ठा kobj_attribute heartbeat_पूर्णांकerval_def =
__ATTR(heartbeat_पूर्णांकerval_ms, 0444, heartbeat_शेष, शून्य);

अटल व्योम kobj_engine_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल काष्ठा kobj_type kobj_engine_type = अणु
	.release = kobj_engine_release,
	.sysfs_ops = &kobj_sysfs_ops
पूर्ण;

अटल काष्ठा kobject *
kobj_engine(काष्ठा kobject *dir, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा kobj_engine *ke;

	ke = kzalloc(माप(*ke), GFP_KERNEL);
	अगर (!ke)
		वापस शून्य;

	kobject_init(&ke->base, &kobj_engine_type);
	ke->engine = engine;

	अगर (kobject_add(&ke->base, dir, "%s", engine->name)) अणु
		kobject_put(&ke->base);
		वापस शून्य;
	पूर्ण

	/* xfer ownership to sysfs tree */
	वापस &ke->base;
पूर्ण

अटल व्योम add_शेषs(काष्ठा kobj_engine *parent)
अणु
	अटल स्थिर काष्ठा attribute *files[] = अणु
		&max_spin_def.attr,
		&stop_समयout_def.attr,
#अगर CONFIG_DRM_I915_HEARTBEAT_INTERVAL
		&heartbeat_पूर्णांकerval_def.attr,
#पूर्ण_अगर
		शून्य
	पूर्ण;
	काष्ठा kobj_engine *ke;

	ke = kzalloc(माप(*ke), GFP_KERNEL);
	अगर (!ke)
		वापस;

	kobject_init(&ke->base, &kobj_engine_type);
	ke->engine = parent->engine;

	अगर (kobject_add(&ke->base, &parent->base, "%s", ".defaults")) अणु
		kobject_put(&ke->base);
		वापस;
	पूर्ण

	अगर (sysfs_create_files(&ke->base, files))
		वापस;

	अगर (पूर्णांकel_engine_has_बारlices(ke->engine) &&
	    sysfs_create_file(&ke->base, &बारlice_duration_def.attr))
		वापस;

	अगर (पूर्णांकel_engine_has_preempt_reset(ke->engine) &&
	    sysfs_create_file(&ke->base, &preempt_समयout_def.attr))
		वापस;
पूर्ण

व्योम पूर्णांकel_engines_add_sysfs(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा attribute *files[] = अणु
		&name_attr.attr,
		&class_attr.attr,
		&inst_attr.attr,
		&mmio_attr.attr,
		&caps_attr.attr,
		&all_caps_attr.attr,
		&max_spin_attr.attr,
		&stop_समयout_attr.attr,
#अगर CONFIG_DRM_I915_HEARTBEAT_INTERVAL
		&heartbeat_पूर्णांकerval_attr.attr,
#पूर्ण_अगर
		शून्य
	पूर्ण;

	काष्ठा device *kdev = i915->drm.primary->kdev;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा kobject *dir;

	dir = kobject_create_and_add("engine", &kdev->kobj);
	अगर (!dir)
		वापस;

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा kobject *kobj;

		kobj = kobj_engine(dir, engine);
		अगर (!kobj)
			जाओ err_engine;

		अगर (sysfs_create_files(kobj, files))
			जाओ err_object;

		अगर (पूर्णांकel_engine_has_बारlices(engine) &&
		    sysfs_create_file(kobj, &बारlice_duration_attr.attr))
			जाओ err_engine;

		अगर (पूर्णांकel_engine_has_preempt_reset(engine) &&
		    sysfs_create_file(kobj, &preempt_समयout_attr.attr))
			जाओ err_engine;

		add_शेषs(container_of(kobj, काष्ठा kobj_engine, base));

		अगर (0) अणु
err_object:
			kobject_put(kobj);
err_engine:
			dev_err(kdev, "Failed to add sysfs engine '%s'\n",
				engine->name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
