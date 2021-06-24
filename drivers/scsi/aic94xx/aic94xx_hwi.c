<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver hardware पूर्णांकerface.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>

#समावेश "aic94xx.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_hwi.h"
#समावेश "aic94xx_seq.h"
#समावेश "aic94xx_dump.h"

u32 MBAR0_SWB_SIZE;

/* ---------- Initialization ---------- */

अटल पूर्णांक asd_get_user_sas_addr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	/* adapter came with a sas address */
	अगर (asd_ha->hw_prof.sas_addr[0])
		वापस 0;

	वापस sas_request_addr(asd_ha->sas_ha.core.shost,
				asd_ha->hw_prof.sas_addr);
पूर्ण

अटल व्योम asd_propagate_sas_addr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		अगर (asd_ha->hw_prof.phy_desc[i].sas_addr[0] == 0)
			जारी;
		/* Set a phy's address only अगर it has none.
		 */
		ASD_DPRINTK("setting phy%d addr to %llx\n", i,
			    SAS_ADDR(asd_ha->hw_prof.sas_addr));
		स_नकल(asd_ha->hw_prof.phy_desc[i].sas_addr,
		       asd_ha->hw_prof.sas_addr, SAS_ADDR_SIZE);
	पूर्ण
पूर्ण

/* ---------- PHY initialization ---------- */

अटल व्योम asd_init_phy_identअगरy(काष्ठा asd_phy *phy)
अणु
	phy->identअगरy_frame = phy->id_frm_tok->vaddr;

	स_रखो(phy->identअगरy_frame, 0, माप(*phy->identअगरy_frame));

	phy->identअगरy_frame->dev_type = SAS_END_DEVICE;
	अगर (phy->sas_phy.role & PHY_ROLE_INITIATOR)
		phy->identअगरy_frame->initiator_bits = phy->sas_phy.iproto;
	अगर (phy->sas_phy.role & PHY_ROLE_TARGET)
		phy->identअगरy_frame->target_bits = phy->sas_phy.tproto;
	स_नकल(phy->identअगरy_frame->sas_addr, phy->phy_desc->sas_addr,
	       SAS_ADDR_SIZE);
	phy->identअगरy_frame->phy_id = phy->sas_phy.id;
पूर्ण

अटल पूर्णांक asd_init_phy(काष्ठा asd_phy *phy)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = phy->sas_phy.ha->lldd_ha;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	sas_phy->enabled = 1;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;

	phy->id_frm_tok = asd_alloc_coherent(asd_ha,
					     माप(*phy->identअगरy_frame),
					     GFP_KERNEL);
	अगर (!phy->id_frm_tok) अणु
		asd_prपूर्णांकk("no mem for IDENTIFY for phy%d\n", sas_phy->id);
		वापस -ENOMEM;
	पूर्ण अन्यथा
		asd_init_phy_identअगरy(phy);

	स_रखो(phy->frame_rcvd, 0, माप(phy->frame_rcvd));

	वापस 0;
पूर्ण

