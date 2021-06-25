<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम a cx23416 mpeg encoder via cx2388x host port.
 *  "blackbird" reference design.
 *
 *    (c) 2004 Jelle Foks <jelle@foks.us>
 *    (c) 2004 Gerd Knorr <kraxel@bytesex.org>
 *
 *    (c) 2005-2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 *        - video_ioctl2 conversion
 *
 *  Includes parts from the ivtv driver <http://sourceक्रमge.net/projects/ivtv/>
 */

#समावेश "cx88.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>

MODULE_DESCRIPTION("driver for cx2388x/cx23416 based mpeg encoder cards");
MODULE_AUTHOR("Jelle Foks <jelle@foks.us>, Gerd Knorr <kraxel@bytesex.org> [SuSE Labs]");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(CX88_VERSION);

अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages [blackbird]");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (debug + 1 > level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: blackbird:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

#घोषणा BLACKBIRD_FIRM_IMAGE_SIZE 376836

/* defines below are from ivtv-driver.h */

#घोषणा IVTV_CMD_HW_BLOCKS_RST 0xFFFFFFFF

/* Firmware API commands */
#घोषणा IVTV_API_STD_TIMEOUT 500

क्रमागत blackbird_capture_type अणु
	BLACKBIRD_MPEG_CAPTURE,
	BLACKBIRD_RAW_CAPTURE,
	BLACKBIRD_RAW_PASSTHRU_CAPTURE
पूर्ण;

क्रमागत blackbird_capture_bits अणु
	BLACKBIRD_RAW_BITS_NONE             = 0x00,
	BLACKBIRD_RAW_BITS_YUV_CAPTURE      = 0x01,
	BLACKBIRD_RAW_BITS_PCM_CAPTURE      = 0x02,
	BLACKBIRD_RAW_BITS_VBI_CAPTURE      = 0x04,
	BLACKBIRD_RAW_BITS_PASSTHRU_CAPTURE = 0x08,
	BLACKBIRD_RAW_BITS_TO_HOST_CAPTURE  = 0x10
पूर्ण;

क्रमागत blackbird_capture_end अणु
	BLACKBIRD_END_AT_GOP, /* stop at the end of gop, generate irq */
	BLACKBIRD_END_NOW, /* stop immediately, no irq */
पूर्ण;

क्रमागत blackbird_framerate अणु
	BLACKBIRD_FRAMERATE_NTSC_30, /* NTSC: 30fps */
	BLACKBIRD_FRAMERATE_PAL_25   /* PAL: 25fps */
पूर्ण;

क्रमागत blackbird_stream_port अणु
	BLACKBIRD_OUTPUT_PORT_MEMORY,
	BLACKBIRD_OUTPUT_PORT_STREAMING,
	BLACKBIRD_OUTPUT_PORT_SERIAL
पूर्ण;

क्रमागत blackbird_data_xfer_status अणु
	BLACKBIRD_MORE_BUFFERS_FOLLOW,
	BLACKBIRD_LAST_BUFFER,
पूर्ण;

क्रमागत blackbird_picture_mask अणु
	BLACKBIRD_PICTURE_MASK_NONE,
	BLACKBIRD_PICTURE_MASK_I_FRAMES,
	BLACKBIRD_PICTURE_MASK_I_P_FRAMES = 0x3,
	BLACKBIRD_PICTURE_MASK_ALL_FRAMES = 0x7,
पूर्ण;

क्रमागत blackbird_vbi_mode_bits अणु
	BLACKBIRD_VBI_BITS_SLICED,
	BLACKBIRD_VBI_BITS_RAW,
पूर्ण;

क्रमागत blackbird_vbi_insertion_bits अणु
	BLACKBIRD_VBI_BITS_INSERT_IN_XTENSION_USR_DATA,
	BLACKBIRD_VBI_BITS_INSERT_IN_PRIVATE_PACKETS = 0x1 << 1,
	BLACKBIRD_VBI_BITS_SEPARATE_STREAM = 0x2 << 1,
	BLACKBIRD_VBI_BITS_SEPARATE_STREAM_USR_DATA = 0x4 << 1,
	BLACKBIRD_VBI_BITS_SEPARATE_STREAM_PRV_DATA = 0x5 << 1,
पूर्ण;

क्रमागत blackbird_dma_unit अणु
	BLACKBIRD_DMA_BYTES,
	BLACKBIRD_DMA_FRAMES,
पूर्ण;

क्रमागत blackbird_dma_transfer_status_bits अणु
	BLACKBIRD_DMA_TRANSFER_BITS_DONE = 0x01,
	BLACKBIRD_DMA_TRANSFER_BITS_ERROR = 0x04,
	BLACKBIRD_DMA_TRANSFER_BITS_LL_ERROR = 0x10,
पूर्ण;

क्रमागत blackbird_छोड़ो अणु
	BLACKBIRD_PAUSE_ENCODING,
	BLACKBIRD_RESUME_ENCODING,
पूर्ण;

क्रमागत blackbird_copyright अणु
	BLACKBIRD_COPYRIGHT_OFF,
	BLACKBIRD_COPYRIGHT_ON,
पूर्ण;

क्रमागत blackbird_notअगरication_type अणु
	BLACKBIRD_NOTIFICATION_REFRESH,
पूर्ण;

