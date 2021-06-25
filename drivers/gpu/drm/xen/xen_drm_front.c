<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>

#समावेश <xen/platक्रमm_pci.h>
#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>

#समावेश <xen/xen-front-pgdir-shbuf.h>
#समावेश <xen/पूर्णांकerface/io/displअगर.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_cfg.h"
#समावेश "xen_drm_front_evtchnl.h"
#समावेश "xen_drm_front_gem.h"
#समावेश "xen_drm_front_kms.h"

काष्ठा xen_drm_front_dbuf अणु
	काष्ठा list_head list;
	u64 dbuf_cookie;
	u64 fb_cookie;

	काष्ठा xen_front_pgdir_shbuf shbuf;
पूर्ण;

अटल व्योम dbuf_add_to_list(काष्ठा xen_drm_front_info *front_info,
			     काष्ठा xen_drm_front_dbuf *dbuf, u64 dbuf_cookie)
अणु
	dbuf->dbuf_cookie = dbuf_cookie;
	list_add(&dbuf->list, &front_info->dbuf_list);
पूर्ण

अटल काष्ठा xen_drm_front_dbuf *dbuf_get(काष्ठा list_head *dbuf_list,
					   u64 dbuf_cookie)
अणु
	काष्ठा xen_drm_front_dbuf *buf, *q;

	list_क्रम_each_entry_safe(buf, q, dbuf_list, list)
		अगर (buf->dbuf_cookie == dbuf_cookie)
			वापस buf;

	वापस शून्य;
पूर्ण

अटल व्योम dbuf_मुक्त(काष्ठा list_head *dbuf_list, u64 dbuf_cookie)
अणु
	काष्ठा xen_drm_front_dbuf *buf, *q;

	list_क्रम_each_entry_safe(buf, q, dbuf_list, list)
		अगर (buf->dbuf_cookie == dbuf_cookie) अणु
			list_del(&buf->list);
			xen_front_pgdir_shbuf_unmap(&buf->shbuf);
			xen_front_pgdir_shbuf_मुक्त(&buf->shbuf);
			kमुक्त(buf);
			अवरोध;
		पूर्ण
पूर्ण

अटल व्योम dbuf_मुक्त_all(काष्ठा list_head *dbuf_list)
अणु
	काष्ठा xen_drm_front_dbuf *buf, *q;

	list_क्रम_each_entry_safe(buf, q, dbuf_list, list) अणु
		list_del(&buf->list);
		xen_front_pgdir_shbuf_unmap(&buf->shbuf);
		xen_front_pgdir_shbuf_मुक्त(&buf->shbuf);
		kमुक्त(buf);
	पूर्ण
पूर्ण

अटल काष्ठा xendispl_req *
be_prepare_req(काष्ठा xen_drm_front_evtchnl *evtchnl, u8 operation)
अणु
	काष्ठा xendispl_req *req;

	req = RING_GET_REQUEST(&evtchnl->u.req.ring,
			       evtchnl->u.req.ring.req_prod_pvt);
	req->operation = operation;
	req->id = evtchnl->evt_next_id++;
	evtchnl->evt_id = req->id;
	वापस req;
पूर्ण

अटल पूर्णांक be_stream_करो_io(काष्ठा xen_drm_front_evtchnl *evtchnl,
			   काष्ठा xendispl_req *req)
अणु
	reinit_completion(&evtchnl->u.req.completion);
	अगर (unlikely(evtchnl->state != EVTCHNL_STATE_CONNECTED))
		वापस -EIO;

	xen_drm_front_evtchnl_flush(evtchnl);
	वापस 0;
पूर्ण

अटल पूर्णांक be_stream_रुको_io(काष्ठा xen_drm_front_evtchnl *evtchnl)
अणु
	अगर (रुको_क्रम_completion_समयout(&evtchnl->u.req.completion,
			msecs_to_jअगरfies(XEN_DRM_FRONT_WAIT_BACK_MS)) <= 0)
		वापस -ETIMEDOUT;

	वापस evtchnl->u.req.resp_status;
पूर्ण

