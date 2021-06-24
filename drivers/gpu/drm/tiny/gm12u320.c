<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2019 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

अटल bool eco_mode;
module_param(eco_mode, bool, 0644);
MODULE_PARM_DESC(eco_mode, "Turn on Eco mode (less bright, more silent)");

#घोषणा DRIVER_NAME		"gm12u320"
#घोषणा DRIVER_DESC		"Grain Media GM12U320 USB projector display"
#घोषणा DRIVER_DATE		"2019"
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		0

/*
 * The DLP has an actual width of 854 pixels, but that is not a multiple
 * of 8, अवरोधing things left and right, so we export a width of 848.
 */
#घोषणा GM12U320_USER_WIDTH		848
#घोषणा GM12U320_REAL_WIDTH		854
#घोषणा GM12U320_HEIGHT			480

#घोषणा GM12U320_BLOCK_COUNT		20

#घोषणा GM12U320_ERR(fmt, ...) \
	DRM_DEV_ERROR(gm12u320->dev.dev, fmt, ##__VA_ARGS__)

#घोषणा MISC_RCV_EPT			1
#घोषणा DATA_RCV_EPT			2
#घोषणा DATA_SND_EPT			3
#घोषणा MISC_SND_EPT			4

#घोषणा DATA_BLOCK_HEADER_SIZE		84
#घोषणा DATA_BLOCK_CONTENT_SIZE		64512
#घोषणा DATA_BLOCK_FOOTER_SIZE		20
#घोषणा DATA_BLOCK_SIZE			(DATA_BLOCK_HEADER_SIZE + \
					 DATA_BLOCK_CONTENT_SIZE + \
					 DATA_BLOCK_FOOTER_SIZE)
#घोषणा DATA_LAST_BLOCK_CONTENT_SIZE	4032
#घोषणा DATA_LAST_BLOCK_SIZE		(DATA_BLOCK_HEADER_SIZE + \
					 DATA_LAST_BLOCK_CONTENT_SIZE + \
					 DATA_BLOCK_FOOTER_SIZE)

#घोषणा CMD_SIZE			31
#घोषणा READ_STATUS_SIZE		13
#घोषणा MISC_VALUE_SIZE			4

#घोषणा CMD_TIMEOUT			msecs_to_jअगरfies(200)
#घोषणा DATA_TIMEOUT			msecs_to_jअगरfies(1000)
#घोषणा IDLE_TIMEOUT			msecs_to_jअगरfies(2000)
#घोषणा FIRST_FRAME_TIMEOUT		msecs_to_jअगरfies(2000)

#घोषणा MISC_REQ_GET_SET_ECO_A		0xff
#घोषणा MISC_REQ_GET_SET_ECO_B		0x35
/* Winकरोws driver करोes once every second, with arg d = 1, other args 0 */
#घोषणा MISC_REQ_UNKNOWN1_A		0xff
#घोषणा MISC_REQ_UNKNOWN1_B		0x38
/* Winकरोws driver करोes this on init, with arg a, b = 0, c = 0xa0, d = 4 */
#घोषणा MISC_REQ_UNKNOWN2_A		0xa5
#घोषणा MISC_REQ_UNKNOWN2_B		0x00

काष्ठा gm12u320_device अणु
	काष्ठा drm_device	         dev;
	काष्ठा device                   *dmadev;
	काष्ठा drm_simple_display_pipe   pipe;
	काष्ठा drm_connector	         conn;
	अचिन्हित अक्षर                   *cmd_buf;
	अचिन्हित अक्षर                   *data_buf[GM12U320_BLOCK_COUNT];
	काष्ठा अणु
		काष्ठा delayed_work       work;
		काष्ठा mutex             lock;
		काष्ठा drm_framebuffer  *fb;
		काष्ठा drm_rect          rect;
		पूर्णांक frame;
		पूर्णांक draw_status_समयout;
		काष्ठा dma_buf_map src_map;
	पूर्ण fb_update;
पूर्ण;

#घोषणा to_gm12u320(__dev) container_of(__dev, काष्ठा gm12u320_device, dev)

