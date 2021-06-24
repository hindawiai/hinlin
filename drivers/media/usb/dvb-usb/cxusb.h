<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DVB_USB_CXUSB_H_
#घोषणा _DVB_USB_CXUSB_H_

#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-v4l2.h>

#घोषणा DVB_USB_LOG_PREFIX "cxusb"
#समावेश "dvb-usb.h"

#घोषणा CXUSB_VIDEO_URBS (5)
#घोषणा CXUSB_VIDEO_URB_MAX_SIZE (512 * 1024)

#घोषणा CXUSB_VIDEO_PKT_SIZE 3030
#घोषणा CXUSB_VIDEO_MAX_FRAME_PKTS 346
#घोषणा CXUSB_VIDEO_MAX_FRAME_SIZE (CXUSB_VIDEO_MAX_FRAME_PKTS * \
					CXUSB_VIDEO_PKT_SIZE)

/* usb commands - some of it are guesses, करोn't have a reference yet */
#घोषणा CMD_BLUEBIRD_GPIO_RW 0x05

#घोषणा CMD_I2C_WRITE     0x08
#घोषणा CMD_I2C_READ      0x09

#घोषणा CMD_GPIO_READ     0x0d
#घोषणा CMD_GPIO_WRITE    0x0e
#घोषणा     GPIO_TUNER         0x02

#घोषणा CMD_POWER_OFF     0xdc
#घोषणा CMD_POWER_ON      0xde

#घोषणा CMD_STREAMING_ON  0x36
#घोषणा CMD_STREAMING_OFF 0x37

#घोषणा CMD_AVER_STREAM_ON  0x18
#घोषणा CMD_AVER_STREAM_OFF 0x19

#घोषणा CMD_GET_IR_CODE   0x47

#घोषणा CMD_ANALOG        0x50
#घोषणा CMD_DIGITAL       0x51

#घोषणा CXUSB_BT656_PREAMBLE ((स्थिर u8 *)"\xff\x00\x00")

#घोषणा CXUSB_BT656_FIELD_MASK BIT(6)
#घोषणा CXUSB_BT656_FIELD_1 0
#घोषणा CXUSB_BT656_FIELD_2 BIT(6)

#घोषणा CXUSB_BT656_VBI_MASK BIT(5)
#घोषणा CXUSB_BT656_VBI_ON BIT(5)
#घोषणा CXUSB_BT656_VBI_OFF 0

#घोषणा CXUSB_BT656_SEAV_MASK BIT(4)
#घोषणा CXUSB_BT656_SEAV_EAV BIT(4)
#घोषणा CXUSB_BT656_SEAV_SAV 0

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  80

काष्ठा cxusb_state अणु
	u8 gpio_ग_लिखो_state[3];
	bool gpio_ग_लिखो_refresh[3];
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;

	अचिन्हित अक्षर data[MAX_XFER_SIZE];

	काष्ठा mutex stream_mutex;
	u8 last_lock;
	पूर्णांक (*fe_पढ़ो_status)(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_status *status);
पूर्ण;

क्रमागत cxusb_खोलो_type अणु
	CXUSB_OPEN_INIT,
	CXUSB_OPEN_NONE,
	CXUSB_OPEN_ANALOG,
	CXUSB_OPEN_DIGITAL
पूर्ण;

काष्ठा cxusb_medion_auxbuf अणु
	u8 *buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक paylen;
पूर्ण;

क्रमागत cxusb_bt656_mode अणु
	NEW_FRAME, FIRST_FIELD, SECOND_FIELD
पूर्ण;

क्रमागत cxusb_bt656_भ_शेषe अणु
	START_SEARCH, LINE_SAMPLES, VBI_SAMPLES
पूर्ण;

काष्ठा cxusb_bt656_params अणु
	क्रमागत cxusb_bt656_mode mode;
	क्रमागत cxusb_bt656_भ_शेषe भ_शेषe;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक line;
	अचिन्हित पूर्णांक linesamples;
	u8 *buf;
