<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2020 Noralf Trथचnnes
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/lz4.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/gud.h>

#समावेश "gud_internal.h"

/* Only used पूर्णांकernally */
अटल स्थिर काष्ठा drm_क्रमmat_info gud_drm_क्रमmat_r1 = अणु
	.क्रमmat = GUD_DRM_FORMAT_R1,
	.num_planes = 1,
	.अक्षर_per_block = अणु 1, 0, 0 पूर्ण,
	.block_w = अणु 8, 0, 0 पूर्ण,
	.block_h = अणु 1, 0, 0 पूर्ण,
	.hsub = 1,
	.vsub = 1,
पूर्ण;

अटल स्थिर काष्ठा drm_क्रमmat_info gud_drm_क्रमmat_xrgb1111 = अणु
	.क्रमmat = GUD_DRM_FORMAT_XRGB1111,
	.num_planes = 1,
	.अक्षर_per_block = अणु 1, 0, 0 पूर्ण,
	.block_w = अणु 2, 0, 0 पूर्ण,
	.block_h = अणु 1, 0, 0 पूर्ण,
	.hsub = 1,
	.vsub = 1,
पूर्ण;

अटल पूर्णांक gud_usb_control_msg(काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool in,
			       u8 request, u16 value, व्योम *buf, माप_प्रकार len)
अणु
	u8 requesttype = USB_TYPE_VENDOR | USB_RECIP_INTERFACE;
	u8 अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अचिन्हित पूर्णांक pipe;

	अगर (len && !buf)
		वापस -EINVAL;

	अगर (in) अणु
		pipe = usb_rcvctrlpipe(usb, 0);
		requesttype |= USB_सूची_IN;
	पूर्ण अन्यथा अणु
		pipe = usb_sndctrlpipe(usb, 0);
		requesttype |= USB_सूची_OUT;
	पूर्ण

	वापस usb_control_msg(usb, pipe, request, requesttype, value,
			       अगरnum, buf, len, USB_CTRL_GET_TIMEOUT);
पूर्ण

अटल पूर्णांक gud_get_display_descriptor(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				      काष्ठा gud_display_descriptor_req *desc)
अणु
	व्योम *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(माप(*desc), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = gud_usb_control_msg(पूर्णांकf, true, GUD_REQ_GET_DESCRIPTOR, 0, buf, माप(*desc));
	स_नकल(desc, buf, माप(*desc));
	kमुक्त(buf);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(*desc))
		वापस -EIO;

	अगर (desc->magic != le32_to_cpu(GUD_DISPLAY_MAGIC))
		वापस -ENODATA;

	DRM_DEV_DEBUG_DRIVER(&पूर्णांकf->dev,
			     "version=%u flags=0x%x compression=0x%x max_buffer_size=%u\n",
			     desc->version, le32_to_cpu(desc->flags), desc->compression,
			     le32_to_cpu(desc->max_buffer_size));

	अगर (!desc->version || !desc->max_width || !desc->max_height ||
	    le32_to_cpu(desc->min_width) > le32_to_cpu(desc->max_width) ||
	    le32_to_cpu(desc->min_height) > le32_to_cpu(desc->max_height))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक gud_status_to_त्रुटि_सं(u8 status)
अणु
	चयन (status) अणु
	हाल GUD_STATUS_OK:
		वापस 0;
	हाल GUD_STATUS_BUSY:
		वापस -EBUSY;
	हाल GUD_STATUS_REQUEST_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	हाल GUD_STATUS_PROTOCOL_ERROR:
		वापस -EPROTO;
	हाल GUD_STATUS_INVALID_PARAMETER:
		वापस -EINVAL;
	हाल GUD_STATUS_ERROR:
		वापस -EREMOTEIO;
	शेष:
		वापस -EREMOTEIO;
	पूर्ण
पूर्ण

