<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, Microsoft Corporation.
 *
 * Author:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 */

/*
 * Hyper-V Synthetic Video Frame Buffer Driver
 *
 * This is the driver क्रम the Hyper-V Synthetic Video, which supports
 * screen resolution up to Full HD 1920x1080 with 32 bit color on Winकरोws
 * Server 2012, and 1600x1200 with 16 bit color on Winकरोws Server 2008 R2
 * or earlier.
 *
 * It also solves the द्विगुन mouse cursor issue of the emulated video mode.
 *
 * The शेष screen resolution is 1152x864, which may be changed by a
 * kernel parameter:
 *     video=hyperv_fb:<width>x<height>
 *     For example: video=hyperv_fb:1280x1024
 *
 * Portrait orientation is also supported:
 *     For example: video=hyperv_fb:864x1152
 *
 * When a Winकरोws 10 RS5+ host is used, the भव machine screen
 * resolution is obtained from the host. The "video=hyperv_fb" option is
 * not needed, but still can be used to overग_लिखो what the host specअगरies.
 * The VM resolution on the host could be set by executing the घातershell
 * "set-vmvideo" command. For example
 *     set-vmvideo -vmname name -horizontalresolution:1920 \
 * -verticalresolution:1200 -resolutiontype single
 *
 * Gen 1 VMs also support direct using VM's physical memory क्रम framebuffer.
 * It could improve the efficiency and perक्रमmance क्रम framebuffer and VM.
 * This requires to allocate contiguous physical memory from Linux kernel's
 * CMA memory allocator. To enable this, supply a kernel parameter to give
 * enough memory space to CMA allocator क्रम framebuffer. For example:
 *    cma=130m
 * This gives 130MB memory to CMA allocator that can be allocated to
 * framebuffer. For reference, 8K resolution (7680x4320) takes about
 * 127MB memory.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/efi.h>
#समावेश <linux/console.h>

#समावेश <linux/hyperv.h>


/* Hyper-V Synthetic Video Protocol definitions and काष्ठाures */
#घोषणा MAX_VMBUS_PKT_SIZE 0x4000

#घोषणा SYNTHVID_VERSION(major, minor) ((minor) << 16 | (major))
#घोषणा SYNTHVID_VERSION_WIN7 SYNTHVID_VERSION(3, 0)
#घोषणा SYNTHVID_VERSION_WIN8 SYNTHVID_VERSION(3, 2)
#घोषणा SYNTHVID_VERSION_WIN10 SYNTHVID_VERSION(3, 5)

#घोषणा SYNTHVID_VER_GET_MAJOR(ver) (ver & 0x0000ffff)
#घोषणा SYNTHVID_VER_GET_MINOR(ver) ((ver & 0xffff0000) >> 16)

#घोषणा SYNTHVID_DEPTH_WIN7 16
#घोषणा SYNTHVID_DEPTH_WIN8 32

#घोषणा SYNTHVID_FB_SIZE_WIN7 (4 * 1024 * 1024)
#घोषणा SYNTHVID_WIDTH_MAX_WIN7 1600
#घोषणा SYNTHVID_HEIGHT_MAX_WIN7 1200

#घोषणा SYNTHVID_FB_SIZE_WIN8 (8 * 1024 * 1024)

#घोषणा PCI_VENDOR_ID_MICROSOFT 0x1414
#घोषणा PCI_DEVICE_ID_HYPERV_VIDEO 0x5353


क्रमागत pipe_msg_type अणु
	PIPE_MSG_INVALID,
	PIPE_MSG_DATA,
	PIPE_MSG_MAX
पूर्ण;

काष्ठा pipe_msg_hdr अणु
	u32 type;
	u32 size; /* size of message after this field */
पूर्ण __packed;


क्रमागत synthvid_msg_type अणु
	SYNTHVID_ERROR			= 0,
	SYNTHVID_VERSION_REQUEST	= 1,
	SYNTHVID_VERSION_RESPONSE	= 2,
	SYNTHVID_VRAM_LOCATION		= 3,
	SYNTHVID_VRAM_LOCATION_ACK	= 4,
	SYNTHVID_SITUATION_UPDATE	= 5,
	SYNTHVID_SITUATION_UPDATE_ACK	= 6,
	SYNTHVID_POINTER_POSITION	= 7,
	SYNTHVID_POINTER_SHAPE		= 8,
	SYNTHVID_FEATURE_CHANGE		= 9,
	SYNTHVID_सूचीT			= 10,
	SYNTHVID_RESOLUTION_REQUEST	= 13,
	SYNTHVID_RESOLUTION_RESPONSE	= 14,

	SYNTHVID_MAX			= 15
पूर्ण;

#घोषणा		SYNTHVID_EDID_BLOCK_SIZE	128
#घोषणा		SYNTHVID_MAX_RESOLUTION_COUNT	64

काष्ठा hvd_screen_info अणु
	u16 width;
	u16 height;
पूर्ण __packed;

काष्ठा synthvid_msg_hdr अणु
	u32 type;
	u32 size;  /* size of this header + payload after this field*/
पूर्ण __packed;

काष्ठा synthvid_version_req अणु
	u32 version;
पूर्ण __packed;

काष्ठा synthvid_version_resp अणु
	u32 version;
	u8 is_accepted;
	u8 max_video_outमाला_दो;
पूर्ण __packed;

काष्ठा synthvid_supported_resolution_req अणु
	u8 maximum_resolution_count;
पूर्ण __packed;

काष्ठा synthvid_supported_resolution_resp अणु
	u8 edid_block[SYNTHVID_EDID_BLOCK_SIZE];
	u8 resolution_count;
	u8 शेष_resolution_index;
	u8 is_standard;
	काष्ठा hvd_screen_info
		supported_resolution[SYNTHVID_MAX_RESOLUTION_COUNT];
पूर्ण __packed;

काष्ठा synthvid_vram_location अणु
	u64 user_ctx;
	u8 is_vram_gpa_specअगरied;
	u64 vram_gpa;
पूर्ण __packed;

काष्ठा synthvid_vram_location_ack अणु
	u64 user_ctx;
पूर्ण __packed;

काष्ठा video_output_situation अणु
	u8 active;
	u32 vram_offset;
	u8 depth_bits;
	u32 width_pixels;
	u32 height_pixels;
	u32 pitch_bytes;
