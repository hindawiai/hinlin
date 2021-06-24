<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kontron PLD driver definitions
 *
 * Copyright (c) 2010-2012 Kontron Europe GmbH
 * Author: Michael Brunner <michael.brunner@kontron.com>
 */

#अगर_अघोषित _LINUX_MFD_KEMPLD_H_
#घोषणा _LINUX_MFD_KEMPLD_H_

/* kempld रेजिस्टर definitions */
#घोषणा KEMPLD_IOINDEX			0xa80
#घोषणा KEMPLD_IODATA			0xa81
#घोषणा KEMPLD_MUTEX_KEY		0x80
#घोषणा KEMPLD_VERSION			0x00
#घोषणा KEMPLD_VERSION_LSB		0x00
#घोषणा KEMPLD_VERSION_MSB		0x01
#घोषणा KEMPLD_VERSION_GET_MINOR(x)	(x & 0x1f)
#घोषणा KEMPLD_VERSION_GET_MAJOR(x)	((x >> 5) & 0x1f)
#घोषणा KEMPLD_VERSION_GET_NUMBER(x)	((x >> 10) & 0xf)
#घोषणा KEMPLD_VERSION_GET_TYPE(x)	((x >> 14) & 0x3)
#घोषणा KEMPLD_BUILDNR			0x02
#घोषणा KEMPLD_BUILDNR_LSB		0x02
#घोषणा KEMPLD_BUILDNR_MSB		0x03
#घोषणा KEMPLD_FEATURE			0x04
#घोषणा KEMPLD_FEATURE_LSB		0x04
#घोषणा KEMPLD_FEATURE_MSB		0x05
#घोषणा KEMPLD_FEATURE_BIT_I2C		(1 << 0)
#घोषणा KEMPLD_FEATURE_BIT_WATCHDOG	(1 << 1)
#घोषणा KEMPLD_FEATURE_BIT_GPIO		(1 << 2)
#घोषणा KEMPLD_FEATURE_MASK_UART	(7 << 3)
#घोषणा KEMPLD_FEATURE_BIT_NMI		(1 << 8)
#घोषणा KEMPLD_FEATURE_BIT_SMI		(1 << 9)
#घोषणा KEMPLD_FEATURE_BIT_SCI		(1 << 10)
#घोषणा KEMPLD_SPEC			0x06
#घोषणा KEMPLD_SPEC_GET_MINOR(x)	(x & 0x0f)
#घोषणा KEMPLD_SPEC_GET_MAJOR(x)	((x >> 4) & 0x0f)
#घोषणा KEMPLD_IRQ_GPIO			0x35
#घोषणा KEMPLD_IRQ_I2C			0x36
#घोषणा KEMPLD_CFG			0x37
#घोषणा KEMPLD_CFG_GPIO_I2C_MUX		(1 << 0)
#घोषणा KEMPLD_CFG_BIOS_WP		(1 << 7)

#घोषणा KEMPLD_CLK			33333333

#घोषणा	KEMPLD_TYPE_RELEASE		0x0
#घोषणा	KEMPLD_TYPE_DEBUG		0x1
#घोषणा	KEMPLD_TYPE_CUSTOM		0x2

#घोषणा KEMPLD_VERSION_LEN		10

/**
 * काष्ठा kempld_info - PLD device inक्रमmation काष्ठाure
 * @major:	PLD major revision
 * @minor:	PLD minor revision
 * @buildnr:	PLD build number
 * @number:	PLD board specअगरic index
 * @type:	PLD type
 * @spec_major:	PLD FW specअगरication major revision
 * @spec_minor:	PLD FW specअगरication minor revision
 * @version:	PLD version string
 */
काष्ठा kempld_info अणु
	अचिन्हित पूर्णांक major;
	अचिन्हित पूर्णांक minor;
	अचिन्हित पूर्णांक buildnr;
	अचिन्हित पूर्णांक number;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक spec_major;
	अचिन्हित पूर्णांक spec_minor;
	अक्षर version[KEMPLD_VERSION_LEN];
पूर्ण;

/**
 * काष्ठा kempld_device_data - Internal representation of the PLD device
 * @io_base:		Poपूर्णांकer to the IO memory
 * @io_index:		Poपूर्णांकer to the IO index रेजिस्टर
 * @io_data:		Poपूर्णांकer to the IO data रेजिस्टर
 * @pld_घड़ी:		PLD घड़ी frequency
 * @feature_mask:	PLD feature mask
 * @dev:		Poपूर्णांकer to kernel device काष्ठाure
 * @info:		KEMPLD info काष्ठाure
 * @lock:		PLD mutex
 */
काष्ठा kempld_device_data अणु
	व्योम __iomem		*io_base;
	व्योम __iomem		*io_index;
	व्योम __iomem		*io_data;
	u32			pld_घड़ी;
	u32			feature_mask;
	काष्ठा device		*dev;
	काष्ठा kempld_info	info;
	काष्ठा mutex		lock;
पूर्ण;

/**
 * काष्ठा kempld_platक्रमm_data - PLD hardware configuration काष्ठाure
 * @pld_घड़ी:			PLD घड़ी frequency
 * @gpio_base			GPIO base pin number
 * @ioresource:			IO addresses of the PLD
 * @get_mutex:			PLD specअगरic get_mutex callback
 * @release_mutex:		PLD specअगरic release_mutex callback
 * @get_info:			PLD specअगरic get_info callback
 * @रेजिस्टर_cells:		PLD specअगरic रेजिस्टर_cells callback
 */
काष्ठा kempld_platक्रमm_data अणु
	u32				pld_घड़ी;
	पूर्णांक				gpio_base;
	काष्ठा resource			*ioresource;
	व्योम (*get_hardware_mutex)	(काष्ठा kempld_device_data *);
	व्योम (*release_hardware_mutex)	(काष्ठा kempld_device_data *);
	पूर्णांक (*get_info)			(काष्ठा kempld_device_data *);
	पूर्णांक (*रेजिस्टर_cells)		(काष्ठा kempld_device_data *);
पूर्ण;

बाह्य व्योम kempld_get_mutex(काष्ठा kempld_device_data *pld);
बाह्य व्योम kempld_release_mutex(काष्ठा kempld_device_data *pld);
बाह्य u8 kempld_पढ़ो8(काष्ठा kempld_device_data *pld, u8 index);
बाह्य व्योम kempld_ग_लिखो8(काष्ठा kempld_device_data *pld, u8 index, u8 data);
बाह्य u16 kempld_पढ़ो16(काष्ठा kempld_device_data *pld, u8 index);
बाह्य व्योम kempld_ग_लिखो16(काष्ठा kempld_device_data *pld, u8 index, u16 data);
बाह्य u32 kempld_पढ़ो32(काष्ठा kempld_device_data *pld, u8 index);
बाह्य व्योम kempld_ग_लिखो32(काष्ठा kempld_device_data *pld, u8 index, u32 data);

#पूर्ण_अगर /* _LINUX_MFD_KEMPLD_H_ */
