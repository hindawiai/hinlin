<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SQ930x subdriver
 *
 * Copyright (C) 2010 Jean-Franथईois Moine <http://moinejf.मुक्त.fr>
 * Copyright (C) 2006 -2008 Gerard Klaver <gerard at gkall करोt hobby करोt nl>
 * Copyright (C) 2007 Sam Revitch <samr7@cs.washington.edu>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "sq930x"

#समावेश "gspca.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>\n"
		"Gerard Klaver <gerard at gkall dot hobby dot nl\n"
		"Sam Revitch <samr7@cs.washington.edu>");
MODULE_DESCRIPTION("GSPCA/SQ930x USB Camera Driver");
MODULE_LICENSE("GPL");

/* Structure to hold all of our device specअगरic stuff */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा अणु /* exposure/gain control cluster */
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;

	u8 करो_ctrl;
	u8 gpio[2];
	u8 sensor;
	u8 type;
#घोषणा Generic 0
#घोषणा Creative_live_motion 1
पूर्ण;
क्रमागत sensors अणु
	SENSOR_ICX098BQ,
	SENSOR_LZ24BP,
	SENSOR_MI0360,
	SENSOR_MT9V111,		/* = MI360SOC */
	SENSOR_OV7660,
	SENSOR_OV9630,
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_SRGGB8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_SRGGB8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
पूर्ण;

/* sq930x रेजिस्टरs */
#घोषणा SQ930_CTRL_UCBUS_IO	0x0001
#घोषणा SQ930_CTRL_I2C_IO	0x0002
#घोषणा SQ930_CTRL_GPIO		0x0005
#घोषणा SQ930_CTRL_CAP_START	0x0010
#घोषणा SQ930_CTRL_CAP_STOP	0x0011
#घोषणा SQ930_CTRL_SET_EXPOSURE 0x001d
#घोषणा SQ930_CTRL_RESET	0x001e
#घोषणा SQ930_CTRL_GET_DEV_INFO 0x001f

/* gpio 1 (8..15) */
#घोषणा SQ930_GPIO_DFL_I2C_SDA	0x0001
#घोषणा SQ930_GPIO_DFL_I2C_SCL	0x0002
#घोषणा SQ930_GPIO_RSTBAR	0x0004
#घोषणा SQ930_GPIO_EXTRA1	0x0040
#घोषणा SQ930_GPIO_EXTRA2	0x0080
/* gpio 3 (24..31) */
#घोषणा SQ930_GPIO_POWER	0x0200
#घोषणा SQ930_GPIO_DFL_LED	0x1000

काष्ठा ucbus_ग_लिखो_cmd अणु
	u16	bw_addr;
	u8	bw_data;
पूर्ण;
काष्ठा i2c_ग_लिखो_cmd अणु
	u8	reg;
	u16	val;
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd icx098bq_start_0[] = अणु
	अणु0x0354, 0x00पूर्ण, अणु0x03fa, 0x00पूर्ण, अणु0xf800, 0x02पूर्ण, अणु0xf801, 0xceपूर्ण,
	अणु0xf802, 0xc1पूर्ण, अणु0xf804, 0x00पूर्ण, अणु0xf808, 0x00पूर्ण, अणु0xf809, 0x0eपूर्ण,
	अणु0xf80a, 0x01पूर्ण, अणु0xf80b, 0xeeपूर्ण, अणु0xf807, 0x60पूर्ण, अणु0xf80c, 0x02पूर्ण,
	अणु0xf80d, 0xf0पूर्ण, अणु0xf80e, 0x03पूर्ण, अणु0xf80f, 0x0aपूर्ण, अणु0xf81c, 0x02पूर्ण,
	अणु0xf81d, 0xf0पूर्ण, अणु0xf81e, 0x03पूर्ण, अणु0xf81f, 0x0aपूर्ण, अणु0xf83a, 0x00पूर्ण,
	अणु0xf83b, 0x10पूर्ण, अणु0xf83c, 0x00पूर्ण, अणु0xf83d, 0x4eपूर्ण, अणु0xf810, 0x04पूर्ण,
	अणु0xf811, 0x00पूर्ण, अणु0xf812, 0x02पूर्ण, अणु0xf813, 0x10पूर्ण, अणु0xf803, 0x00पूर्ण,
	अणु0xf814, 0x01पूर्ण, अणु0xf815, 0x18पूर्ण, अणु0xf816, 0x00पूर्ण, अणु0xf817, 0x48पूर्ण,
	अणु0xf818, 0x00पूर्ण, अणु0xf819, 0x25पूर्ण, अणु0xf81a, 0x00पूर्ण, अणु0xf81b, 0x3cपूर्ण,
	अणु0xf82f, 0x03पूर्ण, अणु0xf820, 0xffपूर्ण, अणु0xf821, 0x0dपूर्ण, अणु0xf822, 0xffपूर्ण,
	अणु0xf823, 0x07पूर्ण, अणु0xf824, 0xffपूर्ण, अणु0xf825, 0x03पूर्ण, अणु0xf826, 0xffपूर्ण,
	अणु0xf827, 0x06पूर्ण, अणु0xf828, 0xffपूर्ण, अणु0xf829, 0x03पूर्ण, अणु0xf82a, 0xffपूर्ण,
	अणु0xf82b, 0x0cपूर्ण, अणु0xf82c, 0xfdपूर्ण, अणु0xf82d, 0x01पूर्ण, अणु0xf82e, 0x00पूर्ण,
	अणु0xf830, 0x00पूर्ण, अणु0xf831, 0x47पूर्ण, अणु0xf832, 0x00पूर्ण, अणु0xf833, 0x00पूर्ण,
	अणु0xf850, 0x00पूर्ण, अणु0xf851, 0x00पूर्ण, अणु0xf852, 0x00पूर्ण, अणु0xf853, 0x24पूर्ण,
	अणु0xf854, 0x00पूर्ण, अणु0xf855, 0x18पूर्ण, अणु0xf856, 0x00पूर्ण, अणु0xf857, 0x3cपूर्ण,
	अणु0xf858, 0x00पूर्ण, अणु0xf859, 0x0cपूर्ण, अणु0xf85a, 0x00पूर्ण, अणु0xf85b, 0x30पूर्ण,
	अणु0xf85c, 0x00पूर्ण, अणु0xf85d, 0x0cपूर्ण, अणु0xf85e, 0x00पूर्ण, अणु0xf85f, 0x30पूर्ण,
	अणु0xf860, 0x00पूर्ण, अणु0xf861, 0x48पूर्ण, अणु0xf862, 0x01पूर्ण, अणु0xf863, 0xdcपूर्ण,
	अणु0xf864, 0xffपूर्ण, अणु0xf865, 0x98पूर्ण, अणु0xf866, 0xffपूर्ण, अणु0xf867, 0xc0पूर्ण,
	अणु0xf868, 0xffपूर्ण, अणु0xf869, 0x70पूर्ण, अणु0xf86c, 0xffपूर्ण, अणु0xf86d, 0x00पूर्ण,
	अणु0xf86a, 0xffपूर्ण, अणु0xf86b, 0x48पूर्ण, अणु0xf86e, 0xffपूर्ण, अणु0xf86f, 0x00पूर्ण,
	अणु0xf870, 0x01पूर्ण, अणु0xf871, 0xdbपूर्ण, अणु0xf872, 0x01पूर्ण, अणु0xf873, 0xfaपूर्ण,
	अणु0xf874, 0x01पूर्ण, अणु0xf875, 0xdbपूर्ण, अणु0xf876, 0x01पूर्ण, अणु0xf877, 0xfaपूर्ण,
	अणु0xf878, 0x0fपूर्ण, अणु0xf879, 0x0fपूर्ण, अणु0xf87a, 0xffपूर्ण, अणु0xf87b, 0xffपूर्ण,
	अणु0xf800, 0x03पूर्ण