क्रमागत blackbird_notअगरication_status अणु
	BLACKBIRD_NOTIFICATION_OFF,
	BLACKBIRD_NOTIFICATION_ON,
पूर्ण;

क्रमागत blackbird_notअगरication_mailbox अणु
	BLACKBIRD_NOTIFICATION_NO_MAILBOX = -1,
पूर्ण;

क्रमागत blackbird_field1_lines अणु
	BLACKBIRD_FIELD1_SAA7114 = 0x00EF, /* 239 */
	BLACKBIRD_FIELD1_SAA7115 = 0x00F0, /* 240 */
	BLACKBIRD_FIELD1_MICRONAS = 0x0105, /* 261 */
पूर्ण;

क्रमागत blackbird_field2_lines अणु
	BLACKBIRD_FIELD2_SAA7114 = 0x00EF, /* 239 */
	BLACKBIRD_FIELD2_SAA7115 = 0x00F0, /* 240 */
	BLACKBIRD_FIELD2_MICRONAS = 0x0106, /* 262 */
पूर्ण;

क्रमागत blackbird_custom_data_type अणु
	BLACKBIRD_CUSTOM_EXTENSION_USR_DATA,
	BLACKBIRD_CUSTOM_PRIVATE_PACKET,
पूर्ण;

क्रमागत blackbird_mute अणु
	BLACKBIRD_UNMUTE,
	BLACKBIRD_MUTE,
पूर्ण;

क्रमागत blackbird_mute_video_mask अणु
	BLACKBIRD_MUTE_VIDEO_V_MASK = 0x0000FF00,
	BLACKBIRD_MUTE_VIDEO_U_MASK = 0x00FF0000,
	BLACKBIRD_MUTE_VIDEO_Y_MASK = 0xFF000000,
पूर्ण;

क्रमागत blackbird_mute_video_shअगरt अणु
	BLACKBIRD_MUTE_VIDEO_V_SHIFT = 8,
	BLACKBIRD_MUTE_VIDEO_U_SHIFT = 16,
	BLACKBIRD_MUTE_VIDEO_Y_SHIFT = 24,
पूर्ण;

/* Registers */
#घोषणा IVTV_REG_ENC_SDRAM_REFRESH (0x07F8 /*| IVTV_REG_OFFSET*/)
#घोषणा IVTV_REG_ENC_SDRAM_PRECHARGE (0x07FC /*| IVTV_REG_OFFSET*/)
#घोषणा IVTV_REG_SPU (0x9050 /*| IVTV_REG_OFFSET*/)
#घोषणा IVTV_REG_HW_BLOCKS (0x9054 /*| IVTV_REG_OFFSET*/)
#घोषणा IVTV_REG_VPU (0x9058 /*| IVTV_REG_OFFSET*/)
#घोषणा IVTV_REG_APU (0xA064 /*| IVTV_REG_OFFSET*/)

/* ------------------------------------------------------------------ */

अटल व्योम host_setup(काष्ठा cx88_core *core)
अणु
	/* toggle reset of the host */
	cx_ग_लिखो(MO_GPHST_SOFT_RST, 1);
	udelay(100);
	cx_ग_लिखो(MO_GPHST_SOFT_RST, 0);
	udelay(100);

	/* host port setup */
	cx_ग_लिखो(MO_GPHST_WSC, 0x44444444U);
	cx_ग_लिखो(MO_GPHST_XFR, 0);
	cx_ग_लिखो(MO_GPHST_WDTH, 15);
	cx_ग_लिखो(MO_GPHST_HDSHK, 0);
	cx_ग_लिखो(MO_GPHST_MUX16, 0x44448888U);
	cx_ग_लिखो(MO_GPHST_MODE, 0);
पूर्ण

/* ------------------------------------------------------------------ */

#घोषणा P1_MDATA0 0x390000
#घोषणा P1_MDATA1 0x390001
#घोषणा P1_MDATA2 0x390002
#घोषणा P1_MDATA3 0x390003
#घोषणा P1_MADDR2 0x390004
#घोषणा P1_MADDR1 0x390005
#घोषणा P1_MADDR0 0x390006
#घोषणा P1_RDATA0 0x390008
#घोषणा P1_RDATA1 0x390009
#घोषणा P1_RDATA2 0x39000A
#घोषणा P1_RDATA3 0x39000B
#घोषणा P1_RADDR0 0x39000C
#घोषणा P1_RADDR1 0x39000D
#घोषणा P1_RRDWR  0x39000E

अटल पूर्णांक रुको_पढ़ोy_gpio0_bit1(काष्ठा cx88_core *core, u32 state)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);
	u32 gpio0, need;

	need = state ? 2 : 0;
	क्रम (;;) अणु
		gpio0 = cx_पढ़ो(MO_GP0_IO) & 2;
		अगर (need == gpio0)
			वापस 0;
		अगर (समय_after(jअगरfies, समयout))
			वापस -1;
		udelay(1);
	पूर्ण
पूर्ण

