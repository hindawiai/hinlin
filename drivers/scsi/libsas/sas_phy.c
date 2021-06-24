<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial Attached SCSI (SAS) Phy class
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश "sas_internal.h"
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश "../scsi_sas_internal.h"

/* ---------- Phy events ---------- */

अटल व्योम sas_phye_loss_of_संकेत(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	phy->error = 0;
	sas_deक्रमm_port(phy, 1);
पूर्ण

अटल व्योम sas_phye_oob_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	phy->error = 0;
पूर्ण

अटल व्योम sas_phye_oob_error(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा asd_sas_port *port = phy->port;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

	sas_deक्रमm_port(phy, 1);

	अगर (!port && phy->enabled && i->dft->lldd_control_phy) अणु
		phy->error++;
		चयन (phy->error) अणु
		हाल 1:
		हाल 2:
			i->dft->lldd_control_phy(phy, PHY_FUNC_HARD_RESET,
						 शून्य);
			अवरोध;
		हाल 3:
		शेष:
			phy->error = 0;
			phy->enabled = 0;
			i->dft->lldd_control_phy(phy, PHY_FUNC_DISABLE, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sas_phye_spinup_hold(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

	phy->error = 0;
	i->dft->lldd_control_phy(phy, PHY_FUNC_RELEASE_SPINUP_HOLD, शून्य);
पूर्ण

अटल व्योम sas_phye_resume_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;

	/* phew, lldd got the phy back in the nick of समय */
	अगर (!phy->suspended) अणु
		dev_info(&phy->phy->dev, "resume timeout cancelled\n");
		वापस;
	पूर्ण

	phy->error = 0;
	phy->suspended = 0;
	sas_deक्रमm_port(phy, 1);
पूर्ण


अटल व्योम sas_phye_shutकरोwn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = to_asd_sas_event(work);
	काष्ठा asd_sas_phy *phy = ev->phy;
	काष्ठा sas_ha_काष्ठा *sas_ha = phy->ha;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(sas_ha->core.shost->transportt);

	अगर (phy->enabled) अणु
		पूर्णांक ret;

		phy->error = 0;
		phy->enabled = 0;
		ret = i->dft->lldd_control_phy(phy, PHY_FUNC_DISABLE, शून्य);
		अगर (ret)
			pr_notice("lldd disable phy%d returned %d\n", phy->id,
				  ret);
	पूर्ण अन्यथा
		pr_notice("phy%d is not enabled, cannot shutdown\n", phy->id);
	phy->in_shutकरोwn = 0;
पूर्ण

/* ---------- Phy class registration ---------- */

पूर्णांक sas_रेजिस्टर_phys(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	पूर्णांक i;

	/* Now रेजिस्टर the phys. */
	क्रम (i = 0; i < sas_ha->num_phys; i++) अणु
		काष्ठा asd_sas_phy *phy = sas_ha->sas_phy[i];

		phy->error = 0;
		atomic_set(&phy->event_nr, 0);
		INIT_LIST_HEAD(&phy->port_phy_el);

		phy->port = शून्य;
		phy->ha = sas_ha;
		spin_lock_init(&phy->frame_rcvd_lock);
		spin_lock_init(&phy->sas_prim_lock);
		phy->frame_rcvd_size = 0;

		phy->phy = sas_phy_alloc(&sas_ha->core.shost->shost_gendev, i);
		अगर (!phy->phy)
			वापस -ENOMEM;

		phy->phy->identअगरy.initiator_port_protocols =
			phy->iproto;
		phy->phy->identअगरy.target_port_protocols = phy->tproto;
		phy->phy->identअगरy.sas_address = SAS_ADDR(sas_ha->sas_addr);
		phy->phy->identअगरy.phy_identअगरier = i;
		phy->phy->minimum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
		phy->phy->maximum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
		phy->phy->minimum_linkrate = SAS_LINK_RATE_UNKNOWN;
		phy->phy->maximum_linkrate = SAS_LINK_RATE_UNKNOWN;
		phy->phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;

		sas_phy_add(phy->phy);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर work_func_t sas_phy_event_fns[PHY_NUM_EVENTS] = अणु
	[PHYE_LOSS_OF_SIGNAL] = sas_phye_loss_of_संकेत,
	[PHYE_OOB_DONE] = sas_phye_oob_करोne,
	[PHYE_OOB_ERROR] = sas_phye_oob_error,
	[PHYE_SPINUP_HOLD] = sas_phye_spinup_hold,
	[PHYE_RESUME_TIMEOUT] = sas_phye_resume_समयout,
	[PHYE_SHUTDOWN] = sas_phye_shutकरोwn,
पूर्ण;
