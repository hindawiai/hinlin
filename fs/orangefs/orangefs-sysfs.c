<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Documentation/ABI/stable/sysfs-fs-orangefs:
 *
 * What:		/sys/fs/orangefs/perf_counter_reset
 * Date:		June 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			echo a 0 or a 1 पूर्णांकo perf_counter_reset to
 * 			reset all the counters in
 * 			/sys/fs/orangefs/perf_counters
 * 			except ones with PINT_PERF_PRESERVE set.
 *
 *
 * What:		/sys/fs/orangefs/perf_counters/...
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Counters and settings क्रम various caches.
 * 			Read only.
 *
 *
 * What:		/sys/fs/orangefs/perf_समय_पूर्णांकerval_secs
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 *			Length of perf counter पूर्णांकervals in
 *			seconds.
 *
 *
 * What:		/sys/fs/orangefs/perf_history_size
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			The perf_counters cache statistics have N, or
 * 			perf_history_size, samples. The शेष is
 * 			one.
 *
 *			Every perf_समय_पूर्णांकerval_secs the (first)
 *			samples are reset.
 *
 *			If N is greater than one, the "current" set
 *			of samples is reset, and the samples from the
 *			other N-1 पूर्णांकervals reमुख्य available.
 *
 *
 * What:		/sys/fs/orangefs/op_समयout_secs
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 *			Service operation समयout in seconds.
 *
 *
 * What:		/sys/fs/orangefs/slot_समयout_secs
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 *			"Slot" समयout in seconds. A "slot"
 *			is an indexed buffer in the shared
 *			memory segment used क्रम communication
 *			between the kernel module and userspace.
 *			Slots are requested and रुकोed क्रम,
 *			the रुको बार out after slot_समयout_secs.
 *
 * What:		/sys/fs/orangefs/cache_समयout_msecs
 * Date:		Mar 2018
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Time in milliseconds between which
 *			orangefs_revalidate_mapping will invalidate the page
 *			cache.
 *
 * What:		/sys/fs/orangefs/dcache_समयout_msecs
 * Date:		Jul 2016
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Time lookup is valid in milliseconds.
 *
 * What:		/sys/fs/orangefs/getattr_समयout_msecs
 * Date:		Jul 2016
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Time getattr is valid in milliseconds.
 *
 * What:		/sys/fs/orangefs/पढ़ोahead_count
 * Date:		Aug 2016
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Readahead cache buffer count.
 *
 * What:		/sys/fs/orangefs/पढ़ोahead_size
 * Date:		Aug 2016
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Readahead cache buffer size.
 *
 * What:		/sys/fs/orangefs/पढ़ोahead_count_size
 * Date:		Aug 2016
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Readahead cache buffer count and size.
 *
 * What:		/sys/fs/orangefs/पढ़ोahead_पढ़ोcnt
 * Date:		Jan 2017
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 *			Number of buffers (in multiples of पढ़ोahead_size)
 *			which can be पढ़ो ahead क्रम a single file at once.
 *
 * What:		/sys/fs/orangefs/acache/...
 * Date:		Jun 2015
 * Contact:		Martin Bअक्रमenburg <martin@omnibond.com>
 * Description:
 * 			Attribute cache configurable settings.
 *
 *
 * What:		/sys/fs/orangefs/ncache/...
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Name cache configurable settings.
 *
 *
 * What:		/sys/fs/orangefs/capcache/...
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Capability cache configurable settings.
 *
 *
 * What:		/sys/fs/orangefs/ccache/...
 * Date:		Jun 2015
 * Contact:		Mike Marshall <hubcap@omnibond.com>
 * Description:
 * 			Credential cache configurable settings.
 *
 */

#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-sysfs.h"

#घोषणा ORANGEFS_KOBJ_ID "orangefs"
#घोषणा ACACHE_KOBJ_ID "acache"
#घोषणा CAPCACHE_KOBJ_ID "capcache"
#घोषणा CCACHE_KOBJ_ID "ccache"
#घोषणा NCACHE_KOBJ_ID "ncache"
#घोषणा PC_KOBJ_ID "pc"
#घोषणा STATS_KOBJ_ID "stats"

