<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* drivers/video/backlight/ili9320.h
 *
 * ILI9320 LCD controller driver core.
 *
 * Copyright 2007 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * http://armlinux.simtec.co.uk/
*/

/* Holder क्रम रेजिस्टर and value pairs. */
काष्ठा ili9320_reg अणु
	अचिन्हित लघु		address;
	अचिन्हित लघु		value;
पूर्ण;

काष्ठा ili9320;

काष्ठा ili9320_client अणु
	स्थिर अक्षर	*name;
	पूर्णांक	(*init)(काष्ठा ili9320 *ili, काष्ठा ili9320_platdata *cfg);

पूर्ण;
/* Device attached via an SPI bus. */
काष्ठा  ili9320_spi अणु
	काष्ठा spi_device	*dev;
	काष्ठा spi_message	message;
	काष्ठा spi_transfer	xfer[2];

	अचिन्हित अक्षर		id;
	अचिन्हित अक्षर		buffer_addr[4];
	अचिन्हित अक्षर		buffer_data[4];
पूर्ण;

/* ILI9320 device state. */
काष्ठा ili9320 अणु
	जोड़ अणु
		काष्ठा ili9320_spi	spi;	/* SPI attachged device. */
	पूर्ण access;				/* Register access method. */

	काष्ठा device			*dev;
	काष्ठा lcd_device		*lcd;	/* LCD device we created. */
	काष्ठा ili9320_client		*client;
	काष्ठा ili9320_platdata		*platdata;

	पूर्णांक				 घातer; /* current घातer state. */
	पूर्णांक				 initialised;

	अचिन्हित लघु			 display1;
	अचिन्हित लघु			 घातer1;

	पूर्णांक (*ग_लिखो)(काष्ठा ili9320 *ili, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
पूर्ण;


/* ILI9320 रेजिस्टर access routines */

बाह्य पूर्णांक ili9320_ग_लिखो(काष्ठा ili9320 *ili,
			 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value);

बाह्य पूर्णांक ili9320_ग_लिखो_regs(काष्ठा ili9320 *ili,
			      स्थिर काष्ठा ili9320_reg *values,
			      पूर्णांक nr_values);

/* Device probe */

बाह्य पूर्णांक ili9320_probe_spi(काष्ठा spi_device *spi,
			     काष्ठा ili9320_client *cli);

बाह्य पूर्णांक ili9320_हटाओ(काष्ठा ili9320 *lcd);
बाह्य व्योम ili9320_shutकरोwn(काष्ठा ili9320 *lcd);

/* PM */

बाह्य पूर्णांक ili9320_suspend(काष्ठा ili9320 *lcd);
बाह्य पूर्णांक ili9320_resume(काष्ठा ili9320 *lcd);
