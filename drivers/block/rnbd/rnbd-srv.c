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

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>

#समावेश "rnbd-srv.h"
#समावेश "rnbd-srv-dev.h"

MODULE_DESCRIPTION("RDMA Network Block Device Server");
MODULE_LICENSE("GPL");

अटल u16 port_nr = RTRS_PORT;

module_param_named(port_nr, port_nr, uलघु, 0444);
MODULE_PARM_DESC(port_nr,
		 "The port number the server is listening on (default: "
		 __stringअगरy(RTRS_PORT)")");

#घोषणा DEFAULT_DEV_SEARCH_PATH "/"

अटल अक्षर dev_search_path[PATH_MAX] = DEFAULT_DEV_SEARCH_PATH;

अटल पूर्णांक dev_search_path_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर अक्षर *p = म_खोजप(val, '\n') ? : val + म_माप(val);

	अगर (म_माप(val) >= माप(dev_search_path))
		वापस -EINVAL;

	snम_लिखो(dev_search_path, माप(dev_search_path), "%.*s",
		 (पूर्णांक)(p - val), val);

	pr_info("dev_search_path changed to '%s'\n", dev_search_path);

	वापस 0;
पूर्ण

अटल काष्ठा kparam_string dev_search_path_kparam_str = अणु
	.maxlen	= माप(dev_search_path),
	.string	= dev_search_path
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops dev_search_path_ops = अणु
	.set	= dev_search_path_set,
	.get	= param_get_string,
पूर्ण;

module_param_cb(dev_search_path, &dev_search_path_ops,
		&dev_search_path_kparam_str, 0444);
MODULE_PARM_DESC(dev_search_path,
		 "Sets the dev_search_path. When a device is mapped this path is prepended to the device path from the map device operation.  If %SESSNAME% is specified in a path, then device will be searched in a session namespace. (default: "
		 DEFAULT_DEV_SEARCH_PATH ")");

अटल DEFINE_MUTEX(sess_lock);
अटल DEFINE_SPINLOCK(dev_lock);

अटल LIST_HEAD(sess_list);
अटल LIST_HEAD(dev_list);

काष्ठा rnbd_io_निजी अणु
	काष्ठा rtrs_srv_op		*id;
	काष्ठा rnbd_srv_sess_dev	*sess_dev;
पूर्ण;

अटल व्योम rnbd_sess_dev_release(काष्ठा kref *kref)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kref, काष्ठा rnbd_srv_sess_dev, kref);
	complete(sess_dev->destroy_comp);
पूर्ण

अटल अंतरभूत व्योम rnbd_put_sess_dev(काष्ठा rnbd_srv_sess_dev *sess_dev)
अणु
	kref_put(&sess_dev->kref, rnbd_sess_dev_release);
पूर्ण

व्योम rnbd_endio(व्योम *priv, पूर्णांक error)
अणु
	काष्ठा rnbd_io_निजी *rnbd_priv = priv;
	काष्ठा rnbd_srv_sess_dev *sess_dev = rnbd_priv->sess_dev;

	rnbd_put_sess_dev(sess_dev);

	rtrs_srv_resp_rdma(rnbd_priv->id, error);

	kमुक्त(priv);
पूर्ण

अटल काष्ठा rnbd_srv_sess_dev *
rnbd_get_sess_dev(पूर्णांक dev_id, काष्ठा rnbd_srv_session *srv_sess)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	sess_dev = xa_load(&srv_sess->index_idr, dev_id);
	अगर (sess_dev)
		ret = kref_get_unless_zero(&sess_dev->kref);
	rcu_पढ़ो_unlock();

	अगर (!sess_dev || !ret)
		वापस ERR_PTR(-ENXIO);

	वापस sess_dev;
पूर्ण

अटल पूर्णांक process_rdma(काष्ठा rnbd_srv_session *srv_sess,
			काष्ठा rtrs_srv_op *id, व्योम *data, u32 datalen,
			स्थिर व्योम *usr, माप_प्रकार usrlen)
