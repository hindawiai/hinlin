<शैली गुरु>
/*
 * arch/arm/include/यंत्र/hardware/locomo.h
 *
 * This file contains the definitions क्रम the LoCoMo G/A Chip
 *
 * (C) Copyright 2004 John Lenz
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * Based on sa1111.h
 */
#अगर_अघोषित _ASM_ARCH_LOCOMO
#घोषणा _ASM_ARCH_LOCOMO

#घोषणा locomo_ग_लिखोl(val,addr)	(अणु *(अस्थिर u16 *)(addr) = (val); पूर्ण)
#घोषणा locomo_पढ़ोl(addr)	(*(अस्थिर u16 *)(addr))

/* LOCOMO version */
#घोषणा LOCOMO_VER	0x00

/* Pin status */
#घोषणा LOCOMO_ST	0x04

/* Pin status */
#घोषणा LOCOMO_C32K	0x08

/* Interrupt controller */
#घोषणा LOCOMO_ICR	0x0C

/* MCS decoder क्रम boot selecting */
#घोषणा LOCOMO_MCSX0	0x10
#घोषणा LOCOMO_MCSX1	0x14
#घोषणा LOCOMO_MCSX2	0x18
#घोषणा LOCOMO_MCSX3	0x1c

/* Touch panel controller */
#घोषणा LOCOMO_ASD	0x20		/* AD start delay */
#घोषणा LOCOMO_HSD	0x28		/* HSYS delay */
#घोषणा LOCOMO_HSC	0x2c		/* HSYS period */
#घोषणा LOCOMO_TADC	0x30		/* tablet ADC घड़ी */


/* Long समय समयr */
#घोषणा LOCOMO_LTC	0xd8		/* LTC पूर्णांकerrupt setting */
#घोषणा LOCOMO_LTINT	0xdc		/* LTC पूर्णांकerrupt */

/* DAC control संकेत क्रम LCD (COMADJ ) */
#घोषणा LOCOMO_DAC		0xe0
/* DAC control */
#घोषणा	LOCOMO_DAC_SCLOEB	0x08	/* SCL pin output data       */
#घोषणा	LOCOMO_DAC_TEST		0x04	/* Test bit                  */
#घोषणा	LOCOMO_DAC_SDA		0x02	/* SDA pin level (पढ़ो-only) */
#घोषणा	LOCOMO_DAC_SDAOEB	0x01	/* SDA pin output data       */

/* SPI पूर्णांकerface */
#घोषणा LOCOMO_SPI	0x60
#घोषणा LOCOMO_SPIMD	0x00		/* SPI mode setting */
#घोषणा LOCOMO_SPICT	0x04		/* SPI mode control */
#घोषणा LOCOMO_SPIST	0x08		/* SPI status */
#घोषणा	LOCOMO_SPI_TEND	(1 << 3)	/* Transfer end bit */
#घोषणा	LOCOMO_SPI_REND	(1 << 2)	/* Receive end bit */
#घोषणा	LOCOMO_SPI_RFW	(1 << 1)	/* ग_लिखो buffer bit */
#घोषणा	LOCOMO_SPI_RFR	(1)		/* पढ़ो buffer bit */

#घोषणा LOCOMO_SPIIS	0x10		/* SPI पूर्णांकerrupt status */
#घोषणा LOCOMO_SPIWE	0x14		/* SPI पूर्णांकerrupt status ग_लिखो enable */
#घोषणा LOCOMO_SPIIE	0x18		/* SPI पूर्णांकerrupt enable */
#घोषणा LOCOMO_SPIIR	0x1c		/* SPI पूर्णांकerrupt request */
#घोषणा LOCOMO_SPITD	0x20		/* SPI transfer data ग_लिखो */
#घोषणा LOCOMO_SPIRD	0x24		/* SPI receive data पढ़ो */
#घोषणा LOCOMO_SPITS	0x28		/* SPI transfer data shअगरt */
#घोषणा LOCOMO_SPIRS	0x2C		/* SPI receive data shअगरt */

