<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Support क्रम a cx23417 mpeg encoder via cx23885 host port.
 *
 *    (c) 2004 Jelle Foks <jelle@foks.us>
 *    (c) 2004 Gerd Knorr <kraxel@bytesex.org>
 *    (c) 2008 Steven Toth <stoth@linuxtv.org>
 *      - CX23885/7/8 support
 *
 *  Includes parts from the ivtv driver <http://sourceक्रमge.net/projects/ivtv/>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-ioctl.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>

#घोषणा CX23885_FIRM_IMAGE_SIZE 376836
#घोषणा CX23885_FIRM_IMAGE_NAME "v4l-cx23885-enc.fw"

अटल अचिन्हित पूर्णांक mpegbufs = 32;
module_param(mpegbufs, पूर्णांक, 0644);
MODULE_PARM_DESC(mpegbufs, "number of mpeg buffers, range 2-32");
अटल अचिन्हित पूर्णांक mpeglines = 32;
module_param(mpeglines, पूर्णांक, 0644);
MODULE_PARM_DESC(mpeglines, "number of lines in an MPEG buffer, range 2-32");
अटल अचिन्हित पूर्णांक mpeglinesize = 512;
module_param(mpeglinesize, पूर्णांक, 0644);
MODULE_PARM_DESC(mpeglinesize,
	"number of bytes in each line of an MPEG buffer, range 512-1024");