अणु
	स्थिर काष्ठा rnbd_msg_io *msg = usr;
	काष्ठा rnbd_io_निजी *priv;
	काष्ठा rnbd_srv_sess_dev *sess_dev;
	u32 dev_id;
	पूर्णांक err;
	काष्ठा rnbd_dev_blk_io *io;
	काष्ठा bio *bio;
	लघु prio;

	priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_id = le32_to_cpu(msg->device_id);

	sess_dev = rnbd_get_sess_dev(dev_id, srv_sess);
	अगर (IS_ERR(sess_dev)) अणु
		pr_err_ratelimited("Got I/O request on session %s for unknown device id %d\n",
				   srv_sess->sessname, dev_id);
		err = -ENOTCONN;
		जाओ err;
	पूर्ण

	priv->sess_dev = sess_dev;
	priv->id = id;

	/* Generate bio with pages poपूर्णांकing to the rdma buffer */
	bio = rnbd_bio_map_kern(data, sess_dev->rnbd_dev->ibd_bio_set, datalen, GFP_KERNEL);
	अगर (IS_ERR(bio)) अणु
		err = PTR_ERR(bio);
		rnbd_srv_err(sess_dev, "Failed to generate bio, err: %d\n", err);
		जाओ sess_dev_put;
	पूर्ण

	io = container_of(bio, काष्ठा rnbd_dev_blk_io, bio);
	io->dev = sess_dev->rnbd_dev;
	io->priv = priv;

	bio->bi_end_io = rnbd_dev_bi_end_io;
	bio->bi_निजी = io;
	bio->bi_opf = rnbd_to_bio_flags(le32_to_cpu(msg->rw));
	bio->bi_iter.bi_sector = le64_to_cpu(msg->sector);
	bio->bi_iter.bi_size = le32_to_cpu(msg->bi_size);
	prio = srv_sess->ver < RNBD_PROTO_VER_MAJOR ||
	       usrlen < माप(*msg) ? 0 : le16_to_cpu(msg->prio);
	bio_set_prio(bio, prio);
	bio_set_dev(bio, sess_dev->rnbd_dev->bdev);

	submit_bio(bio);

	वापस 0;

sess_dev_put:
	rnbd_put_sess_dev(sess_dev);
err:
	kमुक्त(priv);
	वापस err;
पूर्ण

अटल व्योम destroy_device(काष्ठा kref *kref)
अणु
	काष्ठा rnbd_srv_dev *dev = container_of(kref, काष्ठा rnbd_srv_dev, kref);

	WARN_ONCE(!list_empty(&dev->sess_dev_list),
		  "Device %s is being destroyed but still in use!\n",
		  dev->id);

	spin_lock(&dev_lock);
	list_del(&dev->list);
	spin_unlock(&dev_lock);

	mutex_destroy(&dev->lock);
	अगर (dev->dev_kobj.state_in_sysfs)
		/*
		 * Destroy kobj only अगर it was really created.
		 */
		rnbd_srv_destroy_dev_sysfs(dev);
	अन्यथा
		kमुक्त(dev);
पूर्ण

अटल व्योम rnbd_put_srv_dev(काष्ठा rnbd_srv_dev *dev)
अणु
	kref_put(&dev->kref, destroy_device);
पूर्ण

व्योम rnbd_destroy_sess_dev(काष्ठा rnbd_srv_sess_dev *sess_dev, bool keep_id)
अणु
	DECLARE_COMPLETION_ONSTACK(dc);

	अगर (keep_id)
		/* मुक्त the resources क्रम the id but करोn't  */
		/* allow to re-use the id itself because it */
		/* is still used by the client              */
		xa_cmpxchg(&sess_dev->sess->index_idr, sess_dev->device_id,
			   sess_dev, शून्य, 0);
	अन्यथा
		xa_erase(&sess_dev->sess->index_idr, sess_dev->device_id);
	synchronize_rcu();

	sess_dev->destroy_comp = &dc;
	rnbd_put_sess_dev(sess_dev);
	रुको_क्रम_completion(&dc); /* रुको क्रम inflights to drop to zero */

	rnbd_dev_बंद(sess_dev->rnbd_dev);
	list_del(&sess_dev->sess_list);
	mutex_lock(&sess_dev->dev->lock);
	list_del(&sess_dev->dev_list);
	अगर (sess_dev->खोलो_flags & FMODE_WRITE)
		sess_dev->dev->खोलो_ग_लिखो_cnt--;
	mutex_unlock(&sess_dev->dev->lock);

	rnbd_put_srv_dev(sess_dev->dev);

	rnbd_srv_info(sess_dev, "Device closed\n");
	kमुक्त(sess_dev);
पूर्ण