अटल पूर्णांक memory_ग_लिखो(काष्ठा cx88_core *core, u32 address, u32 value)
अणु
	/* Warning: address is dword address (4 bytes) */
	cx_ग_लिखोb(P1_MDATA0, (अचिन्हित पूर्णांक)value);
	cx_ग_लिखोb(P1_MDATA1, (अचिन्हित पूर्णांक)(value >> 8));
	cx_ग_लिखोb(P1_MDATA2, (अचिन्हित पूर्णांक)(value >> 16));
	cx_ग_लिखोb(P1_MDATA3, (अचिन्हित पूर्णांक)(value >> 24));
	cx_ग_लिखोb(P1_MADDR2, (अचिन्हित पूर्णांक)(address >> 16) | 0x40);
	cx_ग_लिखोb(P1_MADDR1, (अचिन्हित पूर्णांक)(address >> 8));
	cx_ग_लिखोb(P1_MADDR0, (अचिन्हित पूर्णांक)address);
	cx_पढ़ो(P1_MDATA0);
	cx_पढ़ो(P1_MADDR0);

	वापस रुको_पढ़ोy_gpio0_bit1(core, 1);
पूर्ण

अटल पूर्णांक memory_पढ़ो(काष्ठा cx88_core *core, u32 address, u32 *value)
अणु
	पूर्णांक retval;
	u32 val;

	/* Warning: address is dword address (4 bytes) */
	cx_ग_लिखोb(P1_MADDR2, (अचिन्हित पूर्णांक)(address >> 16) & ~0xC0);
	cx_ग_लिखोb(P1_MADDR1, (अचिन्हित पूर्णांक)(address >> 8));
	cx_ग_लिखोb(P1_MADDR0, (अचिन्हित पूर्णांक)address);
	cx_पढ़ो(P1_MADDR0);

	retval = रुको_पढ़ोy_gpio0_bit1(core, 1);

	cx_ग_लिखोb(P1_MDATA3, 0);
	val     = (अचिन्हित अक्षर)cx_पढ़ो(P1_MDATA3) << 24;
	cx_ग_लिखोb(P1_MDATA2, 0);
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_MDATA2) << 16;
	cx_ग_लिखोb(P1_MDATA1, 0);
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_MDATA1) << 8;
	cx_ग_लिखोb(P1_MDATA0, 0);
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_MDATA0);

	*value  = val;
	वापस retval;
पूर्ण

अटल पूर्णांक रेजिस्टर_ग_लिखो(काष्ठा cx88_core *core, u32 address, u32 value)
अणु
	cx_ग_लिखोb(P1_RDATA0, (अचिन्हित पूर्णांक)value);
	cx_ग_लिखोb(P1_RDATA1, (अचिन्हित पूर्णांक)(value >> 8));
	cx_ग_लिखोb(P1_RDATA2, (अचिन्हित पूर्णांक)(value >> 16));
	cx_ग_लिखोb(P1_RDATA3, (अचिन्हित पूर्णांक)(value >> 24));
	cx_ग_लिखोb(P1_RADDR0, (अचिन्हित पूर्णांक)address);
	cx_ग_लिखोb(P1_RADDR1, (अचिन्हित पूर्णांक)(address >> 8));
	cx_ग_लिखोb(P1_RRDWR, 1);
	cx_पढ़ो(P1_RDATA0);
	cx_पढ़ो(P1_RADDR0);

	वापस रुको_पढ़ोy_gpio0_bit1(core, 1);
पूर्ण

अटल पूर्णांक रेजिस्टर_पढ़ो(काष्ठा cx88_core *core, u32 address, u32 *value)
अणु
	पूर्णांक retval;
	u32 val;

	cx_ग_लिखोb(P1_RADDR0, (अचिन्हित पूर्णांक)address);
	cx_ग_लिखोb(P1_RADDR1, (अचिन्हित पूर्णांक)(address >> 8));
	cx_ग_लिखोb(P1_RRDWR, 0);
	cx_पढ़ो(P1_RADDR0);

	retval  = रुको_पढ़ोy_gpio0_bit1(core, 1);
	val     = (अचिन्हित अक्षर)cx_पढ़ो(P1_RDATA0);
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_RDATA1) << 8;
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_RDATA2) << 16;
	val    |= (अचिन्हित अक्षर)cx_पढ़ो(P1_RDATA3) << 24;

	*value  = val;
	वापस retval;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक blackbird_mbox_func(व्योम *priv, u32 command, पूर्णांक in,
			       पूर्णांक out, u32 data[CX2341X_MBOX_MAX_DATA])
