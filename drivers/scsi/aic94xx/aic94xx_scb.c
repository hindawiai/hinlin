<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver SCB management.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>

#समावेश "aic94xx.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_hwi.h"
#समावेश "aic94xx_seq.h"

#समावेश "aic94xx_dump.h"

/* ---------- EMPTY SCB ---------- */

#घोषणा DL_PHY_MASK      7
#घोषणा BYTES_DMAED      0
#घोषणा PRIMITIVE_RECVD  0x08
#घोषणा PHY_EVENT        0x10
#घोषणा LINK_RESET_ERROR 0x18
#घोषणा TIMER_EVENT      0x20
#घोषणा REQ_TASK_ABORT   0xF0
#घोषणा REQ_DEVICE_RESET 0xF1
#घोषणा SIGNAL_NCQ_ERROR 0xF2
#घोषणा CLEAR_NCQ_ERROR  0xF3

#घोषणा PHY_EVENTS_STATUS (CURRENT_LOSS_OF_SIGNAL | CURRENT_OOB_DONE   \
			   | CURRENT_SPINUP_HOLD | CURRENT_GTO_TIMEOUT \
			   | CURRENT_OOB_ERROR)

अटल व्योम get_lrate_mode(काष्ठा asd_phy *phy, u8 oob_mode)
अणु
	काष्ठा sas_phy *sas_phy = phy->sas_phy.phy;

	चयन (oob_mode & 7) अणु
	हाल PHY_SPEED_60:
		/* FIXME: sas transport class करोesn't have this */
		phy->sas_phy.linkrate = SAS_LINK_RATE_6_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_6_0_GBPS;
		अवरोध;
	हाल PHY_SPEED_30:
		phy->sas_phy.linkrate = SAS_LINK_RATE_3_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	हाल PHY_SPEED_15:
		phy->sas_phy.linkrate = SAS_LINK_RATE_1_5_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	पूर्ण
	sas_phy->negotiated_linkrate = phy->sas_phy.linkrate;
	sas_phy->maximum_linkrate_hw = SAS_LINK_RATE_3_0_GBPS;
	sas_phy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
	sas_phy->maximum_linkrate = phy->phy_desc->max_sas_lrate;
	sas_phy->minimum_linkrate = phy->phy_desc->min_sas_lrate;

	अगर (oob_mode & SAS_MODE)
		phy->sas_phy.oob_mode = SAS_OOB_MODE;
	अन्यथा अगर (oob_mode & SATA_MODE)
		phy->sas_phy.oob_mode = SATA_OOB_MODE;
पूर्ण