अटल व्योम destroy_sess(काष्ठा rnbd_srv_session *srv_sess)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev, *पंचांगp;

	अगर (list_empty(&srv_sess->sess_dev_list))
		जाओ out;

	mutex_lock(&srv_sess->lock);
	list_क्रम_each_entry_safe(sess_dev, पंचांगp, &srv_sess->sess_dev_list,
				 sess_list)
		rnbd_srv_destroy_dev_session_sysfs(sess_dev);
	mutex_unlock(&srv_sess->lock);

out:
	xa_destroy(&srv_sess->index_idr);
	bioset_निकास(&srv_sess->sess_bio_set);

	pr_info("RTRS Session %s disconnected\n", srv_sess->sessname);

	mutex_lock(&sess_lock);
	list_del(&srv_sess->list);
	mutex_unlock(&sess_lock);

	mutex_destroy(&srv_sess->lock);
	kमुक्त(srv_sess);
पूर्ण

अटल पूर्णांक create_sess(काष्ठा rtrs_srv *rtrs)
अणु
	काष्ठा rnbd_srv_session *srv_sess;
	अक्षर sessname[NAME_MAX];
	पूर्णांक err;

	err = rtrs_srv_get_sess_name(rtrs, sessname, माप(sessname));
	अगर (err) अणु
		pr_err("rtrs_srv_get_sess_name(%s): %d\n", sessname, err);

		वापस err;
	पूर्ण
	srv_sess = kzalloc(माप(*srv_sess), GFP_KERNEL);
	अगर (!srv_sess)
		वापस -ENOMEM;

	srv_sess->queue_depth = rtrs_srv_get_queue_depth(rtrs);
	err = bioset_init(&srv_sess->sess_bio_set, srv_sess->queue_depth,
			  दुरत्व(काष्ठा rnbd_dev_blk_io, bio),
			  BIOSET_NEED_BVECS);
	अगर (err) अणु
		pr_err("Allocating srv_session for session %s failed\n",
		       sessname);
		kमुक्त(srv_sess);
		वापस err;
	पूर्ण

	xa_init_flags(&srv_sess->index_idr, XA_FLAGS_ALLOC);
	INIT_LIST_HEAD(&srv_sess->sess_dev_list);
	mutex_init(&srv_sess->lock);
	mutex_lock(&sess_lock);
	list_add(&srv_sess->list, &sess_list);
	mutex_unlock(&sess_lock);

	srv_sess->rtrs = rtrs;
	strscpy(srv_sess->sessname, sessname, माप(srv_sess->sessname));

	rtrs_srv_set_sess_priv(rtrs, srv_sess);

	वापस 0;
पूर्ण

अटल पूर्णांक rnbd_srv_link_ev(काष्ठा rtrs_srv *rtrs,
			     क्रमागत rtrs_srv_link_ev ev, व्योम *priv)
अणु
	काष्ठा rnbd_srv_session *srv_sess = priv;

	चयन (ev) अणु
	हाल RTRS_SRV_LINK_EV_CONNECTED:
		वापस create_sess(rtrs);

	हाल RTRS_SRV_LINK_EV_DISCONNECTED:
		अगर (WARN_ON_ONCE(!srv_sess))
			वापस -EINVAL;

		destroy_sess(srv_sess);
		वापस 0;

	शेष:
		pr_warn("Received unknown RTRS session event %d from session %s\n",
			ev, srv_sess->sessname);
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम rnbd_srv_sess_dev_क्रमce_बंद(काष्ठा rnbd_srv_sess_dev *sess_dev,
				   काष्ठा kobj_attribute *attr)
अणु
	काष्ठा rnbd_srv_session	*sess = sess_dev->sess;

	sess_dev->keep_id = true;
	/* It is alपढ़ोy started to बंद by client's बंद message. */
	अगर (!mutex_trylock(&sess->lock))
		वापस;
	/* first हटाओ sysfs itself to aव्योम deadlock */
	sysfs_हटाओ_file_self(&sess_dev->kobj, &attr->attr);
	rnbd_srv_destroy_dev_session_sysfs(sess_dev);
	mutex_unlock(&sess->lock);
पूर्ण

अटल पूर्णांक process_msg_बंद(काष्ठा rnbd_srv_session *srv_sess,
			     व्योम *data, माप_प्रकार datalen, स्थिर व्योम *usr,
			     माप_प्रकार usrlen)