पूर्ण;
अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd icx098bq_start_1[] = अणु
	अणु0xf5f0, 0x00पूर्ण, अणु0xf5f1, 0xcdपूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xc0पूर्ण,
	अणु0xf5f0, 0x49पूर्ण, अणु0xf5f1, 0xcdपूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xc0पूर्ण,
	अणु0xf5fa, 0x00पूर्ण, अणु0xf5f6, 0x00पूर्ण, अणु0xf5f7, 0x00पूर्ण, अणु0xf5f8, 0x00पूर्ण,
	अणु0xf5f9, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd icx098bq_start_2[] = अणु
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x82पूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x40पूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0xcfपूर्ण, अणु0xf806, 0xd0पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x00पूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd lz24bp_start_0[] = अणु
	अणु0x0354, 0x00पूर्ण, अणु0x03fa, 0x00पूर्ण, अणु0xf800, 0x02पूर्ण, अणु0xf801, 0xbeपूर्ण,
	अणु0xf802, 0xc6पूर्ण, अणु0xf804, 0x00पूर्ण, अणु0xf808, 0x00पूर्ण, अणु0xf809, 0x06पूर्ण,
	अणु0xf80a, 0x01पूर्ण, अणु0xf80b, 0xfeपूर्ण, अणु0xf807, 0x84पूर्ण, अणु0xf80c, 0x02पूर्ण,
	अणु0xf80d, 0xf7पूर्ण, अणु0xf80e, 0x03पूर्ण, अणु0xf80f, 0x0bपूर्ण, अणु0xf81c, 0x00पूर्ण,
	अणु0xf81d, 0x49पूर्ण, अणु0xf81e, 0x03पूर्ण, अणु0xf81f, 0x0bपूर्ण, अणु0xf83a, 0x00पूर्ण,
	अणु0xf83b, 0x01पूर्ण, अणु0xf83c, 0x00पूर्ण, अणु0xf83d, 0x6bपूर्ण, अणु0xf810, 0x03पूर्ण,
	अणु0xf811, 0x10पूर्ण, अणु0xf812, 0x02पूर्ण, अणु0xf813, 0x6fपूर्ण, अणु0xf803, 0x00पूर्ण,
	अणु0xf814, 0x00पूर्ण, अणु0xf815, 0x44पूर्ण, अणु0xf816, 0x00पूर्ण, अणु0xf817, 0x48पूर्ण,
	अणु0xf818, 0x00पूर्ण, अणु0xf819, 0x25पूर्ण, अणु0xf81a, 0x00पूर्ण, अणु0xf81b, 0x3cपूर्ण,
	अणु0xf82f, 0x03पूर्ण, अणु0xf820, 0xffपूर्ण, अणु0xf821, 0x0dपूर्ण, अणु0xf822, 0xffपूर्ण,
	अणु0xf823, 0x07पूर्ण, अणु0xf824, 0xfdपूर्ण, अणु0xf825, 0x07पूर्ण, अणु0xf826, 0xf0पूर्ण,
	अणु0xf827, 0x0cपूर्ण, अणु0xf828, 0xffपूर्ण, अणु0xf829, 0x03पूर्ण, अणु0xf82a, 0xffपूर्ण,
	अणु0xf82b, 0x0cपूर्ण, अणु0xf82c, 0xfcपूर्ण, अणु0xf82d, 0x01पूर्ण, अणु0xf82e, 0x00पूर्ण,
	अणु0xf830, 0x00पूर्ण, अणु0xf831, 0x47पूर्ण, अणु0xf832, 0x00पूर्ण, अणु0xf833, 0x00पूर्ण,
	अणु0xf850, 0x00पूर्ण, अणु0xf851, 0x00पूर्ण, अणु0xf852, 0x00पूर्ण, अणु0xf853, 0x24पूर्ण,
	अणु0xf854, 0x00पूर्ण, अणु0xf855, 0x0cपूर्ण, अणु0xf856, 0x00पूर्ण, अणु0xf857, 0x30पूर्ण,
	अणु0xf858, 0x00पूर्ण, अणु0xf859, 0x18पूर्ण, अणु0xf85a, 0x00पूर्ण, अणु0xf85b, 0x3cपूर्ण,
	अणु0xf85c, 0x00पूर्ण, अणु0xf85d, 0x18पूर्ण, अणु0xf85e, 0x00पूर्ण, अणु0xf85f, 0x3cपूर्ण,
	अणु0xf860, 0xffपूर्ण, अणु0xf861, 0x37पूर्ण, अणु0xf862, 0xffपूर्ण, अणु0xf863, 0x1dपूर्ण,
	अणु0xf864, 0xffपूर्ण, अणु0xf865, 0x98पूर्ण, अणु0xf866, 0xffपूर्ण, अणु0xf867, 0xc0पूर्ण,
	अणु0xf868, 0x00पूर्ण, अणु0xf869, 0x37पूर्ण, अणु0xf86c, 0x02पूर्ण, अणु0xf86d, 0x1dपूर्ण,
	अणु0xf86a, 0x00पूर्ण, अणु0xf86b, 0x37पूर्ण, अणु0xf86e, 0x02पूर्ण, अणु0xf86f, 0x1dपूर्ण,
	अणु0xf870, 0x01पूर्ण, अणु0xf871, 0xc6पूर्ण, अणु0xf872, 0x02पूर्ण, अणु0xf873, 0x04पूर्ण,
	अणु0xf874, 0x01पूर्ण, अणु0xf875, 0xc6पूर्ण, अणु0xf876, 0x02पूर्ण, अणु0xf877, 0x04पूर्ण,
	अणु0xf878, 0x0fपूर्ण, अणु0xf879, 0x0fपूर्ण, अणु0xf87a, 0xffपूर्ण, अणु0xf87b, 0xffपूर्ण,
	अणु0xf800, 0x03पूर्ण