/*
 * Every item calls orangefs_attr_show and orangefs_attr_store through
 * orangefs_sysfs_ops. They look at the orangefs_attributes further below to
 * call one of sysfs_पूर्णांक_show, sysfs_पूर्णांक_store, sysfs_service_op_show, or
 * sysfs_service_op_store.
 */

काष्ठा orangefs_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा kobject *kobj,
			काष्ठा orangefs_attribute *attr,
			अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा kobject *kobj,
			 काष्ठा orangefs_attribute *attr,
			 स्थिर अक्षर *buf,
			 माप_प्रकार count);
पूर्ण;

अटल sमाप_प्रकार orangefs_attr_show(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा orangefs_attribute *attribute;

	attribute = container_of(attr, काष्ठा orangefs_attribute, attr);
	अगर (!attribute->show)
		वापस -EIO;
	वापस attribute->show(kobj, attribute, buf);
पूर्ण

अटल sमाप_प्रकार orangefs_attr_store(काष्ठा kobject *kobj,
				   काष्ठा attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार len)
अणु
	काष्ठा orangefs_attribute *attribute;

	अगर (!म_भेद(kobj->name, PC_KOBJ_ID) ||
	    !म_भेद(kobj->name, STATS_KOBJ_ID))
		वापस -EPERM;

	attribute = container_of(attr, काष्ठा orangefs_attribute, attr);
	अगर (!attribute->store)
		वापस -EIO;
	वापस attribute->store(kobj, attribute, buf, len);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops orangefs_sysfs_ops = अणु
	.show = orangefs_attr_show,
	.store = orangefs_attr_store,
पूर्ण;

अटल sमाप_प्रकार sysfs_पूर्णांक_show(काष्ठा kobject *kobj,
    काष्ठा orangefs_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc = -EIO;

	gossip_debug(GOSSIP_SYSFS_DEBUG, "sysfs_int_show: id:%s:\n",
	    kobj->name);

	अगर (!म_भेद(kobj->name, ORANGEFS_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "op_timeout_secs")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%d\n",
				       op_समयout_secs);
			जाओ out;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "slot_timeout_secs")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%d\n",
				       slot_समयout_secs);
			जाओ out;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "cache_timeout_msecs")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%d\n",
				       orangefs_cache_समयout_msecs);
			जाओ out;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "dcache_timeout_msecs")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%d\n",
				       orangefs_dcache_समयout_msecs);
			जाओ out;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "getattr_timeout_msecs")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%d\n",
				       orangefs_getattr_समयout_msecs);
			जाओ out;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, STATS_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "reads")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%lu\n",
				       orangefs_stats.पढ़ोs);
			जाओ out;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "writes")) अणु
			rc = scnम_लिखो(buf,
				       PAGE_SIZE,
				       "%lu\n",
				       orangefs_stats.ग_लिखोs);
			जाओ out;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण

out:

	वापस rc;
पूर्ण

अटल sमाप_प्रकार sysfs_पूर्णांक_store(काष्ठा kobject *kobj,
    काष्ठा orangefs_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc = 0;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_int_store: start attr->attr.name:%s: buf:%s:\n",
		     attr->attr.name, buf);

	अगर (!म_भेद(attr->attr.name, "op_timeout_secs")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &op_समयout_secs);
		जाओ out;
	पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "slot_timeout_secs")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &slot_समयout_secs);
		जाओ out;
	पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "cache_timeout_msecs")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &orangefs_cache_समयout_msecs);
		जाओ out;
	पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "dcache_timeout_msecs")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &orangefs_dcache_समयout_msecs);
		जाओ out;
	पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "getattr_timeout_msecs")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &orangefs_getattr_समयout_msecs);
		जाओ out;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

out:
	अगर (rc)
		rc = -EINVAL;
	अन्यथा
		rc = count;

	वापस rc;
पूर्ण

/*
 * obtain attribute values from userspace with a service operation.
 */
