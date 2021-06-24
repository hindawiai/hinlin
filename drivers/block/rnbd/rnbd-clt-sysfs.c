<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/parser.h>
#समावेश <linux/module.h>
#समावेश <linux/in6.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/device.h>
#समावेश <rdma/ib.h>
#समावेश <rdma/rdma_cm.h>

#समावेश "rnbd-clt.h"

अटल काष्ठा device *rnbd_dev;
अटल काष्ठा class *rnbd_dev_class;
अटल काष्ठा kobject *rnbd_devs_kobj;

क्रमागत अणु
	RNBD_OPT_ERR		= 0,
	RNBD_OPT_DEST_PORT	= 1 << 0,
	RNBD_OPT_PATH		= 1 << 1,
	RNBD_OPT_DEV_PATH	= 1 << 2,
	RNBD_OPT_ACCESS_MODE	= 1 << 3,
	RNBD_OPT_SESSNAME	= 1 << 6,
	RNBD_OPT_NR_POLL_QUEUES	= 1 << 7,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rnbd_opt_mandatory[] = अणु
	RNBD_OPT_DEV_PATH,
	RNBD_OPT_SESSNAME,
पूर्ण;

अटल स्थिर match_table_t rnbd_opt_tokens = अणु
	अणुRNBD_OPT_PATH,			"path=%s"		पूर्ण,
	अणुRNBD_OPT_DEV_PATH,		"device_path=%s"	पूर्ण,
	अणुRNBD_OPT_DEST_PORT,		"dest_port=%d"		पूर्ण,
	अणुRNBD_OPT_ACCESS_MODE,		"access_mode=%s"	पूर्ण,
	अणुRNBD_OPT_SESSNAME,		"sessname=%s"		पूर्ण,
	अणुRNBD_OPT_NR_POLL_QUEUES,	"nr_poll_queues=%d"	पूर्ण,
	अणुRNBD_OPT_ERR,			शून्य			पूर्ण,
पूर्ण;

काष्ठा rnbd_map_options अणु
	अक्षर *sessname;
	काष्ठा rtrs_addr *paths;
	माप_प्रकार *path_cnt;
	अक्षर *pathname;
	u16 *dest_port;
	क्रमागत rnbd_access_mode *access_mode;
	u32 *nr_poll_queues;
पूर्ण;

अटल पूर्णांक rnbd_clt_parse_map_options(स्थिर अक्षर *buf, माप_प्रकार max_path_cnt,
				       काष्ठा rnbd_map_options *opt)