पूर्ण;
अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd lz24bp_start_1_gen[] = अणु
	अणु0xf5f0, 0x00पूर्ण, अणु0xf5f1, 0xffपूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xb3पूर्ण,
	अणु0xf5f0, 0x40पूर्ण, अणु0xf5f1, 0xffपूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xb3पूर्ण,
	अणु0xf5fa, 0x00पूर्ण, अणु0xf5f6, 0x00पूर्ण, अणु0xf5f7, 0x00पूर्ण, अणु0xf5f8, 0x00पूर्ण,
	अणु0xf5f9, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd lz24bp_start_1_clm[] = अणु
	अणु0xf5f0, 0x00पूर्ण, अणु0xf5f1, 0xffपूर्ण, अणु0xf5f2, 0x88पूर्ण, अणु0xf5f3, 0x88पूर्ण,
	अणु0xf5f4, 0xc0पूर्ण,
	अणु0xf5f0, 0x40पूर्ण, अणु0xf5f1, 0xffपूर्ण, अणु0xf5f2, 0x88पूर्ण, अणु0xf5f3, 0x88पूर्ण,
	अणु0xf5f4, 0xc0पूर्ण,
	अणु0xf5fa, 0x00पूर्ण, अणु0xf5f6, 0x00पूर्ण, अणु0xf5f7, 0x00पूर्ण, अणु0xf5f8, 0x00पूर्ण,
	अणु0xf5f9, 0x00पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd lz24bp_start_2[] = अणु
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x80पूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x4eपूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0xc0पूर्ण, अणु0xf806, 0x48पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण,
	अणु0xf800, 0x02पूर्ण, अणु0xf807, 0xffपूर्ण, अणु0xf805, 0x00पूर्ण, अणु0xf806, 0x00पूर्ण,
	अणु0xf807, 0x7fपूर्ण, अणु0xf800, 0x03पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd mi0360_start_0[] = अणु
	अणु0x0354, 0x00पूर्ण, अणु0x03fa, 0x00पूर्ण, अणु0xf332, 0xccपूर्ण, अणु0xf333, 0xccपूर्ण,
	अणु0xf334, 0xccपूर्ण, अणु0xf335, 0xccपूर्ण, अणु0xf33f, 0x00पूर्ण
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_init_23[] = अणु
	अणु0x30, 0x0040पूर्ण,		/* reserved - def 0x0005 */
	अणु0x31, 0x0000पूर्ण,		/* reserved - def 0x002a */
	अणु0x34, 0x0100पूर्ण,		/* reserved - def 0x0100 */
	अणु0x3d, 0x068fपूर्ण,		/* reserved - def 0x068f */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_init_24[] = अणु
	अणु0x03, 0x01e5पूर्ण,		/* winकरोw height */
	अणु0x04, 0x0285पूर्ण,		/* winकरोw width */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_init_25[] = अणु
	अणु0x35, 0x0020पूर्ण,		/* global gain */
	अणु0x2b, 0x0020पूर्ण,		/* green1 gain */
	अणु0x2c, 0x002aपूर्ण,		/* blue gain */
	अणु0x2d, 0x0028पूर्ण,		/* red gain */
	अणु0x2e, 0x0020पूर्ण,		/* green2 gain */
पूर्ण;
अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd mi0360_start_1[] = अणु
	अणु0xf5f0, 0x11पूर्ण, अणु0xf5f1, 0x99पूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xa6पूर्ण,
	अणु0xf5f0, 0x51पूर्ण, अणु0xf5f1, 0x99पूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xa6पूर्ण,
	अणु0xf5fa, 0x00पूर्ण, अणु0xf5f6, 0x00पूर्ण, अणु0xf5f7, 0x00पूर्ण, अणु0xf5f8, 0x00पूर्ण,
	अणु0xf5f9, 0x00पूर्ण
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_start_2[] = अणु
	अणु0x62, 0x041dपूर्ण,		/* reserved - def 0x0418 */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_start_3[] = अणु
	अणु0x05, 0x007bपूर्ण,		/* horiz blanking */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mi0360_start_4[] = अणु
	अणु0x05, 0x03f5पूर्ण,		/* horiz blanking */
