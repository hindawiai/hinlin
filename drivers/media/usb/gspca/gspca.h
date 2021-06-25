<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GSPCAV2_H
#घोषणा GSPCAV2_H

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <linux/mutex.h>



/* GSPCA debug codes */

#घोषणा D_PROBE  1
#घोषणा D_CONF   2
#घोषणा D_STREAM 3
#घोषणा D_FRAM   4
#घोषणा D_PACK   5
#घोषणा D_USBI   6
#घोषणा D_USBO   7

बाह्य पूर्णांक gspca_debug;


#घोषणा gspca_dbg(gspca_dev, level, fmt, ...)			\
	v4l2_dbg(level, gspca_debug, &(gspca_dev)->v4l2_dev,	\
		 fmt, ##__VA_ARGS__)

#घोषणा gspca_err(gspca_dev, fmt, ...)				\
	v4l2_err(&(gspca_dev)->v4l2_dev, fmt, ##__VA_ARGS__)

#घोषणा GSPCA_MAX_FRAMES 16	/* maximum number of video frame buffers */
/* image transfers */
#घोषणा MAX_NURBS 4		/* max number of URBs */


/* used to list framerates supported by a camera mode (resolution) */
काष्ठा framerates अणु
	स्थिर u8 *rates;
	पूर्णांक nrates;
पूर्ण;

/* device inक्रमmation - set at probe समय */
काष्ठा cam अणु
	स्थिर काष्ठा v4l2_pix_क्रमmat *cam_mode;	/* size nmodes */
	स्थिर काष्ठा framerates *mode_framerates; /* must have size nmodes,
						   * just like cam_mode */
	u32 bulk_size;		/* buffer size when image transfer by bulk */
	u32 input_flags;	/* value क्रम ENUM_INPUT status flags */
	u8 nmodes;		/* size of cam_mode */
	u8 no_urb_create;	/* करोn't create transfer URBs */
	u8 bulk_nurbs;		/* number of URBs in bulk mode
				 * - cannot be > MAX_NURBS
				 * - when 0 and bulk_size != 0 means
				 *   1 URB and submit करोne by subdriver */
	u8 bulk;		/* image transfer by 0:isoc / 1:bulk */
	u8 npkt;		/* number of packets in an ISOC message
				 * 0 is the शेष value: 32 packets */
	u8 needs_full_bandwidth;/* Set this flag to notअगरy the bandwidth calc.
				 * code that the cam fills all image buffers to
				 * the max, even when using compression. */
पूर्ण;

काष्ठा gspca_dev;
काष्ठा gspca_frame;

/* subdriver operations */
प्रकार पूर्णांक (*cam_op) (काष्ठा gspca_dev *);
प्रकार व्योम (*cam_v_op) (काष्ठा gspca_dev *);
प्रकार पूर्णांक (*cam_cf_op) (काष्ठा gspca_dev *, स्थिर काष्ठा usb_device_id *);
प्रकार पूर्णांक (*cam_get_jpg_op) (काष्ठा gspca_dev *,
				काष्ठा v4l2_jpegcompression *);
प्रकार पूर्णांक (*cam_set_jpg_op) (काष्ठा gspca_dev *,
				स्थिर काष्ठा v4l2_jpegcompression *);
प्रकार पूर्णांक (*cam_get_reg_op) (काष्ठा gspca_dev *,
				काष्ठा v4l2_dbg_रेजिस्टर *);
प्रकार पूर्णांक (*cam_set_reg_op) (काष्ठा gspca_dev *,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *);
प्रकार पूर्णांक (*cam_chip_info_op) (काष्ठा gspca_dev *,
				काष्ठा v4l2_dbg_chip_info *);
प्रकार व्योम (*cam_streamparm_op) (काष्ठा gspca_dev *,
				  काष्ठा v4l2_streamparm *);
प्रकार व्योम (*cam_pkt_op) (काष्ठा gspca_dev *gspca_dev,
				u8 *data,
				पूर्णांक len);
प्रकार पूर्णांक (*cam_पूर्णांक_pkt_op) (काष्ठा gspca_dev *gspca_dev,
				u8 *data,
				पूर्णांक len);
प्रकार व्योम (*cam_क्रमmat_op) (काष्ठा gspca_dev *gspca_dev,
				काष्ठा v4l2_क्रमmat *fmt);
प्रकार पूर्णांक (*cam_frmsize_op) (काष्ठा gspca_dev *gspca_dev,
				काष्ठा v4l2_frmsizeक्रमागत *fsize);

/* subdriver description */
काष्ठा sd_desc अणु
/* inक्रमmation */
	स्थिर अक्षर *name;	/* sub-driver name */
/* mandatory operations */
	cam_cf_op config;	/* called on probe */
	cam_op init;		/* called on probe and resume */
	cam_op init_controls;	/* called on probe */
	cam_v_op probe_error;	/* called अगर probe failed, करो cleanup here */
	cam_op start;		/* called on stream on after URBs creation */
	cam_pkt_op pkt_scan;
/* optional operations */
	cam_op isoc_init;	/* called on stream on beक्रमe getting the EP */
	cam_op isoc_nego;	/* called when URB submit failed with NOSPC */
	cam_v_op stopN;		/* called on stream off - मुख्य alt */
	cam_v_op stop0;		/* called on stream off & disconnect - alt 0 */
	cam_v_op dq_callback;	/* called when a frame has been dequeued */
	cam_get_jpg_op get_jcomp;
	cam_set_jpg_op set_jcomp;
	cam_streamparm_op get_streamparm;
	cam_streamparm_op set_streamparm;
	cam_क्रमmat_op try_fmt;
	cam_frmsize_op क्रमागत_framesizes;
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	cam_set_reg_op set_रेजिस्टर;
	cam_get_reg_op get_रेजिस्टर;
	cam_chip_info_op get_chip_info;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_INPUT)
	cam_पूर्णांक_pkt_op पूर्णांक_pkt_scan;
	/* other_input makes the gspca core create gspca_dev->input even when
	   पूर्णांक_pkt_scan is शून्य, क्रम cams with non पूर्णांकerrupt driven buttons */
	u8 other_input;
#पूर्ण_अगर
पूर्ण;

/* packet types when moving from iso buf to frame buf */
क्रमागत gspca_packet_type अणु
	DISCARD_PACKET,
	FIRST_PACKET,
	INTER_PACKET,
	LAST_PACKET
पूर्ण;

काष्ठा gspca_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत काष्ठा gspca_buffer *to_gspca_buffer(काष्ठा vb2_buffer *vb2)
अणु
	वापस container_of(vb2, काष्ठा gspca_buffer, vb.vb2_buf);
पूर्ण

काष्ठा gspca_dev अणु
	काष्ठा video_device vdev;	/* !! must be the first item */
	काष्ठा module *module;		/* subdriver handling the device */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा usb_device *dev;

#अगर IS_ENABLED(CONFIG_INPUT)
	काष्ठा input_dev *input_dev;
	अक्षर phys[64];			/* physical device path */
#पूर्ण_अगर

	काष्ठा cam cam;				/* device inक्रमmation */
	स्थिर काष्ठा sd_desc *sd_desc;		/* subdriver description */
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	/* स्वतःgain and exposure or gain control cluster, these are global as
	   the स्वतःgain/exposure functions in स्वतःgain_functions.c use them */
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *gain;
		पूर्णांक exp_too_low_cnt, exp_too_high_cnt;
	पूर्ण;

#घोषणा USB_BUF_SZ 64
	__u8 *usb_buf;				/* buffer क्रम USB exchanges */
	काष्ठा urb *urb[MAX_NURBS];
#अगर IS_ENABLED(CONFIG_INPUT)
	काष्ठा urb *पूर्णांक_urb;
#पूर्ण_अगर

	u8 *image;				/* image being filled */
	u32 image_len;				/* current length of image */
	__u8 last_packet_type;
	__s8 empty_packet;		/* अगर (-1) करोn't check empty packets */
	bool streaming;

	__u8 curr_mode;			/* current camera mode */
	काष्ठा v4l2_pix_क्रमmat pixfmt;	/* current mode parameters */
	__u32 sequence;			/* frame sequence number */

	काष्ठा vb2_queue queue;

	spinlock_t qlock;
	काष्ठा list_head buf_list;

	रुको_queue_head_t wq;		/* रुको queue */
	काष्ठा mutex usb_lock;		/* usb exchange protection */
	पूर्णांक usb_err;			/* USB error - रक्षित by usb_lock */
	u16 pkt_size;			/* ISOC packet size */
#अगर_घोषित CONFIG_PM
	अक्षर frozen;			/* suspend - resume */
#पूर्ण_अगर
	bool present;
	अक्षर memory;			/* memory type (V4L2_MEMORY_xxx) */
	__u8 अगरace;			/* USB पूर्णांकerface number */
	__u8 alt;			/* USB alternate setting */
	पूर्णांक xfer_ep;			/* USB transfer endpoपूर्णांक address */
	u8 audio;			/* presence of audio device */

	/* (*) These variables are proteced by both usb_lock and queue_lock,
	   that is any code setting them is holding *both*, which means that
	   any code getting them needs to hold at least one of them */
पूर्ण;

पूर्णांक gspca_dev_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर काष्ठा sd_desc *sd_desc,
		पूर्णांक dev_size,
		काष्ठा module *module);
पूर्णांक gspca_dev_probe2(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर काष्ठा sd_desc *sd_desc,
		पूर्णांक dev_size,
		काष्ठा module *module);
व्योम gspca_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
व्योम gspca_frame_add(काष्ठा gspca_dev *gspca_dev,
			क्रमागत gspca_packet_type packet_type,
			स्थिर u8 *data,
			पूर्णांक len);
#अगर_घोषित CONFIG_PM
पूर्णांक gspca_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
पूर्णांक gspca_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
#पूर्ण_अगर
पूर्णांक gspca_expo_स्वतःgain(काष्ठा gspca_dev *gspca_dev, पूर्णांक avg_lum,
	पूर्णांक desired_avg_lum, पूर्णांक deadzone, पूर्णांक gain_knee, पूर्णांक exposure_knee);
पूर्णांक gspca_coarse_grained_expo_स्वतःgain(काष्ठा gspca_dev *gspca_dev,
	पूर्णांक avg_lum, पूर्णांक desired_avg_lum, पूर्णांक deadzone);

#पूर्ण_अगर /* GSPCAV2_H */
