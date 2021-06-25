<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#समावेश "bfa_cee.h"
#समावेश "bfi_cna.h"
#समावेश "bfa_ioc.h"

अटल व्योम bfa_cee_क्रमmat_lldp_cfg(काष्ठा bfa_cee_lldp_cfg *lldp_cfg);
अटल व्योम bfa_cee_क्रमmat_cee_cfg(व्योम *buffer);

अटल व्योम
bfa_cee_क्रमmat_cee_cfg(व्योम *buffer)
अणु
	काष्ठा bfa_cee_attr *cee_cfg = buffer;
	bfa_cee_क्रमmat_lldp_cfg(&cee_cfg->lldp_remote);
पूर्ण

अटल व्योम
bfa_cee_stats_swap(काष्ठा bfa_cee_stats *stats)
अणु
	u32 *buffer = (u32 *)stats;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(काष्ठा bfa_cee_stats) / माप(u32));
		i++) अणु
		buffer[i] = ntohl(buffer[i]);
	पूर्ण
पूर्ण

अटल व्योम
bfa_cee_क्रमmat_lldp_cfg(काष्ठा bfa_cee_lldp_cfg *lldp_cfg)
अणु
	lldp_cfg->समय_प्रकारo_live =
			ntohs(lldp_cfg->समय_प्रकारo_live);
	lldp_cfg->enabled_प्रणाली_cap =
			ntohs(lldp_cfg->enabled_प्रणाली_cap);
पूर्ण

/**
 * bfa_cee_attr_meminfo - Returns the size of the DMA memory needed by CEE attributes
 */
अटल u32
bfa_cee_attr_meminfo(व्योम)
अणु
	वापस roundup(माप(काष्ठा bfa_cee_attr), BFA_DMA_ALIGN_SZ);
पूर्ण
/**
 * bfa_cee_stats_meminfo - Returns the size of the DMA memory needed by CEE stats
 */
अटल u32
bfa_cee_stats_meminfo(व्योम)
अणु
	वापस roundup(माप(काष्ठा bfa_cee_stats), BFA_DMA_ALIGN_SZ);
पूर्ण

/**
 * bfa_cee_get_attr_isr - CEE ISR क्रम get-attributes responses from f/w
 *
 * @cee: Poपूर्णांकer to the CEE module
 * @status: Return status from the f/w
 */
अटल व्योम
bfa_cee_get_attr_isr(काष्ठा bfa_cee *cee, क्रमागत bfa_status status)
अणु
	cee->get_attr_status = status;
	अगर (status == BFA_STATUS_OK) अणु
		स_नकल(cee->attr, cee->attr_dma.kva,
		    माप(काष्ठा bfa_cee_attr));
		bfa_cee_क्रमmat_cee_cfg(cee->attr);
	पूर्ण
	cee->get_attr_pending = false;
	अगर (cee->cbfn.get_attr_cbfn)
		cee->cbfn.get_attr_cbfn(cee->cbfn.get_attr_cbarg, status);
पूर्ण

/**
 * bfa_cee_get_attr_isr - CEE ISR क्रम get-stats responses from f/w
 *
 * @cee: Poपूर्णांकer to the CEE module
 * @status: Return status from the f/w
 */
अटल व्योम
bfa_cee_get_stats_isr(काष्ठा bfa_cee *cee, क्रमागत bfa_status status)
अणु
	cee->get_stats_status = status;
	अगर (status == BFA_STATUS_OK) अणु
		स_नकल(cee->stats, cee->stats_dma.kva,
			माप(काष्ठा bfa_cee_stats));
		bfa_cee_stats_swap(cee->stats);
	पूर्ण
	cee->get_stats_pending = false;
	अगर (cee->cbfn.get_stats_cbfn)
		cee->cbfn.get_stats_cbfn(cee->cbfn.get_stats_cbarg, status);
पूर्ण

/**
 * bfa_cee_reset_stats_isr - CEE ISR क्रम reset-stats responses from f/w
 *
 * @cee: Input Poपूर्णांकer to the CEE module
 * @status: Return status from the f/w
 */
अटल व्योम
bfa_cee_reset_stats_isr(काष्ठा bfa_cee *cee, क्रमागत bfa_status status)
अणु
	cee->reset_stats_status = status;
	cee->reset_stats_pending = false;
	अगर (cee->cbfn.reset_stats_cbfn)
		cee->cbfn.reset_stats_cbfn(cee->cbfn.reset_stats_cbarg, status);
पूर्ण
/**
 * bfa_nw_cee_meminfo - Returns the size of the DMA memory needed by CEE module
 */
u32
bfa_nw_cee_meminfo(व्योम)
अणु
	वापस bfa_cee_attr_meminfo() + bfa_cee_stats_meminfo();
पूर्ण

/**
 * bfa_nw_cee_mem_claim - Initialized CEE DMA Memory
 *
 * @cee: CEE module poपूर्णांकer
 * @dma_kva: Kernel Virtual Address of CEE DMA Memory
 * @dma_pa:  Physical Address of CEE DMA Memory
 */
व्योम
bfa_nw_cee_mem_claim(काष्ठा bfa_cee *cee, u8 *dma_kva, u64 dma_pa)
अणु
	cee->attr_dma.kva = dma_kva;
	cee->attr_dma.pa = dma_pa;
	cee->stats_dma.kva = dma_kva + bfa_cee_attr_meminfo();
	cee->stats_dma.pa = dma_pa + bfa_cee_attr_meminfo();
	cee->attr = (काष्ठा bfa_cee_attr *) dma_kva;
	cee->stats = (काष्ठा bfa_cee_stats *)
		(dma_kva + bfa_cee_attr_meminfo());