अटल स्थिर अक्षर cmd_data[CMD_SIZE] = अणु
	0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00,
	0x68, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x10, 0xff,
	0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अक्षर cmd_draw[CMD_SIZE] = अणु
	0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xfe,
	0x00, 0x00, 0x00, 0xc0, 0xd1, 0x05, 0x00, 0x40,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अक्षर cmd_misc[CMD_SIZE] = अणु
	0x55, 0x53, 0x42, 0x43, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00, 0x00, 0x00, 0x80, 0x01, 0x10, 0xfd,
	0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अक्षर data_block_header[DATA_BLOCK_HEADER_SIZE] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xfb, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x04, 0x15, 0x00, 0x00, 0xfc, 0x00, 0x00,
	0x01, 0x00, 0x00, 0xdb
पूर्ण;

अटल स्थिर अक्षर data_last_block_header[DATA_BLOCK_HEADER_SIZE] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xfb, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x2a, 0x00, 0x20, 0x00, 0xc0, 0x0f, 0x00, 0x00,
	0x01, 0x00, 0x00, 0xd7
पूर्ण;

अटल स्थिर अक्षर data_block_footer[DATA_BLOCK_FOOTER_SIZE] = अणु
	0xfb, 0x14, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x4f
पूर्ण;

अटल अंतरभूत काष्ठा usb_device *gm12u320_to_usb_device(काष्ठा gm12u320_device *gm12u320)
अणु
	वापस पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(gm12u320->dev.dev));
पूर्ण

