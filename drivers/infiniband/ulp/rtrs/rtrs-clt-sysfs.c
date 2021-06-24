<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश "rtrs-pri.h"
#समावेश "rtrs-clt.h"
#समावेश "rtrs-log.h"

#घोषणा MIN_MAX_RECONN_ATT -1
#घोषणा MAX_MAX_RECONN_ATT 9999

अटल व्योम rtrs_clt_sess_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);

	मुक्त_sess(sess);
पूर्ण

अटल काष्ठा kobj_type ktype_sess = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = rtrs_clt_sess_release
पूर्ण;

अटल व्योम rtrs_clt_sess_stats_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rtrs_clt_stats *stats;

	stats = container_of(kobj, काष्ठा rtrs_clt_stats, kobj_stats);

	मुक्त_percpu(stats->pcpu_stats);

	kमुक्त(stats);
पूर्ण

अटल काष्ठा kobj_type ktype_stats = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = rtrs_clt_sess_stats_release,
पूर्ण;

अटल sमाप_प्रकार max_reconnect_attempts_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *page)
अणु
	काष्ठा rtrs_clt *clt = container_of(dev, काष्ठा rtrs_clt, dev);

	वापस sysfs_emit(page, "%d\n",
			  rtrs_clt_get_max_reconnect_attempts(clt));
पूर्ण

अटल sमाप_प्रकार max_reconnect_attempts_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार count)
अणु
	पूर्णांक value;
	पूर्णांक ret;
	काष्ठा rtrs_clt *clt  = container_of(dev, काष्ठा rtrs_clt, dev);

	ret = kstrtoपूर्णांक(buf, 10, &value);
	अगर (ret) अणु
		rtrs_err(clt, "%s: failed to convert string '%s' to int\n",
			  attr->attr.name, buf);
		वापस ret;
	पूर्ण
	अगर (value > MAX_MAX_RECONN_ATT ||
		     value < MIN_MAX_RECONN_ATT) अणु
		rtrs_err(clt,
			  "%s: invalid range (provided: '%s', accepted: min: %d, max: %d)\n",
			  attr->attr.name, buf, MIN_MAX_RECONN_ATT,
			  MAX_MAX_RECONN_ATT);
		वापस -EINVAL;
	पूर्ण
	rtrs_clt_set_max_reconnect_attempts(clt, value);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(max_reconnect_attempts);

अटल sमाप_प्रकार mpath_policy_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *page)
अणु
	काष्ठा rtrs_clt *clt;

	clt = container_of(dev, काष्ठा rtrs_clt, dev);

	चयन (clt->mp_policy) अणु
	हाल MP_POLICY_RR:
		वापस sysfs_emit(page, "round-robin (RR: %d)\n",
				  clt->mp_policy);
	हाल MP_POLICY_MIN_INFLIGHT:
		वापस sysfs_emit(page, "min-inflight (MI: %d)\n",
				  clt->mp_policy);
	हाल MP_POLICY_MIN_LATENCY:
		वापस sysfs_emit(page, "min-latency (ML: %d)\n",
				  clt->mp_policy);
	शेष:
		वापस sysfs_emit(page, "Unknown (%d)\n", clt->mp_policy);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mpath_policy_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार count)
अणु
	काष्ठा rtrs_clt *clt;
	पूर्णांक value;
	पूर्णांक ret;
	माप_प्रकार len = 0;

	clt = container_of(dev, काष्ठा rtrs_clt, dev);

	ret = kstrtoपूर्णांक(buf, 10, &value);
	अगर (!ret && (value == MP_POLICY_RR ||
		     value == MP_POLICY_MIN_INFLIGHT ||
		     value == MP_POLICY_MIN_LATENCY)) अणु
		clt->mp_policy = value;
		वापस count;
	पूर्ण

	/* distinguish "mi" and "min-latency" with length */
	len = strnlen(buf, NAME_MAX);
	अगर (buf[len - 1] == '\n')
		len--;

	अगर (!strnहालcmp(buf, "round-robin", 11) ||
	    (len == 2 && !strnहालcmp(buf, "rr", 2)))
		clt->mp_policy = MP_POLICY_RR;
	अन्यथा अगर (!strnहालcmp(buf, "min-inflight", 12) ||
		 (len == 2 && !strnहालcmp(buf, "mi", 2)))
		clt->mp_policy = MP_POLICY_MIN_INFLIGHT;
	अन्यथा अगर (!strnहालcmp(buf, "min-latency", 11) ||
		 (len == 2 && !strnहालcmp(buf, "ml", 2)))
		clt->mp_policy = MP_POLICY_MIN_LATENCY;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(mpath_policy);

अटल sमाप_प्रकार add_path_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *page)
अणु
	वापस sysfs_emit(
		page,
		"Usage: echo [<source addr>@]<destination addr> > %s\n\n*addr ::= [ ip:<ipv4|ipv6> | gid:<gid> ]\n",
		attr->attr.name);
पूर्ण