पूर्ण;

अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mt9v111_init_0[] = अणु
	अणु0x01, 0x0001पूर्ण,		/* select IFP/SOC रेजिस्टरs */
	अणु0x06, 0x300cपूर्ण,		/* operating mode control */
	अणु0x08, 0xcc00पूर्ण,		/* output क्रमmat control (RGB) */
	अणु0x01, 0x0004पूर्ण,		/* select sensor core रेजिस्टरs */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mt9v111_init_1[] = अणु
	अणु0x03, 0x01e5पूर्ण,		/* winकरोw height */
	अणु0x04, 0x0285पूर्ण,		/* winकरोw width */
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mt9v111_init_2[] = अणु
	अणु0x30, 0x7800पूर्ण,
	अणु0x31, 0x0000पूर्ण,
	अणु0x07, 0x3002पूर्ण,		/* output control */
	अणु0x35, 0x0020पूर्ण,		/* global gain */
	अणु0x2b, 0x0020पूर्ण,		/* green1 gain */
	अणु0x2c, 0x0020पूर्ण,		/* blue gain */
	अणु0x2d, 0x0020पूर्ण,		/* red gain */
	अणु0x2e, 0x0020पूर्ण,		/* green2 gain */
पूर्ण;
अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd mt9v111_start_1[] = अणु
	अणु0xf5f0, 0x11पूर्ण, अणु0xf5f1, 0x96पूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xaaपूर्ण,
	अणु0xf5f0, 0x51पूर्ण, अणु0xf5f1, 0x96पूर्ण, अणु0xf5f2, 0x80पूर्ण, अणु0xf5f3, 0x80पूर्ण,
	अणु0xf5f4, 0xaaपूर्ण,
	अणु0xf5fa, 0x00पूर्ण, अणु0xf5f6, 0x0aपूर्ण, अणु0xf5f7, 0x0aपूर्ण, अणु0xf5f8, 0x0aपूर्ण,
	अणु0xf5f9, 0x0aपूर्ण
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mt9v111_init_3[] = अणु
	अणु0x62, 0x0405पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा i2c_ग_लिखो_cmd mt9v111_init_4[] = अणु
/*	अणु0x05, 0x00ceपूर्ण, */
	अणु0x05, 0x005dपूर्ण,		/* horizontal blanking */
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd ov7660_start_0[] = अणु
	अणु0x0354, 0x00पूर्ण, अणु0x03fa, 0x00पूर्ण, अणु0xf332, 0x00पूर्ण, अणु0xf333, 0xc0पूर्ण,
	अणु0xf334, 0x39पूर्ण, अणु0xf335, 0xe7पूर्ण, अणु0xf33f, 0x03पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd ov9630_start_0[] = अणु
	अणु0x0354, 0x00पूर्ण, अणु0x03fa, 0x00पूर्ण, अणु0xf332, 0x00पूर्ण, अणु0xf333, 0x00पूर्ण,
	अणु0xf334, 0x3eपूर्ण, अणु0xf335, 0xf8पूर्ण, अणु0xf33f, 0x03पूर्ण
पूर्ण;

/* start parameters indexed by [sensor][mode] */
अटल स्थिर काष्ठा cap_s अणु
	u8	cc_sizeid;
	u8	cc_bytes[32];
पूर्ण capconfig[4][2] = अणु
	[SENSOR_ICX098BQ] = अणु
		अणु2,				/* Bayer 320x240 */
		  अणु0x05, 0x1f, 0x20, 0x0e, 0x00, 0x9f, 0x02, 0xee,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
		अणु4,				/* Bayer 640x480 */
		  अणु0x01, 0x1f, 0x20, 0x0e, 0x00, 0x9f, 0x02, 0xee,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	पूर्ण,
	[SENSOR_LZ24BP] = अणु
		अणु2,				/* Bayer 320x240 */
		  अणु0x05, 0x22, 0x20, 0x0e, 0x00, 0xa2, 0x02, 0xee,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
		अणु4,				/* Bayer 640x480 */
		  अणु0x01, 0x22, 0x20, 0x0e, 0x00, 0xa2, 0x02, 0xee,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	पूर्ण,
	[SENSOR_MI0360] = अणु
		अणु2,				/* Bayer 320x240 */
		  अणु0x05, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
		अणु4,				/* Bayer 640x480 */
		  अणु0x01, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	पूर्ण,
	[SENSOR_MT9V111] = अणु
		अणु2,				/* Bayer 320x240 */
		  अणु0x05, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x01, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
		अणु4,				/* Bayer 640x480 */
		  अणु0x01, 0x02, 0x20, 0x01, 0x20, 0x82, 0x02, 0xe1,
		   0x01, 0x02, 0x00, 0x08, 0x18, 0x12, 0x78, 0xc8,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा sensor_s अणु
	स्थिर अक्षर *name;
	u8 i2c_addr;
	u8 i2c_dum;
	u8 gpio[5];
	u8 cmd_len;
	स्थिर काष्ठा ucbus_ग_लिखो_cmd *cmd;
पूर्ण;