अटल व्योम asd_init_ports(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	spin_lock_init(&asd_ha->asd_ports_lock);
	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		काष्ठा asd_port *asd_port = &asd_ha->asd_ports[i];

		स_रखो(asd_port->sas_addr, 0, SAS_ADDR_SIZE);
		स_रखो(asd_port->attached_sas_addr, 0, SAS_ADDR_SIZE);
		asd_port->phy_mask = 0;
		asd_port->num_phys = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक asd_init_phys(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u8 i;
	u8 phy_mask = asd_ha->hw_prof.enabled_phys;

	क्रम (i = 0; i < ASD_MAX_PHYS; i++) अणु
		काष्ठा asd_phy *phy = &asd_ha->phys[i];

		phy->phy_desc = &asd_ha->hw_prof.phy_desc[i];
		phy->asd_port = शून्य;

		phy->sas_phy.enabled = 0;
		phy->sas_phy.id = i;
		phy->sas_phy.sas_addr = &phy->phy_desc->sas_addr[0];
		phy->sas_phy.frame_rcvd = &phy->frame_rcvd[0];
		phy->sas_phy.ha = &asd_ha->sas_ha;
		phy->sas_phy.lldd_phy = phy;
	पूर्ण

	/* Now enable and initialize only the enabled phys. */
	क्रम_each_phy(phy_mask, phy_mask, i) अणु
		पूर्णांक err = asd_init_phy(&asd_ha->phys[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------- Sliding winकरोws ---------- */

अटल पूर्णांक asd_init_sw(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा pci_dev *pcidev = asd_ha->pcidev;
	पूर्णांक err;
	u32 v;

	/* Unlock MBARs */
	err = pci_पढ़ो_config_dword(pcidev, PCI_CONF_MBAR_KEY, &v);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't access conf. space of %s\n",
			   pci_name(pcidev));
		जाओ Err;
	पूर्ण
	अगर (v)
		err = pci_ग_लिखो_config_dword(pcidev, PCI_CONF_MBAR_KEY, v);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't write to MBAR_KEY of %s\n",
			   pci_name(pcidev));
		जाओ Err;
	पूर्ण

	/* Set sliding winकरोws A, B and C to poपूर्णांक to proper पूर्णांकernal
	 * memory regions.
	 */
	pci_ग_लिखो_config_dword(pcidev, PCI_CONF_MBAR0_SWA, REG_BASE_ADDR);
	pci_ग_लिखो_config_dword(pcidev, PCI_CONF_MBAR0_SWB,
			       REG_BASE_ADDR_CSEQCIO);
	pci_ग_लिखो_config_dword(pcidev, PCI_CONF_MBAR0_SWC, REG_BASE_ADDR_EXSI);
	asd_ha->io_handle[0].swa_base = REG_BASE_ADDR;
	asd_ha->io_handle[0].swb_base = REG_BASE_ADDR_CSEQCIO;
	asd_ha->io_handle[0].swc_base = REG_BASE_ADDR_EXSI;
	MBAR0_SWB_SIZE = asd_ha->io_handle[0].len - 0x80;
	अगर (!asd_ha->iospace) अणु
		/* MBAR1 will poपूर्णांक to OCM (On Chip Memory) */
		pci_ग_लिखो_config_dword(pcidev, PCI_CONF_MBAR1, OCM_BASE_ADDR);
		asd_ha->io_handle[1].swa_base = OCM_BASE_ADDR;
	पूर्ण
	spin_lock_init(&asd_ha->iolock);
Err:
	वापस err;
पूर्ण

/* ---------- SCB initialization ---------- */

/**
 * asd_init_scbs - manually allocate the first SCB.
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * This allocates the very first SCB which would be sent to the
 * sequencer क्रम execution.  Its bus address is written to
 * CSEQ_Q_NEW_POINTER, mode page 2, mode 8.  Since the bus address of
 * the _next_ scb to be DMA-ed to the host adapter is पढ़ो from the last
 * SCB DMA-ed to the host adapter, we have to always stay one step
 * ahead of the sequencer and keep one SCB alपढ़ोy allocated.
 */
अटल पूर्णांक asd_init_scbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक biपंचांगap_bytes;

	/* allocate the index array and biपंचांगap */
	asd_ha->seq.tc_index_biपंचांगap_bits = asd_ha->hw_prof.max_scbs;
	asd_ha->seq.tc_index_array = kसुस्मृति(asd_ha->seq.tc_index_biपंचांगap_bits,
					     माप(व्योम *),
					     GFP_KERNEL);
	अगर (!asd_ha->seq.tc_index_array)
		वापस -ENOMEM;

	biपंचांगap_bytes = (asd_ha->seq.tc_index_biपंचांगap_bits+7)/8;
	biपंचांगap_bytes = BITS_TO_LONGS(biपंचांगap_bytes*8)*माप(अचिन्हित दीर्घ);
	asd_ha->seq.tc_index_biपंचांगap = kzalloc(biपंचांगap_bytes, GFP_KERNEL);
	अगर (!asd_ha->seq.tc_index_biपंचांगap) अणु
		kमुक्त(asd_ha->seq.tc_index_array);
		asd_ha->seq.tc_index_array = शून्य;
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&seq->tc_index_lock);

	seq->next_scb.size = माप(काष्ठा scb);
	seq->next_scb.vaddr = dma_pool_alloc(asd_ha->scb_pool, GFP_KERNEL,
					     &seq->next_scb.dma_handle);
	अगर (!seq->next_scb.vaddr) अणु
		kमुक्त(asd_ha->seq.tc_index_biपंचांगap);
		kमुक्त(asd_ha->seq.tc_index_array);
		asd_ha->seq.tc_index_biपंचांगap = शून्य;
		asd_ha->seq.tc_index_array = शून्य;
		वापस -ENOMEM;
	पूर्ण

	seq->pending = 0;
	spin_lock_init(&seq->pend_q_lock);
	INIT_LIST_HEAD(&seq->pend_q);

	वापस 0;
पूर्ण

अटल व्योम asd_get_max_scb_ddb(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	asd_ha->hw_prof.max_scbs = asd_get_cmdctx_size(asd_ha)/ASD_SCB_SIZE;
	asd_ha->hw_prof.max_ddbs = asd_get_devctx_size(asd_ha)/ASD_DDB_SIZE;
	ASD_DPRINTK("max_scbs:%d, max_ddbs:%d\n",
		    asd_ha->hw_prof.max_scbs,
		    asd_ha->hw_prof.max_ddbs);
पूर्ण

/* ---------- Done List initialization ---------- */

अटल व्योम asd_dl_tasklet_handler(अचिन्हित दीर्घ);

अटल पूर्णांक asd_init_dl(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	asd_ha->seq.actual_dl
		= asd_alloc_coherent(asd_ha,
			     ASD_DL_SIZE * माप(काष्ठा करोne_list_काष्ठा),
				     GFP_KERNEL);
	अगर (!asd_ha->seq.actual_dl)
		वापस -ENOMEM;
	asd_ha->seq.dl = asd_ha->seq.actual_dl->vaddr;
	asd_ha->seq.dl_toggle = ASD_DEF_DL_TOGGLE;
	asd_ha->seq.dl_next = 0;
	tasklet_init(&asd_ha->seq.dl_tasklet, asd_dl_tasklet_handler,
		     (अचिन्हित दीर्घ) asd_ha);

	वापस 0;
पूर्ण

/* ---------- EDB and ESCB init ---------- */

अटल पूर्णांक asd_alloc_edbs(काष्ठा asd_ha_काष्ठा *asd_ha, gfp_t gfp_flags)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक i;

	seq->edb_arr = kदो_स्मृति_array(seq->num_edbs, माप(*seq->edb_arr),
				     gfp_flags);
	अगर (!seq->edb_arr)
		वापस -ENOMEM;

	क्रम (i = 0; i < seq->num_edbs; i++) अणु
		seq->edb_arr[i] = asd_alloc_coherent(asd_ha, ASD_EDB_SIZE,
						     gfp_flags);
		अगर (!seq->edb_arr[i])
			जाओ Err_unroll;
		स_रखो(seq->edb_arr[i]->vaddr, 0, ASD_EDB_SIZE);
	पूर्ण

	ASD_DPRINTK("num_edbs:%d\n", seq->num_edbs);

	वापस 0;

Err_unroll:
	क्रम (i-- ; i >= 0; i--)
		asd_मुक्त_coherent(asd_ha, seq->edb_arr[i]);
	kमुक्त(seq->edb_arr);
	seq->edb_arr = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक asd_alloc_escbs(काष्ठा asd_ha_काष्ठा *asd_ha,
			   gfp_t gfp_flags)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	काष्ठा asd_ascb *escb;
	पूर्णांक i, escbs;

	seq->escb_arr = kदो_स्मृति_array(seq->num_escbs, माप(*seq->escb_arr),
				      gfp_flags);
	अगर (!seq->escb_arr)
		वापस -ENOMEM;

	escbs = seq->num_escbs;
	escb = asd_ascb_alloc_list(asd_ha, &escbs, gfp_flags);
	अगर (!escb) अणु
		asd_prपूर्णांकk("couldn't allocate list of escbs\n");
		जाओ Err;
	पूर्ण
	seq->num_escbs -= escbs;  /* subtract what was not allocated */
	ASD_DPRINTK("num_escbs:%d\n", seq->num_escbs);

	क्रम (i = 0; i < seq->num_escbs; i++, escb = list_entry(escb->list.next,
							       काष्ठा asd_ascb,
							       list)) अणु
		seq->escb_arr[i] = escb;
		escb->scb->header.opcode = EMPTY_SCB;
	पूर्ण

	वापस 0;
Err:
	kमुक्त(seq->escb_arr);
	seq->escb_arr = शून्य;
	वापस -ENOMEM;

पूर्ण

अटल व्योम asd_assign_edbs2escbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक i, k, z = 0;

	क्रम (i = 0; i < seq->num_escbs; i++) अणु
		काष्ठा asd_ascb *ascb = seq->escb_arr[i];
		काष्ठा empty_scb *escb = &ascb->scb->escb;

		ascb->edb_index = z;

		escb->num_valid = ASD_EDBS_PER_SCB;

		क्रम (k = 0; k < ASD_EDBS_PER_SCB; k++) अणु
			काष्ठा sg_el *eb = &escb->eb[k];
			काष्ठा asd_dma_tok *edb = seq->edb_arr[z++];

			स_रखो(eb, 0, माप(*eb));
			eb->bus_addr = cpu_to_le64(((u64) edb->dma_handle));
			eb->size = cpu_to_le32(((u32) edb->size));
		पूर्ण
	पूर्ण
पूर्ण

/**
 * asd_init_escbs -- allocate and initialize empty scbs
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * An empty SCB has sg_elements of ASD_EDBS_PER_SCB (7) buffers.
 * They transport sense data, etc.
 */
अटल पूर्णांक asd_init_escbs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	पूर्णांक err = 0;

	/* Allocate two empty data buffers (edb) per sequencer. */
	पूर्णांक edbs = 2*(1+asd_ha->hw_prof.num_phys);

	seq->num_escbs = (edbs+ASD_EDBS_PER_SCB-1)/ASD_EDBS_PER_SCB;
	seq->num_edbs = seq->num_escbs * ASD_EDBS_PER_SCB;

	err = asd_alloc_edbs(asd_ha, GFP_KERNEL);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't allocate edbs\n");
		वापस err;
	पूर्ण

	err = asd_alloc_escbs(asd_ha, GFP_KERNEL);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't allocate escbs\n");
		वापस err;
	पूर्ण

	asd_assign_edbs2escbs(asd_ha);
	/* In order to insure that normal SCBs करो not overfill sequencer
	 * memory and leave no space क्रम escbs (halting condition),
	 * we increment pending here by the number of escbs.  However,
	 * escbs are never pending.
	 */
	seq->pending   = seq->num_escbs;
	seq->can_queue = 1 + (asd_ha->hw_prof.max_scbs - seq->pending)/2;

	वापस 0;
पूर्ण

/* ---------- HW initialization ---------- */

/**
 * asd_chip_hardrst -- hard reset the chip
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * This takes 16 cycles and is synchronous to CFCLK, which runs
 * at 200 MHz, so this should take at most 80 nanoseconds.
 */
पूर्णांक asd_chip_hardrst(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;
	पूर्णांक count = 100;
	u32 reg;

	क्रम (i = 0 ; i < 4 ; i++) अणु
		asd_ग_लिखो_reg_dword(asd_ha, COMBIST, HARDRST);
	पूर्ण

	करो अणु
		udelay(1);
		reg = asd_पढ़ो_reg_dword(asd_ha, CHIMINT);
		अगर (reg & HARDRSTDET) अणु
			asd_ग_लिखो_reg_dword(asd_ha, CHIMINT,
					    HARDRSTDET|PORRSTDET);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (--count > 0);

	वापस -ENODEV;
पूर्ण

/**
 * asd_init_chip -- initialize the chip
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Hard resets the chip, disables HA पूर्णांकerrupts, करोwnloads the sequnecer
 * microcode and starts the sequencers.  The caller has to explicitly
 * enable HA पूर्णांकerrupts with asd_enable_पूर्णांकs(asd_ha).
 */
अटल पूर्णांक asd_init_chip(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;

	err = asd_chip_hardrst(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't hard reset %s\n",
			    pci_name(asd_ha->pcidev));
		जाओ out;
	पूर्ण

	asd_disable_पूर्णांकs(asd_ha);

	err = asd_init_seqs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't init seqs for %s\n",
			   pci_name(asd_ha->pcidev));
		जाओ out;
	पूर्ण

	err = asd_start_seqs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't start seqs for %s\n",
			   pci_name(asd_ha->pcidev));
		जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

#घोषणा MAX_DEVS ((OCM_MAX_SIZE) / (ASD_DDB_SIZE))

अटल पूर्णांक max_devs = 0;
module_param_named(max_devs, max_devs, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_devs, "\n"
	"\tMaximum number of SAS devices to support (not LUs).\n"
	"\tDefault: 2176, Maximum: 65663.\n");

अटल पूर्णांक max_cmnds = 0;
module_param_named(max_cmnds, max_cmnds, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_cmnds, "\n"
	"\tMaximum number of commands queuable.\n"
	"\tDefault: 512, Maximum: 66047.\n");

अटल व्योम asd_extend_devctx_ocm(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	अचिन्हित दीर्घ dma_addr = OCM_BASE_ADDR;
	u32 d;

	dma_addr -= asd_ha->hw_prof.max_ddbs * ASD_DDB_SIZE;
	asd_ग_लिखो_reg_addr(asd_ha, DEVCTXBASE, (dma_addr_t) dma_addr);
	d = asd_पढ़ो_reg_dword(asd_ha, CTXDOMAIN);
	d |= 4;
	asd_ग_लिखो_reg_dword(asd_ha, CTXDOMAIN, d);
	asd_ha->hw_prof.max_ddbs += MAX_DEVS;
पूर्ण

अटल पूर्णांक asd_extend_devctx(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ dma_addr;
	u32 d;
	पूर्णांक size;

	asd_extend_devctx_ocm(asd_ha);

	asd_ha->hw_prof.ddb_ext = शून्य;
	अगर (max_devs <= asd_ha->hw_prof.max_ddbs || max_devs > 0xFFFF) अणु
		max_devs = asd_ha->hw_prof.max_ddbs;
		वापस 0;
	पूर्ण

	size = (max_devs - asd_ha->hw_prof.max_ddbs + 1) * ASD_DDB_SIZE;

	asd_ha->hw_prof.ddb_ext = asd_alloc_coherent(asd_ha, size, GFP_KERNEL);
	अगर (!asd_ha->hw_prof.ddb_ext) अणु
		asd_prपूर्णांकk("couldn't allocate memory for %d devices\n",
			   max_devs);
		max_devs = asd_ha->hw_prof.max_ddbs;
		वापस -ENOMEM;
	पूर्ण
	dma_handle = asd_ha->hw_prof.ddb_ext->dma_handle;
	dma_addr = ALIGN((अचिन्हित दीर्घ) dma_handle, ASD_DDB_SIZE);
	dma_addr -= asd_ha->hw_prof.max_ddbs * ASD_DDB_SIZE;
	dma_handle = (dma_addr_t) dma_addr;
	asd_ग_लिखो_reg_addr(asd_ha, DEVCTXBASE, dma_handle);
	d = asd_पढ़ो_reg_dword(asd_ha, CTXDOMAIN);
	d &= ~4;
	asd_ग_लिखो_reg_dword(asd_ha, CTXDOMAIN, d);

	asd_ha->hw_prof.max_ddbs = max_devs;

	वापस 0;
पूर्ण

अटल पूर्णांक asd_extend_cmdctx(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ dma_addr;
	u32 d;
	पूर्णांक size;

	asd_ha->hw_prof.scb_ext = शून्य;
	अगर (max_cmnds <= asd_ha->hw_prof.max_scbs || max_cmnds > 0xFFFF) अणु
		max_cmnds = asd_ha->hw_prof.max_scbs;
		वापस 0;
	पूर्ण

	size = (max_cmnds - asd_ha->hw_prof.max_scbs + 1) * ASD_SCB_SIZE;

	asd_ha->hw_prof.scb_ext = asd_alloc_coherent(asd_ha, size, GFP_KERNEL);
	अगर (!asd_ha->hw_prof.scb_ext) अणु
		asd_prपूर्णांकk("couldn't allocate memory for %d commands\n",
			   max_cmnds);
		max_cmnds = asd_ha->hw_prof.max_scbs;
		वापस -ENOMEM;
	पूर्ण
	dma_handle = asd_ha->hw_prof.scb_ext->dma_handle;
	dma_addr = ALIGN((अचिन्हित दीर्घ) dma_handle, ASD_SCB_SIZE);
	dma_addr -= asd_ha->hw_prof.max_scbs * ASD_SCB_SIZE;
	dma_handle = (dma_addr_t) dma_addr;
	asd_ग_लिखो_reg_addr(asd_ha, CMDCTXBASE, dma_handle);
	d = asd_पढ़ो_reg_dword(asd_ha, CTXDOMAIN);
	d &= ~1;
	asd_ग_लिखो_reg_dword(asd_ha, CTXDOMAIN, d);

	asd_ha->hw_prof.max_scbs = max_cmnds;

	वापस 0;
पूर्ण

/**
 * asd_init_ctxmem -- initialize context memory
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * This function sets the maximum number of SCBs and
 * DDBs which can be used by the sequencer.  This is normally
 * 512 and 128 respectively.  If support क्रम more SCBs or more DDBs
 * is required then CMDCTXBASE, DEVCTXBASE and CTXDOMAIN are
 * initialized here to extend context memory to poपूर्णांक to host memory,
 * thus allowing unlimited support क्रम SCBs and DDBs -- only limited
 * by host memory.
 */
अटल पूर्णांक asd_init_ctxmem(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक biपंचांगap_bytes;

	asd_get_max_scb_ddb(asd_ha);
	asd_extend_devctx(asd_ha);
	asd_extend_cmdctx(asd_ha);

	/* The kernel wants biपंचांगaps to be अचिन्हित दीर्घ sized. */
	biपंचांगap_bytes = (asd_ha->hw_prof.max_ddbs+7)/8;
	biपंचांगap_bytes = BITS_TO_LONGS(biपंचांगap_bytes*8)*माप(अचिन्हित दीर्घ);
	asd_ha->hw_prof.ddb_biपंचांगap = kzalloc(biपंचांगap_bytes, GFP_KERNEL);
	अगर (!asd_ha->hw_prof.ddb_biपंचांगap)
		वापस -ENOMEM;
	spin_lock_init(&asd_ha->hw_prof.ddb_lock);

	वापस 0;
पूर्ण

पूर्णांक asd_init_hw(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;
	u32 v;

	err = asd_init_sw(asd_ha);
	अगर (err)
		वापस err;

	err = pci_पढ़ो_config_dword(asd_ha->pcidev, PCIC_HSTPCIX_CNTRL, &v);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't read PCIC_HSTPCIX_CNTRL of %s\n",
			   pci_name(asd_ha->pcidev));
		वापस err;
	पूर्ण
	err = pci_ग_लिखो_config_dword(asd_ha->pcidev, PCIC_HSTPCIX_CNTRL,
					v | SC_TMR_DIS);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't disable split completion timer of %s\n",
			   pci_name(asd_ha->pcidev));
		वापस err;
	पूर्ण

	err = asd_पढ़ो_ocm(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't read ocm(%d)\n", err);
		/* While suspicios, it is not an error that we
		 * couldn't पढ़ो the OCM. */
	पूर्ण

	err = asd_पढ़ो_flash(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't read flash(%d)\n", err);
		/* While suspicios, it is not an error that we
		 * couldn't पढ़ो FLASH memory.
		 */
	पूर्ण

	asd_init_ctxmem(asd_ha);

	अगर (asd_get_user_sas_addr(asd_ha)) अणु
		asd_prपूर्णांकk("No SAS Address provided for %s\n",
			   pci_name(asd_ha->pcidev));
		err = -ENODEV;
		जाओ Out;
	पूर्ण

	asd_propagate_sas_addr(asd_ha);

	err = asd_init_phys(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't initialize phys for %s\n",
			    pci_name(asd_ha->pcidev));
		जाओ Out;
	पूर्ण

	asd_init_ports(asd_ha);

	err = asd_init_scbs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't initialize scbs for %s\n",
			    pci_name(asd_ha->pcidev));
		जाओ Out;
	पूर्ण

	err = asd_init_dl(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't initialize the done list:%d\n",
			    err);
		जाओ Out;
	पूर्ण

	err = asd_init_escbs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't initialize escbs\n");
		जाओ Out;
	पूर्ण

	err = asd_init_chip(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't init the chip\n");
		जाओ Out;
	पूर्ण
Out:
	वापस err;
पूर्ण

/* ---------- Chip reset ---------- */

/**
 * asd_chip_reset -- reset the host adapter, etc
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure of पूर्णांकerest
 *
 * Called from the ISR.  Hard reset the chip.  Let everything
 * समयout.  This should be no dअगरferent than hot-unplugging the
 * host adapter.  Once everything बार out we'll init the chip with
 * a call to asd_init_chip() and enable पूर्णांकerrupts with asd_enable_पूर्णांकs().
 * XXX finish.
 */
अटल व्योम asd_chip_reset(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	ASD_DPRINTK("chip reset for %s\n", pci_name(asd_ha->pcidev));
	asd_chip_hardrst(asd_ha);
पूर्ण

/* ---------- Done List Routines ---------- */

अटल व्योम asd_dl_tasklet_handler(अचिन्हित दीर्घ data)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = (काष्ठा asd_ha_काष्ठा *) data;
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		काष्ठा करोne_list_काष्ठा *dl = &seq->dl[seq->dl_next];
		काष्ठा asd_ascb *ascb;

		अगर ((dl->toggle & DL_TOGGLE_MASK) != seq->dl_toggle)
			अवरोध;

		/* find the aSCB */
		spin_lock_irqsave(&seq->tc_index_lock, flags);
		ascb = asd_tc_index_find(seq, (पूर्णांक)le16_to_cpu(dl->index));
		spin_unlock_irqrestore(&seq->tc_index_lock, flags);
		अगर (unlikely(!ascb)) अणु
			ASD_DPRINTK("BUG:sequencer:dl:no ascb?!\n");
			जाओ next_1;
		पूर्ण अन्यथा अगर (ascb->scb->header.opcode == EMPTY_SCB) अणु
			जाओ out;
		पूर्ण अन्यथा अगर (!ascb->uldd_समयr && !del_समयr(&ascb->समयr)) अणु
			जाओ next_1;
		पूर्ण
		spin_lock_irqsave(&seq->pend_q_lock, flags);
		list_del_init(&ascb->list);
		seq->pending--;
		spin_unlock_irqrestore(&seq->pend_q_lock, flags);
	out:
		ascb->tasklet_complete(ascb, dl);

	next_1:
		seq->dl_next = (seq->dl_next + 1) & (ASD_DL_SIZE-1);
		अगर (!seq->dl_next)
			seq->dl_toggle ^= DL_TOGGLE_MASK;
	पूर्ण
पूर्ण

/* ---------- Interrupt Service Routines ---------- */

/**
 * asd_process_करोnelist_isr -- schedule processing of करोne list entries
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_process_करोnelist_isr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	tasklet_schedule(&asd_ha->seq.dl_tasklet);
पूर्ण

/**
 * asd_com_sas_isr -- process device communication पूर्णांकerrupt (COMINT)
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_com_sas_isr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u32 comstat = asd_पढ़ो_reg_dword(asd_ha, COMSTAT);

	/* clear COMSTAT पूर्णांक */
	asd_ग_लिखो_reg_dword(asd_ha, COMSTAT, 0xFFFFFFFF);

	अगर (comstat & CSBUFPERR) अणु
		asd_prपूर्णांकk("%s: command/status buffer dma parity error\n",
			   pci_name(asd_ha->pcidev));
	पूर्ण अन्यथा अगर (comstat & CSERR) अणु
		पूर्णांक i;
		u32 dmaerr = asd_पढ़ो_reg_dword(asd_ha, DMAERR);
		dmaerr &= 0xFF;
		asd_prपूर्णांकk("%s: command/status dma error, DMAERR: 0x%02x, "
			   "CSDMAADR: 0x%04x, CSDMAADR+4: 0x%04x\n",
			   pci_name(asd_ha->pcidev),
			   dmaerr,
			   asd_पढ़ो_reg_dword(asd_ha, CSDMAADR),
			   asd_पढ़ो_reg_dword(asd_ha, CSDMAADR+4));
		asd_prपूर्णांकk("CSBUFFER:\n");
		क्रम (i = 0; i < 8; i++) अणु
			asd_prपूर्णांकk("%08x %08x %08x %08x\n",
				   asd_पढ़ो_reg_dword(asd_ha, CSBUFFER),
				   asd_पढ़ो_reg_dword(asd_ha, CSBUFFER+4),
				   asd_पढ़ो_reg_dword(asd_ha, CSBUFFER+8),
				   asd_पढ़ो_reg_dword(asd_ha, CSBUFFER+12));
		पूर्ण
		asd_dump_seq_state(asd_ha, 0);
	पूर्ण अन्यथा अगर (comstat & OVLYERR) अणु
		u32 dmaerr = asd_पढ़ो_reg_dword(asd_ha, DMAERR);
		dmaerr = (dmaerr >> 8) & 0xFF;
		asd_prपूर्णांकk("%s: overlay dma error:0x%x\n",
			   pci_name(asd_ha->pcidev),
			   dmaerr);
	पूर्ण
	asd_chip_reset(asd_ha);
पूर्ण

अटल व्योम asd_arp2_err(काष्ठा asd_ha_काष्ठा *asd_ha, u32 dchstatus)
अणु
	अटल स्थिर अक्षर *halt_code[256] = अणु
		"UNEXPECTED_INTERRUPT0",
		"UNEXPECTED_INTERRUPT1",
		"UNEXPECTED_INTERRUPT2",
		"UNEXPECTED_INTERRUPT3",
		"UNEXPECTED_INTERRUPT4",
		"UNEXPECTED_INTERRUPT5",
		"UNEXPECTED_INTERRUPT6",
		"UNEXPECTED_INTERRUPT7",
		"UNEXPECTED_INTERRUPT8",
		"UNEXPECTED_INTERRUPT9",
		"UNEXPECTED_INTERRUPT10",
		[11 ... 19] = "unknown[11,19]",
		"NO_FREE_SCB_AVAILABLE",
		"INVALID_SCB_OPCODE",
		"INVALID_MBX_OPCODE",
		"INVALID_ATA_STATE",
		"ATA_QUEUE_FULL",
		"ATA_TAG_TABLE_FAULT",
		"ATA_TAG_MASK_FAULT",
		"BAD_LINK_QUEUE_STATE",
		"DMA2CHIM_QUEUE_ERROR",
		"EMPTY_SCB_LIST_FULL",
		"unknown[30]",
		"IN_USE_SCB_ON_FREE_LIST",
		"BAD_OPEN_WAIT_STATE",
		"INVALID_STP_AFFILIATION",
		"unknown[34]",
		"EXEC_QUEUE_ERROR",
		"TOO_MANY_EMPTIES_NEEDED",
		"EMPTY_REQ_QUEUE_ERROR",
		"Q_MONIRTT_MGMT_ERROR",
		"TARGET_MODE_FLOW_ERROR",
		"DEVICE_QUEUE_NOT_FOUND",
		"START_IRTT_TIMER_ERROR",
		"ABORT_TASK_ILLEGAL_REQ",
		[43 ... 255] = "unknown[43,255]"
	पूर्ण;

	अगर (dchstatus & CSEQINT) अणु
		u32 arp2पूर्णांक = asd_पढ़ो_reg_dword(asd_ha, CARP2INT);

		अगर (arp2पूर्णांक & (ARP2WAITTO|ARP2ILLOPC|ARP2PERR|ARP2CIOPERR)) अणु
			asd_prपूर्णांकk("%s: CSEQ arp2int:0x%x\n",
				   pci_name(asd_ha->pcidev),
				   arp2पूर्णांक);
		पूर्ण अन्यथा अगर (arp2पूर्णांक & ARP2HALTC)
			asd_prपूर्णांकk("%s: CSEQ halted: %s\n",
				   pci_name(asd_ha->pcidev),
				   halt_code[(arp2पूर्णांक>>16)&0xFF]);
		अन्यथा
			asd_prपूर्णांकk("%s: CARP2INT:0x%x\n",
				   pci_name(asd_ha->pcidev),
				   arp2पूर्णांक);
	पूर्ण
	अगर (dchstatus & LSEQINT_MASK) अणु
		पूर्णांक lseq;
		u8  lseq_mask = dchstatus & LSEQINT_MASK;

		क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
			u32 arp2पूर्णांक = asd_पढ़ो_reg_dword(asd_ha,
							 LmARP2INT(lseq));
			अगर (arp2पूर्णांक & (ARP2WAITTO | ARP2ILLOPC | ARP2PERR
				       | ARP2CIOPERR)) अणु
				asd_prपूर्णांकk("%s: LSEQ%d arp2int:0x%x\n",
					   pci_name(asd_ha->pcidev),
					   lseq, arp2पूर्णांक);
				/* XXX we should only करो lseq reset */
			पूर्ण अन्यथा अगर (arp2पूर्णांक & ARP2HALTC)
				asd_prपूर्णांकk("%s: LSEQ%d halted: %s\n",
					   pci_name(asd_ha->pcidev),
					   lseq,halt_code[(arp2पूर्णांक>>16)&0xFF]);
			अन्यथा
				asd_prपूर्णांकk("%s: LSEQ%d ARP2INT:0x%x\n",
					   pci_name(asd_ha->pcidev), lseq,
					   arp2पूर्णांक);
		पूर्ण
	पूर्ण
	asd_chip_reset(asd_ha);
पूर्ण

/**
 * asd_dch_sas_isr -- process device channel पूर्णांकerrupt (DEVINT)
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_dch_sas_isr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u32 dchstatus = asd_पढ़ो_reg_dword(asd_ha, DCHSTATUS);

	अगर (dchstatus & CFIFTOERR) अणु
		asd_prपूर्णांकk("%s: CFIFTOERR\n", pci_name(asd_ha->pcidev));
		asd_chip_reset(asd_ha);
	पूर्ण अन्यथा
		asd_arp2_err(asd_ha, dchstatus);
पूर्ण

/**
 * asd_rbi_exsi_isr -- process बाह्यal प्रणाली पूर्णांकerface पूर्णांकerrupt (INITERR)
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_rbi_exsi_isr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u32 stat0r = asd_पढ़ो_reg_dword(asd_ha, ASISTAT0R);

	अगर (!(stat0r & ASIERR)) अणु
		asd_prपूर्णांकk("hmm, EXSI interrupted but no error?\n");
		वापस;
	पूर्ण

	अगर (stat0r & ASIFMTERR) अणु
		asd_prपूर्णांकk("ASI SEEPROM format error for %s\n",
			   pci_name(asd_ha->pcidev));
	पूर्ण अन्यथा अगर (stat0r & ASISEECHKERR) अणु
		u32 stat1r = asd_पढ़ो_reg_dword(asd_ha, ASISTAT1R);
		asd_prपूर्णांकk("ASI SEEPROM checksum 0x%x error for %s\n",
			   stat1r & CHECKSUM_MASK,
			   pci_name(asd_ha->pcidev));
	पूर्ण अन्यथा अणु
		u32 statr = asd_पढ़ो_reg_dword(asd_ha, ASIERRSTATR);

		अगर (!(statr & CPI2ASIMSTERR_MASK)) अणु
			ASD_DPRINTK("hmm, ASIERR?\n");
			वापस;
		पूर्ण अन्यथा अणु
			u32 addr = asd_पढ़ो_reg_dword(asd_ha, ASIERRADDR);
			u32 data = asd_पढ़ो_reg_dword(asd_ha, ASIERRDATAR);

			asd_prपूर्णांकk("%s: CPI2 xfer err: addr: 0x%x, wdata: 0x%x, "
				   "count: 0x%x, byteen: 0x%x, targerr: 0x%x "
				   "master id: 0x%x, master err: 0x%x\n",
				   pci_name(asd_ha->pcidev),
				   addr, data,
				   (statr & CPI2ASIBYTECNT_MASK) >> 16,
				   (statr & CPI2ASIBYTEEN_MASK) >> 12,
				   (statr & CPI2ASITARGERR_MASK) >> 8,
				   (statr & CPI2ASITARGMID_MASK) >> 4,
				   (statr & CPI2ASIMSTERR_MASK));
		पूर्ण
	पूर्ण
	asd_chip_reset(asd_ha);
पूर्ण

/**
 * asd_hst_pcix_isr -- process host पूर्णांकerface पूर्णांकerrupts
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Asserted on PCIX errors: target पात, etc.
 */
अटल व्योम asd_hst_pcix_isr(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u16 status;
	u32 pcix_status;
	u32 ecc_status;

	pci_पढ़ो_config_word(asd_ha->pcidev, PCI_STATUS, &status);
	pci_पढ़ो_config_dword(asd_ha->pcidev, PCIX_STATUS, &pcix_status);
	pci_पढ़ो_config_dword(asd_ha->pcidev, ECC_CTRL_STAT, &ecc_status);

	अगर (status & PCI_STATUS_DETECTED_PARITY)
		asd_prपूर्णांकk("parity error for %s\n", pci_name(asd_ha->pcidev));
	अन्यथा अगर (status & PCI_STATUS_REC_MASTER_ABORT)
		asd_prपूर्णांकk("master abort for %s\n", pci_name(asd_ha->pcidev));
	अन्यथा अगर (status & PCI_STATUS_REC_TARGET_ABORT)
		asd_prपूर्णांकk("target abort for %s\n", pci_name(asd_ha->pcidev));
	अन्यथा अगर (status & PCI_STATUS_PARITY)
		asd_prपूर्णांकk("data parity for %s\n", pci_name(asd_ha->pcidev));
	अन्यथा अगर (pcix_status & RCV_SCE) अणु
		asd_prपूर्णांकk("received split completion error for %s\n",
			   pci_name(asd_ha->pcidev));
		pci_ग_लिखो_config_dword(asd_ha->pcidev,PCIX_STATUS,pcix_status);
		/* XXX: Abort task? */
		वापस;
	पूर्ण अन्यथा अगर (pcix_status & UNEXP_SC) अणु
		asd_prपूर्णांकk("unexpected split completion for %s\n",
			   pci_name(asd_ha->pcidev));
		pci_ग_लिखो_config_dword(asd_ha->pcidev,PCIX_STATUS,pcix_status);
		/* ignore */
		वापस;
	पूर्ण अन्यथा अगर (pcix_status & SC_DISCARD)
		asd_prपूर्णांकk("split completion discarded for %s\n",
			   pci_name(asd_ha->pcidev));
	अन्यथा अगर (ecc_status & UNCOR_ECCERR)
		asd_prपूर्णांकk("uncorrectable ECC error for %s\n",
			   pci_name(asd_ha->pcidev));
	asd_chip_reset(asd_ha);
पूर्ण

/**
 * asd_hw_isr -- host adapter पूर्णांकerrupt service routine
 * @irq: ignored
 * @dev_id: poपूर्णांकer to host adapter काष्ठाure
 *
 * The ISR processes करोne list entries and level 3 error handling.
 */
irqवापस_t asd_hw_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev_id;
	u32 chimपूर्णांक = asd_पढ़ो_reg_dword(asd_ha, CHIMINT);

	अगर (!chimपूर्णांक)
		वापस IRQ_NONE;

	asd_ग_लिखो_reg_dword(asd_ha, CHIMINT, chimपूर्णांक);
	(व्योम) asd_पढ़ो_reg_dword(asd_ha, CHIMINT);

	अगर (chimपूर्णांक & DLAVAIL)
		asd_process_करोnelist_isr(asd_ha);
	अगर (chimपूर्णांक & COMINT)
		asd_com_sas_isr(asd_ha);
	अगर (chimपूर्णांक & DEVINT)
		asd_dch_sas_isr(asd_ha);
	अगर (chimपूर्णांक & INITERR)
		asd_rbi_exsi_isr(asd_ha);
	अगर (chimपूर्णांक & HOSTERR)
		asd_hst_pcix_isr(asd_ha);

	वापस IRQ_HANDLED;
पूर्ण

/* ---------- SCB handling ---------- */

अटल काष्ठा asd_ascb *asd_ascb_alloc(काष्ठा asd_ha_काष्ठा *asd_ha,
				       gfp_t gfp_flags)
अणु
	बाह्य काष्ठा kmem_cache *asd_ascb_cache;
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	काष्ठा asd_ascb *ascb;
	अचिन्हित दीर्घ flags;

	ascb = kmem_cache_zalloc(asd_ascb_cache, gfp_flags);

	अगर (ascb) अणु
		ascb->dma_scb.size = माप(काष्ठा scb);
		ascb->dma_scb.vaddr = dma_pool_zalloc(asd_ha->scb_pool,
						     gfp_flags,
						    &ascb->dma_scb.dma_handle);
		अगर (!ascb->dma_scb.vaddr) अणु
			kmem_cache_मुक्त(asd_ascb_cache, ascb);
			वापस शून्य;
		पूर्ण
		asd_init_ascb(asd_ha, ascb);

		spin_lock_irqsave(&seq->tc_index_lock, flags);
		ascb->tc_index = asd_tc_index_get(seq, ascb);
		spin_unlock_irqrestore(&seq->tc_index_lock, flags);
		अगर (ascb->tc_index == -1)
			जाओ unकरो;

		ascb->scb->header.index = cpu_to_le16((u16)ascb->tc_index);
	पूर्ण

	वापस ascb;
unकरो:
	dma_pool_मुक्त(asd_ha->scb_pool, ascb->dma_scb.vaddr,
		      ascb->dma_scb.dma_handle);
	kmem_cache_मुक्त(asd_ascb_cache, ascb);
	ASD_DPRINTK("no index for ascb\n");
	वापस शून्य;
पूर्ण

/**
 * asd_ascb_alloc_list -- allocate a list of aSCBs
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @num: poपूर्णांकer to पूर्णांकeger number of aSCBs
 * @gfp_flags: GFP_ flags.
 *
 * This is the only function which is used to allocate aSCBs.
 * It can allocate one or many. If more than one, then they क्रमm
 * a linked list in two ways: by their list field of the ascb काष्ठा
 * and by the next_scb field of the scb_header.
 *
 * Returns शून्य अगर no memory was available, अन्यथा poपूर्णांकer to a list
 * of ascbs.  When this function वापसs, @num would be the number
 * of SCBs which were not able to be allocated, 0 अगर all requested
 * were able to be allocated.
 */
काष्ठा asd_ascb *asd_ascb_alloc_list(काष्ठा asd_ha_काष्ठा
				     *asd_ha, पूर्णांक *num,
				     gfp_t gfp_flags)
अणु
	काष्ठा asd_ascb *first = शून्य;

	क्रम ( ; *num > 0; --*num) अणु
		काष्ठा asd_ascb *ascb = asd_ascb_alloc(asd_ha, gfp_flags);

		अगर (!ascb)
			अवरोध;
		अन्यथा अगर (!first)
			first = ascb;
		अन्यथा अणु
			काष्ठा asd_ascb *last = list_entry(first->list.prev,
							   काष्ठा asd_ascb,
							   list);
			list_add_tail(&ascb->list, &first->list);
			last->scb->header.next_scb =
				cpu_to_le64(((u64)ascb->dma_scb.dma_handle));
		पूर्ण
	पूर्ण

	वापस first;
पूर्ण

/**
 * asd_swap_head_scb -- swap the head scb
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @ascb: poपूर्णांकer to the head of an ascb list
 *
 * The sequencer knows the DMA address of the next SCB to be DMAed to
 * the host adapter, from initialization or from the last list DMAed.
 * seq->next_scb keeps the address of this SCB.  The sequencer will
 * DMA to the host adapter this list of SCBs.  But the head (first
 * element) of this list is not known to the sequencer.  Here we swap
 * the head of the list with the known SCB (स_नकल()).
 * Only one स_नकल() is required per list so it is in our पूर्णांकerest
 * to keep the list of SCB as दीर्घ as possible so that the ratio
 * of number of स_नकल calls to the number of SCB DMA-ed is as small
 * as possible.
 *
 * LOCKING: called with the pending list lock held.
 */
अटल व्योम asd_swap_head_scb(काष्ठा asd_ha_काष्ठा *asd_ha,
			      काष्ठा asd_ascb *ascb)
अणु
	काष्ठा asd_seq_data *seq = &asd_ha->seq;
	काष्ठा asd_ascb *last = list_entry(ascb->list.prev,
					   काष्ठा asd_ascb,
					   list);
	काष्ठा asd_dma_tok t = ascb->dma_scb;

	स_नकल(seq->next_scb.vaddr, ascb->scb, माप(*ascb->scb));
	ascb->dma_scb = seq->next_scb;
	ascb->scb = ascb->dma_scb.vaddr;
	seq->next_scb = t;
	last->scb->header.next_scb =
		cpu_to_le64(((u64)seq->next_scb.dma_handle));
पूर्ण

/**
 * asd_start_scb_समयrs -- (add and) start समयrs of SCBs
 * @list: poपूर्णांकer to काष्ठा list_head of the scbs
 *
 * If an SCB in the @list has no समयr function, assign the शेष
 * one,  then start the समयr of the SCB.  This function is
 * पूर्णांकended to be called from asd_post_ascb_list(), just prior to
 * posting the SCBs to the sequencer.
 */
अटल व्योम asd_start_scb_समयrs(काष्ठा list_head *list)
अणु
	काष्ठा asd_ascb *ascb;
	list_क्रम_each_entry(ascb, list, list) अणु
		अगर (!ascb->uldd_समयr) अणु
			ascb->समयr.function = asd_ascb_समयकरोut;
			ascb->समयr.expires = jअगरfies + AIC94XX_SCB_TIMEOUT;
			add_समयr(&ascb->समयr);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * asd_post_ascb_list -- post a list of 1 or more aSCBs to the host adapter
 * @asd_ha: poपूर्णांकer to a host adapter काष्ठाure
 * @ascb: poपूर्णांकer to the first aSCB in the list
 * @num: number of aSCBs in the list (to be posted)
 *
 * See queueing comment in asd_post_escb_list().
 *
 * Additional note on queuing: In order to minimize the ratio of स_नकल()
 * to the number of ascbs sent, we try to batch-send as many ascbs as possible
 * in one go.
 * Two हालs are possible:
 *    A) can_queue >= num,
 *    B) can_queue < num.
 * Case A: we can send the whole batch at once.  Increment "pending"
 * in the beginning of this function, when it is checked, in order to
 * eliminate races when this function is called by multiple processes.
 * Case B: should never happen.
 */
पूर्णांक asd_post_ascb_list(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_ascb *ascb,
		       पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);
	पूर्णांक can_queue;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	can_queue = asd_ha->hw_prof.max_scbs - asd_ha->seq.pending;
	अगर (can_queue >= num)
		asd_ha->seq.pending += num;
	अन्यथा
		can_queue = 0;

	अगर (!can_queue) अणु
		spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);
		asd_prपूर्णांकk("%s: scb queue full\n", pci_name(asd_ha->pcidev));
		वापस -SAS_QUEUE_FULL;
	पूर्ण

	asd_swap_head_scb(asd_ha, ascb);

	__list_add(&list, ascb->list.prev, &ascb->list);

	asd_start_scb_समयrs(&list);

	asd_ha->seq.scbpro += num;
	list_splice_init(&list, asd_ha->seq.pend_q.prev);
	asd_ग_लिखो_reg_dword(asd_ha, SCBPRO, (u32)asd_ha->seq.scbpro);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	वापस 0;
पूर्ण

/**
 * asd_post_escb_list -- post a list of 1 or more empty scb
 * @asd_ha: poपूर्णांकer to a host adapter काष्ठाure
 * @ascb: poपूर्णांकer to the first empty SCB in the list
 * @num: number of aSCBs in the list (to be posted)
 *
 * This is essentially the same as asd_post_ascb_list, but we करो not
 * increment pending, add those to the pending list or get indexes.
 * See asd_init_escbs() and asd_init_post_escbs().
 *
 * Since sending a list of ascbs is a superset of sending a single
 * ascb, this function exists to generalize this.  More specअगरically,
 * when sending a list of those, we want to करो only a _single_
 * स_नकल() at swap head, as opposed to क्रम each ascb sent (in the
 * हाल of sending them one by one).  That is, we want to minimize the
 * ratio of स_नकल() operations to the number of ascbs sent.  The same
 * logic applies to asd_post_ascb_list().
 */
पूर्णांक asd_post_escb_list(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_ascb *ascb,
		       पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_swap_head_scb(asd_ha, ascb);
	asd_ha->seq.scbpro += num;
	asd_ग_लिखो_reg_dword(asd_ha, SCBPRO, (u32)asd_ha->seq.scbpro);
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	वापस 0;
पूर्ण

/* ---------- LED ---------- */

/**
 * asd_turn_led -- turn on/off an LED
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @phy_id: the PHY id whose LED we want to manupulate
 * @op: 1 to turn on, 0 to turn off
 */
व्योम asd_turn_led(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक phy_id, पूर्णांक op)
अणु
	अगर (phy_id < ASD_MAX_PHYS) अणु
		u32 v = asd_पढ़ो_reg_dword(asd_ha, LmCONTROL(phy_id));
		अगर (op)
			v |= LEDPOL;
		अन्यथा
			v &= ~LEDPOL;
		asd_ग_लिखो_reg_dword(asd_ha, LmCONTROL(phy_id), v);
	पूर्ण
पूर्ण

/**
 * asd_control_led -- enable/disable an LED on the board
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @phy_id: पूर्णांकeger, the phy id
 * @op: पूर्णांकeger, 1 to enable, 0 to disable the LED
 *
 * First we output enable the LED, then we set the source
 * to be an बाह्यal module.
 */
व्योम asd_control_led(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक phy_id, पूर्णांक op)
अणु
	अगर (phy_id < ASD_MAX_PHYS) अणु
		u32 v;

		v = asd_पढ़ो_reg_dword(asd_ha, GPIOOER);
		अगर (op)
			v |= (1 << phy_id);
		अन्यथा
			v &= ~(1 << phy_id);
		asd_ग_लिखो_reg_dword(asd_ha, GPIOOER, v);

		v = asd_पढ़ो_reg_dword(asd_ha, GPIOCNFGR);
		अगर (op)
			v |= (1 << phy_id);
		अन्यथा
			v &= ~(1 << phy_id);
		asd_ग_लिखो_reg_dword(asd_ha, GPIOCNFGR, v);
	पूर्ण
पूर्ण

/* ---------- PHY enable ---------- */

अटल पूर्णांक asd_enable_phy(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक phy_id)
अणु
	काष्ठा asd_phy *phy = &asd_ha->phys[phy_id];

	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, INT_ENABLE_2), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, HOT_PLUG_DELAY),
			   HOTPLUG_DELAY_TIMEOUT);

	/* Get शेषs from manuf. sector */
	/* XXX we need शेषs क्रम those in हाल MS is broken. */
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_0),
			   phy->phy_desc->phy_control_0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_1),
			   phy->phy_desc->phy_control_1);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_2),
			   phy->phy_desc->phy_control_2);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_3),
			   phy->phy_desc->phy_control_3);

	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_TEN_MS_COMINIT_TIMEOUT(phy_id),
			    ASD_COMINIT_TIMEOUT);

	asd_ग_लिखो_reg_addr(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(phy_id),
			   phy->id_frm_tok->dma_handle);

	asd_control_led(asd_ha, phy_id, 1);

	वापस 0;
