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
#समावेश "rtrs-srv.h"
#समावेश "rtrs-log.h"

अटल व्योम rtrs_srv_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rtrs_srv_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_srv_sess, kobj);
	kमुक्त(sess);
पूर्ण

अटल काष्ठा kobj_type ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.release	= rtrs_srv_release,
पूर्ण;

अटल sमाप_प्रकार rtrs_srv_disconnect_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "Usage: echo 1 > %s\n", attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rtrs_srv_disconnect_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rtrs_srv_sess *sess;
	काष्ठा rtrs_sess *s;
	अक्षर str[MAXHOSTNAMELEN];

	sess = container_of(kobj, काष्ठा rtrs_srv_sess, kobj);
	s = &sess->s;
	अगर (!sysfs_streq(buf, "1")) अणु
		rtrs_err(s, "%s: invalid value: '%s'\n",
			  attr->attr.name, buf);
		वापस -EINVAL;
	पूर्ण

	sockaddr_to_str((काष्ठा sockaddr *)&sess->s.dst_addr, str, माप(str));

	rtrs_info(s, "disconnect for path %s requested\n", str);
	/* first हटाओ sysfs itself to aव्योम deadlock */
	sysfs_हटाओ_file_self(&sess->kobj, &attr->attr);
	बंद_sess(sess);

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_srv_disconnect_attr =
	__ATTR(disconnect, 0644,
	       rtrs_srv_disconnect_show, rtrs_srv_disconnect_store);

अटल sमाप_प्रकार rtrs_srv_hca_port_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_srv_sess *sess;
	काष्ठा rtrs_con *usr_con;

	sess = container_of(kobj, typeof(*sess), kobj);
	usr_con = sess->s.con[0];

	वापस sysfs_emit(page, "%u\n", usr_con->cm_id->port_num);
पूर्ण

अटल काष्ठा kobj_attribute rtrs_srv_hca_port_attr =
	__ATTR(hca_port, 0444, rtrs_srv_hca_port_show, शून्य);

अटल sमाप_प्रकार rtrs_srv_hca_name_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_srv_sess *sess;

	sess = container_of(kobj, काष्ठा rtrs_srv_sess, kobj);

	वापस sysfs_emit(page, "%s\n", sess->s.dev->ib_dev->name);
पूर्ण

अटल काष्ठा kobj_attribute rtrs_srv_hca_name_attr =
	__ATTR(hca_name, 0444, rtrs_srv_hca_name_show, शून्य);

अटल sमाप_प्रकार rtrs_srv_src_addr_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_srv_sess *sess;
	पूर्णांक cnt;

	sess = container_of(kobj, काष्ठा rtrs_srv_sess, kobj);
	cnt = sockaddr_to_str((काष्ठा sockaddr *)&sess->s.dst_addr,
			      page, PAGE_SIZE);
	वापस cnt + scnम_लिखो(page + cnt, PAGE_SIZE - cnt, "\n");
पूर्ण

अटल काष्ठा kobj_attribute rtrs_srv_src_addr_attr =
	__ATTR(src_addr, 0444, rtrs_srv_src_addr_show, शून्य);

अटल sमाप_प्रकार rtrs_srv_dst_addr_show(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       अक्षर *page)
अणु
	काष्ठा rtrs_srv_sess *sess;
	पूर्णांक len;

	sess = container_of(kobj, काष्ठा rtrs_srv_sess, kobj);
	len = sockaddr_to_str((काष्ठा sockaddr *)&sess->s.src_addr, page,
			      PAGE_SIZE);
	len += sysfs_emit_at(page, len, "\n");
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute rtrs_srv_dst_addr_attr =
	__ATTR(dst_addr, 0444, rtrs_srv_dst_addr_show, शून्य);

अटल काष्ठा attribute *rtrs_srv_sess_attrs[] = अणु
	&rtrs_srv_hca_name_attr.attr,
	&rtrs_srv_hca_port_attr.attr,
	&rtrs_srv_src_addr_attr.attr,
	&rtrs_srv_dst_addr_attr.attr,
	&rtrs_srv_disconnect_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtrs_srv_sess_attr_group = अणु
	.attrs = rtrs_srv_sess_attrs,
पूर्ण;

STAT_ATTR(काष्ठा rtrs_srv_stats, rdma,
	  rtrs_srv_stats_rdma_to_str,
	  rtrs_srv_reset_rdma_stats);

अटल काष्ठा attribute *rtrs_srv_stats_attrs[] = अणु
	&rdma_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rtrs_srv_stats_attr_group = अणु
	.attrs = rtrs_srv_stats_attrs,
पूर्ण;