अटल स्थिर काष्ठा sensor_s sensor_tb[] = अणु
	[SENSOR_ICX098BQ] = अणु
		"icx098bp",
		0x00, 0x00,
		अणु0,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 SQ930_GPIO_RSTBAR
		पूर्ण,
		8, icx098bq_start_0
	    पूर्ण,
	[SENSOR_LZ24BP] = अणु
		"lz24bp",
		0x00, 0x00,
		अणु0,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 SQ930_GPIO_RSTBAR
		पूर्ण,
		8, lz24bp_start_0
	    पूर्ण,
	[SENSOR_MI0360] = अणु
		"mi0360",
		0x5d, 0x80,
		अणुSQ930_GPIO_RSTBAR,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 0
		पूर्ण,
		7, mi0360_start_0
	    पूर्ण,
	[SENSOR_MT9V111] = अणु
		"mt9v111",
		0x5c, 0x7f,
		अणुSQ930_GPIO_RSTBAR,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 0
		पूर्ण,
		7, mi0360_start_0
	    पूर्ण,
	[SENSOR_OV7660] = अणु
		"ov7660",
		0x21, 0x00,
		अणु0,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 SQ930_GPIO_RSTBAR
		पूर्ण,
		7, ov7660_start_0
	    पूर्ण,
	[SENSOR_OV9630] = अणु
		"ov9630",
		0x30, 0x00,
		अणु0,
		 SQ930_GPIO_DFL_I2C_SDA | SQ930_GPIO_DFL_I2C_SCL,
		 SQ930_GPIO_DFL_I2C_SDA,
		 0,
		 SQ930_GPIO_RSTBAR
		पूर्ण,
		7, ov9630_start_0
	    पूर्ण,
पूर्ण;

अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		u16 value, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0x0c,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, 0, gspca_dev->usb_buf, len,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_r %04x failed %d\n", value, ret);
		gspca_dev->usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	पूर्ण
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dbg(gspca_dev, D_USBO, "reg_w v: %04x i: %04x\n", value, index);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x0c,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0,
			500);
	msleep(30);
	अगर (ret < 0) अणु
		pr_err("reg_w %04x %04x failed %d\n", value, index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_wb(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index,
		स्थिर u8 *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dbg(gspca_dev, D_USBO, "reg_wb v: %04x i: %04x %02x...%02x\n",
		  value, index, *data, data[len - 1]);
	स_नकल(gspca_dev->usb_buf, data, len);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x0c,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, gspca_dev->usb_buf, len,
			1000);
	msleep(30);
	अगर (ret < 0) अणु
		pr_err("reg_wb %04x %04x failed %d\n", value, index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम i2c_ग_लिखो(काष्ठा sd *sd,
			स्थिर काष्ठा i2c_ग_लिखो_cmd *cmd,
			पूर्णांक ncmds)
अणु
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;
	स्थिर काष्ठा sensor_s *sensor;
	u16 val, idx;
	u8 *buf;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	sensor = &sensor_tb[sd->sensor];

	val = (sensor->i2c_addr << 8) | SQ930_CTRL_I2C_IO;
	idx = (cmd->val & 0xff00) | cmd->reg;

	buf = gspca_dev->usb_buf;
	*buf++ = sensor->i2c_dum;
	*buf++ = cmd->val;

	जबतक (--ncmds > 0) अणु
		cmd++;
		*buf++ = cmd->reg;
		*buf++ = cmd->val >> 8;
		*buf++ = sensor->i2c_dum;
		*buf++ = cmd->val;
	पूर्ण

	gspca_dbg(gspca_dev, D_USBO, "i2c_w v: %04x i: %04x %02x...%02x\n",
		  val, idx, gspca_dev->usb_buf[0], buf[-1]);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x0c,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			val, idx,
			gspca_dev->usb_buf, buf - gspca_dev->usb_buf,
			500);
	अगर (ret < 0) अणु
		pr_err("i2c_write failed %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम ucbus_ग_लिखो(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा ucbus_ग_लिखो_cmd *cmd,
			पूर्णांक ncmds,
			पूर्णांक batchsize)
अणु
	u8 *buf;
	u16 val, idx;
	पूर्णांक len, ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	अगर ((batchsize - 1) * 3 > USB_BUF_SZ) अणु
		gspca_err(gspca_dev, "Bug: usb_buf overflow\n");
		gspca_dev->usb_err = -ENOMEM;
		वापस;
	पूर्ण

	क्रम (;;) अणु
		len = ncmds;
		अगर (len > batchsize)
			len = batchsize;
		ncmds -= len;

		val = (cmd->bw_addr << 8) | SQ930_CTRL_UCBUS_IO;
		idx = (cmd->bw_data << 8) | (cmd->bw_addr >> 8);

		buf = gspca_dev->usb_buf;
		जबतक (--len > 0) अणु
			cmd++;
			*buf++ = cmd->bw_addr;
			*buf++ = cmd->bw_addr >> 8;
			*buf++ = cmd->bw_data;
		पूर्ण
		अगर (buf != gspca_dev->usb_buf)
			gspca_dbg(gspca_dev, D_USBO, "ucbus v: %04x i: %04x %02x...%02x\n",
				  val, idx,
				  gspca_dev->usb_buf[0], buf[-1]);
		अन्यथा
			gspca_dbg(gspca_dev, D_USBO, "ucbus v: %04x i: %04x\n",
				  val, idx);
		ret = usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0x0c,			/* request */
			   USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				val, idx,
				gspca_dev->usb_buf, buf - gspca_dev->usb_buf,
				500);
		अगर (ret < 0) अणु
			pr_err("ucbus_write failed %d\n", ret);
			gspca_dev->usb_err = ret;
			वापस;
		पूर्ण
		msleep(30);
		अगर (ncmds <= 0)
			अवरोध;
		cmd++;
	पूर्ण
पूर्ण

अटल व्योम gpio_set(काष्ठा sd *sd, u16 val, u16 mask)
अणु
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;

	अगर (mask & 0x00ff) अणु
		sd->gpio[0] &= ~mask;
		sd->gpio[0] |= val;
		reg_w(gspca_dev, 0x0100 | SQ930_CTRL_GPIO,
			~sd->gpio[0] << 8);
	पूर्ण
	mask >>= 8;
	val >>= 8;
	अगर (mask) अणु
		sd->gpio[1] &= ~mask;
		sd->gpio[1] |= val;
		reg_w(gspca_dev, 0x0300 | SQ930_CTRL_GPIO,
			~sd->gpio[1] << 8);
	पूर्ण