पूर्ण

/**
 * bfa_nw_cee_get_attr - Send the request to the f/w to fetch CEE attributes.
 *
 * @cee: Poपूर्णांकer to the CEE module data काष्ठाure.
 * @attr: attribute requested
 * @cbfn: function poपूर्णांकer
 * @cbarg: function poपूर्णांकer arguments
 *
 * Return: status
 */
क्रमागत bfa_status
bfa_nw_cee_get_attr(काष्ठा bfa_cee *cee, काष्ठा bfa_cee_attr *attr,
		    bfa_cee_get_attr_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_cee_get_req *cmd;

	BUG_ON(!((cee != शून्य) && (cee->ioc != शून्य)));
	अगर (!bfa_nw_ioc_is_operational(cee->ioc))
		वापस BFA_STATUS_IOC_FAILURE;

	अगर (cee->get_attr_pending)
		वापस  BFA_STATUS_DEVBUSY;

	cee->get_attr_pending = true;
	cmd = (काष्ठा bfi_cee_get_req *) cee->get_cfg_mb.msg;
	cee->attr = attr;
	cee->cbfn.get_attr_cbfn = cbfn;
	cee->cbfn.get_attr_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_REQ,
		    bfa_ioc_portid(cee->ioc));
	bfa_dma_be_addr_set(cmd->dma_addr, cee->attr_dma.pa);
	bfa_nw_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb, शून्य, शून्य);

	वापस BFA_STATUS_OK;
पूर्ण

/**
 * bfa_cee_isr - Handles Mail-box पूर्णांकerrupts क्रम CEE module.
 * @cbarg: argument passed containing poपूर्णांकer to the CEE module data काष्ठाure.
 * @m: message poपूर्णांकer
 */

अटल व्योम
bfa_cee_isr(व्योम *cbarg, काष्ठा bfi_mbmsg *m)
अणु
	जोड़ bfi_cee_i2h_msg_u *msg;
	काष्ठा bfi_cee_get_rsp *get_rsp;
	काष्ठा bfa_cee *cee = (काष्ठा bfa_cee *) cbarg;
	msg = (जोड़ bfi_cee_i2h_msg_u *) m;
	get_rsp = (काष्ठा bfi_cee_get_rsp *) m;
	चयन (msg->mh.msg_id) अणु
	हाल BFI_CEE_I2H_GET_CFG_RSP:
		bfa_cee_get_attr_isr(cee, get_rsp->cmd_status);
		अवरोध;
	हाल BFI_CEE_I2H_GET_STATS_RSP:
		bfa_cee_get_stats_isr(cee, get_rsp->cmd_status);
		अवरोध;
	हाल BFI_CEE_I2H_RESET_STATS_RSP:
		bfa_cee_reset_stats_isr(cee, get_rsp->cmd_status);
		अवरोध;
	शेष:
		BUG_ON(1);
	पूर्ण
पूर्ण

/**
 * bfa_cee_notअगरy - CEE module heart-beat failure handler.
 *
 * @arg: argument passed containing poपूर्णांकer to the CEE module data काष्ठाure.
 * @event: IOC event type
 */

अटल व्योम
bfa_cee_notअगरy(व्योम *arg, क्रमागत bfa_ioc_event event)
अणु
	काष्ठा bfa_cee *cee;
	cee = (काष्ठा bfa_cee *) arg;

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (cee->get_attr_pending) अणु
			cee->get_attr_status = BFA_STATUS_FAILED;
			cee->get_attr_pending  = false;
			अगर (cee->cbfn.get_attr_cbfn) अणु
				cee->cbfn.get_attr_cbfn(
					cee->cbfn.get_attr_cbarg,
					BFA_STATUS_FAILED);
			पूर्ण
		पूर्ण
		अगर (cee->get_stats_pending) अणु
			cee->get_stats_status = BFA_STATUS_FAILED;
			cee->get_stats_pending  = false;
			अगर (cee->cbfn.get_stats_cbfn) अणु
				cee->cbfn.get_stats_cbfn(
					cee->cbfn.get_stats_cbarg,
					BFA_STATUS_FAILED);
			पूर्ण
		पूर्ण
		अगर (cee->reset_stats_pending) अणु
			cee->reset_stats_status = BFA_STATUS_FAILED;
			cee->reset_stats_pending  = false;
			अगर (cee->cbfn.reset_stats_cbfn) अणु
				cee->cbfn.reset_stats_cbfn(
					cee->cbfn.reset_stats_cbarg,
					BFA_STATUS_FAILED);
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * bfa_nw_cee_attach - CEE module-attach API
 *
 * @cee: Poपूर्णांकer to the CEE module data काष्ठाure
 * @ioc: Poपूर्णांकer to the ioc module data काष्ठाure
 * @dev: Poपूर्णांकer to the device driver module data काष्ठाure.
 *       The device driver specअगरic mbox ISR functions have
 *       this poपूर्णांकer as one of the parameters.
 */
व्योम
bfa_nw_cee_attach(काष्ठा bfa_cee *cee, काष्ठा bfa_ioc *ioc,
		व्योम *dev)
अणु
	BUG_ON(!(cee != शून्य));
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_nw_ioc_mbox_regisr(cee->ioc, BFI_MC_CEE, bfa_cee_isr, cee);
	bfa_ioc_notअगरy_init(&cee->ioc_notअगरy, bfa_cee_notअगरy, cee);
	bfa_nw_ioc_notअगरy_रेजिस्टर(cee->ioc, &cee->ioc_notअगरy);
पूर्ण