पूर्णांक xen_drm_front_mode_set(काष्ठा xen_drm_front_drm_pipeline *pipeline,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 bpp, u64 fb_cookie)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xen_drm_front_info *front_info;
	काष्ठा xendispl_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	front_info = pipeline->drm_info->front_info;
	evtchnl = &front_info->evt_pairs[pipeline->index].req;
	अगर (unlikely(!evtchnl))
		वापस -EIO;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_SET_CONFIG);
	req->op.set_config.x = x;
	req->op.set_config.y = y;
	req->op.set_config.width = width;
	req->op.set_config.height = height;
	req->op.set_config.bpp = bpp;
	req->op.set_config.fb_cookie = fb_cookie;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_dbuf_create(काष्ठा xen_drm_front_info *front_info,
			      u64 dbuf_cookie, u32 width, u32 height,
			      u32 bpp, u64 size, u32 offset,
			      काष्ठा page **pages)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xen_drm_front_dbuf *dbuf;
	काष्ठा xendispl_req *req;
	काष्ठा xen_front_pgdir_shbuf_cfg buf_cfg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	evtchnl = &front_info->evt_pairs[GENERIC_OP_EVT_CHNL].req;
	अगर (unlikely(!evtchnl))
		वापस -EIO;

	dbuf = kzalloc(माप(*dbuf), GFP_KERNEL);
	अगर (!dbuf)
		वापस -ENOMEM;

	dbuf_add_to_list(front_info, dbuf, dbuf_cookie);

	स_रखो(&buf_cfg, 0, माप(buf_cfg));
	buf_cfg.xb_dev = front_info->xb_dev;
	buf_cfg.num_pages = DIV_ROUND_UP(size, PAGE_SIZE);
	buf_cfg.pages = pages;
	buf_cfg.pgdir = &dbuf->shbuf;
	buf_cfg.be_alloc = front_info->cfg.be_alloc;

	ret = xen_front_pgdir_shbuf_alloc(&buf_cfg);
	अगर (ret < 0)
		जाओ fail_shbuf_alloc;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_DBUF_CREATE);
	req->op.dbuf_create.gref_directory =
			xen_front_pgdir_shbuf_get_dir_start(&dbuf->shbuf);
	req->op.dbuf_create.buffer_sz = size;
	req->op.dbuf_create.data_ofs = offset;
	req->op.dbuf_create.dbuf_cookie = dbuf_cookie;
	req->op.dbuf_create.width = width;
	req->op.dbuf_create.height = height;
	req->op.dbuf_create.bpp = bpp;
	अगर (buf_cfg.be_alloc)
		req->op.dbuf_create.flags |= XENDISPL_DBUF_FLG_REQ_ALLOC;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret < 0)
		जाओ fail;

	ret = be_stream_रुको_io(evtchnl);
	अगर (ret < 0)
		जाओ fail;

	ret = xen_front_pgdir_shbuf_map(&dbuf->shbuf);
	अगर (ret < 0)
		जाओ fail;

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस 0;

fail:
	mutex_unlock(&evtchnl->u.req.req_io_lock);
fail_shbuf_alloc:
	dbuf_मुक्त(&front_info->dbuf_list, dbuf_cookie);
	वापस ret;
पूर्ण