अटल पूर्णांक gud_usb_get_status(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret, status = -EIO;
	u8 *buf;

	buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = gud_usb_control_msg(पूर्णांकf, true, GUD_REQ_GET_STATUS, 0, buf, माप(*buf));
	अगर (ret == माप(*buf))
		status = gud_status_to_त्रुटि_सं(*buf);
	kमुक्त(buf);

	अगर (ret < 0)
		वापस ret;

	वापस status;
पूर्ण

अटल पूर्णांक gud_usb_transfer(काष्ठा gud_device *gdrm, bool in, u8 request, u16 index,
			    व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(gdrm->drm.dev);
	पूर्णांक idx, ret;

	drm_dbg(&gdrm->drm, "%s: request=0x%x index=%u len=%zu\n",
		in ? "get" : "set", request, index, len);

	अगर (!drm_dev_enter(&gdrm->drm, &idx))
		वापस -ENODEV;

	mutex_lock(&gdrm->ctrl_lock);

	ret = gud_usb_control_msg(पूर्णांकf, in, request, index, buf, len);
	अगर (ret == -EPIPE || ((gdrm->flags & GUD_DISPLAY_FLAG_STATUS_ON_SET) && !in && ret >= 0)) अणु
		पूर्णांक status;

		status = gud_usb_get_status(पूर्णांकf);
		अगर (status < 0) अणु
			ret = status;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			dev_err_once(gdrm->drm.dev,
				     "Unexpected status OK for failed transfer\n");
			ret = -EPIPE;
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		drm_dbg(&gdrm->drm, "ret=%d\n", ret);
		gdrm->stats_num_errors++;
	पूर्ण

	mutex_unlock(&gdrm->ctrl_lock);
	drm_dev_निकास(idx);

	वापस ret;
पूर्ण

/*
 * @buf cannot be allocated on the stack.
 * Returns number of bytes received or negative error code on failure.
 */
पूर्णांक gud_usb_get(काष्ठा gud_device *gdrm, u8 request, u16 index, व्योम *buf, माप_प्रकार max_len)
अणु
	वापस gud_usb_transfer(gdrm, true, request, index, buf, max_len);
पूर्ण

/*
 * @buf can be allocated on the stack or शून्य.
 * Returns zero on success or negative error code on failure.
 */
पूर्णांक gud_usb_set(काष्ठा gud_device *gdrm, u8 request, u16 index, व्योम *buf, माप_प्रकार len)
अणु
	व्योम *trbuf = शून्य;
	पूर्णांक ret;

	अगर (buf && len) अणु
		trbuf = kmemdup(buf, len, GFP_KERNEL);
		अगर (!trbuf)
			वापस -ENOMEM;
	पूर्ण

	ret = gud_usb_transfer(gdrm, false, request, index, trbuf, len);
	kमुक्त(trbuf);
	अगर (ret < 0)
		वापस ret;

	वापस ret != len ? -EIO : 0;
पूर्ण

/*
 * @val can be allocated on the stack.
 * Returns zero on success or negative error code on failure.
 */
पूर्णांक gud_usb_get_u8(काष्ठा gud_device *gdrm, u8 request, u16 index, u8 *val)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(माप(*val), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, request, index, buf, माप(*val));
	*val = *buf;
	kमुक्त(buf);
	अगर (ret < 0)
		वापस ret;

	वापस ret != माप(*val) ? -EIO : 0;
पूर्ण

/* Returns zero on success or negative error code on failure. */
पूर्णांक gud_usb_set_u8(काष्ठा gud_device *gdrm, u8 request, u8 val)
अणु
	वापस gud_usb_set(gdrm, request, 0, &val, माप(val));
पूर्ण

अटल पूर्णांक gud_get_properties(काष्ठा gud_device *gdrm)
अणु
	काष्ठा gud_property_req *properties;
	अचिन्हित पूर्णांक i, num_properties;
	पूर्णांक ret;

	properties = kसुस्मृति(GUD_PROPERTIES_MAX_NUM, माप(*properties), GFP_KERNEL);
	अगर (!properties)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_PROPERTIES, 0,
			  properties, GUD_PROPERTIES_MAX_NUM * माप(*properties));
	अगर (ret <= 0)
		जाओ out;
	अगर (ret % माप(*properties)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	num_properties = ret / माप(*properties);
	ret = 0;

	gdrm->properties = drmm_kसुस्मृति(&gdrm->drm, num_properties, माप(*gdrm->properties),
					GFP_KERNEL);
	अगर (!gdrm->properties) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_properties; i++) अणु
		u16 prop = le16_to_cpu(properties[i].prop);
		u64 val = le64_to_cpu(properties[i].val);

		चयन (prop) अणु
		हाल GUD_PROPERTY_ROTATION:
			/*
			 * DRM UAPI matches the protocol so use the value directly,
			 * but mask out any additions on future devices.
			 */
			val &= GUD_ROTATION_MASK;
			ret = drm_plane_create_rotation_property(&gdrm->pipe.plane,
								 DRM_MODE_ROTATE_0, val);
			अवरोध;
		शेष:
			/* New ones might show up in future devices, skip those we करोn't know. */
			drm_dbg(&gdrm->drm, "Ignoring unknown property: %u\n", prop);
			जारी;
		पूर्ण

		अगर (ret)
			जाओ out;

		gdrm->properties[gdrm->num_properties++] = prop;
	पूर्ण
out:
	kमुक्त(properties);

	वापस ret;
पूर्ण

/*
 * FIXME: Dma-buf sharing requires DMA support by the importing device.
 *        This function is a workaround to make USB devices work as well.
 *        See toकरो.rst क्रम how to fix the issue in the dma-buf framework.
 */
अटल काष्ठा drm_gem_object *gud_gem_prime_import(काष्ठा drm_device *drm, काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा gud_device *gdrm = to_gud_device(drm);

	अगर (!gdrm->dmadev)
		वापस ERR_PTR(-ENODEV);

	वापस drm_gem_prime_import_dev(drm, dma_buf, gdrm->dmadev);
पूर्ण

अटल पूर्णांक gud_stats_debugfs(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा gud_device *gdrm = to_gud_device(node->minor->dev);
	अक्षर buf[10];

	string_get_size(gdrm->bulk_len, 1, STRING_UNITS_2, buf, माप(buf));
	seq_म_लिखो(m, "Max buffer size: %s\n", buf);
	seq_म_लिखो(m, "Number of errors:  %u\n", gdrm->stats_num_errors);

	seq_माला_दो(m, "Compression:      ");
	अगर (gdrm->compression & GUD_COMPRESSION_LZ4)
		seq_माला_दो(m, " lz4");
	अगर (!gdrm->compression)
		seq_माला_दो(m, " none");
	seq_माला_दो(m, "\n");

	अगर (gdrm->compression) अणु
		u64 reमुख्यder;
		u64 ratio = भाग64_u64_rem(gdrm->stats_length, gdrm->stats_actual_length,
					  &reमुख्यder);
		u64 ratio_frac = भाग64_u64(reमुख्यder * 10, gdrm->stats_actual_length);

		seq_म_लिखो(m, "Compression ratio: %llu.%llu\n", ratio, ratio_frac);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list gud_debugfs_list[] = अणु
	अणु "stats", gud_stats_debugfs, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम gud_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(gud_debugfs_list, ARRAY_SIZE(gud_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs gud_pipe_funcs = अणु
	.check      = gud_pipe_check,
	.update	    = gud_pipe_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs gud_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल स्थिर u64 gud_pipe_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

DEFINE_DRM_GEM_FOPS(gud_fops);

अटल स्थिर काष्ठा drm_driver gud_drm_driver = अणु
	.driver_features	= DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,
	.fops			= &gud_fops,
	DRM_GEM_SHMEM_DRIVER_OPS,
	.gem_prime_import	= gud_gem_prime_import,
	.debugfs_init		= gud_debugfs_init,

	.name			= "gud",
	.desc			= "Generic USB Display",
	.date			= "20200422",
	.major			= 1,
	.minor			= 0,
पूर्ण;

अटल व्योम gud_मुक्त_buffers_and_mutex(काष्ठा drm_device *drm, व्योम *unused)
अणु
	काष्ठा gud_device *gdrm = to_gud_device(drm);

	vमुक्त(gdrm->compress_buf);
	kमुक्त(gdrm->bulk_buf);
	mutex_destroy(&gdrm->ctrl_lock);
	mutex_destroy(&gdrm->damage_lock);
पूर्ण

अटल पूर्णांक gud_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *xrgb8888_emulation_क्रमmat = शून्य;
	bool rgb565_supported = false, xrgb8888_supported = false;
	अचिन्हित पूर्णांक num_क्रमmats_dev, num_क्रमmats = 0;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_out;
	काष्ठा gud_display_descriptor_req desc;
	काष्ठा device *dev = &पूर्णांकf->dev;
	माप_प्रकार max_buffer_size = 0;
	काष्ठा gud_device *gdrm;
	काष्ठा drm_device *drm;
	u8 *क्रमmats_dev;
	u32 *क्रमmats;
	पूर्णांक ret, i;

	ret = usb_find_bulk_out_endpoपूर्णांक(पूर्णांकf->cur_altsetting, &bulk_out);
	अगर (ret)
		वापस ret;

	ret = gud_get_display_descriptor(पूर्णांकf, &desc);
	अगर (ret) अणु
		DRM_DEV_DEBUG_DRIVER(dev, "Not a display interface: ret=%d\n", ret);
		वापस -ENODEV;
	पूर्ण

	अगर (desc.version > 1) अणु
		dev_err(dev, "Protocol version %u is not supported\n", desc.version);
		वापस -ENODEV;
	पूर्ण

	gdrm = devm_drm_dev_alloc(dev, &gud_drm_driver, काष्ठा gud_device, drm);
	अगर (IS_ERR(gdrm))
		वापस PTR_ERR(gdrm);

	drm = &gdrm->drm;
	drm->mode_config.funcs = &gud_mode_config_funcs;
	ret = drmm_mode_config_init(drm);
	अगर (ret)
		वापस ret;

	gdrm->flags = le32_to_cpu(desc.flags);
	gdrm->compression = desc.compression & GUD_COMPRESSION_LZ4;

	अगर (gdrm->flags & GUD_DISPLAY_FLAG_FULL_UPDATE && gdrm->compression)
		वापस -EINVAL;

	mutex_init(&gdrm->ctrl_lock);
	mutex_init(&gdrm->damage_lock);
	INIT_WORK(&gdrm->work, gud_flush_work);
	gud_clear_damage(gdrm);

	ret = drmm_add_action_or_reset(drm, gud_मुक्त_buffers_and_mutex, शून्य);
	अगर (ret)
		वापस ret;

	drm->mode_config.min_width = le32_to_cpu(desc.min_width);
	drm->mode_config.max_width = le32_to_cpu(desc.max_width);
	drm->mode_config.min_height = le32_to_cpu(desc.min_height);
	drm->mode_config.max_height = le32_to_cpu(desc.max_height);

	क्रमmats_dev = devm_kदो_स्मृति(dev, GUD_FORMATS_MAX_NUM, GFP_KERNEL);
	/* Add room क्रम emulated XRGB8888 */
	क्रमmats = devm_kदो_स्मृति_array(dev, GUD_FORMATS_MAX_NUM + 1, माप(*क्रमmats), GFP_KERNEL);
	अगर (!क्रमmats_dev || !क्रमmats)
		वापस -ENOMEM;

	ret = gud_usb_get(gdrm, GUD_REQ_GET_FORMATS, 0, क्रमmats_dev, GUD_FORMATS_MAX_NUM);
	अगर (ret < 0)
		वापस ret;

	num_क्रमmats_dev = ret;
	क्रम (i = 0; i < num_क्रमmats_dev; i++) अणु
		स्थिर काष्ठा drm_क्रमmat_info *info;
		माप_प्रकार fmt_buf_size;
		u32 क्रमmat;

		क्रमmat = gud_to_fourcc(क्रमmats_dev[i]);
		अगर (!क्रमmat) अणु
			drm_dbg(drm, "Unsupported format: 0x%02x\n", क्रमmats_dev[i]);
			जारी;
		पूर्ण

		अगर (क्रमmat == GUD_DRM_FORMAT_R1)
			info = &gud_drm_क्रमmat_r1;
		अन्यथा अगर (क्रमmat == GUD_DRM_FORMAT_XRGB1111)
			info = &gud_drm_क्रमmat_xrgb1111;
		अन्यथा
			info = drm_क्रमmat_info(क्रमmat);

		चयन (क्रमmat) अणु
		हाल GUD_DRM_FORMAT_R1:
			fallthrough;
		हाल GUD_DRM_FORMAT_XRGB1111:
			अगर (!xrgb8888_emulation_क्रमmat)
				xrgb8888_emulation_क्रमmat = info;
			अवरोध;
		हाल DRM_FORMAT_RGB565:
			rgb565_supported = true;
			अगर (!xrgb8888_emulation_क्रमmat)
				xrgb8888_emulation_क्रमmat = info;
			अवरोध;
		हाल DRM_FORMAT_XRGB8888:
			xrgb8888_supported = true;
			अवरोध;
		पूर्ण

		fmt_buf_size = drm_क्रमmat_info_min_pitch(info, 0, drm->mode_config.max_width) *
			       drm->mode_config.max_height;
		max_buffer_size = max(max_buffer_size, fmt_buf_size);

		अगर (क्रमmat == GUD_DRM_FORMAT_R1 || क्रमmat == GUD_DRM_FORMAT_XRGB1111)
			जारी; /* Internal not क्रम userspace */

		क्रमmats[num_क्रमmats++] = क्रमmat;
	पूर्ण

	अगर (!num_क्रमmats && !xrgb8888_emulation_क्रमmat) अणु
		dev_err(dev, "No supported pixel formats found\n");
		वापस -EINVAL;
	पूर्ण

	/* Prefer speed over color depth */
	अगर (rgb565_supported)
		drm->mode_config.preferred_depth = 16;

	अगर (!xrgb8888_supported && xrgb8888_emulation_क्रमmat) अणु
		gdrm->xrgb8888_emulation_क्रमmat = xrgb8888_emulation_क्रमmat;
		क्रमmats[num_क्रमmats++] = DRM_FORMAT_XRGB8888;
	पूर्ण

	अगर (desc.max_buffer_size)
		max_buffer_size = le32_to_cpu(desc.max_buffer_size);
retry:
	/*
	 * Use plain kदो_स्मृति here since devm_kदो_स्मृति() places काष्ठा devres at the beginning
	 * of the buffer it allocates. This wastes a lot of memory when allocating big buffers.
	 * Asking क्रम 2M would actually allocate 4M. This would also prevent getting the biggest
	 * possible buffer potentially leading to split transfers.
	 */
	gdrm->bulk_buf = kदो_स्मृति(max_buffer_size, GFP_KERNEL | __GFP_NOWARN);
	अगर (!gdrm->bulk_buf) अणु
		max_buffer_size = roundup_घात_of_two(max_buffer_size) / 2;
		अगर (max_buffer_size < SZ_512K)
			वापस -ENOMEM;
		जाओ retry;
	पूर्ण

	gdrm->bulk_pipe = usb_sndbulkpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), usb_endpoपूर्णांक_num(bulk_out));
	gdrm->bulk_len = max_buffer_size;

	अगर (gdrm->compression & GUD_COMPRESSION_LZ4) अणु
		gdrm->lz4_comp_mem = devm_kदो_स्मृति(dev, LZ4_MEM_COMPRESS, GFP_KERNEL);
		अगर (!gdrm->lz4_comp_mem)
			वापस -ENOMEM;

		gdrm->compress_buf = vदो_स्मृति(gdrm->bulk_len);
		अगर (!gdrm->compress_buf)
			वापस -ENOMEM;
	पूर्ण

	ret = drm_simple_display_pipe_init(drm, &gdrm->pipe, &gud_pipe_funcs,
					   क्रमmats, num_क्रमmats,
					   gud_pipe_modअगरiers, शून्य);
	अगर (ret)
		वापस ret;

	devm_kमुक्त(dev, क्रमmats);
	devm_kमुक्त(dev, क्रमmats_dev);

	ret = gud_get_properties(gdrm);
	अगर (ret) अणु
		dev_err(dev, "Failed to get properties (error=%d)\n", ret);
		वापस ret;
	पूर्ण

	drm_plane_enable_fb_damage_clips(&gdrm->pipe.plane);

	ret = gud_get_connectors(gdrm);
	अगर (ret) अणु
		dev_err(dev, "Failed to get connectors (error=%d)\n", ret);
		वापस ret;
	पूर्ण

	drm_mode_config_reset(drm);

	usb_set_पूर्णांकfdata(पूर्णांकf, gdrm);

	gdrm->dmadev = usb_पूर्णांकf_get_dma_device(पूर्णांकf);
	अगर (!gdrm->dmadev)
		dev_warn(dev, "buffer sharing not supported");

	ret = drm_dev_रेजिस्टर(drm, 0);
	अगर (ret) अणु
		put_device(gdrm->dmadev);
		वापस ret;
	पूर्ण

	drm_kms_helper_poll_init(drm);

	drm_fbdev_generic_setup(drm, 0);

	वापस 0;
पूर्ण

अटल व्योम gud_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा gud_device *gdrm = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा drm_device *drm = &gdrm->drm;

	drm_dbg(drm, "%s:\n", __func__);

	drm_kms_helper_poll_fini(drm);
	drm_dev_unplug(drm);
	drm_atomic_helper_shutकरोwn(drm);
	put_device(gdrm->dmadev);
	gdrm->dmadev = शून्य;
पूर्ण

अटल पूर्णांक gud_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा gud_device *gdrm = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस drm_mode_config_helper_suspend(&gdrm->drm);
पूर्ण

अटल पूर्णांक gud_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gud_device *gdrm = usb_get_पूर्णांकfdata(पूर्णांकf);

	drm_mode_config_helper_resume(&gdrm->drm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_device_id gud_id_table[] = अणु
	अणु USB_DEVICE_INTERFACE_CLASS(0x1d50, 0x614d, USB_CLASS_VENDOR_SPEC) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, gud_id_table);

अटल काष्ठा usb_driver gud_usb_driver = अणु
	.name		= "gud",
	.probe		= gud_probe,
	.disconnect	= gud_disconnect,
	.id_table	= gud_id_table,
	.suspend	= gud_suspend,
	.resume		= gud_resume,
	.reset_resume	= gud_resume,
पूर्ण;

module_usb_driver(gud_usb_driver);

MODULE_AUTHOR("Noralf Trथचnnes");
MODULE_LICENSE("Dual MIT/GPL");
