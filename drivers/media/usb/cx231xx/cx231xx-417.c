<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Support क्रम a cx23417 mpeg encoder via cx231xx host port.
 *
 *    (c) 2004 Jelle Foks <jelle@foks.us>
 *    (c) 2004 Gerd Knorr <kraxel@bytesex.org>
 *    (c) 2008 Steven Toth <stoth@linuxtv.org>
 *      - CX23885/7/8 support
 *
 *  Includes parts from the ivtv driver( http://ivtv.sourceक्रमge.net/),
 */

#समावेश "cx231xx.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>
#समावेश <media/tuner.h>

#घोषणा CX231xx_FIRM_IMAGE_SIZE 376836
#घोषणा CX231xx_FIRM_IMAGE_NAME "v4l-cx23885-enc.fw"

/* क्रम polaris ITVC */
#घोषणा ITVC_WRITE_सूची          0x03FDFC00
#घोषणा ITVC_READ_सूची            0x0001FC00

#घोषणा  MCI_MEMORY_DATA_BYTE0          0x00
#घोषणा  MCI_MEMORY_DATA_BYTE1          0x08
#घोषणा  MCI_MEMORY_DATA_BYTE2          0x10
#घोषणा  MCI_MEMORY_DATA_BYTE3          0x18

#घोषणा  MCI_MEMORY_ADDRESS_BYTE2       0x20
#घोषणा  MCI_MEMORY_ADDRESS_BYTE1       0x28
#घोषणा  MCI_MEMORY_ADDRESS_BYTE0       0x30

#घोषणा  MCI_REGISTER_DATA_BYTE0        0x40
#घोषणा  MCI_REGISTER_DATA_BYTE1        0x48
#घोषणा  MCI_REGISTER_DATA_BYTE2        0x50
#घोषणा  MCI_REGISTER_DATA_BYTE3        0x58

#घोषणा  MCI_REGISTER_ADDRESS_BYTE0     0x60
#घोषणा  MCI_REGISTER_ADDRESS_BYTE1     0x68

#घोषणा  MCI_REGISTER_MODE              0x70

/* Read and ग_लिखो modes क्रम polaris ITVC */
#घोषणा  MCI_MODE_REGISTER_READ         0x000
#घोषणा  MCI_MODE_REGISTER_WRITE        0x100
#घोषणा  MCI_MODE_MEMORY_READ           0x000
#घोषणा  MCI_MODE_MEMORY_WRITE          0x4000

अटल अचिन्हित पूर्णांक mpeglines = 128;
module_param(mpeglines, पूर्णांक, 0644);
MODULE_PARM_DESC(mpeglines, "number of lines in an MPEG buffer, range 2-32");

अटल अचिन्हित पूर्णांक mpeglinesize = 512;
module_param(mpeglinesize, पूर्णांक, 0644);
MODULE_PARM_DESC(mpeglinesize,
	"number of bytes in each line of an MPEG buffer, range 512-1024");

अटल अचिन्हित पूर्णांक v4l_debug = 1;
module_param(v4l_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(v4l_debug, "enable V4L debug messages");

#घोषणा dprपूर्णांकk(level, fmt, arg...)	\
	करो अणु				\
		अगर (v4l_debug >= level) \
			prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ## arg); \
	पूर्ण जबतक (0)

अटल काष्ठा cx231xx_tvnorm cx231xx_tvnorms[] = अणु
	अणु
		.name      = "NTSC-M",
		.id        = V4L2_STD_NTSC_M,
	पूर्ण, अणु
		.name      = "NTSC-JP",
		.id        = V4L2_STD_NTSC_M_JP,
	पूर्ण, अणु
		.name      = "PAL-BG",
		.id        = V4L2_STD_PAL_BG,
	पूर्ण, अणु
		.name      = "PAL-DK",
		.id        = V4L2_STD_PAL_DK,
	पूर्ण, अणु
		.name      = "PAL-I",
		.id        = V4L2_STD_PAL_I,
	पूर्ण, अणु
		.name      = "PAL-M",
		.id        = V4L2_STD_PAL_M,
	पूर्ण, अणु
		.name      = "PAL-N",
		.id        = V4L2_STD_PAL_N,
	पूर्ण, अणु
		.name      = "PAL-Nc",
		.id        = V4L2_STD_PAL_Nc,
	पूर्ण, अणु
		.name      = "PAL-60",
		.id        = V4L2_STD_PAL_60,
	पूर्ण, अणु
		.name      = "SECAM-L",
		.id        = V4L2_STD_SECAM_L,
	पूर्ण, अणु
		.name      = "SECAM-DK",
		.id        = V4L2_STD_SECAM_DK,
	पूर्ण
पूर्ण;

/* ------------------------------------------------------------------ */

क्रमागत cx231xx_capture_type अणु
	CX231xx_MPEG_CAPTURE,
	CX231xx_RAW_CAPTURE,
	CX231xx_RAW_PASSTHRU_CAPTURE
पूर्ण;

क्रमागत cx231xx_capture_bits अणु
	CX231xx_RAW_BITS_NONE             = 0x00,
	CX231xx_RAW_BITS_YUV_CAPTURE      = 0x01,
	CX231xx_RAW_BITS_PCM_CAPTURE      = 0x02,
	CX231xx_RAW_BITS_VBI_CAPTURE      = 0x04,
	CX231xx_RAW_BITS_PASSTHRU_CAPTURE = 0x08,
	CX231xx_RAW_BITS_TO_HOST_CAPTURE  = 0x10
पूर्ण;

क्रमागत cx231xx_capture_end अणु
	CX231xx_END_AT_GOP, /* stop at the end of gop, generate irq */
	CX231xx_END_NOW, /* stop immediately, no irq */
पूर्ण;

क्रमागत cx231xx_framerate अणु
	CX231xx_FRAMERATE_NTSC_30, /* NTSC: 30fps */
	CX231xx_FRAMERATE_PAL_25   /* PAL: 25fps */
पूर्ण;

क्रमागत cx231xx_stream_port अणु
	CX231xx_OUTPUT_PORT_MEMORY,
	CX231xx_OUTPUT_PORT_STREAMING,
	CX231xx_OUTPUT_PORT_SERIAL
पूर्ण;

क्रमागत cx231xx_data_xfer_status अणु
	CX231xx_MORE_BUFFERS_FOLLOW,
	CX231xx_LAST_BUFFER,
पूर्ण;

क्रमागत cx231xx_picture_mask अणु
	CX231xx_PICTURE_MASK_NONE,
	CX231xx_PICTURE_MASK_I_FRAMES,
	CX231xx_PICTURE_MASK_I_P_FRAMES = 0x3,
	CX231xx_PICTURE_MASK_ALL_FRAMES = 0x7,
पूर्ण;

क्रमागत cx231xx_vbi_mode_bits अणु
	CX231xx_VBI_BITS_SLICED,
	CX231xx_VBI_BITS_RAW,
पूर्ण;

क्रमागत cx231xx_vbi_insertion_bits अणु
	CX231xx_VBI_BITS_INSERT_IN_XTENSION_USR_DATA,
	CX231xx_VBI_BITS_INSERT_IN_PRIVATE_PACKETS = 0x1 << 1,
	CX231xx_VBI_BITS_SEPARATE_STREAM = 0x2 << 1,
	CX231xx_VBI_BITS_SEPARATE_STREAM_USR_DATA = 0x4 << 1,
	CX231xx_VBI_BITS_SEPARATE_STREAM_PRV_DATA = 0x5 << 1,
पूर्ण;

क्रमागत cx231xx_dma_unit अणु
	CX231xx_DMA_BYTES,
	CX231xx_DMA_FRAMES,
पूर्ण;

क्रमागत cx231xx_dma_transfer_status_bits अणु
	CX231xx_DMA_TRANSFER_BITS_DONE = 0x01,
	CX231xx_DMA_TRANSFER_BITS_ERROR = 0x04,
	CX231xx_DMA_TRANSFER_BITS_LL_ERROR = 0x10,
पूर्ण;

क्रमागत cx231xx_छोड़ो अणु
	CX231xx_PAUSE_ENCODING,
	CX231xx_RESUME_ENCODING,
पूर्ण;

क्रमागत cx231xx_copyright अणु
	CX231xx_COPYRIGHT_OFF,
	CX231xx_COPYRIGHT_ON,
पूर्ण;

क्रमागत cx231xx_notअगरication_type अणु
	CX231xx_NOTIFICATION_REFRESH,
पूर्ण;

क्रमागत cx231xx_notअगरication_status अणु
	CX231xx_NOTIFICATION_OFF,
	CX231xx_NOTIFICATION_ON,
पूर्ण;

क्रमागत cx231xx_notअगरication_mailbox अणु
	CX231xx_NOTIFICATION_NO_MAILBOX = -1,
पूर्ण;

क्रमागत cx231xx_field1_lines अणु
	CX231xx_FIELD1_SAA7114 = 0x00EF, /* 239 */
	CX231xx_FIELD1_SAA7115 = 0x00F0, /* 240 */
	CX231xx_FIELD1_MICRONAS = 0x0105, /* 261 */
पूर्ण;

क्रमागत cx231xx_field2_lines अणु
	CX231xx_FIELD2_SAA7114 = 0x00EF, /* 239 */
	CX231xx_FIELD2_SAA7115 = 0x00F0, /* 240 */
	CX231xx_FIELD2_MICRONAS = 0x0106, /* 262 */
पूर्ण;

क्रमागत cx231xx_custom_data_type अणु
	CX231xx_CUSTOM_EXTENSION_USR_DATA,
	CX231xx_CUSTOM_PRIVATE_PACKET,
पूर्ण;

क्रमागत cx231xx_mute अणु
	CX231xx_UNMUTE,
	CX231xx_MUTE,
पूर्ण;

क्रमागत cx231xx_mute_video_mask अणु
	CX231xx_MUTE_VIDEO_V_MASK = 0x0000FF00,
	CX231xx_MUTE_VIDEO_U_MASK = 0x00FF0000,
	CX231xx_MUTE_VIDEO_Y_MASK = 0xFF000000,
पूर्ण;

क्रमागत cx231xx_mute_video_shअगरt अणु
	CX231xx_MUTE_VIDEO_V_SHIFT = 8,
	CX231xx_MUTE_VIDEO_U_SHIFT = 16,
	CX231xx_MUTE_VIDEO_Y_SHIFT = 24,
पूर्ण;

/* defines below are from ivtv-driver.h */
#घोषणा IVTV_CMD_HW_BLOCKS_RST 0xFFFFFFFF

/* Firmware API commands */
#घोषणा IVTV_API_STD_TIMEOUT 500

/* Registers */
/* IVTV_REG_OFFSET */
#घोषणा IVTV_REG_ENC_SDRAM_REFRESH (0x07F8)
#घोषणा IVTV_REG_ENC_SDRAM_PRECHARGE (0x07FC)
#घोषणा IVTV_REG_SPU (0x9050)
#घोषणा IVTV_REG_HW_BLOCKS (0x9054)
#घोषणा IVTV_REG_VPU (0x9058)
#घोषणा IVTV_REG_APU (0xA064)

/*
 * Bit definitions क्रम MC417_RWD and MC417_OEN रेजिस्टरs
 *
 * bits 31-16
 *+-----------+
 *| Reserved  |
 *|+-----------+
 *|  bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
 *|+-------+-------+-------+-------+-------+-------+-------+-------+
 *|| MIWR# | MIRD# | MICS# |MIRDY# |MIADDR3|MIADDR2|MIADDR1|MIADDR0|
 *|+-------+-------+-------+-------+-------+-------+-------+-------+
 *| bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
 *|+-------+-------+-------+-------+-------+-------+-------+-------+
 *||MIDATA7|MIDATA6|MIDATA5|MIDATA4|MIDATA3|MIDATA2|MIDATA1|MIDATA0|
 *|+-------+-------+-------+-------+-------+-------+-------+-------+
 */
#घोषणा MC417_MIWR	0x8000
#घोषणा MC417_MIRD	0x4000
#घोषणा MC417_MICS	0x2000
#घोषणा MC417_MIRDY	0x1000
#घोषणा MC417_MIADDR	0x0F00
#घोषणा MC417_MIDATA	0x00FF


/* Bit definitions क्रम MC417_CTL रेजिस्टर ****
 *bits 31-6   bits 5-4   bit 3    bits 2-1       Bit 0
 *+--------+-------------+--------+--------------+------------+
 *|Reserved|MC417_SPD_CTL|Reserved|MC417_GPIO_SEL|UART_GPIO_EN|
 *+--------+-------------+--------+--------------+------------+
 */
#घोषणा MC417_SPD_CTL(x)	(((x) << 4) & 0x00000030)
#घोषणा MC417_GPIO_SEL(x)	(((x) << 1) & 0x00000006)
#घोषणा MC417_UART_GPIO_EN	0x00000001

/* Values क्रम speed control */
#घोषणा MC417_SPD_CTL_SLOW	0x1
#घोषणा MC417_SPD_CTL_MEDIUM	0x0
#घोषणा MC417_SPD_CTL_FAST	0x3     /* b'1x, but we use b'11 */

/* Values क्रम GPIO select */
#घोषणा MC417_GPIO_SEL_GPIO3	0x3
#घोषणा MC417_GPIO_SEL_GPIO2	0x2
#घोषणा MC417_GPIO_SEL_GPIO1	0x1
#घोषणा MC417_GPIO_SEL_GPIO0	0x0


#घोषणा CX23417_GPIO_MASK 0xFC0003FF

अटल पूर्णांक set_itvc_reg(काष्ठा cx231xx *dev, u32 gpio_direction, u32 value)
अणु
	पूर्णांक status = 0;
	u32 _gpio_direction = 0;

	_gpio_direction = _gpio_direction & CX23417_GPIO_MASK;
	_gpio_direction = _gpio_direction | gpio_direction;
	status = cx231xx_send_gpio_cmd(dev, _gpio_direction,
			 (u8 *)&value, 4, 0, 0);
	वापस status;
पूर्ण

अटल पूर्णांक get_itvc_reg(काष्ठा cx231xx *dev, u32 gpio_direction, u32 *val_ptr)
अणु
	पूर्णांक status = 0;
	u32 _gpio_direction = 0;

	_gpio_direction = _gpio_direction & CX23417_GPIO_MASK;
	_gpio_direction = _gpio_direction | gpio_direction;

	status = cx231xx_send_gpio_cmd(dev, _gpio_direction,
		 (u8 *)val_ptr, 4, 0, 1);
	वापस status;
पूर्ण

अटल पूर्णांक रुको_क्रम_mci_complete(काष्ठा cx231xx *dev)
अणु
	u32 gpio;
	u32 gpio_direction = 0;
	u8 count = 0;
	get_itvc_reg(dev, gpio_direction, &gpio);

	जबतक (!(gpio&0x020000)) अणु
		msleep(10);

		get_itvc_reg(dev, gpio_direction, &gpio);

		अगर (count++ > 100) अणु
			dprपूर्णांकk(3, "ERROR: Timeout - gpio=%x\n", gpio);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mc417_रेजिस्टर_ग_लिखो(काष्ठा cx231xx *dev, u16 address, u32 value)
अणु
	u32 temp;
	पूर्णांक status = 0;

	temp = 0x82 | MCI_REGISTER_DATA_BYTE0 | ((value & 0x000000FF) << 8);
	temp = temp << 10;
	status = set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	अगर (status < 0)
		वापस status;
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 1;*/
	temp = 0x82 | MCI_REGISTER_DATA_BYTE1 | (value & 0x0000FF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 2;*/
	temp = 0x82 | MCI_REGISTER_DATA_BYTE2 | ((value & 0x00FF0000) >> 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 3;*/
	temp = 0x82 | MCI_REGISTER_DATA_BYTE3 | ((value & 0xFF000000) >> 16);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो address byte 0;*/
	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE0 | ((address & 0x000000FF) << 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो address byte 1;*/
	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE1 | (address & 0x0000FF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*Write that the mode is ग_लिखो.*/
	temp = 0x82 | MCI_REGISTER_MODE | MCI_MODE_REGISTER_WRITE;
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	वापस रुको_क्रम_mci_complete(dev);
पूर्ण

अटल पूर्णांक mc417_रेजिस्टर_पढ़ो(काष्ठा cx231xx *dev, u16 address, u32 *value)
अणु
	/*ग_लिखो address byte 0;*/
	u32 temp;
	u32 वापस_value = 0;
	पूर्णांक ret = 0;

	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | ((0x05) << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो address byte 1;*/
	temp = 0x82 | MCI_REGISTER_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | ((0x05) << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो that the mode is पढ़ो;*/
	temp = 0x82 | MCI_REGISTER_MODE | MCI_MODE_REGISTER_READ;
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | ((0x05) << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*रुको क्रम the MIRDY line to be निश्चितed ,
	संकेतling that the पढ़ो is करोne;*/
	ret = रुको_क्रम_mci_complete(dev);

	/*चयन the DATA- GPIO to input mode;*/

	/*Read data byte 0;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE0) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE0) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) >> 18);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/* Read data byte 1;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE1) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE1) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);

	वापस_value |= ((temp & 0x03FC0000) >> 10);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/*Read data byte 2;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE2) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE2) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) >> 2);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/*Read data byte 3;*/
	temp = (0x82 | MCI_REGISTER_DATA_BYTE3) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_REGISTER_DATA_BYTE3) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) << 6);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	*value  = वापस_value;
	वापस ret;
पूर्ण

अटल पूर्णांक mc417_memory_ग_लिखो(काष्ठा cx231xx *dev, u32 address, u32 value)
अणु
	/*ग_लिखो data byte 0;*/

	u32 temp;
	पूर्णांक ret = 0;

	temp = 0x82 | MCI_MEMORY_DATA_BYTE0 | ((value & 0x000000FF) << 8);
	temp = temp << 10;
	ret = set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	अगर (ret < 0)
		वापस ret;
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 1;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE1 | (value & 0x0000FF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 2;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE2 | ((value & 0x00FF0000) >> 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो data byte 3;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE3 | ((value & 0xFF000000) >> 16);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/* ग_लिखो address byte 2;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE2 | MCI_MODE_MEMORY_WRITE |
		((address & 0x003F0000) >> 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/* ग_लिखो address byte 1;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/* ग_लिखो address byte 0;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*रुको क्रम MIRDY line;*/
	रुको_क्रम_mci_complete(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mc417_memory_पढ़ो(काष्ठा cx231xx *dev, u32 address, u32 *value)
अणु
	u32 temp = 0;
	u32 वापस_value = 0;
	पूर्णांक ret = 0;

	/*ग_लिखो address byte 2;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE2 | MCI_MODE_MEMORY_READ |
		((address & 0x003F0000) >> 8);
	temp = temp << 10;
	ret = set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	अगर (ret < 0)
		वापस ret;
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो address byte 1*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*ग_लिखो address byte 0*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);
	temp = temp | (0x05 << 10);
	set_itvc_reg(dev, ITVC_WRITE_सूची, temp);

	/*Wait क्रम MIRDY line*/
	ret = रुको_क्रम_mci_complete(dev);


	/*Read data byte 3;*/
	temp = (0x82 | MCI_MEMORY_DATA_BYTE3) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_MEMORY_DATA_BYTE3) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) << 6);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/*Read data byte 2;*/
	temp = (0x82 | MCI_MEMORY_DATA_BYTE2) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_MEMORY_DATA_BYTE2) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) >> 2);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/* Read data byte 1;*/
	temp = (0x82 | MCI_MEMORY_DATA_BYTE1) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_MEMORY_DATA_BYTE1) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) >> 10);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	/*Read data byte 0;*/
	temp = (0x82 | MCI_MEMORY_DATA_BYTE0) << 10;
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	temp = ((0x81 | MCI_MEMORY_DATA_BYTE0) << 10);
	set_itvc_reg(dev, ITVC_READ_सूची, temp);
	get_itvc_reg(dev, ITVC_READ_सूची, &temp);
	वापस_value |= ((temp & 0x03FC0000) >> 18);
	set_itvc_reg(dev, ITVC_READ_सूची, (0x87 << 10));

	*value  = वापस_value;
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------ */