अटल अचिन्हित पूर्णांक v4l_debug;
module_param(v4l_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(v4l_debug, "enable V4L debug messages");

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (v4l_debug >= level) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: 417:" fmt), \
			__func__, ##arg); \
	पूर्ण जबतक (0)

अटल काष्ठा cx23885_tvnorm cx23885_tvnorms[] = अणु
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
क्रमागत cx23885_capture_type अणु
	CX23885_MPEG_CAPTURE,
	CX23885_RAW_CAPTURE,
	CX23885_RAW_PASSTHRU_CAPTURE
पूर्ण;
क्रमागत cx23885_capture_bits अणु
	CX23885_RAW_BITS_NONE             = 0x00,
	CX23885_RAW_BITS_YUV_CAPTURE      = 0x01,
	CX23885_RAW_BITS_PCM_CAPTURE      = 0x02,
	CX23885_RAW_BITS_VBI_CAPTURE      = 0x04,
	CX23885_RAW_BITS_PASSTHRU_CAPTURE = 0x08,
	CX23885_RAW_BITS_TO_HOST_CAPTURE  = 0x10
पूर्ण;
क्रमागत cx23885_capture_end अणु
	CX23885_END_AT_GOP, /* stop at the end of gop, generate irq */
	CX23885_END_NOW, /* stop immediately, no irq */
पूर्ण;
क्रमागत cx23885_framerate अणु
	CX23885_FRAMERATE_NTSC_30, /* NTSC: 30fps */
	CX23885_FRAMERATE_PAL_25   /* PAL: 25fps */
पूर्ण;
क्रमागत cx23885_stream_port अणु
	CX23885_OUTPUT_PORT_MEMORY,
	CX23885_OUTPUT_PORT_STREAMING,
	CX23885_OUTPUT_PORT_SERIAL
पूर्ण;
क्रमागत cx23885_data_xfer_status अणु
	CX23885_MORE_BUFFERS_FOLLOW,
	CX23885_LAST_BUFFER,
पूर्ण;
क्रमागत cx23885_picture_mask अणु
	CX23885_PICTURE_MASK_NONE,
	CX23885_PICTURE_MASK_I_FRAMES,
	CX23885_PICTURE_MASK_I_P_FRAMES = 0x3,
	CX23885_PICTURE_MASK_ALL_FRAMES = 0x7,
पूर्ण;
क्रमागत cx23885_vbi_mode_bits अणु
	CX23885_VBI_BITS_SLICED,
	CX23885_VBI_BITS_RAW,
पूर्ण;
क्रमागत cx23885_vbi_insertion_bits अणु
	CX23885_VBI_BITS_INSERT_IN_XTENSION_USR_DATA,
	CX23885_VBI_BITS_INSERT_IN_PRIVATE_PACKETS = 0x1 << 1,
	CX23885_VBI_BITS_SEPARATE_STREAM = 0x2 << 1,
	CX23885_VBI_BITS_SEPARATE_STREAM_USR_DATA = 0x4 << 1,
	CX23885_VBI_BITS_SEPARATE_STREAM_PRV_DATA = 0x5 << 1,
पूर्ण;
क्रमागत cx23885_dma_unit अणु
	CX23885_DMA_BYTES,
	CX23885_DMA_FRAMES,
पूर्ण;
क्रमागत cx23885_dma_transfer_status_bits अणु
	CX23885_DMA_TRANSFER_BITS_DONE = 0x01,
	CX23885_DMA_TRANSFER_BITS_ERROR = 0x04,
	CX23885_DMA_TRANSFER_BITS_LL_ERROR = 0x10,
पूर्ण;
क्रमागत cx23885_छोड़ो अणु
	CX23885_PAUSE_ENCODING,
	CX23885_RESUME_ENCODING,
पूर्ण;
क्रमागत cx23885_copyright अणु
	CX23885_COPYRIGHT_OFF,
	CX23885_COPYRIGHT_ON,
पूर्ण;
क्रमागत cx23885_notअगरication_type अणु
	CX23885_NOTIFICATION_REFRESH,
पूर्ण;
क्रमागत cx23885_notअगरication_status अणु
	CX23885_NOTIFICATION_OFF,
	CX23885_NOTIFICATION_ON,
पूर्ण;
क्रमागत cx23885_notअगरication_mailbox अणु
	CX23885_NOTIFICATION_NO_MAILBOX = -1,
पूर्ण;
क्रमागत cx23885_field1_lines अणु
	CX23885_FIELD1_SAA7114 = 0x00EF, /* 239 */
	CX23885_FIELD1_SAA7115 = 0x00F0, /* 240 */
	CX23885_FIELD1_MICRONAS = 0x0105, /* 261 */
पूर्ण;
क्रमागत cx23885_field2_lines अणु
	CX23885_FIELD2_SAA7114 = 0x00EF, /* 239 */
	CX23885_FIELD2_SAA7115 = 0x00F0, /* 240 */
	CX23885_FIELD2_MICRONAS = 0x0106, /* 262 */
पूर्ण;
क्रमागत cx23885_custom_data_type अणु
	CX23885_CUSTOM_EXTENSION_USR_DATA,
	CX23885_CUSTOM_PRIVATE_PACKET,
पूर्ण;
क्रमागत cx23885_mute अणु
	CX23885_UNMUTE,
	CX23885_MUTE,
पूर्ण;
क्रमागत cx23885_mute_video_mask अणु
	CX23885_MUTE_VIDEO_V_MASK = 0x0000FF00,
	CX23885_MUTE_VIDEO_U_MASK = 0x00FF0000,
	CX23885_MUTE_VIDEO_Y_MASK = 0xFF000000,
पूर्ण;
क्रमागत cx23885_mute_video_shअगरt अणु
	CX23885_MUTE_VIDEO_V_SHIFT = 8,
	CX23885_MUTE_VIDEO_U_SHIFT = 16,
	CX23885_MUTE_VIDEO_Y_SHIFT = 24,
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

/**** Bit definitions क्रम MC417_RWD and MC417_OEN रेजिस्टरs  ***
  bits 31-16
+-----------+
| Reserved  |
+-----------+
  bit 15  bit 14  bit 13 bit 12  bit 11  bit 10  bit 9   bit 8
+-------+-------+-------+-------+-------+-------+-------+-------+
| MIWR# | MIRD# | MICS# |MIRDY# |MIADDR3|MIADDR2|MIADDR1|MIADDR0|
+-------+-------+-------+-------+-------+-------+-------+-------+
 bit 7   bit 6   bit 5   bit 4   bit 3   bit 2   bit 1   bit 0
+-------+-------+-------+-------+-------+-------+-------+-------+
|MIDATA7|MIDATA6|MIDATA5|MIDATA4|MIDATA3|MIDATA2|MIDATA1|MIDATA0|
+-------+-------+-------+-------+-------+-------+-------+-------+
***/
#घोषणा MC417_MIWR	0x8000
#घोषणा MC417_MIRD	0x4000
#घोषणा MC417_MICS	0x2000
#घोषणा MC417_MIRDY	0x1000
#घोषणा MC417_MIADDR	0x0F00
#घोषणा MC417_MIDATA	0x00FF

/* MIADDR* nibble definitions */
#घोषणा  MCI_MEMORY_DATA_BYTE0          0x000
#घोषणा  MCI_MEMORY_DATA_BYTE1          0x100
#घोषणा  MCI_MEMORY_DATA_BYTE2          0x200
#घोषणा  MCI_MEMORY_DATA_BYTE3          0x300
#घोषणा  MCI_MEMORY_ADDRESS_BYTE2       0x400
#घोषणा  MCI_MEMORY_ADDRESS_BYTE1       0x500
#घोषणा  MCI_MEMORY_ADDRESS_BYTE0       0x600
#घोषणा  MCI_REGISTER_DATA_BYTE0        0x800
#घोषणा  MCI_REGISTER_DATA_BYTE1        0x900
#घोषणा  MCI_REGISTER_DATA_BYTE2        0xA00
#घोषणा  MCI_REGISTER_DATA_BYTE3        0xB00
#घोषणा  MCI_REGISTER_ADDRESS_BYTE0     0xC00
#घोषणा  MCI_REGISTER_ADDRESS_BYTE1     0xD00
#घोषणा  MCI_REGISTER_MODE              0xE00

/* Read and ग_लिखो modes */
#घोषणा  MCI_MODE_REGISTER_READ         0
#घोषणा  MCI_MODE_REGISTER_WRITE        1
#घोषणा  MCI_MODE_MEMORY_READ           0
#घोषणा  MCI_MODE_MEMORY_WRITE          0x40

/*** Bit definitions क्रम MC417_CTL रेजिस्टर ****
 bits 31-6   bits 5-4   bit 3    bits 2-1       Bit 0
+--------+-------------+--------+--------------+------------+
|Reserved|MC417_SPD_CTL|Reserved|MC417_GPIO_SEL|UART_GPIO_EN|
+--------+-------------+--------+--------------+------------+
***/
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

व्योम cx23885_mc417_init(काष्ठा cx23885_dev *dev)
अणु
	u32 regval;

	dprपूर्णांकk(2, "%s()\n", __func__);

	/* Configure MC417_CTL रेजिस्टर to शेषs. */
	regval = MC417_SPD_CTL(MC417_SPD_CTL_FAST)	|
		 MC417_GPIO_SEL(MC417_GPIO_SEL_GPIO3)	|
		 MC417_UART_GPIO_EN;
	cx_ग_लिखो(MC417_CTL, regval);

	/* Configure MC417_OEN to शेषs. */
	regval = MC417_MIRDY;
	cx_ग_लिखो(MC417_OEN, regval);

	/* Configure MC417_RWD to शेषs. */
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS;
	cx_ग_लिखो(MC417_RWD, regval);
पूर्ण

अटल पूर्णांक mc417_रुको_पढ़ोy(काष्ठा cx23885_dev *dev)
अणु
	u32 mi_पढ़ोy;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);

	क्रम (;;) अणु
		mi_पढ़ोy = cx_पढ़ो(MC417_RWD) & MC417_MIRDY;
		अगर (mi_पढ़ोy != 0)
			वापस 0;
		अगर (समय_after(jअगरfies, समयout))
			वापस -1;
		udelay(1);
	पूर्ण