अटल पूर्णांक gm12u320_usb_alloc(काष्ठा gm12u320_device *gm12u320)
अणु
	पूर्णांक i, block_size;
	स्थिर अक्षर *hdr;

	gm12u320->cmd_buf = drmm_kदो_स्मृति(&gm12u320->dev, CMD_SIZE, GFP_KERNEL);
	अगर (!gm12u320->cmd_buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < GM12U320_BLOCK_COUNT; i++) अणु
		अगर (i == GM12U320_BLOCK_COUNT - 1) अणु
			block_size = DATA_LAST_BLOCK_SIZE;
			hdr = data_last_block_header;
		पूर्ण अन्यथा अणु
			block_size = DATA_BLOCK_SIZE;
			hdr = data_block_header;
		पूर्ण

		gm12u320->data_buf[i] = drmm_kzalloc(&gm12u320->dev,
						     block_size, GFP_KERNEL);
		अगर (!gm12u320->data_buf[i])
			वापस -ENOMEM;

		स_नकल(gm12u320->data_buf[i], hdr, DATA_BLOCK_HEADER_SIZE);
		स_नकल(gm12u320->data_buf[i] +
				(block_size - DATA_BLOCK_FOOTER_SIZE),
		       data_block_footer, DATA_BLOCK_FOOTER_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gm12u320_misc_request(काष्ठा gm12u320_device *gm12u320,
				 u8 req_a, u8 req_b,
				 u8 arg_a, u8 arg_b, u8 arg_c, u8 arg_d)
अणु
	काष्ठा usb_device *udev = gm12u320_to_usb_device(gm12u320);
	पूर्णांक ret, len;

	स_नकल(gm12u320->cmd_buf, &cmd_misc, CMD_SIZE);
	gm12u320->cmd_buf[20] = req_a;
	gm12u320->cmd_buf[21] = req_b;
	gm12u320->cmd_buf[22] = arg_a;
	gm12u320->cmd_buf[23] = arg_b;
	gm12u320->cmd_buf[24] = arg_c;
	gm12u320->cmd_buf[25] = arg_d;

	/* Send request */
	ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, MISC_SND_EPT),
			   gm12u320->cmd_buf, CMD_SIZE, &len, CMD_TIMEOUT);
	अगर (ret || len != CMD_SIZE) अणु
		GM12U320_ERR("Misc. req. error %d\n", ret);
		वापस -EIO;
	पूर्ण

	/* Read value */
	ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, MISC_RCV_EPT),
			   gm12u320->cmd_buf, MISC_VALUE_SIZE, &len,
			   DATA_TIMEOUT);
	अगर (ret || len != MISC_VALUE_SIZE) अणु
		GM12U320_ERR("Misc. value error %d\n", ret);
		वापस -EIO;
	पूर्ण
	/* cmd_buf[0] now contains the पढ़ो value, which we करोn't use */

	/* Read status */
	ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, MISC_RCV_EPT),
			   gm12u320->cmd_buf, READ_STATUS_SIZE, &len,
			   CMD_TIMEOUT);
	अगर (ret || len != READ_STATUS_SIZE) अणु
		GM12U320_ERR("Misc. status error %d\n", ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gm12u320_32bpp_to_24bpp_packed(u8 *dst, u8 *src, पूर्णांक len)
अणु
	जबतक (len--) अणु
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
		src++;
	पूर्ण
पूर्ण

अटल व्योम gm12u320_copy_fb_to_blocks(काष्ठा gm12u320_device *gm12u320)
अणु
	पूर्णांक block, dst_offset, len, reमुख्य, ret, x1, x2, y1, y2;
	काष्ठा drm_framebuffer *fb;
	व्योम *vaddr;
	u8 *src;

	mutex_lock(&gm12u320->fb_update.lock);

	अगर (!gm12u320->fb_update.fb)
		जाओ unlock;

	fb = gm12u320->fb_update.fb;
	x1 = gm12u320->fb_update.rect.x1;
	x2 = gm12u320->fb_update.rect.x2;
	y1 = gm12u320->fb_update.rect.y1;
	y2 = gm12u320->fb_update.rect.y2;
	vaddr = gm12u320->fb_update.src_map.vaddr; /* TODO: Use mapping असलtraction properly */

	अगर (fb->obj[0]->import_attach) अणु
		ret = dma_buf_begin_cpu_access(
			fb->obj[0]->import_attach->dmabuf, DMA_FROM_DEVICE);
		अगर (ret) अणु
			GM12U320_ERR("dma_buf_begin_cpu_access err: %d\n", ret);
			जाओ put_fb;
		पूर्ण
	पूर्ण

	src = vaddr + y1 * fb->pitches[0] + x1 * 4;

	x1 += (GM12U320_REAL_WIDTH - GM12U320_USER_WIDTH) / 2;
	x2 += (GM12U320_REAL_WIDTH - GM12U320_USER_WIDTH) / 2;

	क्रम (; y1 < y2; y1++) अणु
		reमुख्य = 0;
		len = (x2 - x1) * 3;
		dst_offset = (y1 * GM12U320_REAL_WIDTH + x1) * 3;
		block = dst_offset / DATA_BLOCK_CONTENT_SIZE;
		dst_offset %= DATA_BLOCK_CONTENT_SIZE;

		अगर ((dst_offset + len) > DATA_BLOCK_CONTENT_SIZE) अणु
			reमुख्य = dst_offset + len - DATA_BLOCK_CONTENT_SIZE;
			len = DATA_BLOCK_CONTENT_SIZE - dst_offset;
		पूर्ण

		dst_offset += DATA_BLOCK_HEADER_SIZE;
		len /= 3;

		gm12u320_32bpp_to_24bpp_packed(
			gm12u320->data_buf[block] + dst_offset,
			src, len);

		अगर (reमुख्य) अणु
			block++;
			dst_offset = DATA_BLOCK_HEADER_SIZE;
			gm12u320_32bpp_to_24bpp_packed(
				gm12u320->data_buf[block] + dst_offset,
				src + len * 4, reमुख्य / 3);
		पूर्ण
		src += fb->pitches[0];
	पूर्ण

	अगर (fb->obj[0]->import_attach) अणु
		ret = dma_buf_end_cpu_access(fb->obj[0]->import_attach->dmabuf,
					     DMA_FROM_DEVICE);
		अगर (ret)
			GM12U320_ERR("dma_buf_end_cpu_access err: %d\n", ret);
	पूर्ण
put_fb:
	drm_framebuffer_put(fb);
	gm12u320->fb_update.fb = शून्य;
unlock:
	mutex_unlock(&gm12u320->fb_update.lock);
पूर्ण

अटल व्योम gm12u320_fb_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gm12u320_device *gm12u320 =
		container_of(to_delayed_work(work), काष्ठा gm12u320_device,
			     fb_update.work);
	काष्ठा usb_device *udev = gm12u320_to_usb_device(gm12u320);
	पूर्णांक block, block_size, len;
	पूर्णांक ret = 0;

	gm12u320_copy_fb_to_blocks(gm12u320);

	क्रम (block = 0; block < GM12U320_BLOCK_COUNT; block++) अणु
		अगर (block == GM12U320_BLOCK_COUNT - 1)
			block_size = DATA_LAST_BLOCK_SIZE;
		अन्यथा
			block_size = DATA_BLOCK_SIZE;

		/* Send data command to device */
		स_नकल(gm12u320->cmd_buf, cmd_data, CMD_SIZE);
		gm12u320->cmd_buf[8] = block_size & 0xff;
		gm12u320->cmd_buf[9] = block_size >> 8;
		gm12u320->cmd_buf[20] = 0xfc - block * 4;
		gm12u320->cmd_buf[21] =
			block | (gm12u320->fb_update.frame << 7);

		ret = usb_bulk_msg(udev,
				   usb_sndbulkpipe(udev, DATA_SND_EPT),
				   gm12u320->cmd_buf, CMD_SIZE, &len,
				   CMD_TIMEOUT);
		अगर (ret || len != CMD_SIZE)
			जाओ err;

		/* Send data block to device */
		ret = usb_bulk_msg(udev,
				   usb_sndbulkpipe(udev, DATA_SND_EPT),
				   gm12u320->data_buf[block], block_size,
				   &len, DATA_TIMEOUT);
		अगर (ret || len != block_size)
			जाओ err;

		/* Read status */
		ret = usb_bulk_msg(udev,
				   usb_rcvbulkpipe(udev, DATA_RCV_EPT),
				   gm12u320->cmd_buf, READ_STATUS_SIZE, &len,
				   CMD_TIMEOUT);
		अगर (ret || len != READ_STATUS_SIZE)
			जाओ err;
	पूर्ण

	/* Send draw command to device */
	स_नकल(gm12u320->cmd_buf, cmd_draw, CMD_SIZE);
	ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, DATA_SND_EPT),
			   gm12u320->cmd_buf, CMD_SIZE, &len, CMD_TIMEOUT);
	अगर (ret || len != CMD_SIZE)
		जाओ err;

	/* Read status */
	ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, DATA_RCV_EPT),
			   gm12u320->cmd_buf, READ_STATUS_SIZE, &len,
			   gm12u320->fb_update.draw_status_समयout);
	अगर (ret || len != READ_STATUS_SIZE)
		जाओ err;

	gm12u320->fb_update.draw_status_समयout = CMD_TIMEOUT;
	gm12u320->fb_update.frame = !gm12u320->fb_update.frame;

	/*
	 * We must draw a frame every 2s otherwise the projector
	 * चयनes back to showing its logo.
	 */
	queue_delayed_work(प्रणाली_दीर्घ_wq, &gm12u320->fb_update.work,
			   IDLE_TIMEOUT);

	वापस;