अटल व्योम asd_phy_event_tasklet(काष्ठा asd_ascb *ascb,
					 काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	पूर्णांक phy_id = dl->status_block[0] & DL_PHY_MASK;
	काष्ठा asd_phy *phy = &asd_ha->phys[phy_id];

	u8 oob_status = dl->status_block[1] & PHY_EVENTS_STATUS;
	u8 oob_mode   = dl->status_block[2];

	चयन (oob_status) अणु
	हाल CURRENT_LOSS_OF_SIGNAL:
		/* directly attached device was हटाओd */
		ASD_DPRINTK("phy%d: device unplugged\n", phy_id);
		asd_turn_led(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_LOSS_OF_SIGNAL,
				     GFP_ATOMIC);
		अवरोध;
	हाल CURRENT_OOB_DONE:
		/* hot plugged device */
		asd_turn_led(asd_ha, phy_id, 1);
		get_lrate_mode(phy, oob_mode);
		ASD_DPRINTK("phy%d device plugged: lrate:0x%x, proto:0x%x\n",
			    phy_id, phy->sas_phy.linkrate, phy->sas_phy.iproto);
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
		अवरोध;
	हाल CURRENT_SPINUP_HOLD:
		/* hot plug SATA, no COMWAKE sent */
		asd_turn_led(asd_ha, phy_id, 1);
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_SPINUP_HOLD,
				     GFP_ATOMIC);
		अवरोध;
	हाल CURRENT_GTO_TIMEOUT:
	हाल CURRENT_OOB_ERROR:
		ASD_DPRINTK("phy%d error while OOB: oob status:0x%x\n", phy_id,
			    dl->status_block[1]);
		asd_turn_led(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_notअगरy_phy_event(&phy->sas_phy, PHYE_OOB_ERROR, GFP_ATOMIC);
		अवरोध;
	पूर्ण
पूर्ण

/* If phys are enabled sparsely, this will करो the right thing. */
अटल अचिन्हित ord_phy(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_phy *phy)
अणु
	u8 enabled_mask = asd_ha->hw_prof.enabled_phys;
	पूर्णांक i, k = 0;

	क्रम_each_phy(enabled_mask, enabled_mask, i) अणु
		अगर (&asd_ha->phys[i] == phy)
			वापस k;
		k++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * asd_get_attached_sas_addr -- extract/generate attached SAS address
 * @phy: poपूर्णांकer to asd_phy
 * @sas_addr: poपूर्णांकer to buffer where the SAS address is to be written
 *
 * This function extracts the SAS address from an IDENTIFY frame
 * received.  If OOB is SATA, then a SAS address is generated from the
 * HA tables.
 *
 * LOCKING: the frame_rcvd_lock needs to be held since this parses the frame
 * buffer.
 */
अटल व्योम asd_get_attached_sas_addr(काष्ठा asd_phy *phy, u8 *sas_addr)
अणु
	अगर (phy->sas_phy.frame_rcvd[0] == 0x34
	    && phy->sas_phy.oob_mode == SATA_OOB_MODE) अणु
		काष्ठा asd_ha_काष्ठा *asd_ha = phy->sas_phy.ha->lldd_ha;
		/* FIS device-to-host */
		u64 addr = be64_to_cpu(*(__be64 *)phy->phy_desc->sas_addr);

		addr += asd_ha->hw_prof.sata_name_base + ord_phy(asd_ha, phy);
		*(__be64 *)sas_addr = cpu_to_be64(addr);
	पूर्ण अन्यथा अणु
		काष्ठा sas_identअगरy_frame *idframe =
			(व्योम *) phy->sas_phy.frame_rcvd;
		स_नकल(sas_addr, idframe->sas_addr, SAS_ADDR_SIZE);
	पूर्ण
पूर्ण

अटल व्योम asd_क्रमm_port(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_phy *phy)
अणु
	पूर्णांक i;
	काष्ठा asd_port *मुक्त_port = शून्य;
	काष्ठा asd_port *port;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->asd_ports_lock, flags);
	अगर (!phy->asd_port) अणु
		क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
			port = &asd_ha->asd_ports[i];

			/* Check क्रम wide port */
			अगर (port->num_phys > 0 &&
			    स_भेद(port->sas_addr, sas_phy->sas_addr,
				   SAS_ADDR_SIZE) == 0 &&
			    स_भेद(port->attached_sas_addr,
				   sas_phy->attached_sas_addr,
				   SAS_ADDR_SIZE) == 0) अणु
				अवरोध;
			पूर्ण

			/* Find a मुक्त port */
			अगर (port->num_phys == 0 && मुक्त_port == शून्य) अणु
				मुक्त_port = port;
			पूर्ण
		पूर्ण

		/* Use a मुक्त port अगर this करोesn't क्रमm a wide port */
		अगर (i >= ASD_MAX_PHYS) अणु
			port = मुक्त_port;
			BUG_ON(!port);
			स_नकल(port->sas_addr, sas_phy->sas_addr,
			       SAS_ADDR_SIZE);
			स_नकल(port->attached_sas_addr,
			       sas_phy->attached_sas_addr,
			       SAS_ADDR_SIZE);
		पूर्ण
		port->num_phys++;
		port->phy_mask |= (1U << sas_phy->id);
		phy->asd_port = port;
	पूर्ण
	ASD_DPRINTK("%s: updating phy_mask 0x%x for phy%d\n",
		    __func__, phy->asd_port->phy_mask, sas_phy->id);
	asd_update_port_links(asd_ha, phy);
	spin_unlock_irqrestore(&asd_ha->asd_ports_lock, flags);
पूर्ण

अटल व्योम asd_deक्रमm_port(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_phy *phy)
अणु
	काष्ठा asd_port *port = phy->asd_port;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->asd_ports_lock, flags);
	अगर (port) अणु
		port->num_phys--;
		port->phy_mask &= ~(1U << sas_phy->id);
		phy->asd_port = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&asd_ha->asd_ports_lock, flags);
पूर्ण