अणु
	अक्षर *options, *sep_opt;
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक opt_mask = 0;
	पूर्णांक token;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i, dest_port, nr_poll_queues;
	पूर्णांक p_cnt = 0;

	options = kstrdup(buf, GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	sep_opt = म_मालाip(options);
	जबतक ((p = strsep(&sep_opt, " ")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, rnbd_opt_tokens, args);
		opt_mask |= token;

		चयन (token) अणु
		हाल RNBD_OPT_SESSNAME:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(p) > NAME_MAX) अणु
				pr_err("map_device: sessname too long\n");
				ret = -EINVAL;
				kमुक्त(p);
				जाओ out;
			पूर्ण
			strscpy(opt->sessname, p, NAME_MAX);
			kमुक्त(p);
			अवरोध;

		हाल RNBD_OPT_PATH:
			अगर (p_cnt >= max_path_cnt) अणु
				pr_err("map_device: too many (> %zu) paths provided\n",
				       max_path_cnt);
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			ret = rtrs_addr_to_sockaddr(p, म_माप(p),
						    *opt->dest_port,
						    &opt->paths[p_cnt]);
			अगर (ret) अणु
				pr_err("Can't parse path %s: %d\n", p, ret);
				kमुक्त(p);
				जाओ out;
			पूर्ण

			p_cnt++;

			kमुक्त(p);
			अवरोध;

		हाल RNBD_OPT_DEV_PATH:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(p) > NAME_MAX) अणु
				pr_err("map_device: Device path too long\n");
				ret = -EINVAL;
				kमुक्त(p);
				जाओ out;
			पूर्ण
			strscpy(opt->pathname, p, NAME_MAX);
			kमुक्त(p);
			अवरोध;

		हाल RNBD_OPT_DEST_PORT:
			अगर (match_पूर्णांक(args, &dest_port) || dest_port < 0 ||
			    dest_port > 65535) अणु
				pr_err("bad destination port number parameter '%d'\n",
				       dest_port);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			*opt->dest_port = dest_port;
			अवरोध;

		हाल RNBD_OPT_ACCESS_MODE:
			p = match_strdup(args);
			अगर (!p) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			अगर (!म_भेद(p, "ro")) अणु
				*opt->access_mode = RNBD_ACCESS_RO;
			पूर्ण अन्यथा अगर (!म_भेद(p, "rw")) अणु
				*opt->access_mode = RNBD_ACCESS_RW;
			पूर्ण अन्यथा अगर (!म_भेद(p, "migration")) अणु
				*opt->access_mode = RNBD_ACCESS_MIGRATION;
			पूर्ण अन्यथा अणु
				pr_err("map_device: Invalid access_mode: '%s'\n",
				       p);
				ret = -EINVAL;
				kमुक्त(p);
				जाओ out;
			पूर्ण

			kमुक्त(p);
			अवरोध;

		हाल RNBD_OPT_NR_POLL_QUEUES:
			अगर (match_पूर्णांक(args, &nr_poll_queues) || nr_poll_queues < -1 ||
			    nr_poll_queues > (पूर्णांक)nr_cpu_ids) अणु
				pr_err("bad nr_poll_queues parameter '%d'\n",
				       nr_poll_queues);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (nr_poll_queues == -1)
				nr_poll_queues = nr_cpu_ids;
			*opt->nr_poll_queues = nr_poll_queues;
			अवरोध;

		शेष:
			pr_err("map_device: Unknown parameter or missing value '%s'\n",
			       p);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rnbd_opt_mandatory); i++) अणु
		अगर ((opt_mask & rnbd_opt_mandatory[i])) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			pr_err("map_device: Parameters missing\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	*opt->path_cnt = p_cnt;
	kमुक्त(options);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा kobject *kobj,
			  काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	चयन (dev->dev_state) अणु
	हाल DEV_STATE_INIT:
		वापस snम_लिखो(page, PAGE_SIZE, "init\n");
	हाल DEV_STATE_MAPPED:
		/* TODO fix cli tool beक्रमe changing to proper state */
		वापस snम_लिखो(page, PAGE_SIZE, "open\n");
	हाल DEV_STATE_MAPPED_DISCONNECTED:
		/* TODO fix cli tool beक्रमe changing to proper state */
		वापस snम_लिखो(page, PAGE_SIZE, "closed\n");
	हाल DEV_STATE_UNMAPPED:
		वापस snम_लिखो(page, PAGE_SIZE, "unmapped\n");
	शेष:
		वापस snम_लिखो(page, PAGE_SIZE, "unknown\n");
	पूर्ण
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_state_attr = __ATTR_RO(state);

अटल sमाप_प्रकार nr_poll_queues_show(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	वापस sysfs_emit(page, "%d\n", dev->nr_poll_queues);
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_nr_poll_queues =
	__ATTR_RO(nr_poll_queues);

अटल sमाप_प्रकार mapping_path_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	वापस scnम_लिखो(page, PAGE_SIZE, "%s\n", dev->pathname);
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_mapping_path_attr =
	__ATTR_RO(mapping_path);

अटल sमाप_प्रकार access_mode_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			rnbd_access_mode_str(dev->access_mode));
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_access_mode =
	__ATTR_RO(access_mode);

अटल sमाप_प्रकार rnbd_clt_unmap_dev_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "Usage: echo <normal|force> > %s\n",
			 attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rnbd_clt_unmap_dev_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rnbd_clt_dev *dev;
	अक्षर *opt, *options;
	bool क्रमce;
	पूर्णांक err;

	opt = kstrdup(buf, GFP_KERNEL);
	अगर (!opt)
		वापस -ENOMEM;

	options = म_मालाip(opt);
	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);
	अगर (sysfs_streq(options, "normal")) अणु
		क्रमce = false;
	पूर्ण अन्यथा अगर (sysfs_streq(options, "force")) अणु
		क्रमce = true;
	पूर्ण अन्यथा अणु
		rnbd_clt_err(dev,
			      "unmap_device: Invalid value: %s\n",
			      options);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	rnbd_clt_info(dev, "Unmapping device, option: %s.\n",
		       क्रमce ? "force" : "normal");

	/*
	 * We take explicit module reference only क्रम one reason: करो not
	 * race with lockless rnbd_destroy_sessions().
	 */
	अगर (!try_module_get(THIS_MODULE)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	err = rnbd_clt_unmap_device(dev, क्रमce, &attr->attr);
	अगर (err) अणु
		अगर (err != -EALREADY)
			rnbd_clt_err(dev, "unmap_device: %d\n",  err);
		जाओ module_put;
	पूर्ण

	/*
	 * Here device can be vanished!
	 */

	err = count;

module_put:
	module_put(THIS_MODULE);
out:
	kमुक्त(opt);

	वापस err;
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_unmap_device_attr =
	__ATTR(unmap_device, 0644, rnbd_clt_unmap_dev_show,
	       rnbd_clt_unmap_dev_store);

अटल sमाप_प्रकार rnbd_clt_resize_dev_show(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE,
			 "Usage: echo <new size in sectors> > %s\n",
			 attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rnbd_clt_resize_dev_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ sectors;
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	ret = kम_से_अदीर्घ(buf, 0, &sectors);
	अगर (ret)
		वापस ret;

	ret = rnbd_clt_resize_disk(dev, (माप_प्रकार)sectors);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_resize_dev_attr =
	__ATTR(resize, 0644, rnbd_clt_resize_dev_show,
	       rnbd_clt_resize_dev_store);

अटल sमाप_प्रकार rnbd_clt_remap_dev_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "Usage: echo <1> > %s\n",
			 attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rnbd_clt_remap_dev_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rnbd_clt_dev *dev;
	अक्षर *opt, *options;
	पूर्णांक err;

	opt = kstrdup(buf, GFP_KERNEL);
	अगर (!opt)
		वापस -ENOMEM;

	options = म_मालाip(opt);
	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);
	अगर (!sysfs_streq(options, "1")) अणु
		rnbd_clt_err(dev,
			      "remap_device: Invalid value: %s\n",
			      options);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	err = rnbd_clt_remap_device(dev);
	अगर (likely(!err))
		err = count;

out:
	kमुक्त(opt);

	वापस err;
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_remap_device_attr =
	__ATTR(remap_device, 0644, rnbd_clt_remap_dev_show,
	       rnbd_clt_remap_dev_store);

अटल sमाप_प्रकार session_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    अक्षर *page)
अणु
	काष्ठा rnbd_clt_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_clt_dev, kobj);

	वापस scnम_लिखो(page, PAGE_SIZE, "%s\n", dev->sess->sessname);
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_session_attr =
	__ATTR_RO(session);