अणु
	स्थिर काष्ठा rnbd_msg_बंद *बंद_msg = usr;
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = rnbd_get_sess_dev(le32_to_cpu(बंद_msg->device_id),
				      srv_sess);
	अगर (IS_ERR(sess_dev))
		वापस 0;

	rnbd_put_sess_dev(sess_dev);
	mutex_lock(&srv_sess->lock);
	rnbd_srv_destroy_dev_session_sysfs(sess_dev);
	mutex_unlock(&srv_sess->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक process_msg_खोलो(काष्ठा rnbd_srv_session *srv_sess,
			    स्थिर व्योम *msg, माप_प्रकार len,
			    व्योम *data, माप_प्रकार datalen);

अटल पूर्णांक process_msg_sess_info(काष्ठा rnbd_srv_session *srv_sess,
				 स्थिर व्योम *msg, माप_प्रकार len,
				 व्योम *data, माप_प्रकार datalen);

अटल पूर्णांक rnbd_srv_rdma_ev(व्योम *priv,
			    काष्ठा rtrs_srv_op *id, पूर्णांक dir,
			    व्योम *data, माप_प्रकार datalen, स्थिर व्योम *usr,
			    माप_प्रकार usrlen)
अणु
	काष्ठा rnbd_srv_session *srv_sess = priv;
	स्थिर काष्ठा rnbd_msg_hdr *hdr = usr;
	पूर्णांक ret = 0;
	u16 type;

	अगर (WARN_ON_ONCE(!srv_sess))
		वापस -ENODEV;

	type = le16_to_cpu(hdr->type);

	चयन (type) अणु
	हाल RNBD_MSG_IO:
		वापस process_rdma(srv_sess, id, data, datalen, usr, usrlen);
	हाल RNBD_MSG_CLOSE:
		ret = process_msg_बंद(srv_sess, data, datalen, usr, usrlen);
		अवरोध;
	हाल RNBD_MSG_OPEN:
		ret = process_msg_खोलो(srv_sess, usr, usrlen, data, datalen);
		अवरोध;
	हाल RNBD_MSG_SESS_INFO:
		ret = process_msg_sess_info(srv_sess, usr, usrlen, data,
					    datalen);
		अवरोध;
	शेष:
		pr_warn("Received unexpected message type %d with dir %d from session %s\n",
			type, dir, srv_sess->sessname);
		वापस -EINVAL;
	पूर्ण

	rtrs_srv_resp_rdma(id, ret);
	वापस 0;
पूर्ण

अटल काष्ठा rnbd_srv_sess_dev
*rnbd_sess_dev_alloc(काष्ठा rnbd_srv_session *srv_sess)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;
	पूर्णांक error;

	sess_dev = kzalloc(माप(*sess_dev), GFP_KERNEL);
	अगर (!sess_dev)
		वापस ERR_PTR(-ENOMEM);

	error = xa_alloc(&srv_sess->index_idr, &sess_dev->device_id, sess_dev,
			 xa_limit_32b, GFP_NOWAIT);
	अगर (error < 0) अणु
		pr_warn("Allocating idr failed, err: %d\n", error);
		kमुक्त(sess_dev);
		वापस ERR_PTR(error);
	पूर्ण

	वापस sess_dev;
पूर्ण

अटल काष्ठा rnbd_srv_dev *rnbd_srv_init_srv_dev(स्थिर अक्षर *id)
अणु
	काष्ठा rnbd_srv_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	strscpy(dev->id, id, माप(dev->id));
	kref_init(&dev->kref);
	INIT_LIST_HEAD(&dev->sess_dev_list);
	mutex_init(&dev->lock);

	वापस dev;
पूर्ण

अटल काष्ठा rnbd_srv_dev *
rnbd_srv_find_or_add_srv_dev(काष्ठा rnbd_srv_dev *new_dev)
अणु
	काष्ठा rnbd_srv_dev *dev;

	spin_lock(&dev_lock);
	list_क्रम_each_entry(dev, &dev_list, list) अणु
		अगर (!म_भेदन(dev->id, new_dev->id, माप(dev->id))) अणु
			अगर (!kref_get_unless_zero(&dev->kref))
				/*
				 * We lost the race, device is almost dead.
				 *  Continue traversing to find a valid one.
				 */
				जारी;
			spin_unlock(&dev_lock);
			वापस dev;
		पूर्ण
	पूर्ण
	list_add(&new_dev->list, &dev_list);
	spin_unlock(&dev_lock);

	वापस new_dev;
पूर्ण

अटल पूर्णांक rnbd_srv_check_update_खोलो_perm(काष्ठा rnbd_srv_dev *srv_dev,
					    काष्ठा rnbd_srv_session *srv_sess,
					    क्रमागत rnbd_access_mode access_mode)
अणु
	पूर्णांक ret = -EPERM;

	mutex_lock(&srv_dev->lock);

	चयन (access_mode) अणु
	हाल RNBD_ACCESS_RO:
		ret = 0;
		अवरोध;
	हाल RNBD_ACCESS_RW:
		अगर (srv_dev->खोलो_ग_लिखो_cnt == 0)  अणु
			srv_dev->खोलो_ग_लिखो_cnt++;
			ret = 0;
		पूर्ण अन्यथा अणु
			pr_err("Mapping device '%s' for session %s with RW permissions failed. Device already opened as 'RW' by %d client(s), access mode %s.\n",
			       srv_dev->id, srv_sess->sessname,
			       srv_dev->खोलो_ग_लिखो_cnt,
			       rnbd_access_mode_str(access_mode));
		पूर्ण
		अवरोध;
	हाल RNBD_ACCESS_MIGRATION:
		अगर (srv_dev->खोलो_ग_लिखो_cnt < 2) अणु
			srv_dev->खोलो_ग_लिखो_cnt++;
			ret = 0;
		पूर्ण अन्यथा अणु
			pr_err("Mapping device '%s' for session %s with migration permissions failed. Device already opened as 'RW' by %d client(s), access mode %s.\n",
			       srv_dev->id, srv_sess->sessname,
			       srv_dev->खोलो_ग_लिखो_cnt,
			       rnbd_access_mode_str(access_mode));
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Received mapping request for device '%s' on session %s with invalid access mode: %d\n",
		       srv_dev->id, srv_sess->sessname, access_mode);
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&srv_dev->lock);

	वापस ret;