अटल sमाप_प्रकार sysfs_service_op_show(काष्ठा kobject *kobj,
    काष्ठा orangefs_attribute *attr, अक्षर *buf)
अणु
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	पूर्णांक rc = 0;
	अक्षर *ser_op_type = शून्य;
	__u32 op_alloc_type;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_service_op_show: id:%s:\n",
		     kobj->name);

	अगर (म_भेद(kobj->name, PC_KOBJ_ID))
		op_alloc_type = ORANGEFS_VFS_OP_PARAM;
	अन्यथा
		op_alloc_type = ORANGEFS_VFS_OP_PERF_COUNT;

	new_op = op_alloc(op_alloc_type);
	अगर (!new_op)
		वापस -ENOMEM;

	/* Can't करो a service_operation अगर the client is not running... */
	rc = is_daemon_in_service();
	अगर (rc) अणु
		pr_info_ratelimited("%s: Client not running :%d:\n",
			__func__,
			is_daemon_in_service());
		जाओ out;
	पूर्ण

	अगर (म_भेद(kobj->name, PC_KOBJ_ID))
		new_op->upcall.req.param.type = ORANGEFS_PARAM_REQUEST_GET;

	अगर (!म_भेद(kobj->name, ORANGEFS_KOBJ_ID)) अणु
		/* Drop unsupported requests first. */
		अगर (!(orangefs_features & ORANGEFS_FEATURE_READAHEAD) &&
		    (!म_भेद(attr->attr.name, "readahead_count") ||
		    !म_भेद(attr->attr.name, "readahead_size") ||
		    !म_भेद(attr->attr.name, "readahead_count_size") ||
		    !म_भेद(attr->attr.name, "readahead_readcnt"))) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!म_भेद(attr->attr.name, "perf_history_size"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_PERF_HISTORY_SIZE;
		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "perf_time_interval_secs"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_PERF_TIME_INTERVAL_SECS;
		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "perf_counter_reset"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_PERF_RESET;

		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "readahead_count"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT;

		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "readahead_size"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_SIZE;

		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "readahead_count_size"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT_SIZE;

		अन्यथा अगर (!म_भेद(attr->attr.name,
				 "readahead_readcnt"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_READCNT;
	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, ACACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "timeout_msecs"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_ACACHE_TIMEOUT_MSECS;

		अगर (!म_भेद(attr->attr.name, "hard_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_ACACHE_HARD_LIMIT;

		अगर (!म_भेद(attr->attr.name, "soft_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_ACACHE_SOFT_LIMIT;

		अगर (!म_भेद(attr->attr.name, "reclaim_percentage"))
			new_op->upcall.req.param.op =
			  ORANGEFS_PARAM_REQUEST_OP_ACACHE_RECLAIM_PERCENTAGE;

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, CAPCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "timeout_secs"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_TIMEOUT_SECS;

		अगर (!म_भेद(attr->attr.name, "hard_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_HARD_LIMIT;

		अगर (!म_भेद(attr->attr.name, "soft_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_SOFT_LIMIT;

		अगर (!म_भेद(attr->attr.name, "reclaim_percentage"))
			new_op->upcall.req.param.op =
			  ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_RECLAIM_PERCENTAGE;

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, CCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "timeout_secs"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CCACHE_TIMEOUT_SECS;

		अगर (!म_भेद(attr->attr.name, "hard_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CCACHE_HARD_LIMIT;

		अगर (!म_भेद(attr->attr.name, "soft_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_CCACHE_SOFT_LIMIT;

		अगर (!म_भेद(attr->attr.name, "reclaim_percentage"))
			new_op->upcall.req.param.op =
			  ORANGEFS_PARAM_REQUEST_OP_CCACHE_RECLAIM_PERCENTAGE;

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, NCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "timeout_msecs"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_NCACHE_TIMEOUT_MSECS;

		अगर (!म_भेद(attr->attr.name, "hard_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_NCACHE_HARD_LIMIT;

		अगर (!म_भेद(attr->attr.name, "soft_limit"))
			new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_NCACHE_SOFT_LIMIT;

		अगर (!म_भेद(attr->attr.name, "reclaim_percentage"))
			new_op->upcall.req.param.op =
			  ORANGEFS_PARAM_REQUEST_OP_NCACHE_RECLAIM_PERCENTAGE;

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, PC_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, ACACHE_KOBJ_ID))
			new_op->upcall.req.perf_count.type =
				ORANGEFS_PERF_COUNT_REQUEST_ACACHE;

		अगर (!म_भेद(attr->attr.name, CAPCACHE_KOBJ_ID))
			new_op->upcall.req.perf_count.type =
				ORANGEFS_PERF_COUNT_REQUEST_CAPCACHE;

		अगर (!म_भेद(attr->attr.name, NCACHE_KOBJ_ID))
			new_op->upcall.req.perf_count.type =
				ORANGEFS_PERF_COUNT_REQUEST_NCACHE;

	पूर्ण अन्यथा अणु
		gossip_err("sysfs_service_op_show: unknown kobj_id:%s:\n",
			   kobj->name);
		rc = -EINVAL;
		जाओ out;
	पूर्ण


	अगर (म_भेद(kobj->name, PC_KOBJ_ID))
		ser_op_type = "orangefs_param";
	अन्यथा
		ser_op_type = "orangefs_perf_count";

	/*
	 * The service_operation will वापस an त्रुटि_सं वापस code on
	 * error, and zero on success.
	 */
	rc = service_operation(new_op, ser_op_type, ORANGEFS_OP_INTERRUPTIBLE);

out:
	अगर (!rc) अणु
		अगर (म_भेद(kobj->name, PC_KOBJ_ID)) अणु
			अगर (new_op->upcall.req.param.op ==
			    ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT_SIZE) अणु
				rc = scnम_लिखो(buf, PAGE_SIZE, "%d %d\n",
				    (पूर्णांक)new_op->करोwncall.resp.param.u.
				    value32[0],
				    (पूर्णांक)new_op->करोwncall.resp.param.u.
				    value32[1]);
			पूर्ण अन्यथा अणु
				rc = scnम_लिखो(buf, PAGE_SIZE, "%d\n",
				    (पूर्णांक)new_op->करोwncall.resp.param.u.value64);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = scnम_लिखो(
				buf,
				PAGE_SIZE,
				"%s",
				new_op->करोwncall.resp.perf_count.buffer);
		पूर्ण
	पूर्ण

	op_release(new_op);

	वापस rc;

पूर्ण

/*
 * pass attribute values back to userspace with a service operation.
 *
 * We have to करो a memory allocation, an माला_पूछो and a service operation.
 * And we have to evaluate what the user entered, to make sure the
 * value is within the range supported by the attribute. So, there's
 * a lot of वापस code checking and mapping going on here.
 *
 * We want to वापस 1 अगर we think everything went OK, and
 * EINVAL अगर not.
 */
अटल sमाप_प्रकार sysfs_service_op_store(काष्ठा kobject *kobj,
    काष्ठा orangefs_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	पूर्णांक val = 0;
	पूर्णांक rc = 0;

	gossip_debug(GOSSIP_SYSFS_DEBUG,
		     "sysfs_service_op_store: id:%s:\n",
		     kobj->name);

	new_op = op_alloc(ORANGEFS_VFS_OP_PARAM);
	अगर (!new_op)
		वापस -EINVAL; /* sic */

	/* Can't करो a service_operation अगर the client is not running... */
	rc = is_daemon_in_service();
	अगर (rc) अणु
		pr_info("%s: Client not running :%d:\n",
			__func__,
			is_daemon_in_service());
		जाओ out;
	पूर्ण

	/*
	 * The value we want to send back to userspace is in buf, unless this
	 * there are two parameters, which is specially handled below.
	 */
	अगर (म_भेद(kobj->name, ORANGEFS_KOBJ_ID) ||
	    म_भेद(attr->attr.name, "readahead_count_size")) अणु
		rc = kstrtoपूर्णांक(buf, 0, &val);
		अगर (rc)
			जाओ out;
	पूर्ण

	new_op->upcall.req.param.type = ORANGEFS_PARAM_REQUEST_SET;

	अगर (!म_भेद(kobj->name, ORANGEFS_KOBJ_ID)) अणु
		/* Drop unsupported requests first. */
		अगर (!(orangefs_features & ORANGEFS_FEATURE_READAHEAD) &&
		    (!म_भेद(attr->attr.name, "readahead_count") ||
		    !म_भेद(attr->attr.name, "readahead_size") ||
		    !म_भेद(attr->attr.name, "readahead_count_size") ||
		    !म_भेद(attr->attr.name, "readahead_readcnt"))) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!म_भेद(attr->attr.name, "perf_history_size")) अणु
			अगर (val > 0) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_PERF_HISTORY_SIZE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "perf_time_interval_secs")) अणु
			अगर (val > 0) अणु
				new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_PERF_TIME_INTERVAL_SECS;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "perf_counter_reset")) अणु
			अगर ((val == 0) || (val == 1)) अणु
				new_op->upcall.req.param.op =
					ORANGEFS_PARAM_REQUEST_OP_PERF_RESET;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "readahead_count")) अणु
			अगर ((val >= 0)) अणु
				new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "readahead_size")) अणु
			अगर ((val >= 0)) अणु
				new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_SIZE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "readahead_count_size")) अणु
			पूर्णांक val1, val2;
			rc = माला_पूछो(buf, "%d %d", &val1, &val2);
			अगर (rc < 2) अणु
				rc = 0;
				जाओ out;
			पूर्ण
			अगर ((val1 >= 0) && (val2 >= 0)) अणु
				new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_COUNT_SIZE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
			new_op->upcall.req.param.u.value32[0] = val1;
			new_op->upcall.req.param.u.value32[1] = val2;
			जाओ value_set;
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "readahead_readcnt")) अणु
			अगर ((val >= 0)) अणु
				new_op->upcall.req.param.op =
				ORANGEFS_PARAM_REQUEST_OP_READAHEAD_READCNT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, ACACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "hard_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_ACACHE_HARD_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "soft_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_ACACHE_SOFT_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "reclaim_percentage")) अणु
			अगर ((val > -1) && (val < 101)) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_ACACHE_RECLAIM_PERCENTAGE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "timeout_msecs")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_ACACHE_TIMEOUT_MSECS;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, CAPCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "hard_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_HARD_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "soft_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_SOFT_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "reclaim_percentage")) अणु
			अगर ((val > -1) && (val < 101)) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_RECLAIM_PERCENTAGE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "timeout_secs")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CAPCACHE_TIMEOUT_SECS;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, CCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "hard_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CCACHE_HARD_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "soft_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CCACHE_SOFT_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "reclaim_percentage")) अणु
			अगर ((val > -1) && (val < 101)) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CCACHE_RECLAIM_PERCENTAGE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "timeout_secs")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_CCACHE_TIMEOUT_SECS;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (!म_भेद(kobj->name, NCACHE_KOBJ_ID)) अणु
		अगर (!म_भेद(attr->attr.name, "hard_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_NCACHE_HARD_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "soft_limit")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_NCACHE_SOFT_LIMIT;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name,
				   "reclaim_percentage")) अणु
			अगर ((val > -1) && (val < 101)) अणु
				new_op->upcall.req.param.op =
					ORANGEFS_PARAM_REQUEST_OP_NCACHE_RECLAIM_PERCENTAGE;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(attr->attr.name, "timeout_msecs")) अणु
			अगर (val > -1) अणु
				new_op->upcall.req.param.op =
				  ORANGEFS_PARAM_REQUEST_OP_NCACHE_TIMEOUT_MSECS;
			पूर्ण अन्यथा अणु
				rc = 0;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		gossip_err("sysfs_service_op_store: unknown kobj_id:%s:\n",
			   kobj->name);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	new_op->upcall.req.param.u.value64 = val;