पूर्ण __packed;

काष्ठा synthvid_situation_update अणु
	u64 user_ctx;
	u8 video_output_count;
	काष्ठा video_output_situation video_output[1];
पूर्ण __packed;

काष्ठा synthvid_situation_update_ack अणु
	u64 user_ctx;
पूर्ण __packed;

काष्ठा synthvid_poपूर्णांकer_position अणु
	u8 is_visible;
	u8 video_output;
	s32 image_x;
	s32 image_y;
पूर्ण __packed;


#घोषणा CURSOR_MAX_X 96
#घोषणा CURSOR_MAX_Y 96
#घोषणा CURSOR_ARGB_PIXEL_SIZE 4
#घोषणा CURSOR_MAX_SIZE (CURSOR_MAX_X * CURSOR_MAX_Y * CURSOR_ARGB_PIXEL_SIZE)
#घोषणा CURSOR_COMPLETE (-1)

काष्ठा synthvid_poपूर्णांकer_shape अणु
	u8 part_idx;
	u8 is_argb;
	u32 width; /* CURSOR_MAX_X at most */
	u32 height; /* CURSOR_MAX_Y at most */
	u32 hot_x; /* hotspot relative to upper-left of poपूर्णांकer image */
	u32 hot_y;
	u8 data[4];
पूर्ण __packed;

काष्ठा synthvid_feature_change अणु
	u8 is_dirt_needed;
	u8 is_ptr_pos_needed;
	u8 is_ptr_shape_needed;
	u8 is_situ_needed;
पूर्ण __packed;

काष्ठा rect अणु
	s32 x1, y1; /* top left corner */
	s32 x2, y2; /* bottom right corner, exclusive */
पूर्ण __packed;

काष्ठा synthvid_dirt अणु
	u8 video_output;
	u8 dirt_count;
	काष्ठा rect rect[1];
पूर्ण __packed;

काष्ठा synthvid_msg अणु
	काष्ठा pipe_msg_hdr pipe_hdr;
	काष्ठा synthvid_msg_hdr vid_hdr;
	जोड़ अणु
		काष्ठा synthvid_version_req ver_req;
		काष्ठा synthvid_version_resp ver_resp;
		काष्ठा synthvid_vram_location vram;
		काष्ठा synthvid_vram_location_ack vram_ack;
		काष्ठा synthvid_situation_update situ;
		काष्ठा synthvid_situation_update_ack situ_ack;
		काष्ठा synthvid_poपूर्णांकer_position ptr_pos;
		काष्ठा synthvid_poपूर्णांकer_shape ptr_shape;
		काष्ठा synthvid_feature_change feature_chg;
		काष्ठा synthvid_dirt dirt;
		काष्ठा synthvid_supported_resolution_req resolution_req;
		काष्ठा synthvid_supported_resolution_resp resolution_resp;
	पूर्ण;
पूर्ण __packed;


/* FB driver definitions and काष्ठाures */
#घोषणा HVFB_WIDTH 1152 /* शेष screen width */
#घोषणा HVFB_HEIGHT 864 /* शेष screen height */
#घोषणा HVFB_WIDTH_MIN 640
#घोषणा HVFB_HEIGHT_MIN 480

#घोषणा RING_बफ_मानE (256 * 1024)
#घोषणा VSP_TIMEOUT (10 * HZ)
#घोषणा HVFB_UPDATE_DELAY (HZ / 20)
#घोषणा HVFB_ONDEMAND_THROTTLE (HZ / 20)

काष्ठा hvfb_par अणु
	काष्ठा fb_info *info;
	काष्ठा resource *mem;
	bool fb_पढ़ोy; /* fb device is पढ़ोy */
	काष्ठा completion रुको;
	u32 synthvid_version;

	काष्ठा delayed_work dwork;
	bool update;
	bool update_saved; /* The value of 'update' beक्रमe hibernation */

	u32 pseuकरो_palette[16];
	u8 init_buf[MAX_VMBUS_PKT_SIZE];
	u8 recv_buf[MAX_VMBUS_PKT_SIZE];

	/* If true, the VSC notअगरies the VSP on every framebuffer change */
	bool synchronous_fb;

	/* If true, need to copy from deferred IO mem to framebuffer mem */
	bool need_करोcopy;

	काष्ठा notअगरier_block hvfb_panic_nb;

	/* Memory क्रम deferred IO and frame buffer itself */
	अचिन्हित अक्षर *dio_vp;
	अचिन्हित अक्षर *mmio_vp;
	phys_addr_t mmio_pp;

	/* Dirty rectangle, रक्षित by delayed_refresh_lock */
	पूर्णांक x1, y1, x2, y2;
	bool delayed_refresh;
	spinlock_t delayed_refresh_lock;
पूर्ण;

अटल uपूर्णांक screen_width = HVFB_WIDTH;
अटल uपूर्णांक screen_height = HVFB_HEIGHT;
अटल uपूर्णांक screen_width_max = HVFB_WIDTH;
अटल uपूर्णांक screen_height_max = HVFB_HEIGHT;
अटल uपूर्णांक screen_depth;
अटल uपूर्णांक screen_fb_size;
अटल uपूर्णांक dio_fb_size; /* FB size क्रम deferred IO */

/* Send message to Hyper-V host */
अटल अंतरभूत पूर्णांक synthvid_send(काष्ठा hv_device *hdev,
				काष्ठा synthvid_msg *msg)
अणु
	अटल atomic64_t request_id = ATOMIC64_INIT(0);
	पूर्णांक ret;

	msg->pipe_hdr.type = PIPE_MSG_DATA;
	msg->pipe_hdr.size = msg->vid_hdr.size;

	ret = vmbus_sendpacket(hdev->channel, msg,
			       msg->vid_hdr.size + माप(काष्ठा pipe_msg_hdr),
			       atomic64_inc_वापस(&request_id),
			       VM_PKT_DATA_INBAND, 0);

	अगर (ret)
		pr_err_ratelimited("Unable to send packet via vmbus; error %d\n", ret);

	वापस ret;
पूर्ण