अटल पूर्णांक xen_drm_front_dbuf_destroy(काष्ठा xen_drm_front_info *front_info,
				      u64 dbuf_cookie)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xendispl_req *req;
	अचिन्हित दीर्घ flags;
	bool be_alloc;
	पूर्णांक ret;

	evtchnl = &front_info->evt_pairs[GENERIC_OP_EVT_CHNL].req;
	अगर (unlikely(!evtchnl))
		वापस -EIO;

	be_alloc = front_info->cfg.be_alloc;

	/*
	 * For the backend allocated buffer release references now, so backend
	 * can मुक्त the buffer.
	 */
	अगर (be_alloc)
		dbuf_मुक्त(&front_info->dbuf_list, dbuf_cookie);

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_DBUF_DESTROY);
	req->op.dbuf_destroy.dbuf_cookie = dbuf_cookie;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	/*
	 * Do this regardless of communication status with the backend:
	 * अगर we cannot हटाओ remote resources हटाओ what we can locally.
	 */
	अगर (!be_alloc)
		dbuf_मुक्त(&front_info->dbuf_list, dbuf_cookie);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_fb_attach(काष्ठा xen_drm_front_info *front_info,
			    u64 dbuf_cookie, u64 fb_cookie, u32 width,
			    u32 height, u32 pixel_क्रमmat)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xen_drm_front_dbuf *buf;
	काष्ठा xendispl_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	evtchnl = &front_info->evt_pairs[GENERIC_OP_EVT_CHNL].req;
	अगर (unlikely(!evtchnl))
		वापस -EIO;

	buf = dbuf_get(&front_info->dbuf_list, dbuf_cookie);
	अगर (!buf)
		वापस -EINVAL;

	buf->fb_cookie = fb_cookie;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_FB_ATTACH);
	req->op.fb_attach.dbuf_cookie = dbuf_cookie;
	req->op.fb_attach.fb_cookie = fb_cookie;
	req->op.fb_attach.width = width;
	req->op.fb_attach.height = height;
	req->op.fb_attach.pixel_क्रमmat = pixel_क्रमmat;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_fb_detach(काष्ठा xen_drm_front_info *front_info,
			    u64 fb_cookie)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xendispl_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	evtchnl = &front_info->evt_pairs[GENERIC_OP_EVT_CHNL].req;
	अगर (unlikely(!evtchnl))
		वापस -EIO;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_FB_DETACH);
	req->op.fb_detach.fb_cookie = fb_cookie;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_page_flip(काष्ठा xen_drm_front_info *front_info,
			    पूर्णांक conn_idx, u64 fb_cookie)
अणु
	काष्ठा xen_drm_front_evtchnl *evtchnl;
	काष्ठा xendispl_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (unlikely(conn_idx >= front_info->num_evt_pairs))
		वापस -EINVAL;

	evtchnl = &front_info->evt_pairs[conn_idx].req;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	spin_lock_irqsave(&front_info->io_lock, flags);
	req = be_prepare_req(evtchnl, XENDISPL_OP_PG_FLIP);
	req->op.pg_flip.fb_cookie = fb_cookie;

	ret = be_stream_करो_io(evtchnl, req);
	spin_unlock_irqrestore(&front_info->io_lock, flags);

	अगर (ret == 0)
		ret = be_stream_रुको_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	वापस ret;
पूर्ण

व्योम xen_drm_front_on_frame_करोne(काष्ठा xen_drm_front_info *front_info,
				 पूर्णांक conn_idx, u64 fb_cookie)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = front_info->drm_info;

	अगर (unlikely(conn_idx >= front_info->cfg.num_connectors))
		वापस;

	xen_drm_front_kms_on_frame_करोne(&drm_info->pipeline[conn_idx],
					fb_cookie);
पूर्ण