पूर्ण

पूर्णांक mc417_रेजिस्टर_ग_लिखो(काष्ठा cx23885_dev *dev, u16 address, u32 value)
अणु
	u32 regval;

	/* Enable MC417 GPIO outमाला_दो except क्रम MC417_MIRDY,
	 * which is an input.
	 */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY);

	/* Write data byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE0 |
		(value & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);

	/* Transition CS/WR to effect ग_लिखो transaction across bus. */
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE1 |
		((value >> 8) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE2 |
		((value >> 16) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 3 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE3 |
		((value >> 24) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_ADDRESS_BYTE0 |
		(address & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_ADDRESS_BYTE1 |
		((address >> 8) & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Indicate that this is a ग_लिखो. */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_MODE |
		MCI_MODE_REGISTER_WRITE;
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Wait क्रम the trans to complete (MC417_MIRDY निश्चितed). */
	वापस mc417_रुको_पढ़ोy(dev);
पूर्ण

पूर्णांक mc417_रेजिस्टर_पढ़ो(काष्ठा cx23885_dev *dev, u16 address, u32 *value)
अणु
	पूर्णांक retval;
	u32 regval;
	u32 tempval;
	u32 dataval;

	/* Enable MC417 GPIO outमाला_दो except क्रम MC417_MIRDY,
	 * which is an input.
	 */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY);

	/* Write address byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_ADDRESS_BYTE0 |
		((address & 0x00FF));
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_ADDRESS_BYTE1 |
		((address >> 8) & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Indicate that this is a रेजिस्टर पढ़ो. */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_MODE |
		MCI_MODE_REGISTER_READ;
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Wait क्रम the trans to complete (MC417_MIRDY निश्चितed). */
	retval = mc417_रुको_पढ़ोy(dev);

	/* चयन the DAT0-7 GPIO[10:3] to input mode */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY | MC417_MIDATA);

	/* Read data byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE0;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Transition RD to effect पढ़ो transaction across bus.
	 * Transition 0x5000 -> 0x9000 correct (RD/RDY -> WR/RDY)?
	 * Should it be 0x9000 -> 0xF000 (also why is RDY being set, its
	 * input only...)
	 */
	regval = MC417_MIWR | MC417_MIRDY | MCI_REGISTER_DATA_BYTE0;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Collect byte */
	tempval = cx_पढ़ो(MC417_RWD);
	dataval = tempval & 0x000000FF;

	/* Bring CS and RD high. */
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE1;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_REGISTER_DATA_BYTE1;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= ((tempval & 0x000000FF) << 8);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE2;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_REGISTER_DATA_BYTE2;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= ((tempval & 0x000000FF) << 16);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 3 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_REGISTER_DATA_BYTE3;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_REGISTER_DATA_BYTE3;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= ((tempval & 0x000000FF) << 24);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	*value  = dataval;

	वापस retval;
पूर्ण

पूर्णांक mc417_memory_ग_लिखो(काष्ठा cx23885_dev *dev, u32 address, u32 value)
अणु
	u32 regval;

	/* Enable MC417 GPIO outमाला_दो except क्रम MC417_MIRDY,
	 * which is an input.
	 */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY);

	/* Write data byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE0 |
		(value & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);

	/* Transition CS/WR to effect ग_लिखो transaction across bus. */
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE1 |
		((value >> 8) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE2 |
		((value >> 16) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write data byte 3 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE3 |
		((value >> 24) & 0x000000FF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE2 |
		MCI_MODE_MEMORY_WRITE | ((address >> 16) & 0x3F);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE1 |
		((address >> 8) & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE0 |
		(address & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Wait क्रम the trans to complete (MC417_MIRDY निश्चितed). */
	वापस mc417_रुको_पढ़ोy(dev);
पूर्ण

पूर्णांक mc417_memory_पढ़ो(काष्ठा cx23885_dev *dev, u32 address, u32 *value)
अणु
	पूर्णांक retval;
	u32 regval;
	u32 tempval;
	u32 dataval;

	/* Enable MC417 GPIO outमाला_दो except क्रम MC417_MIRDY,
	 * which is an input.
	 */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY);

	/* Write address byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE2 |
		MCI_MODE_MEMORY_READ | ((address >> 16) & 0x3F);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE1 |
		((address >> 8) & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Write address byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_ADDRESS_BYTE0 |
		(address & 0xFF);
	cx_ग_लिखो(MC417_RWD, regval);
	regval |= MC417_MICS | MC417_MIWR;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Wait क्रम the trans to complete (MC417_MIRDY निश्चितed). */
	retval = mc417_रुको_पढ़ोy(dev);

	/* चयन the DAT0-7 GPIO[10:3] to input mode */
	cx_ग_लिखो(MC417_OEN, MC417_MIRDY | MC417_MIDATA);

	/* Read data byte 3 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE3;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Transition RD to effect पढ़ो transaction across bus. */
	regval = MC417_MIWR | MC417_MIRDY | MCI_MEMORY_DATA_BYTE3;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Collect byte */
	tempval = cx_पढ़ो(MC417_RWD);
	dataval = ((tempval & 0x000000FF) << 24);

	/* Bring CS and RD high. */
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 2 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE2;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_MEMORY_DATA_BYTE2;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= ((tempval & 0x000000FF) << 16);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 1 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE1;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_MEMORY_DATA_BYTE1;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= ((tempval & 0x000000FF) << 8);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	/* Read data byte 0 */
	regval = MC417_MIRD | MC417_MIRDY | MCI_MEMORY_DATA_BYTE0;
	cx_ग_लिखो(MC417_RWD, regval);
	regval = MC417_MIWR | MC417_MIRDY | MCI_MEMORY_DATA_BYTE0;
	cx_ग_लिखो(MC417_RWD, regval);
	tempval = cx_पढ़ो(MC417_RWD);
	dataval |= (tempval & 0x000000FF);
	regval = MC417_MIWR | MC417_MIRD | MC417_MICS | MC417_MIRDY;
	cx_ग_लिखो(MC417_RWD, regval);

	*value  = dataval;

	वापस retval;
पूर्ण

व्योम mc417_gpio_set(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	u32 val;

	/* Set the gpio value */
	mc417_रेजिस्टर_पढ़ो(dev, 0x900C, &val);
	val |= (mask & 0x000ffff);
	mc417_रेजिस्टर_ग_लिखो(dev, 0x900C, val);
पूर्ण

व्योम mc417_gpio_clear(काष्ठा cx23885_dev *dev, u32 mask)
अणु
	u32 val;

	/* Clear the gpio value */
	mc417_रेजिस्टर_पढ़ो(dev, 0x900C, &val);
	val &= ~(mask & 0x0000ffff);
	mc417_रेजिस्टर_ग_लिखो(dev, 0x900C, val);
पूर्ण

व्योम mc417_gpio_enable(काष्ठा cx23885_dev *dev, u32 mask, पूर्णांक asoutput)
अणु
	u32 val;

	/* Enable GPIO direction bits */
	mc417_रेजिस्टर_पढ़ो(dev, 0x9020, &val);
	अगर (asoutput)
		val |= (mask & 0x0000ffff);
	अन्यथा
		val &= ~(mask & 0x0000ffff);

	mc417_रेजिस्टर_ग_लिखो(dev, 0x9020, val);
पूर्ण
/* ------------------------------------------------------------------ */

/* MPEG encoder API */
अटल अक्षर *cmd_to_str(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल CX2341X_ENC_PING_FW:
		वापस  "PING_FW";
	हाल CX2341X_ENC_START_CAPTURE:
		वापस  "START_CAPTURE";
	हाल CX2341X_ENC_STOP_CAPTURE:
		वापस  "STOP_CAPTURE";
	हाल CX2341X_ENC_SET_AUDIO_ID:
		वापस  "SET_AUDIO_ID";
	हाल CX2341X_ENC_SET_VIDEO_ID:
		वापस  "SET_VIDEO_ID";
	हाल CX2341X_ENC_SET_PCR_ID:
		वापस  "SET_PCR_ID";
	हाल CX2341X_ENC_SET_FRAME_RATE:
		वापस  "SET_FRAME_RATE";
	हाल CX2341X_ENC_SET_FRAME_SIZE:
		वापस  "SET_FRAME_SIZE";
	हाल CX2341X_ENC_SET_BIT_RATE:
		वापस  "SET_BIT_RATE";
	हाल CX2341X_ENC_SET_GOP_PROPERTIES:
		वापस  "SET_GOP_PROPERTIES";
	हाल CX2341X_ENC_SET_ASPECT_RATIO:
		वापस  "SET_ASPECT_RATIO";
	हाल CX2341X_ENC_SET_DNR_FILTER_MODE:
		वापस  "SET_DNR_FILTER_MODE";
	हाल CX2341X_ENC_SET_DNR_FILTER_PROPS:
		वापस  "SET_DNR_FILTER_PROPS";
	हाल CX2341X_ENC_SET_CORING_LEVELS:
		वापस  "SET_CORING_LEVELS";
	हाल CX2341X_ENC_SET_SPATIAL_FILTER_TYPE:
		वापस  "SET_SPATIAL_FILTER_TYPE";
	हाल CX2341X_ENC_SET_VBI_LINE:
		वापस  "SET_VBI_LINE";
	हाल CX2341X_ENC_SET_STREAM_TYPE:
		वापस  "SET_STREAM_TYPE";
	हाल CX2341X_ENC_SET_OUTPUT_PORT:
		वापस  "SET_OUTPUT_PORT";
	हाल CX2341X_ENC_SET_AUDIO_PROPERTIES:
		वापस  "SET_AUDIO_PROPERTIES";
	हाल CX2341X_ENC_HALT_FW:
		वापस  "HALT_FW";
	हाल CX2341X_ENC_GET_VERSION:
		वापस  "GET_VERSION";
	हाल CX2341X_ENC_SET_GOP_CLOSURE:
		वापस  "SET_GOP_CLOSURE";
	हाल CX2341X_ENC_GET_SEQ_END:
		वापस  "GET_SEQ_END";
	हाल CX2341X_ENC_SET_PGM_INDEX_INFO:
		वापस  "SET_PGM_INDEX_INFO";
	हाल CX2341X_ENC_SET_VBI_CONFIG:
		वापस  "SET_VBI_CONFIG";
	हाल CX2341X_ENC_SET_DMA_BLOCK_SIZE:
		वापस  "SET_DMA_BLOCK_SIZE";
	हाल CX2341X_ENC_GET_PREV_DMA_INFO_MB_10:
		वापस  "GET_PREV_DMA_INFO_MB_10";
	हाल CX2341X_ENC_GET_PREV_DMA_INFO_MB_9:
		वापस  "GET_PREV_DMA_INFO_MB_9";
	हाल CX2341X_ENC_SCHED_DMA_TO_HOST:
		वापस  "SCHED_DMA_TO_HOST";
	हाल CX2341X_ENC_INITIALIZE_INPUT:
		वापस  "INITIALIZE_INPUT";
	हाल CX2341X_ENC_SET_FRAME_DROP_RATE:
		वापस  "SET_FRAME_DROP_RATE";
	हाल CX2341X_ENC_PAUSE_ENCODER:
		वापस  "PAUSE_ENCODER";
	हाल CX2341X_ENC_REFRESH_INPUT:
		वापस  "REFRESH_INPUT";
	हाल CX2341X_ENC_SET_COPYRIGHT:
		वापस  "SET_COPYRIGHT";
	हाल CX2341X_ENC_SET_EVENT_NOTIFICATION:
		वापस  "SET_EVENT_NOTIFICATION";
	हाल CX2341X_ENC_SET_NUM_VSYNC_LINES:
		वापस  "SET_NUM_VSYNC_LINES";
	हाल CX2341X_ENC_SET_PLACEHOLDER:
		वापस  "SET_PLACEHOLDER";
	हाल CX2341X_ENC_MUTE_VIDEO:
		वापस  "MUTE_VIDEO";
	हाल CX2341X_ENC_MUTE_AUDIO:
		वापस  "MUTE_AUDIO";
	हाल CX2341X_ENC_MISC:
		वापस  "MISC";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल पूर्णांक cx23885_mbox_func(व्योम *priv,
			     u32 command,
			     पूर्णांक in,
			     पूर्णांक out,
			     u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	काष्ठा cx23885_dev *dev = priv;
	अचिन्हित दीर्घ समयout;
	u32 value, flag, retval = 0;
	पूर्णांक i;

	dprपूर्णांकk(3, "%s: command(0x%X) = %s\n", __func__, command,
		cmd_to_str(command));

	/* this may not be 100% safe अगर we can't पढ़ो any memory location
	   without side effects */
	mc417_memory_पढ़ो(dev, dev->cx23417_mailbox - 4, &value);
	अगर (value != 0x12345678) अणु
		pr_err("Firmware and/or mailbox pointer not initialized or corrupted, signature = 0x%x, cmd = %s\n",
			value, cmd_to_str(command));
		वापस -1;
	पूर्ण

	/* This पढ़ो looks at 32 bits, but flag is only 8 bits.
	 * Seems we also bail अगर CMD or TIMEOUT bytes are set???
	 */
	mc417_memory_पढ़ो(dev, dev->cx23417_mailbox, &flag);
	अगर (flag) अणु
		pr_err("ERROR: Mailbox appears to be in use (%x), cmd = %s\n",
		       flag, cmd_to_str(command));
		वापस -1;
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
			pr_err("ERROR: API Mailbox timeout\n");
			वापस -1;
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

	वापस retval;
पूर्ण

/* We करोn't need to call the API often, so using just one
 * mailbox will probably suffice
 */
अटल पूर्णांक cx23885_api_cmd(काष्ठा cx23885_dev *dev,
			   u32 command,
			   u32 inअ_दोnt,
			   u32 outअ_दोnt,
			   ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची vargs;
	पूर्णांक i, err;

	dprपूर्णांकk(3, "%s() cmds = 0x%08x\n", __func__, command);

	बहु_शुरू(vargs, outअ_दोnt);
	क्रम (i = 0; i < inअ_दोnt; i++)
		data[i] = बहु_तर्क(vargs, पूर्णांक);

	err = cx23885_mbox_func(dev, command, inअ_दोnt, outअ_दोnt, data);
	क्रम (i = 0; i < outअ_दोnt; i++) अणु
		पूर्णांक *vptr = बहु_तर्क(vargs, पूर्णांक *);
		*vptr = data[i];
	पूर्ण
	बहु_पूर्ण(vargs);

	वापस err;
पूर्ण

अटल पूर्णांक cx23885_api_func(व्योम *priv, u32 cmd, पूर्णांक in, पूर्णांक out, u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	वापस cx23885_mbox_func(priv, cmd, in, out, data);
पूर्ण

अटल पूर्णांक cx23885_find_mailbox(काष्ठा cx23885_dev *dev)
अणु
	u32 signature[4] = अणु
		0x12345678, 0x34567812, 0x56781234, 0x78123456
	पूर्ण;
	पूर्णांक signaturecnt = 0;
	u32 value;
	पूर्णांक i;

	dprपूर्णांकk(2, "%s()\n", __func__);

	क्रम (i = 0; i < CX23885_FIRM_IMAGE_SIZE; i++) अणु
		mc417_memory_पढ़ो(dev, i, &value);
		अगर (value == signature[signaturecnt])
			signaturecnt++;
		अन्यथा
			signaturecnt = 0;
		अगर (4 == signaturecnt) अणु
			dprपूर्णांकk(1, "Mailbox signature found at 0x%x\n", i+1);
			वापस i+1;
		पूर्ण
	पूर्ण
	pr_err("Mailbox signature values not found!\n");
	वापस -1;
पूर्ण

अटल पूर्णांक cx23885_load_firmware(काष्ठा cx23885_dev *dev)
अणु
	अटल स्थिर अचिन्हित अक्षर magic[8] = अणु
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	पूर्ण;
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक i, retval = 0;
	u32 value = 0;
	u32 gpio_output = 0;
	u32 gpio_value;
	u32 checksum = 0;
	u32 *dataptr;

	dprपूर्णांकk(2, "%s()\n", __func__);

	/* Save GPIO settings beक्रमe reset of APU */
	retval |= mc417_memory_पढ़ो(dev, 0x9020, &gpio_output);
	retval |= mc417_memory_पढ़ो(dev, 0x900C, &gpio_value);

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
		pr_err("%s: Error with mc417_register_write\n",
			__func__);
		वापस -1;
	पूर्ण

	retval = request_firmware(&firmware, CX23885_FIRM_IMAGE_NAME,
				  &dev->pci->dev);

	अगर (retval != 0) अणु
		pr_err("ERROR: Hotplug firmware request failed (%s).\n",
		       CX23885_FIRM_IMAGE_NAME);
		pr_err("Please fix your hotplug setup, the board will not work without firmware loaded!\n");
		वापस -1;
	पूर्ण

	अगर (firmware->size != CX23885_FIRM_IMAGE_SIZE) अणु
		pr_err("ERROR: Firmware size mismatch (have %zu, expected %d)\n",
		       firmware->size, CX23885_FIRM_IMAGE_SIZE);
		release_firmware(firmware);
		वापस -1;
	पूर्ण

	अगर (0 != स_भेद(firmware->data, magic, 8)) अणु
		pr_err("ERROR: Firmware magic mismatch, wrong file?\n");
		release_firmware(firmware);
		वापस -1;
	पूर्ण

	/* transfer to the chip */
	dprपूर्णांकk(2, "Loading firmware ...\n");
	dataptr = (u32 *)firmware->data;
	क्रम (i = 0; i < (firmware->size >> 2); i++) अणु
		value = *dataptr;
		checksum += ~value;
		अगर (mc417_memory_ग_लिखो(dev, i, value) != 0) अणु
			pr_err("ERROR: Loading firmware failed!\n");
			release_firmware(firmware);
			वापस -1;
		पूर्ण
		dataptr++;
	पूर्ण

	/* पढ़ो back to verअगरy with the checksum */
	dprपूर्णांकk(1, "Verifying firmware ...\n");
	क्रम (i--; i >= 0; i--) अणु
		अगर (mc417_memory_पढ़ो(dev, i, &value) != 0) अणु
			pr_err("ERROR: Reading firmware failed!\n");
			release_firmware(firmware);
			वापस -1;
		पूर्ण
		checksum -= ~value;
	पूर्ण
	अगर (checksum) अणु
		pr_err("ERROR: Firmware load failed (checksum mismatch).\n");
		release_firmware(firmware);
		वापस -1;
	पूर्ण
	release_firmware(firmware);
	dprपूर्णांकk(1, "Firmware upload successful.\n");

	retval |= mc417_रेजिस्टर_ग_लिखो(dev, IVTV_REG_HW_BLOCKS,
		IVTV_CMD_HW_BLOCKS_RST);

	/* F/W घातer up disturbs the GPIOs, restore state */
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x9020, gpio_output);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x900C, gpio_value);

	retval |= mc417_रेजिस्टर_पढ़ो(dev, IVTV_REG_VPU, &value);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, IVTV_REG_VPU, value & 0xFFFFFFE8);

	/* Hardcoded GPIO's here */
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x9020, 0x4000);
	retval |= mc417_रेजिस्टर_ग_लिखो(dev, 0x900C, 0x4000);

	mc417_रेजिस्टर_पढ़ो(dev, 0x9020, &gpio_output);
	mc417_रेजिस्टर_पढ़ो(dev, 0x900C, &gpio_value);

	अगर (retval < 0)
		pr_err("%s: Error with mc417_register_write\n",
			__func__);
	वापस 0;
पूर्ण

व्योम cx23885_417_check_encoder(काष्ठा cx23885_dev *dev)
अणु
	u32 status, seq;

	status = seq = 0;
	cx23885_api_cmd(dev, CX2341X_ENC_GET_SEQ_END, 0, 2, &status, &seq);
	dprपूर्णांकk(1, "%s() status = %d, seq = %d\n", __func__, status, seq);
पूर्ण

अटल व्योम cx23885_codec_settings(काष्ठा cx23885_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Dynamically change the height based on video standard */
	अगर (dev->encodernorm.id & V4L2_STD_525_60)
		dev->ts1.height = 480;
	अन्यथा
		dev->ts1.height = 576;

	/* assign frame size */
	cx23885_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
				dev->ts1.height, dev->ts1.width);

	dev->cxhdl.width = dev->ts1.width;
	dev->cxhdl.height = dev->ts1.height;
	dev->cxhdl.is_50hz =
		(dev->encodernorm.id & V4L2_STD_625_50) != 0;

	cx2341x_handler_setup(&dev->cxhdl);

	cx23885_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 3, 1);
	cx23885_api_cmd(dev, CX2341X_ENC_MISC, 2, 0, 4, 1);
पूर्ण

अटल पूर्णांक cx23885_initialize_codec(काष्ठा cx23885_dev *dev, पूर्णांक startencoder)
अणु
	पूर्णांक version;
	पूर्णांक retval;
	u32 i, data[7];

	dprपूर्णांकk(1, "%s()\n", __func__);

	retval = cx23885_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0); /* ping */
	अगर (retval < 0) अणु
		dprपूर्णांकk(2, "%s() PING OK\n", __func__);
		retval = cx23885_load_firmware(dev);
		अगर (retval < 0) अणु
			pr_err("%s() f/w load failed\n", __func__);
			वापस retval;
		पूर्ण
		retval = cx23885_find_mailbox(dev);
		अगर (retval < 0) अणु
			pr_err("%s() mailbox < 0, error\n",
				__func__);
			वापस -1;
		पूर्ण
		dev->cx23417_mailbox = retval;
		retval = cx23885_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0);
		अगर (retval < 0) अणु
			pr_err("ERROR: cx23417 firmware ping failed!\n");
			वापस -1;
		पूर्ण
		retval = cx23885_api_cmd(dev, CX2341X_ENC_GET_VERSION, 0, 1,
			&version);
		अगर (retval < 0) अणु
			pr_err("ERROR: cx23417 firmware get encoder :version failed!\n");
			वापस -1;
		पूर्ण
		dprपूर्णांकk(1, "cx23417 firmware version is 0x%08x\n", version);
		msleep(200);
	पूर्ण

	cx23885_codec_settings(dev);
	msleep(60);

	cx23885_api_cmd(dev, CX2341X_ENC_SET_NUM_VSYNC_LINES, 2, 0,
		CX23885_FIELD1_SAA7115, CX23885_FIELD2_SAA7115);
	cx23885_api_cmd(dev, CX2341X_ENC_SET_PLACEHOLDER, 12, 0,
		CX23885_CUSTOM_EXTENSION_USR_DATA, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0);

	/* Setup to capture VBI */
	data[0] = 0x0001BD00;
	data[1] = 1;          /* frames per पूर्णांकerrupt */
	data[2] = 4;          /* total bufs */
	data[3] = 0x91559155; /* start codes */
	data[4] = 0x206080C0; /* stop codes */
	data[5] = 6;          /* lines */
	data[6] = 64;         /* BPL */

	cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_CONFIG, 7, 0, data[0], data[1],
		data[2], data[3], data[4], data[5], data[6]);

	क्रम (i = 2; i <= 24; i++) अणु
		पूर्णांक valid;

		valid = ((i >= 19) && (i <= 21));
		cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_LINE, 5, 0, i,
				valid, 0 , 0, 0);
		cx23885_api_cmd(dev, CX2341X_ENC_SET_VBI_LINE, 5, 0,
				i | 0x80000000, valid, 0, 0, 0);
	पूर्ण

	cx23885_api_cmd(dev, CX2341X_ENC_MUTE_AUDIO, 1, 0, CX23885_UNMUTE);
	msleep(60);

	/* initialize the video input */
	cx23885_api_cmd(dev, CX2341X_ENC_INITIALIZE_INPUT, 0, 0);
	msleep(60);

	/* Enable VIP style pixel invalidation so we work with scaled mode */
	mc417_memory_ग_लिखो(dev, 2120, 0x00000080);

	/* start capturing to the host पूर्णांकerface */
	अगर (startencoder) अणु
		cx23885_api_cmd(dev, CX2341X_ENC_START_CAPTURE, 2, 0,
			CX23885_MPEG_CAPTURE, CX23885_RAW_BITS_NONE);
		msleep(10);
	पूर्ण

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;

	dev->ts1.ts_packet_size  = mpeglinesize;
	dev->ts1.ts_packet_count = mpeglines;
	*num_planes = 1;
	sizes[0] = mpeglinesize * mpeglines;
	*num_buffers = mpegbufs;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf =
		container_of(vbuf, काष्ठा cx23885_buffer, vb);

	वापस cx23885_buf_prepare(buf, &dev->ts1);
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_मुक्त_buffer(dev, buf);
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer   *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_buf_queue(&dev->ts1, buf);
पूर्ण

अटल पूर्णांक cx23885_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &dev->ts1.mpegq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = cx23885_initialize_codec(dev, 1);
	अगर (ret == 0) अणु
		काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

		cx23885_start_dma(&dev->ts1, dmaq, buf);
		वापस 0;
	पूर्ण
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
	वापस ret;
पूर्ण

अटल व्योम cx23885_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx23885_dev *dev = q->drv_priv;

	/* stop mpeg capture */
	cx23885_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			CX23885_END_NOW, CX23885_MPEG_CAPTURE,
			CX23885_RAW_BITS_NONE);

	msleep(500);
	cx23885_417_check_encoder(dev);
	cx23885_cancel_buffers(&dev->ts1);
पूर्ण

अटल स्थिर काष्ठा vb2_ops cx23885_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = cx23885_start_streaming,
	.stop_streaming = cx23885_stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	*id = dev->tvnorm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(cx23885_tvnorms); i++)
		अगर (id & cx23885_tvnorms[i].id)
			अवरोध;
	अगर (i == ARRAY_SIZE(cx23885_tvnorms))
		वापस -EINVAL;

	ret = cx23885_set_tvnorm(dev, id);
	अगर (!ret)
		dev->encodernorm = cx23885_tvnorms[i];
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_input *i)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	dprपूर्णांकk(1, "%s()\n", __func__);
	वापस cx23885_क्रमागत_input(dev, i);
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	वापस cx23885_get_input(file, priv, i);
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस cx23885_set_input(file, priv, i);
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (dev->tuner_type == TUNER_ABSENT)
		वापस -EINVAL;
	अगर (0 != t->index)
		वापस -EINVAL;
	strscpy(t->name, "Television", माप(t->name));
	call_all(dev, tuner, g_tuner, t);

	dprपूर्णांकk(1, "VIDIOC_G_TUNER: tuner type %d\n", t->type);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (dev->tuner_type == TUNER_ABSENT)
		वापस -EINVAL;

	/* Update the A/V core */
	call_all(dev, tuner, s_tuner, t);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	अगर (dev->tuner_type == TUNER_ABSENT)
		वापस -EINVAL;
	f->type = V4L2_TUNER_ANALOG_TV;
	f->frequency = dev->freq;

	call_all(dev, tuner, g_frequency, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
	स्थिर काष्ठा v4l2_frequency *f)
