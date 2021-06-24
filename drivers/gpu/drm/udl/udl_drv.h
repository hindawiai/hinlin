<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Red Hat
 *
 * based in parts on udlfb.c:
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 */

#अगर_अघोषित UDL_DRV_H
#घोषणा UDL_DRV_H

#समावेश <linux/mm_types.h>
#समावेश <linux/usb.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_simple_kms_helper.h>

काष्ठा drm_mode_create_dumb;

#घोषणा DRIVER_NAME		"udl"
#घोषणा DRIVER_DESC		"DisplayLink"
#घोषणा DRIVER_DATE		"20120220"

#घोषणा DRIVER_MAJOR		0
#घोषणा DRIVER_MINOR		0
#घोषणा DRIVER_PATCHLEVEL	1

काष्ठा udl_device;

काष्ठा urb_node अणु
	काष्ठा list_head entry;
	काष्ठा udl_device *dev;
	काष्ठा delayed_work release_urb_work;
	काष्ठा urb *urb;
पूर्ण;

काष्ठा urb_list अणु
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा semaphore limit_sem;
	पूर्णांक available;
	पूर्णांक count;
	माप_प्रकार size;
पूर्ण;

काष्ठा udl_device अणु
	काष्ठा drm_device drm;
	काष्ठा device *dev;
	काष्ठा device *dmadev;

	काष्ठा drm_simple_display_pipe display_pipe;

	काष्ठा mutex gem_lock;

	पूर्णांक sku_pixel_limit;

	काष्ठा urb_list urbs;

	अक्षर mode_buf[1024];
	uपूर्णांक32_t mode_buf_len;
पूर्ण;

#घोषणा to_udl(x) container_of(x, काष्ठा udl_device, drm)

अटल अंतरभूत काष्ठा usb_device *udl_to_usb_device(काष्ठा udl_device *udl)
अणु
	वापस पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(udl->drm.dev));
पूर्ण

/* modeset */
पूर्णांक udl_modeset_init(काष्ठा drm_device *dev);
काष्ठा drm_connector *udl_connector_init(काष्ठा drm_device *dev);

काष्ठा urb *udl_get_urb(काष्ठा drm_device *dev);

पूर्णांक udl_submit_urb(काष्ठा drm_device *dev, काष्ठा urb *urb, माप_प्रकार len);
व्योम udl_urb_completion(काष्ठा urb *urb);

पूर्णांक udl_init(काष्ठा udl_device *udl);

पूर्णांक udl_render_hline(काष्ठा drm_device *dev, पूर्णांक log_bpp, काष्ठा urb **urb_ptr,
		     स्थिर अक्षर *front, अक्षर **urb_buf_ptr,
		     u32 byte_offset, u32 device_byte_offset, u32 byte_width);

पूर्णांक udl_drop_usb(काष्ठा drm_device *dev);

#घोषणा CMD_WRITE_RAW8   "\xAF\x60" /**< 8 bit raw ग_लिखो command. */
#घोषणा CMD_WRITE_RL8    "\xAF\x61" /**< 8 bit run length command. */
#घोषणा CMD_WRITE_COPY8  "\xAF\x62" /**< 8 bit copy command. */
#घोषणा CMD_WRITE_RLX8   "\xAF\x63" /**< 8 bit extended run length command. */

#घोषणा CMD_WRITE_RAW16  "\xAF\x68" /**< 16 bit raw ग_लिखो command. */
#घोषणा CMD_WRITE_RL16   "\xAF\x69" /**< 16 bit run length command. */
#घोषणा CMD_WRITE_COPY16 "\xAF\x6A" /**< 16 bit copy command. */
#घोषणा CMD_WRITE_RLX16  "\xAF\x6B" /**< 16 bit extended run length command. */

/* On/Off क्रम driving the DisplayLink framebuffer to the display */
#घोषणा UDL_REG_BLANK_MODE		0x1f

#घोषणा UDL_BLANK_MODE_ON		0x00 /* hsync and vsync on, visible */
#घोषणा UDL_BLANK_MODE_BLANKED		0x01 /* hsync and vsync on, blanked */
#घोषणा UDL_BLANK_MODE_VSYNC_OFF	0x03 /* vsync off, blanked */
#घोषणा UDL_BLANK_MODE_HSYNC_OFF	0x05 /* hsync off, blanked */
#घोषणा UDL_BLANK_MODE_POWERDOWN	0x07 /* घातered off; requires modeset */

#पूर्ण_अगर
