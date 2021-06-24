<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Freescale SPI controller driver.
 *
 * Maपूर्णांकainer: Kumar Gala
 *
 * Copyright (C) 2006 Polycom, Inc.
 * Copyright 2010 Freescale Semiconductor, Inc.
 *
 * CPM SPI and QE buffer descriptors mode support:
 * Copyright (c) 2009  MontaVista Software, Inc.
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * GRLIB support:
 * Copyright (c) 2012 Aeroflex Gaisler AB.
 * Author: Andreas Larsson <andreas@gaisler.com>
 */

#अगर_अघोषित __SPI_FSL_SPI_H__
#घोषणा __SPI_FSL_SPI_H__

/* SPI Controller रेजिस्टरs */
काष्ठा fsl_spi_reg अणु
	__be32 cap; /* TYPE_GRLIB specअगरic */
	u8 res1[0x1C];
	__be32 mode;
	__be32 event;
	__be32 mask;
	__be32 command;
	__be32 transmit;
	__be32 receive;
	__be32 slvsel; /* TYPE_GRLIB specअगरic */
पूर्ण;

/* SPI Controller mode रेजिस्टर definitions */
#घोषणा	SPMODE_LOOP		(1 << 30)
#घोषणा	SPMODE_CI_INACTIVEHIGH	(1 << 29)
#घोषणा	SPMODE_CP_BEGIN_EDGECLK	(1 << 28)
#घोषणा	SPMODE_DIV16		(1 << 27)
#घोषणा	SPMODE_REV		(1 << 26)
#घोषणा	SPMODE_MS		(1 << 25)
#घोषणा	SPMODE_ENABLE		(1 << 24)
#घोषणा	SPMODE_LEN(x)		((x) << 20)
#घोषणा	SPMODE_PM(x)		((x) << 16)
#घोषणा	SPMODE_OP		(1 << 14)
#घोषणा	SPMODE_CG(x)		((x) << 7)

/* TYPE_GRLIB SPI Controller capability रेजिस्टर definitions */
#घोषणा SPCAP_SSEN(x)		(((x) >> 16) & 0x1)
#घोषणा SPCAP_SSSZ(x)		(((x) >> 24) & 0xff)
#घोषणा SPCAP_MAXWLEN(x)	(((x) >> 20) & 0xf)

/*
 * Default क्रम SPI Mode:
 *	SPI MODE 0 (inactive low, phase middle, MSB, 8-bit length, slow clk
 */
#घोषणा	SPMODE_INIT_VAL (SPMODE_CI_INACTIVEHIGH | SPMODE_DIV16 | SPMODE_REV | \
			 SPMODE_MS | SPMODE_LEN(7) | SPMODE_PM(0xf))

/* SPIE रेजिस्टर values */
#घोषणा	SPIE_NE		0x00000200	/* Not empty */
#घोषणा	SPIE_NF		0x00000100	/* Not full */

/* SPIM रेजिस्टर values */
#घोषणा	SPIM_NE		0x00000200	/* Not empty */
#घोषणा	SPIM_NF		0x00000100	/* Not full */

#पूर्ण_अगर /* __SPI_FSL_SPI_H__ */
