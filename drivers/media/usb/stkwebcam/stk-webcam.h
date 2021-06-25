<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stk-webcam.h : Driver क्रम Syntek 1125 USB webcam controller
 *
 * Copyright (C) 2006 Nicolas VIVIEN
 * Copyright 2007-2008 Jaime Velasco Juan <jsagarribay@gmail.com>
 */

#अगर_अघोषित STKWEBCAM_H
#घोषणा STKWEBCAM_H

#समावेश <linux/usb.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-common.h>

#घोषणा DRIVER_VERSION		"v0.0.1"
#घोषणा DRIVER_VERSION_NUM	0x000001

#घोषणा MAX_ISO_BUFS		3
#घोषणा ISO_FRAMES_PER_DESC	16
#घोषणा ISO_MAX_FRAME_SIZE	3 * 1024
#घोषणा ISO_BUFFER_SIZE		(ISO_FRAMES_PER_DESC * ISO_MAX_FRAME_SIZE)

काष्ठा stk_iso_buf अणु
	व्योम *data;
	पूर्णांक length;
	पूर्णांक पढ़ो;
	काष्ठा urb *urb;
पूर्ण;

/* Streaming IO buffers */
काष्ठा stk_sio_buffer अणु
	काष्ठा v4l2_buffer v4lbuf;
	अक्षर *buffer;
	पूर्णांक mapcount;
	काष्ठा stk_camera *dev;
	काष्ठा list_head list;
पूर्ण;

क्रमागत stk_mode अणुMODE_VGA, MODE_SXGA, MODE_CIF, MODE_QVGA, MODE_QCIFपूर्ण;

काष्ठा stk_video अणु
	क्रमागत stk_mode mode;
	__u32 palette;
	पूर्णांक hflip;
	पूर्णांक vflip;
पूर्ण;

क्रमागत stk_status अणु
	S_PRESENT = 1,
	S_INITIALISED = 2,
	S_MEMALLOCD = 4,
	S_STREAMING = 8,
पूर्ण;
#घोषणा is_present(dev)		((dev)->status & S_PRESENT)
#घोषणा is_initialised(dev)	((dev)->status & S_INITIALISED)
#घोषणा is_streaming(dev)	((dev)->status & S_STREAMING)
#घोषणा is_meदो_स्मृतिd(dev)	((dev)->status & S_MEMALLOCD)
#घोषणा set_present(dev)	((dev)->status = S_PRESENT)
#घोषणा unset_present(dev)	((dev)->status &= \
					~(S_PRESENT|S_INITIALISED|S_STREAMING))
#घोषणा set_initialised(dev)	((dev)->status |= S_INITIALISED)
#घोषणा unset_initialised(dev)	((dev)->status &= ~S_INITIALISED)
#घोषणा set_meदो_स्मृतिd(dev)	((dev)->status |= S_MEMALLOCD)
#घोषणा unset_meदो_स्मृतिd(dev)	((dev)->status &= ~S_MEMALLOCD)
#घोषणा set_streaming(dev)	((dev)->status |= S_STREAMING)
#घोषणा unset_streaming(dev)	((dev)->status &= ~S_STREAMING)

काष्ठा regval अणु
	अचिन्हित reg;
	अचिन्हित val;
पूर्ण;

काष्ठा stk_camera अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा video_device vdev;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक webcam_model;
	काष्ठा file *owner;
	काष्ठा mutex lock;
	पूर्णांक first_init;

	u8 isoc_ep;

	/* Not sure अगर this is right */
	atomic_t urbs_used;

	काष्ठा stk_video vsettings;

	क्रमागत stk_status status;

	spinlock_t spinlock;
	रुको_queue_head_t रुको_frame;

	काष्ठा stk_iso_buf *isobufs;

	पूर्णांक frame_size;
	/* Streaming buffers */
	पूर्णांक पढ़ोing;
	अचिन्हित पूर्णांक n_sbufs;
	काष्ठा stk_sio_buffer *sio_bufs;
	काष्ठा list_head sio_avail;
	काष्ठा list_head sio_full;
	अचिन्हित sequence;
पूर्ण;

#घोषणा vdev_to_camera(d) container_of(d, काष्ठा stk_camera, vdev)

पूर्णांक stk_camera_ग_लिखो_reg(काष्ठा stk_camera *, u16, u8);
पूर्णांक stk_camera_पढ़ो_reg(काष्ठा stk_camera *, u16, u8 *);

पूर्णांक stk_sensor_init(काष्ठा stk_camera *);
पूर्णांक stk_sensor_configure(काष्ठा stk_camera *);
पूर्णांक stk_sensor_sleep(काष्ठा stk_camera *dev);
पूर्णांक stk_sensor_wakeup(काष्ठा stk_camera *dev);
पूर्णांक stk_sensor_set_brightness(काष्ठा stk_camera *dev, पूर्णांक br);

#पूर्ण_अगर
