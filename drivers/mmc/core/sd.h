<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MMC_CORE_SD_H
#घोषणा _MMC_CORE_SD_H

#समावेश <linux/types.h>

बाह्य काष्ठा device_type sd_type;

काष्ठा mmc_host;
काष्ठा mmc_card;

पूर्णांक mmc_sd_get_cid(काष्ठा mmc_host *host, u32 ocr, u32 *cid, u32 *rocr);
पूर्णांक mmc_sd_get_csd(काष्ठा mmc_card *card);
व्योम mmc_decode_cid(काष्ठा mmc_card *card);
पूर्णांक mmc_sd_setup_card(काष्ठा mmc_host *host, काष्ठा mmc_card *card,
	bool reinit);
अचिन्हित mmc_sd_get_max_घड़ी(काष्ठा mmc_card *card);
पूर्णांक mmc_sd_चयन_hs(काष्ठा mmc_card *card);

#पूर्ण_अगर
