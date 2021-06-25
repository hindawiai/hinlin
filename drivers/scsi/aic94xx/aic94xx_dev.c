<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA DDB management
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * $Id: //depot/aic94xx/aic94xx_dev.c#21 $
 */

#समावेश "aic94xx.h"
#समावेश "aic94xx_hwi.h"
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_sas.h"

#घोषणा FIND_FREE_DDB(_ha) find_first_zero_bit((_ha)->hw_prof.ddb_biपंचांगap, \
					       (_ha)->hw_prof.max_ddbs)
#घोषणा SET_DDB(_ddb, _ha) set_bit(_ddb, (_ha)->hw_prof.ddb_biपंचांगap)
#घोषणा CLEAR_DDB(_ddb, _ha) clear_bit(_ddb, (_ha)->hw_prof.ddb_biपंचांगap)

अटल पूर्णांक asd_get_ddb(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक ddb, i;

	ddb = FIND_FREE_DDB(asd_ha);
	अगर (ddb >= asd_ha->hw_prof.max_ddbs) अणु
		ddb = -ENOMEM;
		जाओ out;
	पूर्ण
	SET_DDB(ddb, asd_ha);

	क्रम (i = 0; i < माप(काष्ठा asd_ddb_ssp_smp_target_port); i+= 4)
		asd_ddbsite_ग_लिखो_dword(asd_ha, ddb, i, 0);
out:
	वापस ddb;
पूर्ण

#घोषणा INIT_CONN_TAG   दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, init_conn_tag)
#घोषणा DEST_SAS_ADDR   दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, dest_sas_addr)
#घोषणा SEND_QUEUE_HEAD दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, send_queue_head)
#घोषणा DDB_TYPE        दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, ddb_type)
#घोषणा CONN_MASK       दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, conn_mask)
#घोषणा DDB_TARG_FLAGS  दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, flags)
#घोषणा DDB_TARG_FLAGS2 दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, flags2)
#घोषणा EXEC_QUEUE_TAIL दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, exec_queue_tail)
#घोषणा SEND_QUEUE_TAIL दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, send_queue_tail)
#घोषणा SISTER_DDB      दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, sister_ddb)
#घोषणा MAX_CCONN       दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, max_concurrent_conn)
#घोषणा NUM_CTX         दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, num_contexts)
#घोषणा ATA_CMD_SCBPTR  दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, ata_cmd_scbptr)
#घोषणा SATA_TAG_ALLOC_MASK दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, sata_tag_alloc_mask)
#घोषणा NUM_SATA_TAGS   दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, num_sata_tags)
#घोषणा SATA_STATUS     दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, sata_status)
#घोषणा NCQ_DATA_SCB_PTR दुरत्व(काष्ठा asd_ddb_stp_sata_target_port, ncq_data_scb_ptr)
#घोषणा ITNL_TIMEOUT    दुरत्व(काष्ठा asd_ddb_ssp_smp_target_port, itnl_समयout)

अटल व्योम asd_मुक्त_ddb(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक ddb)
अणु
	अगर (!ddb || ddb >= 0xFFFF)
		वापस;
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, DDB_TYPE, DDB_TYPE_UNUSED);
	CLEAR_DDB(ddb, asd_ha);
पूर्ण

