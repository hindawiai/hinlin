<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <target/target_core_base.h> /* काष्ठा se_cmd */

#घोषणा TCM_LOOP_VERSION		"v2.1-rc2"
#घोषणा TL_WWN_ADDR_LEN			256
#घोषणा TL_TPGS_PER_HBA			32

काष्ठा tcm_loop_cmd अणु
	/* State of Linux/SCSI CDB+Data descriptor */
	u32 sc_cmd_state;
	/* Tagged command queueing */
	u32 sc_cmd_tag;
	/* Poपूर्णांकer to the CDB+Data descriptor from Linux/SCSI subप्रणाली */
	काष्ठा scsi_cmnd *sc;
	/* The TCM I/O descriptor that is accessed via container_of() */
	काष्ठा se_cmd tl_se_cmd;
	काष्ठा completion पंचांगr_करोne;
	/* Sense buffer that will be mapped पूर्णांकo outgoing status */
	अचिन्हित अक्षर tl_sense_buf[TRANSPORT_SENSE_BUFFER];
पूर्ण;

काष्ठा tcm_loop_nexus अणु
	/*
	 * Poपूर्णांकer to TCM session क्रम I_T Nexus
	 */
	काष्ठा se_session *se_sess;
पूर्ण;

#घोषणा TCM_TRANSPORT_ONLINE 0
#घोषणा TCM_TRANSPORT_OFFLINE 1

काष्ठा tcm_loop_tpg अणु
	अचिन्हित लघु tl_tpgt;
	अचिन्हित लघु tl_transport_status;
	क्रमागत target_prot_type tl_fabric_prot_type;
	atomic_t tl_tpg_port_count;
	काष्ठा se_portal_group tl_se_tpg;
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_nexus *tl_nexus;
पूर्ण;

काष्ठा tcm_loop_hba अणु
	u8 tl_proto_id;
	अचिन्हित अक्षर tl_wwn_address[TL_WWN_ADDR_LEN];
	काष्ठा se_hba_s *se_hba;
	काष्ठा se_lun *tl_hba_lun;
	काष्ठा se_port *tl_hba_lun_sep;
	काष्ठा device dev;
	काष्ठा Scsi_Host *sh;
	काष्ठा tcm_loop_tpg tl_hba_tpgs[TL_TPGS_PER_HBA];
	काष्ठा se_wwn tl_hba_wwn;
पूर्ण;