पूर्ण

पूर्णांक asd_enable_phys(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 phy_mask)
अणु
	u8  phy_m;
	u8  i;
	पूर्णांक num = 0, k;
	काष्ठा asd_ascb *ascb;
	काष्ठा asd_ascb *ascb_list;

	अगर (!phy_mask) अणु
		asd_prपूर्णांकk("%s called with phy_mask of 0!?\n", __func__);
		वापस 0;
	पूर्ण

	क्रम_each_phy(phy_mask, phy_m, i) अणु
		num++;
		asd_enable_phy(asd_ha, i);
	पूर्ण

	k = num;
	ascb_list = asd_ascb_alloc_list(asd_ha, &k, GFP_KERNEL);
	अगर (!ascb_list) अणु
		asd_prपूर्णांकk("no memory for control phy ascb list\n");
		वापस -ENOMEM;
	पूर्ण
	num -= k;

	ascb = ascb_list;
	क्रम_each_phy(phy_mask, phy_m, i) अणु
		asd_build_control_phy(ascb, i, ENABLE_PHY);
		ascb = list_entry(ascb->list.next, काष्ठा asd_ascb, list);
	पूर्ण
	ASD_DPRINTK("posting %d control phy scbs\n", num);
	k = asd_post_ascb_list(asd_ha, ascb_list, num);
	अगर (k)
		asd_ascb_मुक्त_list(ascb_list);

	वापस k;
पूर्ण