/* MPEG encoder API */
अटल अक्षर *cmd_to_str(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल CX2341X_ENC_PING_FW:
		वापस "PING_FW";
	हाल CX2341X_ENC_START_CAPTURE:
		वापस "START_CAPTURE";
	हाल CX2341X_ENC_STOP_CAPTURE:
		वापस "STOP_CAPTURE";
	हाल CX2341X_ENC_SET_AUDIO_ID:
		वापस "SET_AUDIO_ID";
	हाल CX2341X_ENC_SET_VIDEO_ID:
		वापस "SET_VIDEO_ID";
	हाल CX2341X_ENC_SET_PCR_ID:
		वापस "SET_PCR_PID";
	हाल CX2341X_ENC_SET_FRAME_RATE:
		वापस "SET_FRAME_RATE";
	हाल CX2341X_ENC_SET_FRAME_SIZE:
		वापस "SET_FRAME_SIZE";
	हाल CX2341X_ENC_SET_BIT_RATE:
		वापस "SET_BIT_RATE";
	हाल CX2341X_ENC_SET_GOP_PROPERTIES:
		वापस "SET_GOP_PROPERTIES";
	हाल CX2341X_ENC_SET_ASPECT_RATIO:
		वापस "SET_ASPECT_RATIO";
	हाल CX2341X_ENC_SET_DNR_FILTER_MODE:
		वापस "SET_DNR_FILTER_PROPS";
	हाल CX2341X_ENC_SET_DNR_FILTER_PROPS:
		वापस "SET_DNR_FILTER_PROPS";
	हाल CX2341X_ENC_SET_CORING_LEVELS:
		वापस "SET_CORING_LEVELS";
	हाल CX2341X_ENC_SET_SPATIAL_FILTER_TYPE:
		वापस "SET_SPATIAL_FILTER_TYPE";
	हाल CX2341X_ENC_SET_VBI_LINE:
		वापस "SET_VBI_LINE";
	हाल CX2341X_ENC_SET_STREAM_TYPE:
		वापस "SET_STREAM_TYPE";
	हाल CX2341X_ENC_SET_OUTPUT_PORT:
		वापस "SET_OUTPUT_PORT";
	हाल CX2341X_ENC_SET_AUDIO_PROPERTIES:
		वापस "SET_AUDIO_PROPERTIES";
	हाल CX2341X_ENC_HALT_FW:
		वापस "HALT_FW";
	हाल CX2341X_ENC_GET_VERSION:
		वापस "GET_VERSION";
	हाल CX2341X_ENC_SET_GOP_CLOSURE:
		वापस "SET_GOP_CLOSURE";
	हाल CX2341X_ENC_GET_SEQ_END:
		वापस "GET_SEQ_END";
	हाल CX2341X_ENC_SET_PGM_INDEX_INFO:
		वापस "SET_PGM_INDEX_INFO";
	हाल CX2341X_ENC_SET_VBI_CONFIG:
		वापस "SET_VBI_CONFIG";
	हाल CX2341X_ENC_SET_DMA_BLOCK_SIZE:
		वापस "SET_DMA_BLOCK_SIZE";
	हाल CX2341X_ENC_GET_PREV_DMA_INFO_MB_10:
		वापस "GET_PREV_DMA_INFO_MB_10";
	हाल CX2341X_ENC_GET_PREV_DMA_INFO_MB_9:
		वापस "GET_PREV_DMA_INFO_MB_9";
	हाल CX2341X_ENC_SCHED_DMA_TO_HOST:
		वापस "SCHED_DMA_TO_HOST";
	हाल CX2341X_ENC_INITIALIZE_INPUT:
		वापस "INITIALIZE_INPUT";
	हाल CX2341X_ENC_SET_FRAME_DROP_RATE:
		वापस "SET_FRAME_DROP_RATE";
	हाल CX2341X_ENC_PAUSE_ENCODER:
		वापस "PAUSE_ENCODER";
	हाल CX2341X_ENC_REFRESH_INPUT:
		वापस "REFRESH_INPUT";
	हाल CX2341X_ENC_SET_COPYRIGHT:
		वापस "SET_COPYRIGHT";
	हाल CX2341X_ENC_SET_EVENT_NOTIFICATION:
		वापस "SET_EVENT_NOTIFICATION";
	हाल CX2341X_ENC_SET_NUM_VSYNC_LINES:
		वापस "SET_NUM_VSYNC_LINES";
	हाल CX2341X_ENC_SET_PLACEHOLDER:
		वापस "SET_PLACEHOLDER";
	हाल CX2341X_ENC_MUTE_VIDEO:
		वापस "MUTE_VIDEO";
	हाल CX2341X_ENC_MUTE_AUDIO:
		वापस "MUTE_AUDIO";
	हाल CX2341X_ENC_MISC:
		वापस "MISC";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल पूर्णांक cx231xx_mbox_func(व्योम *priv, u32 command, पूर्णांक in, पूर्णांक out,
			     u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	काष्ठा cx231xx *dev = priv;
	अचिन्हित दीर्घ समयout;
	u32 value, flag, retval = 0;
	पूर्णांक i;

	dprपूर्णांकk(3, "%s: command(0x%X) = %s\n", __func__, command,
		cmd_to_str(command));

	/* this may not be 100% safe अगर we can't पढ़ो any memory location
	   without side effects */
	mc417_memory_पढ़ो(dev, dev->cx23417_mailbox - 4, &value);
	अगर (value != 0x12345678) अणु
		dprपूर्णांकk(3, "Firmware and/or mailbox pointer not initialized or corrupted, signature = 0x%x, cmd = %s\n",
			value, cmd_to_str(command));
		वापस -EIO;
	पूर्ण

	/* This पढ़ो looks at 32 bits, but flag is only 8 bits.
	 * Seems we also bail अगर CMD or TIMEOUT bytes are set???
	 */
	mc417_memory_पढ़ो(dev, dev->cx23417_mailbox, &flag);
	अगर (flag) अणु
		dprपूर्णांकk(3, "ERROR: Mailbox appears to be in use (%x), cmd = %s\n",
				flag, cmd_to_str(command));
		वापस -EBUSY;
	पूर्ण

	flag |= 1; /* tell 'em we're working on it */
	mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox, flag);

	/* ग_लिखो command + args + fill reमुख्यing with zeros */
	/* command code */
	mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox + 1, command);
	mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox + 3,
		IVTV_API_STD_TIMEOUT); /* समयout */
	क्रम (i = 0; i < in; i++) अणु
		mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox + 4 + i, data[i]);
		dprपूर्णांकk(3, "API Input %d = %d\n", i, data[i]);
	पूर्ण
	क्रम (; i < CX2341X_MBOX_MAX_DATA; i++)
		mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox + 4 + i, 0);

	flag |= 3; /* tell 'em we're करोne writing */
	mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox, flag);

	/* रुको क्रम firmware to handle the API command */
	समयout = jअगरfies + msecs_to_jअगरfies(10);
	क्रम (;;) अणु
		mc417_memory_पढ़ो(dev, dev->cx23417_mailbox, &flag);
		अगर (0 != (flag & 4))
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dprपूर्णांकk(3, "ERROR: API Mailbox timeout\n");
			वापस -EIO;
		पूर्ण
		udelay(10);
	पूर्ण

	/* पढ़ो output values */
	क्रम (i = 0; i < out; i++) अणु
		mc417_memory_पढ़ो(dev, dev->cx23417_mailbox + 4 + i, data + i);
		dprपूर्णांकk(3, "API Output %d = %d\n", i, data[i]);
	पूर्ण

	mc417_memory_पढ़ो(dev, dev->cx23417_mailbox + 2, &retval);
	dprपूर्णांकk(3, "API result = %d\n", retval);

	flag = 0;
	mc417_memory_ग_लिखो(dev, dev->cx23417_mailbox, flag);

	वापस 0;
