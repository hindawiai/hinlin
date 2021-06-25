<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#समावेश "bfad_drv.h"
#समावेश "bfa_defs_svc.h"
#समावेश "bfa_port.h"
#समावेश "bfi.h"
#समावेश "bfa_ioc.h"


BFA_TRC_खाता(CNA, PORT);

अटल व्योम
bfa_port_stats_swap(काष्ठा bfa_port_s *port, जोड़ bfa_port_stats_u *stats)
अणु
	u32    *dip = (u32 *) stats;
	__be32    t0, t1;
	पूर्णांक	    i;

	क्रम (i = 0; i < माप(जोड़ bfa_port_stats_u)/माप(u32);
		i += 2) अणु
		t0 = dip[i];
		t1 = dip[i + 1];
#अगर_घोषित __BIG_ENDIAN
		dip[i] = be32_to_cpu(t0);
		dip[i + 1] = be32_to_cpu(t1);
#अन्यथा
		dip[i] = be32_to_cpu(t1);
		dip[i + 1] = be32_to_cpu(t0);
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * bfa_port_enable_isr()
 *
 *
 * @param[in] port - Poपूर्णांकer to the port module
 *            status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_port_enable_isr(काष्ठा bfa_port_s *port, bfa_status_t status)
अणु
	bfa_trc(port, status);
	port->endis_pending = BFA_FALSE;
	port->endis_cbfn(port->endis_cbarg, status);
पूर्ण

/*
 * bfa_port_disable_isr()
 *
 *
 * @param[in] port - Poपूर्णांकer to the port module
 *            status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_port_disable_isr(काष्ठा bfa_port_s *port, bfa_status_t status)
अणु
	bfa_trc(port, status);
	port->endis_pending = BFA_FALSE;
	port->endis_cbfn(port->endis_cbarg, status);
पूर्ण

/*
 * bfa_port_get_stats_isr()
 *
 *
 * @param[in] port - Poपूर्णांकer to the Port module
 *            status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_port_get_stats_isr(काष्ठा bfa_port_s *port, bfa_status_t status)
अणु
	port->stats_status = status;
	port->stats_busy = BFA_FALSE;

	अगर (status == BFA_STATUS_OK) अणु
		स_नकल(port->stats, port->stats_dma.kva,
		       माप(जोड़ bfa_port_stats_u));
		bfa_port_stats_swap(port, port->stats);

		port->stats->fc.secs_reset = kसमय_get_seconds() - port->stats_reset_समय;
	पूर्ण

	अगर (port->stats_cbfn) अणु
		port->stats_cbfn(port->stats_cbarg, status);
		port->stats_cbfn = शून्य;
	पूर्ण
पूर्ण

/*
 * bfa_port_clear_stats_isr()
 *
 *
 * @param[in] port - Poपूर्णांकer to the Port module
 *            status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_port_clear_stats_isr(काष्ठा bfa_port_s *port, bfa_status_t status)
अणु
	port->stats_status = status;
	port->stats_busy   = BFA_FALSE;

	/*
	* re-initialize समय stamp क्रम stats reset
	*/
	port->stats_reset_समय = kसमय_get_seconds();

	अगर (port->stats_cbfn) अणु
		port->stats_cbfn(port->stats_cbarg, status);
		port->stats_cbfn = शून्य;
	पूर्ण
पूर्ण

