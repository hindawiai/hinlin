<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote Processor Framework
 */

#समावेश <linux/remoteproc.h>
#समावेश <linux/slab.h>

#समावेश "remoteproc_internal.h"

#घोषणा to_rproc(d) container_of(d, काष्ठा rproc, dev)

अटल sमाप_प्रकार recovery_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);

	वापस sysfs_emit(buf, "%s", rproc->recovery_disabled ? "disabled\n" : "enabled\n");
पूर्ण

/*
 * By writing to the 'recovery' sysfs entry, we control the behavior of the
 * recovery mechanism dynamically. The शेष value of this entry is "enabled".
 *
 * The 'recovery' sysfs entry supports these commands:
 *
 * enabled:	When enabled, the remote processor will be स्वतःmatically
 *		recovered whenever it crashes. Moreover, अगर the remote
 *		processor crashes जबतक recovery is disabled, it will
 *		be स्वतःmatically recovered too as soon as recovery is enabled.
 *
 * disabled:	When disabled, a remote processor will reमुख्य in a crashed
 *		state अगर it crashes. This is useful क्रम debugging purposes;
 *		without it, debugging a crash is substantially harder.
 *
 * recover:	This function will trigger an immediate recovery अगर the
 *		remote processor is in a crashed state, without changing
 *		or checking the recovery state (enabled/disabled).
 *		This is useful during debugging sessions, when one expects
 *		additional crashes to happen after enabling recovery. In this
 *		हाल, enabling recovery will make it hard to debug subsequent
 *		crashes, so it's recommended to keep recovery disabled, and
 *		instead use the "recover" command as needed.
 */
अटल sमाप_प्रकार recovery_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);

	अगर (sysfs_streq(buf, "enabled")) अणु
		/* change the flag and begin the recovery process अगर needed */
		rproc->recovery_disabled = false;
		rproc_trigger_recovery(rproc);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "disabled")) अणु
		rproc->recovery_disabled = true;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "recover")) अणु
		/* begin the recovery process without changing the flag */
		rproc_trigger_recovery(rproc);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(recovery);

/*
 * A coredump-configuration-to-string lookup table, क्रम exposing a
 * human पढ़ोable configuration via sysfs. Always keep in sync with
 * क्रमागत rproc_coredump_mechanism
 */
अटल स्थिर अक्षर * स्थिर rproc_coredump_str[] = अणु
	[RPROC_COREDUMP_DISABLED]	= "disabled",
	[RPROC_COREDUMP_ENABLED]	= "enabled",
	[RPROC_COREDUMP_INLINE]		= "inline",
पूर्ण;

/* Expose the current coredump configuration via debugfs */
अटल sमाप_प्रकार coredump_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);

	वापस sysfs_emit(buf, "%s\n", rproc_coredump_str[rproc->dump_conf]);
पूर्ण

/*
 * By writing to the 'coredump' sysfs entry, we control the behavior of the
 * coredump mechanism dynamically. The शेष value of this entry is "default".
 *
 * The 'coredump' sysfs entry supports these commands:
 *
 * disabled:	This is the शेष coredump mechanism. Recovery will proceed
 *		without collecting any dump.
 *
 * शेष:	When the remoteproc crashes the entire coredump will be
 *		copied to a separate buffer and exposed to userspace.
 *
 * अंतरभूत:	The coredump will not be copied to a separate buffer and the
 *		recovery process will have to रुको until data is पढ़ो by
 *		userspace. But this aव्योम usage of extra memory.
 */
अटल sमाप_प्रकार coredump_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);

	अगर (rproc->state == RPROC_CRASHED) अणु
		dev_err(&rproc->dev, "can't change coredump configuration\n");
		वापस -EBUSY;
	पूर्ण

	अगर (sysfs_streq(buf, "disabled")) अणु
		rproc->dump_conf = RPROC_COREDUMP_DISABLED;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "enabled")) अणु
		rproc->dump_conf = RPROC_COREDUMP_ENABLED;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "inline")) अणु
		rproc->dump_conf = RPROC_COREDUMP_INLINE;
	पूर्ण अन्यथा अणु
		dev_err(&rproc->dev, "Invalid coredump configuration\n");
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(coredump);