value_set:

	/*
	 * The service_operation will वापस a त्रुटि_सं वापस code on
	 * error, and zero on success.
	 */
	rc = service_operation(new_op, "orangefs_param", ORANGEFS_OP_INTERRUPTIBLE);

	अगर (rc < 0) अणु
		gossip_err("sysfs_service_op_store: service op returned:%d:\n",
			rc);
		rc = 0;
	पूर्ण अन्यथा अणु
		rc = count;
	पूर्ण

out:
	op_release(new_op);

	अगर (rc == -ENOMEM || rc == 0)
		rc = -EINVAL;

	वापस rc;
पूर्ण

अटल काष्ठा orangefs_attribute op_समयout_secs_attribute =
	__ATTR(op_समयout_secs, 0664, sysfs_पूर्णांक_show, sysfs_पूर्णांक_store);

अटल काष्ठा orangefs_attribute slot_समयout_secs_attribute =
	__ATTR(slot_समयout_secs, 0664, sysfs_पूर्णांक_show, sysfs_पूर्णांक_store);

अटल काष्ठा orangefs_attribute cache_समयout_msecs_attribute =
	__ATTR(cache_समयout_msecs, 0664, sysfs_पूर्णांक_show, sysfs_पूर्णांक_store);

अटल काष्ठा orangefs_attribute dcache_समयout_msecs_attribute =
	__ATTR(dcache_समयout_msecs, 0664, sysfs_पूर्णांक_show, sysfs_पूर्णांक_store);

