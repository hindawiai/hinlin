<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित UDLFB_H
#घोषणा UDLFB_H

/*
 * TODO: Propose standard fb.h ioctl क्रम reporting damage,
 * using _IOWR() and one of the existing area काष्ठाs from fb.h
 * Consider these ioctls deprecated, but they're still used by the
 * DisplayLink X server as yet - need both to be modअगरied in tandem
 * when new ioctl(s) are पढ़ोy.
 */
#घोषणा DLFB_IOCTL_RETURN_EDID	 0xAD
#घोषणा DLFB_IOCTL_REPORT_DAMAGE 0xAA
काष्ठा dloarea अणु
	पूर्णांक x, y;
	पूर्णांक w, h;
	पूर्णांक x2, y2;
पूर्ण;

काष्ठा urb_node अणु
	काष्ठा list_head entry;
	काष्ठा dlfb_data *dlfb;
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

काष्ठा dlfb_data अणु
	काष्ठा usb_device *udev;
	काष्ठा fb_info *info;
	काष्ठा urb_list urbs;
	अक्षर *backing_buffer;
	पूर्णांक fb_count;
	bool भवized; /* true when physical usb device not present */
	atomic_t usb_active; /* 0 = update भव buffer, but no usb traffic */
	atomic_t lost_pixels; /* 1 = a render op failed. Need screen refresh */
	अक्षर *edid; /* null until we पढ़ो edid from hw or get from sysfs */
	माप_प्रकार edid_size;
	पूर्णांक sku_pixel_limit;
	पूर्णांक base16;
	पूर्णांक base8;
	u32 pseuकरो_palette[256];
	पूर्णांक blank_mode; /*one of FB_BLANK_ */
	काष्ठा mutex render_mutex;
	पूर्णांक damage_x;
	पूर्णांक damage_y;
	पूर्णांक damage_x2;
	पूर्णांक damage_y2;
	spinlock_t damage_lock;
	काष्ठा work_काष्ठा damage_work;
	काष्ठा fb_ops ops;
	/* blit-only rendering path metrics, exposed through sysfs */
	atomic_t bytes_rendered; /* raw pixel-bytes driver asked to render */
	atomic_t bytes_identical; /* saved efक्रमt with backbuffer comparison */
	atomic_t bytes_sent; /* to usb, after compression including overhead */
	atomic_t cpu_kcycles_used; /* transpired during pixel processing */
	काष्ठा fb_var_screeninfo current_mode;
	काष्ठा list_head deferred_मुक्त;
पूर्ण;

#घोषणा NR_USB_REQUEST_I2C_SUB_IO 0x02
#घोषणा NR_USB_REQUEST_CHANNEL 0x12

/* -BULK_SIZE as per usb-skeleton. Can we get full page and aव्योम overhead? */
#घोषणा BULK_SIZE 512
#घोषणा MAX_TRANSFER (PAGE_SIZE*16 - BULK_SIZE)
#घोषणा WRITES_IN_FLIGHT (4)

#घोषणा MAX_VENDOR_DESCRIPTOR_SIZE 256

#घोषणा GET_URB_TIMEOUT	HZ
#घोषणा FREE_URB_TIMEOUT (HZ*2)

#घोषणा BPP                     2
#घोषणा MAX_CMD_PIXELS		255

#घोषणा RLX_HEADER_BYTES	7
#घोषणा MIN_RLX_PIX_BYTES       4
#घोषणा MIN_RLX_CMD_BYTES	(RLX_HEADER_BYTES + MIN_RLX_PIX_BYTES)

#घोषणा RLE_HEADER_BYTES	6
#घोषणा MIN_RLE_PIX_BYTES	3
#घोषणा MIN_RLE_CMD_BYTES	(RLE_HEADER_BYTES + MIN_RLE_PIX_BYTES)

#घोषणा RAW_HEADER_BYTES	6
#घोषणा MIN_RAW_PIX_BYTES	2
#घोषणा MIN_RAW_CMD_BYTES	(RAW_HEADER_BYTES + MIN_RAW_PIX_BYTES)

#घोषणा DL_DEFIO_WRITE_DELAY    msecs_to_jअगरfies(HZ <= 300 ? 4 : 10) /* optimal value क्रम 720p video */
#घोषणा DL_DEFIO_WRITE_DISABLE  (HZ*60) /* "disable" with दीर्घ delay */

/* हटाओ these once align.h patch is taken पूर्णांकo kernel */
#घोषणा DL_ALIGN_UP(x, a) ALIGN(x, a)
#घोषणा DL_ALIGN_DOWN(x, a) ALIGN_DOWN(x, a)

#पूर्ण_अगर
