<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mmc/core/host.h
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2007 Pierre Ossman
 */
#अगर_अघोषित _MMC_CORE_HOST_H
#घोषणा _MMC_CORE_HOST_H

#समावेश <linux/mmc/host.h>

पूर्णांक mmc_रेजिस्टर_host_class(व्योम);
व्योम mmc_unरेजिस्टर_host_class(व्योम);

व्योम mmc_retune_enable(काष्ठा mmc_host *host);
व्योम mmc_retune_disable(काष्ठा mmc_host *host);
व्योम mmc_retune_hold(काष्ठा mmc_host *host);
व्योम mmc_retune_release(काष्ठा mmc_host *host);
पूर्णांक mmc_retune(काष्ठा mmc_host *host);
व्योम mmc_retune_छोड़ो(काष्ठा mmc_host *host);
व्योम mmc_retune_unछोड़ो(काष्ठा mmc_host *host);

अटल अंतरभूत व्योम mmc_retune_hold_now(काष्ठा mmc_host *host)
अणु
	host->retune_now = 0;
	host->hold_retune += 1;
पूर्ण

अटल अंतरभूत व्योम mmc_retune_recheck(काष्ठा mmc_host *host)
अणु
	अगर (host->hold_retune <= 1)
		host->retune_now = 1;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_host_cmd23(काष्ठा mmc_host *host)
अणु
	वापस host->caps & MMC_CAP_CMD23;
पूर्ण

अटल अंतरभूत bool mmc_host_करोne_complete(काष्ठा mmc_host *host)
अणु
	वापस host->caps & MMC_CAP_DONE_COMPLETE;
पूर्ण

अटल अंतरभूत पूर्णांक mmc_boot_partition_access(काष्ठा mmc_host *host)
अणु
	वापस !(host->caps2 & MMC_CAP2_BOOTPART_NOACC);
पूर्ण

अटल अंतरभूत पूर्णांक mmc_host_uhs(काष्ठा mmc_host *host)
अणु
	वापस host->caps &
		(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
		 MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 |
		 MMC_CAP_UHS_DDR50) &&
	       host->caps & MMC_CAP_4_BIT_DATA;
पूर्ण

अटल अंतरभूत bool mmc_card_hs200(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.timing == MMC_TIMING_MMC_HS200;
पूर्ण

अटल अंतरभूत bool mmc_card_ddr52(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.timing == MMC_TIMING_MMC_DDR52;
पूर्ण

अटल अंतरभूत bool mmc_card_hs400(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.timing == MMC_TIMING_MMC_HS400;
पूर्ण

अटल अंतरभूत bool mmc_card_hs400es(काष्ठा mmc_card *card)
अणु
	वापस card->host->ios.enhanced_strobe;
पूर्ण

अटल अंतरभूत bool mmc_card_sd_express(काष्ठा mmc_host *host)
अणु
	वापस host->ios.timing == MMC_TIMING_SD_EXP ||
		host->ios.timing == MMC_TIMING_SD_EXP_1_2V;
पूर्ण

#पूर्ण_अगर

