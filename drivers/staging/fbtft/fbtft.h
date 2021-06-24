<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2013 Noralf Tronnes */

#अगर_अघोषित __LINUX_FBTFT_H
#घोषणा __LINUX_FBTFT_H

#समावेश <linux/fb.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा FBTFT_ONBOARD_BACKLIGHT 2

#घोषणा FBTFT_GPIO_NO_MATCH		0xFFFF
#घोषणा FBTFT_GPIO_NAME_SIZE	32
#घोषणा FBTFT_MAX_INIT_SEQUENCE      512
#घोषणा FBTFT_GAMMA_MAX_VALUES_TOTAL 128

#घोषणा FBTFT_OF_INIT_CMD	BIT(24)
#घोषणा FBTFT_OF_INIT_DELAY	BIT(25)

/**
 * काष्ठा fbtft_gpio - Structure that holds one pinname to gpio mapping
 * @name: pinname (reset, dc, etc.)
 * @gpio: GPIO number
 *
 */
काष्ठा fbtft_gpio अणु
	अक्षर name[FBTFT_GPIO_NAME_SIZE];
	काष्ठा gpio_desc *gpio;
पूर्ण;

काष्ठा fbtft_par;

/**
 * काष्ठा fbtft_ops - FBTFT operations काष्ठाure
 * @ग_लिखो: Writes to पूर्णांकerface bus
 * @पढ़ो: Reads from पूर्णांकerface bus
 * @ग_लिखो_vmem: Writes video memory to display
 * @ग_लिखो_reg: Writes to controller रेजिस्टर
 * @set_addr_win: Set the GRAM update winकरोw
 * @reset: Reset the LCD controller
 * @सूची_गढ़ोty: Marks display lines क्रम update
 * @update_display: Updates the display
 * @init_display: Initializes the display
 * @blank: Blank the display (optional)
 * @request_gpios_match: Do pinname to gpio matching
 * @request_gpios: Request gpios from the kernel
 * @मुक्त_gpios: Free previously requested gpios
 * @verअगरy_gpios: Verअगरy that necessary gpios is present (optional)
 * @रेजिस्टर_backlight: Used to रेजिस्टर backlight device (optional)
 * @unरेजिस्टर_backlight: Unरेजिस्टर backlight device (optional)
 * @set_var: Configure LCD with values from variables like @rotate and @bgr
 *           (optional)
 * @set_gamma: Set Gamma curve (optional)
 *
 * Most of these operations have शेष functions asचिन्हित to them in
 *     fbtft_framebuffer_alloc()
 */