अटल काष्ठा attribute *rnbd_dev_attrs[] = अणु
	&rnbd_clt_unmap_device_attr.attr,
	&rnbd_clt_resize_dev_attr.attr,
	&rnbd_clt_remap_device_attr.attr,
	&rnbd_clt_mapping_path_attr.attr,
	&rnbd_clt_state_attr.attr,
	&rnbd_clt_session_attr.attr,
	&rnbd_clt_access_mode.attr,
	&rnbd_clt_nr_poll_queues.attr,
	शून्य,
पूर्ण;

व्योम rnbd_clt_हटाओ_dev_symlink(काष्ठा rnbd_clt_dev *dev)
अणु
	/*
	 * The module unload rnbd_client_निकास path is racing with unmapping of
	 * the last single device from the sysfs manually
	 * i.e. rnbd_clt_unmap_dev_store() leading to a sysfs warning because
	 * of sysfs link alपढ़ोy was हटाओd alपढ़ोy.
	 */
	अगर (dev->blk_symlink_name) अणु
		अगर (try_module_get(THIS_MODULE)) अणु
			sysfs_हटाओ_link(rnbd_devs_kobj, dev->blk_symlink_name);
			module_put(THIS_MODULE);
		पूर्ण
		/* It should be मुक्तd always. */
		kमुक्त(dev->blk_symlink_name);
		dev->blk_symlink_name = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा kobj_type rnbd_dev_ktype = अणु
	.sysfs_ops      = &kobj_sysfs_ops,
	.शेष_attrs  = rnbd_dev_attrs,
