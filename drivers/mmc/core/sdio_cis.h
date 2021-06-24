<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/drivers/mmc/core/sdio_cis.h
 *
 * Author:	Nicolas Pitre
 * Created:	June 11, 2007
 * Copyright:	MontaVista Software Inc.
 */

#अगर_अघोषित _MMC_SDIO_CIS_H
#घोषणा _MMC_SDIO_CIS_H

काष्ठा mmc_card;
काष्ठा sdio_func;

पूर्णांक sdio_पढ़ो_common_cis(काष्ठा mmc_card *card);
व्योम sdio_मुक्त_common_cis(काष्ठा mmc_card *card);

पूर्णांक sdio_पढ़ो_func_cis(काष्ठा sdio_func *func);
व्योम sdio_मुक्त_func_cis(काष्ठा sdio_func *func);

#पूर्ण_अगर
