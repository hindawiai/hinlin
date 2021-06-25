<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */


#अगर_अघोषित __RPM_INTERNAL_H__
#घोषणा __RPM_INTERNAL_H__

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/रुको.h>
#समावेश <soc/qcom/tcs.h>

#घोषणा TCS_TYPE_NR			4
#घोषणा MAX_CMDS_PER_TCS		16
#घोषणा MAX_TCS_PER_TYPE		3
#घोषणा MAX_TCS_NR			(MAX_TCS_PER_TYPE * TCS_TYPE_NR)
#घोषणा MAX_TCS_SLOTS			(MAX_CMDS_PER_TCS * MAX_TCS_PER_TYPE)

काष्ठा rsc_drv;

/**
 * काष्ठा tcs_group: group of Trigger Command Sets (TCS) to send state requests
 * to the controller
 *
 * @drv:       The controller.
 * @type:      Type of the TCS in this group - active, sleep, wake.
 * @mask:      Mask of the TCSes relative to all the TCSes in the RSC.
 * @offset:    Start of the TCS group relative to the TCSes in the RSC.
 * @num_tcs:   Number of TCSes in this type.
 * @ncpt:      Number of commands in each TCS.
 * @req:       Requests that are sent from the TCS; only used क्रम ACTIVE_ONLY
 *             transfers (could be on a wake/sleep TCS अगर we are borrowing क्रम
 *             an ACTIVE_ONLY transfer).
 *             Start: grab drv->lock, set req, set tcs_in_use, drop drv->lock,
 *                    trigger
 *             End: get irq, access req,
 *                  grab drv->lock, clear tcs_in_use, drop drv->lock
 * @slots:     Indicates which of @cmd_addr are occupied; only used क्रम
 *             SLEEP / WAKE TCSs.  Things are tightly packed in the
 *             हाल that (ncpt < MAX_CMDS_PER_TCS).  That is अगर ncpt = 2 and
 *             MAX_CMDS_PER_TCS = 16 then bit[2] = the first bit in 2nd TCS.
 */
काष्ठा tcs_group अणु
	काष्ठा rsc_drv *drv;
	पूर्णांक type;
	u32 mask;
	u32 offset;
	पूर्णांक num_tcs;
	पूर्णांक ncpt;
	स्थिर काष्ठा tcs_request *req[MAX_TCS_PER_TYPE];
	DECLARE_BITMAP(slots, MAX_TCS_SLOTS);
पूर्ण;

/**
 * काष्ठा rpmh_request: the message to be sent to rpmh-rsc
 *
 * @msg: the request
 * @cmd: the payload that will be part of the @msg
 * @completion: triggered when request is करोne
 * @dev: the device making the request
 * @err: err वापस from the controller
 * @needs_मुक्त: check to मुक्त dynamically allocated request object
 */
काष्ठा rpmh_request अणु
	काष्ठा tcs_request msg;
	काष्ठा tcs_cmd cmd[MAX_RPMH_PAYLOAD];
	काष्ठा completion *completion;
	स्थिर काष्ठा device *dev;
	पूर्णांक err;
	bool needs_मुक्त;
पूर्ण;

/**
 * काष्ठा rpmh_ctrlr: our representation of the controller
 *
 * @cache: the list of cached requests
 * @cache_lock: synchronize access to the cache data
 * @dirty: was the cache updated since flush
 * @batch_cache: Cache sleep and wake requests sent as batch
 */
काष्ठा rpmh_ctrlr अणु
	काष्ठा list_head cache;
	spinlock_t cache_lock;
	bool dirty;
	काष्ठा list_head batch_cache;
पूर्ण;

/**
 * काष्ठा rsc_drv: the Direct Resource Voter (DRV) of the
 * Resource State Coordinator controller (RSC)
 *
 * @name:               Controller identअगरier.
 * @tcs_base:           Start address of the TCS रेजिस्टरs in this controller.
 * @id:                 Instance id in the controller (Direct Resource Voter).
 * @num_tcs:            Number of TCSes in this DRV.
 * @rsc_pm:             CPU PM notअगरier क्रम controller.
 *                      Used when solver mode is not present.
 * @cpus_in_pm:         Number of CPUs not in idle घातer collapse.
 *                      Used when solver mode is not present.
 * @tcs:                TCS groups.
 * @tcs_in_use:         S/W state of the TCS; only set क्रम ACTIVE_ONLY
 *                      transfers, but might show a sleep/wake TCS in use अगर
 *                      it was borrowed क्रम an active_only transfer.  You
 *                      must hold the lock in this काष्ठा (AKA drv->lock) in
 *                      order to update this.
 * @lock:               Synchronize state of the controller.  If RPMH's cache
 *                      lock will also be held, the order is: drv->lock then
 *                      cache_lock.
 * @tcs_रुको:           Wait queue used to रुको क्रम @tcs_in_use to मुक्त up a
 *                      slot
 * @client:             Handle to the DRV's client.
 */
काष्ठा rsc_drv अणु
	स्थिर अक्षर *name;
	व्योम __iomem *tcs_base;
	पूर्णांक id;
	पूर्णांक num_tcs;
	काष्ठा notअगरier_block rsc_pm;
	atomic_t cpus_in_pm;
	काष्ठा tcs_group tcs[TCS_TYPE_NR];
	DECLARE_BITMAP(tcs_in_use, MAX_TCS_NR);
	spinlock_t lock;
	रुको_queue_head_t tcs_रुको;
	काष्ठा rpmh_ctrlr client;
पूर्ण;

पूर्णांक rpmh_rsc_send_data(काष्ठा rsc_drv *drv, स्थिर काष्ठा tcs_request *msg);
पूर्णांक rpmh_rsc_ग_लिखो_ctrl_data(काष्ठा rsc_drv *drv,
			     स्थिर काष्ठा tcs_request *msg);
व्योम rpmh_rsc_invalidate(काष्ठा rsc_drv *drv);

व्योम rpmh_tx_करोne(स्थिर काष्ठा tcs_request *msg, पूर्णांक r);
पूर्णांक rpmh_flush(काष्ठा rpmh_ctrlr *ctrlr);

#पूर्ण_अगर /* __RPM_INTERNAL_H__ */
