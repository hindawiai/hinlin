<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/core/sd_ops.h
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#अगर_अघोषित _MMC_SD_OPS_H
#घोषणा _MMC_SD_OPS_H

#समावेश <linux/types.h>

काष्ठा mmc_card;
काष्ठा mmc_host;

पूर्णांक mmc_app_set_bus_width(काष्ठा mmc_card *card, पूर्णांक width);
पूर्णांक mmc_send_app_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr);
पूर्णांक mmc_send_अगर_cond(काष्ठा mmc_host *host, u32 ocr);
पूर्णांक mmc_send_अगर_cond_pcie(काष्ठा mmc_host *host, u32 ocr);
पूर्णांक mmc_send_relative_addr(काष्ठा mmc_host *host, अचिन्हित पूर्णांक *rca);
पूर्णांक mmc_app_send_scr(काष्ठा mmc_card *card);
पूर्णांक mmc_sd_चयन(काष्ठा mmc_card *card, पूर्णांक mode, पूर्णांक group,
	u8 value, u8 *resp);
पूर्णांक mmc_app_sd_status(काष्ठा mmc_card *card, व्योम *ssr);
पूर्णांक mmc_app_cmd(काष्ठा mmc_host *host, काष्ठा mmc_card *card);

#पूर्ण_अगर