अटल व्योम asd_set_ddb_type(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	पूर्णांक ddb = (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev;

	अगर (dev->dev_type == SAS_SATA_PM_PORT)
		asd_ddbsite_ग_लिखो_byte(asd_ha,ddb, DDB_TYPE, DDB_TYPE_PM_PORT);
	अन्यथा अगर (dev->tproto)
		asd_ddbsite_ग_लिखो_byte(asd_ha,ddb, DDB_TYPE, DDB_TYPE_TARGET);
	अन्यथा
		asd_ddbsite_ग_लिखो_byte(asd_ha,ddb,DDB_TYPE,DDB_TYPE_INITIATOR);
पूर्ण

अटल पूर्णांक asd_init_sata_tag_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	पूर्णांक ddb, i;

	ddb = asd_get_ddb(asd_ha);
	अगर (ddb < 0)
		वापस ddb;

	क्रम (i = 0; i < माप(काष्ठा asd_ddb_sata_tag); i += 2)
		asd_ddbsite_ग_लिखो_word(asd_ha, ddb, i, 0xFFFF);

	asd_ddbsite_ग_लिखो_word(asd_ha, (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev,
			       SISTER_DDB, ddb);
	वापस 0;
पूर्ण

व्योम asd_set_dmamode(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	काष्ठा ata_device *ata_dev = sas_to_ata_dev(dev);
	पूर्णांक ddb = (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev;
	u32 qdepth = 0;

	अगर (dev->dev_type == SAS_SATA_DEV || dev->dev_type == SAS_SATA_PM_PORT) अणु
		अगर (ata_id_has_ncq(ata_dev->id))
			qdepth = ata_id_queue_depth(ata_dev->id);
		asd_ddbsite_ग_लिखो_dword(asd_ha, ddb, SATA_TAG_ALLOC_MASK,
					(1ULL<<qdepth)-1);
		asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, NUM_SATA_TAGS, qdepth);
	पूर्ण

	अगर (qdepth > 0)
		अगर (asd_init_sata_tag_ddb(dev) != 0) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(dev->sata_dev.ap->lock, flags);
			ata_dev->flags |= ATA_DFLAG_NCQ_OFF;
			spin_unlock_irqrestore(dev->sata_dev.ap->lock, flags);
		पूर्ण
पूर्ण

अटल पूर्णांक asd_init_sata(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	पूर्णांक ddb = (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev;

	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, ATA_CMD_SCBPTR, 0xFFFF);
	अगर (dev->dev_type == SAS_SATA_DEV || dev->dev_type == SAS_SATA_PM ||
	    dev->dev_type == SAS_SATA_PM_PORT) अणु
		काष्ठा dev_to_host_fis *fis = (काष्ठा dev_to_host_fis *)
			dev->frame_rcvd;
		asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, SATA_STATUS, fis->status);
	पूर्ण
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, NCQ_DATA_SCB_PTR, 0xFFFF);

	वापस 0;
पूर्ण

अटल पूर्णांक asd_init_target_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक ddb, i;
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	u8 flags = 0;

	ddb = asd_get_ddb(asd_ha);
	अगर (ddb < 0)
		वापस ddb;

	dev->lldd_dev = (व्योम *) (अचिन्हित दीर्घ) ddb;

	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, 0, DDB_TP_CONN_TYPE);
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, 1, 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, INIT_CONN_TAG, 0xFFFF);
	क्रम (i = 0; i < SAS_ADDR_SIZE; i++)
		asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, DEST_SAS_ADDR+i,
				       dev->sas_addr[i]);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, SEND_QUEUE_HEAD, 0xFFFF);
	asd_set_ddb_type(dev);
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, CONN_MASK, dev->port->phy_mask);
	अगर (dev->port->oob_mode != SATA_OOB_MODE) अणु
		flags |= OPEN_REQUIRED;
		अगर ((dev->dev_type == SAS_SATA_DEV) ||
		    (dev->tproto & SAS_PROTOCOL_STP)) अणु
			काष्ठा smp_resp *rps_resp = &dev->sata_dev.rps_resp;
			अगर (rps_resp->frame_type == SMP_RESPONSE &&
			    rps_resp->function == SMP_REPORT_PHY_SATA &&
			    rps_resp->result == SMP_RESP_FUNC_ACC) अणु
				अगर (rps_resp->rps.affil_valid)
					flags |= STP_AFFIL_POL;
				अगर (rps_resp->rps.affil_supp)
					flags |= SUPPORTS_AFFIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			flags |= CONCURRENT_CONN_SUPP;
			अगर (!dev->parent && dev_is_expander(dev->dev_type))
				asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, MAX_CCONN,
						       4);
			अन्यथा
				asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, MAX_CCONN,
						       dev->pathways);
			asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, NUM_CTX, 1);
		पूर्ण
	पूर्ण
	अगर (dev->dev_type == SAS_SATA_PM)
		flags |= SATA_MULTIPORT;
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, DDB_TARG_FLAGS, flags);

	flags = 0;
	अगर (dev->tproto & SAS_PROTOCOL_STP)
		flags |= STP_CL_POL_NO_TX;
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, DDB_TARG_FLAGS2, flags);

	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, EXEC_QUEUE_TAIL, 0xFFFF);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, SEND_QUEUE_TAIL, 0xFFFF);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, SISTER_DDB, 0xFFFF);

	अगर (dev->dev_type == SAS_SATA_DEV || (dev->tproto & SAS_PROTOCOL_STP)) अणु
		i = asd_init_sata(dev);
		अगर (i < 0) अणु
			asd_मुक्त_ddb(asd_ha, ddb);
			वापस i;
		पूर्ण
	पूर्ण

	अगर (dev->dev_type == SAS_END_DEVICE) अणु
		काष्ठा sas_end_device *rdev = rphy_to_end_device(dev->rphy);
		अगर (rdev->I_T_nexus_loss_समयout > 0)
			asd_ddbsite_ग_लिखो_word(asd_ha, ddb, ITNL_TIMEOUT,
					       min(rdev->I_T_nexus_loss_समयout,
						   (u16)ITNL_TIMEOUT_CONST));
		अन्यथा
			asd_ddbsite_ग_लिखो_word(asd_ha, ddb, ITNL_TIMEOUT,
					       (u16)ITNL_TIMEOUT_CONST);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक asd_init_sata_pm_table_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	पूर्णांक ddb, i;

	ddb = asd_get_ddb(asd_ha);
	अगर (ddb < 0)
		वापस ddb;

	क्रम (i = 0; i < 32; i += 2)
		asd_ddbsite_ग_लिखो_word(asd_ha, ddb, i, 0xFFFF);

	asd_ddbsite_ग_लिखो_word(asd_ha, (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev,
			       SISTER_DDB, ddb);

	वापस 0;
पूर्ण

#घोषणा PM_PORT_FLAGS दुरत्व(काष्ठा asd_ddb_sata_pm_port, pm_port_flags)
#घोषणा PARENT_DDB    दुरत्व(काष्ठा asd_ddb_sata_pm_port, parent_ddb)

/**
 * asd_init_sata_pm_port_ddb -- SATA Port Multiplier Port
 * @dev: poपूर्णांकer to करोमुख्य device
 *
 * For SATA Port Multiplier Ports we need to allocate one SATA Port
 * Multiplier Port DDB and depending on whether the target on it
 * supports SATA II NCQ, one SATA Tag DDB.
 */
अटल पूर्णांक asd_init_sata_pm_port_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक ddb, i, parent_ddb, pmtable_ddb;
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	u8  flags;

	ddb = asd_get_ddb(asd_ha);
	अगर (ddb < 0)
		वापस ddb;

	asd_set_ddb_type(dev);
	flags = (dev->sata_dev.port_no << 4) | PM_PORT_SET;
	asd_ddbsite_ग_लिखो_byte(asd_ha, ddb, PM_PORT_FLAGS, flags);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, SISTER_DDB, 0xFFFF);
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, ATA_CMD_SCBPTR, 0xFFFF);
	asd_init_sata(dev);

	parent_ddb = (पूर्णांक) (अचिन्हित दीर्घ) dev->parent->lldd_dev;
	asd_ddbsite_ग_लिखो_word(asd_ha, ddb, PARENT_DDB, parent_ddb);
	pmtable_ddb = asd_ddbsite_पढ़ो_word(asd_ha, parent_ddb, SISTER_DDB);
	asd_ddbsite_ग_लिखो_word(asd_ha, pmtable_ddb, dev->sata_dev.port_no,ddb);

	अगर (asd_ddbsite_पढ़ो_byte(asd_ha, ddb, NUM_SATA_TAGS) > 0) अणु
		i = asd_init_sata_tag_ddb(dev);
		अगर (i < 0) अणु
			asd_मुक्त_ddb(asd_ha, ddb);
			वापस i;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक asd_init_initiator_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	वापस -ENODEV;