/* GPIO */
#घोषणा LOCOMO_GPD		0x90	/* GPIO direction */
#घोषणा LOCOMO_GPE		0x94	/* GPIO input enable */
#घोषणा LOCOMO_GPL		0x98	/* GPIO level */
#घोषणा LOCOMO_GPO		0x9c	/* GPIO out data setting */
#घोषणा LOCOMO_GRIE		0xa0	/* GPIO rise detection */
#घोषणा LOCOMO_GFIE		0xa4	/* GPIO fall detection */
#घोषणा LOCOMO_GIS		0xa8	/* GPIO edge detection status */
#घोषणा LOCOMO_GWE		0xac	/* GPIO status ग_लिखो enable */
#घोषणा LOCOMO_GIE		0xb0	/* GPIO पूर्णांकerrupt enable */
#घोषणा LOCOMO_GIR		0xb4	/* GPIO पूर्णांकerrupt request */
#घोषणा	LOCOMO_GPIO(Nb)		(0x01 << (Nb))
#घोषणा LOCOMO_GPIO_RTS		LOCOMO_GPIO(0)
#घोषणा LOCOMO_GPIO_CTS		LOCOMO_GPIO(1)
#घोषणा LOCOMO_GPIO_DSR		LOCOMO_GPIO(2)
#घोषणा LOCOMO_GPIO_DTR		LOCOMO_GPIO(3)
#घोषणा LOCOMO_GPIO_LCD_VSHA_ON	LOCOMO_GPIO(4)
#घोषणा LOCOMO_GPIO_LCD_VSHD_ON	LOCOMO_GPIO(5)
#घोषणा LOCOMO_GPIO_LCD_VEE_ON	LOCOMO_GPIO(6)
#घोषणा LOCOMO_GPIO_LCD_MOD	LOCOMO_GPIO(7)
#घोषणा LOCOMO_GPIO_DAC_ON	LOCOMO_GPIO(8)
#घोषणा LOCOMO_GPIO_FL_VR	LOCOMO_GPIO(9)
#घोषणा LOCOMO_GPIO_DAC_SDATA	LOCOMO_GPIO(10)
#घोषणा LOCOMO_GPIO_DAC_SCK	LOCOMO_GPIO(11)
#घोषणा LOCOMO_GPIO_DAC_SLOAD	LOCOMO_GPIO(12)
#घोषणा LOCOMO_GPIO_CARD_DETECT LOCOMO_GPIO(13)
#घोषणा LOCOMO_GPIO_WRITE_PROT  LOCOMO_GPIO(14)
#घोषणा LOCOMO_GPIO_CARD_POWER  LOCOMO_GPIO(15)

/* Start the definitions of the devices.  Each device has an initial
 * base address and a series of offsets from that base address. */

/* Keyboard controller */
#घोषणा LOCOMO_KEYBOARD		0x40
#घोषणा LOCOMO_KIB		0x00	/* KIB level */
#घोषणा LOCOMO_KSC		0x04	/* KSTRB control */
#घोषणा LOCOMO_KCMD		0x08	/* KSTRB command */
#घोषणा LOCOMO_KIC		0x0c	/* Key पूर्णांकerrupt */

/* Front light adjusपंचांगent controller */
#घोषणा LOCOMO_FRONTLIGHT	0xc8
#घोषणा LOCOMO_ALS		0x00	/* Adjust light cycle */
#घोषणा LOCOMO_ALD		0x04	/* Adjust light duty */

#घोषणा LOCOMO_ALC_EN		0x8000

/* Backlight controller: TFT संकेत */
#घोषणा LOCOMO_BACKLIGHT	0x38
#घोषणा LOCOMO_TC		0x00		/* TFT control संकेत */
#घोषणा LOCOMO_CPSD		0x04		/* CPS delay */

/* Audio controller */
#घोषणा LOCOMO_AUDIO		0x54
#घोषणा LOCOMO_ACC		0x00	/* Audio घड़ी */
#घोषणा LOCOMO_PAIF		0xD0	/* PCM audio पूर्णांकerface */
/* Audio घड़ी */
#घोषणा	LOCOMO_ACC_XON		0x80
#घोषणा	LOCOMO_ACC_XEN		0x40
#घोषणा	LOCOMO_ACC_XSEL0	0x00
#घोषणा	LOCOMO_ACC_XSEL1	0x20
#घोषणा	LOCOMO_ACC_MCLKEN	0x10
#घोषणा	LOCOMO_ACC_64FSEN	0x08
#घोषणा	LOCOMO_ACC_CLKSEL000	0x00	/* mclk  2 */
#घोषणा	LOCOMO_ACC_CLKSEL001	0x01	/* mclk  3 */
#घोषणा	LOCOMO_ACC_CLKSEL010	0x02	/* mclk  4 */
#घोषणा	LOCOMO_ACC_CLKSEL011	0x03	/* mclk  6 */
#घोषणा	LOCOMO_ACC_CLKSEL100	0x04	/* mclk  8 */
#घोषणा	LOCOMO_ACC_CLKSEL101	0x05	/* mclk 12 */
/* PCM audio पूर्णांकerface */
#घोषणा	LOCOMO_PAIF_SCINV	0x20
#घोषणा	LOCOMO_PAIF_SCEN	0x10
#घोषणा	LOCOMO_PAIF_LRCRST	0x08
#घोषणा	LOCOMO_PAIF_LRCEVE	0x04
#घोषणा	LOCOMO_PAIF_LRCINV	0x02
#घोषणा	LOCOMO_PAIF_LRCEN	0x01