/* Send screen resolution info to host */
अटल पूर्णांक synthvid_send_situ(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा synthvid_msg msg;

	अगर (!info)
		वापस -ENODEV;

	स_रखो(&msg, 0, माप(काष्ठा synthvid_msg));

	msg.vid_hdr.type = SYNTHVID_SITUATION_UPDATE;
	msg.vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_situation_update);
	msg.situ.user_ctx = 0;
	msg.situ.video_output_count = 1;
	msg.situ.video_output[0].active = 1;
	msg.situ.video_output[0].vram_offset = 0;
	msg.situ.video_output[0].depth_bits = info->var.bits_per_pixel;
	msg.situ.video_output[0].width_pixels = info->var.xres;
	msg.situ.video_output[0].height_pixels = info->var.yres;
	msg.situ.video_output[0].pitch_bytes = info->fix.line_length;

	synthvid_send(hdev, &msg);

	वापस 0;
पूर्ण

/* Send mouse poपूर्णांकer info to host */
अटल पूर्णांक synthvid_send_ptr(काष्ठा hv_device *hdev)
अणु
	काष्ठा synthvid_msg msg;

	स_रखो(&msg, 0, माप(काष्ठा synthvid_msg));
	msg.vid_hdr.type = SYNTHVID_POINTER_POSITION;
	msg.vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_poपूर्णांकer_position);
	msg.ptr_pos.is_visible = 1;
	msg.ptr_pos.video_output = 0;
	msg.ptr_pos.image_x = 0;
	msg.ptr_pos.image_y = 0;
	synthvid_send(hdev, &msg);

	स_रखो(&msg, 0, माप(काष्ठा synthvid_msg));
	msg.vid_hdr.type = SYNTHVID_POINTER_SHAPE;
	msg.vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_poपूर्णांकer_shape);
	msg.ptr_shape.part_idx = CURSOR_COMPLETE;
	msg.ptr_shape.is_argb = 1;
	msg.ptr_shape.width = 1;
	msg.ptr_shape.height = 1;
	msg.ptr_shape.hot_x = 0;
	msg.ptr_shape.hot_y = 0;
	msg.ptr_shape.data[0] = 0;
	msg.ptr_shape.data[1] = 1;
	msg.ptr_shape.data[2] = 1;
	msg.ptr_shape.data[3] = 1;
	synthvid_send(hdev, &msg);

	वापस 0;
पूर्ण

/* Send updated screen area (dirty rectangle) location to host */
अटल पूर्णांक
synthvid_update(काष्ठा fb_info *info, पूर्णांक x1, पूर्णांक y1, पूर्णांक x2, पूर्णांक y2)
अणु
	काष्ठा hv_device *hdev = device_to_hv_device(info->device);
	काष्ठा synthvid_msg msg;

	स_रखो(&msg, 0, माप(काष्ठा synthvid_msg));
	अगर (x2 == पूर्णांक_उच्च)
		x2 = info->var.xres;
	अगर (y2 == पूर्णांक_उच्च)
		y2 = info->var.yres;

	msg.vid_hdr.type = SYNTHVID_सूचीT;
	msg.vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_dirt);
	msg.dirt.video_output = 0;
	msg.dirt.dirt_count = 1;
	msg.dirt.rect[0].x1 = (x1 > x2) ? 0 : x1;
	msg.dirt.rect[0].y1 = (y1 > y2) ? 0 : y1;
	msg.dirt.rect[0].x2 =
		(x2 < x1 || x2 > info->var.xres) ? info->var.xres : x2;
	msg.dirt.rect[0].y2 =
		(y2 < y1 || y2 > info->var.yres) ? info->var.yres : y2;

	synthvid_send(hdev, &msg);

	वापस 0;
पूर्ण

अटल व्योम hvfb_करोcopy(काष्ठा hvfb_par *par,
			अचिन्हित दीर्घ offset,
			अचिन्हित दीर्घ size)
अणु
	अगर (!par || !par->mmio_vp || !par->dio_vp || !par->fb_पढ़ोy ||
	    size == 0 || offset >= dio_fb_size)
		वापस;

	अगर (offset + size > dio_fb_size)
		size = dio_fb_size - offset;

	स_नकल(par->mmio_vp + offset, par->dio_vp + offset, size);
पूर्ण

/* Deferred IO callback */
अटल व्योम synthvid_deferred_io(काष्ठा fb_info *p,
				 काष्ठा list_head *pagelist)
अणु
	काष्ठा hvfb_par *par = p->par;
	काष्ठा page *page;
	अचिन्हित दीर्घ start, end;
	पूर्णांक y1, y2, miny, maxy;

	miny = पूर्णांक_उच्च;
	maxy = 0;

	/*
	 * Merge dirty pages. It is possible that last page cross
	 * over the end of frame buffer row yres. This is taken care of
	 * in synthvid_update function by clamping the y2
	 * value to yres.
	 */
	list_क्रम_each_entry(page, pagelist, lru) अणु
		start = page->index << PAGE_SHIFT;
		end = start + PAGE_SIZE - 1;
		y1 = start / p->fix.line_length;
		y2 = end / p->fix.line_length;
		miny = min_t(पूर्णांक, miny, y1);
		maxy = max_t(पूर्णांक, maxy, y2);

		/* Copy from dio space to mmio address */
		अगर (par->fb_पढ़ोy && par->need_करोcopy)
			hvfb_करोcopy(par, start, PAGE_SIZE);
	पूर्ण

	अगर (par->fb_पढ़ोy && par->update)
		synthvid_update(p, 0, miny, p->var.xres, maxy + 1);
पूर्ण

अटल काष्ठा fb_deferred_io synthvid_defio = अणु
	.delay		= HZ / 20,
	.deferred_io	= synthvid_deferred_io,
पूर्ण;

/*
 * Actions on received messages from host:
 * Complete the रुको event.
 * Or, reply with screen and cursor info.
 */