अणु
	काष्ठा cx8802_dev *dev = priv;
	अचिन्हित दीर्घ समयout;
	u32 value, flag, retval;
	पूर्णांक i;

	dprपूर्णांकk(1, "%s: 0x%X\n", __func__, command);

	/*
	 * this may not be 100% safe अगर we can't पढ़ो any memory location
	 * without side effects
	 */
	memory_पढ़ो(dev->core, dev->mailbox - 4, &value);
	अगर (value != 0x12345678) अणु
		dprपूर्णांकk(0,
			"Firmware and/or mailbox pointer not initialized or corrupted\n");
		वापस -EIO;
	पूर्ण

	memory_पढ़ो(dev->core, dev->mailbox, &flag);
	अगर (flag) अणु
		dprपूर्णांकk(0, "ERROR: Mailbox appears to be in use (%x)\n", flag);
		वापस -EIO;
	पूर्ण

	flag |= 1; /* tell 'em we're working on it */
	memory_ग_लिखो(dev->core, dev->mailbox, flag);

	/* ग_लिखो command + args + fill reमुख्यing with zeros */
	memory_ग_लिखो(dev->core, dev->mailbox + 1, command); /* command code */
	/* समयout */
	memory_ग_लिखो(dev->core, dev->mailbox + 3, IVTV_API_STD_TIMEOUT);
	क्रम (i = 0; i < in; i++) अणु
		memory_ग_लिखो(dev->core, dev->mailbox + 4 + i, data[i]);
		dprपूर्णांकk(1, "API Input %d = %d\n", i, data[i]);
	पूर्ण
	क्रम (; i < CX2341X_MBOX_MAX_DATA; i++)
		memory_ग_लिखो(dev->core, dev->mailbox + 4 + i, 0);

	flag |= 3; /* tell 'em we're करोne writing */
	memory_ग_लिखो(dev->core, dev->mailbox, flag);

	/* रुको क्रम firmware to handle the API command */
	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	क्रम (;;) अणु
		memory_पढ़ो(dev->core, dev->mailbox, &flag);
		अगर (0 != (flag & 4))
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			dprपूर्णांकk(0, "ERROR: API Mailbox timeout %x\n", command);
			वापस -EIO;
		पूर्ण
		udelay(10);
	पूर्ण

	/* पढ़ो output values */
	क्रम (i = 0; i < out; i++) अणु
		memory_पढ़ो(dev->core, dev->mailbox + 4 + i, data + i);
		dprपूर्णांकk(1, "API Output %d = %d\n", i, data[i]);
	पूर्ण

	memory_पढ़ो(dev->core, dev->mailbox + 2, &retval);
	dprपूर्णांकk(1, "API result = %d\n", retval);

	flag = 0;
	memory_ग_लिखो(dev->core, dev->mailbox, flag);
	वापस retval;
पूर्ण

/* ------------------------------------------------------------------ */

/*
 * We करोn't need to call the API often, so using just one mailbox
 * will probably suffice
 */
अटल पूर्णांक blackbird_api_cmd(काष्ठा cx8802_dev *dev, u32 command,
			     u32 inअ_दोnt, u32 outअ_दोnt, ...)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	बहु_सूची vargs;
	पूर्णांक i, err;

	बहु_शुरू(vargs, outअ_दोnt);

	क्रम (i = 0; i < inअ_दोnt; i++)
		data[i] = बहु_तर्क(vargs, पूर्णांक);

	err = blackbird_mbox_func(dev, command, inअ_दोnt, outअ_दोnt, data);
	क्रम (i = 0; i < outअ_दोnt; i++) अणु
		पूर्णांक *vptr = बहु_तर्क(vargs, पूर्णांक *);
		*vptr = data[i];
	पूर्ण
	बहु_पूर्ण(vargs);
	वापस err;
पूर्ण

अटल पूर्णांक blackbird_find_mailbox(काष्ठा cx8802_dev *dev)
अणु
	u32 signature[4] = अणु0x12345678, 0x34567812, 0x56781234, 0x78123456पूर्ण;
	पूर्णांक signaturecnt = 0;
	u32 value;
	पूर्णांक i;

	क्रम (i = 0; i < BLACKBIRD_FIRM_IMAGE_SIZE; i++) अणु
		memory_पढ़ो(dev->core, i, &value);
		अगर (value == signature[signaturecnt])
			signaturecnt++;
		अन्यथा
			signaturecnt = 0;
		अगर (signaturecnt == 4) अणु
			dprपूर्णांकk(1, "Mailbox signature found\n");
			वापस i + 1;
		पूर्ण
	पूर्ण
	dprपूर्णांकk(0, "Mailbox signature values not found!\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक blackbird_load_firmware(काष्ठा cx8802_dev *dev)
अणु
	अटल स्थिर अचिन्हित अक्षर magic[8] = अणु
		0xa7, 0x0d, 0x00, 0x00, 0x66, 0xbb, 0x55, 0xaa
	पूर्ण;
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक i, retval = 0;
	u32 value = 0;
	u32 checksum = 0;
	__le32 *dataptr;

	retval  = रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_VPU, 0xFFFFFFED);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_HW_BLOCKS,
				 IVTV_CMD_HW_BLOCKS_RST);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_ENC_SDRAM_REFRESH,
				 0x80000640);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_ENC_SDRAM_PRECHARGE,
				 0x1A);
	usleep_range(10000, 20000);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_APU, 0);

	अगर (retval < 0)
		dprपूर्णांकk(0, "Error with register_write\n");

	retval = request_firmware(&firmware, CX2341X_FIRM_ENC_खाताNAME,
				  &dev->pci->dev);

	अगर (retval != 0) अणु
		pr_err("Hotplug firmware request failed (%s).\n",
		       CX2341X_FIRM_ENC_खाताNAME);
		pr_err("Please fix your hotplug setup, the board will not work without firmware loaded!\n");
		वापस -EIO;
	पूर्ण

	अगर (firmware->size != BLACKBIRD_FIRM_IMAGE_SIZE) अणु
		pr_err("Firmware size mismatch (have %zd, expected %d)\n",
		       firmware->size, BLACKBIRD_FIRM_IMAGE_SIZE);
		release_firmware(firmware);
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(firmware->data, magic, 8) != 0) अणु
		pr_err("Firmware magic mismatch, wrong file?\n");
		release_firmware(firmware);
		वापस -EINVAL;
	पूर्ण

	/* transfer to the chip */
	dprपूर्णांकk(1, "Loading firmware ...\n");
	dataptr = (__le32 *)firmware->data;
	क्रम (i = 0; i < (firmware->size >> 2); i++) अणु
		value = le32_to_cpu(*dataptr);
		checksum += ~value;
		memory_ग_लिखो(dev->core, i, value);
		dataptr++;
	पूर्ण

	/* पढ़ो back to verअगरy with the checksum */
	क्रम (i--; i >= 0; i--) अणु
		memory_पढ़ो(dev->core, i, &value);
		checksum -= ~value;
	पूर्ण
	release_firmware(firmware);
	अगर (checksum) अणु
		pr_err("Firmware load might have failed (checksum mismatch).\n");
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(0, "Firmware upload successful.\n");

	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_HW_BLOCKS,
				 IVTV_CMD_HW_BLOCKS_RST);
	retval |= रेजिस्टर_पढ़ो(dev->core, IVTV_REG_SPU, &value);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_SPU, value & 0xFFFFFFFE);
	usleep_range(10000, 20000);

	retval |= रेजिस्टर_पढ़ो(dev->core, IVTV_REG_VPU, &value);
	retval |= रेजिस्टर_ग_लिखो(dev->core, IVTV_REG_VPU, value & 0xFFFFFFE8);

	अगर (retval < 0)
		dprपूर्णांकk(0, "Error with register_write\n");
	वापस 0;