err:
	/* Do not log errors caused by module unload or device unplug */
	अगर (ret != -ENODEV && ret != -ECONNRESET && ret != -ESHUTDOWN)
		GM12U320_ERR("Frame update error: %d\n", ret);
पूर्ण

अटल व्योम gm12u320_fb_mark_dirty(काष्ठा drm_framebuffer *fb, स्थिर काष्ठा dma_buf_map *map,
				   काष्ठा drm_rect *dirty)
अणु
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(fb->dev);
	काष्ठा drm_framebuffer *old_fb = शून्य;
	bool wakeup = false;

	mutex_lock(&gm12u320->fb_update.lock);

	अगर (gm12u320->fb_update.fb != fb) अणु
		old_fb = gm12u320->fb_update.fb;
		drm_framebuffer_get(fb);
		gm12u320->fb_update.fb = fb;
		gm12u320->fb_update.rect = *dirty;
		gm12u320->fb_update.src_map = *map;
		wakeup = true;
	पूर्ण अन्यथा अणु
		काष्ठा drm_rect *rect = &gm12u320->fb_update.rect;

		rect->x1 = min(rect->x1, dirty->x1);
		rect->y1 = min(rect->y1, dirty->y1);
		rect->x2 = max(rect->x2, dirty->x2);
		rect->y2 = max(rect->y2, dirty->y2);
	पूर्ण

	mutex_unlock(&gm12u320->fb_update.lock);

	अगर (wakeup)
		mod_delayed_work(प्रणाली_दीर्घ_wq, &gm12u320->fb_update.work, 0);

	अगर (old_fb)
		drm_framebuffer_put(old_fb);