अटल व्योम asd_bytes_dmaed_tasklet(काष्ठा asd_ascb *ascb,
				    काष्ठा करोne_list_काष्ठा *dl,
				    पूर्णांक edb_id, पूर्णांक phy_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक edb_el = edb_id + ascb->edb_index;
	काष्ठा asd_dma_tok *edb = ascb->ha->seq.edb_arr[edb_el];
	काष्ठा asd_phy *phy = &ascb->ha->phys[phy_id];
	u16 size = ((dl->status_block[3] & 7) << 8) | dl->status_block[2];

	size = min(size, (u16) माप(phy->frame_rcvd));

	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	स_नकल(phy->sas_phy.frame_rcvd, edb->vaddr, size);
	phy->sas_phy.frame_rcvd_size = size;
	asd_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	asd_dump_frame_rcvd(phy, dl);
	asd_क्रमm_port(ascb->ha, phy);
	sas_notअगरy_port_event(&phy->sas_phy, PORTE_BYTES_DMAED, GFP_ATOMIC);
पूर्ण

अटल व्योम asd_link_reset_err_tasklet(काष्ठा asd_ascb *ascb,
				       काष्ठा करोne_list_काष्ठा *dl,
				       पूर्णांक phy_id)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा sas_ha_काष्ठा *sas_ha = &asd_ha->sas_ha;
	काष्ठा asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	काष्ठा asd_phy *phy = &asd_ha->phys[phy_id];
	u8 lr_error = dl->status_block[1];
	u8 retries_left = dl->status_block[2];

	चयन (lr_error) अणु
	हाल 0:
		ASD_DPRINTK("phy%d: Receive ID timer expired\n", phy_id);
		अवरोध;
	हाल 1:
		ASD_DPRINTK("phy%d: Loss of signal\n", phy_id);
		अवरोध;
	हाल 2:
		ASD_DPRINTK("phy%d: Loss of dword sync\n", phy_id);
		अवरोध;
	हाल 3:
		ASD_DPRINTK("phy%d: Receive FIS timeout\n", phy_id);
		अवरोध;
	शेष:
		ASD_DPRINTK("phy%d: unknown link reset error code: 0x%x\n",
			    phy_id, lr_error);
		अवरोध;
	पूर्ण

	asd_turn_led(asd_ha, phy_id, 0);
	sas_phy_disconnected(sas_phy);
	asd_deक्रमm_port(asd_ha, phy);
	sas_notअगरy_port_event(sas_phy, PORTE_LINK_RESET_ERR, GFP_ATOMIC);

	अगर (retries_left == 0) अणु
		पूर्णांक num = 1;
		काष्ठा asd_ascb *cp = asd_ascb_alloc_list(ascb->ha, &num,
							  GFP_ATOMIC);
		अगर (!cp) अणु
			asd_prपूर्णांकk("%s: out of memory\n", __func__);
			जाओ out;
		पूर्ण
		ASD_DPRINTK("phy%d: retries:0 performing link reset seq\n",
			    phy_id);
		asd_build_control_phy(cp, phy_id, ENABLE_PHY);
		अगर (asd_post_ascb_list(ascb->ha, cp, 1) != 0)
			asd_ascb_मुक्त(cp);
	पूर्ण
out:
	;
पूर्ण

अटल व्योम asd_primitive_rcvd_tasklet(काष्ठा asd_ascb *ascb,
				       काष्ठा करोne_list_काष्ठा *dl,
				       पूर्णांक phy_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sas_ha_काष्ठा *sas_ha = &ascb->ha->sas_ha;
	काष्ठा asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा asd_phy *phy = &asd_ha->phys[phy_id];
	u8  reg  = dl->status_block[1];
	u32 cont = dl->status_block[2] << ((reg & 3)*8);

	reg &= ~3;
	चयन (reg) अणु
	हाल LmPRMSTAT0BYTE0:
		चयन (cont) अणु
		हाल LmBROADCH:
		हाल LmBROADRVCH0:
		हाल LmBROADRVCH1:
		हाल LmBROADSES:
			ASD_DPRINTK("phy%d: BROADCAST change received:%d\n",
				    phy_id, cont);
			spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
			sas_phy->sas_prim = ffs(cont);
			spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
			sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
					      GFP_ATOMIC);
			अवरोध;

		हाल LmUNKNOWNP:
			ASD_DPRINTK("phy%d: unknown BREAK\n", phy_id);
			अवरोध;

		शेष:
			ASD_DPRINTK("phy%d: primitive reg:0x%x, cont:0x%04x\n",
				    phy_id, reg, cont);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल LmPRMSTAT1BYTE0:
		चयन (cont) अणु
		हाल LmHARDRST:
			ASD_DPRINTK("phy%d: HARD_RESET primitive rcvd\n",
				    phy_id);
			/* The sequencer disables all phys on that port.
			 * We have to re-enable the phys ourselves. */
			asd_deक्रमm_port(asd_ha, phy);
			sas_notअगरy_port_event(sas_phy, PORTE_HARD_RESET,
					      GFP_ATOMIC);
			अवरोध;

		शेष:
			ASD_DPRINTK("phy%d: primitive reg:0x%x, cont:0x%04x\n",
				    phy_id, reg, cont);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ASD_DPRINTK("unknown primitive register:0x%x\n",
			    dl->status_block[1]);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * asd_invalidate_edb -- invalidate an EDB and अगर necessary post the ESCB
 * @ascb: poपूर्णांकer to Empty SCB
 * @edb_id: index [0,6] to the empty data buffer which is to be invalidated
 *
 * After an EDB has been invalidated, अगर all EDBs in this ESCB have been
 * invalidated, the ESCB is posted back to the sequencer.
 * Context is tasklet/IRQ.
 */
व्योम asd_invalidate_edb(काष्ठा asd_ascb *ascb, पूर्णांक edb_id)
अणु
	काष्ठा asd_seq_data *seq = &ascb->ha->seq;
	काष्ठा empty_scb *escb = &ascb->scb->escb;
	काष्ठा sg_el     *eb   = &escb->eb[edb_id];
	काष्ठा asd_dma_tok *edb = seq->edb_arr[ascb->edb_index + edb_id];

	स_रखो(edb->vaddr, 0, ASD_EDB_SIZE);
	eb->flags |= ELEMENT_NOT_VALID;
	escb->num_valid--;

	अगर (escb->num_valid == 0) अणु
		पूर्णांक i;
		/* ASD_DPRINTK("reposting escb: vaddr: 0x%p, "
			    "dma_handle: 0x%08llx, next: 0x%08llx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddr,
			    (u64)ascb->dma_scb.dma_handle,
			    le64_to_cpu(ascb->scb->header.next_scb),
			    le16_to_cpu(ascb->scb->header.index),
			    ascb->scb->header.opcode);
		*/
		escb->num_valid = ASD_EDBS_PER_SCB;
		क्रम (i = 0; i < ASD_EDBS_PER_SCB; i++)
			escb->eb[i].flags = 0;
		अगर (!list_empty(&ascb->list))
			list_del_init(&ascb->list);
		i = asd_post_escb_list(ascb->ha, ascb, 1);
		अगर (i)
			asd_prपूर्णांकk("couldn't post escb, err:%d\n", i);
	पूर्ण
पूर्ण

अटल व्योम escb_tasklet_complete(काष्ठा asd_ascb *ascb,
				  काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा sas_ha_काष्ठा *sas_ha = &asd_ha->sas_ha;
	पूर्णांक edb = (dl->opcode & DL_PHY_MASK) - 1; /* [0xc1,0xc7] -> [0,6] */
	u8  sb_opcode = dl->status_block[0];
	पूर्णांक phy_id = sb_opcode & DL_PHY_MASK;
	काष्ठा asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	काष्ठा asd_phy *phy = &asd_ha->phys[phy_id];

	अगर (edb > 6 || edb < 0) अणु
		ASD_DPRINTK("edb is 0x%x! dl->opcode is 0x%x\n",
			    edb, dl->opcode);
		ASD_DPRINTK("sb_opcode : 0x%x, phy_id: 0x%x\n",
			    sb_opcode, phy_id);
		ASD_DPRINTK("escb: vaddr: 0x%p, "
			    "dma_handle: 0x%llx, next: 0x%llx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddr,
			    (अचिन्हित दीर्घ दीर्घ)ascb->dma_scb.dma_handle,
			    (अचिन्हित दीर्घ दीर्घ)
			    le64_to_cpu(ascb->scb->header.next_scb),
			    le16_to_cpu(ascb->scb->header.index),
			    ascb->scb->header.opcode);
	पूर्ण

	/* Catch these beक्रमe we mask off the sb_opcode bits */
	चयन (sb_opcode) अणु
	हाल REQ_TASK_ABORT: अणु
		काष्ठा asd_ascb *a, *b;
		u16 tc_पात;
		काष्ठा करोमुख्य_device *failed_dev = शून्य;

		ASD_DPRINTK("%s: REQ_TASK_ABORT, reason=0x%X\n",
			    __func__, dl->status_block[3]);

		/*
		 * Find the task that caused the पात and पात it first.
		 * The sequencer won't put anything on the करोne list until
		 * that happens.
		 */
		tc_पात = *((u16*)(&dl->status_block[1]));
		tc_पात = le16_to_cpu(tc_पात);

		list_क्रम_each_entry_safe(a, b, &asd_ha->seq.pend_q, list) अणु
			काष्ठा sas_task *task = a->uldd_task;

			अगर (a->tc_index != tc_पात)
				जारी;

			अगर (task) अणु
				failed_dev = task->dev;
				sas_task_पात(task);
			पूर्ण अन्यथा अणु
				ASD_DPRINTK("R_T_A for non TASK scb 0x%x\n",
					    a->scb->header.opcode);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (!failed_dev) अणु
			ASD_DPRINTK("%s: Can't find task (tc=%d) to abort!\n",
				    __func__, tc_पात);
			जाओ out;
		पूर्ण

		/*
		 * Now पात everything अन्यथा क्रम that device (hba?) so
		 * that the EH will wake up and करो something.
		 */
		list_क्रम_each_entry_safe(a, b, &asd_ha->seq.pend_q, list) अणु
			काष्ठा sas_task *task = a->uldd_task;

			अगर (task &&
			    task->dev == failed_dev &&
			    a->tc_index != tc_पात)
				sas_task_पात(task);
		पूर्ण

		जाओ out;
	पूर्ण
	हाल REQ_DEVICE_RESET: अणु
		काष्ठा asd_ascb *a;
		u16 conn_handle;
		अचिन्हित दीर्घ flags;
		काष्ठा sas_task *last_dev_task = शून्य;

		conn_handle = *((u16*)(&dl->status_block[1]));
		conn_handle = le16_to_cpu(conn_handle);

		ASD_DPRINTK("%s: REQ_DEVICE_RESET, reason=0x%X\n", __func__,
			    dl->status_block[3]);

		/* Find the last pending task क्रम the device... */
		list_क्रम_each_entry(a, &asd_ha->seq.pend_q, list) अणु
			u16 x;
			काष्ठा करोमुख्य_device *dev;
			काष्ठा sas_task *task = a->uldd_task;

			अगर (!task)
				जारी;
			dev = task->dev;

			x = (अचिन्हित दीर्घ)dev->lldd_dev;
			अगर (x == conn_handle)
				last_dev_task = task;
		पूर्ण

		अगर (!last_dev_task) अणु
			ASD_DPRINTK("%s: Device reset for idle device %d?\n",
				    __func__, conn_handle);
			जाओ out;
		पूर्ण

		/* ...and set the reset flag */
		spin_lock_irqsave(&last_dev_task->task_state_lock, flags);
		last_dev_task->task_state_flags |= SAS_TASK_NEED_DEV_RESET;
		spin_unlock_irqrestore(&last_dev_task->task_state_lock, flags);

		/* Kill all pending tasks क्रम the device */
		list_क्रम_each_entry(a, &asd_ha->seq.pend_q, list) अणु
			u16 x;
			काष्ठा करोमुख्य_device *dev;
			काष्ठा sas_task *task = a->uldd_task;

			अगर (!task)
				जारी;
			dev = task->dev;

			x = (अचिन्हित दीर्घ)dev->lldd_dev;
			अगर (x == conn_handle)
				sas_task_पात(task);
		पूर्ण

		जाओ out;
	पूर्ण
	हाल SIGNAL_NCQ_ERROR:
		ASD_DPRINTK("%s: SIGNAL_NCQ_ERROR\n", __func__);
		जाओ out;
	हाल CLEAR_NCQ_ERROR:
		ASD_DPRINTK("%s: CLEAR_NCQ_ERROR\n", __func__);
		जाओ out;
	पूर्ण

	sb_opcode &= ~DL_PHY_MASK;

	चयन (sb_opcode) अणु
	हाल BYTES_DMAED:
		ASD_DPRINTK("%s: phy%d: BYTES_DMAED\n", __func__, phy_id);
		asd_bytes_dmaed_tasklet(ascb, dl, edb, phy_id);
		अवरोध;
	हाल PRIMITIVE_RECVD:
		ASD_DPRINTK("%s: phy%d: PRIMITIVE_RECVD\n", __func__,
			    phy_id);
		asd_primitive_rcvd_tasklet(ascb, dl, phy_id);
		अवरोध;
	हाल PHY_EVENT:
		ASD_DPRINTK("%s: phy%d: PHY_EVENT\n", __func__, phy_id);
		asd_phy_event_tasklet(ascb, dl);
		अवरोध;
	हाल LINK_RESET_ERROR:
		ASD_DPRINTK("%s: phy%d: LINK_RESET_ERROR\n", __func__,
			    phy_id);
		asd_link_reset_err_tasklet(ascb, dl, phy_id);
		अवरोध;
	हाल TIMER_EVENT:
		ASD_DPRINTK("%s: phy%d: TIMER_EVENT, lost dw sync\n",
			    __func__, phy_id);
		asd_turn_led(asd_ha, phy_id, 0);
		/* the device is gone */
		sas_phy_disconnected(sas_phy);
		asd_deक्रमm_port(asd_ha, phy);
		sas_notअगरy_port_event(sas_phy, PORTE_TIMER_EVENT, GFP_ATOMIC);
		अवरोध;
	शेष:
		ASD_DPRINTK("%s: phy%d: unknown event:0x%x\n", __func__,
			    phy_id, sb_opcode);
		ASD_DPRINTK("edb is 0x%x! dl->opcode is 0x%x\n",
			    edb, dl->opcode);
		ASD_DPRINTK("sb_opcode : 0x%x, phy_id: 0x%x\n",
			    sb_opcode, phy_id);
		ASD_DPRINTK("escb: vaddr: 0x%p, "
			    "dma_handle: 0x%llx, next: 0x%llx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddr,
			    (अचिन्हित दीर्घ दीर्घ)ascb->dma_scb.dma_handle,
			    (अचिन्हित दीर्घ दीर्घ)
			    le64_to_cpu(ascb->scb->header.next_scb),
			    le16_to_cpu(ascb->scb->header.index),
			    ascb->scb->header.opcode);

		अवरोध;
	पूर्ण
out:
	asd_invalidate_edb(ascb, edb);
पूर्ण

पूर्णांक asd_init_post_escbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक i;

	क्रम (i = 0; i < seq->num_escbs; i++)
		seq->escb_arr[i]->tasklet_complete = escb_tasklet_complete;

	ASD_DPRINTK("posting %d escbs\n", i);
	वापस asd_post_escb_list(asd_ha, seq->escb_arr[0], seq->num_escbs);
पूर्ण

/* ---------- CONTROL PHY ---------- */

#घोषणा CONTROL_PHY_STATUS (CURRENT_DEVICE_PRESENT | CURRENT_OOB_DONE   \
			    | CURRENT_SPINUP_HOLD | CURRENT_GTO_TIMEOUT \
			    | CURRENT_OOB_ERROR)

/**
 * control_phy_tasklet_complete -- tasklet complete क्रम CONTROL PHY ascb
 * @ascb: poपूर्णांकer to an ascb
 * @dl: poपूर्णांकer to the करोne list entry
 *
 * This function completes a CONTROL PHY scb and मुक्तs the ascb.
 * A note on LEDs:
 *  - an LED blinks अगर there is IO though it,
 *  - अगर a device is connected to the LED, it is lit,
 *  - अगर no device is connected to the LED, is is dimmed (off).
 */
अटल व्योम control_phy_tasklet_complete(काष्ठा asd_ascb *ascb,
					 काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा scb *scb = ascb->scb;
	काष्ठा control_phy *control_phy = &scb->control_phy;
	u8 phy_id = control_phy->phy_id;
	काष्ठा asd_phy *phy = &ascb->ha->phys[phy_id];

	u8 status     = dl->status_block[0];
	u8 oob_status = dl->status_block[1];
	u8 oob_mode   = dl->status_block[2];
	/* u8 oob_संकेतs= dl->status_block[3]; */

	अगर (status != 0) अणु
		ASD_DPRINTK("%s: phy%d status block opcode:0x%x\n",
			    __func__, phy_id, status);
		जाओ out;
	पूर्ण

	चयन (control_phy->sub_func) अणु
	हाल DISABLE_PHY:
		asd_ha->hw_prof.enabled_phys &= ~(1 << phy_id);
		asd_turn_led(asd_ha, phy_id, 0);
		asd_control_led(asd_ha, phy_id, 0);
		ASD_DPRINTK("%s: disable phy%d\n", __func__, phy_id);
		अवरोध;

	हाल ENABLE_PHY:
		asd_control_led(asd_ha, phy_id, 1);
		अगर (oob_status & CURRENT_OOB_DONE) अणु
			asd_ha->hw_prof.enabled_phys |= (1 << phy_id);
			get_lrate_mode(phy, oob_mode);
			asd_turn_led(asd_ha, phy_id, 1);
			ASD_DPRINTK("%s: phy%d, lrate:0x%x, proto:0x%x\n",
				    __func__, phy_id,phy->sas_phy.linkrate,
				    phy->sas_phy.iproto);
		पूर्ण अन्यथा अगर (oob_status & CURRENT_SPINUP_HOLD) अणु
			asd_ha->hw_prof.enabled_phys |= (1 << phy_id);
			asd_turn_led(asd_ha, phy_id, 1);
			ASD_DPRINTK("%s: phy%d, spinup hold\n", __func__,
				    phy_id);
		पूर्ण अन्यथा अगर (oob_status & CURRENT_ERR_MASK) अणु
			asd_turn_led(asd_ha, phy_id, 0);
			ASD_DPRINTK("%s: phy%d: error: oob status:0x%02x\n",
				    __func__, phy_id, oob_status);
		पूर्ण अन्यथा अगर (oob_status & (CURRENT_HOT_PLUG_CNCT
					 | CURRENT_DEVICE_PRESENT))  अणु
			asd_ha->hw_prof.enabled_phys |= (1 << phy_id);
			asd_turn_led(asd_ha, phy_id, 1);
			ASD_DPRINTK("%s: phy%d: hot plug or device present\n",
				    __func__, phy_id);
		पूर्ण अन्यथा अणु
			asd_ha->hw_prof.enabled_phys |= (1 << phy_id);
			asd_turn_led(asd_ha, phy_id, 0);
			ASD_DPRINTK("%s: phy%d: no device present: "
				    "oob_status:0x%x\n",
				    __func__, phy_id, oob_status);
		पूर्ण
		अवरोध;
	हाल RELEASE_SPINUP_HOLD:
	हाल PHY_NO_OP:
	हाल EXECUTE_HARD_RESET:
		ASD_DPRINTK("%s: phy%d: sub_func:0x%x\n", __func__,
			    phy_id, control_phy->sub_func);
		/* XXX finish */
		अवरोध;
	शेष:
		ASD_DPRINTK("%s: phy%d: sub_func:0x%x?\n", __func__,
			    phy_id, control_phy->sub_func);
		अवरोध;
	पूर्ण
out:
	asd_ascb_मुक्त(ascb);
पूर्ण

अटल व्योम set_speed_mask(u8 *speed_mask, काष्ठा asd_phy_desc *pd)
अणु
	/* disable all speeds, then enable शेषs */
	*speed_mask = SAS_SPEED_60_DIS | SAS_SPEED_30_DIS | SAS_SPEED_15_DIS
		| SATA_SPEED_30_DIS | SATA_SPEED_15_DIS;

	चयन (pd->max_sas_lrate) अणु
	हाल SAS_LINK_RATE_6_0_GBPS:
		*speed_mask &= ~SAS_SPEED_60_DIS;
		fallthrough;
	शेष:
	हाल SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SAS_SPEED_30_DIS;
		fallthrough;
	हाल SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SAS_SPEED_15_DIS;
	पूर्ण

	चयन (pd->min_sas_lrate) अणु
	हाल SAS_LINK_RATE_6_0_GBPS:
		*speed_mask |= SAS_SPEED_30_DIS;
		fallthrough;
	हाल SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SAS_SPEED_15_DIS;
		fallthrough;
	शेष:
	हाल SAS_LINK_RATE_1_5_GBPS:
		/* nothing to करो */
		;
	पूर्ण

	चयन (pd->max_sata_lrate) अणु
	हाल SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SATA_SPEED_30_DIS;
		fallthrough;
	शेष:
	हाल SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SATA_SPEED_15_DIS;
	पूर्ण

	चयन (pd->min_sata_lrate) अणु
	हाल SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SATA_SPEED_15_DIS;
		fallthrough;
	शेष:
	हाल SAS_LINK_RATE_1_5_GBPS:
		/* nothing to करो */
		;
	पूर्ण
पूर्ण

/**
 * asd_build_control_phy -- build a CONTROL PHY SCB
 * @ascb: poपूर्णांकer to an ascb
 * @phy_id: phy id to control, पूर्णांकeger
 * @subfunc: subfunction, what to actually to करो the phy
 *
 * This function builds a CONTROL PHY scb.  No allocation of any kind
 * is perक्रमmed. @ascb is allocated with the list function.
 * The caller can override the ascb->tasklet_complete to poपूर्णांक
 * to its own callback function.  It must call asd_ascb_मुक्त()
 * at its tasklet complete function.
 * See the शेष implementation.
 */
व्योम asd_build_control_phy(काष्ठा asd_ascb *ascb, पूर्णांक phy_id, u8 subfunc)
अणु
	काष्ठा asd_phy *phy = &ascb->ha->phys[phy_id];
	काष्ठा scb *scb = ascb->scb;
	काष्ठा control_phy *control_phy = &scb->control_phy;

	scb->header.opcode = CONTROL_PHY;
	control_phy->phy_id = (u8) phy_id;
	control_phy->sub_func = subfunc;

	चयन (subfunc) अणु
	हाल EXECUTE_HARD_RESET:  /* 0x81 */
	हाल ENABLE_PHY:          /* 0x01 */
		/* decide hot plug delay */
		control_phy->hot_plug_delay = HOTPLUG_DELAY_TIMEOUT;

		/* decide speed mask */
		set_speed_mask(&control_phy->speed_mask, phy->phy_desc);

		/* initiator port settings are in the hi nibble */
		अगर (phy->sas_phy.role == PHY_ROLE_INITIATOR)
			control_phy->port_type = SAS_PROTOCOL_ALL << 4;
		अन्यथा अगर (phy->sas_phy.role == PHY_ROLE_TARGET)
			control_phy->port_type = SAS_PROTOCOL_ALL;
		अन्यथा
			control_phy->port_type =
				(SAS_PROTOCOL_ALL << 4) | SAS_PROTOCOL_ALL;

		/* link reset retries, this should be nominal */
		control_phy->link_reset_retries = 10;
		fallthrough;

	हाल RELEASE_SPINUP_HOLD: /* 0x02 */
		/* decide the func_mask */
		control_phy->func_mask = FUNCTION_MASK_DEFAULT;
		अगर (phy->phy_desc->flags & ASD_SATA_SPINUP_HOLD)
			control_phy->func_mask &= ~SPINUP_HOLD_DIS;
		अन्यथा
			control_phy->func_mask |= SPINUP_HOLD_DIS;
	पूर्ण

	control_phy->conn_handle = cpu_to_le16(0xFFFF);

	ascb->tasklet_complete = control_phy_tasklet_complete;
पूर्ण

/* ---------- INITIATE LINK ADM TASK ---------- */

#अगर 0

अटल व्योम link_adm_tasklet_complete(काष्ठा asd_ascb *ascb,
				      काष्ठा करोne_list_काष्ठा *dl)
अणु
	u8 opcode = dl->opcode;
	काष्ठा initiate_link_adm *link_adm = &ascb->scb->link_adm;
	u8 phy_id = link_adm->phy_id;

	अगर (opcode != TC_NO_ERROR) अणु
		asd_prपूर्णांकk("phy%d: link adm task 0x%x completed with error "
			   "0x%x\n", phy_id, link_adm->sub_func, opcode);
	पूर्ण
	ASD_DPRINTK("phy%d: link adm task 0x%x: 0x%x\n",
		    phy_id, link_adm->sub_func, opcode);

	asd_ascb_मुक्त(ascb);
पूर्ण

व्योम asd_build_initiate_link_adm_task(काष्ठा asd_ascb *ascb, पूर्णांक phy_id,
				      u8 subfunc)
अणु
	काष्ठा scb *scb = ascb->scb;
	काष्ठा initiate_link_adm *link_adm = &scb->link_adm;

	scb->header.opcode = INITIATE_LINK_ADM_TASK;

	link_adm->phy_id = phy_id;
	link_adm->sub_func = subfunc;
	link_adm->conn_handle = cpu_to_le16(0xFFFF);

	ascb->tasklet_complete = link_adm_tasklet_complete;
पूर्ण

#पूर्ण_अगर  /*  0  */

/* ---------- SCB समयr ---------- */

/**
 * asd_ascb_समयकरोut -- called when a pending SCB's समयr has expired
 * @t: Timer context used to fetch the SCB
 *
 * This is the शेष समयout function which करोes the most necessary.
 * Upper layers can implement their own समयout function, say to मुक्त
 * resources they have with this SCB, and then call this one at the
 * end of their समयout function.  To करो this, one should initialize
 * the ascb->समयr.अणुfunction, expiresपूर्ण prior to calling the post
 * function. The समयr is started by the post function.
 */
व्योम asd_ascb_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा asd_ascb *ascb = from_समयr(ascb, t, समयr);
	काष्ठा asd_seq_data *seq = &ascb->ha->seq;
	अचिन्हित दीर्घ flags;

	ASD_DPRINTK("scb:0x%x timed out\n", ascb->scb->header.opcode);

	spin_lock_irqsave(&seq->pend_q_lock, flags);
	seq->pending--;
	list_del_init(&ascb->list);
	spin_unlock_irqrestore(&seq->pend_q_lock, flags);

	asd_ascb_मुक्त(ascb);
पूर्ण

/* ---------- CONTROL PHY ---------- */

/* Given the spec value, वापस a driver value. */
अटल स्थिर पूर्णांक phy_func_table[] = अणु
	[PHY_FUNC_NOP]        = PHY_NO_OP,
	[PHY_FUNC_LINK_RESET] = ENABLE_PHY,
	[PHY_FUNC_HARD_RESET] = EXECUTE_HARD_RESET,
	[PHY_FUNC_DISABLE]    = DISABLE_PHY,
	[PHY_FUNC_RELEASE_SPINUP_HOLD] = RELEASE_SPINUP_HOLD,
पूर्ण;

पूर्णांक asd_control_phy(काष्ठा asd_sas_phy *phy, क्रमागत phy_func func, व्योम *arg)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = phy->ha->lldd_ha;
	काष्ठा asd_phy_desc *pd = asd_ha->phys[phy->id].phy_desc;
	काष्ठा asd_ascb *ascb;
	काष्ठा sas_phy_linkrates *rates;
	पूर्णांक res = 1;

	चयन (func) अणु
	हाल PHY_FUNC_CLEAR_ERROR_LOG:
	हाल PHY_FUNC_GET_EVENTS:
		वापस -ENOSYS;
	हाल PHY_FUNC_SET_LINK_RATE:
		rates = arg;
		अगर (rates->minimum_linkrate) अणु
			pd->min_sas_lrate = rates->minimum_linkrate;
			pd->min_sata_lrate = rates->minimum_linkrate;
		पूर्ण
		अगर (rates->maximum_linkrate) अणु
			pd->max_sas_lrate = rates->maximum_linkrate;
			pd->max_sata_lrate = rates->maximum_linkrate;
		पूर्ण
		func = PHY_FUNC_LINK_RESET;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ascb = asd_ascb_alloc_list(asd_ha, &res, GFP_KERNEL);
	अगर (!ascb)
		वापस -ENOMEM;

	asd_build_control_phy(ascb, phy->id, phy_func_table[func]);
	res = asd_post_ascb_list(asd_ha, ascb , 1);
	अगर (res)
		asd_ascb_मुक्त(ascb);

	वापस res;
पूर्ण
