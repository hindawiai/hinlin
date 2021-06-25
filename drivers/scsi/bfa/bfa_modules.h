<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 *  bfa_modules.h BFA modules
 */

#अगर_अघोषित __BFA_MODULES_H__
#घोषणा __BFA_MODULES_H__

#समावेश "bfa_cs.h"
#समावेश "bfa.h"
#समावेश "bfa_svc.h"
#समावेश "bfa_fcpim.h"
#समावेश "bfa_port.h"

काष्ठा bfa_modules_s अणु
	काष्ठा bfa_fcdiag_s	fcdiag;		/* fcdiag module */
	काष्ठा bfa_fcport_s	fcport;		/*  fc port module	      */
	काष्ठा bfa_fcxp_mod_s	fcxp_mod;	/*  fcxp module	      */
	काष्ठा bfa_lps_mod_s	lps_mod;	/*  fcxp module	      */
	काष्ठा bfa_uf_mod_s	uf_mod;		/*  unsolicited frame module */
	काष्ठा bfa_rport_mod_s	rport_mod;	/*  remote port module	      */
	काष्ठा bfa_fcp_mod_s	fcp_mod;	/*  FCP initiator module     */
	काष्ठा bfa_sgpg_mod_s	sgpg_mod;	/*  SG page module	      */
	काष्ठा bfa_port_s	port;		/*  Physical port module     */
	काष्ठा bfa_ablk_s	ablk;		/*  ASIC block config module */
	काष्ठा bfa_cee_s	cee;		/*  CEE Module	*/
	काष्ठा bfa_sfp_s	sfp;		/*  SFP module	*/
	काष्ठा bfa_flash_s	flash;		/*  flash module */
	काष्ठा bfa_diag_s	diag_mod;	/*  diagnostics module	*/
	काष्ठा bfa_phy_s	phy;		/*  phy module		*/
	काष्ठा bfa_dconf_mod_s	dconf_mod;	/*  DCONF common module	*/
	काष्ठा bfa_fru_s	fru;		/*  fru module		*/
पूर्ण;

/*
 * !!! Only append to the क्रमागतs defined here to aव्योम any versioning
 * !!! needed between trace utility and driver version
 */
क्रमागत अणु
	BFA_TRC_HAL_CORE	= 1,
	BFA_TRC_HAL_FCXP	= 2,
	BFA_TRC_HAL_FCPIM	= 3,
	BFA_TRC_HAL_IOCFC_CT	= 4,
	BFA_TRC_HAL_IOCFC_CB	= 5,
पूर्ण;

#घोषणा BFA_CACHELINE_SZ	(256)

काष्ठा bfa_s अणु
	व्योम			*bfad;		/*  BFA driver instance    */
	काष्ठा bfa_plog_s	*plog;		/*  portlog buffer	    */
	काष्ठा bfa_trc_mod_s	*trcmod;	/*  driver tracing	    */
	काष्ठा bfa_ioc_s	ioc;		/*  IOC module		    */
	काष्ठा bfa_iocfc_s	iocfc;		/*  IOCFC module	    */
	काष्ठा bfa_समयr_mod_s	समयr_mod;	/*  समयr module	    */
	काष्ठा bfa_modules_s	modules;	/*  BFA modules	    */
	काष्ठा list_head	comp_q;		/*  pending completions     */
	bfa_boolean_t		queue_process;	/*  queue processing enabled */
	काष्ठा list_head	reqq_रुकोq[BFI_IOC_MAX_CQS];
	bfa_boolean_t		fcs;		/*  FCS is attached to BFA */
	काष्ठा bfa_msix_s	msix;
	पूर्णांक			bfa_aen_seq;
	bfa_boolean_t		पूर्णांकr_enabled;	/*  Status of पूर्णांकerrupts */
पूर्ण;

बाह्य bfa_boolean_t bfa_स्वतः_recover;

व्योम bfa_dconf_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *);
व्योम bfa_dconf_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		  काष्ठा bfa_s *);
व्योम bfa_dconf_iocdisable(काष्ठा bfa_s *);
व्योम bfa_fcp_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_fcp_iocdisable(काष्ठा bfa_s *bfa);
व्योम bfa_fcp_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_fcpim_iocdisable(काष्ठा bfa_fcp_mod_s *);
व्योम bfa_fcport_start(काष्ठा bfa_s *);
व्योम bfa_fcport_iocdisable(काष्ठा bfa_s *);
व्योम bfa_fcport_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		   काष्ठा bfa_s *);
व्योम bfa_fcport_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_fcxp_iocdisable(काष्ठा bfa_s *);
व्योम bfa_fcxp_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_fcxp_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_fcdiag_iocdisable(काष्ठा bfa_s *);
व्योम bfa_fcdiag_attach(काष्ठा bfa_s *bfa, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_ioim_lm_init(काष्ठा bfa_s *);
व्योम bfa_lps_iocdisable(काष्ठा bfa_s *bfa);
व्योम bfa_lps_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_lps_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
	काष्ठा bfa_pcidev_s *);
व्योम bfa_rport_iocdisable(काष्ठा bfa_s *bfa);
व्योम bfa_rport_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_rport_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_sgpg_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_sgpg_attach(काष्ठा bfa_s *, व्योम *bfad, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_uf_iocdisable(काष्ठा bfa_s *);
व्योम bfa_uf_meminfo(काष्ठा bfa_iocfc_cfg_s *, काष्ठा bfa_meminfo_s *,
		काष्ठा bfa_s *);
व्योम bfa_uf_attach(काष्ठा bfa_s *, व्योम *, काष्ठा bfa_iocfc_cfg_s *,
		काष्ठा bfa_pcidev_s *);
व्योम bfa_uf_start(काष्ठा bfa_s *);

#पूर्ण_अगर /* __BFA_MODULES_H__ */