व्योम xen_drm_front_gem_object_मुक्त(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = obj->dev->dev_निजी;
	पूर्णांक idx;

	अगर (drm_dev_enter(obj->dev, &idx)) अणु
		xen_drm_front_dbuf_destroy(drm_info->front_info,
					   xen_drm_front_dbuf_to_cookie(obj));
		drm_dev_निकास(idx);
	पूर्ण अन्यथा अणु
		dbuf_मुक्त(&drm_info->front_info->dbuf_list,
			  xen_drm_front_dbuf_to_cookie(obj));
	पूर्ण

	xen_drm_front_gem_मुक्त_object_unlocked(obj);
पूर्ण

अटल पूर्णांक xen_drm_drv_dumb_create(काष्ठा drm_file *filp,
				   काष्ठा drm_device *dev,
				   काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = dev->dev_निजी;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	/*
	 * Dumb creation is a two stage process: first we create a fully
	 * स्थिरructed GEM object which is communicated to the backend, and
	 * only after that we can create GEM's handle. This is करोne so,
	 * because of the possible races: once you create a handle it becomes
	 * immediately visible to user-space, so the latter can try accessing
	 * object without pages etc.
	 * For details also see drm_gem_handle_create
	 */
	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	obj = xen_drm_front_gem_create(dev, args->size);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ fail;
	पूर्ण

	ret = xen_drm_front_dbuf_create(drm_info->front_info,
					xen_drm_front_dbuf_to_cookie(obj),
					args->width, args->height, args->bpp,
					args->size, 0,
					xen_drm_front_gem_get_pages(obj));
	अगर (ret)
		जाओ fail_backend;

	/* This is the tail of GEM object creation */
	ret = drm_gem_handle_create(filp, obj, &args->handle);
	अगर (ret)
		जाओ fail_handle;

	/* Drop reference from allocate - handle holds it now */
	drm_gem_object_put(obj);
	वापस 0;

fail_handle:
	xen_drm_front_dbuf_destroy(drm_info->front_info,
				   xen_drm_front_dbuf_to_cookie(obj));
fail_backend:
	/* drop reference from allocate */
	drm_gem_object_put(obj);
fail:
	DRM_ERROR("Failed to create dumb buffer: %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम xen_drm_drv_release(काष्ठा drm_device *dev)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = dev->dev_निजी;
	काष्ठा xen_drm_front_info *front_info = drm_info->front_info;

	xen_drm_front_kms_fini(drm_info);

	drm_atomic_helper_shutकरोwn(dev);
	drm_mode_config_cleanup(dev);

	अगर (front_info->cfg.be_alloc)
		xenbus_चयन_state(front_info->xb_dev,
				    XenbusStateInitialising);

	kमुक्त(drm_info);
पूर्ण

अटल स्थिर काष्ठा file_operations xen_drm_dev_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = drm_खोलो,
	.release        = drm_release,
	.unlocked_ioctl = drm_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = drm_compat_ioctl,
#पूर्ण_अगर
	.poll           = drm_poll,
	.पढ़ो           = drm_पढ़ो,
	.llseek         = no_llseek,
	.mmap           = xen_drm_front_gem_mmap,
पूर्ण;

अटल स्थिर काष्ठा drm_driver xen_drm_driver = अणु
	.driver_features           = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.release                   = xen_drm_drv_release,
	.prime_handle_to_fd        = drm_gem_prime_handle_to_fd,
	.prime_fd_to_handle        = drm_gem_prime_fd_to_handle,
	.gem_prime_import_sg_table = xen_drm_front_gem_import_sg_table,
	.gem_prime_mmap            = xen_drm_front_gem_prime_mmap,
	.dumb_create               = xen_drm_drv_dumb_create,
	.fops                      = &xen_drm_dev_fops,
	.name                      = "xendrm-du",
	.desc                      = "Xen PV DRM Display Unit",
	.date                      = "20180221",
	.major                     = 1,
	.minor                     = 0,

पूर्ण;

अटल पूर्णांक xen_drm_drv_init(काष्ठा xen_drm_front_info *front_info)
अणु
	काष्ठा device *dev = &front_info->xb_dev->dev;
	काष्ठा xen_drm_front_drm_info *drm_info;
	काष्ठा drm_device *drm_dev;
	पूर्णांक ret;

	DRM_INFO("Creating %s\n", xen_drm_driver.desc);

	drm_info = kzalloc(माप(*drm_info), GFP_KERNEL);
	अगर (!drm_info) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	drm_info->front_info = front_info;
	front_info->drm_info = drm_info;

	drm_dev = drm_dev_alloc(&xen_drm_driver, dev);
	अगर (IS_ERR(drm_dev)) अणु
		ret = PTR_ERR(drm_dev);
		जाओ fail_dev;
	पूर्ण

	drm_info->drm_dev = drm_dev;

	drm_dev->dev_निजी = drm_info;

	ret = xen_drm_front_kms_init(drm_info);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize DRM/KMS, ret %d\n", ret);
		जाओ fail_modeset;
	पूर्ण

	ret = drm_dev_रेजिस्टर(drm_dev, 0);
	अगर (ret)
		जाओ fail_रेजिस्टर;

	DRM_INFO("Initialized %s %d.%d.%d %s on minor %d\n",
		 xen_drm_driver.name, xen_drm_driver.major,
		 xen_drm_driver.minor, xen_drm_driver.patchlevel,
		 xen_drm_driver.date, drm_dev->primary->index);

	वापस 0;

fail_रेजिस्टर:
	drm_dev_unरेजिस्टर(drm_dev);
fail_modeset:
	drm_kms_helper_poll_fini(drm_dev);
	drm_mode_config_cleanup(drm_dev);
	drm_dev_put(drm_dev);
fail_dev:
	kमुक्त(drm_info);
	front_info->drm_info = शून्य;
fail:
	वापस ret;
पूर्ण

अटल व्योम xen_drm_drv_fini(काष्ठा xen_drm_front_info *front_info)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = front_info->drm_info;
	काष्ठा drm_device *dev;

	अगर (!drm_info)
		वापस;

	dev = drm_info->drm_dev;
	अगर (!dev)
		वापस;

	/* Nothing to करो अगर device is alपढ़ोy unplugged */
	अगर (drm_dev_is_unplugged(dev))
		वापस;

	drm_kms_helper_poll_fini(dev);
	drm_dev_unplug(dev);
	drm_dev_put(dev);

	front_info->drm_info = शून्य;

	xen_drm_front_evtchnl_मुक्त_all(front_info);
	dbuf_मुक्त_all(&front_info->dbuf_list);

	/*
	 * If we are not using backend allocated buffers, then tell the
	 * backend we are पढ़ोy to (re)initialize. Otherwise, रुको क्रम
	 * drm_driver.release.
	 */
	अगर (!front_info->cfg.be_alloc)
		xenbus_चयन_state(front_info->xb_dev,
				    XenbusStateInitialising);
पूर्ण

अटल पूर्णांक displback_initरुको(काष्ठा xen_drm_front_info *front_info)
अणु
	काष्ठा xen_drm_front_cfg *cfg = &front_info->cfg;
	पूर्णांक ret;

	cfg->front_info = front_info;
	ret = xen_drm_front_cfg_card(front_info, cfg);
	अगर (ret < 0)
		वापस ret;

	DRM_INFO("Have %d connector(s)\n", cfg->num_connectors);
	/* Create event channels क्रम all connectors and publish */
	ret = xen_drm_front_evtchnl_create_all(front_info);
	अगर (ret < 0)
		वापस ret;

	वापस xen_drm_front_evtchnl_publish_all(front_info);
पूर्ण

अटल पूर्णांक displback_connect(काष्ठा xen_drm_front_info *front_info)
अणु
	xen_drm_front_evtchnl_set_state(front_info, EVTCHNL_STATE_CONNECTED);
	वापस xen_drm_drv_init(front_info);
पूर्ण

अटल व्योम displback_disconnect(काष्ठा xen_drm_front_info *front_info)
अणु
	अगर (!front_info->drm_info)
		वापस;

	/* Tell the backend to रुको until we release the DRM driver. */
	xenbus_चयन_state(front_info->xb_dev, XenbusStateReconfiguring);

	xen_drm_drv_fini(front_info);
पूर्ण

अटल व्योम displback_changed(काष्ठा xenbus_device *xb_dev,
			      क्रमागत xenbus_state backend_state)
अणु
	काष्ठा xen_drm_front_info *front_info = dev_get_drvdata(&xb_dev->dev);
	पूर्णांक ret;

	DRM_DEBUG("Backend state is %s, front is %s\n",
		  xenbus_strstate(backend_state),
		  xenbus_strstate(xb_dev->state));

	चयन (backend_state) अणु
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateInitialised:
		अवरोध;

	हाल XenbusStateInitialising:
		अगर (xb_dev->state == XenbusStateReconfiguring)
			अवरोध;

		/* recovering after backend unexpected closure */
		displback_disconnect(front_info);
		अवरोध;

	हाल XenbusStateInitWait:
		अगर (xb_dev->state == XenbusStateReconfiguring)
			अवरोध;

		/* recovering after backend unexpected closure */
		displback_disconnect(front_info);
		अगर (xb_dev->state != XenbusStateInitialising)
			अवरोध;

		ret = displback_initरुको(front_info);
		अगर (ret < 0)
			xenbus_dev_fatal(xb_dev, ret, "initializing frontend");
		अन्यथा
			xenbus_चयन_state(xb_dev, XenbusStateInitialised);
		अवरोध;

	हाल XenbusStateConnected:
		अगर (xb_dev->state != XenbusStateInitialised)
			अवरोध;

		ret = displback_connect(front_info);
		अगर (ret < 0) अणु
			displback_disconnect(front_info);
			xenbus_dev_fatal(xb_dev, ret, "connecting backend");
		पूर्ण अन्यथा अणु
			xenbus_चयन_state(xb_dev, XenbusStateConnected);
		पूर्ण
		अवरोध;

	हाल XenbusStateClosing:
		/*
		 * in this state backend starts मुक्तing resources,
		 * so let it go पूर्णांकo बंदd state, so we can also
		 * हटाओ ours
		 */
		अवरोध;

	हाल XenbusStateUnknown:
	हाल XenbusStateClosed:
		अगर (xb_dev->state == XenbusStateClosed)
			अवरोध;

		displback_disconnect(front_info);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xen_drv_probe(काष्ठा xenbus_device *xb_dev,
			 स्थिर काष्ठा xenbus_device_id *id)
अणु
	काष्ठा xen_drm_front_info *front_info;
	काष्ठा device *dev = &xb_dev->dev;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret < 0) अणु
		DRM_ERROR("Cannot setup DMA mask, ret %d", ret);
		वापस ret;
	पूर्ण

	front_info = devm_kzalloc(&xb_dev->dev,
				  माप(*front_info), GFP_KERNEL);
	अगर (!front_info)
		वापस -ENOMEM;

	front_info->xb_dev = xb_dev;
	spin_lock_init(&front_info->io_lock);
	INIT_LIST_HEAD(&front_info->dbuf_list);
	dev_set_drvdata(&xb_dev->dev, front_info);

	वापस xenbus_चयन_state(xb_dev, XenbusStateInitialising);
पूर्ण

अटल पूर्णांक xen_drv_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xen_drm_front_info *front_info = dev_get_drvdata(&dev->dev);
	पूर्णांक to = 100;

	xenbus_चयन_state(dev, XenbusStateClosing);

	/*
	 * On driver removal it is disconnected from XenBus,
	 * so no backend state change events come via .otherend_changed
	 * callback. This prevents us from निकासing gracefully, e.g.
	 * संकेतing the backend to मुक्त event channels, रुकोing क्रम its
	 * state to change to XenbusStateClosed and cleaning at our end.
	 * Normally when front driver हटाओd backend will finally go पूर्णांकo
	 * XenbusStateInitWait state.
	 *
	 * Workaround: पढ़ो backend's state manually and रुको with समय-out.
	 */
	जबतक ((xenbus_पढ़ो_अचिन्हित(front_info->xb_dev->otherend, "state",
				     XenbusStateUnknown) != XenbusStateInitWait) &&
				     --to)
		msleep(10);

	अगर (!to) अणु
		अचिन्हित पूर्णांक state;

		state = xenbus_पढ़ो_अचिन्हित(front_info->xb_dev->otherend,
					     "state", XenbusStateUnknown);
		DRM_ERROR("Backend state is %s while removing driver\n",
			  xenbus_strstate(state));
	पूर्ण

	xen_drm_drv_fini(front_info);
	xenbus_frontend_बंदd(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xen_driver_ids[] = अणु
	अणु XENDISPL_DRIVER_NAME पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xen_driver = अणु
	.ids = xen_driver_ids,
	.probe = xen_drv_probe,
	.हटाओ = xen_drv_हटाओ,
	.otherend_changed = displback_changed,
पूर्ण;

अटल पूर्णांक __init xen_drv_init(व्योम)
अणु
	/* At the moment we only support हाल with XEN_PAGE_SIZE == PAGE_SIZE */
	अगर (XEN_PAGE_SIZE != PAGE_SIZE) अणु
		DRM_ERROR(XENDISPL_DRIVER_NAME ": different kernel and Xen page sizes are not supported: XEN_PAGE_SIZE (%lu) != PAGE_SIZE (%lu)\n",
			  XEN_PAGE_SIZE, PAGE_SIZE);
		वापस -ENODEV;
	पूर्ण

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	DRM_INFO("Registering XEN PV " XENDISPL_DRIVER_NAME "\n");
	वापस xenbus_रेजिस्टर_frontend(&xen_driver);
पूर्ण

अटल व्योम __निकास xen_drv_fini(व्योम)
अणु
	DRM_INFO("Unregistering XEN PV " XENDISPL_DRIVER_NAME "\n");
	xenbus_unरेजिस्टर_driver(&xen_driver);
पूर्ण

module_init(xen_drv_init);
module_निकास(xen_drv_fini);

MODULE_DESCRIPTION("Xen para-virtualized display device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:" XENDISPL_DRIVER_NAME);
