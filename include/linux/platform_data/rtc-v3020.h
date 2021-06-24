<शैली गुरु>
/*
 * v3020.h - Registers definition and platक्रमm data काष्ठाure क्रम the v3020 RTC.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006, 8D Technologies inc.
 */
#अगर_अघोषित __LINUX_V3020_H
#घोषणा __LINUX_V3020_H

/* The v3020 has only one data pin but which one
 * is used depends on the board. */
काष्ठा v3020_platक्रमm_data अणु
	पूर्णांक leftshअगरt; /* (1<<(leftshअगरt)) & पढ़ोl() */

	अचिन्हित पूर्णांक use_gpio:1;
	अचिन्हित पूर्णांक gpio_cs;
	अचिन्हित पूर्णांक gpio_wr;
	अचिन्हित पूर्णांक gpio_rd;
	अचिन्हित पूर्णांक gpio_io;
पूर्ण;

#घोषणा V3020_STATUS_0	0x00
#घोषणा V3020_STATUS_1	0x01
#घोषणा V3020_SECONDS	0x02
#घोषणा V3020_MINUTES	0x03
#घोषणा V3020_HOURS		0x04
#घोषणा V3020_MONTH_DAY	0x05
#घोषणा V3020_MONTH		0x06
#घोषणा V3020_YEAR		0x07
#घोषणा V3020_WEEK_DAY	0x08
#घोषणा V3020_WEEK		0x09

#घोषणा V3020_IS_COMMAND(val) ((val)>=0x0E)

#घोषणा V3020_CMD_RAM2CLOCK	0x0E
#घोषणा V3020_CMD_CLOCK2RAM	0x0F

#पूर्ण_अगर /* __LINUX_V3020_H */