अटल काष्ठा orangefs_attribute getattr_समयout_msecs_attribute =
	__ATTR(getattr_समयout_msecs, 0664, sysfs_पूर्णांक_show, sysfs_पूर्णांक_store);

अटल काष्ठा orangefs_attribute पढ़ोahead_count_attribute =
	__ATTR(पढ़ोahead_count, 0664, sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute पढ़ोahead_size_attribute =
	__ATTR(पढ़ोahead_size, 0664, sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute पढ़ोahead_count_size_attribute =
	__ATTR(पढ़ोahead_count_size, 0664, sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute पढ़ोahead_पढ़ोcnt_attribute =
	__ATTR(पढ़ोahead_पढ़ोcnt, 0664, sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute perf_counter_reset_attribute =
	__ATTR(perf_counter_reset,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute perf_history_size_attribute =
	__ATTR(perf_history_size,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute perf_समय_पूर्णांकerval_secs_attribute =
	__ATTR(perf_समय_पूर्णांकerval_secs,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा attribute *orangefs_शेष_attrs[] = अणु
	&op_समयout_secs_attribute.attr,
	&slot_समयout_secs_attribute.attr,
	&cache_समयout_msecs_attribute.attr,
	&dcache_समयout_msecs_attribute.attr,
	&getattr_समयout_msecs_attribute.attr,
	&पढ़ोahead_count_attribute.attr,
	&पढ़ोahead_size_attribute.attr,
	&पढ़ोahead_count_size_attribute.attr,
	&पढ़ोahead_पढ़ोcnt_attribute.attr,
	&perf_counter_reset_attribute.attr,
	&perf_history_size_attribute.attr,
	&perf_समय_पूर्णांकerval_secs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute acache_hard_limit_attribute =
	__ATTR(hard_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute acache_reclaim_percent_attribute =
	__ATTR(reclaim_percentage,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute acache_soft_limit_attribute =
	__ATTR(soft_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute acache_समयout_msecs_attribute =
	__ATTR(समयout_msecs,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा attribute *acache_orangefs_शेष_attrs[] = अणु
	&acache_hard_limit_attribute.attr,
	&acache_reclaim_percent_attribute.attr,
	&acache_soft_limit_attribute.attr,
	&acache_समयout_msecs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type acache_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = acache_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute capcache_hard_limit_attribute =
	__ATTR(hard_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute capcache_reclaim_percent_attribute =
	__ATTR(reclaim_percentage,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute capcache_soft_limit_attribute =
	__ATTR(soft_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute capcache_समयout_secs_attribute =
	__ATTR(समयout_secs,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा attribute *capcache_orangefs_शेष_attrs[] = अणु
	&capcache_hard_limit_attribute.attr,
	&capcache_reclaim_percent_attribute.attr,
	&capcache_soft_limit_attribute.attr,
	&capcache_समयout_secs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type capcache_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = capcache_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute ccache_hard_limit_attribute =
	__ATTR(hard_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ccache_reclaim_percent_attribute =
	__ATTR(reclaim_percentage,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ccache_soft_limit_attribute =
	__ATTR(soft_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ccache_समयout_secs_attribute =
	__ATTR(समयout_secs,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा attribute *ccache_orangefs_शेष_attrs[] = अणु
	&ccache_hard_limit_attribute.attr,
	&ccache_reclaim_percent_attribute.attr,
	&ccache_soft_limit_attribute.attr,
	&ccache_समयout_secs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type ccache_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = ccache_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute ncache_hard_limit_attribute =
	__ATTR(hard_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ncache_reclaim_percent_attribute =
	__ATTR(reclaim_percentage,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ncache_soft_limit_attribute =
	__ATTR(soft_limit,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा orangefs_attribute ncache_समयout_msecs_attribute =
	__ATTR(समयout_msecs,
	       0664,
	       sysfs_service_op_show,
	       sysfs_service_op_store);

अटल काष्ठा attribute *ncache_orangefs_शेष_attrs[] = अणु
	&ncache_hard_limit_attribute.attr,
	&ncache_reclaim_percent_attribute.attr,
	&ncache_soft_limit_attribute.attr,
	&ncache_समयout_msecs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type ncache_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = ncache_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute pc_acache_attribute =
	__ATTR(acache,
	       0664,
	       sysfs_service_op_show,
	       शून्य);

अटल काष्ठा orangefs_attribute pc_capcache_attribute =
	__ATTR(capcache,
	       0664,
	       sysfs_service_op_show,
	       शून्य);

अटल काष्ठा orangefs_attribute pc_ncache_attribute =
	__ATTR(ncache,
	       0664,
	       sysfs_service_op_show,
	       शून्य);

अटल काष्ठा attribute *pc_orangefs_शेष_attrs[] = अणु
	&pc_acache_attribute.attr,
	&pc_capcache_attribute.attr,
	&pc_ncache_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type pc_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = pc_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा orangefs_attribute stats_पढ़ोs_attribute =
	__ATTR(पढ़ोs,
	       0664,
	       sysfs_पूर्णांक_show,
	       शून्य);

अटल काष्ठा orangefs_attribute stats_ग_लिखोs_attribute =
	__ATTR(ग_लिखोs,
	       0664,
	       sysfs_पूर्णांक_show,
	       शून्य);

अटल काष्ठा attribute *stats_orangefs_शेष_attrs[] = अणु
	&stats_पढ़ोs_attribute.attr,
	&stats_ग_लिखोs_attribute.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type stats_orangefs_ktype = अणु
	.sysfs_ops = &orangefs_sysfs_ops,
	.शेष_attrs = stats_orangefs_शेष_attrs,
पूर्ण;

अटल काष्ठा kobject *orangefs_obj;
अटल काष्ठा kobject *acache_orangefs_obj;
अटल काष्ठा kobject *capcache_orangefs_obj;
अटल काष्ठा kobject *ccache_orangefs_obj;
अटल काष्ठा kobject *ncache_orangefs_obj;
अटल काष्ठा kobject *pc_orangefs_obj;
अटल काष्ठा kobject *stats_orangefs_obj;

पूर्णांक orangefs_sysfs_init(व्योम)
अणु
	पूर्णांक rc = -EINVAL;

	gossip_debug(GOSSIP_SYSFS_DEBUG, "orangefs_sysfs_init: start\n");

	/* create /sys/fs/orangefs. */
	orangefs_obj = kzalloc(माप(*orangefs_obj), GFP_KERNEL);
	अगर (!orangefs_obj)
		जाओ out;

	rc = kobject_init_and_add(orangefs_obj,
				  &orangefs_ktype,
				  fs_kobj,
				  ORANGEFS_KOBJ_ID);

	अगर (rc)
		जाओ ofs_obj_bail;

	kobject_uevent(orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/acache. */
	acache_orangefs_obj = kzalloc(माप(*acache_orangefs_obj), GFP_KERNEL);
	अगर (!acache_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ ofs_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(acache_orangefs_obj,
				  &acache_orangefs_ktype,
				  orangefs_obj,
				  ACACHE_KOBJ_ID);

	अगर (rc)
		जाओ acache_obj_bail;

	kobject_uevent(acache_orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/capcache. */
	capcache_orangefs_obj =
		kzalloc(माप(*capcache_orangefs_obj), GFP_KERNEL);
	अगर (!capcache_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ acache_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(capcache_orangefs_obj,
				  &capcache_orangefs_ktype,
				  orangefs_obj,
				  CAPCACHE_KOBJ_ID);
	अगर (rc)
		जाओ capcache_obj_bail;

	kobject_uevent(capcache_orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/ccache. */
	ccache_orangefs_obj =
		kzalloc(माप(*ccache_orangefs_obj), GFP_KERNEL);
	अगर (!ccache_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ capcache_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(ccache_orangefs_obj,
				  &ccache_orangefs_ktype,
				  orangefs_obj,
				  CCACHE_KOBJ_ID);
	अगर (rc)
		जाओ ccache_obj_bail;

	kobject_uevent(ccache_orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/ncache. */
	ncache_orangefs_obj = kzalloc(माप(*ncache_orangefs_obj), GFP_KERNEL);
	अगर (!ncache_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ ccache_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(ncache_orangefs_obj,
				  &ncache_orangefs_ktype,
				  orangefs_obj,
				  NCACHE_KOBJ_ID);

	अगर (rc)
		जाओ ncache_obj_bail;

	kobject_uevent(ncache_orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/perf_counters. */
	pc_orangefs_obj = kzalloc(माप(*pc_orangefs_obj), GFP_KERNEL);
	अगर (!pc_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ ncache_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(pc_orangefs_obj,
				  &pc_orangefs_ktype,
				  orangefs_obj,
				  "perf_counters");

	अगर (rc)
		जाओ pc_obj_bail;

	kobject_uevent(pc_orangefs_obj, KOBJ_ADD);

	/* create /sys/fs/orangefs/stats. */
	stats_orangefs_obj = kzalloc(माप(*stats_orangefs_obj), GFP_KERNEL);
	अगर (!stats_orangefs_obj) अणु
		rc = -EINVAL;
		जाओ pc_obj_bail;
	पूर्ण

	rc = kobject_init_and_add(stats_orangefs_obj,
				  &stats_orangefs_ktype,
				  orangefs_obj,
				  STATS_KOBJ_ID);

	अगर (rc)
		जाओ stats_obj_bail;

	kobject_uevent(stats_orangefs_obj, KOBJ_ADD);
	जाओ out;

stats_obj_bail:
		kobject_put(stats_orangefs_obj);
pc_obj_bail:
		kobject_put(pc_orangefs_obj);
ncache_obj_bail:
		kobject_put(ncache_orangefs_obj);
ccache_obj_bail:
		kobject_put(ccache_orangefs_obj);
capcache_obj_bail:
		kobject_put(capcache_orangefs_obj);
acache_obj_bail:
		kobject_put(acache_orangefs_obj);
ofs_obj_bail:
		kobject_put(orangefs_obj);
out:
	वापस rc;
पूर्ण

व्योम orangefs_sysfs_निकास(व्योम)
अणु
	gossip_debug(GOSSIP_SYSFS_DEBUG, "orangefs_sysfs_exit: start\n");
	kobject_put(acache_orangefs_obj);
	kobject_put(capcache_orangefs_obj);
	kobject_put(ccache_orangefs_obj);
	kobject_put(ncache_orangefs_obj);
	kobject_put(pc_orangefs_obj);
	kobject_put(stats_orangefs_obj);
	kobject_put(orangefs_obj);
पूर्ण