पूर्ण

/*
 * Settings used by the winकरोws tv app क्रम PVR2000:
 * =================================================================================================================
 * Profile | Codec | Resolution | CBR/VBR | Video Qlty   | V. Bitrate | Frmrate | Audio Codec | A. Bitrate | A. Mode
 * -----------------------------------------------------------------------------------------------------------------
 * MPEG-1  | MPEG1 | 352x288PAL | (CBR)   | 1000:Optimal | 2000 Kbps  | 25fps   | MPG1 Layer2 | 224kbps    | Stereo
 * MPEG-2  | MPEG2 | 720x576PAL | VBR     | 600 :Good    | 4000 Kbps  | 25fps   | MPG1 Layer2 | 224kbps    | Stereo
 * VCD     | MPEG1 | 352x288PAL | (CBR)   | 1000:Optimal | 1150 Kbps  | 25fps   | MPG1 Layer2 | 224kbps    | Stereo
 * DVD     | MPEG2 | 720x576PAL | VBR     | 600 :Good    | 6000 Kbps  | 25fps   | MPG1 Layer2 | 224kbps    | Stereo
 * DB* DVD | MPEG2 | 720x576PAL | CBR     | 600 :Good    | 6000 Kbps  | 25fps   | MPG1 Layer2 | 224kbps    | Stereo
 * =================================================================================================================
 * [*] DB: "DirectBurn"
 */

अटल व्योम blackbird_codec_settings(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;

	/* assign frame size */
	blackbird_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
			  core->height, core->width);

	dev->cxhdl.width = core->width;
	dev->cxhdl.height = core->height;
	cx2341x_handler_set_50hz(&dev->cxhdl,
				 dev->core->tvnorm & V4L2_STD_625_50);
	cx2341x_handler_setup(&dev->cxhdl);
पूर्ण