पूर्ण;

अटल पूर्णांक rnbd_clt_add_dev_kobj(काष्ठा rnbd_clt_dev *dev)
अणु
	पूर्णांक ret;
	काष्ठा kobject *gd_kobj = &disk_to_dev(dev->gd)->kobj;

	ret = kobject_init_and_add(&dev->kobj, &rnbd_dev_ktype, gd_kobj, "%s",
				   "rnbd");
	अगर (ret) अणु
		rnbd_clt_err(dev, "Failed to create device sysfs dir, err: %d\n",
			      ret);
		kobject_put(&dev->kobj);
	पूर्ण
	kobject_uevent(gd_kobj, KOBJ_ONLINE);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार rnbd_clt_map_device_show(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE,
			 "Usage: echo \"[dest_port=server port number] sessname=<name of the rtrs session> path=<[srcaddr@]dstaddr> [path=<[srcaddr@]dstaddr>] device_path=<full path on remote side> [access_mode=<ro|rw|migration>] [nr_poll_queues=<number of queues>]\" > %s\n\naddr ::= [ ip:<ipv4> | ip:<ipv6> | gid:<gid> ]\n",
			 attr->attr.name);
पूर्ण

अटल पूर्णांक rnbd_clt_get_path_name(काष्ठा rnbd_clt_dev *dev, अक्षर *buf,
				   माप_प्रकार len)
अणु
	पूर्णांक ret;
	अक्षर pathname[NAME_MAX], *s;

	strscpy(pathname, dev->pathname, माप(pathname));
	जबतक ((s = म_अक्षर(pathname, '/')))
		s[0] = '!';

	ret = snम_लिखो(buf, len, "%s@%s", pathname, dev->sess->sessname);
	अगर (ret >= len)
		वापस -ENAMETOOLONG;

	वापस 0;
पूर्ण