पूर्ण

अटल व्योम gpio_init(काष्ठा sd *sd,
			स्थिर u8 *gpio)
अणु
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio++, 0x000f);
	gpio_set(sd, *gpio, 0x000f);
पूर्ण

अटल व्योम bridge_init(काष्ठा sd *sd)
अणु
	अटल स्थिर काष्ठा ucbus_ग_लिखो_cmd clkfreq_cmd = अणु
				0xf031, 0	/* SQ930_CLKFREQ_60MHZ */
	पूर्ण;

	ucbus_ग_लिखो(&sd->gspca_dev, &clkfreq_cmd, 1, 1);

	gpio_set(sd, SQ930_GPIO_POWER, 0xff00);
पूर्ण

अटल व्योम cmos_probe(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;
	स्थिर काष्ठा sensor_s *sensor;
	अटल स्थिर u8 probe_order[] = अणु
/*		SENSOR_LZ24BP,		(tested as ccd) */
		SENSOR_OV9630,
		SENSOR_MI0360,
		SENSOR_OV7660,
		SENSOR_MT9V111,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(probe_order); i++) अणु
		sensor = &sensor_tb[probe_order[i]];
		ucbus_ग_लिखो(&sd->gspca_dev, sensor->cmd, sensor->cmd_len, 8);
		gpio_init(sd, sensor->gpio);
		msleep(100);
		reg_r(gspca_dev, (sensor->i2c_addr << 8) | 0x001c, 1);
		msleep(100);
		अगर (gspca_dev->usb_buf[0] != 0)
			अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(probe_order)) अणु
		pr_err("Unknown sensor\n");
		gspca_dev->usb_err = -EINVAL;
		वापस;
	पूर्ण
	sd->sensor = probe_order[i];
	चयन (sd->sensor) अणु
	हाल SENSOR_OV7660:
	हाल SENSOR_OV9630:
		pr_err("Sensor %s not yet treated\n",
		       sensor_tb[sd->sensor].name);
		gspca_dev->usb_err = -EINVAL;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt9v111_init(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i, nरुको;
	अटल स्थिर u8 cmd_001b[] = अणु
		0x00, 0x3b, 0xf6, 0x01, 0x03, 0x02, 0x00, 0x00,
		0x00, 0x00, 0x00
	पूर्ण;
	अटल स्थिर u8 cmd_011b[][7] = अणु
		अणु0x10, 0x01, 0x66, 0x08, 0x00, 0x00, 0x00पूर्ण,
		अणु0x01, 0x00, 0x1a, 0x04, 0x00, 0x00, 0x00पूर्ण,
		अणु0x20, 0x00, 0x10, 0x04, 0x00, 0x00, 0x00पूर्ण,
		अणु0x02, 0x01, 0xae, 0x01, 0x00, 0x00, 0x00पूर्ण,
	पूर्ण;

	reg_wb(gspca_dev, 0x001b, 0x0000, cmd_001b, माप cmd_001b);
	क्रम (i = 0; i < ARRAY_SIZE(cmd_011b); i++) अणु
		reg_wb(gspca_dev, 0x001b, 0x0000, cmd_011b[i],
				ARRAY_SIZE(cmd_011b[0]));
		msleep(400);
		nरुको = 20;
		क्रम (;;) अणु
			reg_r(gspca_dev, 0x031b, 1);
			अगर (gspca_dev->usb_buf[0] == 0
			 || gspca_dev->usb_err != 0)
				अवरोध;
			अगर (--nरुको < 0) अणु
				gspca_dbg(gspca_dev, D_PROBE, "mt9v111_init timeout\n");
				gspca_dev->usb_err = -ETIME;
				वापस;
			पूर्ण
			msleep(50);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम global_init(काष्ठा sd *sd, पूर्णांक first_समय)
अणु
	चयन (sd->sensor) अणु
	हाल SENSOR_ICX098BQ:
		अगर (first_समय)
			ucbus_ग_लिखो(&sd->gspca_dev,
					icx098bq_start_0,
					8, 8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		अवरोध;
	हाल SENSOR_LZ24BP:
		अगर (sd->type != Creative_live_motion)
			gpio_set(sd, SQ930_GPIO_EXTRA1, 0x00ff);
		अन्यथा
			gpio_set(sd, 0, 0x00ff);
		msleep(50);
		अगर (first_समय)
			ucbus_ग_लिखो(&sd->gspca_dev,
					lz24bp_start_0,
					8, 8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		अवरोध;
	हाल SENSOR_MI0360:
		अगर (first_समय)
			ucbus_ग_लिखो(&sd->gspca_dev,
					mi0360_start_0,
					ARRAY_SIZE(mi0360_start_0),
					8);
		gpio_init(sd, sensor_tb[sd->sensor].gpio);
		gpio_set(sd, SQ930_GPIO_EXTRA2, SQ930_GPIO_EXTRA2);
		अवरोध;
	शेष:
/*	हाल SENSOR_MT9V111: */
		अगर (first_समय)
			mt9v111_init(&sd->gspca_dev);
		अन्यथा
			gpio_init(sd, sensor_tb[sd->sensor].gpio);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम lz24bp_ppl(काष्ठा sd *sd, u16 ppl)
अणु
	काष्ठा ucbus_ग_लिखो_cmd cmds[2] = अणु
		अणु0xf810, ppl >> 8पूर्ण,
		अणु0xf811, pplपूर्ण
	पूर्ण;

	ucbus_ग_लिखो(&sd->gspca_dev, cmds, ARRAY_SIZE(cmds), 2);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 expo, s32 gain)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, पूर्णांकegclks, पूर्णांकstartclk, frameclks, min_frclk;
	स्थिर काष्ठा sensor_s *sensor;
	u16 cmd;
	u8 buf[15];

	पूर्णांकegclks = expo;
	i = 0;
	cmd = SQ930_CTRL_SET_EXPOSURE;

	चयन (sd->sensor) अणु
	हाल SENSOR_ICX098BQ:			/* ccd */
	हाल SENSOR_LZ24BP:
		min_frclk = sd->sensor == SENSOR_ICX098BQ ? 0x210 : 0x26f;
		अगर (पूर्णांकegclks >= min_frclk) अणु
			पूर्णांकstartclk = 0;
			frameclks = पूर्णांकegclks;
		पूर्ण अन्यथा अणु
			पूर्णांकstartclk = min_frclk - पूर्णांकegclks;
			frameclks = min_frclk;
		पूर्ण
		buf[i++] = पूर्णांकstartclk >> 8;
		buf[i++] = पूर्णांकstartclk;
		buf[i++] = frameclks >> 8;
		buf[i++] = frameclks;
		buf[i++] = gain;
		अवरोध;
	शेष:				/* cmos */
/*	हाल SENSOR_MI0360: */
/*	हाल SENSOR_MT9V111: */
		cmd |= 0x0100;
		sensor = &sensor_tb[sd->sensor];
		buf[i++] = sensor->i2c_addr;	/* i2c_slave_addr */
		buf[i++] = 0x08;	/* 2 * ni2c */
		buf[i++] = 0x09;	/* reg = shutter width */
		buf[i++] = पूर्णांकegclks >> 8; /* val H */
		buf[i++] = sensor->i2c_dum;
		buf[i++] = पूर्णांकegclks;	/* val L */
		buf[i++] = 0x35;	/* reg = global gain */
		buf[i++] = 0x00;	/* val H */
		buf[i++] = sensor->i2c_dum;
		buf[i++] = 0x80 + gain / 2; /* val L */
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x83;
		अवरोध;
	पूर्ण
	reg_wb(gspca_dev, cmd, 0, buf, i);
पूर्ण

/* This function is called at probe समय just beक्रमe sd_init */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;

	sd->sensor = id->driver_info >> 8;
	sd->type = id->driver_info;

	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);

	cam->bulk = 1;

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	sd->gpio[0] = sd->gpio[1] = 0xff;	/* क्रमce gpio reग_लिखो */

/*fixme: is this needed क्रम icx098bp and mi0360?
	अगर (sd->sensor != SENSOR_LZ24BP)
		reg_w(gspca_dev, SQ930_CTRL_RESET, 0x0000);
 */

	reg_r(gspca_dev, SQ930_CTRL_GET_DEV_INFO, 8);
	अगर (gspca_dev->usb_err < 0)
		वापस gspca_dev->usb_err;

/* it वापसs:
 * 03 00 12 93 0b f6 c9 00	live! ultra
 * 03 00 07 93 0b f6 ca 00	live! ultra क्रम notebook
 * 03 00 12 93 0b fe c8 00	Trust WB-3500T
 * 02 00 06 93 0b fe c8 00	Joy-IT 318S
 * 03 00 12 93 0b f6 cf 00	icam tracer - sensor icx098bq
 * 02 00 12 93 0b fe cf 00	ProQ Motion Webcam
 *
 * byte
 * 0: 02 = usb 1.0 (12Mbit) / 03 = usb2.0 (480Mbit)
 * 1: 00
 * 2: 06 / 07 / 12 = mode webcam? firmware??
 * 3: 93 chip = 930b (930b or 930c)
 * 4: 0b
 * 5: f6 = cdd (icx098bq, lz24bp) / fe or de = cmos (i2c) (other sensors)
 * 6: c8 / c9 / ca / cf = mode webcam?, sensor? webcam?
 * 7: 00
 */
	gspca_dbg(gspca_dev, D_PROBE, "info: %*ph\n", 8, gspca_dev->usb_buf);

	bridge_init(sd);

	अगर (sd->sensor == SENSOR_MI0360) अणु

		/* no sensor probe क्रम icam tracer */
		अगर (gspca_dev->usb_buf[5] == 0xf6)	/* अगर ccd */
			sd->sensor = SENSOR_ICX098BQ;
		अन्यथा
			cmos_probe(gspca_dev);
	पूर्ण
	अगर (gspca_dev->usb_err >= 0) अणु
		gspca_dbg(gspca_dev, D_PROBE, "Sensor %s\n",
			  sensor_tb[sd->sensor].name);
		global_init(sd, 1);
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

/* send the start/stop commands to the webcam */
अटल व्योम send_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	स्थिर काष्ठा cap_s *cap;
	पूर्णांक mode;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	cap = &capconfig[sd->sensor][mode];
	reg_wb(gspca_dev, 0x0900 | SQ930_CTRL_CAP_START,
			0x0a00 | cap->cc_sizeid,
			cap->cc_bytes, 32);
पूर्ण

अटल व्योम send_stop(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, SQ930_CTRL_CAP_STOP, 0);
पूर्ण

/* function called at start समय beक्रमe URB creation */
अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->cam.bulk_nurbs = 1;	/* there must be one URB only */
	sd->करो_ctrl = 0;
	gspca_dev->cam.bulk_size = gspca_dev->pixfmt.width *
			gspca_dev->pixfmt.height + 8;
	वापस 0;
पूर्ण

/* start the capture */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक mode;

	bridge_init(sd);
	global_init(sd, 0);
	msleep(100);

	चयन (sd->sensor) अणु
	हाल SENSOR_ICX098BQ:
		ucbus_ग_लिखो(gspca_dev, icx098bq_start_0,
				ARRAY_SIZE(icx098bq_start_0),
				8);
		ucbus_ग_लिखो(gspca_dev, icx098bq_start_1,
				ARRAY_SIZE(icx098bq_start_1),
				5);
		ucbus_ग_लिखो(gspca_dev, icx098bq_start_2,
				ARRAY_SIZE(icx098bq_start_2),
				6);
		msleep(50);

		/* 1st start */
		send_start(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTRA2 | SQ930_GPIO_RSTBAR, 0x00ff);
		msleep(70);
		reg_w(gspca_dev, SQ930_CTRL_CAP_STOP, 0x0000);
		gpio_set(sd, 0x7f, 0x00ff);

		/* 2nd start */
		send_start(gspca_dev);
		gpio_set(sd, SQ930_GPIO_EXTRA2 | SQ930_GPIO_RSTBAR, 0x00ff);
		जाओ out;
	हाल SENSOR_LZ24BP:
		ucbus_ग_लिखो(gspca_dev, lz24bp_start_0,
				ARRAY_SIZE(lz24bp_start_0),
				8);
		अगर (sd->type != Creative_live_motion)
			ucbus_ग_लिखो(gspca_dev, lz24bp_start_1_gen,
					ARRAY_SIZE(lz24bp_start_1_gen),
					5);
		अन्यथा
			ucbus_ग_लिखो(gspca_dev, lz24bp_start_1_clm,
					ARRAY_SIZE(lz24bp_start_1_clm),
					5);
		ucbus_ग_लिखो(gspca_dev, lz24bp_start_2,
				ARRAY_SIZE(lz24bp_start_2),
				6);
		mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
		lz24bp_ppl(sd, mode == 1 ? 0x0564 : 0x0310);
		msleep(10);
		अवरोध;
	हाल SENSOR_MI0360:
		ucbus_ग_लिखो(gspca_dev, mi0360_start_0,
				ARRAY_SIZE(mi0360_start_0),
				8);
		i2c_ग_लिखो(sd, mi0360_init_23,
				ARRAY_SIZE(mi0360_init_23));
		i2c_ग_लिखो(sd, mi0360_init_24,
				ARRAY_SIZE(mi0360_init_24));
		i2c_ग_लिखो(sd, mi0360_init_25,
				ARRAY_SIZE(mi0360_init_25));
		ucbus_ग_लिखो(gspca_dev, mi0360_start_1,
				ARRAY_SIZE(mi0360_start_1),
				5);
		i2c_ग_लिखो(sd, mi0360_start_2,
				ARRAY_SIZE(mi0360_start_2));
		i2c_ग_लिखो(sd, mi0360_start_3,
				ARRAY_SIZE(mi0360_start_3));

		/* 1st start */
		send_start(gspca_dev);
		msleep(60);
		send_stop(gspca_dev);

		i2c_ग_लिखो(sd,
			mi0360_start_4, ARRAY_SIZE(mi0360_start_4));
		अवरोध;
	शेष:
/*	हाल SENSOR_MT9V111: */
		ucbus_ग_लिखो(gspca_dev, mi0360_start_0,
				ARRAY_SIZE(mi0360_start_0),
				8);
		i2c_ग_लिखो(sd, mt9v111_init_0,
				ARRAY_SIZE(mt9v111_init_0));
		i2c_ग_लिखो(sd, mt9v111_init_1,
				ARRAY_SIZE(mt9v111_init_1));
		i2c_ग_लिखो(sd, mt9v111_init_2,
				ARRAY_SIZE(mt9v111_init_2));
		ucbus_ग_लिखो(gspca_dev, mt9v111_start_1,
				ARRAY_SIZE(mt9v111_start_1),
				5);
		i2c_ग_लिखो(sd, mt9v111_init_3,
				ARRAY_SIZE(mt9v111_init_3));
		i2c_ग_लिखो(sd, mt9v111_init_4,
				ARRAY_SIZE(mt9v111_init_4));
		अवरोध;
	पूर्ण

	send_start(gspca_dev);
out:
	msleep(1000);

	अगर (sd->sensor == SENSOR_MT9V111)
		gpio_set(sd, SQ930_GPIO_DFL_LED, SQ930_GPIO_DFL_LED);

	sd->करो_ctrl = 1;	/* set the exposure */

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor == SENSOR_MT9V111)
		gpio_set(sd, 0, SQ930_GPIO_DFL_LED);
	send_stop(gspca_dev);
