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

#समावेश <linux/uaccess.h>
#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfad_bsg.h"

BFA_TRC_खाता(LDRV, BSG);

अटल पूर्णांक
bfad_iocmd_ioc_enable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	/* If IOC is not in disabled state - वापस */
	अगर (!bfa_ioc_is_disabled(&bfad->bfa.ioc)) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_OK;
		वापस 0;
	पूर्ण

	init_completion(&bfad->enable_comp);
	bfa_iocfc_enable(&bfad->bfa);
	iocmd->status = BFA_STATUS_OK;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(&bfad->enable_comp);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_disable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (bfa_ioc_is_disabled(&bfad->bfa.ioc)) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_OK;
		वापस 0;
	पूर्ण

	अगर (bfad->disable_active) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस -EBUSY;
	पूर्ण

	bfad->disable_active = BFA_TRUE;
	init_completion(&bfad->disable_comp);
	bfa_iocfc_disable(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	रुको_क्रम_completion(&bfad->disable_comp);
	bfad->disable_active = BFA_FALSE;
	iocmd->status = BFA_STATUS_OK;

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_get_info(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	पूर्णांक	i;
	काष्ठा bfa_bsg_ioc_info_s *iocmd = (काष्ठा bfa_bsg_ioc_info_s *)cmd;
	काष्ठा bfad_im_port_s	*im_port;
	काष्ठा bfa_port_attr_s	pattr;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcport_get_attr(&bfad->bfa, &pattr);
	iocmd->nwwn = pattr.nwwn;
	iocmd->pwwn = pattr.pwwn;
	iocmd->ioc_type = bfa_get_type(&bfad->bfa);
	iocmd->mac = bfa_get_mac(&bfad->bfa);
	iocmd->factory_mac = bfa_get_mfg_mac(&bfad->bfa);
	bfa_get_adapter_serial_num(&bfad->bfa, iocmd->serialnum);
	iocmd->factorynwwn = pattr.factorynwwn;
	iocmd->factorypwwn = pattr.factorypwwn;
	iocmd->bfad_num = bfad->inst_no;
	im_port = bfad->pport.im_port;
	iocmd->host = im_port->shost->host_no;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	म_नकल(iocmd->name, bfad->adapter_name);
	म_नकल(iocmd->port_name, bfad->port_name);
	म_नकल(iocmd->hwpath, bfad->pci_name);

	/* set adapter hw path */
	म_नकल(iocmd->adapter_hwpath, bfad->pci_name);
	क्रम (i = 0; iocmd->adapter_hwpath[i] != ':' && i < BFA_STRING_32; i++)
		;
	क्रम (; iocmd->adapter_hwpath[++i] != ':' && i < BFA_STRING_32; )
		;
	iocmd->adapter_hwpath[i] = '\0';
	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_ioc_attr_s *iocmd = (काष्ठा bfa_bsg_ioc_attr_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_ioc_get_attr(&bfad->bfa.ioc, &iocmd->ioc_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* fill in driver attr info */
	म_नकल(iocmd->ioc_attr.driver_attr.driver, BFAD_DRIVER_NAME);
	strlcpy(iocmd->ioc_attr.driver_attr.driver_ver,
		BFAD_DRIVER_VERSION, BFA_VERSION_LEN);
	म_नकल(iocmd->ioc_attr.driver_attr.fw_ver,
		iocmd->ioc_attr.adapter_attr.fw_ver);
	म_नकल(iocmd->ioc_attr.driver_attr.bios_ver,
		iocmd->ioc_attr.adapter_attr.optrom_ver);

	/* copy chip rev info first otherwise it will be overwritten */
	स_नकल(bfad->pci_attr.chip_rev, iocmd->ioc_attr.pci_attr.chip_rev,
		माप(bfad->pci_attr.chip_rev));
	स_नकल(&iocmd->ioc_attr.pci_attr, &bfad->pci_attr,
		माप(काष्ठा bfa_ioc_pci_attr_s));

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_ioc_stats_s *iocmd = (काष्ठा bfa_bsg_ioc_stats_s *)cmd;

	bfa_ioc_get_stats(&bfad->bfa, &iocmd->ioc_stats);
	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_get_fwstats(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_ioc_fwstats_s *iocmd =
			(काष्ठा bfa_bsg_ioc_fwstats_s *)cmd;
	व्योम	*iocmd_bufptr;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_ioc_fwstats_s),
			माप(काष्ठा bfa_fw_stats_s)) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		जाओ out;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_ioc_fwstats_s);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ioc_fw_stats_get(&bfad->bfa.ioc, iocmd_bufptr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण
out:
	bfa_trc(bfad, 0x6666);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ	flags;

	अगर (v_cmd == IOCMD_IOC_RESET_STATS) अणु
		bfa_ioc_clear_stats(&bfad->bfa);
		iocmd->status = BFA_STATUS_OK;
	पूर्ण अन्यथा अगर (v_cmd == IOCMD_IOC_RESET_FWSTATS) अणु
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		iocmd->status = bfa_ioc_fw_stats_clear(&bfad->bfa.ioc);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_set_name(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_ioc_name_s *iocmd = (काष्ठा bfa_bsg_ioc_name_s *) cmd;

	अगर (v_cmd == IOCMD_IOC_SET_ADAPTER_NAME)
		म_नकल(bfad->adapter_name, iocmd->name);
	अन्यथा अगर (v_cmd == IOCMD_IOC_SET_PORT_NAME)
		म_नकल(bfad->port_name, iocmd->name);

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_iocfc_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_iocfc_attr_s *iocmd = (काष्ठा bfa_bsg_iocfc_attr_s *)cmd;

	iocmd->status = BFA_STATUS_OK;
	bfa_iocfc_get_attr(&bfad->bfa, &iocmd->iocfc_attr);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_fw_sig_inv(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ioc_fwsig_invalidate(&bfad->bfa.ioc);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_iocfc_set_पूर्णांकr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_iocfc_पूर्णांकr_s *iocmd = (काष्ठा bfa_bsg_iocfc_पूर्णांकr_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_iocfc_israttr_set(&bfad->bfa, &iocmd->attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_enable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_port_enable(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		वापस 0;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_disable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_port_disable(&bfad->bfa.modules.port,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		वापस 0;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_port_attr_s *iocmd = (काष्ठा bfa_bsg_port_attr_s *)cmd;
	काष्ठा bfa_lport_attr_s	port_attr;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcport_get_attr(&bfad->bfa, &iocmd->attr);
	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->attr.topology != BFA_PORT_TOPOLOGY_NONE)
		iocmd->attr.pid = port_attr.pid;
	अन्यथा
		iocmd->attr.pid = 0;

	iocmd->attr.port_type = port_attr.port_type;
	iocmd->attr.loopback = port_attr.loopback;
	iocmd->attr.authfail = port_attr.authfail;
	strlcpy(iocmd->attr.port_symname.symname,
		port_attr.port_cfg.sym_name.symname,
		माप(iocmd->attr.port_symname.symname));

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_port_stats_s *iocmd = (काष्ठा bfa_bsg_port_stats_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	व्योम	*iocmd_bufptr;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_port_stats_s),
			माप(जोड़ bfa_port_stats_u)) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_port_stats_s);

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_port_get_stats(&bfad->bfa.modules.port,
				iocmd_bufptr, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_port_clear_stats(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		वापस 0;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_set_port_cfg(काष्ठा bfad_s *bfad, व्योम *iocmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_port_cfg_s *cmd = (काष्ठा bfa_bsg_port_cfg_s *)iocmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (v_cmd == IOCMD_PORT_CFG_TOPO)
		cmd->status = bfa_fcport_cfg_topology(&bfad->bfa, cmd->param);
	अन्यथा अगर (v_cmd == IOCMD_PORT_CFG_SPEED)
		cmd->status = bfa_fcport_cfg_speed(&bfad->bfa, cmd->param);
	अन्यथा अगर (v_cmd == IOCMD_PORT_CFG_ALPA)
		cmd->status = bfa_fcport_cfg_hardalpa(&bfad->bfa, cmd->param);
	अन्यथा अगर (v_cmd == IOCMD_PORT_CLR_ALPA)
		cmd->status = bfa_fcport_clr_hardalpa(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_cfg_maxfrsize(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_port_cfg_maxfrsize_s *iocmd =
				(काष्ठा bfa_bsg_port_cfg_maxfrsize_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_cfg_maxfrsize(&bfad->bfa, iocmd->maxfrsize);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_cfg_bbcr(काष्ठा bfad_s *bfad, अचिन्हित पूर्णांक cmd, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_bbcr_enable_s *iocmd =
			(काष्ठा bfa_bsg_bbcr_enable_s *)pcmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (cmd == IOCMD_PORT_BBCR_ENABLE)
		rc = bfa_fcport_cfg_bbcr(&bfad->bfa, BFA_TRUE, iocmd->bb_scn);
	अन्यथा अगर (cmd == IOCMD_PORT_BBCR_DISABLE)
		rc = bfa_fcport_cfg_bbcr(&bfad->bfa, BFA_FALSE, 0);
	अन्यथा अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->status = rc;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_get_bbcr_attr(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_bbcr_attr_s *iocmd = (काष्ठा bfa_bsg_bbcr_attr_s *) pcmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status =
		bfa_fcport_get_bbcr_attr(&bfad->bfa, &iocmd->attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण


अटल पूर्णांक
bfad_iocmd_lport_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_lport_s	*fcs_port;
	काष्ठा bfa_bsg_lport_attr_s *iocmd = (काष्ठा bfa_bsg_lport_attr_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_lport_get_attr(fcs_port, &iocmd->port_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_lport_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_bsg_lport_stats_s *iocmd =
			(काष्ठा bfa_bsg_lport_stats_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_lport_get_stats(fcs_port, &iocmd->port_stats);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_lport_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_bsg_reset_stats_s *iocmd =
			(काष्ठा bfa_bsg_reset_stats_s *)cmd;
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(&bfad->bfa);
	काष्ठा list_head *qe, *qen;
	काष्ठा bfa_itnim_s *itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_lport_clear_stats(fcs_port);
	/* clear IO stats from all active itnims */
	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		अगर (itnim->rport->rport_info.lp_tag != fcs_port->lp_tag)
			जारी;
		bfa_itnim_clear_stats(itnim);
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_lport_get_iostats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_bsg_lport_iostats_s *iocmd =
			(काष्ठा bfa_bsg_lport_iostats_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	bfa_fcpim_port_iostats(&bfad->bfa, &iocmd->iostats,
			fcs_port->lp_tag);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_lport_get_rports(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_lport_get_rports_s *iocmd =
			(काष्ठा bfa_bsg_lport_get_rports_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	अचिन्हित दीर्घ	flags;
	व्योम	*iocmd_bufptr;

	अगर (iocmd->nrports == 0)
		वापस -EINVAL;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_lport_get_rports_s),
			माप(काष्ठा bfa_rport_qualअगरier_s) * iocmd->nrports)
			!= BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd +
			माप(काष्ठा bfa_bsg_lport_get_rports_s);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		bfa_trc(bfad, 0);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_lport_get_rport_quals(fcs_port,
			(काष्ठा bfa_rport_qualअगरier_s *)iocmd_bufptr,
			&iocmd->nrports);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_rport_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_attr_s *iocmd = (काष्ठा bfa_bsg_rport_attr_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_rport_s *fcs_rport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	अगर (iocmd->pid)
		fcs_rport = bfa_fcs_lport_get_rport_by_qualअगरier(fcs_port,
						iocmd->rpwwn, iocmd->pid);
	अन्यथा
		fcs_rport = bfa_fcs_rport_lookup(fcs_port, iocmd->rpwwn);
	अगर (fcs_rport == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_rport_get_attr(fcs_rport, &iocmd->attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_rport_get_addr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_scsi_addr_s *iocmd =
			(काष्ठा bfa_bsg_rport_scsi_addr_s *)cmd;
	काष्ठा bfa_fcs_lport_s	*fcs_port;
	काष्ठा bfa_fcs_itnim_s	*fcs_itnim;
	काष्ठा bfad_itnim_s	*drv_itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	fcs_itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
	अगर (fcs_itnim == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	drv_itnim = fcs_itnim->itnim_drv;

	अगर (drv_itnim && drv_itnim->im_port)
		iocmd->host = drv_itnim->im_port->shost->host_no;
	अन्यथा अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	iocmd->target = drv_itnim->scsi_tgt_id;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->bus = 0;
	iocmd->lun = 0;
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_rport_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_stats_s *iocmd =
			(काष्ठा bfa_bsg_rport_stats_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_rport_s *fcs_rport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	fcs_rport = bfa_fcs_rport_lookup(fcs_port, iocmd->rpwwn);
	अगर (fcs_rport == शून्य) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	स_नकल((व्योम *)&iocmd->stats, (व्योम *)&fcs_rport->stats,
		माप(काष्ठा bfa_rport_stats_s));
	अगर (bfa_fcs_rport_get_halrport(fcs_rport)) अणु
		स_नकल((व्योम *)&iocmd->stats.hal_stats,
		       (व्योम *)&(bfa_fcs_rport_get_halrport(fcs_rport)->stats),
			माप(काष्ठा bfa_rport_hal_stats_s));
	पूर्ण

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_rport_clr_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_reset_stats_s *iocmd =
				(काष्ठा bfa_bsg_rport_reset_stats_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_rport_s *fcs_rport;
	काष्ठा bfa_rport_s *rport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	fcs_rport = bfa_fcs_rport_lookup(fcs_port, iocmd->rpwwn);
	अगर (fcs_rport == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	स_रखो((अक्षर *)&fcs_rport->stats, 0, माप(काष्ठा bfa_rport_stats_s));
	rport = bfa_fcs_rport_get_halrport(fcs_rport);
	अगर (rport)
		स_रखो(&rport->stats, 0, माप(rport->stats));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_rport_set_speed(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_set_speed_s *iocmd =
				(काष्ठा bfa_bsg_rport_set_speed_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_rport_s *fcs_rport;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (fcs_port == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		जाओ out;
	पूर्ण

	fcs_rport = bfa_fcs_rport_lookup(fcs_port, iocmd->rpwwn);
	अगर (fcs_rport == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		जाओ out;
	पूर्ण

	fcs_rport->rpf.asचिन्हित_speed  = iocmd->speed;
	/* Set this speed in f/w only अगर the RPSC speed is not available */
	अगर (fcs_rport->rpf.rpsc_speed == BFA_PORT_SPEED_UNKNOWN)
		अगर (fcs_rport->bfa_rport)
			bfa_rport_speed(fcs_rport->bfa_rport, iocmd->speed);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vport_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	काष्ठा bfa_bsg_vport_attr_s *iocmd = (काष्ठा bfa_bsg_vport_attr_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	अगर (fcs_vport == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VWWN;
		जाओ out;
	पूर्ण

	bfa_fcs_vport_get_attr(fcs_vport, &iocmd->vport_attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vport_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	काष्ठा bfa_bsg_vport_stats_s *iocmd =
				(काष्ठा bfa_bsg_vport_stats_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	अगर (fcs_vport == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VWWN;
		जाओ out;
	पूर्ण

	स_नकल((व्योम *)&iocmd->vport_stats, (व्योम *)&fcs_vport->vport_stats,
		माप(काष्ठा bfa_vport_stats_s));
	स_नकल((व्योम *)&iocmd->vport_stats.port_stats,
	       (व्योम *)&fcs_vport->lport.stats,
		माप(काष्ठा bfa_lport_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vport_clr_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	काष्ठा bfa_bsg_reset_stats_s *iocmd =
				(काष्ठा bfa_bsg_reset_stats_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	अगर (fcs_vport == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VWWN;
		जाओ out;
	पूर्ण

	स_रखो(&fcs_vport->vport_stats, 0, माप(काष्ठा bfa_vport_stats_s));
	स_रखो(&fcs_vport->lport.stats, 0, माप(काष्ठा bfa_lport_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fabric_get_lports(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_fabric_get_lports_s *iocmd =
			(काष्ठा bfa_bsg_fabric_get_lports_s *)cmd;
	bfa_fcs_vf_t	*fcs_vf;
	uपूर्णांक32_t	nports = iocmd->nports;
	अचिन्हित दीर्घ	flags;
	व्योम	*iocmd_bufptr;

	अगर (nports == 0) अणु
		iocmd->status = BFA_STATUS_EINVAL;
		जाओ out;
	पूर्ण

	अगर (bfad_chk_iocmd_sz(payload_len,
		माप(काष्ठा bfa_bsg_fabric_get_lports_s),
		माप(wwn_t) * iocmd->nports) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		जाओ out;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd +
			माप(काष्ठा bfa_bsg_fabric_get_lports_s);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vf = bfa_fcs_vf_lookup(&bfad->bfa_fcs, iocmd->vf_id);
	अगर (fcs_vf == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VFID;
		जाओ out;
	पूर्ण
	bfa_fcs_vf_get_ports(fcs_vf, (wwn_t *)iocmd_bufptr, &nports);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->nports = nports;
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos_set_bw(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_qos_bw_s *iocmd = (काष्ठा bfa_bsg_qos_bw_s *)pcmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_set_qos_bw(&bfad->bfa, &iocmd->qos_bw);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ratelim(काष्ठा bfad_s *bfad, अचिन्हित पूर्णांक cmd, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)pcmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा अणु
		अगर (cmd == IOCMD_RATELIM_ENABLE)
			fcport->cfg.ratelimit = BFA_TRUE;
		अन्यथा अगर (cmd == IOCMD_RATELIM_DISABLE)
			fcport->cfg.ratelimit = BFA_FALSE;

		अगर (fcport->cfg.trl_def_speed == BFA_PORT_SPEED_UNKNOWN)
			fcport->cfg.trl_def_speed = BFA_PORT_SPEED_1GBPS;

		iocmd->status = BFA_STATUS_OK;
	पूर्ण

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ratelim_speed(काष्ठा bfad_s *bfad, अचिन्हित पूर्णांक cmd, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_trl_speed_s *iocmd = (काष्ठा bfa_bsg_trl_speed_s *)pcmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	/* Auto and speeds greater than the supported speed, are invalid */
	अगर ((iocmd->speed == BFA_PORT_SPEED_AUTO) ||
	    (iocmd->speed > fcport->speed_sup)) अणु
		iocmd->status = BFA_STATUS_UNSUPP_SPEED;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस 0;
	पूर्ण

	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा अणु
		fcport->cfg.trl_def_speed = iocmd->speed;
		iocmd->status = BFA_STATUS_OK;
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_cfg_fcpim(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_s *iocmd = (काष्ठा bfa_bsg_fcpim_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcpim_path_tov_set(&bfad->bfa, iocmd->param);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_get_modstats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_modstats_s *iocmd =
			(काष्ठा bfa_bsg_fcpim_modstats_s *)cmd;
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(&bfad->bfa);
	काष्ठा list_head *qe, *qen;
	काष्ठा bfa_itnim_s *itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	/* accumulate IO stats from itnim */
	स_रखो((व्योम *)&iocmd->modstats, 0, माप(काष्ठा bfa_itnim_iostats_s));
	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		bfa_fcpim_add_stats(&iocmd->modstats, &(itnim->stats));
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_clr_modstats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_modstatsclr_s *iocmd =
				(काष्ठा bfa_bsg_fcpim_modstatsclr_s *)cmd;
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(&bfad->bfa);
	काष्ठा list_head *qe, *qen;
	काष्ठा bfa_itnim_s *itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	list_क्रम_each_safe(qe, qen, &fcpim->itnim_q) अणु
		itnim = (काष्ठा bfa_itnim_s *) qe;
		bfa_itnim_clear_stats(itnim);
	पूर्ण
	स_रखो(&fcpim->del_itn_stats, 0,
		माप(काष्ठा bfa_fcpim_del_itn_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_get_del_itn_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_del_itn_stats_s *iocmd =
			(काष्ठा bfa_bsg_fcpim_del_itn_stats_s *)cmd;
	काष्ठा bfa_fcpim_s *fcpim = BFA_FCPIM(&bfad->bfa);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	स_नकल((व्योम *)&iocmd->modstats, (व्योम *)&fcpim->del_itn_stats,
		माप(काष्ठा bfa_fcpim_del_itn_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_itnim_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_itnim_attr_s *iocmd = (काष्ठा bfa_bsg_itnim_attr_s *)cmd;
	काष्ठा bfa_fcs_lport_s	*fcs_port;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->lpwwn);
	अगर (!fcs_port)
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
	अन्यथा
		iocmd->status = bfa_fcs_itnim_attr_get(fcs_port,
					iocmd->rpwwn, &iocmd->attr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_itnim_get_iostats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_itnim_iostats_s *iocmd =
			(काष्ठा bfa_bsg_itnim_iostats_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_itnim_s *itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->lpwwn);
	अगर (!fcs_port) अणु
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		bfa_trc(bfad, 0);
	पूर्ण अन्यथा अणु
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		अगर (itnim == शून्य)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		अन्यथा अणु
			iocmd->status = BFA_STATUS_OK;
			अगर (bfa_fcs_itnim_get_halitn(itnim))
				स_नकल((व्योम *)&iocmd->iostats, (व्योम *)
				&(bfa_fcs_itnim_get_halitn(itnim)->stats),
				       माप(काष्ठा bfa_itnim_iostats_s));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_itnim_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_rport_reset_stats_s *iocmd =
			(काष्ठा bfa_bsg_rport_reset_stats_s *)cmd;
	काष्ठा bfa_fcs_lport_s	*fcs_port;
	काष्ठा bfa_fcs_itnim_s	*itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	अगर (!fcs_port)
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
	अन्यथा अणु
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		अगर (itnim == शून्य)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		अन्यथा अणु
			iocmd->status = BFA_STATUS_OK;
			bfa_fcs_itnim_stats_clear(fcs_port, iocmd->rpwwn);
			bfa_itnim_clear_stats(bfa_fcs_itnim_get_halitn(itnim));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_itnim_get_itnstats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_itnim_itnstats_s *iocmd =
			(काष्ठा bfa_bsg_itnim_itnstats_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_itnim_s *itnim;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->lpwwn);
	अगर (!fcs_port) अणु
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		bfa_trc(bfad, 0);
	पूर्ण अन्यथा अणु
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		अगर (itnim == शून्य)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		अन्यथा अणु
			iocmd->status = BFA_STATUS_OK;
			bfa_fcs_itnim_stats_get(fcs_port, iocmd->rpwwn,
					&iocmd->itnstats);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcport_enable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_enable(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcport_disable(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_disable(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ioc_get_pcअगरn_cfg(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_pcअगरn_cfg_s *iocmd = (काष्ठा bfa_bsg_pcअगरn_cfg_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_query(&bfad->bfa.modules.ablk,
				&iocmd->pcअगरn_cfg,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_pcअगरn_create(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_pcअगरn_s *iocmd = (काष्ठा bfa_bsg_pcअगरn_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_pf_create(&bfad->bfa.modules.ablk,
				&iocmd->pcअगरn_id, iocmd->port,
				iocmd->pcअगरn_class, iocmd->bw_min,
				iocmd->bw_max, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_pcअगरn_delete(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_pcअगरn_s *iocmd = (काष्ठा bfa_bsg_pcअगरn_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_pf_delete(&bfad->bfa.modules.ablk,
				iocmd->pcअगरn_id,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_pcअगरn_bw(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_pcअगरn_s *iocmd = (काष्ठा bfa_bsg_pcअगरn_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_pf_update(&bfad->bfa.modules.ablk,
				iocmd->pcअगरn_id, iocmd->bw_min,
				iocmd->bw_max, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	bfa_trc(bfad, iocmd->status);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_adapter_cfg_mode(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_adapter_cfg_mode_s *iocmd =
			(काष्ठा bfa_bsg_adapter_cfg_mode_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_adapter_config(&bfad->bfa.modules.ablk,
				iocmd->cfg.mode, iocmd->cfg.max_pf,
				iocmd->cfg.max_vf, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_port_cfg_mode(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_port_cfg_mode_s *iocmd =
			(काष्ठा bfa_bsg_port_cfg_mode_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ablk_port_config(&bfad->bfa.modules.ablk,
				iocmd->instance, iocmd->cfg.mode,
				iocmd->cfg.max_pf, iocmd->cfg.max_vf,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ablk_optrom(काष्ठा bfad_s *bfad, अचिन्हित पूर्णांक cmd, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)pcmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (cmd == IOCMD_FLASH_ENABLE_OPTROM)
		iocmd->status = bfa_ablk_optrom_en(&bfad->bfa.modules.ablk,
					bfad_hcb_comp, &fcomp);
	अन्यथा
		iocmd->status = bfa_ablk_optrom_dis(&bfad->bfa.modules.ablk,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_faa_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_faa_attr_s *iocmd = (काष्ठा bfa_bsg_faa_attr_s *)cmd;
	काष्ठा bfad_hal_comp    fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	iocmd->status = BFA_STATUS_OK;
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_faa_query(&bfad->bfa, &iocmd->faa_attr,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_cee_attr(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_cee_attr_s *iocmd =
				(काष्ठा bfa_bsg_cee_attr_s *)cmd;
	व्योम	*iocmd_bufptr;
	काष्ठा bfad_hal_comp	cee_comp;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_cee_attr_s),
			माप(काष्ठा bfa_cee_attr_s)) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_cee_attr_s);

	cee_comp.status = 0;
	init_completion(&cee_comp.comp);
	mutex_lock(&bfad_mutex);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_cee_get_attr(&bfad->bfa.modules.cee, iocmd_bufptr,
					 bfad_hcb_comp, &cee_comp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		mutex_unlock(&bfad_mutex);
		bfa_trc(bfad, 0x5555);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&cee_comp.comp);
	mutex_unlock(&bfad_mutex);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_cee_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_cee_stats_s *iocmd =
				(काष्ठा bfa_bsg_cee_stats_s *)cmd;
	व्योम	*iocmd_bufptr;
	काष्ठा bfad_hal_comp	cee_comp;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_cee_stats_s),
			माप(काष्ठा bfa_cee_stats_s)) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_cee_stats_s);

	cee_comp.status = 0;
	init_completion(&cee_comp.comp);
	mutex_lock(&bfad_mutex);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_cee_get_stats(&bfad->bfa.modules.cee, iocmd_bufptr,
					bfad_hcb_comp, &cee_comp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		mutex_unlock(&bfad_mutex);
		bfa_trc(bfad, 0x5555);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&cee_comp.comp);
	mutex_unlock(&bfad_mutex);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_cee_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_cee_reset_stats(&bfad->bfa.modules.cee, शून्य, शून्य);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		bfa_trc(bfad, 0x5555);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_sfp_media(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_sfp_media_s *iocmd = (काष्ठा bfa_bsg_sfp_media_s *)cmd;
	काष्ठा bfad_hal_comp	fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_sfp_media(BFA_SFP_MOD(&bfad->bfa), &iocmd->media,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_SFP_NOT_READY)
		जाओ out;

	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_sfp_speed(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_sfp_speed_s *iocmd = (काष्ठा bfa_bsg_sfp_speed_s *)cmd;
	काष्ठा bfad_hal_comp	fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_sfp_speed(BFA_SFP_MOD(&bfad->bfa), iocmd->speed,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_SFP_NOT_READY)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_flash_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_flash_attr_s *iocmd =
			(काष्ठा bfa_bsg_flash_attr_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_get_attr(BFA_FLASH(&bfad->bfa), &iocmd->attr,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_flash_erase_part(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_flash_s *iocmd = (काष्ठा bfa_bsg_flash_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_erase_part(BFA_FLASH(&bfad->bfa), iocmd->type,
				iocmd->instance, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_flash_update_part(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_flash_s *iocmd = (काष्ठा bfa_bsg_flash_s *)cmd;
	व्योम	*iocmd_bufptr;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_flash_s),
			iocmd->bufsz) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_flash_s);

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_update_part(BFA_FLASH(&bfad->bfa),
				iocmd->type, iocmd->instance, iocmd_bufptr,
				iocmd->bufsz, 0, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_flash_पढ़ो_part(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_flash_s *iocmd = (काष्ठा bfa_bsg_flash_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	व्योम	*iocmd_bufptr;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_flash_s),
			iocmd->bufsz) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_flash_s);

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_पढ़ो_part(BFA_FLASH(&bfad->bfa), iocmd->type,
				iocmd->instance, iocmd_bufptr, iocmd->bufsz, 0,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_temp(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_get_temp_s *iocmd =
			(काष्ठा bfa_bsg_diag_get_temp_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_diag_tsensor_query(BFA_DIAG_MOD(&bfad->bfa),
				&iocmd->result, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_memtest(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_memtest_s *iocmd =
			(काष्ठा bfa_bsg_diag_memtest_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_diag_memtest(BFA_DIAG_MOD(&bfad->bfa),
				&iocmd->memtest, iocmd->pat,
				&iocmd->result, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_loopback(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_loopback_s *iocmd =
			(काष्ठा bfa_bsg_diag_loopback_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcdiag_loopback(&bfad->bfa, iocmd->opmode,
				iocmd->speed, iocmd->lpcnt, iocmd->pat,
				&iocmd->result, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_fwping(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_fwping_s *iocmd =
			(काष्ठा bfa_bsg_diag_fwping_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_diag_fwping(BFA_DIAG_MOD(&bfad->bfa), iocmd->cnt,
				iocmd->pattern, &iocmd->result,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	bfa_trc(bfad, 0x77771);
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_queuetest(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_qtest_s *iocmd = (काष्ठा bfa_bsg_diag_qtest_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcdiag_queuetest(&bfad->bfa, iocmd->क्रमce,
				iocmd->queue, &iocmd->result,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_sfp(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_sfp_show_s *iocmd =
			(काष्ठा bfa_bsg_sfp_show_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_sfp_show(BFA_SFP_MOD(&bfad->bfa), &iocmd->sfp,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	bfa_trc(bfad, iocmd->status);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_led(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_led_s *iocmd = (काष्ठा bfa_bsg_diag_led_s *)cmd;
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_diag_ledtest(BFA_DIAG_MOD(&bfad->bfa),
				&iocmd->ledtest);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_beacon_lport(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_beacon_s *iocmd =
			(काष्ठा bfa_bsg_diag_beacon_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_diag_beacon_port(BFA_DIAG_MOD(&bfad->bfa),
				iocmd->beacon, iocmd->link_e2e_beacon,
				iocmd->second);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_lb_stat(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_diag_lb_stat_s *iocmd =
			(काष्ठा bfa_bsg_diag_lb_stat_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcdiag_lb_is_running(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfa_trc(bfad, iocmd->status);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_dport_enable(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_dport_enable_s *iocmd =
				(काष्ठा bfa_bsg_dport_enable_s *)pcmd;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfad_hal_comp fcomp;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_dport_enable(&bfad->bfa, iocmd->lpcnt,
					iocmd->pat, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		bfa_trc(bfad, iocmd->status);
	अन्यथा अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_dport_disable(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)pcmd;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfad_hal_comp fcomp;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_dport_disable(&bfad->bfa, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		bfa_trc(bfad, iocmd->status);
	अन्यथा अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_dport_start(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_dport_enable_s *iocmd =
				(काष्ठा bfa_bsg_dport_enable_s *)pcmd;
	अचिन्हित दीर्घ   flags;
	काष्ठा bfad_hal_comp fcomp;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_dport_start(&bfad->bfa, iocmd->lpcnt,
					iocmd->pat, bfad_hcb_comp,
					&fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
	पूर्ण अन्यथा अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_diag_dport_show(काष्ठा bfad_s *bfad, व्योम *pcmd)
अणु
	काष्ठा bfa_bsg_diag_dport_show_s *iocmd =
				(काष्ठा bfa_bsg_diag_dport_show_s *)pcmd;
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_dport_show(&bfad->bfa, &iocmd->result);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण


अटल पूर्णांक
bfad_iocmd_phy_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_phy_attr_s *iocmd =
			(काष्ठा bfa_bsg_phy_attr_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_get_attr(BFA_PHY(&bfad->bfa), iocmd->instance,
				&iocmd->attr, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_phy_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_phy_stats_s *iocmd =
			(काष्ठा bfa_bsg_phy_stats_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_get_stats(BFA_PHY(&bfad->bfa), iocmd->instance,
				&iocmd->stats, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_phy_पढ़ो(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_phy_s *iocmd = (काष्ठा bfa_bsg_phy_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	व्योम	*iocmd_bufptr;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_phy_s),
			iocmd->bufsz) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_phy_s);
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_पढ़ो(BFA_PHY(&bfad->bfa),
				iocmd->instance, iocmd_bufptr, iocmd->bufsz,
				0, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vhba_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_vhba_attr_s *iocmd =
			(काष्ठा bfa_bsg_vhba_attr_s *)cmd;
	काष्ठा bfa_vhba_attr_s *attr = &iocmd->attr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	attr->pwwn =  bfad->bfa.ioc.attr->pwwn;
	attr->nwwn =  bfad->bfa.ioc.attr->nwwn;
	attr->plog_enabled = (bfa_boolean_t)bfad->bfa.plog->plog_enabled;
	attr->io_profile = bfa_fcpim_get_io_profile(&bfad->bfa);
	attr->path_tov  = bfa_fcpim_path_tov_get(&bfad->bfa);
	iocmd->status = BFA_STATUS_OK;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_phy_update(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_phy_s *iocmd = (काष्ठा bfa_bsg_phy_s *)cmd;
	व्योम	*iocmd_bufptr;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	अगर (bfad_chk_iocmd_sz(payload_len,
			माप(काष्ठा bfa_bsg_phy_s),
			iocmd->bufsz) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_phy_s);
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_update(BFA_PHY(&bfad->bfa),
				iocmd->instance, iocmd_bufptr, iocmd->bufsz,
				0, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_porglog_get(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_debug_s *iocmd = (काष्ठा bfa_bsg_debug_s *)cmd;
	व्योम *iocmd_bufptr;

	अगर (iocmd->bufsz < माप(काष्ठा bfa_plog_s)) अणु
		bfa_trc(bfad, माप(काष्ठा bfa_plog_s));
		iocmd->status = BFA_STATUS_EINVAL;
		जाओ out;
	पूर्ण

	iocmd->status = BFA_STATUS_OK;
	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_debug_s);
	स_नकल(iocmd_bufptr, (u8 *) &bfad->plog_buf, माप(काष्ठा bfa_plog_s));
out:
	वापस 0;
पूर्ण

#घोषणा BFA_DEBUG_FW_CORE_CHUNK_SZ	0x4000U /* 16K chunks क्रम FW dump */
अटल पूर्णांक
bfad_iocmd_debug_fw_core(काष्ठा bfad_s *bfad, व्योम *cmd,
			अचिन्हित पूर्णांक payload_len)
अणु
	काष्ठा bfa_bsg_debug_s *iocmd = (काष्ठा bfa_bsg_debug_s *)cmd;
	व्योम	*iocmd_bufptr;
	अचिन्हित दीर्घ	flags;
	u32 offset;

	अगर (bfad_chk_iocmd_sz(payload_len, माप(काष्ठा bfa_bsg_debug_s),
			BFA_DEBUG_FW_CORE_CHUNK_SZ) != BFA_STATUS_OK) अणु
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		वापस 0;
	पूर्ण

	अगर (iocmd->bufsz < BFA_DEBUG_FW_CORE_CHUNK_SZ ||
			!IS_ALIGNED(iocmd->bufsz, माप(u16)) ||
			!IS_ALIGNED(iocmd->offset, माप(u32))) अणु
		bfa_trc(bfad, BFA_DEBUG_FW_CORE_CHUNK_SZ);
		iocmd->status = BFA_STATUS_EINVAL;
		जाओ out;
	पूर्ण

	iocmd_bufptr = (अक्षर *)iocmd + माप(काष्ठा bfa_bsg_debug_s);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	offset = iocmd->offset;
	iocmd->status = bfa_ioc_debug_fwcore(&bfad->bfa.ioc, iocmd_bufptr,
				&offset, &iocmd->bufsz);
	iocmd->offset = offset;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_debug_ctl(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	अचिन्हित दीर्घ	flags;

	अगर (v_cmd == IOCMD_DEBUG_FW_STATE_CLR) अणु
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfa.ioc.dbg_fwsave_once = BFA_TRUE;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण अन्यथा अगर (v_cmd == IOCMD_DEBUG_PORTLOG_CLR)
		bfad->plog_buf.head = bfad->plog_buf.tail = 0;
	अन्यथा अगर (v_cmd == IOCMD_DEBUG_START_DTRC)
		bfa_trc_init(bfad->trcmod);
	अन्यथा अगर (v_cmd == IOCMD_DEBUG_STOP_DTRC)
		bfa_trc_stop(bfad->trcmod);

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_porglog_ctl(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_portlogctl_s *iocmd = (काष्ठा bfa_bsg_portlogctl_s *)cmd;

	अगर (iocmd->ctl == BFA_TRUE)
		bfad->plog_buf.plog_enabled = 1;
	अन्यथा
		bfad->plog_buf.plog_enabled = 0;

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_cfg_profile(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_fcpim_profile_s *iocmd =
				(काष्ठा bfa_bsg_fcpim_profile_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (v_cmd == IOCMD_FCPIM_PROखाता_ON)
		iocmd->status = bfa_fcpim_profile_on(&bfad->bfa, kसमय_get_real_seconds());
	अन्यथा अगर (v_cmd == IOCMD_FCPIM_PROखाता_OFF)
		iocmd->status = bfa_fcpim_profile_off(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_itnim_get_ioprofile(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_itnim_ioprofile_s *iocmd =
				(काष्ठा bfa_bsg_itnim_ioprofile_s *)cmd;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_itnim_s *itnim;
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->lpwwn);
	अगर (!fcs_port)
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
	अन्यथा अणु
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		अगर (itnim == शून्य)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		अन्यथा
			iocmd->status = bfa_itnim_get_ioprofile(
						bfa_fcs_itnim_get_halitn(itnim),
						&iocmd->ioprofile);
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcport_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcport_stats_s *iocmd =
				(काष्ठा bfa_bsg_fcport_stats_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfa_cb_pending_q_s cb_qe;

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp,
			   &fcomp, &iocmd->stats);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_get_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcport_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfa_cb_pending_q_s cb_qe;

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp, &fcomp, शून्य);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_clear_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_boot_cfg(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_boot_s *iocmd = (काष्ठा bfa_bsg_boot_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_update_part(BFA_FLASH(&bfad->bfa),
			BFA_FLASH_PART_BOOT, bfad->bfa.ioc.port_id,
			&iocmd->cfg, माप(काष्ठा bfa_boot_cfg_s), 0,
			bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_boot_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_boot_s *iocmd = (काष्ठा bfa_bsg_boot_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_पढ़ो_part(BFA_FLASH(&bfad->bfa),
			BFA_FLASH_PART_BOOT, bfad->bfa.ioc.port_id,
			&iocmd->cfg, माप(काष्ठा bfa_boot_cfg_s), 0,
			bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_preboot_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_preboot_s *iocmd = (काष्ठा bfa_bsg_preboot_s *)cmd;
	काष्ठा bfi_iocfc_cfgrsp_s *cfgrsp = bfad->bfa.iocfc.cfgrsp;
	काष्ठा bfa_boot_pbc_s *pbcfg = &iocmd->cfg;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	pbcfg->enable = cfgrsp->pbc_cfg.boot_enabled;
	pbcfg->nbluns = cfgrsp->pbc_cfg.nbluns;
	pbcfg->speed = cfgrsp->pbc_cfg.port_speed;
	स_नकल(pbcfg->pblun, cfgrsp->pbc_cfg.blun, माप(pbcfg->pblun));
	iocmd->status = BFA_STATUS_OK;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ethboot_cfg(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_ethboot_s *iocmd = (काष्ठा bfa_bsg_ethboot_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_update_part(BFA_FLASH(&bfad->bfa),
				BFA_FLASH_PART_PXECFG,
				bfad->bfa.ioc.port_id, &iocmd->cfg,
				माप(काष्ठा bfa_ethboot_cfg_s), 0,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_ethboot_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_ethboot_s *iocmd = (काष्ठा bfa_bsg_ethboot_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_पढ़ो_part(BFA_FLASH(&bfad->bfa),
				BFA_FLASH_PART_PXECFG,
				bfad->bfa.ioc.port_id, &iocmd->cfg,
				माप(काष्ठा bfa_ethboot_cfg_s), 0,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK)
		जाओ out;
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_cfg_trunk(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	काष्ठा bfa_fcport_trunk_s *trunk = &fcport->trunk;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	अगर (bfa_fcport_is_dport(&bfad->bfa)) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस BFA_STATUS_DPORT_ERR;
	पूर्ण

	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) ||
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा अणु
		अगर (v_cmd == IOCMD_TRUNK_ENABLE) अणु
			trunk->attr.state = BFA_TRUNK_OFFLINE;
			bfa_fcport_disable(&bfad->bfa);
			fcport->cfg.trunked = BFA_TRUE;
		पूर्ण अन्यथा अगर (v_cmd == IOCMD_TRUNK_DISABLE) अणु
			trunk->attr.state = BFA_TRUNK_DISABLED;
			bfa_fcport_disable(&bfad->bfa);
			fcport->cfg.trunked = BFA_FALSE;
		पूर्ण

		अगर (!bfa_fcport_is_disabled(&bfad->bfa))
			bfa_fcport_enable(&bfad->bfa);

		iocmd->status = BFA_STATUS_OK;
	पूर्ण

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_trunk_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_trunk_attr_s *iocmd = (काष्ठा bfa_bsg_trunk_attr_s *)cmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	काष्ठा bfa_fcport_trunk_s *trunk = &fcport->trunk;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) ||
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा अणु
		स_नकल((व्योम *)&iocmd->attr, (व्योम *)&trunk->attr,
			माप(काष्ठा bfa_trunk_attr_s));
		iocmd->attr.port_id = bfa_lps_get_base_pid(&bfad->bfa);
		iocmd->status = BFA_STATUS_OK;
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (bfa_ioc_get_type(&bfad->bfa.ioc) == BFA_IOC_TYPE_FC) अणु
		अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
			iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
		अन्यथा अणु
			अगर (v_cmd == IOCMD_QOS_ENABLE)
				fcport->cfg.qos_enabled = BFA_TRUE;
			अन्यथा अगर (v_cmd == IOCMD_QOS_DISABLE) अणु
				fcport->cfg.qos_enabled = BFA_FALSE;
				fcport->cfg.qos_bw.high = BFA_QOS_BW_HIGH;
				fcport->cfg.qos_bw.med = BFA_QOS_BW_MED;
				fcport->cfg.qos_bw.low = BFA_QOS_BW_LOW;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos_get_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_qos_attr_s *iocmd = (काष्ठा bfa_bsg_qos_attr_s *)cmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा अणु
		iocmd->attr.state = fcport->qos_attr.state;
		iocmd->attr.total_bb_cr =
			be32_to_cpu(fcport->qos_attr.total_bb_cr);
		iocmd->attr.qos_bw.high = fcport->cfg.qos_bw.high;
		iocmd->attr.qos_bw.med = fcport->cfg.qos_bw.med;
		iocmd->attr.qos_bw.low = fcport->cfg.qos_bw.low;
		iocmd->attr.qos_bw_op = fcport->qos_attr.qos_bw_op;
		iocmd->status = BFA_STATUS_OK;
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos_get_vc_attr(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_qos_vc_attr_s *iocmd =
				(काष्ठा bfa_bsg_qos_vc_attr_s *)cmd;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);
	काष्ठा bfa_qos_vc_attr_s *bfa_vc_attr = &fcport->qos_vc_attr;
	अचिन्हित दीर्घ	flags;
	u32	i = 0;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->attr.total_vc_count = be16_to_cpu(bfa_vc_attr->total_vc_count);
	iocmd->attr.shared_credit  = be16_to_cpu(bfa_vc_attr->shared_credit);
	iocmd->attr.elp_opmode_flags  =
				be32_to_cpu(bfa_vc_attr->elp_opmode_flags);

	/* Inभागidual VC info */
	जबतक (i < iocmd->attr.total_vc_count) अणु
		iocmd->attr.vc_info[i].vc_credit =
				bfa_vc_attr->vc_info[i].vc_credit;
		iocmd->attr.vc_info[i].borrow_credit =
				bfa_vc_attr->vc_info[i].borrow_credit;
		iocmd->attr.vc_info[i].priority =
				bfa_vc_attr->vc_info[i].priority;
		i++;
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->status = BFA_STATUS_OK;
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcport_stats_s *iocmd =
				(काष्ठा bfa_bsg_fcport_stats_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfa_cb_pending_q_s cb_qe;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp,
			   &fcomp, &iocmd->stats);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	WARN_ON(!bfa_ioc_get_fcmode(&bfad->bfa.ioc));
	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा
		iocmd->status = bfa_fcport_get_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_qos_reset_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfa_cb_pending_q_s cb_qe;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp,
			   &fcomp, शून्य);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	WARN_ON(!bfa_ioc_get_fcmode(&bfad->bfa.ioc));
	अगर ((fcport->cfg.topology == BFA_PORT_TOPOLOGY_LOOP) &&
		(fcport->topology == BFA_PORT_TOPOLOGY_LOOP))
		iocmd->status = BFA_STATUS_TOPOLOGY_LOOP;
	अन्यथा
		iocmd->status = bfa_fcport_clear_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status != BFA_STATUS_OK) अणु
		bfa_trc(bfad, iocmd->status);
		जाओ out;
	पूर्ण
	रुको_क्रम_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vf_get_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_vf_stats_s *iocmd =
			(काष्ठा bfa_bsg_vf_stats_s *)cmd;
	काष्ठा bfa_fcs_fabric_s	*fcs_vf;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vf = bfa_fcs_vf_lookup(&bfad->bfa_fcs, iocmd->vf_id);
	अगर (fcs_vf == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VFID;
		जाओ out;
	पूर्ण
	स_नकल((व्योम *)&iocmd->stats, (व्योम *)&fcs_vf->stats,
		माप(काष्ठा bfa_vf_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_vf_clr_stats(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_vf_reset_stats_s *iocmd =
			(काष्ठा bfa_bsg_vf_reset_stats_s *)cmd;
	काष्ठा bfa_fcs_fabric_s	*fcs_vf;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vf = bfa_fcs_vf_lookup(&bfad->bfa_fcs, iocmd->vf_id);
	अगर (fcs_vf == शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VFID;
		जाओ out;
	पूर्ण
	स_रखो((व्योम *)&fcs_vf->stats, 0, माप(काष्ठा bfa_vf_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	वापस 0;
पूर्ण

/* Function to reset the LUN SCAN mode */
अटल व्योम
bfad_iocmd_lunmask_reset_lunscan_mode(काष्ठा bfad_s *bfad, पूर्णांक lunmask_cfg)
अणु
	काष्ठा bfad_im_port_s *pport_im = bfad->pport.im_port;
	काष्ठा bfad_vport_s *vport = शून्य;

	/* Set the scsi device LUN SCAN flags क्रम base port */
	bfad_reset_sdev_bflags(pport_im, lunmask_cfg);

	/* Set the scsi device LUN SCAN flags क्रम the vports */
	list_क्रम_each_entry(vport, &bfad->vport_list, list_entry)
		bfad_reset_sdev_bflags(vport->drv_port.im_port, lunmask_cfg);
पूर्ण

अटल पूर्णांक
bfad_iocmd_lunmask(काष्ठा bfad_s *bfad, व्योम *pcmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_gen_s *iocmd = (काष्ठा bfa_bsg_gen_s *)pcmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (v_cmd == IOCMD_FCPIM_LUNMASK_ENABLE) अणु
		iocmd->status = bfa_fcpim_lunmask_update(&bfad->bfa, BFA_TRUE);
		/* Set the LUN Scanning mode to be Sequential scan */
		अगर (iocmd->status == BFA_STATUS_OK)
			bfad_iocmd_lunmask_reset_lunscan_mode(bfad, BFA_TRUE);
	पूर्ण अन्यथा अगर (v_cmd == IOCMD_FCPIM_LUNMASK_DISABLE) अणु
		iocmd->status = bfa_fcpim_lunmask_update(&bfad->bfa, BFA_FALSE);
		/* Set the LUN Scanning mode to शेष REPORT_LUNS scan */
		अगर (iocmd->status == BFA_STATUS_OK)
			bfad_iocmd_lunmask_reset_lunscan_mode(bfad, BFA_FALSE);
	पूर्ण अन्यथा अगर (v_cmd == IOCMD_FCPIM_LUNMASK_CLEAR)
		iocmd->status = bfa_fcpim_lunmask_clear(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_lunmask_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_lunmask_query_s *iocmd =
			(काष्ठा bfa_bsg_fcpim_lunmask_query_s *)cmd;
	काष्ठा bfa_lunmask_cfg_s *lun_mask = &iocmd->lun_mask;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcpim_lunmask_query(&bfad->bfa, lun_mask);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_cfg_lunmask(काष्ठा bfad_s *bfad, व्योम *cmd, अचिन्हित पूर्णांक v_cmd)
अणु
	काष्ठा bfa_bsg_fcpim_lunmask_s *iocmd =
				(काष्ठा bfa_bsg_fcpim_lunmask_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (v_cmd == IOCMD_FCPIM_LUNMASK_ADD)
		iocmd->status = bfa_fcpim_lunmask_add(&bfad->bfa, iocmd->vf_id,
					&iocmd->pwwn, iocmd->rpwwn, iocmd->lun);
	अन्यथा अगर (v_cmd == IOCMD_FCPIM_LUNMASK_DELETE)
		iocmd->status = bfa_fcpim_lunmask_delete(&bfad->bfa,
					iocmd->vf_id, &iocmd->pwwn,
					iocmd->rpwwn, iocmd->lun);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_throttle_query(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_throttle_s *iocmd =
			(काष्ठा bfa_bsg_fcpim_throttle_s *)cmd;
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcpim_throttle_get(&bfad->bfa,
				(व्योम *)&iocmd->throttle);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fcpim_throttle_set(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fcpim_throttle_s *iocmd =
			(काष्ठा bfa_bsg_fcpim_throttle_s *)cmd;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcpim_throttle_set(&bfad->bfa,
				iocmd->throttle.cfg_value);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_tfru_पढ़ो(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_tfru_s *iocmd =
			(काष्ठा bfa_bsg_tfru_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_tfru_पढ़ो(BFA_FRU(&bfad->bfa),
				&iocmd->data, iocmd->len, iocmd->offset,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status == BFA_STATUS_OK) अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_tfru_ग_लिखो(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_tfru_s *iocmd =
			(काष्ठा bfa_bsg_tfru_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_tfru_ग_लिखो(BFA_FRU(&bfad->bfa),
				&iocmd->data, iocmd->len, iocmd->offset,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status == BFA_STATUS_OK) अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fruvpd_पढ़ो(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fruvpd_s *iocmd =
			(काष्ठा bfa_bsg_fruvpd_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fruvpd_पढ़ो(BFA_FRU(&bfad->bfa),
				&iocmd->data, iocmd->len, iocmd->offset,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status == BFA_STATUS_OK) अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fruvpd_update(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fruvpd_s *iocmd =
			(काष्ठा bfa_bsg_fruvpd_s *)cmd;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fruvpd_update(BFA_FRU(&bfad->bfa),
				&iocmd->data, iocmd->len, iocmd->offset,
				bfad_hcb_comp, &fcomp, iocmd->trfr_cmpl);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (iocmd->status == BFA_STATUS_OK) अणु
		रुको_क्रम_completion(&fcomp.comp);
		iocmd->status = fcomp.status;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_fruvpd_get_max_size(काष्ठा bfad_s *bfad, व्योम *cmd)
अणु
	काष्ठा bfa_bsg_fruvpd_max_size_s *iocmd =
			(काष्ठा bfa_bsg_fruvpd_max_size_s *)cmd;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fruvpd_get_max_size(BFA_FRU(&bfad->bfa),
						&iocmd->max_size);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_iocmd_handler(काष्ठा bfad_s *bfad, अचिन्हित पूर्णांक cmd, व्योम *iocmd,
		अचिन्हित पूर्णांक payload_len)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (cmd) अणु
	हाल IOCMD_IOC_ENABLE:
		rc = bfad_iocmd_ioc_enable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_DISABLE:
		rc = bfad_iocmd_ioc_disable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_GET_INFO:
		rc = bfad_iocmd_ioc_get_info(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_GET_ATTR:
		rc = bfad_iocmd_ioc_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_GET_STATS:
		rc = bfad_iocmd_ioc_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_GET_FWSTATS:
		rc = bfad_iocmd_ioc_get_fwstats(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_IOC_RESET_STATS:
	हाल IOCMD_IOC_RESET_FWSTATS:
		rc = bfad_iocmd_ioc_reset_stats(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_IOC_SET_ADAPTER_NAME:
	हाल IOCMD_IOC_SET_PORT_NAME:
		rc = bfad_iocmd_ioc_set_name(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_IOCFC_GET_ATTR:
		rc = bfad_iocmd_iocfc_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOCFC_SET_INTR:
		rc = bfad_iocmd_iocfc_set_पूर्णांकr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_ENABLE:
		rc = bfad_iocmd_port_enable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_DISABLE:
		rc = bfad_iocmd_port_disable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_GET_ATTR:
		rc = bfad_iocmd_port_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_GET_STATS:
		rc = bfad_iocmd_port_get_stats(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_PORT_RESET_STATS:
		rc = bfad_iocmd_port_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_CFG_TOPO:
	हाल IOCMD_PORT_CFG_SPEED:
	हाल IOCMD_PORT_CFG_ALPA:
	हाल IOCMD_PORT_CLR_ALPA:
		rc = bfad_iocmd_set_port_cfg(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_PORT_CFG_MAXFRSZ:
		rc = bfad_iocmd_port_cfg_maxfrsize(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_BBCR_ENABLE:
	हाल IOCMD_PORT_BBCR_DISABLE:
		rc = bfad_iocmd_port_cfg_bbcr(bfad, cmd, iocmd);
		अवरोध;
	हाल IOCMD_PORT_BBCR_GET_ATTR:
		rc = bfad_iocmd_port_get_bbcr_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_LPORT_GET_ATTR:
		rc = bfad_iocmd_lport_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_LPORT_GET_STATS:
		rc = bfad_iocmd_lport_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_LPORT_RESET_STATS:
		rc = bfad_iocmd_lport_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_LPORT_GET_IOSTATS:
		rc = bfad_iocmd_lport_get_iostats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_LPORT_GET_RPORTS:
		rc = bfad_iocmd_lport_get_rports(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_RPORT_GET_ATTR:
		rc = bfad_iocmd_rport_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_RPORT_GET_ADDR:
		rc = bfad_iocmd_rport_get_addr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_RPORT_GET_STATS:
		rc = bfad_iocmd_rport_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_RPORT_RESET_STATS:
		rc = bfad_iocmd_rport_clr_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_RPORT_SET_SPEED:
		rc = bfad_iocmd_rport_set_speed(bfad, iocmd);
		अवरोध;
	हाल IOCMD_VPORT_GET_ATTR:
		rc = bfad_iocmd_vport_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_VPORT_GET_STATS:
		rc = bfad_iocmd_vport_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_VPORT_RESET_STATS:
		rc = bfad_iocmd_vport_clr_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FABRIC_GET_LPORTS:
		rc = bfad_iocmd_fabric_get_lports(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_RATELIM_ENABLE:
	हाल IOCMD_RATELIM_DISABLE:
		rc = bfad_iocmd_ratelim(bfad, cmd, iocmd);
		अवरोध;
	हाल IOCMD_RATELIM_DEF_SPEED:
		rc = bfad_iocmd_ratelim_speed(bfad, cmd, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_FAILOVER:
		rc = bfad_iocmd_cfg_fcpim(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_MODSTATS:
		rc = bfad_iocmd_fcpim_get_modstats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_MODSTATSCLR:
		rc = bfad_iocmd_fcpim_clr_modstats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_DEL_ITN_STATS:
		rc = bfad_iocmd_fcpim_get_del_itn_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ITNIM_GET_ATTR:
		rc = bfad_iocmd_itnim_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ITNIM_GET_IOSTATS:
		rc = bfad_iocmd_itnim_get_iostats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ITNIM_RESET_STATS:
		rc = bfad_iocmd_itnim_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ITNIM_GET_ITNSTATS:
		rc = bfad_iocmd_itnim_get_itnstats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPORT_ENABLE:
		rc = bfad_iocmd_fcport_enable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPORT_DISABLE:
		rc = bfad_iocmd_fcport_disable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_PCIFN_CFG:
		rc = bfad_iocmd_ioc_get_pcअगरn_cfg(bfad, iocmd);
		अवरोध;
	हाल IOCMD_IOC_FW_SIG_INV:
		rc = bfad_iocmd_ioc_fw_sig_inv(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PCIFN_CREATE:
		rc = bfad_iocmd_pcअगरn_create(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PCIFN_DELETE:
		rc = bfad_iocmd_pcअगरn_delete(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PCIFN_BW:
		rc = bfad_iocmd_pcअगरn_bw(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ADAPTER_CFG_MODE:
		rc = bfad_iocmd_adapter_cfg_mode(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PORT_CFG_MODE:
		rc = bfad_iocmd_port_cfg_mode(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FLASH_ENABLE_OPTROM:
	हाल IOCMD_FLASH_DISABLE_OPTROM:
		rc = bfad_iocmd_ablk_optrom(bfad, cmd, iocmd);
		अवरोध;
	हाल IOCMD_FAA_QUERY:
		rc = bfad_iocmd_faa_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_CEE_GET_ATTR:
		rc = bfad_iocmd_cee_attr(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_CEE_GET_STATS:
		rc = bfad_iocmd_cee_get_stats(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_CEE_RESET_STATS:
		rc = bfad_iocmd_cee_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_SFP_MEDIA:
		rc = bfad_iocmd_sfp_media(bfad, iocmd);
		 अवरोध;
	हाल IOCMD_SFP_SPEED:
		rc = bfad_iocmd_sfp_speed(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FLASH_GET_ATTR:
		rc = bfad_iocmd_flash_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FLASH_ERASE_PART:
		rc = bfad_iocmd_flash_erase_part(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FLASH_UPDATE_PART:
		rc = bfad_iocmd_flash_update_part(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_FLASH_READ_PART:
		rc = bfad_iocmd_flash_पढ़ो_part(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_DIAG_TEMP:
		rc = bfad_iocmd_diag_temp(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_MEMTEST:
		rc = bfad_iocmd_diag_memtest(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_LOOPBACK:
		rc = bfad_iocmd_diag_loopback(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_FWPING:
		rc = bfad_iocmd_diag_fwping(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_QUEUETEST:
		rc = bfad_iocmd_diag_queuetest(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_SFP:
		rc = bfad_iocmd_diag_sfp(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_LED:
		rc = bfad_iocmd_diag_led(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_BEACON_LPORT:
		rc = bfad_iocmd_diag_beacon_lport(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_LB_STAT:
		rc = bfad_iocmd_diag_lb_stat(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_DPORT_ENABLE:
		rc = bfad_iocmd_diag_dport_enable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_DPORT_DISABLE:
		rc = bfad_iocmd_diag_dport_disable(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_DPORT_SHOW:
		rc = bfad_iocmd_diag_dport_show(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DIAG_DPORT_START:
		rc = bfad_iocmd_diag_dport_start(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PHY_GET_ATTR:
		rc = bfad_iocmd_phy_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PHY_GET_STATS:
		rc = bfad_iocmd_phy_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PHY_UPDATE_FW:
		rc = bfad_iocmd_phy_update(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_PHY_READ_FW:
		rc = bfad_iocmd_phy_पढ़ो(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_VHBA_QUERY:
		rc = bfad_iocmd_vhba_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DEBUG_PORTLOG:
		rc = bfad_iocmd_porglog_get(bfad, iocmd);
		अवरोध;
	हाल IOCMD_DEBUG_FW_CORE:
		rc = bfad_iocmd_debug_fw_core(bfad, iocmd, payload_len);
		अवरोध;
	हाल IOCMD_DEBUG_FW_STATE_CLR:
	हाल IOCMD_DEBUG_PORTLOG_CLR:
	हाल IOCMD_DEBUG_START_DTRC:
	हाल IOCMD_DEBUG_STOP_DTRC:
		rc = bfad_iocmd_debug_ctl(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_DEBUG_PORTLOG_CTL:
		rc = bfad_iocmd_porglog_ctl(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_PROखाता_ON:
	हाल IOCMD_FCPIM_PROखाता_OFF:
		rc = bfad_iocmd_fcpim_cfg_profile(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_ITNIM_GET_IOPROखाता:
		rc = bfad_iocmd_itnim_get_ioprofile(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPORT_GET_STATS:
		rc = bfad_iocmd_fcport_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPORT_RESET_STATS:
		rc = bfad_iocmd_fcport_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_BOOT_CFG:
		rc = bfad_iocmd_boot_cfg(bfad, iocmd);
		अवरोध;
	हाल IOCMD_BOOT_QUERY:
		rc = bfad_iocmd_boot_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_PREBOOT_QUERY:
		rc = bfad_iocmd_preboot_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ETHBOOT_CFG:
		rc = bfad_iocmd_ethboot_cfg(bfad, iocmd);
		अवरोध;
	हाल IOCMD_ETHBOOT_QUERY:
		rc = bfad_iocmd_ethboot_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_TRUNK_ENABLE:
	हाल IOCMD_TRUNK_DISABLE:
		rc = bfad_iocmd_cfg_trunk(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_TRUNK_GET_ATTR:
		rc = bfad_iocmd_trunk_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_QOS_ENABLE:
	हाल IOCMD_QOS_DISABLE:
		rc = bfad_iocmd_qos(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_QOS_GET_ATTR:
		rc = bfad_iocmd_qos_get_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_QOS_GET_VC_ATTR:
		rc = bfad_iocmd_qos_get_vc_attr(bfad, iocmd);
		अवरोध;
	हाल IOCMD_QOS_GET_STATS:
		rc = bfad_iocmd_qos_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_QOS_RESET_STATS:
		rc = bfad_iocmd_qos_reset_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_QOS_SET_BW:
		rc = bfad_iocmd_qos_set_bw(bfad, iocmd);
		अवरोध;
	हाल IOCMD_VF_GET_STATS:
		rc = bfad_iocmd_vf_get_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_VF_RESET_STATS:
		rc = bfad_iocmd_vf_clr_stats(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_LUNMASK_ENABLE:
	हाल IOCMD_FCPIM_LUNMASK_DISABLE:
	हाल IOCMD_FCPIM_LUNMASK_CLEAR:
		rc = bfad_iocmd_lunmask(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_FCPIM_LUNMASK_QUERY:
		rc = bfad_iocmd_fcpim_lunmask_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_LUNMASK_ADD:
	हाल IOCMD_FCPIM_LUNMASK_DELETE:
		rc = bfad_iocmd_fcpim_cfg_lunmask(bfad, iocmd, cmd);
		अवरोध;
	हाल IOCMD_FCPIM_THROTTLE_QUERY:
		rc = bfad_iocmd_fcpim_throttle_query(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FCPIM_THROTTLE_SET:
		rc = bfad_iocmd_fcpim_throttle_set(bfad, iocmd);
		अवरोध;
	/* TFRU */
	हाल IOCMD_TFRU_READ:
		rc = bfad_iocmd_tfru_पढ़ो(bfad, iocmd);
		अवरोध;
	हाल IOCMD_TFRU_WRITE:
		rc = bfad_iocmd_tfru_ग_लिखो(bfad, iocmd);
		अवरोध;
	/* FRU */
	हाल IOCMD_FRUVPD_READ:
		rc = bfad_iocmd_fruvpd_पढ़ो(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FRUVPD_UPDATE:
		rc = bfad_iocmd_fruvpd_update(bfad, iocmd);
		अवरोध;
	हाल IOCMD_FRUVPD_GET_MAX_SIZE:
		rc = bfad_iocmd_fruvpd_get_max_size(bfad, iocmd);
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
bfad_im_bsg_venकरोr_request(काष्ठा bsg_job *job)
अणु
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	uपूर्णांक32_t venकरोr_cmd = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[0];
	काष्ठा Scsi_Host *shost = fc_bsg_to_shost(job);
	काष्ठा bfad_im_port_s *im_port = bfad_get_im_port(shost);
	काष्ठा bfad_s *bfad = im_port->bfad;
	व्योम *payload_kbuf;
	पूर्णांक rc = -EINVAL;

	/* Allocate a temp buffer to hold the passed in user space command */
	payload_kbuf = kzalloc(job->request_payload.payload_len, GFP_KERNEL);
	अगर (!payload_kbuf) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Copy the sg_list passed in to a linear buffer: holds the cmnd data */
	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt, payload_kbuf,
			  job->request_payload.payload_len);

	/* Invoke IOCMD handler - to handle all the venकरोr command requests */
	rc = bfad_iocmd_handler(bfad, venकरोr_cmd, payload_kbuf,
				job->request_payload.payload_len);
	अगर (rc != BFA_STATUS_OK)
		जाओ error;

	/* Copy the response data to the job->reply_payload sg_list */
	sg_copy_from_buffer(job->reply_payload.sg_list,
			    job->reply_payload.sg_cnt,
			    payload_kbuf,
			    job->reply_payload.payload_len);

	/* मुक्त the command buffer */
	kमुक्त(payload_kbuf);

	/* Fill the BSG job reply data */
	job->reply_len = job->reply_payload.payload_len;
	bsg_reply->reply_payload_rcv_len = job->reply_payload.payload_len;
	bsg_reply->result = rc;

	bsg_job_करोne(job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस rc;
error:
	/* मुक्त the command buffer */
	kमुक्त(payload_kbuf);
out:
	bsg_reply->result = rc;
	job->reply_len = माप(uपूर्णांक32_t);
	bsg_reply->reply_payload_rcv_len = 0;
	वापस rc;
पूर्ण

/* FC passthru call backs */
अटल u64
bfad_fcxp_get_req_sgaddr_cb(व्योम *bfad_fcxp, पूर्णांक sgeid)
अणु
	काष्ठा bfad_fcxp	*drv_fcxp = bfad_fcxp;
	काष्ठा bfa_sge_s  *sge;
	u64	addr;

	sge = drv_fcxp->req_sge + sgeid;
	addr = (u64)(माप_प्रकार) sge->sg_addr;
	वापस addr;
पूर्ण

अटल u32
bfad_fcxp_get_req_sglen_cb(व्योम *bfad_fcxp, पूर्णांक sgeid)
अणु
	काष्ठा bfad_fcxp	*drv_fcxp = bfad_fcxp;
	काष्ठा bfa_sge_s	*sge;

	sge = drv_fcxp->req_sge + sgeid;
	वापस sge->sg_len;
पूर्ण

अटल u64
bfad_fcxp_get_rsp_sgaddr_cb(व्योम *bfad_fcxp, पूर्णांक sgeid)
अणु
	काष्ठा bfad_fcxp	*drv_fcxp = bfad_fcxp;
	काष्ठा bfa_sge_s	*sge;
	u64	addr;

	sge = drv_fcxp->rsp_sge + sgeid;
	addr = (u64)(माप_प्रकार) sge->sg_addr;
	वापस addr;
पूर्ण

अटल u32
bfad_fcxp_get_rsp_sglen_cb(व्योम *bfad_fcxp, पूर्णांक sgeid)
अणु
	काष्ठा bfad_fcxp	*drv_fcxp = bfad_fcxp;
	काष्ठा bfa_sge_s	*sge;

	sge = drv_fcxp->rsp_sge + sgeid;
	वापस sge->sg_len;
पूर्ण

अटल व्योम
bfad_send_fcpt_cb(व्योम *bfad_fcxp, काष्ठा bfa_fcxp_s *fcxp, व्योम *cbarg,
		bfa_status_t req_status, u32 rsp_len, u32 resid_len,
		काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfad_fcxp *drv_fcxp = bfad_fcxp;

	drv_fcxp->req_status = req_status;
	drv_fcxp->rsp_len = rsp_len;

	/* bfa_fcxp will be स्वतःmatically मुक्तd by BFA */
	drv_fcxp->bfa_fcxp = शून्य;
	complete(&drv_fcxp->comp);
पूर्ण

अटल काष्ठा bfad_buf_info *
bfad_fcxp_map_sg(काष्ठा bfad_s *bfad, व्योम *payload_kbuf,
		 uपूर्णांक32_t payload_len, uपूर्णांक32_t *num_sgles)
अणु
	काष्ठा bfad_buf_info	*buf_base, *buf_info;
	काष्ठा bfa_sge_s	*sg_table;
	पूर्णांक sge_num = 1;

	buf_base = kसुस्मृति(माप(काष्ठा bfad_buf_info) +
				माप(काष्ठा bfa_sge_s),
			   sge_num, GFP_KERNEL);
	अगर (!buf_base)
		वापस शून्य;

	sg_table = (काष्ठा bfa_sge_s *) (((uपूर्णांक8_t *)buf_base) +
			(माप(काष्ठा bfad_buf_info) * sge_num));

	/* Allocate dma coherent memory */
	buf_info = buf_base;
	buf_info->size = payload_len;
	buf_info->virt = dma_alloc_coherent(&bfad->pcidev->dev,
					    buf_info->size, &buf_info->phys,
					    GFP_KERNEL);
	अगर (!buf_info->virt)
		जाओ out_मुक्त_mem;

	/* copy the linear bsg buffer to buf_info */
	स_नकल(buf_info->virt, payload_kbuf, buf_info->size);

	/*
	 * Setup SG table
	 */
	sg_table->sg_len = buf_info->size;
	sg_table->sg_addr = (व्योम *)(माप_प्रकार) buf_info->phys;

	*num_sgles = sge_num;

	वापस buf_base;

out_मुक्त_mem:
	kमुक्त(buf_base);
	वापस शून्य;
पूर्ण

अटल व्योम
bfad_fcxp_मुक्त_mem(काष्ठा bfad_s *bfad, काष्ठा bfad_buf_info *buf_base,
		   uपूर्णांक32_t num_sgles)
अणु
	पूर्णांक i;
	काष्ठा bfad_buf_info *buf_info = buf_base;

	अगर (buf_base) अणु
		क्रम (i = 0; i < num_sgles; buf_info++, i++) अणु
			अगर (buf_info->virt != शून्य)
				dma_मुक्त_coherent(&bfad->pcidev->dev,
					buf_info->size, buf_info->virt,
					buf_info->phys);
		पूर्ण
		kमुक्त(buf_base);
	पूर्ण
पूर्ण

अटल पूर्णांक
bfad_fcxp_bsg_send(काष्ठा bsg_job *job, काष्ठा bfad_fcxp *drv_fcxp,
		   bfa_bsg_fcpt_t *bsg_fcpt)
अणु
	काष्ठा bfa_fcxp_s *hal_fcxp;
	काष्ठा bfad_s	*bfad = drv_fcxp->port->bfad;
	अचिन्हित दीर्घ	flags;
	uपूर्णांक8_t	lp_tag;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	/* Allocate bfa_fcxp काष्ठाure */
	hal_fcxp = bfa_fcxp_req_rsp_alloc(drv_fcxp, &bfad->bfa,
				  drv_fcxp->num_req_sgles,
				  drv_fcxp->num_rsp_sgles,
				  bfad_fcxp_get_req_sgaddr_cb,
				  bfad_fcxp_get_req_sglen_cb,
				  bfad_fcxp_get_rsp_sgaddr_cb,
				  bfad_fcxp_get_rsp_sglen_cb, BFA_TRUE);
	अगर (!hal_fcxp) अणु
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस BFA_STATUS_ENOMEM;
	पूर्ण

	drv_fcxp->bfa_fcxp = hal_fcxp;

	lp_tag = bfa_lps_get_tag_from_pid(&bfad->bfa, bsg_fcpt->fchs.s_id);

	bfa_fcxp_send(hal_fcxp, drv_fcxp->bfa_rport, bsg_fcpt->vf_id, lp_tag,
		      bsg_fcpt->cts, bsg_fcpt->cos,
		      job->request_payload.payload_len,
		      &bsg_fcpt->fchs, bfad_send_fcpt_cb, bfad,
		      job->reply_payload.payload_len, bsg_fcpt->tsecs);

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस BFA_STATUS_OK;
पूर्ण

अटल पूर्णांक
bfad_im_bsg_els_ct_request(काष्ठा bsg_job *job)
अणु
	काष्ठा bfa_bsg_data *bsg_data;
	काष्ठा Scsi_Host *shost = fc_bsg_to_shost(job);
	काष्ठा bfad_im_port_s *im_port = bfad_get_im_port(shost);
	काष्ठा bfad_s *bfad = im_port->bfad;
	bfa_bsg_fcpt_t *bsg_fcpt;
	काष्ठा bfad_fcxp    *drv_fcxp;
	काष्ठा bfa_fcs_lport_s *fcs_port;
	काष्ठा bfa_fcs_rport_s *fcs_rport;
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	uपूर्णांक32_t command_type = bsg_request->msgcode;
	अचिन्हित दीर्घ flags;
	काष्ठा bfad_buf_info *rsp_buf_info;
	व्योम *req_kbuf = शून्य, *rsp_kbuf = शून्य;
	पूर्णांक rc = -EINVAL;

	job->reply_len  = माप(uपूर्णांक32_t);	/* Atleast uपूर्णांक32_t reply_len */
	bsg_reply->reply_payload_rcv_len = 0;

	/* Get the payload passed in from userspace */
	bsg_data = (काष्ठा bfa_bsg_data *) (((अक्षर *)bsg_request) +
					    माप(काष्ठा fc_bsg_request));
	अगर (bsg_data == शून्य)
		जाओ out;

	/*
	 * Allocate buffer क्रम bsg_fcpt and करो a copy_from_user op क्रम payload
	 * buffer of size bsg_data->payload_len
	 */
	bsg_fcpt = kzalloc(bsg_data->payload_len, GFP_KERNEL);
	अगर (!bsg_fcpt) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (copy_from_user((uपूर्णांक8_t *)bsg_fcpt,
				(व्योम *)(अचिन्हित दीर्घ)bsg_data->payload,
				bsg_data->payload_len)) अणु
		kमुक्त(bsg_fcpt);
		rc = -EIO;
		जाओ out;
	पूर्ण

	drv_fcxp = kzalloc(माप(काष्ठा bfad_fcxp), GFP_KERNEL);
	अगर (drv_fcxp == शून्य) अणु
		kमुक्त(bsg_fcpt);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs, bsg_fcpt->vf_id,
					bsg_fcpt->lpwwn);
	अगर (fcs_port == शून्य) अणु
		bsg_fcpt->status = BFA_STATUS_UNKNOWN_LWWN;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		जाओ out_मुक्त_mem;
	पूर्ण

	/* Check अगर the port is online beक्रमe sending FC Passthru cmd */
	अगर (!bfa_fcs_lport_is_online(fcs_port)) अणु
		bsg_fcpt->status = BFA_STATUS_PORT_OFFLINE;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		जाओ out_मुक्त_mem;
	पूर्ण

	drv_fcxp->port = fcs_port->bfad_port;

	अगर (!drv_fcxp->port->bfad)
		drv_fcxp->port->bfad = bfad;

	/* Fetch the bfa_rport - अगर nexus needed */
	अगर (command_type == FC_BSG_HST_ELS_NOLOGIN ||
	    command_type == FC_BSG_HST_CT) अणु
		/* BSG HST commands: no nexus needed */
		drv_fcxp->bfa_rport = शून्य;

	पूर्ण अन्यथा अगर (command_type == FC_BSG_RPT_ELS ||
		   command_type == FC_BSG_RPT_CT) अणु
		/* BSG RPT commands: nexus needed */
		fcs_rport = bfa_fcs_lport_get_rport_by_pwwn(fcs_port,
							    bsg_fcpt->dpwwn);
		अगर (fcs_rport == शून्य) अणु
			bsg_fcpt->status = BFA_STATUS_UNKNOWN_RWWN;
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);
			जाओ out_मुक्त_mem;
		पूर्ण

		drv_fcxp->bfa_rport = fcs_rport->bfa_rport;

	पूर्ण अन्यथा अणु /* Unknown BSG msgcode; वापस -EINVAL */
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		जाओ out_मुक्त_mem;
	पूर्ण

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* allocate memory क्रम req / rsp buffers */
	req_kbuf = kzalloc(job->request_payload.payload_len, GFP_KERNEL);
	अगर (!req_kbuf) अणु
		prपूर्णांकk(KERN_INFO "bfa %s: fcpt request buffer alloc failed\n",
				bfad->pci_name);
		rc = -ENOMEM;
		जाओ out_मुक्त_mem;
	पूर्ण

	rsp_kbuf = kzalloc(job->reply_payload.payload_len, GFP_KERNEL);
	अगर (!rsp_kbuf) अणु
		prपूर्णांकk(KERN_INFO "bfa %s: fcpt response buffer alloc failed\n",
				bfad->pci_name);
		rc = -ENOMEM;
		जाओ out_मुक्त_mem;
	पूर्ण

	/* map req sg - copy the sg_list passed in to the linear buffer */
	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt, req_kbuf,
			  job->request_payload.payload_len);

	drv_fcxp->reqbuf_info = bfad_fcxp_map_sg(bfad, req_kbuf,
					job->request_payload.payload_len,
					&drv_fcxp->num_req_sgles);
	अगर (!drv_fcxp->reqbuf_info) अणु
		prपूर्णांकk(KERN_INFO "bfa %s: fcpt request fcxp_map_sg failed\n",
				bfad->pci_name);
		rc = -ENOMEM;
		जाओ out_मुक्त_mem;
	पूर्ण

	drv_fcxp->req_sge = (काष्ठा bfa_sge_s *)
			    (((uपूर्णांक8_t *)drv_fcxp->reqbuf_info) +
			    (माप(काष्ठा bfad_buf_info) *
					drv_fcxp->num_req_sgles));

	/* map rsp sg */
	drv_fcxp->rspbuf_info = bfad_fcxp_map_sg(bfad, rsp_kbuf,
					job->reply_payload.payload_len,
					&drv_fcxp->num_rsp_sgles);
	अगर (!drv_fcxp->rspbuf_info) अणु
		prपूर्णांकk(KERN_INFO "bfa %s: fcpt response fcxp_map_sg failed\n",
				bfad->pci_name);
		rc = -ENOMEM;
		जाओ out_मुक्त_mem;
	पूर्ण

	rsp_buf_info = (काष्ठा bfad_buf_info *)drv_fcxp->rspbuf_info;
	drv_fcxp->rsp_sge = (काष्ठा bfa_sge_s  *)
			    (((uपूर्णांक8_t *)drv_fcxp->rspbuf_info) +
			    (माप(काष्ठा bfad_buf_info) *
					drv_fcxp->num_rsp_sgles));

	/* fcxp send */
	init_completion(&drv_fcxp->comp);
	rc = bfad_fcxp_bsg_send(job, drv_fcxp, bsg_fcpt);
	अगर (rc == BFA_STATUS_OK) अणु
		रुको_क्रम_completion(&drv_fcxp->comp);
		bsg_fcpt->status = drv_fcxp->req_status;
	पूर्ण अन्यथा अणु
		bsg_fcpt->status = rc;
		जाओ out_मुक्त_mem;
	पूर्ण

	/* fill the job->reply data */
	अगर (drv_fcxp->req_status == BFA_STATUS_OK) अणु
		job->reply_len = drv_fcxp->rsp_len;
		bsg_reply->reply_payload_rcv_len = drv_fcxp->rsp_len;
		bsg_reply->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	पूर्ण अन्यथा अणु
		bsg_reply->reply_payload_rcv_len =
					माप(काष्ठा fc_bsg_ctels_reply);
		job->reply_len = माप(uपूर्णांक32_t);
		bsg_reply->reply_data.ctels_reply.status =
						FC_CTELS_STATUS_REJECT;
	पूर्ण

	/* Copy the response data to the reply_payload sg list */
	sg_copy_from_buffer(job->reply_payload.sg_list,
			    job->reply_payload.sg_cnt,
			    (uपूर्णांक8_t *)rsp_buf_info->virt,
			    job->reply_payload.payload_len);

out_मुक्त_mem:
	bfad_fcxp_मुक्त_mem(bfad, drv_fcxp->rspbuf_info,
			   drv_fcxp->num_rsp_sgles);
	bfad_fcxp_मुक्त_mem(bfad, drv_fcxp->reqbuf_info,
			   drv_fcxp->num_req_sgles);
	kमुक्त(req_kbuf);
	kमुक्त(rsp_kbuf);

	/* Need a copy to user op */
	अगर (copy_to_user((व्योम *)(अचिन्हित दीर्घ)bsg_data->payload,
			(व्योम *)bsg_fcpt, bsg_data->payload_len))
		rc = -EIO;

	kमुक्त(bsg_fcpt);
	kमुक्त(drv_fcxp);
out:
	bsg_reply->result = rc;

	अगर (rc == BFA_STATUS_OK)
		bsg_job_करोne(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);

	वापस rc;
पूर्ण

पूर्णांक
bfad_im_bsg_request(काष्ठा bsg_job *job)
अणु
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	uपूर्णांक32_t rc = BFA_STATUS_OK;

	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_HST_VENDOR:
		/* Process BSG HST Venकरोr requests */
		rc = bfad_im_bsg_venकरोr_request(job);
		अवरोध;
	हाल FC_BSG_HST_ELS_NOLOGIN:
	हाल FC_BSG_RPT_ELS:
	हाल FC_BSG_HST_CT:
	हाल FC_BSG_RPT_CT:
		/* Process BSG ELS/CT commands */
		rc = bfad_im_bsg_els_ct_request(job);
		अवरोध;
	शेष:
		bsg_reply->result = rc = -EINVAL;
		bsg_reply->reply_payload_rcv_len = 0;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक
bfad_im_bsg_समयout(काष्ठा bsg_job *job)
अणु
	/* Don't complete the BSG job request - वापस -EAGAIN
	 * to reset bsg job समयout : क्रम ELS/CT pass thru we
	 * alपढ़ोy have समयr to track the request.
	 */
	वापस -EAGAIN;
पूर्ण