अणु
	वापस cx23885_set_frequency(file, priv, f);
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	काष्ठा cx23885_tsport  *tsport = &dev->ts1;

	strscpy(cap->driver, dev->name, माप(cap->driver));
	strscpy(cap->card, cx23885_boards[tsport->dev->board].name,
		माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_STREAMING | V4L2_CAP_VBI_CAPTURE |
			    V4L2_CAP_AUDIO | V4L2_CAP_DEVICE_CAPS;
	अगर (dev->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;

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
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.colorspace   = 0;
	f->fmt.pix.width        = dev->ts1.width;
	f->fmt.pix.height       = dev->ts1.height;
	f->fmt.pix.field        = V4L2_FIELD_INTERLACED;
	dprपूर्णांकk(1, "VIDIOC_G_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.colorspace   = 0;
	f->fmt.pix.field        = V4L2_FIELD_INTERLACED;
	dprपूर्णांकk(1, "VIDIOC_TRY_FMT: w: %d, h: %d\n",
		dev->ts1.width, dev->ts1.height);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    =
		dev->ts1.ts_packet_size * dev->ts1.ts_packet_count;
	f->fmt.pix.colorspace   = 0;
	f->fmt.pix.field        = V4L2_FIELD_INTERLACED;
	dprपूर्णांकk(1, "VIDIOC_S_FMT: w: %d, h: %d, f: %d\n",
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.field);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा cx23885_dev *dev = video_drvdata(file);
	अक्षर name[32 + 2];

	snम_लिखो(name, माप(name), "%s/2", dev->name);
	call_all(dev, core, log_status);
	v4l2_ctrl_handler_log_status(&dev->cxhdl.hdl, name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations mpeg_fops = अणु
	.owner	       = THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = vb2_fop_release,
	.पढ़ो           = vb2_fop_पढ़ो,
	.poll		= vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,
	.mmap           = vb2_fop_mmap,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops mpeg_ioctl_ops = अणु
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_क्रमागत_input	 = vidioc_क्रमागत_input,
	.vidioc_g_input		 = vidioc_g_input,
	.vidioc_s_input		 = vidioc_s_input,
	.vidioc_g_tuner		 = vidioc_g_tuner,
	.vidioc_s_tuner		 = vidioc_s_tuner,
	.vidioc_g_frequency	 = vidioc_g_frequency,
	.vidioc_s_frequency	 = vidioc_s_frequency,
	.vidioc_querycap	 = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	 = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	 = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	 = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_prepare_buf   = vb2_ioctl_prepare_buf,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_log_status	 = vidioc_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info	 = cx23885_g_chip_info,
	.vidioc_g_रेजिस्टर	 = cx23885_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर	 = cx23885_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा video_device cx23885_mpeg_ढाँचा = अणु
	.name          = "cx23885",
	.fops          = &mpeg_fops,
	.ioctl_ops     = &mpeg_ioctl_ops,
	.tvnorms       = CX23885_NORMS,
पूर्ण;

व्योम cx23885_417_unरेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (dev->v4l_device) अणु
		अगर (video_is_रेजिस्टरed(dev->v4l_device))
			video_unरेजिस्टर_device(dev->v4l_device);
		अन्यथा
			video_device_release(dev->v4l_device);
		v4l2_ctrl_handler_मुक्त(&dev->cxhdl.hdl);
		dev->v4l_device = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा video_device *cx23885_video_dev_alloc(
	काष्ठा cx23885_tsport *tsport,
	काष्ठा pci_dev *pci,
	काष्ठा video_device *ढाँचा,
	अक्षर *type)
अणु
	काष्ठा video_device *vfd;
	काष्ठा cx23885_dev *dev = tsport->dev;

	dprपूर्णांकk(1, "%s()\n", __func__);

	vfd = video_device_alloc();
	अगर (शून्य == vfd)
		वापस शून्य;
	*vfd = *ढाँचा;
	snम_लिखो(vfd->name, माप(vfd->name), "%s (%s)",
		cx23885_boards[tsport->dev->board].name, type);
	vfd->v4l2_dev = &dev->v4l2_dev;
	vfd->release = video_device_release;
	वापस vfd;
पूर्ण

पूर्णांक cx23885_417_रेजिस्टर(काष्ठा cx23885_dev *dev)
अणु
	/* FIXME: Port1 hardcoded here */
	पूर्णांक err = -ENODEV;
	काष्ठा cx23885_tsport *tsport = &dev->ts1;
	काष्ठा vb2_queue *q;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (cx23885_boards[dev->board].portb != CX23885_MPEG_ENCODER)
		वापस err;

	/* Set शेष TV standard */
	dev->encodernorm = cx23885_tvnorms[0];

	अगर (dev->encodernorm.id & V4L2_STD_525_60)
		tsport->height = 480;
	अन्यथा
		tsport->height = 576;

	tsport->width = 720;
	dev->cxhdl.port = CX2341X_PORT_SERIAL;
	err = cx2341x_handler_init(&dev->cxhdl, 50);
	अगर (err)
		वापस err;
	dev->cxhdl.priv = dev;
	dev->cxhdl.func = cx23885_api_func;
	cx2341x_handler_set_50hz(&dev->cxhdl, tsport->height == 576);
	v4l2_ctrl_add_handler(&dev->ctrl_handler, &dev->cxhdl.hdl, शून्य, false);

	/* Allocate and initialize V4L video device */
	dev->v4l_device = cx23885_video_dev_alloc(tsport,
		dev->pci, &cx23885_mpeg_ढाँचा, "mpeg");
	q = &dev->vb2_mpegq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->gfp_flags = GFP_DMA32;
	q->min_buffers_needed = 2;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx23885_buffer);
	q->ops = &cx23885_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;

	err = vb2_queue_init(q);
	अगर (err < 0)
		वापस err;
	video_set_drvdata(dev->v4l_device, dev);
	dev->v4l_device->lock = &dev->lock;
	dev->v4l_device->queue = q;
	dev->v4l_device->device_caps = V4L2_CAP_VIDEO_CAPTURE |
				       V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	अगर (dev->tuner_type != TUNER_ABSENT)
		dev->v4l_device->device_caps |= V4L2_CAP_TUNER;
	err = video_रेजिस्टर_device(dev->v4l_device,
		VFL_TYPE_VIDEO, -1);
	अगर (err < 0) अणु
		pr_info("%s: can't register mpeg device\n", dev->name);
		वापस err;
	पूर्ण

	pr_info("%s: registered device %s [mpeg]\n",
	       dev->name, video_device_node_name(dev->v4l_device));

	/* ST: Configure the encoder parameters, but करोn't begin
	 * encoding, this resolves an issue where the first समय the
	 * encoder is started video can be choppy.
	 */
	cx23885_initialize_codec(dev, 0);

	वापस 0;
पूर्ण

MODULE_FIRMWARE(CX23885_FIRM_IMAGE_NAME);