अटल पूर्णांक blackbird_initialize_codec(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	पूर्णांक version;
	पूर्णांक retval;

	dprपूर्णांकk(1, "Initialize codec\n");
	retval = blackbird_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0); /* ping */
	अगर (retval < 0) अणु
		/* ping was not successful, reset and upload firmware */
		cx_ग_लिखो(MO_SRST_IO, 0); /* SYS_RSTO=0 */
		cx_ग_लिखो(MO_SRST_IO, 1); /* SYS_RSTO=1 */
		retval = blackbird_load_firmware(dev);
		अगर (retval < 0)
			वापस retval;

		retval = blackbird_find_mailbox(dev);
		अगर (retval < 0)
			वापस -1;

		dev->mailbox = retval;

		/* ping */
		retval = blackbird_api_cmd(dev, CX2341X_ENC_PING_FW, 0, 0);
		अगर (retval < 0) अणु
			dprपूर्णांकk(0, "ERROR: Firmware ping failed!\n");
			वापस -1;
		पूर्ण

		retval = blackbird_api_cmd(dev, CX2341X_ENC_GET_VERSION,
					   0, 1, &version);
		अगर (retval < 0) अणु
			dprपूर्णांकk(0,
				"ERROR: Firmware get encoder version failed!\n");
			वापस -1;
		पूर्ण
		dprपूर्णांकk(0, "Firmware version is 0x%08x\n", version);
	पूर्ण

	cx_ग_लिखो(MO_PINMUX_IO, 0x88); /* 656-8bit IO and enable MPEG parallel IO */
	cx_clear(MO_INPUT_FORMAT, 0x100); /* chroma subcarrier lock to normal? */
	cx_ग_लिखो(MO_VBOS_CONTROL, 0x84A00); /* no 656 mode, 8-bit pixels, disable VBI */
	cx_clear(MO_OUTPUT_FORMAT, 0x0008); /* Normal Y-limits to let the mpeg encoder sync */

	blackbird_codec_settings(dev);

	blackbird_api_cmd(dev, CX2341X_ENC_SET_NUM_VSYNC_LINES, 2, 0,
			  BLACKBIRD_FIELD1_SAA7115, BLACKBIRD_FIELD2_SAA7115);

	blackbird_api_cmd(dev, CX2341X_ENC_SET_PLACEHOLDER, 12, 0,
			  BLACKBIRD_CUSTOM_EXTENSION_USR_DATA,
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक blackbird_start_codec(काष्ठा cx8802_dev *dev)
अणु
	काष्ठा cx88_core *core = dev->core;
	/* start capturing to the host पूर्णांकerface */
	u32 reg;

	पूर्णांक i;
	पूर्णांक lastchange = -1;
	पूर्णांक lastval = 0;

	क्रम (i = 0; (i < 10) && (i < (lastchange + 4)); i++) अणु
		reg = cx_पढ़ो(AUD_STATUS);

		dprपूर्णांकk(1, "AUD_STATUS:%dL: 0x%x\n", i, reg);
		अगर ((reg & 0x0F) != lastval) अणु
			lastval = reg & 0x0F;
			lastchange = i;
		पूर्ण
		msleep(100);
	पूर्ण

	/* unmute audio source */
	cx_clear(AUD_VOL_CTL, (1 << 6));

	blackbird_api_cmd(dev, CX2341X_ENC_REFRESH_INPUT, 0, 0);

	/* initialize the video input */
	blackbird_api_cmd(dev, CX2341X_ENC_INITIALIZE_INPUT, 0, 0);

	cx2341x_handler_set_busy(&dev->cxhdl, 1);

	/* start capturing to the host पूर्णांकerface */
	blackbird_api_cmd(dev, CX2341X_ENC_START_CAPTURE, 2, 0,
			  BLACKBIRD_MPEG_CAPTURE, BLACKBIRD_RAW_BITS_NONE);

	वापस 0;
पूर्ण

अटल पूर्णांक blackbird_stop_codec(काष्ठा cx8802_dev *dev)
अणु
	blackbird_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			  BLACKBIRD_END_NOW,
			  BLACKBIRD_MPEG_CAPTURE,
			  BLACKBIRD_RAW_BITS_NONE);

	cx2341x_handler_set_busy(&dev->cxhdl, 0);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;

	*num_planes = 1;
	dev->ts_packet_size  = 188 * 4;
	dev->ts_packet_count  = 32;
	sizes[0] = dev->ts_packet_size * dev->ts_packet_count;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);

	वापस cx8802_buf_prepare(vb->vb2_queue, dev, buf);
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);
	काष्ठा cx88_riscmem *risc = &buf->risc;

	अगर (risc->cpu)
		pci_मुक्त_consistent(dev->pci, risc->size, risc->cpu, risc->dma);
	स_रखो(risc, 0, माप(*risc));
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx8802_dev *dev = vb->vb2_queue->drv_priv;
	काष्ठा cx88_buffer    *buf = container_of(vbuf, काष्ठा cx88_buffer, vb);

	cx8802_buf_queue(dev, buf);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->mpegq;
	काष्ठा cx8802_driver *drv;
	काष्ठा cx88_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/* Make sure we can acquire the hardware */
	drv = cx8802_get_driver(dev, CX88_MPEG_BLACKBIRD);
	अगर (!drv) अणु
		dprपूर्णांकk(1, "%s: blackbird driver is not loaded\n", __func__);
		err = -ENODEV;
		जाओ fail;
	पूर्ण

	err = drv->request_acquire(drv);
	अगर (err != 0) अणु
		dprपूर्णांकk(1, "%s: Unable to acquire hardware, %d\n", __func__,
			err);
		जाओ fail;
	पूर्ण

	अगर (blackbird_initialize_codec(dev) < 0) अणु
		drv->request_release(drv);
		err = -EINVAL;
		जाओ fail;
	पूर्ण

	err = blackbird_start_codec(dev);
	अगर (err == 0) अणु
		buf = list_entry(dmaq->active.next, काष्ठा cx88_buffer, list);
		cx8802_start_dma(dev, dmaq, buf);
		वापस 0;
	पूर्ण