/*
 * bfa_port_isr()
 *
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_port_isr(व्योम *cbarg, काष्ठा bfi_mbmsg_s *m)
अणु
	काष्ठा bfa_port_s *port = (काष्ठा bfa_port_s *) cbarg;
	जोड़ bfi_port_i2h_msg_u *i2hmsg;

	i2hmsg = (जोड़ bfi_port_i2h_msg_u *) m;
	bfa_trc(port, m->mh.msg_id);

	चयन (m->mh.msg_id) अणु
	हाल BFI_PORT_I2H_ENABLE_RSP:
		अगर (port->endis_pending == BFA_FALSE)
			अवरोध;
		bfa_port_enable_isr(port, i2hmsg->enable_rsp.status);
		अवरोध;

	हाल BFI_PORT_I2H_DISABLE_RSP:
		अगर (port->endis_pending == BFA_FALSE)
			अवरोध;
		bfa_port_disable_isr(port, i2hmsg->disable_rsp.status);
		अवरोध;

	हाल BFI_PORT_I2H_GET_STATS_RSP:
		/* Stats busy flag is still set? (may be cmd समयd out) */
		अगर (port->stats_busy == BFA_FALSE)
			अवरोध;
		bfa_port_get_stats_isr(port, i2hmsg->माला_लोtats_rsp.status);
		अवरोध;

	हाल BFI_PORT_I2H_CLEAR_STATS_RSP:
		अगर (port->stats_busy == BFA_FALSE)
			अवरोध;
		bfa_port_clear_stats_isr(port, i2hmsg->clearstats_rsp.status);
		अवरोध;

	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * bfa_port_meminfo()
 *
 *
 * @param[in] व्योम
 *
 * @वापस Size of DMA region
 */