अटल sमाप_प्रकार add_path_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sockaddr_storage srcaddr, dstaddr;
	काष्ठा rtrs_addr addr = अणु
		.src = &srcaddr,
		.dst = &dstaddr
	पूर्ण;
	काष्ठा rtrs_clt *clt;
	स्थिर अक्षर *nl;
	माप_प्रकार len;
	पूर्णांक err;

	clt = container_of(dev, काष्ठा rtrs_clt, dev);

	nl = म_अक्षर(buf, '\n');
	अगर (nl)
		len = nl - buf;
	अन्यथा
		len = count;
	err = rtrs_addr_to_sockaddr(buf, len, clt->port, &addr);
	अगर (err)
		वापस -EINVAL;

	err = rtrs_clt_create_path_from_sysfs(clt, &addr);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(add_path);

अटल sमाप_प्रकार rtrs_clt_state_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	अगर (sess->state == RTRS_CLT_CONNECTED)
		वापस sysfs_emit(page, "connected\n");

	वापस sysfs_emit(page, "disconnected\n");
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_state_attr =
	__ATTR(state, 0444, rtrs_clt_state_show, शून्य);

अटल sमाप_प्रकार rtrs_clt_reconnect_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Usage: echo 1 > %s\n", attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rtrs_clt_reconnect_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक ret;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	अगर (!sysfs_streq(buf, "1")) अणु
		rtrs_err(sess->clt, "%s: unknown value: '%s'\n",
			  attr->attr.name, buf);
		वापस -EINVAL;
	पूर्ण
	ret = rtrs_clt_reconnect_from_sysfs(sess);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_reconnect_attr =
	__ATTR(reconnect, 0644, rtrs_clt_reconnect_show,
	       rtrs_clt_reconnect_store);

अटल sमाप_प्रकार rtrs_clt_disconnect_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Usage: echo 1 > %s\n", attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rtrs_clt_disconnect_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक ret;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	अगर (!sysfs_streq(buf, "1")) अणु
		rtrs_err(sess->clt, "%s: unknown value: '%s'\n",
			  attr->attr.name, buf);
		वापस -EINVAL;
	पूर्ण
	ret = rtrs_clt_disconnect_from_sysfs(sess);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_disconnect_attr =
	__ATTR(disconnect, 0644, rtrs_clt_disconnect_show,
	       rtrs_clt_disconnect_store);

अटल sमाप_प्रकार rtrs_clt_हटाओ_path_show(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Usage: echo 1 > %s\n", attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rtrs_clt_हटाओ_path_store(काष्ठा kobject *kobj,
					   काष्ठा kobj_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक ret;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	अगर (!sysfs_streq(buf, "1")) अणु
		rtrs_err(sess->clt, "%s: unknown value: '%s'\n",
			  attr->attr.name, buf);
		वापस -EINVAL;
	पूर्ण
	ret = rtrs_clt_हटाओ_path_from_sysfs(sess, &attr->attr);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_हटाओ_path_attr =
	__ATTR(हटाओ_path, 0644, rtrs_clt_हटाओ_path_show,
	       rtrs_clt_हटाओ_path_store);

STAT_ATTR(काष्ठा rtrs_clt_stats, cpu_migration,
	  rtrs_clt_stats_migration_cnt_to_str,
	  rtrs_clt_reset_cpu_migr_stats);

STAT_ATTR(काष्ठा rtrs_clt_stats, reconnects,
	  rtrs_clt_stats_reconnects_to_str,
	  rtrs_clt_reset_reconnects_stat);

STAT_ATTR(काष्ठा rtrs_clt_stats, rdma,
	  rtrs_clt_stats_rdma_to_str,
	  rtrs_clt_reset_rdma_stats);

STAT_ATTR(काष्ठा rtrs_clt_stats, reset_all,
	  rtrs_clt_reset_all_help,
	  rtrs_clt_reset_all_stats);

अटल काष्ठा attribute *rtrs_clt_stats_attrs[] = अणु
	&cpu_migration_attr.attr,
	&reconnects_attr.attr,
	&rdma_attr.attr,
	&reset_all_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtrs_clt_stats_attr_group = अणु
	.attrs = rtrs_clt_stats_attrs,
पूर्ण;

अटल sमाप_प्रकार rtrs_clt_hca_port_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(kobj, typeof(*sess), kobj);

	वापस sysfs_emit(page, "%u\n", sess->hca_port);
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_hca_port_attr =
	__ATTR(hca_port, 0444, rtrs_clt_hca_port_show, शून्य);

अटल sमाप_प्रकार rtrs_clt_hca_name_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);

	वापस sysfs_emit(page, "%s\n", sess->hca_name);
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_hca_name_attr =
	__ATTR(hca_name, 0444, rtrs_clt_hca_name_show, शून्य);

अटल sमाप_प्रकार rtrs_clt_cur_latency_show(काष्ठा kobject *kobj,
				    काष्ठा kobj_attribute *attr,
				    अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);

	वापस sysfs_emit(page, "%lld ns\n",
			  kसमय_प्रकारo_ns(sess->s.hb_cur_latency));
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_cur_latency_attr =
	__ATTR(cur_latency, 0444, rtrs_clt_cur_latency_show, शून्य);

