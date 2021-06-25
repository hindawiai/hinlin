<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <target/target_core_base.h>
#समावेश <linux/btree.h>

/* length of ASCII WWPNs including pad */
#घोषणा TCM_QLA2XXX_NAMELEN	32
/*
 * Number of pre-allocated per-session tags, based upon the worst-हाल
 * per port number of iocbs
 */
#घोषणा TCM_QLA2XXX_DEFAULT_TAGS 2088

#समावेश "qla_target.h"

काष्ठा tcm_qla2xxx_nacl अणु
	काष्ठा se_node_acl se_node_acl;

	/* From libfc काष्ठा fc_rport->port_id */
	u32 nport_id;
	/* Binary World Wide unique Node Name क्रम remote FC Initiator Nport */
	u64 nport_wwnn;
	/* ASCII क्रमmatted WWPN क्रम FC Initiator Nport */
	अक्षर nport_name[TCM_QLA2XXX_NAMELEN];
	/* Poपूर्णांकer to fc_port */
	काष्ठा fc_port *fc_port;
	/* Poपूर्णांकer to TCM FC nexus */
	काष्ठा se_session *nport_nexus;
पूर्ण;

काष्ठा tcm_qla2xxx_tpg_attrib अणु
	पूर्णांक generate_node_acls;
	पूर्णांक cache_dynamic_acls;
	पूर्णांक demo_mode_ग_लिखो_protect;
	पूर्णांक prod_mode_ग_लिखो_protect;
	पूर्णांक demo_mode_login_only;
	पूर्णांक fabric_prot_type;
	पूर्णांक jam_host;
पूर्ण;

काष्ठा tcm_qla2xxx_tpg अणु
	/* FC lport target portal group tag क्रम TCM */
	u16 lport_tpgt;
	/* Atomic bit to determine TPG active status */
	atomic_t lport_tpg_enabled;
	/* Poपूर्णांकer back to tcm_qla2xxx_lport */
	काष्ठा tcm_qla2xxx_lport *lport;
	/* Used by tcm_qla2xxx_tpg_attrib_cit */
	काष्ठा tcm_qla2xxx_tpg_attrib tpg_attrib;
	/* Returned by tcm_qla2xxx_make_tpg() */
	काष्ठा se_portal_group se_tpg;
पूर्ण;

काष्ठा tcm_qla2xxx_fc_loopid अणु
	काष्ठा se_node_acl *se_nacl;
पूर्ण;

काष्ठा tcm_qla2xxx_lport अणु
	/* Binary World Wide unique Port Name क्रम FC Target Lport */
	u64 lport_wwpn;
	/* Binary World Wide unique Port Name क्रम FC NPIV Target Lport */
	u64 lport_npiv_wwpn;
	/* Binary World Wide unique Node Name क्रम FC NPIV Target Lport */
	u64 lport_npiv_wwnn;
	/* ASCII क्रमmatted WWPN क्रम FC Target Lport */
	अक्षर lport_name[TCM_QLA2XXX_NAMELEN];
	/* ASCII क्रमmatted naa WWPN क्रम VPD page 83 etc */
	अक्षर lport_naa_name[TCM_QLA2XXX_NAMELEN];
	/* map क्रम fc_port poपूर्णांकers in 24-bit FC Port ID space */
	काष्ठा btree_head32 lport_fcport_map;
	/* vदो_स्मृति-ed memory क्रम fc_port poपूर्णांकers क्रम 16-bit FC loop ID */
	काष्ठा tcm_qla2xxx_fc_loopid *lport_loopid_map;
	/* Poपूर्णांकer to काष्ठा scsi_qla_host from qla2xxx LLD */
	काष्ठा scsi_qla_host *qla_vha;
	/* Poपूर्णांकer to काष्ठा qla_tgt poपूर्णांकer */
	काष्ठा qla_tgt lport_qla_tgt;
	/* Poपूर्णांकer to TPG=1 क्रम non NPIV mode */
	काष्ठा tcm_qla2xxx_tpg *tpg_1;
	/* Returned by tcm_qla2xxx_make_lport() */
	काष्ठा se_wwn lport_wwn;
पूर्ण;