पूर्ण

अटल व्योम gm12u320_stop_fb_update(काष्ठा gm12u320_device *gm12u320)
अणु
	काष्ठा drm_framebuffer *old_fb;

	cancel_delayed_work_sync(&gm12u320->fb_update.work);

	mutex_lock(&gm12u320->fb_update.lock);
	old_fb = gm12u320->fb_update.fb;
	gm12u320->fb_update.fb = शून्य;
	dma_buf_map_clear(&gm12u320->fb_update.src_map);
	mutex_unlock(&gm12u320->fb_update.lock);

	drm_framebuffer_put(old_fb);
पूर्ण

अटल पूर्णांक gm12u320_set_ecomode(काष्ठा gm12u320_device *gm12u320)
अणु
	वापस gm12u320_misc_request(gm12u320, MISC_REQ_GET_SET_ECO_A,
				     MISC_REQ_GET_SET_ECO_B, 0x01 /* set */,
				     eco_mode ? 0x01 : 0x00, 0x00, 0x01);
पूर्ण

/* ------------------------------------------------------------------ */
/* gm12u320 connector						      */

/*
 *त We use fake EDID info so that userspace know that it is dealing with
 * an Acer projector, rather then listing this as an "unknown" monitor.
 * Note this assumes this driver is only ever used with the Acer C120, अगर we
 * add support क्रम other devices the venकरोr and model should be parameterized.
 */
अटल काष्ठा edid gm12u320_edid = अणु
	.header		= अणु 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 पूर्ण,
	.mfg_id		= अणु 0x04, 0x72 पूर्ण,	/* "ACR" */
	.prod_code	= अणु 0x20, 0xc1 पूर्ण,	/* C120h */
	.serial		= 0xaa55aa55,
	.mfg_week	= 1,
	.mfg_year	= 16,
	.version	= 1,			/* EDID 1.3 */
	.revision	= 3,			/* EDID 1.3 */
	.input		= 0x08,			/* Analog input */
	.features	= 0x0a,			/* Pref timing in DTD 1 */
	.standard_timings = अणु अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण,
			      अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण, अणु 1, 1 पूर्ण पूर्ण,
	.detailed_timings = अणु अणु
		.pixel_घड़ी = 3383,
		/* hactive = 848, hblank = 256 */
		.data.pixel_data.hactive_lo = 0x50,
		.data.pixel_data.hblank_lo = 0x00,
		.data.pixel_data.hactive_hblank_hi = 0x31,
		/* vactive = 480, vblank = 28 */
		.data.pixel_data.vactive_lo = 0xe0,
		.data.pixel_data.vblank_lo = 0x1c,
		.data.pixel_data.vactive_vblank_hi = 0x10,
		/* hsync offset 40 pw 128, vsync offset 1 pw 4 */
		.data.pixel_data.hsync_offset_lo = 0x28,
		.data.pixel_data.hsync_pulse_width_lo = 0x80,
		.data.pixel_data.vsync_offset_pulse_width_lo = 0x14,
		.data.pixel_data.hsync_vsync_offset_pulse_width_hi = 0x00,
		/* Digital separate syncs, hsync+, vsync+ */
		.data.pixel_data.misc = 0x1e,
	पूर्ण, अणु
		.pixel_घड़ी = 0,
		.data.other_data.type = 0xfd, /* Monitor ranges */
		.data.other_data.data.range.min_vfreq = 59,
		.data.other_data.data.range.max_vfreq = 61,
		.data.other_data.data.range.min_hfreq_khz = 29,
		.data.other_data.data.range.max_hfreq_khz = 32,
		.data.other_data.data.range.pixel_घड़ी_mhz = 4, /* 40 MHz */
		.data.other_data.data.range.flags = 0,
		.data.other_data.data.range.क्रमmula.cvt = अणु
			0xa0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 पूर्ण,
	पूर्ण, अणु
		.pixel_घड़ी = 0,
		.data.other_data.type = 0xfc, /* Model string */
		.data.other_data.data.str.str = अणु
			'P', 'r', 'o', 'j', 'e', 'c', 't', 'o', 'r', '\n',
			' ', ' ',  ' ' पूर्ण,
	पूर्ण, अणु
		.pixel_घड़ी = 0,
		.data.other_data.type = 0xfe, /* Unspecअगरied text / padding */
		.data.other_data.data.str.str = अणु
			'\n', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ',  ' ' पूर्ण,
	पूर्ण पूर्ण,
	.checksum = 0x13,