पूर्ण

/**
 * asd_init_sata_pm_ddb -- SATA Port Multiplier
 * @dev: poपूर्णांकer to करोमुख्य device
 *
 * For STP and direct-attached SATA Port Multipliers we need
 * one target port DDB entry and one SATA PM table DDB entry.
 */
अटल पूर्णांक asd_init_sata_pm_ddb(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res = 0;

	res = asd_init_target_ddb(dev);
	अगर (res)
		जाओ out;
	res = asd_init_sata_pm_table_ddb(dev);
	अगर (res)
		asd_मुक्त_ddb(dev->port->ha->lldd_ha,
			     (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev);
out:
	वापस res;
पूर्ण

पूर्णांक asd_dev_found(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res = 0;
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;

	spin_lock_irqsave(&asd_ha->hw_prof.ddb_lock, flags);
	चयन (dev->dev_type) अणु
	हाल SAS_SATA_PM:
		res = asd_init_sata_pm_ddb(dev);
		अवरोध;
	हाल SAS_SATA_PM_PORT:
		res = asd_init_sata_pm_port_ddb(dev);
		अवरोध;
	शेष:
		अगर (dev->tproto)
			res = asd_init_target_ddb(dev);
		अन्यथा
			res = asd_init_initiator_ddb(dev);
	पूर्ण
	spin_unlock_irqrestore(&asd_ha->hw_prof.ddb_lock, flags);

	वापस res;
पूर्ण

व्योम asd_dev_gone(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक ddb, sister_ddb;
	अचिन्हित दीर्घ flags;
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;

	spin_lock_irqsave(&asd_ha->hw_prof.ddb_lock, flags);
	ddb = (पूर्णांक) (अचिन्हित दीर्घ) dev->lldd_dev;
	sister_ddb = asd_ddbsite_पढ़ो_word(asd_ha, ddb, SISTER_DDB);

	अगर (sister_ddb != 0xFFFF)
		asd_मुक्त_ddb(asd_ha, sister_ddb);
	asd_मुक्त_ddb(asd_ha, ddb);
	dev->lldd_dev = शून्य;
	spin_unlock_irqrestore(&asd_ha->hw_prof.ddb_lock, flags);
पूर्ण