अटल व्योम synthvid_recv_sub(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par;
	काष्ठा synthvid_msg *msg;

	अगर (!info)
		वापस;

	par = info->par;
	msg = (काष्ठा synthvid_msg *)par->recv_buf;

	/* Complete the रुको event */
	अगर (msg->vid_hdr.type == SYNTHVID_VERSION_RESPONSE ||
	    msg->vid_hdr.type == SYNTHVID_RESOLUTION_RESPONSE ||
	    msg->vid_hdr.type == SYNTHVID_VRAM_LOCATION_ACK) अणु
		स_नकल(par->init_buf, msg, MAX_VMBUS_PKT_SIZE);
		complete(&par->रुको);
		वापस;
	पूर्ण

	/* Reply with screen and cursor info */
	अगर (msg->vid_hdr.type == SYNTHVID_FEATURE_CHANGE) अणु
		अगर (par->fb_पढ़ोy) अणु
			synthvid_send_ptr(hdev);
			synthvid_send_situ(hdev);
		पूर्ण

		par->update = msg->feature_chg.is_dirt_needed;
		अगर (par->update)
			schedule_delayed_work(&par->dwork, HVFB_UPDATE_DELAY);
	पूर्ण
पूर्ण

/* Receive callback क्रम messages from the host */
अटल व्योम synthvid_receive(व्योम *ctx)
अणु
	काष्ठा hv_device *hdev = ctx;
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par;
	काष्ठा synthvid_msg *recv_buf;
	u32 bytes_recvd;
	u64 req_id;
	पूर्णांक ret;

	अगर (!info)
		वापस;

	par = info->par;
	recv_buf = (काष्ठा synthvid_msg *)par->recv_buf;

	करो अणु
		ret = vmbus_recvpacket(hdev->channel, recv_buf,
				       MAX_VMBUS_PKT_SIZE,
				       &bytes_recvd, &req_id);
		अगर (bytes_recvd > 0 &&
		    recv_buf->pipe_hdr.type == PIPE_MSG_DATA)
			synthvid_recv_sub(hdev);
	पूर्ण जबतक (bytes_recvd > 0 && ret == 0);
पूर्ण

/* Check अगर the ver1 version is equal or greater than ver2 */
अटल अंतरभूत bool synthvid_ver_ge(u32 ver1, u32 ver2)
अणु
	अगर (SYNTHVID_VER_GET_MAJOR(ver1) > SYNTHVID_VER_GET_MAJOR(ver2) ||
	    (SYNTHVID_VER_GET_MAJOR(ver1) == SYNTHVID_VER_GET_MAJOR(ver2) &&
	     SYNTHVID_VER_GET_MINOR(ver1) >= SYNTHVID_VER_GET_MINOR(ver2)))
		वापस true;

	वापस false;
पूर्ण

/* Check synthetic video protocol version with the host */
अटल पूर्णांक synthvid_negotiate_ver(काष्ठा hv_device *hdev, u32 ver)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;
	काष्ठा synthvid_msg *msg = (काष्ठा synthvid_msg *)par->init_buf;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ t;

	स_रखो(msg, 0, माप(काष्ठा synthvid_msg));
	msg->vid_hdr.type = SYNTHVID_VERSION_REQUEST;
	msg->vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_version_req);
	msg->ver_req.version = ver;
	synthvid_send(hdev, msg);

	t = रुको_क्रम_completion_समयout(&par->रुको, VSP_TIMEOUT);
	अगर (!t) अणु
		pr_err("Time out on waiting version response\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण
	अगर (!msg->ver_resp.is_accepted) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	par->synthvid_version = ver;
	pr_info("Synthvid Version major %d, minor %d\n",
		SYNTHVID_VER_GET_MAJOR(ver), SYNTHVID_VER_GET_MINOR(ver));

out:
	वापस ret;
पूर्ण

/* Get current resolution from the host */
अटल पूर्णांक synthvid_get_supported_resolution(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;
	काष्ठा synthvid_msg *msg = (काष्ठा synthvid_msg *)par->init_buf;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ t;
	u8 index;
	पूर्णांक i;

	स_रखो(msg, 0, माप(काष्ठा synthvid_msg));
	msg->vid_hdr.type = SYNTHVID_RESOLUTION_REQUEST;
	msg->vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_supported_resolution_req);

	msg->resolution_req.maximum_resolution_count =
		SYNTHVID_MAX_RESOLUTION_COUNT;
	synthvid_send(hdev, msg);

	t = रुको_क्रम_completion_समयout(&par->रुको, VSP_TIMEOUT);
	अगर (!t) अणु
		pr_err("Time out on waiting resolution response\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	अगर (msg->resolution_resp.resolution_count == 0) अणु
		pr_err("No supported resolutions\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	index = msg->resolution_resp.शेष_resolution_index;
	अगर (index >= msg->resolution_resp.resolution_count) अणु
		pr_err("Invalid resolution index: %d\n", index);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < msg->resolution_resp.resolution_count; i++) अणु
		screen_width_max = max_t(अचिन्हित पूर्णांक, screen_width_max,
		    msg->resolution_resp.supported_resolution[i].width);
		screen_height_max = max_t(अचिन्हित पूर्णांक, screen_height_max,
		    msg->resolution_resp.supported_resolution[i].height);
	पूर्ण

	screen_width =
		msg->resolution_resp.supported_resolution[index].width;
	screen_height =
		msg->resolution_resp.supported_resolution[index].height;

out:
	वापस ret;
पूर्ण

/* Connect to VSP (Virtual Service Provider) on host */
अटल पूर्णांक synthvid_connect_vsp(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;
	पूर्णांक ret;

	ret = vmbus_खोलो(hdev->channel, RING_बफ_मानE, RING_बफ_मानE,
			 शून्य, 0, synthvid_receive, hdev);
	अगर (ret) अणु
		pr_err("Unable to open vmbus channel\n");
		वापस ret;
	पूर्ण

	/* Negotiate the protocol version with host */
	चयन (vmbus_proto_version) अणु
	हाल VERSION_WIN10:
	हाल VERSION_WIN10_V5:
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN10);
		अगर (!ret)
			अवरोध;
		fallthrough;
	हाल VERSION_WIN8:
	हाल VERSION_WIN8_1:
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN8);
		अगर (!ret)
			अवरोध;
		fallthrough;
	हाल VERSION_WS2008:
	हाल VERSION_WIN7:
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN7);
		अवरोध;
	शेष:
		ret = synthvid_negotiate_ver(hdev, SYNTHVID_VERSION_WIN10);
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		pr_err("Synthetic video device version not accepted\n");
		जाओ error;
	पूर्ण

	अगर (par->synthvid_version == SYNTHVID_VERSION_WIN7)
		screen_depth = SYNTHVID_DEPTH_WIN7;
	अन्यथा
		screen_depth = SYNTHVID_DEPTH_WIN8;

	अगर (synthvid_ver_ge(par->synthvid_version, SYNTHVID_VERSION_WIN10)) अणु
		ret = synthvid_get_supported_resolution(hdev);
		अगर (ret)
			pr_info("Failed to get supported resolution from host, use default\n");
	पूर्ण

	screen_fb_size = hdev->channel->offermsg.offer.
				mmio_megabytes * 1024 * 1024;

	वापस 0;