अटल पूर्णांक rtrs_srv_create_once_sysfs_root_folders(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	पूर्णांक err = 0;

	mutex_lock(&srv->paths_mutex);
	अगर (srv->dev_ref++) अणु
		/*
		 * Device needs to be रेजिस्टरed only on the first session
		 */
		जाओ unlock;
	पूर्ण
	srv->dev.class = rtrs_dev_class;
	err = dev_set_name(&srv->dev, "%s", sess->s.sessname);
	अगर (err)
		जाओ unlock;

	/*
	 * Suppress user space notअगरication until
	 * sysfs files are created
	 */
	dev_set_uevent_suppress(&srv->dev, true);
	err = device_add(&srv->dev);
	अगर (err) अणु
		pr_err("device_add(): %d\n", err);
		put_device(&srv->dev);
		जाओ unlock;
	पूर्ण
	srv->kobj_paths = kobject_create_and_add("paths", &srv->dev.kobj);
	अगर (!srv->kobj_paths) अणु
		err = -ENOMEM;
		pr_err("kobject_create_and_add(): %d\n", err);
		device_del(&srv->dev);
		put_device(&srv->dev);
		जाओ unlock;
	पूर्ण
	dev_set_uevent_suppress(&srv->dev, false);
	kobject_uevent(&srv->dev.kobj, KOBJ_ADD);
unlock:
	mutex_unlock(&srv->paths_mutex);

	वापस err;
पूर्ण

अटल व्योम
rtrs_srv_destroy_once_sysfs_root_folders(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;

	mutex_lock(&srv->paths_mutex);
	अगर (!--srv->dev_ref) अणु
		kobject_del(srv->kobj_paths);
		kobject_put(srv->kobj_paths);
		mutex_unlock(&srv->paths_mutex);
		device_del(&srv->dev);
		put_device(&srv->dev);
	पूर्ण अन्यथा अणु
		mutex_unlock(&srv->paths_mutex);
	पूर्ण
पूर्ण

अटल व्योम rtrs_srv_sess_stats_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rtrs_srv_stats *stats;

	stats = container_of(kobj, काष्ठा rtrs_srv_stats, kobj_stats);

	kमुक्त(stats);
पूर्ण

अटल काष्ठा kobj_type ktype_stats = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = rtrs_srv_sess_stats_release,
पूर्ण;

अटल पूर्णांक rtrs_srv_create_stats_files(काष्ठा rtrs_srv_sess *sess)
अणु
	पूर्णांक err;
	काष्ठा rtrs_sess *s = &sess->s;

	err = kobject_init_and_add(&sess->stats->kobj_stats, &ktype_stats,
				   &sess->kobj, "stats");
	अगर (err) अणु
		rtrs_err(s, "kobject_init_and_add(): %d\n", err);
		kobject_put(&sess->stats->kobj_stats);
		वापस err;
	पूर्ण
	err = sysfs_create_group(&sess->stats->kobj_stats,
				 &rtrs_srv_stats_attr_group);
	अगर (err) अणु
		rtrs_err(s, "sysfs_create_group(): %d\n", err);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	kobject_del(&sess->stats->kobj_stats);
	kobject_put(&sess->stats->kobj_stats);

	वापस err;
पूर्ण

पूर्णांक rtrs_srv_create_sess_files(काष्ठा rtrs_srv_sess *sess)
अणु
	काष्ठा rtrs_srv *srv = sess->srv;
	काष्ठा rtrs_sess *s = &sess->s;
	अक्षर str[NAME_MAX];
	पूर्णांक err;
	काष्ठा rtrs_addr path = अणु
		.src = &sess->s.dst_addr,
		.dst = &sess->s.src_addr,
	पूर्ण;

	rtrs_addr_to_str(&path, str, माप(str));
	err = rtrs_srv_create_once_sysfs_root_folders(sess);
	अगर (err)
		वापस err;

	err = kobject_init_and_add(&sess->kobj, &ktype, srv->kobj_paths,
				   "%s", str);
	अगर (err) अणु
		rtrs_err(s, "kobject_init_and_add(): %d\n", err);
		जाओ destroy_root;
	पूर्ण
	err = sysfs_create_group(&sess->kobj, &rtrs_srv_sess_attr_group);
	अगर (err) अणु
		rtrs_err(s, "sysfs_create_group(): %d\n", err);
		जाओ put_kobj;
	पूर्ण
	err = rtrs_srv_create_stats_files(sess);
	अगर (err)
		जाओ हटाओ_group;

	वापस 0;

हटाओ_group:
	sysfs_हटाओ_group(&sess->kobj, &rtrs_srv_sess_attr_group);
put_kobj:
	kobject_del(&sess->kobj);
destroy_root:
	kobject_put(&sess->kobj);
	rtrs_srv_destroy_once_sysfs_root_folders(sess);

	वापस err;
पूर्ण

व्योम rtrs_srv_destroy_sess_files(काष्ठा rtrs_srv_sess *sess)
अणु
	अगर (sess->kobj.state_in_sysfs) अणु
		kobject_del(&sess->stats->kobj_stats);
		kobject_put(&sess->stats->kobj_stats);
		sysfs_हटाओ_group(&sess->kobj, &rtrs_srv_sess_attr_group);
		kobject_put(&sess->kobj);

		rtrs_srv_destroy_once_sysfs_root_folders(sess);
	पूर्ण
पूर्ण