पूर्ण;

अटल पूर्णांक gm12u320_conn_get_modes(काष्ठा drm_connector *connector)
अणु
	drm_connector_update_edid_property(connector, &gm12u320_edid);
	वापस drm_add_edid_modes(connector, &gm12u320_edid);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs gm12u320_conn_helper_funcs = अणु
	.get_modes = gm12u320_conn_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs gm12u320_conn_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक gm12u320_conn_init(काष्ठा gm12u320_device *gm12u320)
अणु
	drm_connector_helper_add(&gm12u320->conn, &gm12u320_conn_helper_funcs);
	वापस drm_connector_init(&gm12u320->dev, &gm12u320->conn,
				  &gm12u320_conn_funcs, DRM_MODE_CONNECTOR_VGA);
पूर्ण

/* ------------------------------------------------------------------ */
/* gm12u320 (simple) display pipe				      */

अटल व्योम gm12u320_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_crtc_state *crtc_state,
				 काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_rect rect = अणु 0, 0, GM12U320_USER_WIDTH, GM12U320_HEIGHT पूर्ण;
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(pipe->crtc.dev);
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);

	gm12u320->fb_update.draw_status_समयout = FIRST_FRAME_TIMEOUT;
	gm12u320_fb_mark_dirty(plane_state->fb, &shaकरोw_plane_state->map[0], &rect);
पूर्ण

अटल व्योम gm12u320_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(pipe->crtc.dev);

	gm12u320_stop_fb_update(gm12u320);
पूर्ण

अटल व्योम gm12u320_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(state);
	काष्ठा drm_rect rect;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		gm12u320_fb_mark_dirty(state->fb, &shaकरोw_plane_state->map[0], &rect);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs gm12u320_pipe_funcs = अणु
	.enable	    = gm12u320_pipe_enable,
	.disable    = gm12u320_pipe_disable,
	.update	    = gm12u320_pipe_update,
	DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS,
पूर्ण;

अटल स्थिर uपूर्णांक32_t gm12u320_pipe_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक64_t gm12u320_pipe_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

/*
 * FIXME: Dma-buf sharing requires DMA support by the importing device.
 *        This function is a workaround to make USB devices work as well.
 *        See toकरो.rst क्रम how to fix the issue in the dma-buf framework.
 */
