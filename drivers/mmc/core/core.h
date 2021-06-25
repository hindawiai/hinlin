<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mmc/core/core.h
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2007 Pierre Ossman
 */
#अगर_अघोषित _MMC_CORE_CORE_H
#घोषणा _MMC_CORE_CORE_H

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>

काष्ठा mmc_host;
काष्ठा mmc_card;
काष्ठा mmc_request;

#घोषणा MMC_CMD_RETRIES        3

काष्ठा mmc_bus_ops अणु
	व्योम (*हटाओ)(काष्ठा mmc_host *);
	व्योम (*detect)(काष्ठा mmc_host *);
	पूर्णांक (*pre_suspend)(काष्ठा mmc_host *);
	पूर्णांक (*suspend)(काष्ठा mmc_host *);
	पूर्णांक (*resume)(काष्ठा mmc_host *);
	पूर्णांक (*runसमय_suspend)(काष्ठा mmc_host *);
	पूर्णांक (*runसमय_resume)(काष्ठा mmc_host *);
	पूर्णांक (*alive)(काष्ठा mmc_host *);
	पूर्णांक (*shutकरोwn)(काष्ठा mmc_host *);
	पूर्णांक (*hw_reset)(काष्ठा mmc_host *);
	पूर्णांक (*sw_reset)(काष्ठा mmc_host *);
	bool (*cache_enabled)(काष्ठा mmc_host *);
पूर्ण;

व्योम mmc_attach_bus(काष्ठा mmc_host *host, स्थिर काष्ठा mmc_bus_ops *ops);
व्योम mmc_detach_bus(काष्ठा mmc_host *host);

काष्ठा device_node *mmc_of_find_child_device(काष्ठा mmc_host *host,
		अचिन्हित func_num);

व्योम mmc_init_erase(काष्ठा mmc_card *card);

व्योम mmc_set_chip_select(काष्ठा mmc_host *host, पूर्णांक mode);
व्योम mmc_set_घड़ी(काष्ठा mmc_host *host, अचिन्हित पूर्णांक hz);
व्योम mmc_set_bus_mode(काष्ठा mmc_host *host, अचिन्हित पूर्णांक mode);
व्योम mmc_set_bus_width(काष्ठा mmc_host *host, अचिन्हित पूर्णांक width);
u32 mmc_select_voltage(काष्ठा mmc_host *host, u32 ocr);
पूर्णांक mmc_set_uhs_voltage(काष्ठा mmc_host *host, u32 ocr);
पूर्णांक mmc_host_set_uhs_voltage(काष्ठा mmc_host *host);
पूर्णांक mmc_set_संकेत_voltage(काष्ठा mmc_host *host, पूर्णांक संकेत_voltage);
व्योम mmc_set_initial_संकेत_voltage(काष्ठा mmc_host *host);
व्योम mmc_set_timing(काष्ठा mmc_host *host, अचिन्हित पूर्णांक timing);
व्योम mmc_set_driver_type(काष्ठा mmc_host *host, अचिन्हित पूर्णांक drv_type);
पूर्णांक mmc_select_drive_strength(काष्ठा mmc_card *card, अचिन्हित पूर्णांक max_dtr,
			      पूर्णांक card_drv_type, पूर्णांक *drv_type);
व्योम mmc_घातer_up(काष्ठा mmc_host *host, u32 ocr);
व्योम mmc_घातer_off(काष्ठा mmc_host *host);
व्योम mmc_घातer_cycle(काष्ठा mmc_host *host, u32 ocr);
व्योम mmc_set_initial_state(काष्ठा mmc_host *host);
u32 mmc_vddrange_to_ocrmask(पूर्णांक vdd_min, पूर्णांक vdd_max);

अटल अंतरभूत व्योम mmc_delay(अचिन्हित पूर्णांक ms)
अणु
	अगर (ms <= 20)
		usleep_range(ms * 1000, ms * 1250);
	अन्यथा
		msleep(ms);
पूर्ण

व्योम mmc_rescan(काष्ठा work_काष्ठा *work);
व्योम mmc_start_host(काष्ठा mmc_host *host);
व्योम mmc_stop_host(काष्ठा mmc_host *host);

व्योम _mmc_detect_change(काष्ठा mmc_host *host, अचिन्हित दीर्घ delay,
			bool cd_irq);
पूर्णांक _mmc_detect_card_हटाओd(काष्ठा mmc_host *host);
पूर्णांक mmc_detect_card_हटाओd(काष्ठा mmc_host *host);