पूर्ण

/* We करोn't need to call the API often, so using just one
 * mailbox will probably suffice
 */
अटल पूर्णांक cx231xx_api_cmd(काष्ठा cx231xx *dev, u32 command,
		u32 inअ_दोnt, u32 outअ_दोnt, ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची vargs;
	पूर्णांक i, err;

	dprपूर्णांकk(3, "%s() cmds = 0x%08x\n", __func__, command);

	बहु_शुरू(vargs, outअ_दोnt);
	क्रम (i = 0; i < inअ_दोnt; i++)
		data[i] = बहु_तर्क(vargs, पूर्णांक);

	err = cx231xx_mbox_func(dev, command, inअ_दोnt, outअ_दोnt, data);
	क्रम (i = 0; i < outअ_दोnt; i++) अणु
		पूर्णांक *vptr = बहु_तर्क(vargs, पूर्णांक *);
		*vptr = data[i];
	पूर्ण
	बहु_पूर्ण(vargs);

	वापस err;
पूर्ण


अटल पूर्णांक cx231xx_find_mailbox(काष्ठा cx231xx *dev)
अणु
	u32 signature[4] = अणु
		0x12345678, 0x34567812, 0x56781234, 0x78123456
	पूर्ण;
	पूर्णांक signaturecnt = 0;
	u32 value;
	पूर्णांक i;
	पूर्णांक ret = 0;

	dprपूर्णांकk(2, "%s()\n", __func__);

	क्रम (i = 0; i < 0x100; i++) अणु/*CX231xx_FIRM_IMAGE_SIZE*/
		ret = mc417_memory_पढ़ो(dev, i, &value);
		अगर (ret < 0)
			वापस ret;
		अगर (value == signature[signaturecnt])
			signaturecnt++;
		अन्यथा
			signaturecnt = 0;
		अगर (4 == signaturecnt) अणु
			dprपूर्णांकk(1, "Mailbox signature found at 0x%x\n", i + 1);
			वापस i + 1;
		पूर्ण
	पूर्ण
	dprपूर्णांकk(3, "Mailbox signature values not found!\n");
	वापस -EIO;
पूर्ण

अटल व्योम mci_ग_लिखो_memory_to_gpio(काष्ठा cx231xx *dev, u32 address, u32 value,
		u32 *p_fw_image)
अणु
	u32 temp = 0;
	पूर्णांक i = 0;

	temp = 0x82 | MCI_MEMORY_DATA_BYTE0 | ((value & 0x000000FF) << 8);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/*ग_लिखो data byte 1;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE1 | (value & 0x0000FF00);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/*ग_लिखो data byte 2;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE2 | ((value & 0x00FF0000) >> 8);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/*ग_लिखो data byte 3;*/
	temp = 0x82 | MCI_MEMORY_DATA_BYTE3 | ((value & 0xFF000000) >> 16);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/* ग_लिखो address byte 2;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE2 | MCI_MODE_MEMORY_WRITE |
		((address & 0x003F0000) >> 8);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/* ग_लिखो address byte 1;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE1 | (address & 0xFF00);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	/* ग_लिखो address byte 0;*/
	temp = 0x82 | MCI_MEMORY_ADDRESS_BYTE0 | ((address & 0x00FF) << 8);
	temp = temp << 10;
	*p_fw_image = temp;
	p_fw_image++;
	temp = temp | (0x05 << 10);
	*p_fw_image = temp;
	p_fw_image++;

	क्रम (i = 0; i < 6; i++) अणु
		*p_fw_image = 0xFFFFFFFF;
		p_fw_image++;
	पूर्ण
पूर्ण


अटल पूर्णांक cx231xx_load_firmware(काष्ठा cx231xx *dev)
अणु
	अटल स्थिर अचिन्हित अक्षर magic[8] = अणु
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	पूर्ण;
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक i, retval = 0;
	u32 value = 0;
	u32 gpio_output = 0;
	/*u32 checksum = 0;*/
	/*u32 *dataptr;*/
	u32 transfer_size = 0;
	u32 fw_data = 0;
	u32 address = 0;
	/*u32 current_fw[800];*/
	u32 *p_current_fw, *p_fw;
	u32 *p_fw_data;
	पूर्णांक frame = 0;
	u16 _buffer_size = 4096;
	u8 *p_buffer;

	p_current_fw = vदो_स्मृति(1884180 * 4);
	p_fw = p_current_fw;
	अगर (p_current_fw == शून्य) अणु
		dprपूर्णांकk(2, "FAIL!!!\n");
		वापस -ENOMEM;
	पूर्ण

	p_buffer = vदो_स्मृति(4096);
	अगर (p_buffer == शून्य) अणु
		dprपूर्णांकk(2, "FAIL!!!\n");
		vमुक्त(p_current_fw);
		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(2, "%s()\n", __func__);

	/* Save GPIO settings beक्रमe reset of APU */
	retval |= mc417_memory_पढ़ो(dev, 0x9020, &gpio_output);
	retval |= mc417_memory_पढ़ो(dev, 0x900C, &value);

	retval  = mc417_रेजिस्टर_ग_लिखो(dev,
		IVTV_REG_VPU, 0xFFFFFFED);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev,
		IVTV_REG_HW_BLOCKS, IVTV_CMD_HW_BLOCKS_RST);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev,
		IVTV_REG_ENC_SDRAM_REFRESH, 0x80000800);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev,
		IVTV_REG_ENC_SDRAM_PRECHARGE, 0x1A);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev,
		IVTV_REG_APU, 0);

	अगर (retval != 0) अणु
		dev_err(dev->dev,
			"%s: Error with mc417_register_write\n", __func__);
		vमुक्त(p_current_fw);
		vमुक्त(p_buffer);
		वापस retval;
	पूर्ण

	retval = request_firmware(&firmware, CX231xx_FIRM_IMAGE_NAME,
				  dev->dev);

	अगर (retval != 0) अणु
		dev_err(dev->dev,
			"ERROR: Hotplug firmware request failed (%s).\n",
			CX231xx_FIRM_IMAGE_NAME);
		dev_err(dev->dev,
			"Please fix your hotplug setup, the board will not work without firmware loaded!\n");
		vमुक्त(p_current_fw);
		vमुक्त(p_buffer);
		वापस retval;
	पूर्ण

	अगर (firmware->size != CX231xx_FIRM_IMAGE_SIZE) अणु
		dev_err(dev->dev,
			"ERROR: Firmware size mismatch (have %zd, expected %d)\n",
			firmware->size, CX231xx_FIRM_IMAGE_SIZE);
		release_firmware(firmware);
		vमुक्त(p_current_fw);
		vमुक्त(p_buffer);
		वापस -EINVAL;
	पूर्ण

	अगर (0 != स_भेद(firmware->data, magic, 8)) अणु
		dev_err(dev->dev,
			"ERROR: Firmware magic mismatch, wrong file?\n");
		release_firmware(firmware);
		vमुक्त(p_current_fw);
		vमुक्त(p_buffer);
		वापस -EINVAL;
	पूर्ण

	initGPIO(dev);

	/* transfer to the chip */
	dprपूर्णांकk(2, "Loading firmware to GPIO...\n");
	p_fw_data = (u32 *)firmware->data;
	dprपूर्णांकk(2, "firmware->size=%zd\n", firmware->size);
	क्रम (transfer_size = 0; transfer_size < firmware->size;
		 transfer_size += 4) अणु
		fw_data = *p_fw_data;

		mci_ग_लिखो_memory_to_gpio(dev, address, fw_data, p_current_fw);
		address = address + 1;
		p_current_fw += 20;
		p_fw_data += 1;
	पूर्ण

	/*करोwnload the firmware by ep5-out*/

	क्रम (frame = 0; frame < (पूर्णांक)(CX231xx_FIRM_IMAGE_SIZE*20/_buffer_size);
	     frame++) अणु
		क्रम (i = 0; i < _buffer_size; i++) अणु
			*(p_buffer + i) = (u8)(*(p_fw + (frame * 128 * 8 + (i / 4))) & 0x000000FF);
			i++;
			*(p_buffer + i) = (u8)((*(p_fw + (frame * 128 * 8 + (i / 4))) & 0x0000FF00) >> 8);
			i++;
			*(p_buffer + i) = (u8)((*(p_fw + (frame * 128 * 8 + (i / 4))) & 0x00FF0000) >> 16);
			i++;
			*(p_buffer + i) = (u8)((*(p_fw + (frame * 128 * 8 + (i / 4))) & 0xFF000000) >> 24);
		पूर्ण
		cx231xx_ep5_bulkout(dev, p_buffer, _buffer_size);
	पूर्ण

	p_current_fw = p_fw;
	vमुक्त(p_current_fw);
	p_current_fw = शून्य;
	vमुक्त(p_buffer);
	uninitGPIO(dev);
	release_firmware(firmware);
	dprपूर्णांकk(1, "Firmware upload successful.\n");

	retval |= mc417_रेजिस्टर_ग_लिखो(dev, IVTV_REG_HW_BLOCKS,
		IVTV_CMD_HW_BLOCKS_RST);
	अगर (retval < 0) अणु
		dev_err(dev->dev,
			"%s: Error with mc417_register_write\n",
			__func__);
		वापस retval;
	पूर्ण
	/* F/W घातer up disturbs the GPIOs, restore state */
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x9020, gpio_output);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x900C, value);

	retval |= mc417_रेजिस्टर_पढ़ो(dev, IVTV_REG_VPU, &value);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, IVTV_REG_VPU, value & 0xFFFFFFE8);

	अगर (retval < 0) अणु
		dev_err(dev->dev,
			"%s: Error with mc417_register_write\n",
			__func__);
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cx231xx_codec_settings(काष्ठा cx231xx *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	/* assign frame size */
	cx231xx_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
				dev->ts1.height, dev->ts1.width);

	dev->mpeg_ctrl_handler.width = dev->ts1.width;
	dev->mpeg_ctrl_handler.height = dev->ts1.height;

	cx2341x_handler_setup(&dev->mpeg_ctrl_handler);

	cx231xx_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 3, 1);
	cx231xx_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 4, 1);