/* LED controller */
#घोषणा LOCOMO_LED		0xe8
#घोषणा LOCOMO_LPT0		0x00
#घोषणा LOCOMO_LPT1		0x04
/* LED control */
#घोषणा LOCOMO_LPT_TOFH		0x80
#घोषणा LOCOMO_LPT_TOFL		0x08
#घोषणा LOCOMO_LPT_TOH(TOH)	((TOH & 0x7) << 4)
#घोषणा LOCOMO_LPT_TOL(TOL)	((TOL & 0x7))

बाह्य काष्ठा bus_type locomo_bus_type;

#घोषणा LOCOMO_DEVID_KEYBOARD	0
#घोषणा LOCOMO_DEVID_FRONTLIGHT	1
#घोषणा LOCOMO_DEVID_BACKLIGHT	2
#घोषणा LOCOMO_DEVID_AUDIO	3
#घोषणा LOCOMO_DEVID_LED	4
#घोषणा LOCOMO_DEVID_UART	5
#घोषणा LOCOMO_DEVID_SPI	6

काष्ठा locomo_dev अणु
	काष्ठा device	dev;
	अचिन्हित पूर्णांक	devid;
	अचिन्हित पूर्णांक	irq[1];

	व्योम		*mapbase;
	अचिन्हित दीर्घ	length;

	u64		dma_mask;
पूर्ण;

#घोषणा LOCOMO_DEV(_d)	container_of((_d), काष्ठा locomo_dev, dev)

#घोषणा locomo_get_drvdata(d)	dev_get_drvdata(&(d)->dev)
#घोषणा locomo_set_drvdata(d,p)	dev_set_drvdata(&(d)->dev, p)

काष्ठा locomo_driver अणु
	काष्ठा device_driver	drv;
	अचिन्हित पूर्णांक		devid;
	पूर्णांक (*probe)(काष्ठा locomo_dev *);
	व्योम (*हटाओ)(काष्ठा locomo_dev *);
पूर्ण;

#घोषणा LOCOMO_DRV(_d)	container_of((_d), काष्ठा locomo_driver, drv)

#घोषणा LOCOMO_DRIVER_NAME(_ldev) ((_ldev)->dev.driver->name)

व्योम locomo_lcd_घातer(काष्ठा locomo_dev *, पूर्णांक, अचिन्हित पूर्णांक);

पूर्णांक locomo_driver_रेजिस्टर(काष्ठा locomo_driver *);
व्योम locomo_driver_unरेजिस्टर(काष्ठा locomo_driver *);

/* GPIO control functions */
व्योम locomo_gpio_set_dir(काष्ठा device *dev, अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक dir);
पूर्णांक locomo_gpio_पढ़ो_level(काष्ठा device *dev, अचिन्हित पूर्णांक bits);
पूर्णांक locomo_gpio_पढ़ो_output(काष्ठा device *dev, अचिन्हित पूर्णांक bits);
व्योम locomo_gpio_ग_लिखो(काष्ठा device *dev, अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक set);

/* M62332 control function */
व्योम locomo_m62332_senddata(काष्ठा locomo_dev *ldev, अचिन्हित पूर्णांक dac_data, पूर्णांक channel);

/* Frontlight control */
व्योम locomo_frontlight_set(काष्ठा locomo_dev *dev, पूर्णांक duty, पूर्णांक vr, पूर्णांक bpwf);

काष्ठा locomo_platक्रमm_data अणु
	पूर्णांक	irq_base;	/* IRQ base क्रम cascaded on-chip IRQs */
पूर्ण;

#पूर्ण_अगर