काष्ठा fbtft_ops अणु
	पूर्णांक (*ग_लिखो)(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
	पूर्णांक (*पढ़ो)(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
	पूर्णांक (*ग_लिखो_vmem)(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len);
	व्योम (*ग_लिखो_रेजिस्टर)(काष्ठा fbtft_par *par, पूर्णांक len, ...);

	व्योम (*set_addr_win)(काष्ठा fbtft_par *par,
			     पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye);
	व्योम (*reset)(काष्ठा fbtft_par *par);
	व्योम (*सूची_गढ़ोty)(काष्ठा fb_info *info, पूर्णांक from, पूर्णांक to);
	व्योम (*update_display)(काष्ठा fbtft_par *par,
			       अचिन्हित पूर्णांक start_line, अचिन्हित पूर्णांक end_line);
	पूर्णांक (*init_display)(काष्ठा fbtft_par *par);
	पूर्णांक (*blank)(काष्ठा fbtft_par *par, bool on);

	अचिन्हित दीर्घ (*request_gpios_match)(काष्ठा fbtft_par *par,
					     स्थिर काष्ठा fbtft_gpio *gpio);
	पूर्णांक (*request_gpios)(काष्ठा fbtft_par *par);
	पूर्णांक (*verअगरy_gpios)(काष्ठा fbtft_par *par);

	व्योम (*रेजिस्टर_backlight)(काष्ठा fbtft_par *par);
	व्योम (*unरेजिस्टर_backlight)(काष्ठा fbtft_par *par);

	पूर्णांक (*set_var)(काष्ठा fbtft_par *par);
	पूर्णांक (*set_gamma)(काष्ठा fbtft_par *par, u32 *curves);
पूर्ण;

/**
 * काष्ठा fbtft_display - Describes the display properties
 * @width: Width of display in pixels
 * @height: Height of display in pixels
 * @regwidth: LCD Controller Register width in bits
 * @buswidth: Display पूर्णांकerface bus width in bits
 * @backlight: Backlight type.
 * @fbtftops: FBTFT operations provided by driver or device (platक्रमm_data)
 * @bpp: Bits per pixel
 * @fps: Frames per second
 * @txbuflen: Size of transmit buffer
 * @init_sequence: Poपूर्णांकer to LCD initialization array
 * @gamma: String representation of Gamma curve(s)
 * @gamma_num: Number of Gamma curves
 * @gamma_len: Number of values per Gamma curve
 * @debug: Initial debug value
 *
 * This काष्ठाure is not stored by FBTFT except क्रम init_sequence.
 */
काष्ठा fbtft_display अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक regwidth;
	अचिन्हित पूर्णांक buswidth;
	अचिन्हित पूर्णांक backlight;
	काष्ठा fbtft_ops fbtftops;
	अचिन्हित पूर्णांक bpp;
	अचिन्हित पूर्णांक fps;
	पूर्णांक txbuflen;
	स्थिर s16 *init_sequence;
	अक्षर *gamma;
	पूर्णांक gamma_num;
	पूर्णांक gamma_len;
	अचिन्हित दीर्घ debug;
पूर्ण;

/**
 * काष्ठा fbtft_platक्रमm_data - Passes display specअगरic data to the driver
 * @display: Display properties
 * @gpios: Poपूर्णांकer to an array of pinname to gpio mappings
 * @rotate: Display rotation angle
 * @bgr: LCD Controller BGR bit
 * @fps: Frames per second (this will go away, use @fps in @fbtft_display)
 * @txbuflen: Size of transmit buffer
 * @startbyte: When set, enables use of Startbyte in transfers
 * @gamma: String representation of Gamma curve(s)
 * @extra: A way to pass extra info
 */
काष्ठा fbtft_platक्रमm_data अणु
	काष्ठा fbtft_display display;
	अचिन्हित पूर्णांक rotate;
	bool bgr;
	अचिन्हित पूर्णांक fps;
	पूर्णांक txbuflen;
	u8 startbyte;
	अक्षर *gamma;
	व्योम *extra;
पूर्ण;

/**
 * काष्ठा fbtft_par - Main FBTFT data काष्ठाure
 *
 * This काष्ठाure holds all relevant data to operate the display
 *
 * See sourcefile क्रम करोcumentation since nested काष्ठाs is not
 * supported by kernel-करोc.
 *
 */
/* @spi: Set अगर it is a SPI device
 * @pdev: Set अगर it is a platक्रमm device
 * @info: Poपूर्णांकer to framebuffer fb_info काष्ठाure
 * @pdata: Poपूर्णांकer to platक्रमm data
 * @ssbuf: Not used
 * @pseuकरो_palette: Used by fb_set_colreg()
 * @txbuf.buf: Transmit buffer
 * @txbuf.len: Transmit buffer length
 * @buf: Small buffer used when writing init data over SPI
 * @startbyte: Used by some controllers when in SPI mode.
 *             Format: 6 bit Device id + RS bit + RW bit
 * @fbtftops: FBTFT operations provided by driver or device (platक्रमm_data)
 * @dirty_lock: Protects dirty_lines_start and dirty_lines_end
 * @dirty_lines_start: Where to begin updating display
 * @dirty_lines_end: Where to end updating display
 * @gpio.reset: GPIO used to reset display
 * @gpio.dc: Data/Command संकेत, also known as RS
 * @gpio.rd: Read latching संकेत
 * @gpio.wr: Write latching संकेत
 * @gpio.latch: Bus latch संकेत, eg. 16->8 bit bus latch
 * @gpio.cs: LCD Chip Select with parallel पूर्णांकerface bus
 * @gpio.db[16]: Parallel databus
 * @gpio.led[16]: Led control संकेतs
 * @gpio.aux[16]: Auxiliary संकेतs, not used by core
 * @init_sequence: Poपूर्णांकer to LCD initialization array
 * @gamma.lock: Mutex क्रम Gamma curve locking
 * @gamma.curves: Poपूर्णांकer to Gamma curve array
 * @gamma.num_values: Number of values per Gamma curve
 * @gamma.num_curves: Number of Gamma curves
 * @debug: Poपूर्णांकer to debug value
 * @current_debug:
 * @first_update_करोne: Used to only समय the first display update
 * @update_समय: Used to calculate 'fps' in debug output
 * @bgr: BGR mode/\न
 * @extra: Extra info needed by driver
 */
काष्ठा fbtft_par अणु
	काष्ठा spi_device *spi;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा fb_info *info;
	काष्ठा fbtft_platक्रमm_data *pdata;
	u16 *ssbuf;
	u32 pseuकरो_palette[16];
	काष्ठा अणु
		व्योम *buf;
		माप_प्रकार len;
	पूर्ण txbuf;
	u8 *buf;
	u8 startbyte;
	काष्ठा fbtft_ops fbtftops;
	spinlock_t dirty_lock;
	अचिन्हित पूर्णांक dirty_lines_start;
	अचिन्हित पूर्णांक dirty_lines_end;
	काष्ठा अणु
		काष्ठा gpio_desc *reset;
		काष्ठा gpio_desc *dc;
		काष्ठा gpio_desc *rd;
		काष्ठा gpio_desc *wr;
		काष्ठा gpio_desc *latch;
		काष्ठा gpio_desc *cs;
		काष्ठा gpio_desc *db[16];
		काष्ठा gpio_desc *led[16];
		काष्ठा gpio_desc *aux[16];
	पूर्ण gpio;
	स्थिर s16 *init_sequence;
	काष्ठा अणु
		काष्ठा mutex lock;
		u32 *curves;
		पूर्णांक num_values;
		पूर्णांक num_curves;
	पूर्ण gamma;
	अचिन्हित दीर्घ debug;
	bool first_update_करोne;
	kसमय_प्रकार update_समय;
	bool bgr;
	व्योम *extra;
	bool polarity;
पूर्ण;

#घोषणा NUMARGS(...)  (माप((पूर्णांक[])अणु__VA_ARGS__पूर्ण) / माप(पूर्णांक))

#घोषणा ग_लिखो_reg(par, ...)                                            \
	((par)->fbtftops.ग_लिखो_रेजिस्टर(par, NUMARGS(__VA_ARGS__), __VA_ARGS__))

/* fbtft-core.c */
पूर्णांक fbtft_ग_लिखो_buf_dc(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len, पूर्णांक dc);
__म_लिखो(5, 6)
व्योम fbtft_dbg_hex(स्थिर काष्ठा device *dev, पूर्णांक groupsize,
		   व्योम *buf, माप_प्रकार len, स्थिर अक्षर *fmt, ...);
काष्ठा fb_info *fbtft_framebuffer_alloc(काष्ठा fbtft_display *display,
					काष्ठा device *dev,
					काष्ठा fbtft_platक्रमm_data *pdata);
व्योम fbtft_framebuffer_release(काष्ठा fb_info *info);
पूर्णांक fbtft_रेजिस्टर_framebuffer(काष्ठा fb_info *fb_info);
पूर्णांक fbtft_unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info);
व्योम fbtft_रेजिस्टर_backlight(काष्ठा fbtft_par *par);
व्योम fbtft_unरेजिस्टर_backlight(काष्ठा fbtft_par *par);
पूर्णांक fbtft_init_display(काष्ठा fbtft_par *par);
पूर्णांक fbtft_probe_common(काष्ठा fbtft_display *display, काष्ठा spi_device *sdev,
		       काष्ठा platक्रमm_device *pdev);
पूर्णांक fbtft_हटाओ_common(काष्ठा device *dev, काष्ठा fb_info *info);

/* fbtft-io.c */
पूर्णांक fbtft_ग_लिखो_spi(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_spi_emulate_9(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
पूर्णांक fbtft_पढ़ो_spi(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_gpio8_wr(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_gpio16_wr(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_gpio16_wr_latched(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len);

/* fbtft-bus.c */
पूर्णांक fbtft_ग_लिखो_vmem8_bus8(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_vmem16_bus16(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_vmem16_bus8(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len);
पूर्णांक fbtft_ग_लिखो_vmem16_bus9(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len);
व्योम fbtft_ग_लिखो_reg8_bus8(काष्ठा fbtft_par *par, पूर्णांक len, ...);
व्योम fbtft_ग_लिखो_reg8_bus9(काष्ठा fbtft_par *par, पूर्णांक len, ...);
व्योम fbtft_ग_लिखो_reg16_bus8(काष्ठा fbtft_par *par, पूर्णांक len, ...);
व्योम fbtft_ग_लिखो_reg16_bus16(काष्ठा fbtft_par *par, पूर्णांक len, ...);

#घोषणा FBTFT_REGISTER_DRIVER(_name, _compatible, _display)                \
									   \
अटल पूर्णांक fbtft_driver_probe_spi(काष्ठा spi_device *spi)                  \
अणु                                                                          \
	वापस fbtft_probe_common(_display, spi, शून्य);                    \
पूर्ण                                                                          \
									   \
अटल पूर्णांक fbtft_driver_हटाओ_spi(काष्ठा spi_device *spi)                 \
अणु                                                                          \
	काष्ठा fb_info *info = spi_get_drvdata(spi);                       \
									   \
	वापस fbtft_हटाओ_common(&spi->dev, info);                       \
पूर्ण                                                                          \
									   \
अटल पूर्णांक fbtft_driver_probe_pdev(काष्ठा platक्रमm_device *pdev)           \
अणु                                                                          \
	वापस fbtft_probe_common(_display, शून्य, pdev);                   \
पूर्ण                                                                          \
									   \
अटल पूर्णांक fbtft_driver_हटाओ_pdev(काष्ठा platक्रमm_device *pdev)          \
अणु                                                                          \
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);                 \
									   \
	वापस fbtft_हटाओ_common(&pdev->dev, info);                      \
पूर्ण                                                                          \
									   \
अटल स्थिर काष्ठा of_device_id dt_ids[] = अणु                              \
	अणु .compatible = _compatible पूर्ण,                                     \
	अणुपूर्ण,                                                                \
पूर्ण;                                                                         \
									   \
MODULE_DEVICE_TABLE(of, dt_ids);                                           \
									   \
									   \
अटल काष्ठा spi_driver fbtft_driver_spi_driver = अणु                       \
	.driver = अणु                                                        \
		.name   = _name,                                           \
		.of_match_table = dt_ids,                                  \
	पूर्ण,                                                                 \
	.probe  = fbtft_driver_probe_spi,                                  \
	.हटाओ = fbtft_driver_हटाओ_spi,                                 \
पूर्ण;                                                                         \
									   \
अटल काष्ठा platक्रमm_driver fbtft_driver_platक्रमm_driver = अणु             \
	.driver = अणु                                                        \
		.name   = _name,                                           \
		.owner  = THIS_MODULE,                                     \
		.of_match_table = dt_ids,                                  \
	पूर्ण,                                                                 \
	.probe  = fbtft_driver_probe_pdev,                                 \
	.हटाओ = fbtft_driver_हटाओ_pdev,                                \
पूर्ण;                                                                         \
									   \
अटल पूर्णांक __init fbtft_driver_module_init(व्योम)                           \
अणु                                                                          \
	पूर्णांक ret;                                                           \
									   \
	ret = spi_रेजिस्टर_driver(&fbtft_driver_spi_driver);               \
	अगर (ret < 0)                                                       \
		वापस ret;                                                \
	वापस platक्रमm_driver_रेजिस्टर(&fbtft_driver_platक्रमm_driver);    \
पूर्ण                                                                          \
									   \
अटल व्योम __निकास fbtft_driver_module_निकास(व्योम)                          \
अणु                                                                          \
	spi_unरेजिस्टर_driver(&fbtft_driver_spi_driver);                   \
	platक्रमm_driver_unरेजिस्टर(&fbtft_driver_platक्रमm_driver);         \
पूर्ण                                                                          \
									   \
module_init(fbtft_driver_module_init);                                     \
module_निकास(fbtft_driver_module_निकास);

/* Debug macros */

/* लघुhand debug levels */
#घोषणा DEBUG_LEVEL_1	DEBUG_REQUEST_GPIOS
#घोषणा DEBUG_LEVEL_2	(DEBUG_LEVEL_1 | DEBUG_DRIVER_INIT_FUNCTIONS        \
				       | DEBUG_TIME_FIRST_UPDATE)
#घोषणा DEBUG_LEVEL_3	(DEBUG_LEVEL_2 | DEBUG_RESET | DEBUG_INIT_DISPLAY   \
				       | DEBUG_BLANK | DEBUG_REQUEST_GPIOS  \
				       | DEBUG_FREE_GPIOS                   \
				       | DEBUG_VERIFY_GPIOS                 \
				       | DEBUG_BACKLIGHT | DEBUG_SYSFS)
#घोषणा DEBUG_LEVEL_4	(DEBUG_LEVEL_2 | DEBUG_FB_READ | DEBUG_FB_WRITE     \
				       | DEBUG_FB_FILLRECT                  \
				       | DEBUG_FB_COPYAREA                  \
				       | DEBUG_FB_IMAGEBLIT | DEBUG_FB_BLANK)
#घोषणा DEBUG_LEVEL_5	(DEBUG_LEVEL_3 | DEBUG_UPDATE_DISPLAY)
#घोषणा DEBUG_LEVEL_6	(DEBUG_LEVEL_4 | DEBUG_LEVEL_5)
#घोषणा DEBUG_LEVEL_7	0xFFFFFFFF

#घोषणा DEBUG_DRIVER_INIT_FUNCTIONS BIT(3)
#घोषणा DEBUG_TIME_FIRST_UPDATE     BIT(4)
#घोषणा DEBUG_TIME_EACH_UPDATE      BIT(5)
#घोषणा DEBUG_DEFERRED_IO           BIT(6)
#घोषणा DEBUG_FBTFT_INIT_FUNCTIONS  BIT(7)

/* fbops */
#घोषणा DEBUG_FB_READ               BIT(8)
#घोषणा DEBUG_FB_WRITE              BIT(9)
#घोषणा DEBUG_FB_FILLRECT           BIT(10)
#घोषणा DEBUG_FB_COPYAREA           BIT(11)
#घोषणा DEBUG_FB_IMAGEBLIT          BIT(12)
#घोषणा DEBUG_FB_SETCOLREG          BIT(13)
#घोषणा DEBUG_FB_BLANK              BIT(14)

#घोषणा DEBUG_SYSFS                 BIT(16)

/* fbtftops */
#घोषणा DEBUG_BACKLIGHT             BIT(17)
#घोषणा DEBUG_READ                  BIT(18)
#घोषणा DEBUG_WRITE                 BIT(19)
#घोषणा DEBUG_WRITE_VMEM            BIT(20)
#घोषणा DEBUG_WRITE_REGISTER        BIT(21)
#घोषणा DEBUG_SET_ADDR_WIN          BIT(22)
#घोषणा DEBUG_RESET                 BIT(23)
#घोषणा DEBUG_MKसूचीTY               BIT(24)
#घोषणा DEBUG_UPDATE_DISPLAY        BIT(25)
#घोषणा DEBUG_INIT_DISPLAY          BIT(26)
#घोषणा DEBUG_BLANK                 BIT(27)
#घोषणा DEBUG_REQUEST_GPIOS         BIT(28)
#घोषणा DEBUG_FREE_GPIOS            BIT(29)
#घोषणा DEBUG_REQUEST_GPIOS_MATCH   BIT(30)
#घोषणा DEBUG_VERIFY_GPIOS          BIT(31)

#घोषणा fbtft_init_dbg(dev, क्रमmat, arg...)                  \
करो अणु                                                         \
	अगर (unlikely((dev)->platक्रमm_data &&                 \
	    (((काष्ठा fbtft_platक्रमm_data *)(dev)->platक्रमm_data)->display.debug & DEBUG_DRIVER_INIT_FUNCTIONS))) \
		dev_info(dev, क्रमmat, ##arg);                \
पूर्ण जबतक (0)

#घोषणा fbtft_par_dbg(level, par, क्रमmat, arg...)            \
करो अणु                                                         \
	अगर (unlikely((par)->debug & (level)))                    \
		dev_info((par)->info->device, क्रमmat, ##arg);  \
पूर्ण जबतक (0)

#घोषणा fbtft_par_dbg_hex(level, par, dev, type, buf, num, क्रमmat, arg...) \
करो अणु                                                                       \
	अगर (unlikely((par)->debug & (level)))                                  \
		fbtft_dbg_hex(dev, माप(type), buf,\
			      (num) * माप(type), क्रमmat, ##arg); \
पूर्ण जबतक (0)

#पूर्ण_अगर /* __LINUX_FBTFT_H */