पूर्ण

अटल पूर्णांक cx231xx_initialize_codec(काष्ठा cx231xx *dev)
अणु
	पूर्णांक version;
	पूर्णांक retval;
	u32 i;
	u32 val = 0;

	dprपूर्णांकk(1, "%s()\n", __func__);
	cx231xx_disable656(dev);
	retval = cx231xx_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0); /* ping */
	अगर (retval < 0) अणु
		dprपूर्णांकk(2, "%s: PING OK\n", __func__);
		retval = cx231xx_load_firmware(dev);
		अगर (retval < 0) अणु
			dev_err(dev->dev,
				"%s: f/w load failed\n", __func__);
			वापस retval;
		पूर्ण
		retval = cx231xx_find_mailbox(dev);
		अगर (retval < 0) अणु
			dev_err(dev->dev, "%s: mailbox < 0, error\n",
				__func__);
			वापस retval;
		पूर्ण
		dev->cx23417_mailbox = retval;
		retval = cx231xx_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0);
		अगर (retval < 0) अणु
			dev_err(dev->dev,
				"ERROR: cx23417 firmware ping failed!\n");
			वापस retval;
		पूर्ण
		retval = cx231xx_api_cmd(dev, CX2341X_ENC_GET_VERSION, 0, 1,
			&version);
		अगर (retval < 0) अणु
			dev_err(dev->dev,
				"ERROR: cx23417 firmware get encoder: version failed!\n");
			वापस retval;
		पूर्ण
		dprपूर्णांकk(1, "cx23417 firmware version is 0x%08x\n", version);
		msleep(200);
	पूर्ण

	क्रम (i = 0; i < 1; i++) अणु
		retval = mc417_रेजिस्टर_पढ़ो(dev, 0x20f8, &val);
		dprपूर्णांकk(3, "***before enable656() VIM Capture Lines = %d ***\n",
				 val);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	cx231xx_enable656(dev);

	/* stop mpeg capture */
	cx231xx_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0, 1, 3, 4);

	cx231xx_codec_settings(dev);
	msleep(60);

