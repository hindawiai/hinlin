<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/mmc/core/mmc_ops.h
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#अगर_अघोषित _MMC_MMC_OPS_H
#घोषणा _MMC_MMC_OPS_H

#समावेश <linux/types.h>

क्रमागत mmc_busy_cmd अणु
	MMC_BUSY_CMD6,
	MMC_BUSY_ERASE,
	MMC_BUSY_HPI,
पूर्ण;

काष्ठा mmc_host;
काष्ठा mmc_card;

पूर्णांक mmc_select_card(काष्ठा mmc_card *card);
पूर्णांक mmc_deselect_cards(काष्ठा mmc_host *host);
पूर्णांक mmc_set_dsr(काष्ठा mmc_host *host);
पूर्णांक mmc_go_idle(काष्ठा mmc_host *host);
पूर्णांक mmc_send_op_cond(काष्ठा mmc_host *host, u32 ocr, u32 *rocr);
पूर्णांक mmc_set_relative_addr(काष्ठा mmc_card *card);
पूर्णांक mmc_send_csd(काष्ठा mmc_card *card, u32 *csd);
पूर्णांक __mmc_send_status(काष्ठा mmc_card *card, u32 *status, अचिन्हित पूर्णांक retries);
पूर्णांक mmc_send_status(काष्ठा mmc_card *card, u32 *status);
पूर्णांक mmc_send_cid(काष्ठा mmc_host *host, u32 *cid);
पूर्णांक mmc_spi_पढ़ो_ocr(काष्ठा mmc_host *host, पूर्णांक highcap, u32 *ocrp);
पूर्णांक mmc_spi_set_crc(काष्ठा mmc_host *host, पूर्णांक use_crc);
पूर्णांक mmc_bus_test(काष्ठा mmc_card *card, u8 bus_width);
पूर्णांक mmc_can_ext_csd(काष्ठा mmc_card *card);
पूर्णांक mmc_get_ext_csd(काष्ठा mmc_card *card, u8 **new_ext_csd);
पूर्णांक mmc_चयन_status(काष्ठा mmc_card *card, bool crc_err_fatal);
पूर्णांक mmc_poll_क्रम_busy(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms,
		      क्रमागत mmc_busy_cmd busy_cmd);
पूर्णांक __mmc_चयन(काष्ठा mmc_card *card, u8 set, u8 index, u8 value,
		अचिन्हित पूर्णांक समयout_ms, अचिन्हित अक्षर timing,
		bool send_status, bool retry_crc_err, अचिन्हित पूर्णांक retries);
पूर्णांक mmc_चयन(काष्ठा mmc_card *card, u8 set, u8 index, u8 value,
		अचिन्हित पूर्णांक समयout_ms);
व्योम mmc_run_bkops(काष्ठा mmc_card *card);
पूर्णांक mmc_flush_cache(काष्ठा mmc_card *card);
पूर्णांक mmc_cmdq_enable(काष्ठा mmc_card *card);
पूर्णांक mmc_cmdq_disable(काष्ठा mmc_card *card);
पूर्णांक mmc_sanitize(काष्ठा mmc_card *card, अचिन्हित पूर्णांक समयout_ms);

#पूर्ण_अगर