पूर्ण;

काष्ठा cxusb_medion_dev अणु
	/* has to be the first one */
	काष्ठा cxusb_state state;

	काष्ठा dvb_usb_device *dvbdev;

	क्रमागत cxusb_खोलो_type खोलो_type;
	अचिन्हित पूर्णांक खोलो_ctr;
	काष्ठा mutex खोलो_lock;

#अगर_घोषित CONFIG_DVB_USB_CXUSB_ANALOG
	काष्ठा v4l2_device v4l2dev;
	काष्ठा v4l2_subdev *cx25840;
	काष्ठा v4l2_subdev *tuner;
	काष्ठा v4l2_subdev *tda9887;
	काष्ठा video_device *videodev, *radiodev;
	काष्ठा mutex dev_lock;

	काष्ठा vb2_queue videoqueue;
	u32 input;
	bool stop_streaming;
	u32 width, height;
	u32 field_order;
	काष्ठा cxusb_medion_auxbuf auxbuf;
	v4l2_std_id norm;

	काष्ठा urb *streamurbs[CXUSB_VIDEO_URBS];
	अचिन्हित दीर्घ urbcomplete;
	काष्ठा work_काष्ठा urbwork;
	अचिन्हित पूर्णांक nexturb;

	काष्ठा cxusb_bt656_params bt656;
	काष्ठा cxusb_medion_vbuffer *vbuf;
	__u32 vbuf_sequence;

	काष्ठा list_head buflist;

	काष्ठा completion v4l2_release;
#पूर्ण_अगर
पूर्ण;

काष्ठा cxusb_medion_vbuffer अणु
	काष्ठा vb2_v4l2_buffer vb2;
	काष्ठा list_head list;
पूर्ण;

/* defines क्रम "debug" module parameter */
#घोषणा CXUSB_DBG_RC BIT(0)
#घोषणा CXUSB_DBG_I2C BIT(1)
#घोषणा CXUSB_DBG_MISC BIT(2)
#घोषणा CXUSB_DBG_BT656 BIT(3)
#घोषणा CXUSB_DBG_URB BIT(4)
#घोषणा CXUSB_DBG_OPS BIT(5)
#घोषणा CXUSB_DBG_AUXB BIT(6)

बाह्य पूर्णांक dvb_usb_cxusb_debug;

#घोषणा cxusb_vprपूर्णांकk(dvbdev, lvl, ...) करो अणु				\
		काष्ठा cxusb_medion_dev *_cxdev = (dvbdev)->priv;	\
		अगर (dvb_usb_cxusb_debug & CXUSB_DBG_##lvl)		\
			v4l2_prपूर्णांकk(KERN_DEBUG,			\
				    &_cxdev->v4l2dev, __VA_ARGS__);	\
	पूर्ण जबतक (0)

पूर्णांक cxusb_ctrl_msg(काष्ठा dvb_usb_device *d,
		   u8 cmd, स्थिर u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen);

#अगर_घोषित CONFIG_DVB_USB_CXUSB_ANALOG
पूर्णांक cxusb_medion_analog_init(काष्ठा dvb_usb_device *dvbdev);
पूर्णांक cxusb_medion_रेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev);
व्योम cxusb_medion_unरेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev);
#अन्यथा
अटल अंतरभूत पूर्णांक cxusb_medion_analog_init(काष्ठा dvb_usb_device *dvbdev)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक cxusb_medion_रेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cxusb_medion_unरेजिस्टर_analog(काष्ठा dvb_usb_device *dvbdev)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक cxusb_medion_get(काष्ठा dvb_usb_device *dvbdev,
		     क्रमागत cxusb_खोलो_type खोलो_type);
व्योम cxusb_medion_put(काष्ठा dvb_usb_device *dvbdev);

#पूर्ण_अगर