/*	cx231xx_api_cmd(dev, CX2341X_ENC_SET_NUM_VSYNC_LINES, 2, 0,
		CX231xx_FIELD1_SAA7115, CX231xx_FIELD2_SAA7115);
	cx231xx_api_cmd(dev, CX2341X_ENC_SET_PLACEHOLDER, 12, 0,
		CX231xx_CUSTOM_EXTENSION_USR_DATA, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0);
*/

#अगर 0
	/* TODO */
	u32 data[7];

	/* Setup to capture VBI */
	data[0] = 0x0001BD00;
	data[1] = 1;          /* frames per पूर्णांकerrupt */
	data[2] = 4;          /* total bufs */
	data[3] = 0x91559155; /* start codes */
	data[4] = 0x206080C0; /* stop codes */
	data[5] = 6;          /* lines */
	data[6] = 64;         /* BPL */

	cx231xx_api_cmd(dev, CX2341X_ENC_SET_VBI_CONFIG, 7, 0, data[0], data[1],
		data[2], data[3], data[4], data[5], data[6]);

	क्रम (i = 2; i <= 24; i++) अणु
		पूर्णांक valid;

		valid = ((i >= 19) && (i <= 21));
		cx231xx_api_cmd(dev, CX2341X_ENC_SET_VBI_LINE, 5, 0, i,
				valid, 0 , 0, 0);
		cx231xx_api_cmd(dev, CX2341X_ENC_SET_VBI_LINE, 5, 0,
				i | 0x80000000, valid, 0, 0, 0);
	पूर्ण