अटल पूर्णांक rnbd_clt_add_dev_symlink(काष्ठा rnbd_clt_dev *dev)
अणु
	काष्ठा kobject *gd_kobj = &disk_to_dev(dev->gd)->kobj;
	पूर्णांक ret, len;

	len = म_माप(dev->pathname) + म_माप(dev->sess->sessname) + 2;
	dev->blk_symlink_name = kzalloc(len, GFP_KERNEL);
	अगर (!dev->blk_symlink_name) अणु
		rnbd_clt_err(dev, "Failed to allocate memory for blk_symlink_name\n");
		वापस -ENOMEM;
	पूर्ण

	ret = rnbd_clt_get_path_name(dev, dev->blk_symlink_name,
				      len);
	अगर (ret) अणु
		rnbd_clt_err(dev, "Failed to get /sys/block symlink path, err: %d\n",
			      ret);
		जाओ out_err;
	पूर्ण

	ret = sysfs_create_link(rnbd_devs_kobj, gd_kobj,
				dev->blk_symlink_name);
	अगर (ret) अणु
		rnbd_clt_err(dev, "Creating /sys/block symlink failed, err: %d\n",
			      ret);
		जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	kमुक्त(dev->blk_symlink_name);
	dev->blk_symlink_name = शून्य ;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार rnbd_clt_map_device_store(काष्ठा kobject *kobj,
					  काष्ठा kobj_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rnbd_clt_dev *dev;
	काष्ठा rnbd_map_options opt;
	पूर्णांक ret;
	अक्षर pathname[NAME_MAX];
	अक्षर sessname[NAME_MAX];
	क्रमागत rnbd_access_mode access_mode = RNBD_ACCESS_RW;
	u16 port_nr = RTRS_PORT;
	u32 nr_poll_queues = 0;

	काष्ठा sockaddr_storage *addrs;
	काष्ठा rtrs_addr paths[6];
	माप_प्रकार path_cnt;

	opt.sessname = sessname;
	opt.paths = paths;
	opt.path_cnt = &path_cnt;
	opt.pathname = pathname;
	opt.dest_port = &port_nr;
	opt.access_mode = &access_mode;
	opt.nr_poll_queues = &nr_poll_queues;
	addrs = kसुस्मृति(ARRAY_SIZE(paths) * 2, माप(*addrs), GFP_KERNEL);
	अगर (!addrs)
		वापस -ENOMEM;

	क्रम (path_cnt = 0; path_cnt < ARRAY_SIZE(paths); path_cnt++) अणु
		paths[path_cnt].src = &addrs[path_cnt * 2];
		paths[path_cnt].dst = &addrs[path_cnt * 2 + 1];
	पूर्ण

	ret = rnbd_clt_parse_map_options(buf, ARRAY_SIZE(paths), &opt);
	अगर (ret)
		जाओ out;

	pr_info("Mapping device %s on session %s, (access_mode: %s, nr_poll_queues: %d)\n",
		pathname, sessname,
		rnbd_access_mode_str(access_mode),
		nr_poll_queues);

	dev = rnbd_clt_map_device(sessname, paths, path_cnt, port_nr, pathname,
				  access_mode, nr_poll_queues);
	अगर (IS_ERR(dev)) अणु
		ret = PTR_ERR(dev);
		जाओ out;
	पूर्ण

	ret = rnbd_clt_add_dev_kobj(dev);
	अगर (ret)
		जाओ unmap_dev;

	ret = rnbd_clt_add_dev_symlink(dev);
	अगर (ret)
		जाओ unmap_dev;

	kमुक्त(addrs);
	वापस count;

unmap_dev:
	rnbd_clt_unmap_device(dev, true, शून्य);
out:
	kमुक्त(addrs);
	वापस ret;
पूर्ण

अटल काष्ठा kobj_attribute rnbd_clt_map_device_attr =
	__ATTR(map_device, 0644,
	       rnbd_clt_map_device_show, rnbd_clt_map_device_store);

अटल काष्ठा attribute *शेष_attrs[] = अणु
	&rnbd_clt_map_device_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group शेष_attr_group = अणु
	.attrs = शेष_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *शेष_attr_groups[] = अणु
	&शेष_attr_group,
	शून्य,
पूर्ण;

पूर्णांक rnbd_clt_create_sysfs_files(व्योम)
अणु
	पूर्णांक err;

	rnbd_dev_class = class_create(THIS_MODULE, "rnbd-client");
	अगर (IS_ERR(rnbd_dev_class))
		वापस PTR_ERR(rnbd_dev_class);

	rnbd_dev = device_create_with_groups(rnbd_dev_class, शून्य,
					      MKDEV(0, 0), शून्य,
					      शेष_attr_groups, "ctl");
	अगर (IS_ERR(rnbd_dev)) अणु
		err = PTR_ERR(rnbd_dev);
		जाओ cls_destroy;
	पूर्ण
	rnbd_devs_kobj = kobject_create_and_add("devices", &rnbd_dev->kobj);
	अगर (!rnbd_devs_kobj) अणु
		err = -ENOMEM;
		जाओ dev_destroy;
	पूर्ण

	वापस 0;

dev_destroy:
	device_destroy(rnbd_dev_class, MKDEV(0, 0));
cls_destroy:
	class_destroy(rnbd_dev_class);

	वापस err;
पूर्ण

व्योम rnbd_clt_destroy_sysfs_files(व्योम)
अणु
	sysfs_हटाओ_group(&rnbd_dev->kobj, &शेष_attr_group);
	kobject_del(rnbd_devs_kobj);
	kobject_put(rnbd_devs_kobj);
	device_destroy(rnbd_dev_class, MKDEV(0, 0));
	class_destroy(rnbd_dev_class);
पूर्ण
