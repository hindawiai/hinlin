<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/core/sdio_bus.h
 *
 *  Copyright 2007 Pierre Ossman
 */
#अगर_अघोषित _MMC_CORE_SDIO_BUS_H
#घोषणा _MMC_CORE_SDIO_BUS_H

काष्ठा mmc_card;
काष्ठा sdio_func;

काष्ठा sdio_func *sdio_alloc_func(काष्ठा mmc_card *card);
पूर्णांक sdio_add_func(काष्ठा sdio_func *func);
व्योम sdio_हटाओ_func(काष्ठा sdio_func *func);

पूर्णांक sdio_रेजिस्टर_bus(व्योम);
व्योम sdio_unरेजिस्टर_bus(व्योम);

#पूर्ण_अगर