#पूर्ण_अगर
/*	cx231xx_api_cmd(dev, CX2341X_ENC_MUTE_AUDIO, 1, 0, CX231xx_UNMUTE);
	msleep(60);
*/
	/* initialize the video input */
	retval = cx231xx_api_cmd(dev, CX2341X_ENC_INITIALIZE_INPUT, 0, 0);
	अगर (retval < 0)
		वापस retval;
	msleep(60);

	/* Enable VIP style pixel invalidation so we work with scaled mode */
	mc417_memory_ग_लिखो(dev, 2120, 0x00000080);

	/* start capturing to the host पूर्णांकerface */
	retval = cx231xx_api_cmd(dev, CX2341X_ENC_START_CAPTURE, 2, 0,
		CX231xx_MPEG_CAPTURE, CX231xx_RAW_BITS_NONE);
	अगर (retval < 0)
		वापस retval;
	msleep(10);

	क्रम (i = 0; i < 1; i++) अणु
		mc417_रेजिस्टर_पढ़ो(dev, 0x20f8, &val);
		dprपूर्णांकk(3, "***VIM Capture Lines =%d ***\n", val);
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = mpeglinesize * mpeglines;

	dev->ts1.ts_packet_size  = mpeglinesize;
	dev->ts1.ts_packet_count = mpeglines;

	अगर (vq->num_buffers + *nbuffers < CX231XX_MIN_BUF)
		*nbuffers = CX231XX_MIN_BUF - vq->num_buffers;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = mpeglinesize * mpeglines;

	वापस 0;
पूर्ण

