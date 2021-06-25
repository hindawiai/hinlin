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

/*
 *  bfa_attr.c Linux driver configuration पूर्णांकerface module.
 */

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"

/*
 * FC transport ढाँचा entry, get SCSI target port ID.
 */
अटल व्योम
bfad_im_get_starget_port_id(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा bfad_im_port_s *im_port;
	काष्ठा bfad_s         *bfad;
	काष्ठा bfad_itnim_s   *itnim = शून्य;
	u32        fc_id = -1;
	अचिन्हित दीर्घ   flags;

	shost = dev_to_shost(starget->dev.parent);
	im_port = (काष्ठा bfad_im_port_s *) shost->hostdata[0];
	bfad = im_port->bfad;
	spin_lock_irqsave(&bfad->bfad_lock, flags);

	itnim = bfad_get_itnim(im_port, starget->id);
	अगर (itnim)
		fc_id = bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim);

	fc_starget_port_id(starget) = fc_id;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI target nwwn.
 */
अटल व्योम
bfad_im_get_starget_node_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा bfad_im_port_s *im_port;
	काष्ठा bfad_s         *bfad;
	काष्ठा bfad_itnim_s   *itnim = शून्य;
	u64             node_name = 0;
	अचिन्हित दीर्घ   flags;

	shost = dev_to_shost(starget->dev.parent);
	im_port = (काष्ठा bfad_im_port_s *) shost->hostdata[0];
	bfad = im_port->bfad;
	spin_lock_irqsave(&bfad->bfad_lock, flags);

	itnim = bfad_get_itnim(im_port, starget->id);
	अगर (itnim)
		node_name = bfa_fcs_itnim_get_nwwn(&itnim->fcs_itnim);

	fc_starget_node_name(starget) = cpu_to_be64(node_name);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI target pwwn.
 */
अटल व्योम
bfad_im_get_starget_port_name(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा bfad_im_port_s *im_port;
	काष्ठा bfad_s         *bfad;
	काष्ठा bfad_itnim_s   *itnim = शून्य;
	u64             port_name = 0;
	अचिन्हित दीर्घ   flags;

	shost = dev_to_shost(starget->dev.parent);
	im_port = (काष्ठा bfad_im_port_s *) shost->hostdata[0];
	bfad = im_port->bfad;
	spin_lock_irqsave(&bfad->bfad_lock, flags);

	itnim = bfad_get_itnim(im_port, starget->id);
	अगर (itnim)
		port_name = bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim);

	fc_starget_port_name(starget) = cpu_to_be64(port_name);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host port ID.
 */