/* Expose the loaded / running firmware name via sysfs */
अटल sमाप_प्रकार firmware_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);
	स्थिर अक्षर *firmware = rproc->firmware;

	/*
	 * If the remote processor has been started by an बाह्यal
	 * entity we have no idea of what image it is running.  As such
	 * simply display a generic string rather then rproc->firmware.
	 */
	अगर (rproc->state == RPROC_ATTACHED)
		firmware = "unknown";

	वापस प्र_लिखो(buf, "%s\n", firmware);
पूर्ण

/* Change firmware name via sysfs */
अटल sमाप_प्रकार firmware_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);
	पूर्णांक err;

	err = rproc_set_firmware(rproc, buf);

	वापस err ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(firmware);

/*
 * A state-to-string lookup table, क्रम exposing a human पढ़ोable state
 * via sysfs. Always keep in sync with क्रमागत rproc_state
 */
अटल स्थिर अक्षर * स्थिर rproc_state_string[] = अणु
	[RPROC_OFFLINE]		= "offline",
	[RPROC_SUSPENDED]	= "suspended",
	[RPROC_RUNNING]		= "running",
	[RPROC_CRASHED]		= "crashed",
	[RPROC_DELETED]		= "deleted",
	[RPROC_ATTACHED]	= "attached",
	[RPROC_DETACHED]	= "detached",
	[RPROC_LAST]		= "invalid",
पूर्ण;

/* Expose the state of the remote processor via sysfs */
अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);
	अचिन्हित पूर्णांक state;

	state = rproc->state > RPROC_LAST ? RPROC_LAST : rproc->state;
	वापस प्र_लिखो(buf, "%s\n", rproc_state_string[state]);
पूर्ण

/* Change remote processor state via sysfs */
अटल sमाप_प्रकार state_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);
	पूर्णांक ret = 0;

	अगर (sysfs_streq(buf, "start")) अणु
		अगर (rproc->state == RPROC_RUNNING ||
		    rproc->state == RPROC_ATTACHED)
			वापस -EBUSY;

		ret = rproc_boot(rproc);
		अगर (ret)
			dev_err(&rproc->dev, "Boot failed: %d\n", ret);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "stop")) अणु
		अगर (rproc->state != RPROC_RUNNING &&
		    rproc->state != RPROC_ATTACHED)
			वापस -EINVAL;

		rproc_shutकरोwn(rproc);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "detach")) अणु
		अगर (rproc->state != RPROC_ATTACHED)
			वापस -EINVAL;

		ret = rproc_detach(rproc);
	पूर्ण अन्यथा अणु
		dev_err(&rproc->dev, "Unrecognised option: %s\n", buf);
		ret = -EINVAL;
	पूर्ण
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(state);

/* Expose the name of the remote processor via sysfs */
अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rproc *rproc = to_rproc(dev);

	वापस प्र_लिखो(buf, "%s\n", rproc->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *rproc_attrs[] = अणु
	&dev_attr_coredump.attr,
	&dev_attr_recovery.attr,
	&dev_attr_firmware.attr,
	&dev_attr_state.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rproc_devgroup = अणु
	.attrs = rproc_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *rproc_devgroups[] = अणु
	&rproc_devgroup,
	शून्य
पूर्ण;

काष्ठा class rproc_class = अणु
	.name		= "remoteproc",
	.dev_groups	= rproc_devgroups,
पूर्ण;

पूर्णांक __init rproc_init_sysfs(व्योम)
अणु
	/* create remoteproc device class क्रम sysfs */
	पूर्णांक err = class_रेजिस्टर(&rproc_class);

	अगर (err)
		pr_err("remoteproc: unable to register class\n");
	वापस err;
पूर्ण

व्योम __निकास rproc_निकास_sysfs(व्योम)
अणु
	class_unरेजिस्टर(&rproc_class);
पूर्ण