fail:
	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
	वापस err;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx8802_dev *dev = q->drv_priv;
	काष्ठा cx88_dmaqueue *dmaq = &dev->mpegq;
	काष्ठा cx8802_driver *drv = शून्य;
	अचिन्हित दीर्घ flags;

	cx8802_cancel_buffers(dev);
	blackbird_stop_codec(dev);

	/* Make sure we release the hardware */
	drv = cx8802_get_driver(dev, CX88_MPEG_BLACKBIRD);
	WARN_ON(!drv);
	अगर (drv)
		drv->request_release(drv);

	spin_lock_irqsave(&dev->slock, flags);
	जबतक (!list_empty(&dmaq->active)) अणु
		काष्ठा cx88_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx88_buffer, list);

		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops blackbird_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	strscpy(cap->driver, "cx88_blackbird", माप(cap->driver));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	वापस cx88_querycap(file, core, cap);
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
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.width        = core->width;
	f->fmt.pix.height       = core->height;
	f->fmt.pix.field        = core->field;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	अचिन्हित पूर्णांक maxw, maxh;
	क्रमागत v4l2_field field;

	f->fmt.pix.pixelक्रमmat  = V4L2_PIX_FMT_MPEG;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage    = dev->ts_packet_size * dev->ts_packet_count;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	maxw = norm_maxw(core->tvnorm);
	maxh = norm_maxh(core->tvnorm);

	field = f->fmt.pix.field;

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_SEQ_TB:
		अवरोध;
	शेष:
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		अवरोध;
	पूर्ण
	अगर (V4L2_FIELD_HAS_T_OR_B(field))
		maxh /= 2;

	v4l_bound_align_image(&f->fmt.pix.width, 48, maxw, 2,
			      &f->fmt.pix.height, 32, maxh, 0, 0);
	f->fmt.pix.field = field;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core  *core = dev->core;

	अगर (vb2_is_busy(&dev->vb2_mpegq))
		वापस -EBUSY;
	अगर (core->v4ldev && (vb2_is_busy(&core->v4ldev->vb2_vidq) ||
			     vb2_is_busy(&core->v4ldev->vb2_vbiq)))
		वापस -EBUSY;
	vidioc_try_fmt_vid_cap(file, priv, f);
	core->width = f->fmt.pix.width;
	core->height = f->fmt.pix.height;
	core->field = f->fmt.pix.field;
	cx88_set_scale(core, f->fmt.pix.width, f->fmt.pix.height,
		       f->fmt.pix.field);
	blackbird_api_cmd(dev, CX2341X_ENC_SET_FRAME_SIZE, 2, 0,
			  f->fmt.pix.height, f->fmt.pix.width);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	bool streaming;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (unlikely(f->tuner != 0))
		वापस -EINVAL;
	streaming = vb2_start_streaming_called(&dev->vb2_mpegq);
	अगर (streaming)
		blackbird_stop_codec(dev);

	cx88_set_freq(core, f);
	blackbird_initialize_codec(dev);
	cx88_set_scale(core, core->width, core->height, core->field);
	अगर (streaming)
		blackbird_start_codec(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	अक्षर name[32 + 2];

	snम_लिखो(name, माप(name), "%s/2", core->name);
	call_all(core, core, log_status);
	v4l2_ctrl_handler_log_status(&dev->cxhdl.hdl, name);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	वापस cx88_क्रमागत_input(core, i);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (unlikely(f->tuner != 0))
		वापस -EINVAL;

	f->frequency = core->freq;
	call_all(core, tuner, g_frequency, f);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	*i = core->input;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (i >= 4)
		वापस -EINVAL;
	अगर (!INPUT(i).type)
		वापस -EINVAL;

	cx88_newstation(core);
	cx88_video_mux(core, i);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;
	u32 reg;

	अगर (unlikely(core->board.tuner_type == UNSET))
		वापस -EINVAL;
	अगर (t->index != 0)
		वापस -EINVAL;

	strscpy(t->name, "Television", माप(t->name));
	t->capability = V4L2_TUNER_CAP_NORM;
	t->rangehigh  = 0xffffffffUL;
	call_all(core, tuner, g_tuner, t);

	cx88_get_stereo(core, t);
	reg = cx_पढ़ो(MO_DEVICE_STATUS);
	t->संकेत = (reg & (1 << 5)) ? 0xffff : 0x0000;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
			  स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	अगर (core->board.tuner_type == UNSET)
		वापस -EINVAL;
	अगर (t->index != 0)
		वापस -EINVAL;

	cx88_set_stereo(core, t->audmode, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *tvnorm)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	*tvnorm = core->tvnorm;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा cx8802_dev *dev = video_drvdata(file);
	काष्ठा cx88_core *core = dev->core;

	वापस cx88_set_tvnorm(core, id);
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
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap  = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap   = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs       = vb2_ioctl_reqbufs,
	.vidioc_querybuf      = vb2_ioctl_querybuf,
	.vidioc_qbuf          = vb2_ioctl_qbuf,
	.vidioc_dqbuf         = vb2_ioctl_dqbuf,
	.vidioc_streamon      = vb2_ioctl_streamon,
	.vidioc_streamoff     = vb2_ioctl_streamoff,
	.vidioc_s_frequency   = vidioc_s_frequency,
	.vidioc_log_status    = vidioc_log_status,
	.vidioc_क्रमागत_input    = vidioc_क्रमागत_input,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_g_input       = vidioc_g_input,
	.vidioc_s_input       = vidioc_s_input,
	.vidioc_g_tuner       = vidioc_g_tuner,
	.vidioc_s_tuner       = vidioc_s_tuner,
	.vidioc_g_std         = vidioc_g_std,
	.vidioc_s_std         = vidioc_s_std,
	.vidioc_subscribe_event      = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event    = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device cx8802_mpeg_ढाँचा = अणु
	.name                 = "cx8802",
	.fops                 = &mpeg_fops,
	.ioctl_ops	      = &mpeg_ioctl_ops,
	.tvnorms              = CX88_NORMS,
पूर्ण;

/* ------------------------------------------------------------------ */

/* The CX8802 MPEG API will call this when we can use the hardware */
अटल पूर्णांक cx8802_blackbird_advise_acquire(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	पूर्णांक err = 0;

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		/*
		 * By शेष, core setup will leave the cx22702 out of reset,
		 * on the bus.
		 * We left the hardware on घातer up with the cx22702 active.
		 * We're being given access to re-arrange the GPIOs.
		 * Take the bus off the cx22702 and put the cx23416 on it.
		 */
		/* Toggle reset on cx22702 leaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000080);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		/* tri-state the cx22702 pins */
		cx_set(MO_GP0_IO, 0x00000004);
		udelay(1000);
		अवरोध;
	शेष:
		err = -ENODEV;
	पूर्ण
	वापस err;
पूर्ण

/* The CX8802 MPEG API will call this when we need to release the hardware */
अटल पूर्णांक cx8802_blackbird_advise_release(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	पूर्णांक err = 0;

	चयन (core->boardnr) अणु
	हाल CX88_BOARD_HAUPPAUGE_HVR1300:
		/* Exit leaving the cx23416 on the bus */
		अवरोध;
	शेष:
		err = -ENODEV;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम blackbird_unरेजिस्टर_video(काष्ठा cx8802_dev *dev)
अणु
	video_unरेजिस्टर_device(&dev->mpeg_dev);
पूर्ण

अटल पूर्णांक blackbird_रेजिस्टर_video(काष्ठा cx8802_dev *dev)
अणु
	पूर्णांक err;

	cx88_vdev_init(dev->core, dev->pci, &dev->mpeg_dev,
		       &cx8802_mpeg_ढाँचा, "mpeg");
	dev->mpeg_dev.ctrl_handler = &dev->cxhdl.hdl;
	video_set_drvdata(&dev->mpeg_dev, dev);
	dev->mpeg_dev.queue = &dev->vb2_mpegq;
	dev->mpeg_dev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				    V4L2_CAP_VIDEO_CAPTURE;
	अगर (dev->core->board.tuner_type != UNSET)
		dev->mpeg_dev.device_caps |= V4L2_CAP_TUNER;
	err = video_रेजिस्टर_device(&dev->mpeg_dev, VFL_TYPE_VIDEO, -1);
	अगर (err < 0) अणु
		pr_info("can't register mpeg device\n");
		वापस err;
	पूर्ण
	pr_info("registered device %s [mpeg]\n",
		video_device_node_name(&dev->mpeg_dev));
	वापस 0;
पूर्ण

/* ----------------------------------------------------------- */

अटल पूर्णांक cx8802_blackbird_probe(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	काष्ठा cx8802_dev *dev = core->dvbdev;
	काष्ठा vb2_queue *q;
	पूर्णांक err;

	dprपूर्णांकk(1, "%s\n", __func__);
	dprपूर्णांकk(1, " ->being probed by Card=%d Name=%s, PCI %02x:%02x\n",
		core->boardnr,
		core->name,
		core->pci_bus,
		core->pci_slot);

	err = -ENODEV;
	अगर (!(core->board.mpeg & CX88_MPEG_BLACKBIRD))
		जाओ fail_core;

	dev->cxhdl.port = CX2341X_PORT_STREAMING;
	dev->cxhdl.width = core->width;
	dev->cxhdl.height = core->height;
	dev->cxhdl.func = blackbird_mbox_func;
	dev->cxhdl.priv = dev;
	err = cx2341x_handler_init(&dev->cxhdl, 36);
	अगर (err)
		जाओ fail_core;
	v4l2_ctrl_add_handler(&dev->cxhdl.hdl, &core->video_hdl, शून्य, false);

	/* blackbird stuff */
	pr_info("cx23416 based mpeg encoder (blackbird reference design)\n");
	host_setup(dev->core);

	blackbird_initialize_codec(dev);

	/* initial device configuration: needed ? */
//	init_controls(core);
	cx88_set_tvnorm(core, core->tvnorm);
	cx88_video_mux(core, 0);
	cx2341x_handler_set_50hz(&dev->cxhdl, core->height == 576);
	cx2341x_handler_setup(&dev->cxhdl);

	q = &dev->vb2_mpegq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
	q->gfp_flags = GFP_DMA32;
	q->min_buffers_needed = 2;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा cx88_buffer);
	q->ops = &blackbird_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &core->lock;
	q->dev = &dev->pci->dev;

	err = vb2_queue_init(q);
	अगर (err < 0)
		जाओ fail_core;

	blackbird_रेजिस्टर_video(dev);

	वापस 0;

fail_core:
	वापस err;
पूर्ण

अटल पूर्णांक cx8802_blackbird_हटाओ(काष्ठा cx8802_driver *drv)
अणु
	काष्ठा cx88_core *core = drv->core;
	काष्ठा cx8802_dev *dev = core->dvbdev;

	/* blackbird */
	blackbird_unरेजिस्टर_video(drv->core->dvbdev);
	v4l2_ctrl_handler_मुक्त(&dev->cxhdl.hdl);

	वापस 0;
पूर्ण

अटल काष्ठा cx8802_driver cx8802_blackbird_driver = अणु
	.type_id	= CX88_MPEG_BLACKBIRD,
	.hw_access	= CX8802_DRVCTL_SHARED,
	.probe		= cx8802_blackbird_probe,
	.हटाओ		= cx8802_blackbird_हटाओ,
	.advise_acquire	= cx8802_blackbird_advise_acquire,
	.advise_release	= cx8802_blackbird_advise_release,
पूर्ण;

अटल पूर्णांक __init blackbird_init(व्योम)
अणु
	pr_info("cx2388x blackbird driver version %s loaded\n",
		CX88_VERSION);
	वापस cx8802_रेजिस्टर_driver(&cx8802_blackbird_driver);
पूर्ण

अटल व्योम __निकास blackbird_fini(व्योम)
अणु
	cx8802_unरेजिस्टर_driver(&cx8802_blackbird_driver);
पूर्ण

module_init(blackbird_init);
module_निकास(blackbird_fini);