अटल व्योम
bfad_im_get_host_port_id(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_port_s    *port = im_port->port;

	fc_host_port_id(shost) =
			bfa_hton3b(bfa_fcs_lport_get_fcid(port->fcs_port));
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host port type.
 */
अटल व्योम
bfad_im_get_host_port_type(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfa_lport_attr_s port_attr;

	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);

	चयन (port_attr.port_type) अणु
	हाल BFA_PORT_TYPE_NPORT:
		fc_host_port_type(shost) = FC_PORTTYPE_NPORT;
		अवरोध;
	हाल BFA_PORT_TYPE_NLPORT:
		fc_host_port_type(shost) = FC_PORTTYPE_NLPORT;
		अवरोध;
	हाल BFA_PORT_TYPE_P2P:
		fc_host_port_type(shost) = FC_PORTTYPE_PTP;
		अवरोध;
	हाल BFA_PORT_TYPE_LPORT:
		fc_host_port_type(shost) = FC_PORTTYPE_LPORT;
		अवरोध;
	शेष:
		fc_host_port_type(shost) = FC_PORTTYPE_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host port state.
 */
अटल व्योम
bfad_im_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfa_port_attr_s attr;

	bfa_fcport_get_attr(&bfad->bfa, &attr);

	चयन (attr.port_state) अणु
	हाल BFA_PORT_ST_LINKDOWN:
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
		अवरोध;
	हाल BFA_PORT_ST_LINKUP:
		fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
		अवरोध;
	हाल BFA_PORT_ST_DISABLED:
	हाल BFA_PORT_ST_STOPPED:
	हाल BFA_PORT_ST_IOCDOWN:
	हाल BFA_PORT_ST_IOCDIS:
		fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
		अवरोध;
	हाल BFA_PORT_ST_UNINIT:
	हाल BFA_PORT_ST_ENABLING_QWAIT:
	हाल BFA_PORT_ST_ENABLING:
	हाल BFA_PORT_ST_DISABLING_QWAIT:
	हाल BFA_PORT_ST_DISABLING:
	शेष:
		fc_host_port_state(shost) = FC_PORTSTATE_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host active fc4s.
 */
अटल व्योम
bfad_im_get_host_active_fc4s(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_port_s    *port = im_port->port;

	स_रखो(fc_host_active_fc4s(shost), 0,
	       माप(fc_host_active_fc4s(shost)));

	अगर (port->supported_fc4s & BFA_LPORT_ROLE_FCP_IM)
		fc_host_active_fc4s(shost)[2] = 1;

	fc_host_active_fc4s(shost)[7] = 1;
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host link speed.
 */
अटल व्योम
bfad_im_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfa_port_attr_s attr;

	bfa_fcport_get_attr(&bfad->bfa, &attr);
	चयन (attr.speed) अणु
	हाल BFA_PORT_SPEED_10GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल BFA_PORT_SPEED_16GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_16GBIT;
		अवरोध;
	हाल BFA_PORT_SPEED_8GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_8GBIT;
		अवरोध;
	हाल BFA_PORT_SPEED_4GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_4GBIT;
		अवरोध;
	हाल BFA_PORT_SPEED_2GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_2GBIT;
		अवरोध;
	हाल BFA_PORT_SPEED_1GBPS:
		fc_host_speed(shost) = FC_PORTSPEED_1GBIT;
		अवरोध;
	शेष:
		fc_host_speed(shost) = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * FC transport ढाँचा entry, get SCSI host port type.
 */
अटल व्योम
bfad_im_get_host_fabric_name(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_port_s    *port = im_port->port;
	wwn_t           fabric_nwwn = 0;

	fabric_nwwn = bfa_fcs_lport_get_fabric_name(port->fcs_port);

	fc_host_fabric_name(shost) = cpu_to_be64(fabric_nwwn);

पूर्ण

/*
 * FC transport ढाँचा entry, get BFAD statistics.
 */
अटल काष्ठा fc_host_statistics *
bfad_im_get_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfad_hal_comp fcomp;
	जोड़ bfa_port_stats_u *fcstats;
	काष्ठा fc_host_statistics *hstats;
	bfa_status_t    rc;
	अचिन्हित दीर्घ   flags;

	fcstats = kzalloc(माप(जोड़ bfa_port_stats_u), GFP_KERNEL);
	अगर (fcstats == शून्य)
		वापस शून्य;

	hstats = &bfad->link_stats;
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	स_रखो(hstats, 0, माप(काष्ठा fc_host_statistics));
	rc = bfa_port_get_stats(BFA_FCPORT(&bfad->bfa),
				fcstats, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (rc != BFA_STATUS_OK) अणु
		kमुक्त(fcstats);
		वापस शून्य;
	पूर्ण

	रुको_क्रम_completion(&fcomp.comp);

	/* Fill the fc_host_statistics काष्ठाure */
	hstats->seconds_since_last_reset = fcstats->fc.secs_reset;
	hstats->tx_frames = fcstats->fc.tx_frames;
	hstats->tx_words  = fcstats->fc.tx_words;
	hstats->rx_frames = fcstats->fc.rx_frames;
	hstats->rx_words  = fcstats->fc.rx_words;
	hstats->lip_count = fcstats->fc.lip_count;
	hstats->nos_count = fcstats->fc.nos_count;
	hstats->error_frames = fcstats->fc.error_frames;
	hstats->dumped_frames = fcstats->fc.dropped_frames;
	hstats->link_failure_count = fcstats->fc.link_failures;
	hstats->loss_of_sync_count = fcstats->fc.loss_of_syncs;
	hstats->loss_of_संकेत_count = fcstats->fc.loss_of_संकेतs;
	hstats->prim_seq_protocol_err_count = fcstats->fc.primseq_errs;
	hstats->invalid_crc_count = fcstats->fc.invalid_crcs;

	kमुक्त(fcstats);
	वापस hstats;
पूर्ण

/*
 * FC transport ढाँचा entry, reset BFAD statistics.
 */
अटल व्योम
bfad_im_reset_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ   flags;
	bfa_status_t    rc;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_port_clear_stats(BFA_FCPORT(&bfad->bfa), bfad_hcb_comp,
					&fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (rc != BFA_STATUS_OK)
		वापस;

	रुको_क्रम_completion(&fcomp.comp);

	वापस;
पूर्ण

/*
 * FC transport ढाँचा entry, set rport loss समयout.
 * Update dev_loss_पंचांगo based on the value pushed करोwn by the stack
 * In हाल it is lesser than path_tov of driver, set it to path_tov + 1
 * to ensure that the driver बार out beक्रमe the application
 */
अटल व्योम
bfad_im_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, u32 समयout)
अणु
	काष्ठा bfad_itnim_data_s *itnim_data = rport->dd_data;
	काष्ठा bfad_itnim_s   *itnim = itnim_data->itnim;
	काष्ठा bfad_s         *bfad = itnim->im->bfad;
	uपूर्णांक16_t path_tov = bfa_fcpim_path_tov_get(&bfad->bfa);

	rport->dev_loss_पंचांगo = समयout;
	अगर (समयout < path_tov)
		rport->dev_loss_पंचांगo = path_tov + 1;
पूर्ण

अटल पूर्णांक
bfad_im_vport_create(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	अक्षर *vname = fc_vport->symbolic_name;
	काष्ठा Scsi_Host *shost = fc_vport->shost;
	काष्ठा bfad_im_port_s *im_port =
		(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	काष्ठा bfa_lport_cfg_s port_cfg;
	काष्ठा bfad_vport_s *vp;
	पूर्णांक status = 0, rc;
	अचिन्हित दीर्घ flags;

	स_रखो(&port_cfg, 0, माप(port_cfg));
	u64_to_wwn(fc_vport->node_name, (u8 *)&port_cfg.nwwn);
	u64_to_wwn(fc_vport->port_name, (u8 *)&port_cfg.pwwn);
	अगर (म_माप(vname) > 0)
		म_नकल((अक्षर *)&port_cfg.sym_name, vname);
	port_cfg.roles = BFA_LPORT_ROLE_FCP_IM;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	list_क्रम_each_entry(vp, &bfad->pbc_vport_list, list_entry) अणु
		अगर (port_cfg.pwwn ==
				vp->fcs_vport.lport.port_cfg.pwwn) अणु
			port_cfg.preboot_vp =
				vp->fcs_vport.lport.port_cfg.preboot_vp;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	rc = bfad_vport_create(bfad, 0, &port_cfg, &fc_vport->dev);
	अगर (rc == BFA_STATUS_OK) अणु
		काष्ठा bfad_vport_s *vport;
		काष्ठा bfa_fcs_vport_s *fcs_vport;
		काष्ठा Scsi_Host *vshost;

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0,
					port_cfg.pwwn);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		अगर (fcs_vport == शून्य)
			वापस VPCERR_BAD_WWN;

		fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
		अगर (disable) अणु
			spin_lock_irqsave(&bfad->bfad_lock, flags);
			bfa_fcs_vport_stop(fcs_vport);
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);
			fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
		पूर्ण

		vport = fcs_vport->vport_drv;
		vshost = vport->drv_port.im_port->shost;
		fc_host_node_name(vshost) = wwn_to_u64((u8 *)&port_cfg.nwwn);
		fc_host_port_name(vshost) = wwn_to_u64((u8 *)&port_cfg.pwwn);
		fc_host_supported_classes(vshost) = FC_COS_CLASS3;

		स_रखो(fc_host_supported_fc4s(vshost), 0,
			माप(fc_host_supported_fc4s(vshost)));

		/* For FCP type 0x08 */
		अगर (supported_fc4s & BFA_LPORT_ROLE_FCP_IM)
			fc_host_supported_fc4s(vshost)[2] = 1;

		/* For fibre channel services type 0x20 */
		fc_host_supported_fc4s(vshost)[7] = 1;

		fc_host_supported_speeds(vshost) =
				bfad_im_supported_speeds(&bfad->bfa);
		fc_host_maxframe_size(vshost) =
				bfa_fcport_get_maxfrsize(&bfad->bfa);

		fc_vport->dd_data = vport;
		vport->drv_port.im_port->fc_vport = fc_vport;
	पूर्ण अन्यथा अगर (rc == BFA_STATUS_INVALID_WWN)
		वापस VPCERR_BAD_WWN;
	अन्यथा अगर (rc == BFA_STATUS_VPORT_EXISTS)
		वापस VPCERR_BAD_WWN;
	अन्यथा अगर (rc == BFA_STATUS_VPORT_MAX)
		वापस VPCERR_NO_FABRIC_SUPP;
	अन्यथा अगर (rc == BFA_STATUS_VPORT_WWN_BP)
		वापस VPCERR_BAD_WWN;
	अन्यथा
		वापस FC_VPORT_FAILED;

	वापस status;
पूर्ण

अटल पूर्णांक
bfad_im_issue_fc_host_lip(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	काष्ठा bfad_hal_comp fcomp;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t status;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	status = bfa_port_disable(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (status != BFA_STATUS_OK)
		वापस -EIO;

	रुको_क्रम_completion(&fcomp.comp);
	अगर (fcomp.status != BFA_STATUS_OK)
		वापस -EIO;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	status = bfa_port_enable(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	अगर (status != BFA_STATUS_OK)
		वापस -EIO;

	रुको_क्रम_completion(&fcomp.comp);
	अगर (fcomp.status != BFA_STATUS_OK)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_im_vport_delete(काष्ठा fc_vport *fc_vport)
अणु
	काष्ठा bfad_vport_s *vport = (काष्ठा bfad_vport_s *)fc_vport->dd_data;
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) vport->drv_port.im_port;
	काष्ठा bfad_s *bfad = im_port->bfad;
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	काष्ठा Scsi_Host *vshost;
	wwn_t   pwwn;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	काष्ठा completion fcomp;

	अगर (im_port->flags & BFAD_PORT_DELETE) अणु
		bfad_scsi_host_मुक्त(bfad, im_port);
		list_del(&vport->list_entry);
		kमुक्त(vport);
		वापस 0;
	पूर्ण

	vshost = vport->drv_port.im_port->shost;
	u64_to_wwn(fc_host_port_name(vshost), (u8 *)&pwwn);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0, pwwn);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (fcs_vport == शून्य)
		वापस VPCERR_BAD_WWN;

	vport->drv_port.flags |= BFAD_PORT_DELETE;

	vport->comp_del = &fcomp;
	init_completion(vport->comp_del);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_fcs_vport_delete(&vport->fcs_vport);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (rc == BFA_STATUS_PBC) अणु
		vport->drv_port.flags &= ~BFAD_PORT_DELETE;
		vport->comp_del = शून्य;
		वापस -1;
	पूर्ण

	रुको_क्रम_completion(vport->comp_del);

	bfad_scsi_host_मुक्त(bfad, im_port);
	list_del(&vport->list_entry);
	kमुक्त(vport);

	वापस 0;
पूर्ण

अटल पूर्णांक
bfad_im_vport_disable(काष्ठा fc_vport *fc_vport, bool disable)
अणु
	काष्ठा bfad_vport_s *vport;
	काष्ठा bfad_s *bfad;
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	काष्ठा Scsi_Host *vshost;
	wwn_t   pwwn;
	अचिन्हित दीर्घ flags;

	vport = (काष्ठा bfad_vport_s *)fc_vport->dd_data;
	bfad = vport->drv_port.bfad;
	vshost = vport->drv_port.im_port->shost;
	u64_to_wwn(fc_host_port_name(vshost), (u8 *)&pwwn);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0, pwwn);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (fcs_vport == शून्य)
		वापस VPCERR_BAD_WWN;

	अगर (disable) अणु
		bfa_fcs_vport_stop(fcs_vport);
		fc_vport_set_state(fc_vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा अणु
		bfa_fcs_vport_start(fcs_vport);
		fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
bfad_im_vport_set_symbolic_name(काष्ठा fc_vport *fc_vport)
अणु
	काष्ठा bfad_vport_s *vport = (काष्ठा bfad_vport_s *)fc_vport->dd_data;
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *)vport->drv_port.im_port;
	काष्ठा bfad_s *bfad = im_port->bfad;
	काष्ठा Scsi_Host *vshost = vport->drv_port.im_port->shost;
	अक्षर *sym_name = fc_vport->symbolic_name;
	काष्ठा bfa_fcs_vport_s *fcs_vport;
	wwn_t	pwwn;
	अचिन्हित दीर्घ flags;

	u64_to_wwn(fc_host_port_name(vshost), (u8 *)&pwwn);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0, pwwn);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (fcs_vport == शून्य)
		वापस;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (म_माप(sym_name) > 0)
		bfa_fcs_lport_set_symname(&fcs_vport->lport, sym_name);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

काष्ठा fc_function_ढाँचा bfad_im_fc_function_ढाँचा = अणु

	/* Target dynamic attributes */
	.get_starget_port_id = bfad_im_get_starget_port_id,
	.show_starget_port_id = 1,
	.get_starget_node_name = bfad_im_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = bfad_im_get_starget_port_name,
	.show_starget_port_name = 1,

	/* Host dynamic attribute */
	.get_host_port_id = bfad_im_get_host_port_id,
	.show_host_port_id = 1,

	/* Host fixed attributes */
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_supported_speeds = 1,
	.show_host_maxframe_size = 1,

	/* More host dynamic attributes */
	.show_host_port_type = 1,
	.get_host_port_type = bfad_im_get_host_port_type,
	.show_host_port_state = 1,
	.get_host_port_state = bfad_im_get_host_port_state,
	.show_host_active_fc4s = 1,
	.get_host_active_fc4s = bfad_im_get_host_active_fc4s,
	.show_host_speed = 1,
	.get_host_speed = bfad_im_get_host_speed,
	.show_host_fabric_name = 1,
	.get_host_fabric_name = bfad_im_get_host_fabric_name,

	.show_host_symbolic_name = 1,

	/* Statistics */
	.get_fc_host_stats = bfad_im_get_stats,
	.reset_fc_host_stats = bfad_im_reset_stats,

	/* Allocation length क्रम host specअगरic data */
	.dd_fcrport_size = माप(काष्ठा bfad_itnim_data_s *),

	/* Remote port fixed attributes */
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,
	.show_rport_dev_loss_पंचांगo = 1,
	.set_rport_dev_loss_पंचांगo = bfad_im_set_rport_loss_पंचांगo,
	.issue_fc_host_lip = bfad_im_issue_fc_host_lip,
	.vport_create = bfad_im_vport_create,
	.vport_delete = bfad_im_vport_delete,
	.vport_disable = bfad_im_vport_disable,
	.set_vport_symbolic_name = bfad_im_vport_set_symbolic_name,
	.bsg_request = bfad_im_bsg_request,
	.bsg_समयout = bfad_im_bsg_समयout,
पूर्ण;

काष्ठा fc_function_ढाँचा bfad_im_vport_fc_function_ढाँचा = अणु

	/* Target dynamic attributes */
	.get_starget_port_id = bfad_im_get_starget_port_id,
	.show_starget_port_id = 1,
	.get_starget_node_name = bfad_im_get_starget_node_name,
	.show_starget_node_name = 1,
	.get_starget_port_name = bfad_im_get_starget_port_name,
	.show_starget_port_name = 1,

	/* Host dynamic attribute */
	.get_host_port_id = bfad_im_get_host_port_id,
	.show_host_port_id = 1,

	/* Host fixed attributes */
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_supported_speeds = 1,
	.show_host_maxframe_size = 1,

	/* More host dynamic attributes */
	.show_host_port_type = 1,
	.get_host_port_type = bfad_im_get_host_port_type,
	.show_host_port_state = 1,
	.get_host_port_state = bfad_im_get_host_port_state,
	.show_host_active_fc4s = 1,
	.get_host_active_fc4s = bfad_im_get_host_active_fc4s,
	.show_host_speed = 1,
	.get_host_speed = bfad_im_get_host_speed,
	.show_host_fabric_name = 1,
	.get_host_fabric_name = bfad_im_get_host_fabric_name,

	.show_host_symbolic_name = 1,

	/* Statistics */
	.get_fc_host_stats = bfad_im_get_stats,
	.reset_fc_host_stats = bfad_im_reset_stats,

	/* Allocation length क्रम host specअगरic data */
	.dd_fcrport_size = माप(काष्ठा bfad_itnim_data_s *),

	/* Remote port fixed attributes */
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,
	.show_rport_dev_loss_पंचांगo = 1,
	.set_rport_dev_loss_पंचांगo = bfad_im_set_rport_loss_पंचांगo,
पूर्ण;

/*
 *  Scsi_Host_attrs SCSI host attributes
 */
अटल sमाप_प्रकार
bfad_im_serial_num_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर serial_num[BFA_ADAPTER_SERIAL_NUM_LEN];

	bfa_get_adapter_serial_num(&bfad->bfa, serial_num);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", serial_num);
पूर्ण

अटल sमाप_प्रकार
bfad_im_model_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर model[BFA_ADAPTER_MODEL_NAME_LEN];

	bfa_get_adapter_model(&bfad->bfa, model);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", model);
पूर्ण

अटल sमाप_प्रकार
bfad_im_model_desc_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर model[BFA_ADAPTER_MODEL_NAME_LEN];
	अक्षर model_descr[BFA_ADAPTER_MODEL_DESCR_LEN];
	पूर्णांक nports = 0;

	bfa_get_adapter_model(&bfad->bfa, model);
	nports = bfa_get_nports(&bfad->bfa);
	अगर (!म_भेद(model, "QLogic-425"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe dual port FC HBA");
	अन्यथा अगर (!म_भेद(model, "QLogic-825"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe dual port FC HBA");
	अन्यथा अगर (!म_भेद(model, "QLogic-42B"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe dual port FC HBA for HP");
	अन्यथा अगर (!म_भेद(model, "QLogic-82B"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe dual port FC HBA for HP");
	अन्यथा अगर (!म_भेद(model, "QLogic-1010"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps single port CNA");
	अन्यथा अगर (!म_भेद(model, "QLogic-1020"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps dual port CNA");
	अन्यथा अगर (!म_भेद(model, "QLogic-1007"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps CNA for IBM Blade Center");
	अन्यथा अगर (!म_भेद(model, "QLogic-415"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe single port FC HBA");
	अन्यथा अगर (!म_भेद(model, "QLogic-815"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe single port FC HBA");
	अन्यथा अगर (!म_भेद(model, "QLogic-41B"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 4Gbps PCIe single port FC HBA for HP");
	अन्यथा अगर (!म_भेद(model, "QLogic-81B"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps PCIe single port FC HBA for HP");
	अन्यथा अगर (!म_भेद(model, "QLogic-804"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 8Gbps FC HBA for HP Bladesystem C-class");
	अन्यथा अगर (!म_भेद(model, "QLogic-1741"))
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"QLogic BR-series 10Gbps CNA for Dell M-Series Blade Servers");
	अन्यथा अगर (म_माला(model, "QLogic-1860")) अणु
		अगर (nports == 1 && bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 10Gbps single port CNA");
		अन्यथा अगर (nports == 1 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe single port FC HBA");
		अन्यथा अगर (nports == 2 && bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 10Gbps dual port CNA");
		अन्यथा अगर (nports == 2 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe dual port FC HBA");
	पूर्ण अन्यथा अगर (!म_भेद(model, "QLogic-1867")) अणु
		अगर (nports == 1 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe single port FC HBA for IBM");
		अन्यथा अगर (nports == 2 && !bfa_ioc_is_cna(&bfad->bfa.ioc))
			snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
				"QLogic BR-series 16Gbps PCIe dual port FC HBA for IBM");
	पूर्ण अन्यथा
		snम_लिखो(model_descr, BFA_ADAPTER_MODEL_DESCR_LEN,
			"Invalid Model");

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", model_descr);
पूर्ण

अटल sमाप_प्रकार
bfad_im_node_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_port_s    *port = im_port->port;
	u64        nwwn;

	nwwn = bfa_fcs_lport_get_nwwn(port->fcs_port);
	वापस snम_लिखो(buf, PAGE_SIZE, "0x%llx\n", cpu_to_be64(nwwn));
पूर्ण

अटल sमाप_प्रकार
bfad_im_symbolic_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	काष्ठा bfa_lport_attr_s port_attr;
	अक्षर symname[BFA_SYMNAME_MAXLEN];

	bfa_fcs_lport_get_attr(&bfad->bfa_fcs.fabric.bport, &port_attr);
	strlcpy(symname, port_attr.port_cfg.sym_name.symname,
			BFA_SYMNAME_MAXLEN);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", symname);
पूर्ण

अटल sमाप_प्रकार
bfad_im_hw_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर hw_ver[BFA_VERSION_LEN];

	bfa_get_pci_chip_rev(&bfad->bfa, hw_ver);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", hw_ver);
पूर्ण

अटल sमाप_प्रकार
bfad_im_drv_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", BFAD_DRIVER_VERSION);
पूर्ण

अटल sमाप_प्रकार
bfad_im_optionrom_version_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर optrom_ver[BFA_VERSION_LEN];

	bfa_get_adapter_optrom_ver(&bfad->bfa, optrom_ver);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", optrom_ver);
पूर्ण

अटल sमाप_प्रकार
bfad_im_fw_version_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;
	अक्षर fw_ver[BFA_VERSION_LEN];

	bfa_get_adapter_fw_ver(&bfad->bfa, fw_ver);
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", fw_ver);
पूर्ण

अटल sमाप_प्रकार
bfad_im_num_of_ports_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n",
			bfa_get_nports(&bfad->bfa));
पूर्ण

अटल sमाप_प्रकार
bfad_im_drv_name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", BFAD_DRIVER_NAME);
पूर्ण

अटल sमाप_प्रकार
bfad_im_num_of_discovered_ports_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_port_s    *port = im_port->port;
	काष्ठा bfad_s         *bfad = im_port->bfad;
	पूर्णांक        nrports = 2048;
	काष्ठा bfa_rport_qualअगरier_s *rports = शून्य;
	अचिन्हित दीर्घ   flags;

	rports = kसुस्मृति(nrports, माप(काष्ठा bfa_rport_qualअगरier_s),
			 GFP_ATOMIC);
	अगर (rports == शून्य)
		वापस snम_लिखो(buf, PAGE_SIZE, "Failed\n");

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcs_lport_get_rport_quals(port->fcs_port, rports, &nrports);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	kमुक्त(rports);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", nrports);
पूर्ण

अटल          DEVICE_ATTR(serial_number, S_IRUGO,
				bfad_im_serial_num_show, शून्य);
अटल          DEVICE_ATTR(model, S_IRUGO, bfad_im_model_show, शून्य);
अटल          DEVICE_ATTR(model_description, S_IRUGO,
				bfad_im_model_desc_show, शून्य);
अटल          DEVICE_ATTR(node_name, S_IRUGO, bfad_im_node_name_show, शून्य);
अटल          DEVICE_ATTR(symbolic_name, S_IRUGO,
				bfad_im_symbolic_name_show, शून्य);
अटल          DEVICE_ATTR(hardware_version, S_IRUGO,
				bfad_im_hw_version_show, शून्य);
अटल          DEVICE_ATTR(driver_version, S_IRUGO,
				bfad_im_drv_version_show, शून्य);
अटल          DEVICE_ATTR(option_rom_version, S_IRUGO,
				bfad_im_optionrom_version_show, शून्य);
अटल          DEVICE_ATTR(firmware_version, S_IRUGO,
				bfad_im_fw_version_show, शून्य);
अटल          DEVICE_ATTR(number_of_ports, S_IRUGO,
				bfad_im_num_of_ports_show, शून्य);
अटल          DEVICE_ATTR(driver_name, S_IRUGO, bfad_im_drv_name_show, शून्य);
अटल          DEVICE_ATTR(number_of_discovered_ports, S_IRUGO,
				bfad_im_num_of_discovered_ports_show, शून्य);

काष्ठा device_attribute *bfad_im_host_attrs[] = अणु
	&dev_attr_serial_number,
	&dev_attr_model,
	&dev_attr_model_description,
	&dev_attr_node_name,
	&dev_attr_symbolic_name,
	&dev_attr_hardware_version,
	&dev_attr_driver_version,
	&dev_attr_option_rom_version,
	&dev_attr_firmware_version,
	&dev_attr_number_of_ports,
	&dev_attr_driver_name,
	&dev_attr_number_of_discovered_ports,
	शून्य,
पूर्ण;

काष्ठा device_attribute *bfad_im_vport_attrs[] = अणु
	&dev_attr_serial_number,
	&dev_attr_model,
	&dev_attr_model_description,
	&dev_attr_node_name,
	&dev_attr_symbolic_name,
	&dev_attr_hardware_version,
	&dev_attr_driver_version,
	&dev_attr_option_rom_version,
	&dev_attr_firmware_version,
	&dev_attr_number_of_ports,
	&dev_attr_driver_name,
	&dev_attr_number_of_discovered_ports,
	शून्य,
पूर्ण;