पूर्ण

/* function called when the application माला_लो a new frame */
/* It sets the exposure अगर required and restart the bulk transfer. */
अटल व्योम sd_dq_callback(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	अगर (!sd->करो_ctrl || gspca_dev->cam.bulk_nurbs != 0)
		वापस;
	sd->करो_ctrl = 0;

	setexposure(gspca_dev, v4l2_ctrl_g_ctrl(sd->exposure),
			v4l2_ctrl_g_ctrl(sd->gain));

	gspca_dev->cam.bulk_nurbs = 1;
	ret = usb_submit_urb(gspca_dev->urb[0], GFP_KERNEL);
	अगर (ret < 0)
		pr_err("sd_dq_callback() err %d\n", ret);

	/* रुको a little समय, otherwise the webcam crashes */
	msleep(100);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			पूर्णांक len)		/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->करो_ctrl)
		gspca_dev->cam.bulk_nurbs = 0;
	gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len - 8);
	gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, ctrl->val, sd->gain->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 2);
	sd->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 1, 0xfff, 1, 0x356);
	sd->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 1, 255, 1, 0x8d);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	v4l2_ctrl_cluster(2, &sd->exposure);
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name   = MODULE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init = sd_isoc_init,
	.start  = sd_start,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.dq_callback = sd_dq_callback,
पूर्ण;

/* Table of supported USB devices */
#घोषणा ST(sensor, type) \
	.driver_info = (SENSOR_ ## sensor << 8) \
			| (type)
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x041e, 0x4038), ST(MI0360, 0)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x403c), ST(LZ24BP, 0)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x403d), ST(LZ24BP, 0)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4041), ST(LZ24BP, Creative_live_motion)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x930b), ST(MI0360, 0)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x930c), ST(MI0360, 0)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);


/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
			THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name	    = MODULE_NAME,
	.id_table   = device_table,
	.probe	    = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend    = gspca_suspend,
	.resume     = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