अटल sमाप_प्रकार rtrs_clt_src_addr_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक len;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	len = sockaddr_to_str((काष्ठा sockaddr *)&sess->s.src_addr, page,
			      PAGE_SIZE);
	len += sysfs_emit_at(page, len, "\n");
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_src_addr_attr =
	__ATTR(src_addr, 0444, rtrs_clt_src_addr_show, शून्य);

अटल sमाप_प्रकार rtrs_clt_dst_addr_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_clt_sess *sess;
	पूर्णांक len;

	sess = container_of(kobj, काष्ठा rtrs_clt_sess, kobj);
	len = sockaddr_to_str((काष्ठा sockaddr *)&sess->s.dst_addr, page,
			      PAGE_SIZE);
	len += sysfs_emit_at(page, len, "\n");
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_clt_dst_addr_attr =
	__ATTR(dst_addr, 0444, rtrs_clt_dst_addr_show, शून्य);

अटल काष्ठा attribute *rtrs_clt_sess_attrs[] = अणु
	&rtrs_clt_hca_name_attr.attr,
	&rtrs_clt_hca_port_attr.attr,
	&rtrs_clt_src_addr_attr.attr,
	&rtrs_clt_dst_addr_attr.attr,
	&rtrs_clt_state_attr.attr,
	&rtrs_clt_reconnect_attr.attr,
	&rtrs_clt_disconnect_attr.attr,
	&rtrs_clt_हटाओ_path_attr.attr,
	&rtrs_clt_cur_latency_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtrs_clt_sess_attr_group = अणु
	.attrs = rtrs_clt_sess_attrs,
पूर्ण;

पूर्णांक rtrs_clt_create_sess_files(काष्ठा rtrs_clt_sess *sess)
अणु
	काष्ठा rtrs_clt *clt = sess->clt;
	अक्षर str[NAME_MAX];
	पूर्णांक err;
	काष्ठा rtrs_addr path = अणु
		.src = &sess->s.src_addr,
		.dst = &sess->s.dst_addr,
	पूर्ण;

	rtrs_addr_to_str(&path, str, माप(str));
	err = kobject_init_and_add(&sess->kobj, &ktype_sess, clt->kobj_paths,
				   "%s", str);
	अगर (err) अणु
		pr_err("kobject_init_and_add: %d\n", err);
		kobject_put(&sess->kobj);
		वापस err;
	पूर्ण
	err = sysfs_create_group(&sess->kobj, &rtrs_clt_sess_attr_group);
	अगर (err) अणु
		pr_err("sysfs_create_group(): %d\n", err);
		जाओ put_kobj;
	पूर्ण
	err = kobject_init_and_add(&sess->stats->kobj_stats, &ktype_stats,
				   &sess->kobj, "stats");
	अगर (err) अणु
		pr_err("kobject_init_and_add: %d\n", err);
		kobject_put(&sess->stats->kobj_stats);
		जाओ हटाओ_group;
	पूर्ण

	err = sysfs_create_group(&sess->stats->kobj_stats,
				 &rtrs_clt_stats_attr_group);
	अगर (err) अणु
		pr_err("failed to create stats sysfs group, err: %d\n", err);
		जाओ put_kobj_stats;
	पूर्ण

	वापस 0;

put_kobj_stats:
	kobject_del(&sess->stats->kobj_stats);
	kobject_put(&sess->stats->kobj_stats);
हटाओ_group:
	sysfs_हटाओ_group(&sess->kobj, &rtrs_clt_sess_attr_group);
put_kobj:
	kobject_del(&sess->kobj);
	kobject_put(&sess->kobj);

	वापस err;
पूर्ण

व्योम rtrs_clt_destroy_sess_files(काष्ठा rtrs_clt_sess *sess,
				  स्थिर काष्ठा attribute *sysfs_self)
अणु
	kobject_del(&sess->stats->kobj_stats);
	kobject_put(&sess->stats->kobj_stats);
	अगर (sysfs_self)
		sysfs_हटाओ_file_self(&sess->kobj, sysfs_self);
	kobject_del(&sess->kobj);
पूर्ण

अटल काष्ठा attribute *rtrs_clt_attrs[] = अणु
	&dev_attr_max_reconnect_attempts.attr,
	&dev_attr_mpath_policy.attr,
	&dev_attr_add_path.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtrs_clt_attr_group = अणु
	.attrs = rtrs_clt_attrs,
पूर्ण;

पूर्णांक rtrs_clt_create_sysfs_root_files(काष्ठा rtrs_clt *clt)
अणु
	वापस sysfs_create_group(&clt->dev.kobj, &rtrs_clt_attr_group);
पूर्ण

व्योम rtrs_clt_destroy_sysfs_root(काष्ठा rtrs_clt *clt)
अणु
	sysfs_हटाओ_group(&clt->dev.kobj, &rtrs_clt_attr_group);

	अगर (clt->kobj_paths) अणु
		kobject_del(clt->kobj_paths);
		kobject_put(clt->kobj_paths);
	पूर्ण
पूर्ण