पूर्ण

अटल काष्ठा rnbd_srv_dev *
rnbd_srv_get_or_create_srv_dev(काष्ठा rnbd_dev *rnbd_dev,
				काष्ठा rnbd_srv_session *srv_sess,
				क्रमागत rnbd_access_mode access_mode)
अणु
	पूर्णांक ret;
	काष्ठा rnbd_srv_dev *new_dev, *dev;

	new_dev = rnbd_srv_init_srv_dev(rnbd_dev->name);
	अगर (IS_ERR(new_dev))
		वापस new_dev;

	dev = rnbd_srv_find_or_add_srv_dev(new_dev);
	अगर (dev != new_dev)
		kमुक्त(new_dev);

	ret = rnbd_srv_check_update_खोलो_perm(dev, srv_sess, access_mode);
	अगर (ret) अणु
		rnbd_put_srv_dev(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम rnbd_srv_fill_msg_खोलो_rsp(काष्ठा rnbd_msg_खोलो_rsp *rsp,
					काष्ठा rnbd_srv_sess_dev *sess_dev)
अणु
	काष्ठा rnbd_dev *rnbd_dev = sess_dev->rnbd_dev;
	काष्ठा request_queue *q = bdev_get_queue(rnbd_dev->bdev);

	rsp->hdr.type = cpu_to_le16(RNBD_MSG_OPEN_RSP);
	rsp->device_id =
		cpu_to_le32(sess_dev->device_id);
	rsp->nsectors =
		cpu_to_le64(get_capacity(rnbd_dev->bdev->bd_disk));
	rsp->logical_block_size	=
		cpu_to_le16(bdev_logical_block_size(rnbd_dev->bdev));
	rsp->physical_block_size =
		cpu_to_le16(bdev_physical_block_size(rnbd_dev->bdev));
	rsp->max_segments =
		cpu_to_le16(rnbd_dev_get_max_segs(rnbd_dev));
	rsp->max_hw_sectors =
		cpu_to_le32(rnbd_dev_get_max_hw_sects(rnbd_dev));
	rsp->max_ग_लिखो_same_sectors =
		cpu_to_le32(bdev_ग_लिखो_same(rnbd_dev->bdev));
	rsp->max_discard_sectors =
		cpu_to_le32(rnbd_dev_get_max_discard_sects(rnbd_dev));
	rsp->discard_granularity =
		cpu_to_le32(rnbd_dev_get_discard_granularity(rnbd_dev));
	rsp->discard_alignment =
		cpu_to_le32(rnbd_dev_get_discard_alignment(rnbd_dev));
	rsp->secure_discard =
		cpu_to_le16(rnbd_dev_get_secure_discard(rnbd_dev));
	rsp->rotational = !blk_queue_nonrot(q);
	rsp->cache_policy = 0;
	अगर (test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		rsp->cache_policy |= RNBD_WRITEBACK;
	अगर (blk_queue_fua(q))
		rsp->cache_policy |= RNBD_FUA;
पूर्ण

अटल काष्ठा rnbd_srv_sess_dev *
rnbd_srv_create_set_sess_dev(काष्ठा rnbd_srv_session *srv_sess,
			      स्थिर काष्ठा rnbd_msg_खोलो *खोलो_msg,
			      काष्ठा rnbd_dev *rnbd_dev, भ_शेषe_t खोलो_flags,
			      काष्ठा rnbd_srv_dev *srv_dev)
अणु
	काष्ठा rnbd_srv_sess_dev *sdev = rnbd_sess_dev_alloc(srv_sess);

	अगर (IS_ERR(sdev))
		वापस sdev;

	kref_init(&sdev->kref);

	strscpy(sdev->pathname, खोलो_msg->dev_name, माप(sdev->pathname));

	sdev->rnbd_dev		= rnbd_dev;
	sdev->sess		= srv_sess;
	sdev->dev		= srv_dev;
	sdev->खोलो_flags	= खोलो_flags;
	sdev->access_mode	= खोलो_msg->access_mode;

	वापस sdev;
पूर्ण

अटल अक्षर *rnbd_srv_get_full_path(काष्ठा rnbd_srv_session *srv_sess,
				     स्थिर अक्षर *dev_name)
अणु
	अक्षर *full_path;
	अक्षर *a, *b;

	full_path = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!full_path)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Replace %SESSNAME% with a real session name in order to
	 * create device namespace.
	 */
	a = strnstr(dev_search_path, "%SESSNAME%", माप(dev_search_path));
	अगर (a) अणु
		पूर्णांक len = a - dev_search_path;

		len = snम_लिखो(full_path, PATH_MAX, "%.*s/%s/%s", len,
			       dev_search_path, srv_sess->sessname, dev_name);
		अगर (len >= PATH_MAX) अणु
			pr_err("Too long path: %s, %s, %s\n",
			       dev_search_path, srv_sess->sessname, dev_name);
			kमुक्त(full_path);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		snम_लिखो(full_path, PATH_MAX, "%s/%s",
			 dev_search_path, dev_name);
	पूर्ण

	/* eliminitate duplicated slashes */
	a = म_अक्षर(full_path, '/');
	b = a;
	जबतक (*b != '\0') अणु
		अगर (*b == '/' && *a == '/') अणु
			b++;
		पूर्ण अन्यथा अणु
			a++;
			*a = *b;
			b++;
		पूर्ण
	पूर्ण
	a++;
	*a = '\0';

	वापस full_path;
पूर्ण

अटल पूर्णांक process_msg_sess_info(काष्ठा rnbd_srv_session *srv_sess,
				 स्थिर व्योम *msg, माप_प्रकार len,
				 व्योम *data, माप_प्रकार datalen)
अणु
	स्थिर काष्ठा rnbd_msg_sess_info *sess_info_msg = msg;
	काष्ठा rnbd_msg_sess_info_rsp *rsp = data;

	srv_sess->ver = min_t(u8, sess_info_msg->ver, RNBD_PROTO_VER_MAJOR);
	pr_debug("Session %s using protocol version %d (client version: %d, server version: %d)\n",
		 srv_sess->sessname, srv_sess->ver,
		 sess_info_msg->ver, RNBD_PROTO_VER_MAJOR);

	rsp->hdr.type = cpu_to_le16(RNBD_MSG_SESS_INFO_RSP);
	rsp->ver = srv_sess->ver;

	वापस 0;
पूर्ण

/**
 * find_srv_sess_dev() - a dev is alपढ़ोy खोलोed by this name
 * @srv_sess:	the session to search.
 * @dev_name:	string containing the name of the device.
 *
 * Return काष्ठा rnbd_srv_sess_dev अगर srv_sess alपढ़ोy खोलोed the dev_name
 * शून्य अगर the session didn't खोलो the device yet.
 */
अटल काष्ठा rnbd_srv_sess_dev *
find_srv_sess_dev(काष्ठा rnbd_srv_session *srv_sess, स्थिर अक्षर *dev_name)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	अगर (list_empty(&srv_sess->sess_dev_list))
		वापस शून्य;

	list_क्रम_each_entry(sess_dev, &srv_sess->sess_dev_list, sess_list)
		अगर (!म_भेद(sess_dev->pathname, dev_name))
			वापस sess_dev;

	वापस शून्य;
पूर्ण

अटल पूर्णांक process_msg_खोलो(काष्ठा rnbd_srv_session *srv_sess,
			    स्थिर व्योम *msg, माप_प्रकार len,
			    व्योम *data, माप_प्रकार datalen)
अणु
	पूर्णांक ret;
	काष्ठा rnbd_srv_dev *srv_dev;
	काष्ठा rnbd_srv_sess_dev *srv_sess_dev;
	स्थिर काष्ठा rnbd_msg_खोलो *खोलो_msg = msg;
	भ_शेषe_t खोलो_flags;
	अक्षर *full_path;
	काष्ठा rnbd_dev *rnbd_dev;
	काष्ठा rnbd_msg_खोलो_rsp *rsp = data;

	pr_debug("Open message received: session='%s' path='%s' access_mode=%d\n",
		 srv_sess->sessname, खोलो_msg->dev_name,
		 खोलो_msg->access_mode);
	खोलो_flags = FMODE_READ;
	अगर (खोलो_msg->access_mode != RNBD_ACCESS_RO)
		खोलो_flags |= FMODE_WRITE;

	mutex_lock(&srv_sess->lock);

	srv_sess_dev = find_srv_sess_dev(srv_sess, खोलो_msg->dev_name);
	अगर (srv_sess_dev)
		जाओ fill_response;

	अगर ((म_माप(dev_search_path) + म_माप(खोलो_msg->dev_name))
	    >= PATH_MAX) अणु
		pr_err("Opening device for session %s failed, device path too long. '%s/%s' is longer than PATH_MAX (%d)\n",
		       srv_sess->sessname, dev_search_path, खोलो_msg->dev_name,
		       PATH_MAX);
		ret = -EINVAL;
		जाओ reject;
	पूर्ण
	अगर (म_माला(खोलो_msg->dev_name, "..")) अणु
		pr_err("Opening device for session %s failed, device path %s contains relative path ..\n",
		       srv_sess->sessname, खोलो_msg->dev_name);
		ret = -EINVAL;
		जाओ reject;
	पूर्ण
	full_path = rnbd_srv_get_full_path(srv_sess, खोलो_msg->dev_name);
	अगर (IS_ERR(full_path)) अणु
		ret = PTR_ERR(full_path);
		pr_err("Opening device '%s' for client %s failed, failed to get device full path, err: %d\n",
		       खोलो_msg->dev_name, srv_sess->sessname, ret);
		जाओ reject;
	पूर्ण

	rnbd_dev = rnbd_dev_खोलो(full_path, खोलो_flags,
				 &srv_sess->sess_bio_set);
	अगर (IS_ERR(rnbd_dev)) अणु
		pr_err("Opening device '%s' on session %s failed, failed to open the block device, err: %ld\n",
		       full_path, srv_sess->sessname, PTR_ERR(rnbd_dev));
		ret = PTR_ERR(rnbd_dev);
		जाओ मुक्त_path;
	पूर्ण

	srv_dev = rnbd_srv_get_or_create_srv_dev(rnbd_dev, srv_sess,
						  खोलो_msg->access_mode);
	अगर (IS_ERR(srv_dev)) अणु
		pr_err("Opening device '%s' on session %s failed, creating srv_dev failed, err: %ld\n",
		       full_path, srv_sess->sessname, PTR_ERR(srv_dev));
		ret = PTR_ERR(srv_dev);
		जाओ rnbd_dev_बंद;
	पूर्ण

	srv_sess_dev = rnbd_srv_create_set_sess_dev(srv_sess, खोलो_msg,
						     rnbd_dev, खोलो_flags,
						     srv_dev);
	अगर (IS_ERR(srv_sess_dev)) अणु
		pr_err("Opening device '%s' on session %s failed, creating sess_dev failed, err: %ld\n",
		       full_path, srv_sess->sessname, PTR_ERR(srv_sess_dev));
		ret = PTR_ERR(srv_sess_dev);
		जाओ srv_dev_put;
	पूर्ण

	/* Create the srv_dev sysfs files अगर they haven't been created yet. The
	 * reason to delay the creation is not to create the sysfs files beक्रमe
	 * we are sure the device can be खोलोed.
	 */
	mutex_lock(&srv_dev->lock);
	अगर (!srv_dev->dev_kobj.state_in_sysfs) अणु
		ret = rnbd_srv_create_dev_sysfs(srv_dev, rnbd_dev->bdev,
						 rnbd_dev->name);
		अगर (ret) अणु
			mutex_unlock(&srv_dev->lock);
			rnbd_srv_err(srv_sess_dev,
				      "Opening device failed, failed to create device sysfs files, err: %d\n",
				      ret);
			जाओ मुक्त_srv_sess_dev;
		पूर्ण
	पूर्ण

	ret = rnbd_srv_create_dev_session_sysfs(srv_sess_dev);
	अगर (ret) अणु
		mutex_unlock(&srv_dev->lock);
		rnbd_srv_err(srv_sess_dev,
			      "Opening device failed, failed to create dev client sysfs files, err: %d\n",
			      ret);
		जाओ मुक्त_srv_sess_dev;
	पूर्ण

	list_add(&srv_sess_dev->dev_list, &srv_dev->sess_dev_list);
	mutex_unlock(&srv_dev->lock);

	list_add(&srv_sess_dev->sess_list, &srv_sess->sess_dev_list);

	rnbd_srv_info(srv_sess_dev, "Opened device '%s'\n", srv_dev->id);

	kमुक्त(full_path);

fill_response:
	rnbd_srv_fill_msg_खोलो_rsp(rsp, srv_sess_dev);
	mutex_unlock(&srv_sess->lock);
	वापस 0;

मुक्त_srv_sess_dev:
	xa_erase(&srv_sess->index_idr, srv_sess_dev->device_id);
	synchronize_rcu();
	kमुक्त(srv_sess_dev);
srv_dev_put:
	अगर (खोलो_msg->access_mode != RNBD_ACCESS_RO) अणु
		mutex_lock(&srv_dev->lock);
		srv_dev->खोलो_ग_लिखो_cnt--;
		mutex_unlock(&srv_dev->lock);
	पूर्ण
	rnbd_put_srv_dev(srv_dev);
rnbd_dev_बंद:
	rnbd_dev_बंद(rnbd_dev);
मुक्त_path:
	kमुक्त(full_path);
reject:
	mutex_unlock(&srv_sess->lock);
	वापस ret;
पूर्ण

अटल काष्ठा rtrs_srv_ctx *rtrs_ctx;

अटल काष्ठा rtrs_srv_ops rtrs_ops;
अटल पूर्णांक __init rnbd_srv_init_module(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_hdr) != 4);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_sess_info) != 36);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_sess_info_rsp) != 36);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_खोलो) != 264);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_बंद) != 8);
	BUILD_BUG_ON(माप(काष्ठा rnbd_msg_खोलो_rsp) != 56);
	rtrs_ops = (काष्ठा rtrs_srv_ops) अणु
		.rdma_ev = rnbd_srv_rdma_ev,
		.link_ev = rnbd_srv_link_ev,
	पूर्ण;
	rtrs_ctx = rtrs_srv_खोलो(&rtrs_ops, port_nr);
	अगर (IS_ERR(rtrs_ctx)) अणु
		err = PTR_ERR(rtrs_ctx);
		pr_err("rtrs_srv_open(), err: %d\n", err);
		वापस err;
	पूर्ण

	err = rnbd_srv_create_sysfs_files();
	अगर (err) अणु
		pr_err("rnbd_srv_create_sysfs_files(), err: %d\n", err);
		rtrs_srv_बंद(rtrs_ctx);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास rnbd_srv_cleanup_module(व्योम)
अणु
	rtrs_srv_बंद(rtrs_ctx);
	WARN_ON(!list_empty(&sess_list));
	rnbd_srv_destroy_sysfs_files();
पूर्ण

module_init(rnbd_srv_init_module);
module_निकास(rnbd_srv_cleanup_module);