u32
bfa_port_meminfo(व्योम)
अणु
	वापस BFA_ROUNDUP(माप(जोड़ bfa_port_stats_u), BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * bfa_port_mem_claim()
 *
 *
 * @param[in] port Port module poपूर्णांकer
 *	      dma_kva Kernel Virtual Address of Port DMA Memory
 *	      dma_pa  Physical Address of Port DMA Memory
 *
 * @वापस व्योम
 */
व्योम
bfa_port_mem_claim(काष्ठा bfa_port_s *port, u8 *dma_kva, u64 dma_pa)
अणु
	port->stats_dma.kva = dma_kva;
	port->stats_dma.pa  = dma_pa;
पूर्ण

/*
 * bfa_port_enable()
 *
 *   Send the Port enable request to the f/w
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 *
 * @वापस Status
 */
bfa_status_t
bfa_port_enable(काष्ठा bfa_port_s *port, bfa_port_endis_cbfn_t cbfn,
		 व्योम *cbarg)
अणु
	काष्ठा bfi_port_generic_req_s *m;

	/* If port is PBC disabled, वापस error */
	अगर (port->pbc_disabled) अणु
		bfa_trc(port, BFA_STATUS_PBC);
		वापस BFA_STATUS_PBC;
	पूर्ण

	अगर (bfa_ioc_is_disabled(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_DISABLED);
		वापस BFA_STATUS_IOC_DISABLED;
	पूर्ण

	अगर (!bfa_ioc_is_operational(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	/* अगर port is d-port enabled, वापस error */
	अगर (port->dport_enabled) अणु
		bfa_trc(port, BFA_STATUS_DPORT_ERR);
		वापस BFA_STATUS_DPORT_ERR;
	पूर्ण

	अगर (port->endis_pending) अणु
		bfa_trc(port, BFA_STATUS_DEVBUSY);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	m = (काष्ठा bfi_port_generic_req_s *) port->endis_mb.msg;

	port->msgtag++;
	port->endis_cbfn    = cbfn;
	port->endis_cbarg   = cbarg;
	port->endis_pending = BFA_TRUE;

	bfi_h2i_set(m->mh, BFI_MC_PORT, BFI_PORT_H2I_ENABLE_REQ,
		    bfa_ioc_portid(port->ioc));
	bfa_ioc_mbox_queue(port->ioc, &port->endis_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_port_disable()
 *
 *   Send the Port disable request to the f/w
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 *
 * @वापस Status
 */
bfa_status_t
bfa_port_disable(काष्ठा bfa_port_s *port, bfa_port_endis_cbfn_t cbfn,
		  व्योम *cbarg)
अणु
	काष्ठा bfi_port_generic_req_s *m;

	/* If port is PBC disabled, वापस error */
	अगर (port->pbc_disabled) अणु
		bfa_trc(port, BFA_STATUS_PBC);
		वापस BFA_STATUS_PBC;
	पूर्ण

	अगर (bfa_ioc_is_disabled(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_DISABLED);
		वापस BFA_STATUS_IOC_DISABLED;
	पूर्ण

	अगर (!bfa_ioc_is_operational(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	/* अगर port is d-port enabled, वापस error */
	अगर (port->dport_enabled) अणु
		bfa_trc(port, BFA_STATUS_DPORT_ERR);
		वापस BFA_STATUS_DPORT_ERR;
	पूर्ण

	अगर (port->endis_pending) अणु
		bfa_trc(port, BFA_STATUS_DEVBUSY);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	m = (काष्ठा bfi_port_generic_req_s *) port->endis_mb.msg;

	port->msgtag++;
	port->endis_cbfn    = cbfn;
	port->endis_cbarg   = cbarg;
	port->endis_pending = BFA_TRUE;

	bfi_h2i_set(m->mh, BFI_MC_PORT, BFI_PORT_H2I_DISABLE_REQ,
		    bfa_ioc_portid(port->ioc));
	bfa_ioc_mbox_queue(port->ioc, &port->endis_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_port_get_stats()
 *
 *   Send the request to the f/w to fetch Port statistics.
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 *
 * @वापस Status
 */
bfa_status_t
bfa_port_get_stats(काष्ठा bfa_port_s *port, जोड़ bfa_port_stats_u *stats,
		    bfa_port_stats_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_port_get_stats_req_s *m;

	अगर (!bfa_ioc_is_operational(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (port->stats_busy) अणु
		bfa_trc(port, BFA_STATUS_DEVBUSY);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	m = (काष्ठा bfi_port_get_stats_req_s *) port->stats_mb.msg;

	port->stats	  = stats;
	port->stats_cbfn  = cbfn;
	port->stats_cbarg = cbarg;
	port->stats_busy  = BFA_TRUE;
	bfa_dma_be_addr_set(m->dma_addr, port->stats_dma.pa);

	bfi_h2i_set(m->mh, BFI_MC_PORT, BFI_PORT_H2I_GET_STATS_REQ,
		    bfa_ioc_portid(port->ioc));
	bfa_ioc_mbox_queue(port->ioc, &port->stats_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_port_clear_stats()
 *
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 *
 * @वापस Status
 */
bfa_status_t
bfa_port_clear_stats(काष्ठा bfa_port_s *port, bfa_port_stats_cbfn_t cbfn,
		      व्योम *cbarg)
अणु
	काष्ठा bfi_port_generic_req_s *m;

	अगर (!bfa_ioc_is_operational(port->ioc)) अणु
		bfa_trc(port, BFA_STATUS_IOC_FAILURE);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण

	अगर (port->stats_busy) अणु
		bfa_trc(port, BFA_STATUS_DEVBUSY);
		वापस BFA_STATUS_DEVBUSY;
	पूर्ण

	m = (काष्ठा bfi_port_generic_req_s *) port->stats_mb.msg;

	port->stats_cbfn  = cbfn;
	port->stats_cbarg = cbarg;
	port->stats_busy  = BFA_TRUE;

	bfi_h2i_set(m->mh, BFI_MC_PORT, BFI_PORT_H2I_CLEAR_STATS_REQ,
		    bfa_ioc_portid(port->ioc));
	bfa_ioc_mbox_queue(port->ioc, &port->stats_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_port_notअगरy()
 *
 * Port module IOC event handler
 *
 * @param[in] Poपूर्णांकer to the Port module data काष्ठाure.
 * @param[in] IOC event काष्ठाure
 *
 * @वापस व्योम
 */
व्योम
bfa_port_notअगरy(व्योम *arg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_port_s *port = (काष्ठा bfa_port_s *) arg;

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		/* Fail any pending get_stats/clear_stats requests */
		अगर (port->stats_busy) अणु
			अगर (port->stats_cbfn)
				port->stats_cbfn(port->stats_cbarg,
						BFA_STATUS_FAILED);
			port->stats_cbfn = शून्य;
			port->stats_busy = BFA_FALSE;
		पूर्ण

		/* Clear any enable/disable is pending */
		अगर (port->endis_pending) अणु
			अगर (port->endis_cbfn)
				port->endis_cbfn(port->endis_cbarg,
						BFA_STATUS_FAILED);
			port->endis_cbfn = शून्य;
			port->endis_pending = BFA_FALSE;
		पूर्ण

		/* clear D-port mode */
		अगर (port->dport_enabled)
			bfa_port_set_dportenabled(port, BFA_FALSE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * bfa_port_attach()
 *
 *
 * @param[in] port - Poपूर्णांकer to the Port module data काष्ठाure
 *            ioc  - Poपूर्णांकer to the ioc module data काष्ठाure
 *            dev  - Poपूर्णांकer to the device driver module data काष्ठाure
 *                   The device driver specअगरic mbox ISR functions have
 *                   this poपूर्णांकer as one of the parameters.
 *            trcmod -
 *
 * @वापस व्योम
 */
व्योम
bfa_port_attach(काष्ठा bfa_port_s *port, काष्ठा bfa_ioc_s *ioc,
		 व्योम *dev, काष्ठा bfa_trc_mod_s *trcmod)
अणु
	WARN_ON(!port);

	port->dev    = dev;
	port->ioc    = ioc;
	port->trcmod = trcmod;

	port->stats_busy = BFA_FALSE;
	port->endis_pending = BFA_FALSE;
	port->stats_cbfn = शून्य;
	port->endis_cbfn = शून्य;
	port->pbc_disabled = BFA_FALSE;
	port->dport_enabled = BFA_FALSE;

	bfa_ioc_mbox_regisr(port->ioc, BFI_MC_PORT, bfa_port_isr, port);
	bfa_q_qe_init(&port->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&port->ioc_notअगरy, bfa_port_notअगरy, port);
	list_add_tail(&port->ioc_notअगरy.qe, &port->ioc->notअगरy_q);

	/*
	 * initialize समय stamp क्रम stats reset
	 */
	port->stats_reset_समय = kसमय_get_seconds();

	bfa_trc(port, 0);
पूर्ण

/*
 * bfa_port_set_dportenabled();
 *
 * Port module- set pbc disabled flag
 *
 * @param[in] port - Poपूर्णांकer to the Port module data काष्ठाure
 *
 * @वापस व्योम
 */
व्योम
bfa_port_set_dportenabled(काष्ठा bfa_port_s *port, bfa_boolean_t enabled)
अणु
	port->dport_enabled = enabled;
पूर्ण

/*
 *	CEE module specअगरic definitions
 */

/*
 * bfa_cee_get_attr_isr()
 *
 * @brief CEE ISR क्रम get-attributes responses from f/w
 *
 * @param[in] cee - Poपूर्णांकer to the CEE module
 *		    status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_cee_get_attr_isr(काष्ठा bfa_cee_s *cee, bfa_status_t status)
अणु
	काष्ठा bfa_cee_lldp_cfg_s *lldp_cfg = &cee->attr->lldp_remote;

	cee->get_attr_status = status;
	bfa_trc(cee, 0);
	अगर (status == BFA_STATUS_OK) अणु
		bfa_trc(cee, 0);
		स_नकल(cee->attr, cee->attr_dma.kva,
			माप(काष्ठा bfa_cee_attr_s));
		lldp_cfg->समय_प्रकारo_live = be16_to_cpu(lldp_cfg->समय_प्रकारo_live);
		lldp_cfg->enabled_प्रणाली_cap =
				be16_to_cpu(lldp_cfg->enabled_प्रणाली_cap);
	पूर्ण
	cee->get_attr_pending = BFA_FALSE;
	अगर (cee->cbfn.get_attr_cbfn) अणु
		bfa_trc(cee, 0);
		cee->cbfn.get_attr_cbfn(cee->cbfn.get_attr_cbarg, status);
	पूर्ण
पूर्ण

/*
 * bfa_cee_get_stats_isr()
 *
 * @brief CEE ISR क्रम get-stats responses from f/w
 *
 * @param[in] cee - Poपूर्णांकer to the CEE module
 *	      status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_cee_get_stats_isr(काष्ठा bfa_cee_s *cee, bfa_status_t status)
अणु
	u32 *buffer;
	पूर्णांक i;

	cee->get_stats_status = status;
	bfa_trc(cee, 0);
	अगर (status == BFA_STATUS_OK) अणु
		bfa_trc(cee, 0);
		स_नकल(cee->stats, cee->stats_dma.kva,
			माप(काष्ठा bfa_cee_stats_s));
		/* swap the cee stats */
		buffer = (u32 *)cee->stats;
		क्रम (i = 0; i < (माप(काष्ठा bfa_cee_stats_s) /
				 माप(u32)); i++)
			buffer[i] = cpu_to_be32(buffer[i]);
	पूर्ण
	cee->get_stats_pending = BFA_FALSE;
	bfa_trc(cee, 0);
	अगर (cee->cbfn.get_stats_cbfn) अणु
		bfa_trc(cee, 0);
		cee->cbfn.get_stats_cbfn(cee->cbfn.get_stats_cbarg, status);
	पूर्ण
पूर्ण

/*
 * bfa_cee_reset_stats_isr()
 *
 * @brief CEE ISR क्रम reset-stats responses from f/w
 *
 * @param[in] cee - Poपूर्णांकer to the CEE module
 *            status - Return status from the f/w
 *
 * @वापस व्योम
 */
अटल व्योम
bfa_cee_reset_stats_isr(काष्ठा bfa_cee_s *cee, bfa_status_t status)
अणु
	cee->reset_stats_status = status;
	cee->reset_stats_pending = BFA_FALSE;
	अगर (cee->cbfn.reset_stats_cbfn)
		cee->cbfn.reset_stats_cbfn(cee->cbfn.reset_stats_cbarg, status);
पूर्ण

/*
 * bfa_cee_meminfo()
 *
 * @brief Returns the size of the DMA memory needed by CEE module
 *
 * @param[in] व्योम
 *
 * @वापस Size of DMA region
 */
u32
bfa_cee_meminfo(व्योम)
अणु
	वापस BFA_ROUNDUP(माप(काष्ठा bfa_cee_attr_s), BFA_DMA_ALIGN_SZ) +
		BFA_ROUNDUP(माप(काष्ठा bfa_cee_stats_s), BFA_DMA_ALIGN_SZ);
पूर्ण

/*
 * bfa_cee_mem_claim()
 *
 * @brief Initialized CEE DMA Memory
 *
 * @param[in] cee CEE module poपूर्णांकer
 *            dma_kva Kernel Virtual Address of CEE DMA Memory
 *            dma_pa  Physical Address of CEE DMA Memory
 *
 * @वापस व्योम
 */
व्योम
bfa_cee_mem_claim(काष्ठा bfa_cee_s *cee, u8 *dma_kva, u64 dma_pa)
अणु
	cee->attr_dma.kva = dma_kva;
	cee->attr_dma.pa = dma_pa;
	cee->stats_dma.kva = dma_kva + BFA_ROUNDUP(
			     माप(काष्ठा bfa_cee_attr_s), BFA_DMA_ALIGN_SZ);
	cee->stats_dma.pa = dma_pa + BFA_ROUNDUP(
			     माप(काष्ठा bfa_cee_attr_s), BFA_DMA_ALIGN_SZ);
	cee->attr = (काष्ठा bfa_cee_attr_s *) dma_kva;
	cee->stats = (काष्ठा bfa_cee_stats_s *) (dma_kva + BFA_ROUNDUP(
			माप(काष्ठा bfa_cee_attr_s), BFA_DMA_ALIGN_SZ));
पूर्ण

/*
 * bfa_cee_get_attr()
 *
 * @brief
 *   Send the request to the f/w to fetch CEE attributes.
 *
 * @param[in] Poपूर्णांकer to the CEE module data काष्ठाure.
 *
 * @वापस Status
 */

bfa_status_t
bfa_cee_get_attr(काष्ठा bfa_cee_s *cee, काष्ठा bfa_cee_attr_s *attr,
		 bfa_cee_get_attr_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_cee_get_req_s *cmd;

	WARN_ON((cee == शून्य) || (cee->ioc == शून्य));
	bfa_trc(cee, 0);
	अगर (!bfa_ioc_is_operational(cee->ioc)) अणु
		bfa_trc(cee, 0);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण
	अगर (cee->get_attr_pending == BFA_TRUE) अणु
		bfa_trc(cee, 0);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण
	cee->get_attr_pending = BFA_TRUE;
	cmd = (काष्ठा bfi_cee_get_req_s *) cee->get_cfg_mb.msg;
	cee->attr = attr;
	cee->cbfn.get_attr_cbfn = cbfn;
	cee->cbfn.get_attr_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_REQ,
		bfa_ioc_portid(cee->ioc));
	bfa_dma_be_addr_set(cmd->dma_addr, cee->attr_dma.pa);
	bfa_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_cee_get_stats()
 *
 * @brief
 *   Send the request to the f/w to fetch CEE statistics.
 *
 * @param[in] Poपूर्णांकer to the CEE module data काष्ठाure.
 *
 * @वापस Status
 */

bfa_status_t
bfa_cee_get_stats(काष्ठा bfa_cee_s *cee, काष्ठा bfa_cee_stats_s *stats,
		  bfa_cee_get_stats_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_cee_get_req_s *cmd;

	WARN_ON((cee == शून्य) || (cee->ioc == शून्य));

	अगर (!bfa_ioc_is_operational(cee->ioc)) अणु
		bfa_trc(cee, 0);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण
	अगर (cee->get_stats_pending == BFA_TRUE) अणु
		bfa_trc(cee, 0);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण
	cee->get_stats_pending = BFA_TRUE;
	cmd = (काष्ठा bfi_cee_get_req_s *) cee->get_stats_mb.msg;
	cee->stats = stats;
	cee->cbfn.get_stats_cbfn = cbfn;
	cee->cbfn.get_stats_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_STATS_REQ,
		bfa_ioc_portid(cee->ioc));
	bfa_dma_be_addr_set(cmd->dma_addr, cee->stats_dma.pa);
	bfa_ioc_mbox_queue(cee->ioc, &cee->get_stats_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_cee_reset_stats()
 *
 * @brief Clears CEE Stats in the f/w.
 *
 * @param[in] Poपूर्णांकer to the CEE module data काष्ठाure.
 *
 * @वापस Status
 */

bfa_status_t
bfa_cee_reset_stats(काष्ठा bfa_cee_s *cee,
		    bfa_cee_reset_stats_cbfn_t cbfn, व्योम *cbarg)
अणु
	काष्ठा bfi_cee_reset_stats_s *cmd;

	WARN_ON((cee == शून्य) || (cee->ioc == शून्य));
	अगर (!bfa_ioc_is_operational(cee->ioc)) अणु
		bfa_trc(cee, 0);
		वापस BFA_STATUS_IOC_FAILURE;
	पूर्ण
	अगर (cee->reset_stats_pending == BFA_TRUE) अणु
		bfa_trc(cee, 0);
		वापस  BFA_STATUS_DEVBUSY;
	पूर्ण
	cee->reset_stats_pending = BFA_TRUE;
	cmd = (काष्ठा bfi_cee_reset_stats_s *) cee->reset_stats_mb.msg;
	cee->cbfn.reset_stats_cbfn = cbfn;
	cee->cbfn.reset_stats_cbarg = cbarg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_RESET_STATS,
		bfa_ioc_portid(cee->ioc));
	bfa_ioc_mbox_queue(cee->ioc, &cee->reset_stats_mb);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * bfa_cee_isrs()
 *
 * @brief Handles Mail-box पूर्णांकerrupts क्रम CEE module.
 *
 * @param[in] Poपूर्णांकer to the CEE module data काष्ठाure.
 *
 * @वापस व्योम
 */

अटल व्योम
bfa_cee_isr(व्योम *cbarg, काष्ठा bfi_mbmsg_s *m)
अणु
	जोड़ bfi_cee_i2h_msg_u *msg;
	काष्ठा bfi_cee_get_rsp_s *get_rsp;
	काष्ठा bfa_cee_s *cee = (काष्ठा bfa_cee_s *) cbarg;
	msg = (जोड़ bfi_cee_i2h_msg_u *) m;
	get_rsp = (काष्ठा bfi_cee_get_rsp_s *) m;
	bfa_trc(cee, msg->mh.msg_id);
	चयन (msg->mh.msg_id) अणु
	हाल BFI_CEE_I2H_GET_CFG_RSP:
		bfa_trc(cee, get_rsp->cmd_status);
		bfa_cee_get_attr_isr(cee, get_rsp->cmd_status);
		अवरोध;
	हाल BFI_CEE_I2H_GET_STATS_RSP:
		bfa_cee_get_stats_isr(cee, get_rsp->cmd_status);
		अवरोध;
	हाल BFI_CEE_I2H_RESET_STATS_RSP:
		bfa_cee_reset_stats_isr(cee, get_rsp->cmd_status);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * bfa_cee_notअगरy()
 *
 * @brief CEE module IOC event handler.
 *
 * @param[in] Poपूर्णांकer to the CEE module data काष्ठाure.
 * @param[in] IOC event type
 *
 * @वापस व्योम
 */

अटल व्योम
bfa_cee_notअगरy(व्योम *arg, क्रमागत bfa_ioc_event_e event)
अणु
	काष्ठा bfa_cee_s *cee = (काष्ठा bfa_cee_s *) arg;

	bfa_trc(cee, event);

	चयन (event) अणु
	हाल BFA_IOC_E_DISABLED:
	हाल BFA_IOC_E_FAILED:
		अगर (cee->get_attr_pending == BFA_TRUE) अणु
			cee->get_attr_status = BFA_STATUS_FAILED;
			cee->get_attr_pending  = BFA_FALSE;
			अगर (cee->cbfn.get_attr_cbfn) अणु
				cee->cbfn.get_attr_cbfn(
					cee->cbfn.get_attr_cbarg,
					BFA_STATUS_FAILED);
			पूर्ण
		पूर्ण
		अगर (cee->get_stats_pending == BFA_TRUE) अणु
			cee->get_stats_status = BFA_STATUS_FAILED;
			cee->get_stats_pending  = BFA_FALSE;
			अगर (cee->cbfn.get_stats_cbfn) अणु
				cee->cbfn.get_stats_cbfn(
				cee->cbfn.get_stats_cbarg,
				BFA_STATUS_FAILED);
			पूर्ण
		पूर्ण
		अगर (cee->reset_stats_pending == BFA_TRUE) अणु
			cee->reset_stats_status = BFA_STATUS_FAILED;
			cee->reset_stats_pending  = BFA_FALSE;
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

/*
 * bfa_cee_attach()
 *
 * @brief CEE module-attach API
 *
 * @param[in] cee - Poपूर्णांकer to the CEE module data काष्ठाure
 *            ioc - Poपूर्णांकer to the ioc module data काष्ठाure
 *            dev - Poपूर्णांकer to the device driver module data काष्ठाure
 *                  The device driver specअगरic mbox ISR functions have
 *                  this poपूर्णांकer as one of the parameters.
 *
 * @वापस व्योम
 */
व्योम
bfa_cee_attach(काष्ठा bfa_cee_s *cee, काष्ठा bfa_ioc_s *ioc,
		व्योम *dev)
अणु
	WARN_ON(cee == शून्य);
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_ioc_mbox_regisr(cee->ioc, BFI_MC_CEE, bfa_cee_isr, cee);
	bfa_q_qe_init(&cee->ioc_notअगरy);
	bfa_ioc_notअगरy_init(&cee->ioc_notअगरy, bfa_cee_notअगरy, cee);
	list_add_tail(&cee->ioc_notअगरy.qe, &cee->ioc->notअगरy_q);
पूर्ण