अटल व्योम buffer_copy(काष्ठा cx231xx *dev, अक्षर *data, पूर्णांक len, काष्ठा urb *urb,
		काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	व्योम *vbuf;
	काष्ठा cx231xx_buffer *buf;
	u32 tail_data = 0;
	अक्षर *p_data;

	अगर (dma_q->mpeg_buffer_करोne == 0) अणु
		अगर (list_empty(&dma_q->active))
			वापस;

		buf = list_entry(dma_q->active.next,
				काष्ठा cx231xx_buffer, list);
		dev->video_mode.isoc_ctl.buf = buf;
		dma_q->mpeg_buffer_करोne = 1;
	पूर्ण
	/* Fill buffer */
	buf = dev->video_mode.isoc_ctl.buf;
	vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	अगर ((dma_q->mpeg_buffer_completed+len) <
			mpeglines*mpeglinesize) अणु
		अगर (dma_q->add_ps_package_head ==
				CX231XX_NEED_ADD_PS_PACKAGE_HEAD) अणु
			स_नकल(vbuf+dma_q->mpeg_buffer_completed,
					dma_q->ps_head, 3);
			dma_q->mpeg_buffer_completed =
				dma_q->mpeg_buffer_completed + 3;
			dma_q->add_ps_package_head =
				CX231XX_NONEED_PS_PACKAGE_HEAD;
		पूर्ण
		स_नकल(vbuf+dma_q->mpeg_buffer_completed, data, len);
		dma_q->mpeg_buffer_completed =
			dma_q->mpeg_buffer_completed + len;
	पूर्ण अन्यथा अणु
		dma_q->mpeg_buffer_करोne = 0;

		tail_data =
			mpeglines*mpeglinesize - dma_q->mpeg_buffer_completed;
		स_नकल(vbuf+dma_q->mpeg_buffer_completed,
				data, tail_data);

		buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
		buf->vb.sequence = dma_q->sequence++;
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		dma_q->mpeg_buffer_completed = 0;

		अगर (len - tail_data > 0) अणु
			p_data = data + tail_data;
			dma_q->left_data_count = len - tail_data;
			स_नकल(dma_q->p_left_data,
					p_data, len - tail_data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम buffer_filled(अक्षर *data, पूर्णांक len, काष्ठा urb *urb,
		काष्ठा cx231xx_dmaqueue *dma_q)
अणु
	व्योम *vbuf;
	काष्ठा cx231xx_buffer *buf;

	अगर (list_empty(&dma_q->active))
		वापस;

	buf = list_entry(dma_q->active.next, काष्ठा cx231xx_buffer, list);

	/* Fill buffer */
	vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	स_नकल(vbuf, data, len);
	buf->vb.sequence = dma_q->sequence++;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	list_del(&buf->list);
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

अटल पूर्णांक cx231xx_isoc_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	अचिन्हित अक्षर *p_buffer;
	u32 buffer_size = 0;
	u32 i = 0;

	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		अगर (dma_q->left_data_count > 0) अणु
			buffer_copy(dev, dma_q->p_left_data,
				    dma_q->left_data_count, urb, dma_q);
			dma_q->mpeg_buffer_completed = dma_q->left_data_count;
			dma_q->left_data_count = 0;
		पूर्ण

		p_buffer = urb->transfer_buffer +
				urb->iso_frame_desc[i].offset;
		buffer_size = urb->iso_frame_desc[i].actual_length;

		अगर (buffer_size > 0)
			buffer_copy(dev, p_buffer, buffer_size, urb, dma_q);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cx231xx_bulk_copy(काष्ठा cx231xx *dev, काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	अचिन्हित अक्षर *p_buffer, *buffer;
	u32 buffer_size = 0;

	p_buffer = urb->transfer_buffer;
	buffer_size = urb->actual_length;

	buffer = kदो_स्मृति(buffer_size, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	स_नकल(buffer, dma_q->ps_head, 3);
	स_नकल(buffer+3, p_buffer, buffer_size-3);
	स_नकल(dma_q->ps_head, p_buffer+buffer_size-3, 3);

	p_buffer = buffer;
	buffer_filled(p_buffer, buffer_size, urb, dma_q);

	kमुक्त(buffer);
	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा cx231xx_buffer *buf =
	    container_of(vb, काष्ठा cx231xx_buffer, vb.vb2_buf);
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा cx231xx *dev,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	काष्ठा cx231xx_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	list_क्रम_each_entry_safe(buf, node, &vidq->active, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	काष्ठा cx231xx_dmaqueue *vidq = &dev->video_mode.vidq;
	पूर्णांक ret = 0;

	vidq->sequence = 0;
	dev->mode_tv = 1;

	cx231xx_set_alt_setting(dev, INDEX_VANC, 1);
	cx231xx_set_gpio_value(dev, 2, 0);

	cx231xx_initialize_codec(dev);

	cx231xx_start_TS1(dev);

	cx231xx_set_alt_setting(dev, INDEX_TS1, 0);
	cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
	अगर (dev->USE_ISO)
		ret = cx231xx_init_isoc(dev, CX231XX_NUM_PACKETS,
					CX231XX_NUM_BUFS,
					dev->ts1_mode.max_pkt_size,
					cx231xx_isoc_copy);
	अन्यथा
		ret = cx231xx_init_bulk(dev, 320, 5,
					dev->ts1_mode.max_pkt_size,
					cx231xx_bulk_copy);
	अगर (ret)
		वापस_all_buffers(dev, VB2_BUF_STATE_QUEUED);

	call_all(dev, video, s_stream, 1);
	वापस ret;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा cx231xx *dev = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ flags;

	call_all(dev, video, s_stream, 0);

	cx231xx_stop_TS1(dev);

	/* करो this beक्रमe setting alternate! */
	अगर (dev->USE_ISO)
		cx231xx_uninit_isoc(dev);
	अन्यथा
		cx231xx_uninit_bulk(dev);
	cx231xx_set_mode(dev, CX231XX_SUSPEND);

	cx231xx_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			CX231xx_END_NOW, CX231xx_MPEG_CAPTURE,
			CX231xx_RAW_BITS_NONE);

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	अगर (dev->USE_ISO)
		dev->video_mode.isoc_ctl.buf = शून्य;
	अन्यथा
		dev->video_mode.bulk_ctl.buf = शून्य;
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
	वापस_all_buffers(dev, VB2_BUF_STATE_ERROR);
पूर्ण

अटल काष्ठा vb2_ops cx231xx_video_qops = अणु
	.queue_setup		= queue_setup,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक vidioc_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	bool is_50hz = dev->encodernorm.id & V4L2_STD_625_50;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	f->numerator = is_50hz ? 54 : 11;
	f->denominator = is_50hz ? 59 : 10;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_selection *s)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	अगर (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (s->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = dev->ts1.width;
		s->r.height = dev->ts1.height;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *fh0, v4l2_std_id *norm)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	*norm = dev->encodernorm.id;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cx231xx_tvnorms); i++)
		अगर (id & cx231xx_tvnorms[i].id)
			अवरोध;
	अगर (i == ARRAY_SIZE(cx231xx_tvnorms))
		वापस -EINVAL;
	dev->encodernorm = cx231xx_tvnorms[i];

	अगर (dev->encodernorm.id & 0xb000) अणु
		dprपूर्णांकk(3, "encodernorm set to NTSC\n");
		dev->norm = V4L2_STD_NTSC;
		dev->ts1.height = 480;
		cx2341x_handler_set_50hz(&dev->mpeg_ctrl_handler, false);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(3, "encodernorm set to PAL\n");
		dev->norm = V4L2_STD_PAL_B;
		dev->ts1.height = 576;
		cx2341x_handler_set_50hz(&dev->mpeg_ctrl_handler, true);
	पूर्ण
	call_all(dev, video, s_std, dev->norm);
	/* करो mode control overrides */
	cx231xx_करो_mode_ctrl_overrides(dev);

	dprपूर्णांकk(3, "exit vidioc_s_std() i=0x%x\n", i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_ctrl(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_control *ctl)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);
	काष्ठा v4l2_subdev *sd;

	dprपूर्णांकk(3, "enter vidioc_s_ctrl()\n");
	/* Update the A/V core */
	v4l2_device_क्रम_each_subdev(sd, &dev->v4l2_dev)
		v4l2_s_ctrl(शून्य, sd->ctrl_handler, ctl);
	dprपूर्णांकk(3, "exit vidioc_s_ctrl()\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index != 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_MPEG;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	dprपूर्णांकk(3, "enter vidioc_g_fmt_vid_cap()\n");
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = mpeglines * mpeglinesize;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.width = dev->ts1.width;
	f->fmt.pix.height = dev->ts1.height;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	dprपूर्णांकk(1, "VIDIOC_G_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	dprपूर्णांकk(3, "exit vidioc_g_fmt_vid_cap()\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	dprपूर्णांकk(3, "enter vidioc_try_fmt_vid_cap()\n");
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = mpeglines * mpeglinesize;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	dprपूर्णांकk(1, "VIDIOC_TRY_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	dprपूर्णांकk(3, "exit vidioc_try_fmt_vid_cap()\n");
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा cx231xx *dev = video_drvdata(file);

	call_all(dev, core, log_status);
	वापस v4l2_ctrl_log_status(file, priv);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mpeg_fops = अणु
	.owner	       = THIS_MODULE,
	.खोलो	       = v4l2_fh_खोलो,
	.release       = vb2_fop_release,
	.पढ़ो	       = vb2_fop_पढ़ो,
	.poll          = vb2_fop_poll,
	.mmap	       = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops mpeg_ioctl_ops = अणु
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_g_tuner          = cx231xx_g_tuner,
	.vidioc_s_tuner          = cx231xx_s_tuner,
	.vidioc_g_frequency      = cx231xx_g_frequency,
	.vidioc_s_frequency      = cx231xx_s_frequency,
	.vidioc_क्रमागत_input	 = cx231xx_क्रमागत_input,
	.vidioc_g_input		 = cx231xx_g_input,
	.vidioc_s_input		 = cx231xx_s_input,
	.vidioc_s_ctrl		 = vidioc_s_ctrl,
	.vidioc_g_pixelaspect	 = vidioc_g_pixelaspect,
	.vidioc_g_selection	 = vidioc_g_selection,
	.vidioc_querycap	 = cx231xx_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	 = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	 = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	 = vidioc_try_fmt_vid_cap,
	.vidioc_reqbufs		 = vb2_ioctl_reqbufs,
	.vidioc_querybuf	 = vb2_ioctl_querybuf,
	.vidioc_qbuf		 = vb2_ioctl_qbuf,
	.vidioc_dqbuf		 = vb2_ioctl_dqbuf,
	.vidioc_streamon	 = vb2_ioctl_streamon,
	.vidioc_streamoff	 = vb2_ioctl_streamoff,
	.vidioc_log_status	 = vidioc_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर	 = cx231xx_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर	 = cx231xx_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device cx231xx_mpeg_ढाँचा = अणु
	.name          = "cx231xx",
	.fops          = &mpeg_fops,
	.ioctl_ops     = &mpeg_ioctl_ops,
	.minor         = -1,
	.tvnorms       = V4L2_STD_ALL,
पूर्ण;

व्योम cx231xx_417_unरेजिस्टर(काष्ठा cx231xx *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	dprपूर्णांकk(3, "%s()\n", __func__);

	अगर (video_is_रेजिस्टरed(&dev->v4l_device)) अणु
		video_unरेजिस्टर_device(&dev->v4l_device);
		v4l2_ctrl_handler_मुक्त(&dev->mpeg_ctrl_handler.hdl);
	पूर्ण
पूर्ण

अटल पूर्णांक cx231xx_s_video_encoding(काष्ठा cx2341x_handler *cxhdl, u32 val)
अणु
	काष्ठा cx231xx *dev = container_of(cxhdl, काष्ठा cx231xx, mpeg_ctrl_handler);
	पूर्णांक is_mpeg1 = val == V4L2_MPEG_VIDEO_ENCODING_MPEG_1;
	काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	/* fix videodecoder resolution */
	क्रमmat.क्रमmat.width = cxhdl->width / (is_mpeg1 ? 2 : 1);
	क्रमmat.क्रमmat.height = cxhdl->height;
	क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
	v4l2_subdev_call(dev->sd_cx25840, pad, set_fmt, शून्य, &क्रमmat);
	वापस 0;
पूर्ण

अटल पूर्णांक cx231xx_s_audio_sampling_freq(काष्ठा cx2341x_handler *cxhdl, u32 idx)
अणु
	अटल स्थिर u32 freqs[3] = अणु 44100, 48000, 32000 पूर्ण;
	काष्ठा cx231xx *dev = container_of(cxhdl, काष्ठा cx231xx, mpeg_ctrl_handler);

	/* The audio घड़ी of the digitizer must match the codec sample
	   rate otherwise you get some very strange effects. */
	अगर (idx < ARRAY_SIZE(freqs))
		call_all(dev, audio, s_घड़ी_freq, freqs[idx]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cx2341x_handler_ops cx231xx_ops = अणु
	/* needed क्रम the video घड़ी freq */
	.s_audio_sampling_freq = cx231xx_s_audio_sampling_freq,
	/* needed क्रम setting up the video resolution */
	.s_video_encoding = cx231xx_s_video_encoding,
पूर्ण;

अटल व्योम cx231xx_video_dev_init(
	काष्ठा cx231xx *dev,
	काष्ठा usb_device *usbdev,
	काष्ठा video_device *vfd,
	स्थिर काष्ठा video_device *ढाँचा,
	स्थिर अक्षर *type)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	*vfd = *ढाँचा;
	snम_लिखो(vfd->name, माप(vfd->name), "%s %s (%s)", dev->name,
		type, cx231xx_boards[dev->model].name);

	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->lock = &dev->lock;
	vfd->release = video_device_release_empty;
	vfd->ctrl_handler = &dev->mpeg_ctrl_handler.hdl;
	video_set_drvdata(vfd, dev);
	अगर (dev->tuner_type == TUNER_ABSENT) अणु
		v4l2_disable_ioctl(vfd, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(vfd, VIDIOC_S_TUNER);
	पूर्ण
पूर्ण

पूर्णांक cx231xx_417_रेजिस्टर(काष्ठा cx231xx *dev)
अणु
	/* FIXME: Port1 hardcoded here */
	पूर्णांक err;
	काष्ठा cx231xx_tsport *tsport = &dev->ts1;
	काष्ठा vb2_queue *q;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Set शेष TV standard */
	dev->encodernorm = cx231xx_tvnorms[0];

	अगर (dev->encodernorm.id & V4L2_STD_525_60)
		tsport->height = 480;
	अन्यथा
		tsport->height = 576;

	tsport->width = 720;
	err = cx2341x_handler_init(&dev->mpeg_ctrl_handler, 50);
	अगर (err) अणु
		dprपूर्णांकk(3, "%s: can't init cx2341x controls\n", dev->name);
		वापस err;
	पूर्ण
	dev->mpeg_ctrl_handler.func = cx231xx_mbox_func;
	dev->mpeg_ctrl_handler.priv = dev;
	dev->mpeg_ctrl_handler.ops = &cx231xx_ops;
	अगर (dev->sd_cx25840)
		v4l2_ctrl_add_handler(&dev->mpeg_ctrl_handler.hdl,
				dev->sd_cx25840->ctrl_handler, शून्य, false);
	अगर (dev->mpeg_ctrl_handler.hdl.error) अणु
		err = dev->mpeg_ctrl_handler.hdl.error;
		dprपूर्णांकk(3, "%s: can't add cx25840 controls\n", dev->name);
		v4l2_ctrl_handler_मुक्त(&dev->mpeg_ctrl_handler.hdl);
		वापस err;
	पूर्ण
	dev->norm = V4L2_STD_NTSC;

	dev->mpeg_ctrl_handler.port = CX2341X_PORT_SERIAL;
	cx2341x_handler_set_50hz(&dev->mpeg_ctrl_handler, false);

	/* Allocate and initialize V4L video device */
	cx231xx_video_dev_init(dev, dev->udev,
			&dev->v4l_device, &cx231xx_mpeg_ढाँचा, "mpeg");
	q = &dev->mpegq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_USERPTR | VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx231xx_buffer);
	q->ops = &cx231xx_video_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 1;
	q->lock = &dev->lock;
	err = vb2_queue_init(q);
	अगर (err)
		वापस err;
	dev->v4l_device.queue = q;

	err = video_रेजिस्टर_device(&dev->v4l_device,
		VFL_TYPE_VIDEO, -1);
	अगर (err < 0) अणु
		dprपूर्णांकk(3, "%s: can't register mpeg device\n", dev->name);
		v4l2_ctrl_handler_मुक्त(&dev->mpeg_ctrl_handler.hdl);
		वापस err;
	पूर्ण

	dprपूर्णांकk(3, "%s: registered device video%d [mpeg]\n",
	       dev->name, dev->v4l_device.num);

	वापस 0;
पूर्ण

MODULE_FIRMWARE(CX231xx_FIRM_IMAGE_NAME);