error:
	vmbus_बंद(hdev->channel);
	वापस ret;
पूर्ण

/* Send VRAM and Situation messages to the host */
अटल पूर्णांक synthvid_send_config(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;
	काष्ठा synthvid_msg *msg = (काष्ठा synthvid_msg *)par->init_buf;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ t;

	/* Send VRAM location */
	स_रखो(msg, 0, माप(काष्ठा synthvid_msg));
	msg->vid_hdr.type = SYNTHVID_VRAM_LOCATION;
	msg->vid_hdr.size = माप(काष्ठा synthvid_msg_hdr) +
		माप(काष्ठा synthvid_vram_location);
	msg->vram.user_ctx = msg->vram.vram_gpa = par->mmio_pp;
	msg->vram.is_vram_gpa_specअगरied = 1;
	synthvid_send(hdev, msg);

	t = रुको_क्रम_completion_समयout(&par->रुको, VSP_TIMEOUT);
	अगर (!t) अणु
		pr_err("Time out on waiting vram location ack\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण
	अगर (msg->vram_ack.user_ctx != par->mmio_pp) अणु
		pr_err("Unable to set VRAM location\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Send poपूर्णांकer and situation update */
	synthvid_send_ptr(hdev);
	synthvid_send_situ(hdev);

out:
	वापस ret;
पूर्ण


/*
 * Delayed work callback:
 * It is scheduled to call whenever update request is received and it has
 * not been called in last HVFB_ONDEMAND_THROTTLE समय पूर्णांकerval.
 */
अटल व्योम hvfb_update_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा hvfb_par *par = container_of(w, काष्ठा hvfb_par, dwork.work);
	काष्ठा fb_info *info = par->info;
	अचिन्हित दीर्घ flags;
	पूर्णांक x1, x2, y1, y2;
	पूर्णांक j;

	spin_lock_irqsave(&par->delayed_refresh_lock, flags);
	/* Reset the request flag */
	par->delayed_refresh = false;

	/* Store the dirty rectangle to local variables */
	x1 = par->x1;
	x2 = par->x2;
	y1 = par->y1;
	y2 = par->y2;

	/* Clear dirty rectangle */
	par->x1 = par->y1 = पूर्णांक_उच्च;
	par->x2 = par->y2 = 0;

	spin_unlock_irqrestore(&par->delayed_refresh_lock, flags);

	अगर (x1 > info->var.xres || x2 > info->var.xres ||
	    y1 > info->var.yres || y2 > info->var.yres || x2 <= x1)
		वापस;

	/* Copy the dirty rectangle to frame buffer memory */
	अगर (par->need_करोcopy)
		क्रम (j = y1; j < y2; j++)
			hvfb_करोcopy(par,
				    j * info->fix.line_length +
				    (x1 * screen_depth / 8),
				    (x2 - x1) * screen_depth / 8);

	/* Refresh */
	अगर (par->fb_पढ़ोy && par->update)
		synthvid_update(info, x1, y1, x2, y2);
पूर्ण

/*
 * Control the on-demand refresh frequency. It schedules a delayed
 * screen update अगर it has not yet.
 */
अटल व्योम hvfb_ondemand_refresh_throttle(काष्ठा hvfb_par *par,
					   पूर्णांक x1, पूर्णांक y1, पूर्णांक w, पूर्णांक h)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक x2 = x1 + w;
	पूर्णांक y2 = y1 + h;

	spin_lock_irqsave(&par->delayed_refresh_lock, flags);

	/* Merge dirty rectangle */
	par->x1 = min_t(पूर्णांक, par->x1, x1);
	par->y1 = min_t(पूर्णांक, par->y1, y1);
	par->x2 = max_t(पूर्णांक, par->x2, x2);
	par->y2 = max_t(पूर्णांक, par->y2, y2);

	/* Schedule a delayed screen update अगर not yet */
	अगर (par->delayed_refresh == false) अणु
		schedule_delayed_work(&par->dwork,
				      HVFB_ONDEMAND_THROTTLE);
		par->delayed_refresh = true;
	पूर्ण

	spin_unlock_irqrestore(&par->delayed_refresh_lock, flags);
पूर्ण

अटल पूर्णांक hvfb_on_panic(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ e, व्योम *p)
अणु
	काष्ठा hvfb_par *par;
	काष्ठा fb_info *info;

	par = container_of(nb, काष्ठा hvfb_par, hvfb_panic_nb);
	par->synchronous_fb = true;
	info = par->info;
	अगर (par->need_करोcopy)
		hvfb_करोcopy(par, 0, dio_fb_size);
	synthvid_update(info, 0, 0, पूर्णांक_उच्च, पूर्णांक_उच्च);

	वापस NOTIFY_DONE;
पूर्ण

/* Framebuffer operation handlers */

अटल पूर्णांक hvfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अगर (var->xres < HVFB_WIDTH_MIN || var->yres < HVFB_HEIGHT_MIN ||
	    var->xres > screen_width || var->yres >  screen_height ||
	    var->bits_per_pixel != screen_depth)
		वापस -EINVAL;

	var->xres_भव = var->xres;
	var->yres_भव = var->yres;

	वापस 0;
पूर्ण

अटल पूर्णांक hvfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा hv_device *hdev = device_to_hv_device(info->device);

	वापस synthvid_send_situ(hdev);
पूर्ण


अटल अंतरभूत u32 chan_to_field(u32 chan, काष्ठा fb_bitfield *bf)
अणु
	वापस ((chan & 0xffff) >> (16 - bf->length)) << bf->offset;
पूर्ण

अटल पूर्णांक hvfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			  अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	u32 *pal = info->pseuकरो_palette;

	अगर (regno > 15)
		वापस -EINVAL;

	pal[regno] = chan_to_field(red, &info->var.red)
		| chan_to_field(green, &info->var.green)
		| chan_to_field(blue, &info->var.blue)
		| chan_to_field(transp, &info->var.transp);

	वापस 0;
पूर्ण

अटल पूर्णांक hvfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	वापस 1;	/* get fb_blank to set the colormap to all black */
पूर्ण

अटल व्योम hvfb_cfb_fillrect(काष्ठा fb_info *p,
			      स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा hvfb_par *par = p->par;

	cfb_fillrect(p, rect);
	अगर (par->synchronous_fb)
		synthvid_update(p, 0, 0, पूर्णांक_उच्च, पूर्णांक_उच्च);
	अन्यथा
		hvfb_ondemand_refresh_throttle(par, rect->dx, rect->dy,
					       rect->width, rect->height);
पूर्ण

अटल व्योम hvfb_cfb_copyarea(काष्ठा fb_info *p,
			      स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा hvfb_par *par = p->par;

	cfb_copyarea(p, area);
	अगर (par->synchronous_fb)
		synthvid_update(p, 0, 0, पूर्णांक_उच्च, पूर्णांक_उच्च);
	अन्यथा
		hvfb_ondemand_refresh_throttle(par, area->dx, area->dy,
					       area->width, area->height);
पूर्ण

अटल व्योम hvfb_cfb_imageblit(काष्ठा fb_info *p,
			       स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा hvfb_par *par = p->par;

	cfb_imageblit(p, image);
	अगर (par->synchronous_fb)
		synthvid_update(p, 0, 0, पूर्णांक_उच्च, पूर्णांक_उच्च);
	अन्यथा
		hvfb_ondemand_refresh_throttle(par, image->dx, image->dy,
					       image->width, image->height);
पूर्ण

अटल स्थिर काष्ठा fb_ops hvfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var = hvfb_check_var,
	.fb_set_par = hvfb_set_par,
	.fb_setcolreg = hvfb_setcolreg,
	.fb_fillrect = hvfb_cfb_fillrect,
	.fb_copyarea = hvfb_cfb_copyarea,
	.fb_imageblit = hvfb_cfb_imageblit,
	.fb_blank = hvfb_blank,
पूर्ण;


/* Get options from kernel paramenter "video=" */
अटल व्योम hvfb_get_option(काष्ठा fb_info *info)
अणु
	काष्ठा hvfb_par *par = info->par;
	अक्षर *opt = शून्य, *p;
	uपूर्णांक x = 0, y = 0;

	अगर (fb_get_options(KBUILD_MODNAME, &opt) || !opt || !*opt)
		वापस;

	p = strsep(&opt, "x");
	अगर (!*p || kstrtouपूर्णांक(p, 0, &x) ||
	    !opt || !*opt || kstrtouपूर्णांक(opt, 0, &y)) अणु
		pr_err("Screen option is invalid: skipped\n");
		वापस;
	पूर्ण

	अगर (x < HVFB_WIDTH_MIN || y < HVFB_HEIGHT_MIN ||
	    (synthvid_ver_ge(par->synthvid_version, SYNTHVID_VERSION_WIN10) &&
	    (x > screen_width_max || y > screen_height_max)) ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN8 &&
	     x * y * screen_depth / 8 > SYNTHVID_FB_SIZE_WIN8) ||
	    (par->synthvid_version == SYNTHVID_VERSION_WIN7 &&
	     (x > SYNTHVID_WIDTH_MAX_WIN7 || y > SYNTHVID_HEIGHT_MAX_WIN7))) अणु
		pr_err("Screen resolution option is out of range: skipped\n");
		वापस;
	पूर्ण

	screen_width = x;
	screen_height = y;
	वापस;
पूर्ण

/*
 * Allocate enough contiguous physical memory.
 * Return physical address अगर succeeded or -1 अगर failed.
 */
अटल phys_addr_t hvfb_get_phymem(काष्ठा hv_device *hdev,
				   अचिन्हित पूर्णांक request_size)
अणु
	काष्ठा page *page = शून्य;
	dma_addr_t dma_handle;
	व्योम *vmem;
	phys_addr_t paddr = 0;
	अचिन्हित पूर्णांक order = get_order(request_size);

	अगर (request_size == 0)
		वापस -1;

	अगर (order < MAX_ORDER) अणु
		/* Call alloc_pages अगर the size is less than 2^MAX_ORDER */
		page = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
		अगर (!page)
			वापस -1;

		paddr = (page_to_pfn(page) << PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		/* Allocate from CMA */
		hdev->device.coherent_dma_mask = DMA_BIT_MASK(64);

		vmem = dma_alloc_coherent(&hdev->device,
					  round_up(request_size, PAGE_SIZE),
					  &dma_handle,
					  GFP_KERNEL | __GFP_NOWARN);

		अगर (!vmem)
			वापस -1;

		paddr = virt_to_phys(vmem);
	पूर्ण

	वापस paddr;
पूर्ण

/* Release contiguous physical memory */
अटल व्योम hvfb_release_phymem(काष्ठा hv_device *hdev,
				phys_addr_t paddr, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक order = get_order(size);

	अगर (order < MAX_ORDER)
		__मुक्त_pages(pfn_to_page(paddr >> PAGE_SHIFT), order);
	अन्यथा
		dma_मुक्त_coherent(&hdev->device,
				  round_up(size, PAGE_SIZE),
				  phys_to_virt(paddr),
				  paddr);
पूर्ण


/* Get framebuffer memory from Hyper-V video pci space */
अटल पूर्णांक hvfb_geपंचांगem(काष्ठा hv_device *hdev, काष्ठा fb_info *info)
अणु
	काष्ठा hvfb_par *par = info->par;
	काष्ठा pci_dev *pdev  = शून्य;
	व्योम __iomem *fb_virt;
	पूर्णांक gen2vm = efi_enabled(EFI_BOOT);
	resource_माप_प्रकार pot_start, pot_end;
	phys_addr_t paddr;
	पूर्णांक ret;

	info->apertures = alloc_apertures(1);
	अगर (!info->apertures)
		वापस -ENOMEM;

	अगर (!gen2vm) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_MICROSOFT,
			PCI_DEVICE_ID_HYPERV_VIDEO, शून्य);
		अगर (!pdev) अणु
			pr_err("Unable to find PCI Hyper-V video\n");
			वापस -ENODEV;
		पूर्ण

		info->apertures->ranges[0].base = pci_resource_start(pdev, 0);
		info->apertures->ranges[0].size = pci_resource_len(pdev, 0);

		/*
		 * For Gen 1 VM, we can directly use the contiguous memory
		 * from VM. If we succeed, deferred IO happens directly
		 * on this allocated framebuffer memory, aव्योमing extra
		 * memory copy.
		 */
		paddr = hvfb_get_phymem(hdev, screen_fb_size);
		अगर (paddr != (phys_addr_t) -1) अणु
			par->mmio_pp = paddr;
			par->mmio_vp = par->dio_vp = __va(paddr);

			info->fix.smem_start = paddr;
			info->fix.smem_len = screen_fb_size;
			info->screen_base = par->mmio_vp;
			info->screen_size = screen_fb_size;

			par->need_करोcopy = false;
			जाओ geपंचांगem_करोne;
		पूर्ण
		pr_info("Unable to allocate enough contiguous physical memory on Gen 1 VM. Using MMIO instead.\n");
	पूर्ण अन्यथा अणु
		info->apertures->ranges[0].base = screen_info.lfb_base;
		info->apertures->ranges[0].size = screen_info.lfb_size;
	पूर्ण

	/*
	 * Cannot use the contiguous physical memory.
	 * Allocate mmio space क्रम framebuffer.
	 */
	dio_fb_size =
		screen_width * screen_height * screen_depth / 8;

	अगर (gen2vm) अणु
		pot_start = 0;
		pot_end = -1;
	पूर्ण अन्यथा अणु
		अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
		    pci_resource_len(pdev, 0) < screen_fb_size) अणु
			pr_err("Resource not available or (0x%lx < 0x%lx)\n",
			       (अचिन्हित दीर्घ) pci_resource_len(pdev, 0),
			       (अचिन्हित दीर्घ) screen_fb_size);
			जाओ err1;
		पूर्ण

		pot_end = pci_resource_end(pdev, 0);
		pot_start = pot_end - screen_fb_size + 1;
	पूर्ण

	ret = vmbus_allocate_mmio(&par->mem, hdev, pot_start, pot_end,
				  screen_fb_size, 0x100000, true);
	अगर (ret != 0) अणु
		pr_err("Unable to allocate framebuffer memory\n");
		जाओ err1;
	पूर्ण

	/*
	 * Map the VRAM cacheable क्रम perक्रमmance. This is also required क्रम
	 * VM Connect to display properly क्रम ARM64 Linux VM, as the host also
	 * maps the VRAM cacheable.
	 */
	fb_virt = ioremap_cache(par->mem->start, screen_fb_size);
	अगर (!fb_virt)
		जाओ err2;

	/* Allocate memory क्रम deferred IO */
	par->dio_vp = vzalloc(round_up(dio_fb_size, PAGE_SIZE));
	अगर (par->dio_vp == शून्य)
		जाओ err3;

	/* Physical address of FB device */
	par->mmio_pp = par->mem->start;
	/* Virtual address of FB device */
	par->mmio_vp = (अचिन्हित अक्षर *) fb_virt;

	info->fix.smem_start = par->mem->start;
	info->fix.smem_len = dio_fb_size;
	info->screen_base = par->dio_vp;
	info->screen_size = dio_fb_size;

geपंचांगem_करोne:
	हटाओ_conflicting_framebuffers(info->apertures,
					KBUILD_MODNAME, false);

	अगर (gen2vm) अणु
		/* framebuffer is पुनः_स्मृतिated, clear screen_info to aव्योम misuse from kexec */
		screen_info.lfb_size = 0;
		screen_info.lfb_base = 0;
		screen_info.orig_video_isVGA = 0;
	पूर्ण अन्यथा अणु
		pci_dev_put(pdev);
	पूर्ण

	वापस 0;

err3:
	iounmap(fb_virt);
err2:
	vmbus_मुक्त_mmio(par->mem->start, screen_fb_size);
	par->mem = शून्य;
err1:
	अगर (!gen2vm)
		pci_dev_put(pdev);

	वापस -ENOMEM;
पूर्ण

/* Release the framebuffer */
अटल व्योम hvfb_puपंचांगem(काष्ठा hv_device *hdev, काष्ठा fb_info *info)
अणु
	काष्ठा hvfb_par *par = info->par;

	अगर (par->need_करोcopy) अणु
		vमुक्त(par->dio_vp);
		iounmap(info->screen_base);
		vmbus_मुक्त_mmio(par->mem->start, screen_fb_size);
	पूर्ण अन्यथा अणु
		hvfb_release_phymem(hdev, info->fix.smem_start,
				    screen_fb_size);
	पूर्ण

	par->mem = शून्य;
पूर्ण


अटल पूर्णांक hvfb_probe(काष्ठा hv_device *hdev,
		      स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा fb_info *info;
	काष्ठा hvfb_par *par;
	पूर्णांक ret;

	info = framebuffer_alloc(माप(काष्ठा hvfb_par), &hdev->device);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->info = info;
	par->fb_पढ़ोy = false;
	par->need_करोcopy = true;
	init_completion(&par->रुको);
	INIT_DELAYED_WORK(&par->dwork, hvfb_update_work);

	par->delayed_refresh = false;
	spin_lock_init(&par->delayed_refresh_lock);
	par->x1 = par->y1 = पूर्णांक_उच्च;
	par->x2 = par->y2 = 0;

	/* Connect to VSP */
	hv_set_drvdata(hdev, info);
	ret = synthvid_connect_vsp(hdev);
	अगर (ret) अणु
		pr_err("Unable to connect to VSP\n");
		जाओ error1;
	पूर्ण

	hvfb_get_option(info);
	pr_info("Screen resolution: %dx%d, Color depth: %d\n",
		screen_width, screen_height, screen_depth);

	ret = hvfb_geपंचांगem(hdev, info);
	अगर (ret) अणु
		pr_err("No memory for framebuffer\n");
		जाओ error2;
	पूर्ण

	/* Set up fb_info */
	info->flags = FBINFO_DEFAULT;

	info->var.xres_भव = info->var.xres = screen_width;
	info->var.yres_भव = info->var.yres = screen_height;
	info->var.bits_per_pixel = screen_depth;

	अगर (info->var.bits_per_pixel == 16) अणु
		info->var.red = (काष्ठा fb_bitfield)अणु11, 5, 0पूर्ण;
		info->var.green = (काष्ठा fb_bitfield)अणु5, 6, 0पूर्ण;
		info->var.blue = (काष्ठा fb_bitfield)अणु0, 5, 0पूर्ण;
		info->var.transp = (काष्ठा fb_bitfield)अणु0, 0, 0पूर्ण;
	पूर्ण अन्यथा अणु
		info->var.red = (काष्ठा fb_bitfield)अणु16, 8, 0पूर्ण;
		info->var.green = (काष्ठा fb_bitfield)अणु8, 8, 0पूर्ण;
		info->var.blue = (काष्ठा fb_bitfield)अणु0, 8, 0पूर्ण;
		info->var.transp = (काष्ठा fb_bitfield)अणु24, 8, 0पूर्ण;
	पूर्ण

	info->var.activate = FB_ACTIVATE_NOW;
	info->var.height = -1;
	info->var.width = -1;
	info->var.vmode = FB_VMODE_NONINTERLACED;

	म_नकल(info->fix.id, KBUILD_MODNAME);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;
	info->fix.line_length = screen_width * screen_depth / 8;
	info->fix.accel = FB_ACCEL_NONE;

	info->fbops = &hvfb_ops;
	info->pseuकरो_palette = par->pseuकरो_palette;

	/* Initialize deferred IO */
	info->fbdefio = &synthvid_defio;
	fb_deferred_io_init(info);

	/* Send config to host */
	ret = synthvid_send_config(hdev);
	अगर (ret)
		जाओ error;

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret) अणु
		pr_err("Unable to register framebuffer\n");
		जाओ error;
	पूर्ण

	par->fb_पढ़ोy = true;

	par->synchronous_fb = false;
	par->hvfb_panic_nb.notअगरier_call = hvfb_on_panic;
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &par->hvfb_panic_nb);

	वापस 0;

error:
	fb_deferred_io_cleanup(info);
	hvfb_puपंचांगem(hdev, info);
error2:
	vmbus_बंद(hdev->channel);
error1:
	cancel_delayed_work_sync(&par->dwork);
	hv_set_drvdata(hdev, शून्य);
	framebuffer_release(info);
	वापस ret;
पूर्ण


अटल पूर्णांक hvfb_हटाओ(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;

	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &par->hvfb_panic_nb);

	par->update = false;
	par->fb_पढ़ोy = false;

	fb_deferred_io_cleanup(info);

	unरेजिस्टर_framebuffer(info);
	cancel_delayed_work_sync(&par->dwork);

	vmbus_बंद(hdev->channel);
	hv_set_drvdata(hdev, शून्य);

	hvfb_puपंचांगem(hdev, info);
	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल पूर्णांक hvfb_suspend(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;

	console_lock();

	/* 1 means करो suspend */
	fb_set_suspend(info, 1);

	cancel_delayed_work_sync(&par->dwork);
	cancel_delayed_work_sync(&info->deferred_work);

	par->update_saved = par->update;
	par->update = false;
	par->fb_पढ़ोy = false;

	vmbus_बंद(hdev->channel);

	console_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक hvfb_resume(काष्ठा hv_device *hdev)
अणु
	काष्ठा fb_info *info = hv_get_drvdata(hdev);
	काष्ठा hvfb_par *par = info->par;
	पूर्णांक ret;

	console_lock();

	ret = synthvid_connect_vsp(hdev);
	अगर (ret != 0)
		जाओ out;

	ret = synthvid_send_config(hdev);
	अगर (ret != 0) अणु
		vmbus_बंद(hdev->channel);
		जाओ out;
	पूर्ण

	par->fb_पढ़ोy = true;
	par->update = par->update_saved;

	schedule_delayed_work(&info->deferred_work, info->fbdefio->delay);
	schedule_delayed_work(&par->dwork, HVFB_UPDATE_DELAY);

	/* 0 means करो resume */
	fb_set_suspend(info, 0);

out:
	console_unlock();

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा pci_device_id pci_stub_id_table[] = अणु
	अणु
		.venकरोr      = PCI_VENDOR_ID_MICROSOFT,
		.device      = PCI_DEVICE_ID_HYPERV_VIDEO,
	पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Synthetic Video Device GUID */
	अणुHV_SYNTHVID_GUIDपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pci_stub_id_table);
MODULE_DEVICE_TABLE(vmbus, id_table);

अटल काष्ठा hv_driver hvfb_drv = अणु
	.name = KBUILD_MODNAME,
	.id_table = id_table,
	.probe = hvfb_probe,
	.हटाओ = hvfb_हटाओ,
	.suspend = hvfb_suspend,
	.resume = hvfb_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hvfb_pci_stub_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *ent)
अणु
	वापस 0;
पूर्ण

अटल व्योम hvfb_pci_stub_हटाओ(काष्ठा pci_dev *pdev)
अणु
पूर्ण

अटल काष्ठा pci_driver hvfb_pci_stub_driver = अणु
	.name =		KBUILD_MODNAME,
	.id_table =	pci_stub_id_table,
	.probe =	hvfb_pci_stub_probe,
	.हटाओ =	hvfb_pci_stub_हटाओ,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init hvfb_drv_init(व्योम)
अणु
	पूर्णांक ret;

	ret = vmbus_driver_रेजिस्टर(&hvfb_drv);
	अगर (ret != 0)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&hvfb_pci_stub_driver);
	अगर (ret != 0) अणु
		vmbus_driver_unरेजिस्टर(&hvfb_drv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hvfb_drv_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hvfb_pci_stub_driver);
	vmbus_driver_unरेजिस्टर(&hvfb_drv);
पूर्ण

module_init(hvfb_drv_init);
module_निकास(hvfb_drv_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V Synthetic Video Frame Buffer Driver");