पूर्णांक mmc_attach_mmc(काष्ठा mmc_host *host);
पूर्णांक mmc_attach_sd(काष्ठा mmc_host *host);
पूर्णांक mmc_attach_sdio(काष्ठा mmc_host *host);

/* Module parameters */
बाह्य bool use_spi_crc;

/* Debugfs inक्रमmation क्रम hosts and cards */
व्योम mmc_add_host_debugfs(काष्ठा mmc_host *host);
व्योम mmc_हटाओ_host_debugfs(काष्ठा mmc_host *host);

व्योम mmc_add_card_debugfs(काष्ठा mmc_card *card);
व्योम mmc_हटाओ_card_debugfs(काष्ठा mmc_card *card);

पूर्णांक mmc_execute_tuning(काष्ठा mmc_card *card);
पूर्णांक mmc_hs200_to_hs400(काष्ठा mmc_card *card);
पूर्णांक mmc_hs400_to_hs200(काष्ठा mmc_card *card);

व्योम mmc_रुको_क्रम_req_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
bool mmc_is_req_करोne(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);

पूर्णांक mmc_start_request(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);

पूर्णांक mmc_erase(काष्ठा mmc_card *card, अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक nr,
		अचिन्हित पूर्णांक arg);
पूर्णांक mmc_can_erase(काष्ठा mmc_card *card);
पूर्णांक mmc_can_trim(काष्ठा mmc_card *card);
पूर्णांक mmc_can_discard(काष्ठा mmc_card *card);
पूर्णांक mmc_can_sanitize(काष्ठा mmc_card *card);
पूर्णांक mmc_can_secure_erase_trim(काष्ठा mmc_card *card);
पूर्णांक mmc_erase_group_aligned(काष्ठा mmc_card *card, अचिन्हित पूर्णांक from,
			अचिन्हित पूर्णांक nr);
अचिन्हित पूर्णांक mmc_calc_max_discard(काष्ठा mmc_card *card);

पूर्णांक mmc_set_blocklen(काष्ठा mmc_card *card, अचिन्हित पूर्णांक blocklen);

पूर्णांक __mmc_claim_host(काष्ठा mmc_host *host, काष्ठा mmc_ctx *ctx,
		     atomic_t *पात);
व्योम mmc_release_host(काष्ठा mmc_host *host);
व्योम mmc_get_card(काष्ठा mmc_card *card, काष्ठा mmc_ctx *ctx);
व्योम mmc_put_card(काष्ठा mmc_card *card, काष्ठा mmc_ctx *ctx);

/**
 *	mmc_claim_host - exclusively claim a host
 *	@host: mmc host to claim
 *
 *	Claim a host क्रम a set of operations.
 */
अटल अंतरभूत व्योम mmc_claim_host(काष्ठा mmc_host *host)
अणु
	__mmc_claim_host(host, शून्य, शून्य);
पूर्ण

पूर्णांक mmc_cqe_start_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
व्योम mmc_cqe_post_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq);
पूर्णांक mmc_cqe_recovery(काष्ठा mmc_host *host);

/**
 *	mmc_pre_req - Prepare क्रम a new request
 *	@host: MMC host to prepare command
 *	@mrq: MMC request to prepare क्रम
 *
 *	mmc_pre_req() is called in prior to mmc_start_req() to let
 *	host prepare क्रम the new request. Preparation of a request may be
 *	perक्रमmed जबतक another request is running on the host.
 */
अटल अंतरभूत व्योम mmc_pre_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	अगर (host->ops->pre_req)
		host->ops->pre_req(host, mrq);
पूर्ण

/**
 *	mmc_post_req - Post process a completed request
 *	@host: MMC host to post process command
 *	@mrq: MMC request to post process क्रम
 *	@err: Error, अगर non zero, clean up any resources made in pre_req
 *
 *	Let the host post process a completed request. Post processing of
 *	a request may be perक्रमmed जबतक another request is running.
 */
अटल अंतरभूत व्योम mmc_post_req(काष्ठा mmc_host *host, काष्ठा mmc_request *mrq,
				पूर्णांक err)
अणु
	अगर (host->ops->post_req)
		host->ops->post_req(host, mrq, err);
पूर्ण

अटल अंतरभूत bool mmc_cache_enabled(काष्ठा mmc_host *host)
अणु
	अगर (host->bus_ops->cache_enabled)
		वापस host->bus_ops->cache_enabled(host);

	वापस false;
पूर्ण

#पूर्ण_अगर