अटल काष्ठा drm_gem_object *gm12u320_gem_prime_import(काष्ठा drm_device *dev,
							काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(dev);

	अगर (!gm12u320->dmadev)
		वापस ERR_PTR(-ENODEV);

	वापस drm_gem_prime_import_dev(dev, dma_buf, gm12u320->dmadev);
पूर्ण

DEFINE_DRM_GEM_FOPS(gm12u320_fops);

अटल स्थिर काष्ठा drm_driver gm12u320_drm_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,

	.name		 = DRIVER_NAME,
	.desc		 = DRIVER_DESC,
	.date		 = DRIVER_DATE,
	.major		 = DRIVER_MAJOR,
	.minor		 = DRIVER_MINOR,

	.fops		 = &gm12u320_fops,
	DRM_GEM_SHMEM_DRIVER_OPS,
	.gem_prime_import = gm12u320_gem_prime_import,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs gm12u320_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक gm12u320_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा gm12u320_device *gm12u320;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	/*
	 * The gm12u320 presents itself to the प्रणाली as 2 usb mass-storage
	 * पूर्णांकerfaces, we only care about / need the first one.
	 */
	अगर (पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber != 0)
		वापस -ENODEV;

	gm12u320 = devm_drm_dev_alloc(&पूर्णांकerface->dev, &gm12u320_drm_driver,
				      काष्ठा gm12u320_device, dev);
	अगर (IS_ERR(gm12u320))
		वापस PTR_ERR(gm12u320);
	dev = &gm12u320->dev;

	gm12u320->dmadev = usb_पूर्णांकf_get_dma_device(to_usb_पूर्णांकerface(dev->dev));
	अगर (!gm12u320->dmadev)
		drm_warn(dev, "buffer sharing not supported"); /* not an error */

	INIT_DELAYED_WORK(&gm12u320->fb_update.work, gm12u320_fb_update_work);
	mutex_init(&gm12u320->fb_update.lock);

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		जाओ err_put_device;

	dev->mode_config.min_width = GM12U320_USER_WIDTH;
	dev->mode_config.max_width = GM12U320_USER_WIDTH;
	dev->mode_config.min_height = GM12U320_HEIGHT;
	dev->mode_config.max_height = GM12U320_HEIGHT;
	dev->mode_config.funcs = &gm12u320_mode_config_funcs;

	ret = gm12u320_usb_alloc(gm12u320);
	अगर (ret)
		जाओ err_put_device;

	ret = gm12u320_set_ecomode(gm12u320);
	अगर (ret)
		जाओ err_put_device;

	ret = gm12u320_conn_init(gm12u320);
	अगर (ret)
		जाओ err_put_device;

	ret = drm_simple_display_pipe_init(&gm12u320->dev,
					   &gm12u320->pipe,
					   &gm12u320_pipe_funcs,
					   gm12u320_pipe_क्रमmats,
					   ARRAY_SIZE(gm12u320_pipe_क्रमmats),
					   gm12u320_pipe_modअगरiers,
					   &gm12u320->conn);
	अगर (ret)
		जाओ err_put_device;

	drm_mode_config_reset(dev);

	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);
	ret = drm_dev_रेजिस्टर(dev, 0);
	अगर (ret)
		जाओ err_put_device;

	drm_fbdev_generic_setup(dev, 0);

	वापस 0;

err_put_device:
	put_device(gm12u320->dmadev);
	वापस ret;
पूर्ण

अटल व्योम gm12u320_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(dev);

	put_device(gm12u320->dmadev);
	gm12u320->dmadev = शून्य;
	drm_dev_unplug(dev);
	drm_atomic_helper_shutकरोwn(dev);
पूर्ण

अटल __maybe_unused पूर्णांक gm12u320_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					   pm_message_t message)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	वापस drm_mode_config_helper_suspend(dev);
पूर्ण

अटल __maybe_unused पूर्णांक gm12u320_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा drm_device *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा gm12u320_device *gm12u320 = to_gm12u320(dev);

	gm12u320_set_ecomode(gm12u320);

	वापस drm_mode_config_helper_resume(dev);
पूर्ण

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x1de1, 0xc102) पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_driver gm12u320_usb_driver = अणु
	.name = "gm12u320",
	.probe = gm12u320_usb_probe,
	.disconnect = gm12u320_usb_disconnect,
	.id_table = id_table,
#अगर_घोषित CONFIG_PM
	.suspend = gm12u320_suspend,
	.resume = gm12u320_resume,
	.reset_resume = gm12u320_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(gm12u320_usb_driver);
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
