<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_REG_H
#घोषणा _MLXSW_REG_H

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "item.h"
#समावेश "port.h"

काष्ठा mlxsw_reg_info अणु
	u16 id;
	u16 len; /* In u8 */
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा MLXSW_REG_DEFINE(_name, _id, _len)				\
अटल स्थिर काष्ठा mlxsw_reg_info mlxsw_reg_##_name = अणु		\
	.id = _id,							\
	.len = _len,							\
	.name = #_name,							\
पूर्ण

#घोषणा MLXSW_REG(type) (&mlxsw_reg_##type)
#घोषणा MLXSW_REG_LEN(type) MLXSW_REG(type)->len
#घोषणा MLXSW_REG_ZERO(type, payload) स_रखो(payload, 0, MLXSW_REG(type)->len)

/* SGCR - Switch General Configuration Register
 * --------------------------------------------
 * This रेजिस्टर is used क्रम configuration of the चयन capabilities.
 */
#घोषणा MLXSW_REG_SGCR_ID 0x2000
#घोषणा MLXSW_REG_SGCR_LEN 0x10

MLXSW_REG_DEFINE(sgcr, MLXSW_REG_SGCR_ID, MLXSW_REG_SGCR_LEN);

/* reg_sgcr_llb
 * Link Local Broadcast (Default=0)
 * When set, all Link Local packets (224.0.0.X) will be treated as broadcast
 * packets and ignore the IGMP snooping entries.
 * Access: RW
 */
MLXSW_ITEM32(reg, sgcr, llb, 0x04, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_sgcr_pack(अक्षर *payload, bool llb)
अणु
	MLXSW_REG_ZERO(sgcr, payload);
	mlxsw_reg_sgcr_llb_set(payload, !!llb);
पूर्ण

/* SPAD - Switch Physical Address Register
 * ---------------------------------------
 * The SPAD रेजिस्टर configures the चयन physical MAC address.
 */
#घोषणा MLXSW_REG_SPAD_ID 0x2002
#घोषणा MLXSW_REG_SPAD_LEN 0x10

MLXSW_REG_DEFINE(spad, MLXSW_REG_SPAD_ID, MLXSW_REG_SPAD_LEN);

/* reg_spad_base_mac
 * Base MAC address क्रम the चयन partitions.
 * Per चयन partition MAC address is equal to:
 * base_mac + swid
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, spad, base_mac, 0x02, 6);

/* SMID - Switch Multicast ID
 * --------------------------
 * The MID record maps from a MID (Multicast ID), which is a unique identअगरier
 * of the multicast group within the stacking करोमुख्य, पूर्णांकo a list of local
 * ports पूर्णांकo which the packet is replicated.
 */
#घोषणा MLXSW_REG_SMID_ID 0x2007
#घोषणा MLXSW_REG_SMID_LEN 0x240

MLXSW_REG_DEFINE(smid, MLXSW_REG_SMID_ID, MLXSW_REG_SMID_LEN);

/* reg_smid_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, smid, swid, 0x00, 24, 8);

/* reg_smid_mid
 * Multicast identअगरier - global identअगरier that represents the multicast group
 * across all devices.
 * Access: Index
 */
MLXSW_ITEM32(reg, smid, mid, 0x00, 0, 16);

/* reg_smid_port
 * Local port memebership (1 bit per port).
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, smid, port, 0x20, 0x20, 1);

/* reg_smid_port_mask
 * Local port mask (1 bit per port).
 * Access: W
 */
MLXSW_ITEM_BIT_ARRAY(reg, smid, port_mask, 0x220, 0x20, 1);

अटल अंतरभूत व्योम mlxsw_reg_smid_pack(अक्षर *payload, u16 mid,
				       u8 port, bool set)
अणु
	MLXSW_REG_ZERO(smid, payload);
	mlxsw_reg_smid_swid_set(payload, 0);
	mlxsw_reg_smid_mid_set(payload, mid);
	mlxsw_reg_smid_port_set(payload, port, set);
	mlxsw_reg_smid_port_mask_set(payload, port, 1);
पूर्ण

/* SSPR - Switch System Port Record Register
 * -----------------------------------------
 * Configures the प्रणाली port to local port mapping.
 */
#घोषणा MLXSW_REG_SSPR_ID 0x2008
#घोषणा MLXSW_REG_SSPR_LEN 0x8

MLXSW_REG_DEFINE(sspr, MLXSW_REG_SSPR_ID, MLXSW_REG_SSPR_LEN);

/* reg_sspr_m
 * Master - अगर set, then the record describes the master प्रणाली port.
 * This is needed in हाल a local port is mapped पूर्णांकo several प्रणाली ports
 * (क्रम multipathing). That number will be reported as the source प्रणाली
 * port when packets are क्रमwarded to the CPU. Only one master port is allowed
 * per local port.
 *
 * Note: Must be set क्रम Spectrum.
 * Access: RW
 */
MLXSW_ITEM32(reg, sspr, m, 0x00, 31, 1);

/* reg_sspr_local_port
 * Local port number.
 *
 * Access: RW
 */
MLXSW_ITEM32(reg, sspr, local_port, 0x00, 16, 8);

/* reg_sspr_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 *
 * Access: RW
 */
MLXSW_ITEM32(reg, sspr, sub_port, 0x00, 8, 8);

/* reg_sspr_प्रणाली_port
 * Unique identअगरier within the stacking करोमुख्य that represents all the ports
 * that are available in the प्रणाली (बाह्यal ports).
 *
 * Currently, only single-ASIC configurations are supported, so we शेष to
 * 1:1 mapping between प्रणाली ports and local ports.
 * Access: Index
 */
MLXSW_ITEM32(reg, sspr, प्रणाली_port, 0x04, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_sspr_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(sspr, payload);
	mlxsw_reg_sspr_m_set(payload, 1);
	mlxsw_reg_sspr_local_port_set(payload, local_port);
	mlxsw_reg_sspr_sub_port_set(payload, 0);
	mlxsw_reg_sspr_प्रणाली_port_set(payload, local_port);
पूर्ण

/* SFDAT - Switch Filtering Database Aging Time
 * --------------------------------------------
 * Controls the Switch aging समय. Aging समय is able to be set per Switch
 * Partition.
 */
#घोषणा MLXSW_REG_SFDAT_ID 0x2009
#घोषणा MLXSW_REG_SFDAT_LEN 0x8

MLXSW_REG_DEFINE(sfdat, MLXSW_REG_SFDAT_ID, MLXSW_REG_SFDAT_LEN);

/* reg_sfdat_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfdat, swid, 0x00, 24, 8);

/* reg_sfdat_age_समय
 * Aging समय in seconds
 * Min - 10 seconds
 * Max - 1,000,000 seconds
 * Default is 300 seconds.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdat, age_समय, 0x04, 0, 20);

अटल अंतरभूत व्योम mlxsw_reg_sfdat_pack(अक्षर *payload, u32 age_समय)
अणु
	MLXSW_REG_ZERO(sfdat, payload);
	mlxsw_reg_sfdat_swid_set(payload, 0);
	mlxsw_reg_sfdat_age_समय_set(payload, age_समय);
पूर्ण

/* SFD - Switch Filtering Database
 * -------------------------------
 * The following रेजिस्टर defines the access to the filtering database.
 * The रेजिस्टर supports querying, adding, removing and modअगरying the database.
 * The access is optimized क्रम bulk updates in which हाल more than one
 * FDB record is present in the same command.
 */
#घोषणा MLXSW_REG_SFD_ID 0x200A
#घोषणा MLXSW_REG_SFD_BASE_LEN 0x10 /* base length, without records */
#घोषणा MLXSW_REG_SFD_REC_LEN 0x10 /* record length */
#घोषणा MLXSW_REG_SFD_REC_MAX_COUNT 64
#घोषणा MLXSW_REG_SFD_LEN (MLXSW_REG_SFD_BASE_LEN +	\
			   MLXSW_REG_SFD_REC_LEN * MLXSW_REG_SFD_REC_MAX_COUNT)

MLXSW_REG_DEFINE(sfd, MLXSW_REG_SFD_ID, MLXSW_REG_SFD_LEN);

/* reg_sfd_swid
 * Switch partition ID क्रम queries. Reserved on Write.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfd, swid, 0x00, 24, 8);

क्रमागत mlxsw_reg_sfd_op अणु
	/* Dump entire FDB a (process according to record_locator) */
	MLXSW_REG_SFD_OP_QUERY_DUMP = 0,
	/* Query records by अणुMAC, VID/FIDपूर्ण value */
	MLXSW_REG_SFD_OP_QUERY_QUERY = 1,
	/* Query and clear activity. Query records by अणुMAC, VID/FIDपूर्ण value */
	MLXSW_REG_SFD_OP_QUERY_QUERY_AND_CLEAR_ACTIVITY = 2,
	/* Test. Response indicates अगर each of the records could be
	 * added to the FDB.
	 */
	MLXSW_REG_SFD_OP_WRITE_TEST = 0,
	/* Add/modअगरy. Aged-out records cannot be added. This command हटाओs
	 * the learning notअगरication of the अणुMAC, VID/FIDपूर्ण. Response includes
	 * the entries that were added to the FDB.
	 */
	MLXSW_REG_SFD_OP_WRITE_EDIT = 1,
	/* Remove record by अणुMAC, VID/FIDपूर्ण. This command also हटाओs
	 * the learning notअगरication and aged-out notअगरications
	 * of the अणुMAC, VID/FIDपूर्ण. The response provides current (pre-removal)
	 * entries as non-aged-out.
	 */
	MLXSW_REG_SFD_OP_WRITE_REMOVE = 2,
	/* Remove learned notअगरication by अणुMAC, VID/FIDपूर्ण. The response provides
	 * the हटाओd learning notअगरication.
	 */
	MLXSW_REG_SFD_OP_WRITE_REMOVE_NOTIFICATION = 2,
पूर्ण;

/* reg_sfd_op
 * Operation.
 * Access: OP
 */
MLXSW_ITEM32(reg, sfd, op, 0x04, 30, 2);

/* reg_sfd_record_locator
 * Used क्रम querying the FDB. Use record_locator=0 to initiate the
 * query. When a record is वापसed, a new record_locator is
 * वापसed to be used in the subsequent query.
 * Reserved क्रम database update.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfd, record_locator, 0x04, 0, 30);

/* reg_sfd_num_rec
 * Request: Number of records to पढ़ो/add/modअगरy/हटाओ
 * Response: Number of records पढ़ो/added/replaced/हटाओd
 * See above description क्रम more details.
 * Ranges 0..64
 * Access: RW
 */
MLXSW_ITEM32(reg, sfd, num_rec, 0x08, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_sfd_pack(अक्षर *payload, क्रमागत mlxsw_reg_sfd_op op,
				      u32 record_locator)
अणु
	MLXSW_REG_ZERO(sfd, payload);
	mlxsw_reg_sfd_op_set(payload, op);
	mlxsw_reg_sfd_record_locator_set(payload, record_locator);
पूर्ण

/* reg_sfd_rec_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, sfd, rec_swid, MLXSW_REG_SFD_BASE_LEN, 24, 8,
		     MLXSW_REG_SFD_REC_LEN, 0x00, false);

क्रमागत mlxsw_reg_sfd_rec_type अणु
	MLXSW_REG_SFD_REC_TYPE_UNICAST = 0x0,
	MLXSW_REG_SFD_REC_TYPE_UNICAST_LAG = 0x1,
	MLXSW_REG_SFD_REC_TYPE_MULTICAST = 0x2,
	MLXSW_REG_SFD_REC_TYPE_UNICAST_TUNNEL = 0xC,
पूर्ण;

/* reg_sfd_rec_type
 * FDB record type.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, rec_type, MLXSW_REG_SFD_BASE_LEN, 20, 4,
		     MLXSW_REG_SFD_REC_LEN, 0x00, false);

क्रमागत mlxsw_reg_sfd_rec_policy अणु
	/* Replacement disabled, aging disabled. */
	MLXSW_REG_SFD_REC_POLICY_STATIC_ENTRY = 0,
	/* (mlag remote): Replacement enabled, aging disabled,
	 * learning notअगरication enabled on this port.
	 */
	MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_MLAG = 1,
	/* (ingress device): Replacement enabled, aging enabled. */
	MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_INGRESS = 3,
पूर्ण;

/* reg_sfd_rec_policy
 * Policy.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, rec_policy, MLXSW_REG_SFD_BASE_LEN, 18, 2,
		     MLXSW_REG_SFD_REC_LEN, 0x00, false);

/* reg_sfd_rec_a
 * Activity. Set क्रम new अटल entries. Set क्रम अटल entries अगर a frame SMAC
 * lookup hits on the entry.
 * To clear the a bit, use "query and clear activity" op.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfd, rec_a, MLXSW_REG_SFD_BASE_LEN, 16, 1,
		     MLXSW_REG_SFD_REC_LEN, 0x00, false);

/* reg_sfd_rec_mac
 * MAC address.
 * Access: Index
 */
MLXSW_ITEM_BUF_INDEXED(reg, sfd, rec_mac, MLXSW_REG_SFD_BASE_LEN, 6,
		       MLXSW_REG_SFD_REC_LEN, 0x02);

क्रमागत mlxsw_reg_sfd_rec_action अणु
	/* क्रमward */
	MLXSW_REG_SFD_REC_ACTION_NOP = 0,
	/* क्रमward and trap, trap_id is FDB_TRAP */
	MLXSW_REG_SFD_REC_ACTION_MIRROR_TO_CPU = 1,
	/* trap and करो not क्रमward, trap_id is FDB_TRAP */
	MLXSW_REG_SFD_REC_ACTION_TRAP = 2,
	/* क्रमward to IP router */
	MLXSW_REG_SFD_REC_ACTION_FORWARD_IP_ROUTER = 3,
	MLXSW_REG_SFD_REC_ACTION_DISCARD_ERROR = 15,
पूर्ण;

/* reg_sfd_rec_action
 * Action to apply on the packet.
 * Note: Dynamic entries can only be configured with NOP action.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, rec_action, MLXSW_REG_SFD_BASE_LEN, 28, 4,
		     MLXSW_REG_SFD_REC_LEN, 0x0C, false);

/* reg_sfd_uc_sub_port
 * VEPA channel on local port.
 * Valid only अगर local port is a non-stacking port. Must be 0 अगर multichannel
 * VEPA is not enabled.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_sub_port, MLXSW_REG_SFD_BASE_LEN, 16, 8,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_uc_fid_vid
 * Filtering ID or VLAN ID
 * For SwitchX and SwitchX-2:
 * - Dynamic entries (policy 2,3) use FID
 * - Static entries (policy 0) use VID
 * - When independent learning is configured, VID=FID
 * For Spectrum: use FID क्रम both Dynamic and Static entries.
 * VID should not be used.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_fid_vid, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_uc_प्रणाली_port
 * Unique port identअगरier क्रम the final destination of the packet.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_प्रणाली_port, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम mlxsw_reg_sfd_rec_pack(अक्षर *payload, पूर्णांक rec_index,
					  क्रमागत mlxsw_reg_sfd_rec_type rec_type,
					  स्थिर अक्षर *mac,
					  क्रमागत mlxsw_reg_sfd_rec_action action)
अणु
	u8 num_rec = mlxsw_reg_sfd_num_rec_get(payload);

	अगर (rec_index >= num_rec)
		mlxsw_reg_sfd_num_rec_set(payload, rec_index + 1);
	mlxsw_reg_sfd_rec_swid_set(payload, rec_index, 0);
	mlxsw_reg_sfd_rec_type_set(payload, rec_index, rec_type);
	mlxsw_reg_sfd_rec_mac_स_नकल_to(payload, rec_index, mac);
	mlxsw_reg_sfd_rec_action_set(payload, rec_index, action);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sfd_uc_pack(अक्षर *payload, पूर्णांक rec_index,
					 क्रमागत mlxsw_reg_sfd_rec_policy policy,
					 स्थिर अक्षर *mac, u16 fid_vid,
					 क्रमागत mlxsw_reg_sfd_rec_action action,
					 u8 local_port)
अणु
	mlxsw_reg_sfd_rec_pack(payload, rec_index,
			       MLXSW_REG_SFD_REC_TYPE_UNICAST, mac, action);
	mlxsw_reg_sfd_rec_policy_set(payload, rec_index, policy);
	mlxsw_reg_sfd_uc_sub_port_set(payload, rec_index, 0);
	mlxsw_reg_sfd_uc_fid_vid_set(payload, rec_index, fid_vid);
	mlxsw_reg_sfd_uc_प्रणाली_port_set(payload, rec_index, local_port);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sfd_uc_unpack(अक्षर *payload, पूर्णांक rec_index,
					   अक्षर *mac, u16 *p_fid_vid,
					   u8 *p_local_port)
अणु
	mlxsw_reg_sfd_rec_mac_स_नकल_from(payload, rec_index, mac);
	*p_fid_vid = mlxsw_reg_sfd_uc_fid_vid_get(payload, rec_index);
	*p_local_port = mlxsw_reg_sfd_uc_प्रणाली_port_get(payload, rec_index);
पूर्ण

/* reg_sfd_uc_lag_sub_port
 * LAG sub port.
 * Must be 0 अगर multichannel VEPA is not enabled.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_lag_sub_port, MLXSW_REG_SFD_BASE_LEN, 16, 8,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_uc_lag_fid_vid
 * Filtering ID or VLAN ID
 * For SwitchX and SwitchX-2:
 * - Dynamic entries (policy 2,3) use FID
 * - Static entries (policy 0) use VID
 * - When independent learning is configured, VID=FID
 * For Spectrum: use FID क्रम both Dynamic and Static entries.
 * VID should not be used.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_lag_fid_vid, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_uc_lag_lag_vid
 * Indicates VID in हाल of vFIDs. Reserved क्रम FIDs.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_lag_lag_vid, MLXSW_REG_SFD_BASE_LEN, 16, 12,
		     MLXSW_REG_SFD_REC_LEN, 0x0C, false);

/* reg_sfd_uc_lag_lag_id
 * LAG Identअगरier - poपूर्णांकer पूर्णांकo the LAG descriptor table.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_lag_lag_id, MLXSW_REG_SFD_BASE_LEN, 0, 10,
		     MLXSW_REG_SFD_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम
mlxsw_reg_sfd_uc_lag_pack(अक्षर *payload, पूर्णांक rec_index,
			  क्रमागत mlxsw_reg_sfd_rec_policy policy,
			  स्थिर अक्षर *mac, u16 fid_vid,
			  क्रमागत mlxsw_reg_sfd_rec_action action, u16 lag_vid,
			  u16 lag_id)
अणु
	mlxsw_reg_sfd_rec_pack(payload, rec_index,
			       MLXSW_REG_SFD_REC_TYPE_UNICAST_LAG,
			       mac, action);
	mlxsw_reg_sfd_rec_policy_set(payload, rec_index, policy);
	mlxsw_reg_sfd_uc_lag_sub_port_set(payload, rec_index, 0);
	mlxsw_reg_sfd_uc_lag_fid_vid_set(payload, rec_index, fid_vid);
	mlxsw_reg_sfd_uc_lag_lag_vid_set(payload, rec_index, lag_vid);
	mlxsw_reg_sfd_uc_lag_lag_id_set(payload, rec_index, lag_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sfd_uc_lag_unpack(अक्षर *payload, पूर्णांक rec_index,
					       अक्षर *mac, u16 *p_vid,
					       u16 *p_lag_id)
अणु
	mlxsw_reg_sfd_rec_mac_स_नकल_from(payload, rec_index, mac);
	*p_vid = mlxsw_reg_sfd_uc_lag_fid_vid_get(payload, rec_index);
	*p_lag_id = mlxsw_reg_sfd_uc_lag_lag_id_get(payload, rec_index);
पूर्ण

/* reg_sfd_mc_pgi
 *
 * Multicast port group index - index पूर्णांकo the port group table.
 * Value 0x1FFF indicates the pgi should poपूर्णांक to the MID entry.
 * For Spectrum this value must be set to 0x1FFF
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, mc_pgi, MLXSW_REG_SFD_BASE_LEN, 16, 13,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_mc_fid_vid
 *
 * Filtering ID or VLAN ID
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, sfd, mc_fid_vid, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_mc_mid
 *
 * Multicast identअगरier - global identअगरier that represents the multicast
 * group across all devices.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, mc_mid, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम
mlxsw_reg_sfd_mc_pack(अक्षर *payload, पूर्णांक rec_index,
		      स्थिर अक्षर *mac, u16 fid_vid,
		      क्रमागत mlxsw_reg_sfd_rec_action action, u16 mid)
अणु
	mlxsw_reg_sfd_rec_pack(payload, rec_index,
			       MLXSW_REG_SFD_REC_TYPE_MULTICAST, mac, action);
	mlxsw_reg_sfd_mc_pgi_set(payload, rec_index, 0x1FFF);
	mlxsw_reg_sfd_mc_fid_vid_set(payload, rec_index, fid_vid);
	mlxsw_reg_sfd_mc_mid_set(payload, rec_index, mid);
पूर्ण

/* reg_sfd_uc_tunnel_uip_msb
 * When protocol is IPv4, the most signअगरicant byte of the underlay IPv4
 * destination IP.
 * When protocol is IPv6, reserved.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_tunnel_uip_msb, MLXSW_REG_SFD_BASE_LEN, 24,
		     8, MLXSW_REG_SFD_REC_LEN, 0x08, false);

/* reg_sfd_uc_tunnel_fid
 * Filtering ID.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_tunnel_fid, MLXSW_REG_SFD_BASE_LEN, 0, 16,
		     MLXSW_REG_SFD_REC_LEN, 0x08, false);

क्रमागत mlxsw_reg_sfd_uc_tunnel_protocol अणु
	MLXSW_REG_SFD_UC_TUNNEL_PROTOCOL_IPV4,
	MLXSW_REG_SFD_UC_TUNNEL_PROTOCOL_IPV6,
पूर्ण;

/* reg_sfd_uc_tunnel_protocol
 * IP protocol.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_tunnel_protocol, MLXSW_REG_SFD_BASE_LEN, 27,
		     1, MLXSW_REG_SFD_REC_LEN, 0x0C, false);

/* reg_sfd_uc_tunnel_uip_lsb
 * When protocol is IPv4, the least signअगरicant bytes of the underlay
 * IPv4 destination IP.
 * When protocol is IPv6, poपूर्णांकer to the underlay IPv6 destination IP
 * which is configured by RIPS.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sfd, uc_tunnel_uip_lsb, MLXSW_REG_SFD_BASE_LEN, 0,
		     24, MLXSW_REG_SFD_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम
mlxsw_reg_sfd_uc_tunnel_pack(अक्षर *payload, पूर्णांक rec_index,
			     क्रमागत mlxsw_reg_sfd_rec_policy policy,
			     स्थिर अक्षर *mac, u16 fid,
			     क्रमागत mlxsw_reg_sfd_rec_action action, u32 uip,
			     क्रमागत mlxsw_reg_sfd_uc_tunnel_protocol proto)
अणु
	mlxsw_reg_sfd_rec_pack(payload, rec_index,
			       MLXSW_REG_SFD_REC_TYPE_UNICAST_TUNNEL, mac,
			       action);
	mlxsw_reg_sfd_rec_policy_set(payload, rec_index, policy);
	mlxsw_reg_sfd_uc_tunnel_uip_msb_set(payload, rec_index, uip >> 24);
	mlxsw_reg_sfd_uc_tunnel_uip_lsb_set(payload, rec_index, uip);
	mlxsw_reg_sfd_uc_tunnel_fid_set(payload, rec_index, fid);
	mlxsw_reg_sfd_uc_tunnel_protocol_set(payload, rec_index, proto);
पूर्ण

क्रमागत mlxsw_reg_tunnel_port अणु
	MLXSW_REG_TUNNEL_PORT_NVE,
	MLXSW_REG_TUNNEL_PORT_VPLS,
	MLXSW_REG_TUNNEL_PORT_FLEX_TUNNEL0,
	MLXSW_REG_TUNNEL_PORT_FLEX_TUNNEL1,
पूर्ण;

/* SFN - Switch FDB Notअगरication Register
 * -------------------------------------------
 * The चयन provides notअगरications on newly learned FDB entries and
 * aged out entries. The notअगरications can be polled by software.
 */
#घोषणा MLXSW_REG_SFN_ID 0x200B
#घोषणा MLXSW_REG_SFN_BASE_LEN 0x10 /* base length, without records */
#घोषणा MLXSW_REG_SFN_REC_LEN 0x10 /* record length */
#घोषणा MLXSW_REG_SFN_REC_MAX_COUNT 64
#घोषणा MLXSW_REG_SFN_LEN (MLXSW_REG_SFN_BASE_LEN +	\
			   MLXSW_REG_SFN_REC_LEN * MLXSW_REG_SFN_REC_MAX_COUNT)

MLXSW_REG_DEFINE(sfn, MLXSW_REG_SFN_ID, MLXSW_REG_SFN_LEN);

/* reg_sfn_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfn, swid, 0x00, 24, 8);

/* reg_sfn_end
 * Forces the current session to end.
 * Access: OP
 */
MLXSW_ITEM32(reg, sfn, end, 0x04, 20, 1);

/* reg_sfn_num_rec
 * Request: Number of learned notअगरications and aged-out notअगरication
 * records requested.
 * Response: Number of notअगरication records वापसed (must be smaller
 * than or equal to the value requested)
 * Ranges 0..64
 * Access: OP
 */
MLXSW_ITEM32(reg, sfn, num_rec, 0x04, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_sfn_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(sfn, payload);
	mlxsw_reg_sfn_swid_set(payload, 0);
	mlxsw_reg_sfn_end_set(payload, 0);
	mlxsw_reg_sfn_num_rec_set(payload, MLXSW_REG_SFN_REC_MAX_COUNT);
पूर्ण

/* reg_sfn_rec_swid
 * Switch partition ID.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, rec_swid, MLXSW_REG_SFN_BASE_LEN, 24, 8,
		     MLXSW_REG_SFN_REC_LEN, 0x00, false);

क्रमागत mlxsw_reg_sfn_rec_type अणु
	/* MAC addresses learned on a regular port. */
	MLXSW_REG_SFN_REC_TYPE_LEARNED_MAC = 0x5,
	/* MAC addresses learned on a LAG port. */
	MLXSW_REG_SFN_REC_TYPE_LEARNED_MAC_LAG = 0x6,
	/* Aged-out MAC address on a regular port. */
	MLXSW_REG_SFN_REC_TYPE_AGED_OUT_MAC = 0x7,
	/* Aged-out MAC address on a LAG port. */
	MLXSW_REG_SFN_REC_TYPE_AGED_OUT_MAC_LAG = 0x8,
	/* Learned unicast tunnel record. */
	MLXSW_REG_SFN_REC_TYPE_LEARNED_UNICAST_TUNNEL = 0xD,
	/* Aged-out unicast tunnel record. */
	MLXSW_REG_SFN_REC_TYPE_AGED_OUT_UNICAST_TUNNEL = 0xE,
पूर्ण;

/* reg_sfn_rec_type
 * Notअगरication record type.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, rec_type, MLXSW_REG_SFN_BASE_LEN, 20, 4,
		     MLXSW_REG_SFN_REC_LEN, 0x00, false);

/* reg_sfn_rec_mac
 * MAC address.
 * Access: RO
 */
MLXSW_ITEM_BUF_INDEXED(reg, sfn, rec_mac, MLXSW_REG_SFN_BASE_LEN, 6,
		       MLXSW_REG_SFN_REC_LEN, 0x02);

/* reg_sfn_mac_sub_port
 * VEPA channel on the local port.
 * 0 अगर multichannel VEPA is not enabled.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, mac_sub_port, MLXSW_REG_SFN_BASE_LEN, 16, 8,
		     MLXSW_REG_SFN_REC_LEN, 0x08, false);

/* reg_sfn_mac_fid
 * Filtering identअगरier.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, mac_fid, MLXSW_REG_SFN_BASE_LEN, 0, 16,
		     MLXSW_REG_SFN_REC_LEN, 0x08, false);

/* reg_sfn_mac_प्रणाली_port
 * Unique port identअगरier क्रम the final destination of the packet.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, mac_प्रणाली_port, MLXSW_REG_SFN_BASE_LEN, 0, 16,
		     MLXSW_REG_SFN_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम mlxsw_reg_sfn_mac_unpack(अक्षर *payload, पूर्णांक rec_index,
					    अक्षर *mac, u16 *p_vid,
					    u8 *p_local_port)
अणु
	mlxsw_reg_sfn_rec_mac_स_नकल_from(payload, rec_index, mac);
	*p_vid = mlxsw_reg_sfn_mac_fid_get(payload, rec_index);
	*p_local_port = mlxsw_reg_sfn_mac_प्रणाली_port_get(payload, rec_index);
पूर्ण

/* reg_sfn_mac_lag_lag_id
 * LAG ID (poपूर्णांकer पूर्णांकo the LAG descriptor table).
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, mac_lag_lag_id, MLXSW_REG_SFN_BASE_LEN, 0, 10,
		     MLXSW_REG_SFN_REC_LEN, 0x0C, false);

अटल अंतरभूत व्योम mlxsw_reg_sfn_mac_lag_unpack(अक्षर *payload, पूर्णांक rec_index,
						अक्षर *mac, u16 *p_vid,
						u16 *p_lag_id)
अणु
	mlxsw_reg_sfn_rec_mac_स_नकल_from(payload, rec_index, mac);
	*p_vid = mlxsw_reg_sfn_mac_fid_get(payload, rec_index);
	*p_lag_id = mlxsw_reg_sfn_mac_lag_lag_id_get(payload, rec_index);
पूर्ण

/* reg_sfn_uc_tunnel_uip_msb
 * When protocol is IPv4, the most signअगरicant byte of the underlay IPv4
 * address of the remote VTEP.
 * When protocol is IPv6, reserved.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, uc_tunnel_uip_msb, MLXSW_REG_SFN_BASE_LEN, 24,
		     8, MLXSW_REG_SFN_REC_LEN, 0x08, false);

क्रमागत mlxsw_reg_sfn_uc_tunnel_protocol अणु
	MLXSW_REG_SFN_UC_TUNNEL_PROTOCOL_IPV4,
	MLXSW_REG_SFN_UC_TUNNEL_PROTOCOL_IPV6,
पूर्ण;

/* reg_sfn_uc_tunnel_protocol
 * IP protocol.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, uc_tunnel_protocol, MLXSW_REG_SFN_BASE_LEN, 27,
		     1, MLXSW_REG_SFN_REC_LEN, 0x0C, false);

/* reg_sfn_uc_tunnel_uip_lsb
 * When protocol is IPv4, the least signअगरicant bytes of the underlay
 * IPv4 address of the remote VTEP.
 * When protocol is IPv6, ipv6_id to be queried from TNIPSD.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, uc_tunnel_uip_lsb, MLXSW_REG_SFN_BASE_LEN, 0,
		     24, MLXSW_REG_SFN_REC_LEN, 0x0C, false);

/* reg_sfn_uc_tunnel_port
 * Tunnel port.
 * Reserved on Spectrum.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sfn, tunnel_port, MLXSW_REG_SFN_BASE_LEN, 0, 4,
		     MLXSW_REG_SFN_REC_LEN, 0x10, false);

अटल अंतरभूत व्योम
mlxsw_reg_sfn_uc_tunnel_unpack(अक्षर *payload, पूर्णांक rec_index, अक्षर *mac,
			       u16 *p_fid, u32 *p_uip,
			       क्रमागत mlxsw_reg_sfn_uc_tunnel_protocol *p_proto)
अणु
	u32 uip_msb, uip_lsb;

	mlxsw_reg_sfn_rec_mac_स_नकल_from(payload, rec_index, mac);
	*p_fid = mlxsw_reg_sfn_mac_fid_get(payload, rec_index);
	uip_msb = mlxsw_reg_sfn_uc_tunnel_uip_msb_get(payload, rec_index);
	uip_lsb = mlxsw_reg_sfn_uc_tunnel_uip_lsb_get(payload, rec_index);
	*p_uip = uip_msb << 24 | uip_lsb;
	*p_proto = mlxsw_reg_sfn_uc_tunnel_protocol_get(payload, rec_index);
पूर्ण

/* SPMS - Switch Port MSTP/RSTP State Register
 * -------------------------------------------
 * Configures the spanning tree state of a physical port.
 */
#घोषणा MLXSW_REG_SPMS_ID 0x200D
#घोषणा MLXSW_REG_SPMS_LEN 0x404

MLXSW_REG_DEFINE(spms, MLXSW_REG_SPMS_ID, MLXSW_REG_SPMS_LEN);

/* reg_spms_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, spms, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_spms_state अणु
	MLXSW_REG_SPMS_STATE_NO_CHANGE,
	MLXSW_REG_SPMS_STATE_DISCARDING,
	MLXSW_REG_SPMS_STATE_LEARNING,
	MLXSW_REG_SPMS_STATE_FORWARDING,
पूर्ण;

/* reg_spms_state
 * Spanning tree state of each VLAN ID (VID) of the local port.
 * 0 - Do not change spanning tree state (used only when writing).
 * 1 - Discarding. No learning or क्रमwarding to/from this port (शेष).
 * 2 - Learning. Port is learning, but not क्रमwarding.
 * 3 - Forwarding. Port is learning and क्रमwarding.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, spms, state, 0x04, 0x400, 2);

अटल अंतरभूत व्योम mlxsw_reg_spms_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(spms, payload);
	mlxsw_reg_spms_local_port_set(payload, local_port);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_spms_vid_pack(अक्षर *payload, u16 vid,
					   क्रमागत mlxsw_reg_spms_state state)
अणु
	mlxsw_reg_spms_state_set(payload, vid, state);
पूर्ण

/* SPVID - Switch Port VID
 * -----------------------
 * The चयन port VID configures the शेष VID क्रम a port.
 */
#घोषणा MLXSW_REG_SPVID_ID 0x200E
#घोषणा MLXSW_REG_SPVID_LEN 0x08

MLXSW_REG_DEFINE(spvid, MLXSW_REG_SPVID_ID, MLXSW_REG_SPVID_LEN);

/* reg_spvid_tport
 * Port is tunnel port.
 * Reserved when SwitchX/-2 or Spectrum-1.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvid, tport, 0x00, 24, 1);

/* reg_spvid_local_port
 * When tport = 0: Local port number. Not supported क्रम CPU port.
 * When tport = 1: Tunnel port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvid, local_port, 0x00, 16, 8);

/* reg_spvid_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvid, sub_port, 0x00, 8, 8);

/* reg_spvid_egr_et_set
 * When VLAN is pushed at ingress (क्रम untagged packets or क्रम
 * QinQ push mode) then the EtherType is decided at the egress port.
 * Reserved when Spectrum-1.
 * Access: RW
 */
MLXSW_ITEM32(reg, spvid, egr_et_set, 0x04, 24, 1);

/* reg_spvid_et_vlan
 * EtherType used क्रम when VLAN is pushed at ingress (क्रम untagged
 * packets or क्रम QinQ push mode).
 * 0: ether_type0 - (शेष)
 * 1: ether_type1
 * 2: ether_type2 - Reserved when Spectrum-1, supported by Spectrum-2
 * Ethertype IDs are configured by SVER.
 * Reserved when egr_et_set = 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, spvid, et_vlan, 0x04, 16, 2);

/* reg_spvid_pvid
 * Port शेष VID
 * Access: RW
 */
MLXSW_ITEM32(reg, spvid, pvid, 0x04, 0, 12);

अटल अंतरभूत व्योम mlxsw_reg_spvid_pack(अक्षर *payload, u8 local_port, u16 pvid,
					u8 et_vlan)
अणु
	MLXSW_REG_ZERO(spvid, payload);
	mlxsw_reg_spvid_local_port_set(payload, local_port);
	mlxsw_reg_spvid_pvid_set(payload, pvid);
	mlxsw_reg_spvid_et_vlan_set(payload, et_vlan);
पूर्ण

/* SPVM - Switch Port VLAN Membership
 * ----------------------------------
 * The Switch Port VLAN Membership रेजिस्टर configures the VLAN membership
 * of a port in a VLAN denoted by VID. VLAN membership is managed per
 * भव port. The रेजिस्टर can be used to add and हटाओ VID(s) from a port.
 */
#घोषणा MLXSW_REG_SPVM_ID 0x200F
#घोषणा MLXSW_REG_SPVM_BASE_LEN 0x04 /* base length, without records */
#घोषणा MLXSW_REG_SPVM_REC_LEN 0x04 /* record length */
#घोषणा MLXSW_REG_SPVM_REC_MAX_COUNT 255
#घोषणा MLXSW_REG_SPVM_LEN (MLXSW_REG_SPVM_BASE_LEN +	\
		    MLXSW_REG_SPVM_REC_LEN * MLXSW_REG_SPVM_REC_MAX_COUNT)

MLXSW_REG_DEFINE(spvm, MLXSW_REG_SPVM_ID, MLXSW_REG_SPVM_LEN);

/* reg_spvm_pt
 * Priority tagged. If this bit is set, packets क्रमwarded to the port with
 * untagged VLAN membership (u bit is set) will be tagged with priority tag
 * (VID=0)
 * Access: RW
 */
MLXSW_ITEM32(reg, spvm, pt, 0x00, 31, 1);

/* reg_spvm_pte
 * Priority Tagged Update Enable. On Write operations, अगर this bit is cleared,
 * the pt bit will NOT be updated. To update the pt bit, pte must be set.
 * Access: WO
 */
MLXSW_ITEM32(reg, spvm, pte, 0x00, 30, 1);

/* reg_spvm_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvm, local_port, 0x00, 16, 8);

/* reg_spvm_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvm, sub_port, 0x00, 8, 8);

/* reg_spvm_num_rec
 * Number of records to update. Each record contains: i, e, u, vid.
 * Access: OP
 */
MLXSW_ITEM32(reg, spvm, num_rec, 0x00, 0, 8);

/* reg_spvm_rec_i
 * Ingress membership in VLAN ID.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, spvm, rec_i,
		     MLXSW_REG_SPVM_BASE_LEN, 14, 1,
		     MLXSW_REG_SPVM_REC_LEN, 0, false);

/* reg_spvm_rec_e
 * Egress membership in VLAN ID.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, spvm, rec_e,
		     MLXSW_REG_SPVM_BASE_LEN, 13, 1,
		     MLXSW_REG_SPVM_REC_LEN, 0, false);

/* reg_spvm_rec_u
 * Untagged - port is an untagged member - egress transmission uses untagged
 * frames on VID<n>
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, spvm, rec_u,
		     MLXSW_REG_SPVM_BASE_LEN, 12, 1,
		     MLXSW_REG_SPVM_REC_LEN, 0, false);

/* reg_spvm_rec_vid
 * Egress membership in VLAN ID.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, spvm, rec_vid,
		     MLXSW_REG_SPVM_BASE_LEN, 0, 12,
		     MLXSW_REG_SPVM_REC_LEN, 0, false);

अटल अंतरभूत व्योम mlxsw_reg_spvm_pack(अक्षर *payload, u8 local_port,
				       u16 vid_begin, u16 vid_end,
				       bool is_member, bool untagged)
अणु
	पूर्णांक size = vid_end - vid_begin + 1;
	पूर्णांक i;

	MLXSW_REG_ZERO(spvm, payload);
	mlxsw_reg_spvm_local_port_set(payload, local_port);
	mlxsw_reg_spvm_num_rec_set(payload, size);

	क्रम (i = 0; i < size; i++) अणु
		mlxsw_reg_spvm_rec_i_set(payload, i, is_member);
		mlxsw_reg_spvm_rec_e_set(payload, i, is_member);
		mlxsw_reg_spvm_rec_u_set(payload, i, untagged);
		mlxsw_reg_spvm_rec_vid_set(payload, i, vid_begin + i);
	पूर्ण
पूर्ण

/* SPAFT - Switch Port Acceptable Frame Types
 * ------------------------------------------
 * The Switch Port Acceptable Frame Types रेजिस्टर configures the frame
 * admittance of the port.
 */
#घोषणा MLXSW_REG_SPAFT_ID 0x2010
#घोषणा MLXSW_REG_SPAFT_LEN 0x08

MLXSW_REG_DEFINE(spaft, MLXSW_REG_SPAFT_ID, MLXSW_REG_SPAFT_LEN);

/* reg_spaft_local_port
 * Local port number.
 * Access: Index
 *
 * Note: CPU port is not supported (all tag types are allowed).
 */
MLXSW_ITEM32(reg, spaft, local_port, 0x00, 16, 8);

/* reg_spaft_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 * Access: RW
 */
MLXSW_ITEM32(reg, spaft, sub_port, 0x00, 8, 8);

/* reg_spaft_allow_untagged
 * When set, untagged frames on the ingress are allowed (शेष).
 * Access: RW
 */
MLXSW_ITEM32(reg, spaft, allow_untagged, 0x04, 31, 1);

/* reg_spaft_allow_prio_tagged
 * When set, priority tagged frames on the ingress are allowed (शेष).
 * Access: RW
 */
MLXSW_ITEM32(reg, spaft, allow_prio_tagged, 0x04, 30, 1);

/* reg_spaft_allow_tagged
 * When set, tagged frames on the ingress are allowed (शेष).
 * Access: RW
 */
MLXSW_ITEM32(reg, spaft, allow_tagged, 0x04, 29, 1);

अटल अंतरभूत व्योम mlxsw_reg_spaft_pack(अक्षर *payload, u8 local_port,
					bool allow_untagged)
अणु
	MLXSW_REG_ZERO(spaft, payload);
	mlxsw_reg_spaft_local_port_set(payload, local_port);
	mlxsw_reg_spaft_allow_untagged_set(payload, allow_untagged);
	mlxsw_reg_spaft_allow_prio_tagged_set(payload, allow_untagged);
	mlxsw_reg_spaft_allow_tagged_set(payload, true);
पूर्ण

/* SFGC - Switch Flooding Group Configuration
 * ------------------------------------------
 * The following रेजिस्टर controls the association of flooding tables and MIDs
 * to packet types used क्रम flooding.
 */
#घोषणा MLXSW_REG_SFGC_ID 0x2011
#घोषणा MLXSW_REG_SFGC_LEN 0x10

MLXSW_REG_DEFINE(sfgc, MLXSW_REG_SFGC_ID, MLXSW_REG_SFGC_LEN);

क्रमागत mlxsw_reg_sfgc_type अणु
	MLXSW_REG_SFGC_TYPE_BROADCAST,
	MLXSW_REG_SFGC_TYPE_UNKNOWN_UNICAST,
	MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV4,
	MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_IPV6,
	MLXSW_REG_SFGC_TYPE_RESERVED,
	MLXSW_REG_SFGC_TYPE_UNREGISTERED_MULTICAST_NON_IP,
	MLXSW_REG_SFGC_TYPE_IPV4_LINK_LOCAL,
	MLXSW_REG_SFGC_TYPE_IPV6_ALL_HOST,
	MLXSW_REG_SFGC_TYPE_MAX,
पूर्ण;

/* reg_sfgc_type
 * The traffic type to reach the flooding table.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfgc, type, 0x00, 0, 4);

क्रमागत mlxsw_reg_sfgc_bridge_type अणु
	MLXSW_REG_SFGC_BRIDGE_TYPE_1Q_FID = 0,
	MLXSW_REG_SFGC_BRIDGE_TYPE_VFID = 1,
पूर्ण;

/* reg_sfgc_bridge_type
 * Access: Index
 *
 * Note: SwitchX-2 only supports 802.1Q mode.
 */
MLXSW_ITEM32(reg, sfgc, bridge_type, 0x04, 24, 3);

क्रमागत mlxsw_flood_table_type अणु
	MLXSW_REG_SFGC_TABLE_TYPE_VID = 1,
	MLXSW_REG_SFGC_TABLE_TYPE_SINGLE = 2,
	MLXSW_REG_SFGC_TABLE_TYPE_ANY = 0,
	MLXSW_REG_SFGC_TABLE_TYPE_FID_OFFSET = 3,
	MLXSW_REG_SFGC_TABLE_TYPE_FID = 4,
पूर्ण;

/* reg_sfgc_table_type
 * See mlxsw_flood_table_type
 * Access: RW
 *
 * Note: FID offset and FID types are not supported in SwitchX-2.
 */
MLXSW_ITEM32(reg, sfgc, table_type, 0x04, 16, 3);

/* reg_sfgc_flood_table
 * Flooding table index to associate with the specअगरic type on the specअगरic
 * चयन partition.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfgc, flood_table, 0x04, 0, 6);

/* reg_sfgc_mid
 * The multicast ID क्रम the swid. Not supported क्रम Spectrum
 * Access: RW
 */
MLXSW_ITEM32(reg, sfgc, mid, 0x08, 0, 16);

/* reg_sfgc_counter_set_type
 * Counter Set Type क्रम flow counters.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfgc, counter_set_type, 0x0C, 24, 8);

/* reg_sfgc_counter_index
 * Counter Index क्रम flow counters.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfgc, counter_index, 0x0C, 0, 24);

अटल अंतरभूत व्योम
mlxsw_reg_sfgc_pack(अक्षर *payload, क्रमागत mlxsw_reg_sfgc_type type,
		    क्रमागत mlxsw_reg_sfgc_bridge_type bridge_type,
		    क्रमागत mlxsw_flood_table_type table_type,
		    अचिन्हित पूर्णांक flood_table)
अणु
	MLXSW_REG_ZERO(sfgc, payload);
	mlxsw_reg_sfgc_type_set(payload, type);
	mlxsw_reg_sfgc_bridge_type_set(payload, bridge_type);
	mlxsw_reg_sfgc_table_type_set(payload, table_type);
	mlxsw_reg_sfgc_flood_table_set(payload, flood_table);
	mlxsw_reg_sfgc_mid_set(payload, MLXSW_PORT_MID);
पूर्ण

/* SFTR - Switch Flooding Table Register
 * -------------------------------------
 * The चयन flooding table is used क्रम flooding packet replication. The table
 * defines a bit mask of ports क्रम packet replication.
 */
#घोषणा MLXSW_REG_SFTR_ID 0x2012
#घोषणा MLXSW_REG_SFTR_LEN 0x420

MLXSW_REG_DEFINE(sftr, MLXSW_REG_SFTR_ID, MLXSW_REG_SFTR_LEN);

/* reg_sftr_swid
 * Switch partition ID with which to associate the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, sftr, swid, 0x00, 24, 8);

/* reg_sftr_flood_table
 * Flooding table index to associate with the specअगरic type on the specअगरic
 * चयन partition.
 * Access: Index
 */
MLXSW_ITEM32(reg, sftr, flood_table, 0x00, 16, 6);

/* reg_sftr_index
 * Index. Used as an index पूर्णांकo the Flooding Table in हाल the table is
 * configured to use VID / FID or FID Offset.
 * Access: Index
 */
MLXSW_ITEM32(reg, sftr, index, 0x00, 0, 16);

/* reg_sftr_table_type
 * See mlxsw_flood_table_type
 * Access: RW
 */
MLXSW_ITEM32(reg, sftr, table_type, 0x04, 16, 3);

/* reg_sftr_range
 * Range of entries to update
 * Access: Index
 */
MLXSW_ITEM32(reg, sftr, range, 0x04, 0, 16);

/* reg_sftr_port
 * Local port membership (1 bit per port).
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, sftr, port, 0x20, 0x20, 1);

/* reg_sftr_cpu_port_mask
 * CPU port mask (1 bit per port).
 * Access: W
 */
MLXSW_ITEM_BIT_ARRAY(reg, sftr, port_mask, 0x220, 0x20, 1);

अटल अंतरभूत व्योम mlxsw_reg_sftr_pack(अक्षर *payload,
				       अचिन्हित पूर्णांक flood_table,
				       अचिन्हित पूर्णांक index,
				       क्रमागत mlxsw_flood_table_type table_type,
				       अचिन्हित पूर्णांक range, u8 port, bool set)
अणु
	MLXSW_REG_ZERO(sftr, payload);
	mlxsw_reg_sftr_swid_set(payload, 0);
	mlxsw_reg_sftr_flood_table_set(payload, flood_table);
	mlxsw_reg_sftr_index_set(payload, index);
	mlxsw_reg_sftr_table_type_set(payload, table_type);
	mlxsw_reg_sftr_range_set(payload, range);
	mlxsw_reg_sftr_port_set(payload, port, set);
	mlxsw_reg_sftr_port_mask_set(payload, port, 1);
पूर्ण

/* SFDF - Switch Filtering DB Flush
 * --------------------------------
 * The चयन filtering DB flush रेजिस्टर is used to flush the FDB.
 * Note that FDB notअगरications are flushed as well.
 */
#घोषणा MLXSW_REG_SFDF_ID 0x2013
#घोषणा MLXSW_REG_SFDF_LEN 0x14

MLXSW_REG_DEFINE(sfdf, MLXSW_REG_SFDF_ID, MLXSW_REG_SFDF_LEN);

/* reg_sfdf_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfdf, swid, 0x00, 24, 8);

क्रमागत mlxsw_reg_sfdf_flush_type अणु
	MLXSW_REG_SFDF_FLUSH_PER_SWID,
	MLXSW_REG_SFDF_FLUSH_PER_FID,
	MLXSW_REG_SFDF_FLUSH_PER_PORT,
	MLXSW_REG_SFDF_FLUSH_PER_PORT_AND_FID,
	MLXSW_REG_SFDF_FLUSH_PER_LAG,
	MLXSW_REG_SFDF_FLUSH_PER_LAG_AND_FID,
	MLXSW_REG_SFDF_FLUSH_PER_NVE,
	MLXSW_REG_SFDF_FLUSH_PER_NVE_AND_FID,
पूर्ण;

/* reg_sfdf_flush_type
 * Flush type.
 * 0 - All SWID dynamic entries are flushed.
 * 1 - All FID dynamic entries are flushed.
 * 2 - All dynamic entries poपूर्णांकing to port are flushed.
 * 3 - All FID dynamic entries poपूर्णांकing to port are flushed.
 * 4 - All dynamic entries poपूर्णांकing to LAG are flushed.
 * 5 - All FID dynamic entries poपूर्णांकing to LAG are flushed.
 * 6 - All entries of type "Unicast Tunnel" or "Multicast Tunnel" are
 *     flushed.
 * 7 - All entries of type "Unicast Tunnel" or "Multicast Tunnel" are
 *     flushed, per FID.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, flush_type, 0x04, 28, 4);

/* reg_sfdf_flush_अटल
 * Static.
 * 0 - Flush only dynamic entries.
 * 1 - Flush both dynamic and अटल entries.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, flush_अटल, 0x04, 24, 1);

अटल अंतरभूत व्योम mlxsw_reg_sfdf_pack(अक्षर *payload,
				       क्रमागत mlxsw_reg_sfdf_flush_type type)
अणु
	MLXSW_REG_ZERO(sfdf, payload);
	mlxsw_reg_sfdf_flush_type_set(payload, type);
	mlxsw_reg_sfdf_flush_अटल_set(payload, true);
पूर्ण

/* reg_sfdf_fid
 * FID to flush.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, fid, 0x0C, 0, 16);

/* reg_sfdf_प्रणाली_port
 * Port to flush.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, प्रणाली_port, 0x0C, 0, 16);

/* reg_sfdf_port_fid_प्रणाली_port
 * Port to flush, poपूर्णांकed to by FID.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, port_fid_प्रणाली_port, 0x08, 0, 16);

/* reg_sfdf_lag_id
 * LAG ID to flush.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, lag_id, 0x0C, 0, 10);

/* reg_sfdf_lag_fid_lag_id
 * LAG ID to flush, poपूर्णांकed to by FID.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfdf, lag_fid_lag_id, 0x08, 0, 10);

/* SLDR - Switch LAG Descriptor Register
 * -----------------------------------------
 * The चयन LAG descriptor रेजिस्टर is populated by LAG descriptors.
 * Each LAG descriptor is indexed by lag_id. The LAG ID runs from 0 to
 * max_lag-1.
 */
#घोषणा MLXSW_REG_SLDR_ID 0x2014
#घोषणा MLXSW_REG_SLDR_LEN 0x0C /* counting in only one port in list */

MLXSW_REG_DEFINE(sldr, MLXSW_REG_SLDR_ID, MLXSW_REG_SLDR_LEN);

क्रमागत mlxsw_reg_sldr_op अणु
	/* Indicates a creation of a new LAG-ID, lag_id must be valid */
	MLXSW_REG_SLDR_OP_LAG_CREATE,
	MLXSW_REG_SLDR_OP_LAG_DESTROY,
	/* Ports that appear in the list have the Distributor enabled */
	MLXSW_REG_SLDR_OP_LAG_ADD_PORT_LIST,
	/* Removes ports from the disributor list */
	MLXSW_REG_SLDR_OP_LAG_REMOVE_PORT_LIST,
पूर्ण;

/* reg_sldr_op
 * Operation.
 * Access: RW
 */
MLXSW_ITEM32(reg, sldr, op, 0x00, 29, 3);

/* reg_sldr_lag_id
 * LAG identअगरier. The lag_id is the index पूर्णांकo the LAG descriptor table.
 * Access: Index
 */
MLXSW_ITEM32(reg, sldr, lag_id, 0x00, 0, 10);

अटल अंतरभूत व्योम mlxsw_reg_sldr_lag_create_pack(अक्षर *payload, u8 lag_id)
अणु
	MLXSW_REG_ZERO(sldr, payload);
	mlxsw_reg_sldr_op_set(payload, MLXSW_REG_SLDR_OP_LAG_CREATE);
	mlxsw_reg_sldr_lag_id_set(payload, lag_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sldr_lag_destroy_pack(अक्षर *payload, u8 lag_id)
अणु
	MLXSW_REG_ZERO(sldr, payload);
	mlxsw_reg_sldr_op_set(payload, MLXSW_REG_SLDR_OP_LAG_DESTROY);
	mlxsw_reg_sldr_lag_id_set(payload, lag_id);
पूर्ण

/* reg_sldr_num_ports
 * The number of member ports of the LAG.
 * Reserved क्रम Create / Destroy operations
 * For Add / Remove operations - indicates the number of ports in the list.
 * Access: RW
 */
MLXSW_ITEM32(reg, sldr, num_ports, 0x04, 24, 8);

/* reg_sldr_प्रणाली_port
 * System port.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, sldr, प्रणाली_port, 0x08, 0, 16, 4, 0, false);

अटल अंतरभूत व्योम mlxsw_reg_sldr_lag_add_port_pack(अक्षर *payload, u8 lag_id,
						    u8 local_port)
अणु
	MLXSW_REG_ZERO(sldr, payload);
	mlxsw_reg_sldr_op_set(payload, MLXSW_REG_SLDR_OP_LAG_ADD_PORT_LIST);
	mlxsw_reg_sldr_lag_id_set(payload, lag_id);
	mlxsw_reg_sldr_num_ports_set(payload, 1);
	mlxsw_reg_sldr_प्रणाली_port_set(payload, 0, local_port);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sldr_lag_हटाओ_port_pack(अक्षर *payload, u8 lag_id,
						       u8 local_port)
अणु
	MLXSW_REG_ZERO(sldr, payload);
	mlxsw_reg_sldr_op_set(payload, MLXSW_REG_SLDR_OP_LAG_REMOVE_PORT_LIST);
	mlxsw_reg_sldr_lag_id_set(payload, lag_id);
	mlxsw_reg_sldr_num_ports_set(payload, 1);
	mlxsw_reg_sldr_प्रणाली_port_set(payload, 0, local_port);
पूर्ण

/* SLCR - Switch LAG Configuration 2 Register
 * -------------------------------------------
 * The Switch LAG Configuration रेजिस्टर is used क्रम configuring the
 * LAG properties of the चयन.
 */
#घोषणा MLXSW_REG_SLCR_ID 0x2015
#घोषणा MLXSW_REG_SLCR_LEN 0x10

MLXSW_REG_DEFINE(slcr, MLXSW_REG_SLCR_ID, MLXSW_REG_SLCR_LEN);

क्रमागत mlxsw_reg_slcr_pp अणु
	/* Global Configuration (क्रम all ports) */
	MLXSW_REG_SLCR_PP_GLOBAL,
	/* Per port configuration, based on local_port field */
	MLXSW_REG_SLCR_PP_PER_PORT,
पूर्ण;

/* reg_slcr_pp
 * Per Port Configuration
 * Note: Reading at Global mode results in पढ़ोing port 1 configuration.
 * Access: Index
 */
MLXSW_ITEM32(reg, slcr, pp, 0x00, 24, 1);

/* reg_slcr_local_port
 * Local port number
 * Supported from CPU port
 * Not supported from router port
 * Reserved when pp = Global Configuration
 * Access: Index
 */
MLXSW_ITEM32(reg, slcr, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_slcr_type अणु
	MLXSW_REG_SLCR_TYPE_CRC, /* शेष */
	MLXSW_REG_SLCR_TYPE_XOR,
	MLXSW_REG_SLCR_TYPE_RANDOM,
पूर्ण;

/* reg_slcr_type
 * Hash type
 * Access: RW
 */
MLXSW_ITEM32(reg, slcr, type, 0x00, 0, 4);

/* Ingress port */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_IN_PORT		BIT(0)
/* SMAC - क्रम IPv4 and IPv6 packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_SMAC_IP		BIT(1)
/* SMAC - क्रम non-IP packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_SMAC_NONIP	BIT(2)
#घोषणा MLXSW_REG_SLCR_LAG_HASH_SMAC \
	(MLXSW_REG_SLCR_LAG_HASH_SMAC_IP | \
	 MLXSW_REG_SLCR_LAG_HASH_SMAC_NONIP)
/* DMAC - क्रम IPv4 and IPv6 packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_DMAC_IP		BIT(3)
/* DMAC - क्रम non-IP packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_DMAC_NONIP	BIT(4)
#घोषणा MLXSW_REG_SLCR_LAG_HASH_DMAC \
	(MLXSW_REG_SLCR_LAG_HASH_DMAC_IP | \
	 MLXSW_REG_SLCR_LAG_HASH_DMAC_NONIP)
/* Ethertype - क्रम IPv4 and IPv6 packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE_IP	BIT(5)
/* Ethertype - क्रम non-IP packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE_NONIP	BIT(6)
#घोषणा MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE \
	(MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE_IP | \
	 MLXSW_REG_SLCR_LAG_HASH_ETHERTYPE_NONIP)
/* VLAN ID - क्रम IPv4 and IPv6 packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_VLANID_IP	BIT(7)
/* VLAN ID - क्रम non-IP packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_VLANID_NONIP	BIT(8)
#घोषणा MLXSW_REG_SLCR_LAG_HASH_VLANID \
	(MLXSW_REG_SLCR_LAG_HASH_VLANID_IP | \
	 MLXSW_REG_SLCR_LAG_HASH_VLANID_NONIP)
/* Source IP address (can be IPv4 or IPv6) */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_SIP		BIT(9)
/* Destination IP address (can be IPv4 or IPv6) */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_DIP		BIT(10)
/* TCP/UDP source port */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_SPORT		BIT(11)
/* TCP/UDP destination port*/
#घोषणा MLXSW_REG_SLCR_LAG_HASH_DPORT		BIT(12)
/* IPv4 Protocol/IPv6 Next Header */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_IPPROTO		BIT(13)
/* IPv6 Flow label */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_FLOWLABEL	BIT(14)
/* SID - FCoE source ID */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_FCOE_SID	BIT(15)
/* DID - FCoE destination ID */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_FCOE_DID	BIT(16)
/* OXID - FCoE originator exchange ID */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_FCOE_OXID	BIT(17)
/* Destination QP number - क्रम RoCE packets */
#घोषणा MLXSW_REG_SLCR_LAG_HASH_ROCE_DQP	BIT(19)

/* reg_slcr_lag_hash
 * LAG hashing configuration. This is a biपंचांगask, in which each set
 * bit includes the corresponding item in the LAG hash calculation.
 * The शेष lag_hash contains SMAC, DMAC, VLANID and
 * Ethertype (क्रम all packet types).
 * Access: RW
 */
MLXSW_ITEM32(reg, slcr, lag_hash, 0x04, 0, 20);

/* reg_slcr_seed
 * LAG seed value. The seed is the same क्रम all ports.
 * Access: RW
 */
MLXSW_ITEM32(reg, slcr, seed, 0x08, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_slcr_pack(अक्षर *payload, u16 lag_hash, u32 seed)
अणु
	MLXSW_REG_ZERO(slcr, payload);
	mlxsw_reg_slcr_pp_set(payload, MLXSW_REG_SLCR_PP_GLOBAL);
	mlxsw_reg_slcr_type_set(payload, MLXSW_REG_SLCR_TYPE_CRC);
	mlxsw_reg_slcr_lag_hash_set(payload, lag_hash);
	mlxsw_reg_slcr_seed_set(payload, seed);
पूर्ण

/* SLCOR - Switch LAG Collector Register
 * -------------------------------------
 * The Switch LAG Collector रेजिस्टर controls the Local Port membership
 * in a LAG and enablement of the collector.
 */
#घोषणा MLXSW_REG_SLCOR_ID 0x2016
#घोषणा MLXSW_REG_SLCOR_LEN 0x10

MLXSW_REG_DEFINE(slcor, MLXSW_REG_SLCOR_ID, MLXSW_REG_SLCOR_LEN);

क्रमागत mlxsw_reg_slcor_col अणु
	/* Port is added with collector disabled */
	MLXSW_REG_SLCOR_COL_LAG_ADD_PORT,
	MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_ENABLED,
	MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_DISABLED,
	MLXSW_REG_SLCOR_COL_LAG_REMOVE_PORT,
पूर्ण;

/* reg_slcor_col
 * Collector configuration
 * Access: RW
 */
MLXSW_ITEM32(reg, slcor, col, 0x00, 30, 2);

/* reg_slcor_local_port
 * Local port number
 * Not supported क्रम CPU port
 * Access: Index
 */
MLXSW_ITEM32(reg, slcor, local_port, 0x00, 16, 8);

/* reg_slcor_lag_id
 * LAG Identअगरier. Index पूर्णांकo the LAG descriptor table.
 * Access: Index
 */
MLXSW_ITEM32(reg, slcor, lag_id, 0x00, 0, 10);

/* reg_slcor_port_index
 * Port index in the LAG list. Only valid on Add Port to LAG col.
 * Valid range is from 0 to cap_max_lag_members-1
 * Access: RW
 */
MLXSW_ITEM32(reg, slcor, port_index, 0x04, 0, 10);

अटल अंतरभूत व्योम mlxsw_reg_slcor_pack(अक्षर *payload,
					u8 local_port, u16 lag_id,
					क्रमागत mlxsw_reg_slcor_col col)
अणु
	MLXSW_REG_ZERO(slcor, payload);
	mlxsw_reg_slcor_col_set(payload, col);
	mlxsw_reg_slcor_local_port_set(payload, local_port);
	mlxsw_reg_slcor_lag_id_set(payload, lag_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_slcor_port_add_pack(अक्षर *payload,
						 u8 local_port, u16 lag_id,
						 u8 port_index)
अणु
	mlxsw_reg_slcor_pack(payload, local_port, lag_id,
			     MLXSW_REG_SLCOR_COL_LAG_ADD_PORT);
	mlxsw_reg_slcor_port_index_set(payload, port_index);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_slcor_port_हटाओ_pack(अक्षर *payload,
						    u8 local_port, u16 lag_id)
अणु
	mlxsw_reg_slcor_pack(payload, local_port, lag_id,
			     MLXSW_REG_SLCOR_COL_LAG_REMOVE_PORT);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_slcor_col_enable_pack(अक्षर *payload,
						   u8 local_port, u16 lag_id)
अणु
	mlxsw_reg_slcor_pack(payload, local_port, lag_id,
			     MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_ENABLED);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_slcor_col_disable_pack(अक्षर *payload,
						    u8 local_port, u16 lag_id)
अणु
	mlxsw_reg_slcor_pack(payload, local_port, lag_id,
			     MLXSW_REG_SLCOR_COL_LAG_COLLECTOR_ENABLED);
पूर्ण

/* SPMLR - Switch Port MAC Learning Register
 * -----------------------------------------
 * Controls the Switch MAC learning policy per port.
 */
#घोषणा MLXSW_REG_SPMLR_ID 0x2018
#घोषणा MLXSW_REG_SPMLR_LEN 0x8

MLXSW_REG_DEFINE(spmlr, MLXSW_REG_SPMLR_ID, MLXSW_REG_SPMLR_LEN);

/* reg_spmlr_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, spmlr, local_port, 0x00, 16, 8);

/* reg_spmlr_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spmlr, sub_port, 0x00, 8, 8);

क्रमागत mlxsw_reg_spmlr_learn_mode अणु
	MLXSW_REG_SPMLR_LEARN_MODE_DISABLE = 0,
	MLXSW_REG_SPMLR_LEARN_MODE_ENABLE = 2,
	MLXSW_REG_SPMLR_LEARN_MODE_SEC = 3,
पूर्ण;

/* reg_spmlr_learn_mode
 * Learning mode on the port.
 * 0 - Learning disabled.
 * 2 - Learning enabled.
 * 3 - Security mode.
 *
 * In security mode the चयन करोes not learn MACs on the port, but uses the
 * SMAC to see अगर it exists on another ingress port. If so, the packet is
 * classअगरied as a bad packet and is discarded unless the software रेजिस्टरs
 * to receive port security error packets usign HPKT.
 */
MLXSW_ITEM32(reg, spmlr, learn_mode, 0x04, 30, 2);

अटल अंतरभूत व्योम mlxsw_reg_spmlr_pack(अक्षर *payload, u8 local_port,
					क्रमागत mlxsw_reg_spmlr_learn_mode mode)
अणु
	MLXSW_REG_ZERO(spmlr, payload);
	mlxsw_reg_spmlr_local_port_set(payload, local_port);
	mlxsw_reg_spmlr_sub_port_set(payload, 0);
	mlxsw_reg_spmlr_learn_mode_set(payload, mode);
पूर्ण

/* SVFA - Switch VID to FID Allocation Register
 * --------------------------------------------
 * Controls the VID to FID mapping and अणुPort, VIDपूर्ण to FID mapping क्रम
 * भवized ports.
 */
#घोषणा MLXSW_REG_SVFA_ID 0x201C
#घोषणा MLXSW_REG_SVFA_LEN 0x10

MLXSW_REG_DEFINE(svfa, MLXSW_REG_SVFA_ID, MLXSW_REG_SVFA_LEN);

/* reg_svfa_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, svfa, swid, 0x00, 24, 8);

/* reg_svfa_local_port
 * Local port number.
 * Access: Index
 *
 * Note: Reserved क्रम 802.1Q FIDs.
 */
MLXSW_ITEM32(reg, svfa, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_svfa_mt अणु
	MLXSW_REG_SVFA_MT_VID_TO_FID,
	MLXSW_REG_SVFA_MT_PORT_VID_TO_FID,
पूर्ण;

/* reg_svfa_mapping_table
 * Mapping table:
 * 0 - VID to FID
 * 1 - अणुPort, VIDपूर्ण to FID
 * Access: Index
 *
 * Note: Reserved क्रम SwitchX-2.
 */
MLXSW_ITEM32(reg, svfa, mapping_table, 0x00, 8, 3);

/* reg_svfa_v
 * Valid.
 * Valid अगर set.
 * Access: RW
 *
 * Note: Reserved क्रम SwitchX-2.
 */
MLXSW_ITEM32(reg, svfa, v, 0x00, 0, 1);

/* reg_svfa_fid
 * Filtering ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, svfa, fid, 0x04, 16, 16);

/* reg_svfa_vid
 * VLAN ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, svfa, vid, 0x04, 0, 12);

/* reg_svfa_counter_set_type
 * Counter set type क्रम flow counters.
 * Access: RW
 *
 * Note: Reserved क्रम SwitchX-2.
 */
MLXSW_ITEM32(reg, svfa, counter_set_type, 0x08, 24, 8);

/* reg_svfa_counter_index
 * Counter index क्रम flow counters.
 * Access: RW
 *
 * Note: Reserved क्रम SwitchX-2.
 */
MLXSW_ITEM32(reg, svfa, counter_index, 0x08, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_svfa_pack(अक्षर *payload, u8 local_port,
				       क्रमागत mlxsw_reg_svfa_mt mt, bool valid,
				       u16 fid, u16 vid)
अणु
	MLXSW_REG_ZERO(svfa, payload);
	local_port = mt == MLXSW_REG_SVFA_MT_VID_TO_FID ? 0 : local_port;
	mlxsw_reg_svfa_swid_set(payload, 0);
	mlxsw_reg_svfa_local_port_set(payload, local_port);
	mlxsw_reg_svfa_mapping_table_set(payload, mt);
	mlxsw_reg_svfa_v_set(payload, valid);
	mlxsw_reg_svfa_fid_set(payload, fid);
	mlxsw_reg_svfa_vid_set(payload, vid);
पूर्ण

/*  SPVTR - Switch Port VLAN Stacking Register
 *  ------------------------------------------
 *  The Switch Port VLAN Stacking रेजिस्टर configures the VLAN mode of the port
 *  to enable VLAN stacking.
 */
#घोषणा MLXSW_REG_SPVTR_ID 0x201D
#घोषणा MLXSW_REG_SPVTR_LEN 0x10

MLXSW_REG_DEFINE(spvtr, MLXSW_REG_SPVTR_ID, MLXSW_REG_SPVTR_LEN);

/* reg_spvtr_tport
 * Port is tunnel port.
 * Access: Index
 *
 * Note: Reserved when SwitchX/-2 or Spectrum-1.
 */
MLXSW_ITEM32(reg, spvtr, tport, 0x00, 24, 1);

/* reg_spvtr_local_port
 * When tport = 0: local port number (Not supported from/to CPU).
 * When tport = 1: tunnel port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spvtr, local_port, 0x00, 16, 8);

/* reg_spvtr_ippe
 * Ingress Port Prio Mode Update Enable.
 * When set, the Port Prio Mode is updated with the provided ipprio_mode field.
 * Reserved on Get operations.
 * Access: OP
 */
MLXSW_ITEM32(reg, spvtr, ippe, 0x04, 31, 1);

/* reg_spvtr_ipve
 * Ingress Port VID Mode Update Enable.
 * When set, the Ingress Port VID Mode is updated with the provided ipvid_mode
 * field.
 * Reserved on Get operations.
 * Access: OP
 */
MLXSW_ITEM32(reg, spvtr, ipve, 0x04, 30, 1);

/* reg_spvtr_epve
 * Egress Port VID Mode Update Enable.
 * When set, the Egress Port VID Mode is updated with the provided epvid_mode
 * field.
 * Access: OP
 */
MLXSW_ITEM32(reg, spvtr, epve, 0x04, 29, 1);

/* reg_spvtr_ipprio_mode
 * Ingress Port Priority Mode.
 * This controls the PCP and DEI of the new outer VLAN
 * Note: क्रम SwitchX/-2 the DEI is not affected.
 * 0: use port शेष PCP and DEI (configured by QPDPC).
 * 1: use C-VLAN PCP and DEI.
 * Has no effect when ipvid_mode = 0.
 * Reserved when tport = 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, spvtr, ipprio_mode, 0x04, 20, 4);

क्रमागत mlxsw_reg_spvtr_ipvid_mode अणु
	/* IEEE Compliant PVID (शेष) */
	MLXSW_REG_SPVTR_IPVID_MODE_IEEE_COMPLIANT_PVID,
	/* Push VLAN (क्रम VLAN stacking, except prio tagged packets) */
	MLXSW_REG_SPVTR_IPVID_MODE_PUSH_VLAN_FOR_UNTAGGED_PACKET,
	/* Always push VLAN (also क्रम prio tagged packets) */
	MLXSW_REG_SPVTR_IPVID_MODE_ALWAYS_PUSH_VLAN,
पूर्ण;

/* reg_spvtr_ipvid_mode
 * Ingress Port VLAN-ID Mode.
 * For Spectrum family, this affects the values of SPVM.i
 * Access: RW
 */
MLXSW_ITEM32(reg, spvtr, ipvid_mode, 0x04, 16, 4);

क्रमागत mlxsw_reg_spvtr_epvid_mode अणु
	/* IEEE Compliant VLAN membership */
	MLXSW_REG_SPVTR_EPVID_MODE_IEEE_COMPLIANT_VLAN_MEMBERSHIP,
	/* Pop VLAN (क्रम VLAN stacking) */
	MLXSW_REG_SPVTR_EPVID_MODE_POP_VLAN,
पूर्ण;

/* reg_spvtr_epvid_mode
 * Egress Port VLAN-ID Mode.
 * For Spectrum family, this affects the values of SPVM.e,u,pt.
 * Access: WO
 */
MLXSW_ITEM32(reg, spvtr, epvid_mode, 0x04, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_spvtr_pack(अक्षर *payload, bool tport,
					u8 local_port,
					क्रमागत mlxsw_reg_spvtr_ipvid_mode ipvid_mode)
अणु
	MLXSW_REG_ZERO(spvtr, payload);
	mlxsw_reg_spvtr_tport_set(payload, tport);
	mlxsw_reg_spvtr_local_port_set(payload, local_port);
	mlxsw_reg_spvtr_ipvid_mode_set(payload, ipvid_mode);
	mlxsw_reg_spvtr_ipve_set(payload, true);
पूर्ण

/* SVPE - Switch Virtual-Port Enabling Register
 * --------------------------------------------
 * Enables port भवization.
 */
#घोषणा MLXSW_REG_SVPE_ID 0x201E
#घोषणा MLXSW_REG_SVPE_LEN 0x4

MLXSW_REG_DEFINE(svpe, MLXSW_REG_SVPE_ID, MLXSW_REG_SVPE_LEN);

/* reg_svpe_local_port
 * Local port number
 * Access: Index
 *
 * Note: CPU port is not supported (uses VLAN mode only).
 */
MLXSW_ITEM32(reg, svpe, local_port, 0x00, 16, 8);

/* reg_svpe_vp_en
 * Virtual port enable.
 * 0 - Disable, VLAN mode (VID to FID).
 * 1 - Enable, Virtual port mode (अणुPort, VIDपूर्ण to FID).
 * Access: RW
 */
MLXSW_ITEM32(reg, svpe, vp_en, 0x00, 8, 1);

अटल अंतरभूत व्योम mlxsw_reg_svpe_pack(अक्षर *payload, u8 local_port,
				       bool enable)
अणु
	MLXSW_REG_ZERO(svpe, payload);
	mlxsw_reg_svpe_local_port_set(payload, local_port);
	mlxsw_reg_svpe_vp_en_set(payload, enable);
पूर्ण

/* SFMR - Switch FID Management Register
 * -------------------------------------
 * Creates and configures FIDs.
 */
#घोषणा MLXSW_REG_SFMR_ID 0x201F
#घोषणा MLXSW_REG_SFMR_LEN 0x18

MLXSW_REG_DEFINE(sfmr, MLXSW_REG_SFMR_ID, MLXSW_REG_SFMR_LEN);

क्रमागत mlxsw_reg_sfmr_op अणु
	MLXSW_REG_SFMR_OP_CREATE_FID,
	MLXSW_REG_SFMR_OP_DESTROY_FID,
पूर्ण;

/* reg_sfmr_op
 * Operation.
 * 0 - Create or edit FID.
 * 1 - Destroy FID.
 * Access: WO
 */
MLXSW_ITEM32(reg, sfmr, op, 0x00, 24, 4);

/* reg_sfmr_fid
 * Filtering ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, sfmr, fid, 0x00, 0, 16);

/* reg_sfmr_fid_offset
 * FID offset.
 * Used to poपूर्णांक पूर्णांकo the flooding table selected by SFGC रेजिस्टर अगर
 * the table is of type FID-Offset. Otherwise, this field is reserved.
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, fid_offset, 0x08, 0, 16);

/* reg_sfmr_vtfp
 * Valid Tunnel Flood Poपूर्णांकer.
 * If not set, then nve_tunnel_flood_ptr is reserved and considered शून्य.
 * Access: RW
 *
 * Note: Reserved क्रम 802.1Q FIDs.
 */
MLXSW_ITEM32(reg, sfmr, vtfp, 0x0C, 31, 1);

/* reg_sfmr_nve_tunnel_flood_ptr
 * Underlay Flooding and BC Poपूर्णांकer.
 * Used as a poपूर्णांकer to the first entry of the group based link lists of
 * flooding or BC entries (क्रम NVE tunnels).
 * Access: RW
 */
MLXSW_ITEM32(reg, sfmr, nve_tunnel_flood_ptr, 0x0C, 0, 24);

/* reg_sfmr_vv
 * VNI Valid.
 * If not set, then vni is reserved.
 * Access: RW
 *
 * Note: Reserved क्रम 802.1Q FIDs.
 */
MLXSW_ITEM32(reg, sfmr, vv, 0x10, 31, 1);

/* reg_sfmr_vni
 * Virtual Network Identअगरier.
 * Access: RW
 *
 * Note: A given VNI can only be asचिन्हित to one FID.
 */
MLXSW_ITEM32(reg, sfmr, vni, 0x10, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_sfmr_pack(अक्षर *payload,
				       क्रमागत mlxsw_reg_sfmr_op op, u16 fid,
				       u16 fid_offset)
अणु
	MLXSW_REG_ZERO(sfmr, payload);
	mlxsw_reg_sfmr_op_set(payload, op);
	mlxsw_reg_sfmr_fid_set(payload, fid);
	mlxsw_reg_sfmr_fid_offset_set(payload, fid_offset);
	mlxsw_reg_sfmr_vtfp_set(payload, false);
	mlxsw_reg_sfmr_vv_set(payload, false);
पूर्ण

/* SPVMLR - Switch Port VLAN MAC Learning Register
 * -----------------------------------------------
 * Controls the चयन MAC learning policy per अणुPort, VIDपूर्ण.
 */
#घोषणा MLXSW_REG_SPVMLR_ID 0x2020
#घोषणा MLXSW_REG_SPVMLR_BASE_LEN 0x04 /* base length, without records */
#घोषणा MLXSW_REG_SPVMLR_REC_LEN 0x04 /* record length */
#घोषणा MLXSW_REG_SPVMLR_REC_MAX_COUNT 255
#घोषणा MLXSW_REG_SPVMLR_LEN (MLXSW_REG_SPVMLR_BASE_LEN + \
			      MLXSW_REG_SPVMLR_REC_LEN * \
			      MLXSW_REG_SPVMLR_REC_MAX_COUNT)

MLXSW_REG_DEFINE(spvmlr, MLXSW_REG_SPVMLR_ID, MLXSW_REG_SPVMLR_LEN);

/* reg_spvmlr_local_port
 * Local ingress port.
 * Access: Index
 *
 * Note: CPU port is not supported.
 */
MLXSW_ITEM32(reg, spvmlr, local_port, 0x00, 16, 8);

/* reg_spvmlr_num_rec
 * Number of records to update.
 * Access: OP
 */
MLXSW_ITEM32(reg, spvmlr, num_rec, 0x00, 0, 8);

/* reg_spvmlr_rec_learn_enable
 * 0 - Disable learning क्रम अणुPort, VIDपूर्ण.
 * 1 - Enable learning क्रम अणुPort, VIDपूर्ण.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, spvmlr, rec_learn_enable, MLXSW_REG_SPVMLR_BASE_LEN,
		     31, 1, MLXSW_REG_SPVMLR_REC_LEN, 0x00, false);

/* reg_spvmlr_rec_vid
 * VLAN ID to be added/हटाओd from port or क्रम querying.
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, spvmlr, rec_vid, MLXSW_REG_SPVMLR_BASE_LEN, 0, 12,
		     MLXSW_REG_SPVMLR_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_spvmlr_pack(अक्षर *payload, u8 local_port,
					 u16 vid_begin, u16 vid_end,
					 bool learn_enable)
अणु
	पूर्णांक num_rec = vid_end - vid_begin + 1;
	पूर्णांक i;

	WARN_ON(num_rec < 1 || num_rec > MLXSW_REG_SPVMLR_REC_MAX_COUNT);

	MLXSW_REG_ZERO(spvmlr, payload);
	mlxsw_reg_spvmlr_local_port_set(payload, local_port);
	mlxsw_reg_spvmlr_num_rec_set(payload, num_rec);

	क्रम (i = 0; i < num_rec; i++) अणु
		mlxsw_reg_spvmlr_rec_learn_enable_set(payload, i, learn_enable);
		mlxsw_reg_spvmlr_rec_vid_set(payload, i, vid_begin + i);
	पूर्ण
पूर्ण

/* SPVC - Switch Port VLAN Classअगरication Register
 * -----------------------------------------------
 * Configures the port to identअगरy packets as untagged / single tagged /
 * द्विगुन packets based on the packet EtherTypes.
 * Ethertype IDs are configured by SVER.
 */
#घोषणा MLXSW_REG_SPVC_ID 0x2026
#घोषणा MLXSW_REG_SPVC_LEN 0x0C

MLXSW_REG_DEFINE(spvc, MLXSW_REG_SPVC_ID, MLXSW_REG_SPVC_LEN);

/* reg_spvc_local_port
 * Local port.
 * Access: Index
 *
 * Note: applies both to Rx port and Tx port, so अगर a packet traverses
 * through Rx port i and a Tx port j then port i and port j must have the
 * same configuration.
 */
MLXSW_ITEM32(reg, spvc, local_port, 0x00, 16, 8);

/* reg_spvc_inner_et2
 * Vlan Tag1 EtherType2 enable.
 * Packet is initially classअगरied as द्विगुन VLAN Tag अगर in addition to
 * being classअगरied with a tag0 VLAN Tag its tag1 EtherType value is
 * equal to ether_type2.
 * 0: disable (शेष)
 * 1: enable
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, inner_et2, 0x08, 17, 1);

/* reg_spvc_et2
 * Vlan Tag0 EtherType2 enable.
 * Packet is initially classअगरied as VLAN Tag अगर its tag0 EtherType is
 * equal to ether_type2.
 * 0: disable (शेष)
 * 1: enable
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, et2, 0x08, 16, 1);

/* reg_spvc_inner_et1
 * Vlan Tag1 EtherType1 enable.
 * Packet is initially classअगरied as द्विगुन VLAN Tag अगर in addition to
 * being classअगरied with a tag0 VLAN Tag its tag1 EtherType value is
 * equal to ether_type1.
 * 0: disable
 * 1: enable (शेष)
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, inner_et1, 0x08, 9, 1);

/* reg_spvc_et1
 * Vlan Tag0 EtherType1 enable.
 * Packet is initially classअगरied as VLAN Tag अगर its tag0 EtherType is
 * equal to ether_type1.
 * 0: disable
 * 1: enable (शेष)
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, et1, 0x08, 8, 1);

/* reg_inner_et0
 * Vlan Tag1 EtherType0 enable.
 * Packet is initially classअगरied as द्विगुन VLAN Tag अगर in addition to
 * being classअगरied with a tag0 VLAN Tag its tag1 EtherType value is
 * equal to ether_type0.
 * 0: disable
 * 1: enable (शेष)
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, inner_et0, 0x08, 1, 1);

/* reg_et0
 * Vlan Tag0 EtherType0 enable.
 * Packet is initially classअगरied as VLAN Tag अगर its tag0 EtherType is
 * equal to ether_type0.
 * 0: disable
 * 1: enable (शेष)
 * Access: RW
 */
MLXSW_ITEM32(reg, spvc, et0, 0x08, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_spvc_pack(अक्षर *payload, u8 local_port, bool et1,
				       bool et0)
अणु
	MLXSW_REG_ZERO(spvc, payload);
	mlxsw_reg_spvc_local_port_set(payload, local_port);
	/* Enable inner_et1 and inner_et0 to enable identअगरication of द्विगुन
	 * tagged packets.
	 */
	mlxsw_reg_spvc_inner_et1_set(payload, 1);
	mlxsw_reg_spvc_inner_et0_set(payload, 1);
	mlxsw_reg_spvc_et1_set(payload, et1);
	mlxsw_reg_spvc_et0_set(payload, et0);
पूर्ण

/* SPEVET - Switch Port Egress VLAN EtherType
 * ------------------------------------------
 * The चयन port egress VLAN EtherType configures which EtherType to push at
 * egress क्रम packets incoming through a local port क्रम which 'SPVID.egr_et_set'
 * is set.
 */
#घोषणा MLXSW_REG_SPEVET_ID 0x202A
#घोषणा MLXSW_REG_SPEVET_LEN 0x08

MLXSW_REG_DEFINE(spevet, MLXSW_REG_SPEVET_ID, MLXSW_REG_SPEVET_LEN);

/* reg_spevet_local_port
 * Egress Local port number.
 * Not supported to CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, spevet, local_port, 0x00, 16, 8);

/* reg_spevet_et_vlan
 * Egress EtherType VLAN to push when SPVID.egr_et_set field set क्रम the packet:
 * 0: ether_type0 - (शेष)
 * 1: ether_type1
 * 2: ether_type2
 * Access: RW
 */
MLXSW_ITEM32(reg, spevet, et_vlan, 0x04, 16, 2);

अटल अंतरभूत व्योम mlxsw_reg_spevet_pack(अक्षर *payload, u8 local_port,
					 u8 et_vlan)
अणु
	MLXSW_REG_ZERO(spevet, payload);
	mlxsw_reg_spevet_local_port_set(payload, local_port);
	mlxsw_reg_spevet_et_vlan_set(payload, et_vlan);
पूर्ण

/* CWTP - Congetion WRED ECN TClass Profile
 * ----------------------------------------
 * Configures the profiles क्रम queues of egress port and traffic class
 */
#घोषणा MLXSW_REG_CWTP_ID 0x2802
#घोषणा MLXSW_REG_CWTP_BASE_LEN 0x28
#घोषणा MLXSW_REG_CWTP_PROखाता_DATA_REC_LEN 0x08
#घोषणा MLXSW_REG_CWTP_LEN 0x40

MLXSW_REG_DEFINE(cwtp, MLXSW_REG_CWTP_ID, MLXSW_REG_CWTP_LEN);

/* reg_cwtp_local_port
 * Local port number
 * Not supported क्रम CPU port
 * Access: Index
 */
MLXSW_ITEM32(reg, cwtp, local_port, 0, 16, 8);

/* reg_cwtp_traffic_class
 * Traffic Class to configure
 * Access: Index
 */
MLXSW_ITEM32(reg, cwtp, traffic_class, 32, 0, 8);

/* reg_cwtp_profile_min
 * Minimum Average Queue Size of the profile in cells.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, cwtp, profile_min, MLXSW_REG_CWTP_BASE_LEN,
		     0, 20, MLXSW_REG_CWTP_PROखाता_DATA_REC_LEN, 0, false);

/* reg_cwtp_profile_percent
 * Percentage of WRED and ECN marking क्रम maximum Average Queue size
 * Range is 0 to 100, units of पूर्णांकeger percentage
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, cwtp, profile_percent, MLXSW_REG_CWTP_BASE_LEN,
		     24, 7, MLXSW_REG_CWTP_PROखाता_DATA_REC_LEN, 4, false);

/* reg_cwtp_profile_max
 * Maximum Average Queue size of the profile in cells
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, cwtp, profile_max, MLXSW_REG_CWTP_BASE_LEN,
		     0, 20, MLXSW_REG_CWTP_PROखाता_DATA_REC_LEN, 4, false);

#घोषणा MLXSW_REG_CWTP_MIN_VALUE 64
#घोषणा MLXSW_REG_CWTP_MAX_PROखाता 2
#घोषणा MLXSW_REG_CWTP_DEFAULT_PROखाता 1

अटल अंतरभूत व्योम mlxsw_reg_cwtp_pack(अक्षर *payload, u8 local_port,
				       u8 traffic_class)
अणु
	पूर्णांक i;

	MLXSW_REG_ZERO(cwtp, payload);
	mlxsw_reg_cwtp_local_port_set(payload, local_port);
	mlxsw_reg_cwtp_traffic_class_set(payload, traffic_class);

	क्रम (i = 0; i <= MLXSW_REG_CWTP_MAX_PROखाता; i++) अणु
		mlxsw_reg_cwtp_profile_min_set(payload, i,
					       MLXSW_REG_CWTP_MIN_VALUE);
		mlxsw_reg_cwtp_profile_max_set(payload, i,
					       MLXSW_REG_CWTP_MIN_VALUE);
	पूर्ण
पूर्ण

#घोषणा MLXSW_REG_CWTP_PROखाता_TO_INDEX(profile) (profile - 1)

अटल अंतरभूत व्योम
mlxsw_reg_cwtp_profile_pack(अक्षर *payload, u8 profile, u32 min, u32 max,
			    u32 probability)
अणु
	u8 index = MLXSW_REG_CWTP_PROखाता_TO_INDEX(profile);

	mlxsw_reg_cwtp_profile_min_set(payload, index, min);
	mlxsw_reg_cwtp_profile_max_set(payload, index, max);
	mlxsw_reg_cwtp_profile_percent_set(payload, index, probability);
पूर्ण

/* CWTPM - Congestion WRED ECN TClass and Pool Mapping
 * ---------------------------------------------------
 * The CWTPM रेजिस्टर maps each egress port and traffic class to profile num.
 */
#घोषणा MLXSW_REG_CWTPM_ID 0x2803
#घोषणा MLXSW_REG_CWTPM_LEN 0x44

MLXSW_REG_DEFINE(cwtpm, MLXSW_REG_CWTPM_ID, MLXSW_REG_CWTPM_LEN);

/* reg_cwtpm_local_port
 * Local port number
 * Not supported क्रम CPU port
 * Access: Index
 */
MLXSW_ITEM32(reg, cwtpm, local_port, 0, 16, 8);

/* reg_cwtpm_traffic_class
 * Traffic Class to configure
 * Access: Index
 */
MLXSW_ITEM32(reg, cwtpm, traffic_class, 32, 0, 8);

/* reg_cwtpm_ew
 * Control enablement of WRED क्रम traffic class:
 * 0 - Disable
 * 1 - Enable
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, ew, 36, 1, 1);

/* reg_cwtpm_ee
 * Control enablement of ECN क्रम traffic class:
 * 0 - Disable
 * 1 - Enable
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, ee, 36, 0, 1);

/* reg_cwtpm_tcp_g
 * TCP Green Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, tcp_g, 52, 0, 2);

/* reg_cwtpm_tcp_y
 * TCP Yellow Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, tcp_y, 56, 16, 2);

/* reg_cwtpm_tcp_r
 * TCP Red Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, tcp_r, 56, 0, 2);

/* reg_cwtpm_ntcp_g
 * Non-TCP Green Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, ntcp_g, 60, 0, 2);

/* reg_cwtpm_ntcp_y
 * Non-TCP Yellow Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, ntcp_y, 64, 16, 2);

/* reg_cwtpm_ntcp_r
 * Non-TCP Red Profile.
 * Index of the profile within अणुport, traffic classपूर्ण to use.
 * 0 क्रम disabling both WRED and ECN क्रम this type of traffic.
 * Access: RW
 */
MLXSW_ITEM32(reg, cwtpm, ntcp_r, 64, 0, 2);

#घोषणा MLXSW_REG_CWTPM_RESET_PROखाता 0

अटल अंतरभूत व्योम mlxsw_reg_cwtpm_pack(अक्षर *payload, u8 local_port,
					u8 traffic_class, u8 profile,
					bool wred, bool ecn)
अणु
	MLXSW_REG_ZERO(cwtpm, payload);
	mlxsw_reg_cwtpm_local_port_set(payload, local_port);
	mlxsw_reg_cwtpm_traffic_class_set(payload, traffic_class);
	mlxsw_reg_cwtpm_ew_set(payload, wred);
	mlxsw_reg_cwtpm_ee_set(payload, ecn);
	mlxsw_reg_cwtpm_tcp_g_set(payload, profile);
	mlxsw_reg_cwtpm_tcp_y_set(payload, profile);
	mlxsw_reg_cwtpm_tcp_r_set(payload, profile);
	mlxsw_reg_cwtpm_ntcp_g_set(payload, profile);
	mlxsw_reg_cwtpm_ntcp_y_set(payload, profile);
	mlxsw_reg_cwtpm_ntcp_r_set(payload, profile);
पूर्ण

/* PGCR - Policy-Engine General Configuration Register
 * ---------------------------------------------------
 * This रेजिस्टर configures general Policy-Engine settings.
 */
#घोषणा MLXSW_REG_PGCR_ID 0x3001
#घोषणा MLXSW_REG_PGCR_LEN 0x20

MLXSW_REG_DEFINE(pgcr, MLXSW_REG_PGCR_ID, MLXSW_REG_PGCR_LEN);

/* reg_pgcr_शेष_action_poपूर्णांकer_base
 * Default action poपूर्णांकer base. Each region has a शेष action poपूर्णांकer
 * which is equal to शेष_action_poपूर्णांकer_base + region_id.
 * Access: RW
 */
MLXSW_ITEM32(reg, pgcr, शेष_action_poपूर्णांकer_base, 0x1C, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_pgcr_pack(अक्षर *payload, u32 poपूर्णांकer_base)
अणु
	MLXSW_REG_ZERO(pgcr, payload);
	mlxsw_reg_pgcr_शेष_action_poपूर्णांकer_base_set(payload, poपूर्णांकer_base);
पूर्ण

/* PPBT - Policy-Engine Port Binding Table
 * ---------------------------------------
 * This रेजिस्टर is used क्रम configuration of the Port Binding Table.
 */
#घोषणा MLXSW_REG_PPBT_ID 0x3002
#घोषणा MLXSW_REG_PPBT_LEN 0x14

MLXSW_REG_DEFINE(ppbt, MLXSW_REG_PPBT_ID, MLXSW_REG_PPBT_LEN);

क्रमागत mlxsw_reg_pxbt_e अणु
	MLXSW_REG_PXBT_E_IACL,
	MLXSW_REG_PXBT_E_EACL,
पूर्ण;

/* reg_ppbt_e
 * Access: Index
 */
MLXSW_ITEM32(reg, ppbt, e, 0x00, 31, 1);

क्रमागत mlxsw_reg_pxbt_op अणु
	MLXSW_REG_PXBT_OP_BIND,
	MLXSW_REG_PXBT_OP_UNBIND,
पूर्ण;

/* reg_ppbt_op
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbt, op, 0x00, 28, 3);

/* reg_ppbt_local_port
 * Local port. Not including CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, ppbt, local_port, 0x00, 16, 8);

/* reg_ppbt_g
 * group - When set, the binding is of an ACL group. When cleared,
 * the binding is of an ACL.
 * Must be set to 1 क्रम Spectrum.
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbt, g, 0x10, 31, 1);

/* reg_ppbt_acl_info
 * ACL/ACL group identअगरier. If the g bit is set, this field should hold
 * the acl_group_id, अन्यथा it should hold the acl_id.
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbt, acl_info, 0x10, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_ppbt_pack(अक्षर *payload, क्रमागत mlxsw_reg_pxbt_e e,
				       क्रमागत mlxsw_reg_pxbt_op op,
				       u8 local_port, u16 acl_info)
अणु
	MLXSW_REG_ZERO(ppbt, payload);
	mlxsw_reg_ppbt_e_set(payload, e);
	mlxsw_reg_ppbt_op_set(payload, op);
	mlxsw_reg_ppbt_local_port_set(payload, local_port);
	mlxsw_reg_ppbt_g_set(payload, true);
	mlxsw_reg_ppbt_acl_info_set(payload, acl_info);
पूर्ण

/* PACL - Policy-Engine ACL Register
 * ---------------------------------
 * This रेजिस्टर is used क्रम configuration of the ACL.
 */
#घोषणा MLXSW_REG_PACL_ID 0x3004
#घोषणा MLXSW_REG_PACL_LEN 0x70

MLXSW_REG_DEFINE(pacl, MLXSW_REG_PACL_ID, MLXSW_REG_PACL_LEN);

/* reg_pacl_v
 * Valid. Setting the v bit makes the ACL valid. It should not be cleared
 * जबतक the ACL is bounded to either a port, VLAN or ACL rule.
 * Access: RW
 */
MLXSW_ITEM32(reg, pacl, v, 0x00, 24, 1);

/* reg_pacl_acl_id
 * An identअगरier representing the ACL (managed by software)
 * Range 0 .. cap_max_acl_regions - 1
 * Access: Index
 */
MLXSW_ITEM32(reg, pacl, acl_id, 0x08, 0, 16);

#घोषणा MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN 16

/* reg_pacl_tcam_region_info
 * Opaque object that represents a TCAM region.
 * Obtained through PTAR रेजिस्टर.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, pacl, tcam_region_info, 0x30,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

अटल अंतरभूत व्योम mlxsw_reg_pacl_pack(अक्षर *payload, u16 acl_id,
				       bool valid, स्थिर अक्षर *tcam_region_info)
अणु
	MLXSW_REG_ZERO(pacl, payload);
	mlxsw_reg_pacl_acl_id_set(payload, acl_id);
	mlxsw_reg_pacl_v_set(payload, valid);
	mlxsw_reg_pacl_tcam_region_info_स_नकल_to(payload, tcam_region_info);
पूर्ण

/* PAGT - Policy-Engine ACL Group Table
 * ------------------------------------
 * This रेजिस्टर is used क्रम configuration of the ACL Group Table.
 */
#घोषणा MLXSW_REG_PAGT_ID 0x3005
#घोषणा MLXSW_REG_PAGT_BASE_LEN 0x30
#घोषणा MLXSW_REG_PAGT_ACL_LEN 4
#घोषणा MLXSW_REG_PAGT_ACL_MAX_NUM 16
#घोषणा MLXSW_REG_PAGT_LEN (MLXSW_REG_PAGT_BASE_LEN + \
		MLXSW_REG_PAGT_ACL_MAX_NUM * MLXSW_REG_PAGT_ACL_LEN)

MLXSW_REG_DEFINE(pagt, MLXSW_REG_PAGT_ID, MLXSW_REG_PAGT_LEN);

/* reg_pagt_size
 * Number of ACLs in the group.
 * Size 0 invalidates a group.
 * Range 0 .. cap_max_acl_group_size (hard coded to 16 क्रम now)
 * Total number of ACLs in all groups must be lower or equal
 * to cap_max_acl_tot_groups
 * Note: a group which is binded must not be invalidated
 * Access: Index
 */
MLXSW_ITEM32(reg, pagt, size, 0x00, 0, 8);

/* reg_pagt_acl_group_id
 * An identअगरier (numbered from 0..cap_max_acl_groups-1) representing
 * the ACL Group identअगरier (managed by software).
 * Access: Index
 */
MLXSW_ITEM32(reg, pagt, acl_group_id, 0x08, 0, 16);

/* reg_pagt_multi
 * Multi-ACL
 * 0 - This ACL is the last ACL in the multi-ACL
 * 1 - This ACL is part of a multi-ACL
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pagt, multi, 0x30, 31, 1, 0x04, 0x00, false);

/* reg_pagt_acl_id
 * ACL identअगरier
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pagt, acl_id, 0x30, 0, 16, 0x04, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_pagt_pack(अक्षर *payload, u16 acl_group_id)
अणु
	MLXSW_REG_ZERO(pagt, payload);
	mlxsw_reg_pagt_acl_group_id_set(payload, acl_group_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pagt_acl_id_pack(अक्षर *payload, पूर्णांक index,
					      u16 acl_id, bool multi)
अणु
	u8 size = mlxsw_reg_pagt_size_get(payload);

	अगर (index >= size)
		mlxsw_reg_pagt_size_set(payload, index + 1);
	mlxsw_reg_pagt_multi_set(payload, index, multi);
	mlxsw_reg_pagt_acl_id_set(payload, index, acl_id);
पूर्ण

/* PTAR - Policy-Engine TCAM Allocation Register
 * ---------------------------------------------
 * This रेजिस्टर is used क्रम allocation of regions in the TCAM.
 * Note: Query method is not supported on this रेजिस्टर.
 */
#घोषणा MLXSW_REG_PTAR_ID 0x3006
#घोषणा MLXSW_REG_PTAR_BASE_LEN 0x20
#घोषणा MLXSW_REG_PTAR_KEY_ID_LEN 1
#घोषणा MLXSW_REG_PTAR_KEY_ID_MAX_NUM 16
#घोषणा MLXSW_REG_PTAR_LEN (MLXSW_REG_PTAR_BASE_LEN + \
		MLXSW_REG_PTAR_KEY_ID_MAX_NUM * MLXSW_REG_PTAR_KEY_ID_LEN)

MLXSW_REG_DEFINE(ptar, MLXSW_REG_PTAR_ID, MLXSW_REG_PTAR_LEN);

क्रमागत mlxsw_reg_ptar_op अणु
	/* allocate a TCAM region */
	MLXSW_REG_PTAR_OP_ALLOC,
	/* resize a TCAM region */
	MLXSW_REG_PTAR_OP_RESIZE,
	/* deallocate TCAM region */
	MLXSW_REG_PTAR_OP_FREE,
	/* test allocation */
	MLXSW_REG_PTAR_OP_TEST,
पूर्ण;

/* reg_ptar_op
 * Access: OP
 */
MLXSW_ITEM32(reg, ptar, op, 0x00, 28, 4);

/* reg_ptar_action_set_type
 * Type of action set to be used on this region.
 * For Spectrum and Spectrum-2, this is always type 2 - "flexible"
 * Access: WO
 */
MLXSW_ITEM32(reg, ptar, action_set_type, 0x00, 16, 8);

क्रमागत mlxsw_reg_ptar_key_type अणु
	MLXSW_REG_PTAR_KEY_TYPE_FLEX = 0x50, /* Spetrum */
	MLXSW_REG_PTAR_KEY_TYPE_FLEX2 = 0x51, /* Spectrum-2 */
पूर्ण;

/* reg_ptar_key_type
 * TCAM key type क्रम the region.
 * Access: WO
 */
MLXSW_ITEM32(reg, ptar, key_type, 0x00, 0, 8);

/* reg_ptar_region_size
 * TCAM region size. When allocating/resizing this is the requested size,
 * the response is the actual size. Note that actual size may be
 * larger than requested.
 * Allowed range 1 .. cap_max_rules-1
 * Reserved during op deallocate.
 * Access: WO
 */
MLXSW_ITEM32(reg, ptar, region_size, 0x04, 0, 16);

/* reg_ptar_region_id
 * Region identअगरier
 * Range 0 .. cap_max_regions-1
 * Access: Index
 */
MLXSW_ITEM32(reg, ptar, region_id, 0x08, 0, 16);

/* reg_ptar_tcam_region_info
 * Opaque object that represents the TCAM region.
 * Returned when allocating a region.
 * Provided by software क्रम ACL generation and region deallocation and resize.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ptar, tcam_region_info, 0x10,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

/* reg_ptar_flexible_key_id
 * Identअगरier of the Flexible Key.
 * Only valid अगर key_type == "FLEX_KEY"
 * The key size will be rounded up to one of the following values:
 * 9B, 18B, 36B, 54B.
 * This field is reserved क्रम in resize operation.
 * Access: WO
 */
MLXSW_ITEM8_INDEXED(reg, ptar, flexible_key_id, 0x20, 0, 8,
		    MLXSW_REG_PTAR_KEY_ID_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_ptar_pack(अक्षर *payload, क्रमागत mlxsw_reg_ptar_op op,
				       क्रमागत mlxsw_reg_ptar_key_type key_type,
				       u16 region_size, u16 region_id,
				       स्थिर अक्षर *tcam_region_info)
अणु
	MLXSW_REG_ZERO(ptar, payload);
	mlxsw_reg_ptar_op_set(payload, op);
	mlxsw_reg_ptar_action_set_type_set(payload, 2); /* "flexible" */
	mlxsw_reg_ptar_key_type_set(payload, key_type);
	mlxsw_reg_ptar_region_size_set(payload, region_size);
	mlxsw_reg_ptar_region_id_set(payload, region_id);
	mlxsw_reg_ptar_tcam_region_info_स_नकल_to(payload, tcam_region_info);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptar_key_id_pack(अक्षर *payload, पूर्णांक index,
					      u16 key_id)
अणु
	mlxsw_reg_ptar_flexible_key_id_set(payload, index, key_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptar_unpack(अक्षर *payload, अक्षर *tcam_region_info)
अणु
	mlxsw_reg_ptar_tcam_region_info_स_नकल_from(payload, tcam_region_info);
पूर्ण

/* PPBS - Policy-Engine Policy Based Switching Register
 * ----------------------------------------------------
 * This रेजिस्टर retrieves and sets Policy Based Switching Table entries.
 */
#घोषणा MLXSW_REG_PPBS_ID 0x300C
#घोषणा MLXSW_REG_PPBS_LEN 0x14

MLXSW_REG_DEFINE(ppbs, MLXSW_REG_PPBS_ID, MLXSW_REG_PPBS_LEN);

/* reg_ppbs_pbs_ptr
 * Index पूर्णांकo the PBS table.
 * For Spectrum, the index poपूर्णांकs to the KVD Linear.
 * Access: Index
 */
MLXSW_ITEM32(reg, ppbs, pbs_ptr, 0x08, 0, 24);

/* reg_ppbs_प्रणाली_port
 * Unique port identअगरier क्रम the final destination of the packet.
 * Access: RW
 */
MLXSW_ITEM32(reg, ppbs, प्रणाली_port, 0x10, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_ppbs_pack(अक्षर *payload, u32 pbs_ptr,
				       u16 प्रणाली_port)
अणु
	MLXSW_REG_ZERO(ppbs, payload);
	mlxsw_reg_ppbs_pbs_ptr_set(payload, pbs_ptr);
	mlxsw_reg_ppbs_प्रणाली_port_set(payload, प्रणाली_port);
पूर्ण

/* PRCR - Policy-Engine Rules Copy Register
 * ----------------------------------------
 * This रेजिस्टर is used क्रम accessing rules within a TCAM region.
 */
#घोषणा MLXSW_REG_PRCR_ID 0x300D
#घोषणा MLXSW_REG_PRCR_LEN 0x40

MLXSW_REG_DEFINE(prcr, MLXSW_REG_PRCR_ID, MLXSW_REG_PRCR_LEN);

क्रमागत mlxsw_reg_prcr_op अणु
	/* Move rules. Moves the rules from "tcam_region_info" starting
	 * at offset "offset" to "dest_tcam_region_info"
	 * at offset "dest_offset."
	 */
	MLXSW_REG_PRCR_OP_MOVE,
	/* Copy rules. Copies the rules from "tcam_region_info" starting
	 * at offset "offset" to "dest_tcam_region_info"
	 * at offset "dest_offset."
	 */
	MLXSW_REG_PRCR_OP_COPY,
पूर्ण;

/* reg_prcr_op
 * Access: OP
 */
MLXSW_ITEM32(reg, prcr, op, 0x00, 28, 4);

/* reg_prcr_offset
 * Offset within the source region to copy/move from.
 * Access: Index
 */
MLXSW_ITEM32(reg, prcr, offset, 0x00, 0, 16);

/* reg_prcr_size
 * The number of rules to copy/move.
 * Access: WO
 */
MLXSW_ITEM32(reg, prcr, size, 0x04, 0, 16);

/* reg_prcr_tcam_region_info
 * Opaque object that represents the source TCAM region.
 * Access: Index
 */
MLXSW_ITEM_BUF(reg, prcr, tcam_region_info, 0x10,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

/* reg_prcr_dest_offset
 * Offset within the source region to copy/move to.
 * Access: Index
 */
MLXSW_ITEM32(reg, prcr, dest_offset, 0x20, 0, 16);

/* reg_prcr_dest_tcam_region_info
 * Opaque object that represents the destination TCAM region.
 * Access: Index
 */
MLXSW_ITEM_BUF(reg, prcr, dest_tcam_region_info, 0x30,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

अटल अंतरभूत व्योम mlxsw_reg_prcr_pack(अक्षर *payload, क्रमागत mlxsw_reg_prcr_op op,
				       स्थिर अक्षर *src_tcam_region_info,
				       u16 src_offset,
				       स्थिर अक्षर *dest_tcam_region_info,
				       u16 dest_offset, u16 size)
अणु
	MLXSW_REG_ZERO(prcr, payload);
	mlxsw_reg_prcr_op_set(payload, op);
	mlxsw_reg_prcr_offset_set(payload, src_offset);
	mlxsw_reg_prcr_size_set(payload, size);
	mlxsw_reg_prcr_tcam_region_info_स_नकल_to(payload,
						  src_tcam_region_info);
	mlxsw_reg_prcr_dest_offset_set(payload, dest_offset);
	mlxsw_reg_prcr_dest_tcam_region_info_स_नकल_to(payload,
						       dest_tcam_region_info);
पूर्ण

/* PEFA - Policy-Engine Extended Flexible Action Register
 * ------------------------------------------------------
 * This रेजिस्टर is used क्रम accessing an extended flexible action entry
 * in the central KVD Linear Database.
 */
#घोषणा MLXSW_REG_PEFA_ID 0x300F
#घोषणा MLXSW_REG_PEFA_LEN 0xB0

MLXSW_REG_DEFINE(pefa, MLXSW_REG_PEFA_ID, MLXSW_REG_PEFA_LEN);

/* reg_pefa_index
 * Index in the KVD Linear Centralized Database.
 * Access: Index
 */
MLXSW_ITEM32(reg, pefa, index, 0x00, 0, 24);

/* reg_pefa_a
 * Index in the KVD Linear Centralized Database.
 * Activity
 * For a new entry: set अगर ca=0, clear अगर ca=1
 * Set अगर a packet lookup has hit on the specअगरic entry
 * Access: RO
 */
MLXSW_ITEM32(reg, pefa, a, 0x04, 29, 1);

/* reg_pefa_ca
 * Clear activity
 * When ग_लिखो: activity is according to this field
 * When पढ़ो: after पढ़ोing the activity is cleared according to ca
 * Access: OP
 */
MLXSW_ITEM32(reg, pefa, ca, 0x04, 24, 1);

#घोषणा MLXSW_REG_FLEX_ACTION_SET_LEN 0xA8

/* reg_pefa_flex_action_set
 * Action-set to perक्रमm when rule is matched.
 * Must be zero padded अगर action set is लघुer.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, pefa, flex_action_set, 0x08, MLXSW_REG_FLEX_ACTION_SET_LEN);

अटल अंतरभूत व्योम mlxsw_reg_pefa_pack(अक्षर *payload, u32 index, bool ca,
				       स्थिर अक्षर *flex_action_set)
अणु
	MLXSW_REG_ZERO(pefa, payload);
	mlxsw_reg_pefa_index_set(payload, index);
	mlxsw_reg_pefa_ca_set(payload, ca);
	अगर (flex_action_set)
		mlxsw_reg_pefa_flex_action_set_स_नकल_to(payload,
							 flex_action_set);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pefa_unpack(अक्षर *payload, bool *p_a)
अणु
	*p_a = mlxsw_reg_pefa_a_get(payload);
पूर्ण

/* PEMRBT - Policy-Engine Multicast Router Binding Table Register
 * --------------------------------------------------------------
 * This रेजिस्टर is used क्रम binding Multicast router to an ACL group
 * that serves the MC router.
 * This रेजिस्टर is not supported by SwitchX/-2 and Spectrum.
 */
#घोषणा MLXSW_REG_PEMRBT_ID 0x3014
#घोषणा MLXSW_REG_PEMRBT_LEN 0x14

MLXSW_REG_DEFINE(pemrbt, MLXSW_REG_PEMRBT_ID, MLXSW_REG_PEMRBT_LEN);

क्रमागत mlxsw_reg_pemrbt_protocol अणु
	MLXSW_REG_PEMRBT_PROTO_IPV4,
	MLXSW_REG_PEMRBT_PROTO_IPV6,
पूर्ण;

/* reg_pemrbt_protocol
 * Access: Index
 */
MLXSW_ITEM32(reg, pemrbt, protocol, 0x00, 0, 1);

/* reg_pemrbt_group_id
 * ACL group identअगरier.
 * Range 0..cap_max_acl_groups-1
 * Access: RW
 */
MLXSW_ITEM32(reg, pemrbt, group_id, 0x10, 0, 16);

अटल अंतरभूत व्योम
mlxsw_reg_pemrbt_pack(अक्षर *payload, क्रमागत mlxsw_reg_pemrbt_protocol protocol,
		      u16 group_id)
अणु
	MLXSW_REG_ZERO(pemrbt, payload);
	mlxsw_reg_pemrbt_protocol_set(payload, protocol);
	mlxsw_reg_pemrbt_group_id_set(payload, group_id);
पूर्ण

/* PTCE-V2 - Policy-Engine TCAM Entry Register Version 2
 * -----------------------------------------------------
 * This रेजिस्टर is used क्रम accessing rules within a TCAM region.
 * It is a new version of PTCE in order to support wider key,
 * mask and action within a TCAM region. This रेजिस्टर is not supported
 * by SwitchX and SwitchX-2.
 */
#घोषणा MLXSW_REG_PTCE2_ID 0x3017
#घोषणा MLXSW_REG_PTCE2_LEN 0x1D8

MLXSW_REG_DEFINE(ptce2, MLXSW_REG_PTCE2_ID, MLXSW_REG_PTCE2_LEN);

/* reg_ptce2_v
 * Valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce2, v, 0x00, 31, 1);

/* reg_ptce2_a
 * Activity. Set अगर a packet lookup has hit on the specअगरic entry.
 * To clear the "a" bit, use "clear activity" op or "clear on read" op.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptce2, a, 0x00, 30, 1);

क्रमागत mlxsw_reg_ptce2_op अणु
	/* Read operation. */
	MLXSW_REG_PTCE2_OP_QUERY_READ = 0,
	/* clear on पढ़ो operation. Used to पढ़ो entry
	 * and clear Activity bit.
	 */
	MLXSW_REG_PTCE2_OP_QUERY_CLEAR_ON_READ = 1,
	/* Write operation. Used to ग_लिखो a new entry to the table.
	 * All R/W fields are relevant क्रम new entry. Activity bit is set
	 * क्रम new entries - Note ग_लिखो with v = 0 will delete the entry.
	 */
	MLXSW_REG_PTCE2_OP_WRITE_WRITE = 0,
	/* Update action. Only action set will be updated. */
	MLXSW_REG_PTCE2_OP_WRITE_UPDATE = 1,
	/* Clear activity. A bit is cleared क्रम the entry. */
	MLXSW_REG_PTCE2_OP_WRITE_CLEAR_ACTIVITY = 2,
पूर्ण;

/* reg_ptce2_op
 * Access: OP
 */
MLXSW_ITEM32(reg, ptce2, op, 0x00, 20, 3);

/* reg_ptce2_offset
 * Access: Index
 */
MLXSW_ITEM32(reg, ptce2, offset, 0x00, 0, 16);

/* reg_ptce2_priority
 * Priority of the rule, higher values win. The range is 1..cap_kvd_size-1.
 * Note: priority करोes not have to be unique per rule.
 * Within a region, higher priority should have lower offset (no limitation
 * between regions in a multi-region).
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce2, priority, 0x04, 0, 24);

/* reg_ptce2_tcam_region_info
 * Opaque object that represents the TCAM region.
 * Access: Index
 */
MLXSW_ITEM_BUF(reg, ptce2, tcam_region_info, 0x10,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

#घोषणा MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN 96

/* reg_ptce2_flex_key_blocks
 * ACL Key.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ptce2, flex_key_blocks, 0x20,
	       MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);

/* reg_ptce2_mask
 * mask- in the same size as key. A bit that is set directs the TCAM
 * to compare the corresponding bit in key. A bit that is clear directs
 * the TCAM to ignore the corresponding bit in key.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ptce2, mask, 0x80,
	       MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);

/* reg_ptce2_flex_action_set
 * ACL action set.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ptce2, flex_action_set, 0xE0,
	       MLXSW_REG_FLEX_ACTION_SET_LEN);

अटल अंतरभूत व्योम mlxsw_reg_ptce2_pack(अक्षर *payload, bool valid,
					क्रमागत mlxsw_reg_ptce2_op op,
					स्थिर अक्षर *tcam_region_info,
					u16 offset, u32 priority)
अणु
	MLXSW_REG_ZERO(ptce2, payload);
	mlxsw_reg_ptce2_v_set(payload, valid);
	mlxsw_reg_ptce2_op_set(payload, op);
	mlxsw_reg_ptce2_offset_set(payload, offset);
	mlxsw_reg_ptce2_priority_set(payload, priority);
	mlxsw_reg_ptce2_tcam_region_info_स_नकल_to(payload, tcam_region_info);
पूर्ण

/* PERPT - Policy-Engine ERP Table Register
 * ----------------------------------------
 * This रेजिस्टर adds and हटाओs eRPs from the eRP table.
 */
#घोषणा MLXSW_REG_PERPT_ID 0x3021
#घोषणा MLXSW_REG_PERPT_LEN 0x80

MLXSW_REG_DEFINE(perpt, MLXSW_REG_PERPT_ID, MLXSW_REG_PERPT_LEN);

/* reg_perpt_erpt_bank
 * eRP table bank.
 * Range 0 .. cap_max_erp_table_banks - 1
 * Access: Index
 */
MLXSW_ITEM32(reg, perpt, erpt_bank, 0x00, 16, 4);

/* reg_perpt_erpt_index
 * Index to eRP table within the eRP bank.
 * Range is 0 .. cap_max_erp_table_bank_size - 1
 * Access: Index
 */
MLXSW_ITEM32(reg, perpt, erpt_index, 0x00, 0, 8);

क्रमागत mlxsw_reg_perpt_key_size अणु
	MLXSW_REG_PERPT_KEY_SIZE_2KB,
	MLXSW_REG_PERPT_KEY_SIZE_4KB,
	MLXSW_REG_PERPT_KEY_SIZE_8KB,
	MLXSW_REG_PERPT_KEY_SIZE_12KB,
पूर्ण;

/* reg_perpt_key_size
 * Access: OP
 */
MLXSW_ITEM32(reg, perpt, key_size, 0x04, 0, 4);

/* reg_perpt_bf_bypass
 * 0 - The eRP is used only अगर bloom filter state is set क्रम the given
 * rule.
 * 1 - The eRP is used regardless of bloom filter state.
 * The bypass is an OR condition of region_id or eRP. See PERCR.bf_bypass
 * Access: RW
 */
MLXSW_ITEM32(reg, perpt, bf_bypass, 0x08, 8, 1);

/* reg_perpt_erp_id
 * eRP ID क्रम use by the rules.
 * Access: RW
 */
MLXSW_ITEM32(reg, perpt, erp_id, 0x08, 0, 4);

/* reg_perpt_erpt_base_bank
 * Base eRP table bank, poपूर्णांकs to head of erp_vector
 * Range is 0 .. cap_max_erp_table_banks - 1
 * Access: OP
 */
MLXSW_ITEM32(reg, perpt, erpt_base_bank, 0x0C, 16, 4);

/* reg_perpt_erpt_base_index
 * Base index to eRP table within the eRP bank
 * Range is 0 .. cap_max_erp_table_bank_size - 1
 * Access: OP
 */
MLXSW_ITEM32(reg, perpt, erpt_base_index, 0x0C, 0, 8);

/* reg_perpt_erp_index_in_vector
 * eRP index in the vector.
 * Access: OP
 */
MLXSW_ITEM32(reg, perpt, erp_index_in_vector, 0x10, 0, 4);

/* reg_perpt_erp_vector
 * eRP vector.
 * Access: OP
 */
MLXSW_ITEM_BIT_ARRAY(reg, perpt, erp_vector, 0x14, 4, 1);

/* reg_perpt_mask
 * Mask
 * 0 - A-TCAM will ignore the bit in key
 * 1 - A-TCAM will compare the bit in key
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, perpt, mask, 0x20, MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);

अटल अंतरभूत व्योम mlxsw_reg_perpt_erp_vector_pack(अक्षर *payload,
						   अचिन्हित दीर्घ *erp_vector,
						   अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ bit;

	क्रम_each_set_bit(bit, erp_vector, size)
		mlxsw_reg_perpt_erp_vector_set(payload, bit, true);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_perpt_pack(अक्षर *payload, u8 erpt_bank, u8 erpt_index,
		     क्रमागत mlxsw_reg_perpt_key_size key_size, u8 erp_id,
		     u8 erpt_base_bank, u8 erpt_base_index, u8 erp_index,
		     अक्षर *mask)
अणु
	MLXSW_REG_ZERO(perpt, payload);
	mlxsw_reg_perpt_erpt_bank_set(payload, erpt_bank);
	mlxsw_reg_perpt_erpt_index_set(payload, erpt_index);
	mlxsw_reg_perpt_key_size_set(payload, key_size);
	mlxsw_reg_perpt_bf_bypass_set(payload, false);
	mlxsw_reg_perpt_erp_id_set(payload, erp_id);
	mlxsw_reg_perpt_erpt_base_bank_set(payload, erpt_base_bank);
	mlxsw_reg_perpt_erpt_base_index_set(payload, erpt_base_index);
	mlxsw_reg_perpt_erp_index_in_vector_set(payload, erp_index);
	mlxsw_reg_perpt_mask_स_नकल_to(payload, mask);
पूर्ण

/* PERAR - Policy-Engine Region Association Register
 * -------------------------------------------------
 * This रेजिस्टर associates a hw region क्रम region_id's. Changing on the fly
 * is supported by the device.
 */
#घोषणा MLXSW_REG_PERAR_ID 0x3026
#घोषणा MLXSW_REG_PERAR_LEN 0x08

MLXSW_REG_DEFINE(perar, MLXSW_REG_PERAR_ID, MLXSW_REG_PERAR_LEN);

/* reg_perar_region_id
 * Region identअगरier
 * Range 0 .. cap_max_regions-1
 * Access: Index
 */
MLXSW_ITEM32(reg, perar, region_id, 0x00, 0, 16);

अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_reg_perar_hw_regions_needed(अचिन्हित पूर्णांक block_num)
अणु
	वापस DIV_ROUND_UP(block_num, 4);
पूर्ण

/* reg_perar_hw_region
 * HW Region
 * Range 0 .. cap_max_regions-1
 * Default: hw_region = region_id
 * For a 8 key block region, 2 consecutive regions are used
 * For a 12 key block region, 3 consecutive regions are used
 * Access: RW
 */
MLXSW_ITEM32(reg, perar, hw_region, 0x04, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_perar_pack(अक्षर *payload, u16 region_id,
					u16 hw_region)
अणु
	MLXSW_REG_ZERO(perar, payload);
	mlxsw_reg_perar_region_id_set(payload, region_id);
	mlxsw_reg_perar_hw_region_set(payload, hw_region);
पूर्ण

/* PTCE-V3 - Policy-Engine TCAM Entry Register Version 3
 * -----------------------------------------------------
 * This रेजिस्टर is a new version of PTCE-V2 in order to support the
 * A-TCAM. This रेजिस्टर is not supported by SwitchX/-2 and Spectrum.
 */
#घोषणा MLXSW_REG_PTCE3_ID 0x3027
#घोषणा MLXSW_REG_PTCE3_LEN 0xF0

MLXSW_REG_DEFINE(ptce3, MLXSW_REG_PTCE3_ID, MLXSW_REG_PTCE3_LEN);

/* reg_ptce3_v
 * Valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce3, v, 0x00, 31, 1);

क्रमागत mlxsw_reg_ptce3_op अणु
	/* Write operation. Used to ग_लिखो a new entry to the table.
	 * All R/W fields are relevant क्रम new entry. Activity bit is set
	 * क्रम new entries. Write with v = 0 will delete the entry. Must
	 * not be used अगर an entry exists.
	 */
	 MLXSW_REG_PTCE3_OP_WRITE_WRITE = 0,
	 /* Update operation */
	 MLXSW_REG_PTCE3_OP_WRITE_UPDATE = 1,
	 /* Read operation */
	 MLXSW_REG_PTCE3_OP_QUERY_READ = 0,
पूर्ण;

/* reg_ptce3_op
 * Access: OP
 */
MLXSW_ITEM32(reg, ptce3, op, 0x00, 20, 3);

/* reg_ptce3_priority
 * Priority of the rule. Higher values win.
 * For Spectrum-2 range is 1..cap_kvd_size - 1
 * Note: Priority करोes not have to be unique per rule.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce3, priority, 0x04, 0, 24);

/* reg_ptce3_tcam_region_info
 * Opaque object that represents the TCAM region.
 * Access: Index
 */
MLXSW_ITEM_BUF(reg, ptce3, tcam_region_info, 0x10,
	       MLXSW_REG_PXXX_TCAM_REGION_INFO_LEN);

/* reg_ptce3_flex2_key_blocks
 * ACL key. The key must be masked according to eRP (अगर exists) or
 * according to master mask.
 * Access: Index
 */
MLXSW_ITEM_BUF(reg, ptce3, flex2_key_blocks, 0x20,
	       MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);

/* reg_ptce3_erp_id
 * eRP ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptce3, erp_id, 0x80, 0, 4);

/* reg_ptce3_delta_start
 * Start poपूर्णांक of delta_value and delta_mask, in bits. Must not exceed
 * num_key_blocks * 36 - 8. Reserved when delta_mask = 0.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptce3, delta_start, 0x84, 0, 10);

/* reg_ptce3_delta_mask
 * Delta mask.
 * 0 - Ignore relevant bit in delta_value
 * 1 - Compare relevant bit in delta_value
 * Delta mask must not be set क्रम reserved fields in the key blocks.
 * Note: No delta when no eRPs. Thus, क्रम regions with
 * PERERP.erpt_poपूर्णांकer_valid = 0 the delta mask must be 0.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptce3, delta_mask, 0x88, 16, 8);

/* reg_ptce3_delta_value
 * Delta value.
 * Bits which are masked by delta_mask must be 0.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptce3, delta_value, 0x88, 0, 8);

/* reg_ptce3_prune_vector
 * Pruning vector relative to the PERPT.erp_id.
 * Used क्रम reducing lookups.
 * 0 - NEED: Do a lookup using the eRP.
 * 1 - PRUNE: Do not perक्रमm a lookup using the eRP.
 * Maybe be modअगरied by PEAPBL and PEAPBM.
 * Note: In Spectrum-2, a region of 8 key blocks must be set to either
 * all 1's or all 0's.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, ptce3, prune_vector, 0x90, 4, 1);

/* reg_ptce3_prune_ctcam
 * Pruning on C-TCAM. Used क्रम reducing lookups.
 * 0 - NEED: Do a lookup in the C-TCAM.
 * 1 - PRUNE: Do not perक्रमm a lookup in the C-TCAM.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce3, prune_ctcam, 0x94, 31, 1);

/* reg_ptce3_large_exists
 * Large entry key ID exists.
 * Within the region:
 * 0 - SINGLE: The large_entry_key_id is not currently in use.
 * For rule insert: The MSB of the key (blocks 6..11) will be added.
 * For rule delete: The MSB of the key will be हटाओd.
 * 1 - NON_SINGLE: The large_entry_key_id is currently in use.
 * For rule insert: The MSB of the key (blocks 6..11) will not be added.
 * For rule delete: The MSB of the key will not be हटाओd.
 * Access: WO
 */
MLXSW_ITEM32(reg, ptce3, large_exists, 0x98, 31, 1);

/* reg_ptce3_large_entry_key_id
 * Large entry key ID.
 * A key क्रम 12 key blocks rules. Reserved when region has less than 12 key
 * blocks. Must be dअगरferent क्रम dअगरferent keys which have the same common
 * 6 key blocks (MSB, blocks 6..11) key within a region.
 * Range is 0..cap_max_pe_large_key_id - 1
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce3, large_entry_key_id, 0x98, 0, 24);

/* reg_ptce3_action_poपूर्णांकer
 * Poपूर्णांकer to action.
 * Range is 0..cap_max_kvd_action_sets - 1
 * Access: RW
 */
MLXSW_ITEM32(reg, ptce3, action_poपूर्णांकer, 0xA0, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_ptce3_pack(अक्षर *payload, bool valid,
					क्रमागत mlxsw_reg_ptce3_op op,
					u32 priority,
					स्थिर अक्षर *tcam_region_info,
					स्थिर अक्षर *key, u8 erp_id,
					u16 delta_start, u8 delta_mask,
					u8 delta_value, bool large_exists,
					u32 lkey_id, u32 action_poपूर्णांकer)
अणु
	MLXSW_REG_ZERO(ptce3, payload);
	mlxsw_reg_ptce3_v_set(payload, valid);
	mlxsw_reg_ptce3_op_set(payload, op);
	mlxsw_reg_ptce3_priority_set(payload, priority);
	mlxsw_reg_ptce3_tcam_region_info_स_नकल_to(payload, tcam_region_info);
	mlxsw_reg_ptce3_flex2_key_blocks_स_नकल_to(payload, key);
	mlxsw_reg_ptce3_erp_id_set(payload, erp_id);
	mlxsw_reg_ptce3_delta_start_set(payload, delta_start);
	mlxsw_reg_ptce3_delta_mask_set(payload, delta_mask);
	mlxsw_reg_ptce3_delta_value_set(payload, delta_value);
	mlxsw_reg_ptce3_large_exists_set(payload, large_exists);
	mlxsw_reg_ptce3_large_entry_key_id_set(payload, lkey_id);
	mlxsw_reg_ptce3_action_poपूर्णांकer_set(payload, action_poपूर्णांकer);
पूर्ण

/* PERCR - Policy-Engine Region Configuration Register
 * ---------------------------------------------------
 * This रेजिस्टर configures the region parameters. The region_id must be
 * allocated.
 */
#घोषणा MLXSW_REG_PERCR_ID 0x302A
#घोषणा MLXSW_REG_PERCR_LEN 0x80

MLXSW_REG_DEFINE(percr, MLXSW_REG_PERCR_ID, MLXSW_REG_PERCR_LEN);

/* reg_percr_region_id
 * Region identअगरier.
 * Range 0..cap_max_regions-1
 * Access: Index
 */
MLXSW_ITEM32(reg, percr, region_id, 0x00, 0, 16);

/* reg_percr_atcam_ignore_prune
 * Ignore prune_vector by other A-TCAM rules. Used e.g., क्रम a new rule.
 * Access: RW
 */
MLXSW_ITEM32(reg, percr, atcam_ignore_prune, 0x04, 25, 1);

/* reg_percr_ctcam_ignore_prune
 * Ignore prune_ctcam by other A-TCAM rules. Used e.g., क्रम a new rule.
 * Access: RW
 */
MLXSW_ITEM32(reg, percr, ctcam_ignore_prune, 0x04, 24, 1);

/* reg_percr_bf_bypass
 * Bloom filter bypass.
 * 0 - Bloom filter is used (शेष)
 * 1 - Bloom filter is bypassed. The bypass is an OR condition of
 * region_id or eRP. See PERPT.bf_bypass
 * Access: RW
 */
MLXSW_ITEM32(reg, percr, bf_bypass, 0x04, 16, 1);

/* reg_percr_master_mask
 * Master mask. Logical OR mask of all masks of all rules of a region
 * (both A-TCAM and C-TCAM). When there are no eRPs
 * (erpt_poपूर्णांकer_valid = 0), then this provides the mask.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, percr, master_mask, 0x20, 96);

अटल अंतरभूत व्योम mlxsw_reg_percr_pack(अक्षर *payload, u16 region_id)
अणु
	MLXSW_REG_ZERO(percr, payload);
	mlxsw_reg_percr_region_id_set(payload, region_id);
	mlxsw_reg_percr_atcam_ignore_prune_set(payload, false);
	mlxsw_reg_percr_ctcam_ignore_prune_set(payload, false);
	mlxsw_reg_percr_bf_bypass_set(payload, false);
पूर्ण

/* PERERP - Policy-Engine Region eRP Register
 * ------------------------------------------
 * This रेजिस्टर configures the region eRP. The region_id must be
 * allocated.
 */
#घोषणा MLXSW_REG_PERERP_ID 0x302B
#घोषणा MLXSW_REG_PERERP_LEN 0x1C

MLXSW_REG_DEFINE(pererp, MLXSW_REG_PERERP_ID, MLXSW_REG_PERERP_LEN);

/* reg_pererp_region_id
 * Region identअगरier.
 * Range 0..cap_max_regions-1
 * Access: Index
 */
MLXSW_ITEM32(reg, pererp, region_id, 0x00, 0, 16);

/* reg_pererp_ctcam_le
 * C-TCAM lookup enable. Reserved when erpt_poपूर्णांकer_valid = 0.
 * Access: RW
 */
MLXSW_ITEM32(reg, pererp, ctcam_le, 0x04, 28, 1);

/* reg_pererp_erpt_poपूर्णांकer_valid
 * erpt_poपूर्णांकer is valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, pererp, erpt_poपूर्णांकer_valid, 0x10, 31, 1);

/* reg_pererp_erpt_bank_poपूर्णांकer
 * Poपूर्णांकer to eRP table bank. May be modअगरied at any समय.
 * Range 0..cap_max_erp_table_banks-1
 * Reserved when erpt_poपूर्णांकer_valid = 0
 */
MLXSW_ITEM32(reg, pererp, erpt_bank_poपूर्णांकer, 0x10, 16, 4);

/* reg_pererp_erpt_poपूर्णांकer
 * Poपूर्णांकer to eRP table within the eRP bank. Can be changed क्रम an
 * existing region.
 * Range 0..cap_max_erp_table_size-1
 * Reserved when erpt_poपूर्णांकer_valid = 0
 * Access: RW
 */
MLXSW_ITEM32(reg, pererp, erpt_poपूर्णांकer, 0x10, 0, 8);

/* reg_pererp_erpt_vector
 * Vector of allowed eRP indexes starting from erpt_poपूर्णांकer within the
 * erpt_bank_poपूर्णांकer. Next entries will be in next bank.
 * Note that eRP index is used and not eRP ID.
 * Reserved when erpt_poपूर्णांकer_valid = 0
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, pererp, erpt_vector, 0x14, 4, 1);

/* reg_pererp_master_rp_id
 * Master RP ID. When there are no eRPs, then this provides the eRP ID
 * क्रम the lookup. Can be changed क्रम an existing region.
 * Reserved when erpt_poपूर्णांकer_valid = 1
 * Access: RW
 */
MLXSW_ITEM32(reg, pererp, master_rp_id, 0x18, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_pererp_erp_vector_pack(अक्षर *payload,
						    अचिन्हित दीर्घ *erp_vector,
						    अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ bit;

	क्रम_each_set_bit(bit, erp_vector, size)
		mlxsw_reg_pererp_erpt_vector_set(payload, bit, true);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pererp_pack(अक्षर *payload, u16 region_id,
					 bool ctcam_le, bool erpt_poपूर्णांकer_valid,
					 u8 erpt_bank_poपूर्णांकer, u8 erpt_poपूर्णांकer,
					 u8 master_rp_id)
अणु
	MLXSW_REG_ZERO(pererp, payload);
	mlxsw_reg_pererp_region_id_set(payload, region_id);
	mlxsw_reg_pererp_ctcam_le_set(payload, ctcam_le);
	mlxsw_reg_pererp_erpt_poपूर्णांकer_valid_set(payload, erpt_poपूर्णांकer_valid);
	mlxsw_reg_pererp_erpt_bank_poपूर्णांकer_set(payload, erpt_bank_poपूर्णांकer);
	mlxsw_reg_pererp_erpt_poपूर्णांकer_set(payload, erpt_poपूर्णांकer);
	mlxsw_reg_pererp_master_rp_id_set(payload, master_rp_id);
पूर्ण

/* PEABFE - Policy-Engine Algorithmic Bloom Filter Entries Register
 * ----------------------------------------------------------------
 * This रेजिस्टर configures the Bloom filter entries.
 */
#घोषणा MLXSW_REG_PEABFE_ID 0x3022
#घोषणा MLXSW_REG_PEABFE_BASE_LEN 0x10
#घोषणा MLXSW_REG_PEABFE_BF_REC_LEN 0x4
#घोषणा MLXSW_REG_PEABFE_BF_REC_MAX_COUNT 256
#घोषणा MLXSW_REG_PEABFE_LEN (MLXSW_REG_PEABFE_BASE_LEN + \
			      MLXSW_REG_PEABFE_BF_REC_LEN * \
			      MLXSW_REG_PEABFE_BF_REC_MAX_COUNT)

MLXSW_REG_DEFINE(peabfe, MLXSW_REG_PEABFE_ID, MLXSW_REG_PEABFE_LEN);

/* reg_peabfe_size
 * Number of BF entries to be updated.
 * Range 1..256
 * Access: Op
 */
MLXSW_ITEM32(reg, peabfe, size, 0x00, 0, 9);

/* reg_peabfe_bf_entry_state
 * Bloom filter state
 * 0 - Clear
 * 1 - Set
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, peabfe, bf_entry_state,
		     MLXSW_REG_PEABFE_BASE_LEN,	31, 1,
		     MLXSW_REG_PEABFE_BF_REC_LEN, 0x00, false);

/* reg_peabfe_bf_entry_bank
 * Bloom filter bank ID
 * Range 0..cap_max_erp_table_banks-1
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, peabfe, bf_entry_bank,
		     MLXSW_REG_PEABFE_BASE_LEN,	24, 4,
		     MLXSW_REG_PEABFE_BF_REC_LEN, 0x00, false);

/* reg_peabfe_bf_entry_index
 * Bloom filter entry index
 * Range 0..2^cap_max_bf_log-1
 * Access: Index
 */
MLXSW_ITEM32_INDEXED(reg, peabfe, bf_entry_index,
		     MLXSW_REG_PEABFE_BASE_LEN,	0, 24,
		     MLXSW_REG_PEABFE_BF_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_peabfe_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(peabfe, payload);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_peabfe_rec_pack(अक्षर *payload, पूर्णांक rec_index,
					     u8 state, u8 bank, u32 bf_index)
अणु
	u8 num_rec = mlxsw_reg_peabfe_size_get(payload);

	अगर (rec_index >= num_rec)
		mlxsw_reg_peabfe_size_set(payload, rec_index + 1);
	mlxsw_reg_peabfe_bf_entry_state_set(payload, rec_index, state);
	mlxsw_reg_peabfe_bf_entry_bank_set(payload, rec_index, bank);
	mlxsw_reg_peabfe_bf_entry_index_set(payload, rec_index, bf_index);
पूर्ण

/* IEDR - Infraकाष्ठाure Entry Delete Register
 * ----------------------------------------------------
 * This रेजिस्टर is used क्रम deleting entries from the entry tables.
 * It is legitimate to attempt to delete a nonexisting entry (the device will
 * respond as a good flow).
 */
#घोषणा MLXSW_REG_IEDR_ID 0x3804
#घोषणा MLXSW_REG_IEDR_BASE_LEN 0x10 /* base length, without records */
#घोषणा MLXSW_REG_IEDR_REC_LEN 0x8 /* record length */
#घोषणा MLXSW_REG_IEDR_REC_MAX_COUNT 64
#घोषणा MLXSW_REG_IEDR_LEN (MLXSW_REG_IEDR_BASE_LEN +	\
			    MLXSW_REG_IEDR_REC_LEN *	\
			    MLXSW_REG_IEDR_REC_MAX_COUNT)

MLXSW_REG_DEFINE(iedr, MLXSW_REG_IEDR_ID, MLXSW_REG_IEDR_LEN);

/* reg_iedr_num_rec
 * Number of records.
 * Access: OP
 */
MLXSW_ITEM32(reg, iedr, num_rec, 0x00, 0, 8);

/* reg_iedr_rec_type
 * Resource type.
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, iedr, rec_type, MLXSW_REG_IEDR_BASE_LEN, 24, 8,
		     MLXSW_REG_IEDR_REC_LEN, 0x00, false);

/* reg_iedr_rec_size
 * Size of entries करो be deleted. The unit is 1 entry, regardless of entry type.
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, iedr, rec_size, MLXSW_REG_IEDR_BASE_LEN, 0, 13,
		     MLXSW_REG_IEDR_REC_LEN, 0x00, false);

/* reg_iedr_rec_index_start
 * Resource index start.
 * Access: OP
 */
MLXSW_ITEM32_INDEXED(reg, iedr, rec_index_start, MLXSW_REG_IEDR_BASE_LEN, 0, 24,
		     MLXSW_REG_IEDR_REC_LEN, 0x04, false);

अटल अंतरभूत व्योम mlxsw_reg_iedr_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(iedr, payload);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_iedr_rec_pack(अक्षर *payload, पूर्णांक rec_index,
					   u8 rec_type, u16 rec_size,
					   u32 rec_index_start)
अणु
	u8 num_rec = mlxsw_reg_iedr_num_rec_get(payload);

	अगर (rec_index >= num_rec)
		mlxsw_reg_iedr_num_rec_set(payload, rec_index + 1);
	mlxsw_reg_iedr_rec_type_set(payload, rec_index, rec_type);
	mlxsw_reg_iedr_rec_size_set(payload, rec_index, rec_size);
	mlxsw_reg_iedr_rec_index_start_set(payload, rec_index, rec_index_start);
पूर्ण

/* QPTS - QoS Priority Trust State Register
 * ----------------------------------------
 * This रेजिस्टर controls the port policy to calculate the चयन priority and
 * packet color based on incoming packet fields.
 */
#घोषणा MLXSW_REG_QPTS_ID 0x4002
#घोषणा MLXSW_REG_QPTS_LEN 0x8

MLXSW_REG_DEFINE(qpts, MLXSW_REG_QPTS_ID, MLXSW_REG_QPTS_LEN);

/* reg_qpts_local_port
 * Local port number.
 * Access: Index
 *
 * Note: CPU port is supported.
 */
MLXSW_ITEM32(reg, qpts, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_qpts_trust_state अणु
	MLXSW_REG_QPTS_TRUST_STATE_PCP = 1,
	MLXSW_REG_QPTS_TRUST_STATE_DSCP = 2, /* For MPLS, trust EXP. */
पूर्ण;

/* reg_qpts_trust_state
 * Trust state क्रम a given port.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpts, trust_state, 0x04, 0, 3);

अटल अंतरभूत व्योम mlxsw_reg_qpts_pack(अक्षर *payload, u8 local_port,
				       क्रमागत mlxsw_reg_qpts_trust_state ts)
अणु
	MLXSW_REG_ZERO(qpts, payload);

	mlxsw_reg_qpts_local_port_set(payload, local_port);
	mlxsw_reg_qpts_trust_state_set(payload, ts);
पूर्ण

/* QPCR - QoS Policer Configuration Register
 * -----------------------------------------
 * The QPCR रेजिस्टर is used to create policers - that limit
 * the rate of bytes or packets via some trap group.
 */
#घोषणा MLXSW_REG_QPCR_ID 0x4004
#घोषणा MLXSW_REG_QPCR_LEN 0x28

MLXSW_REG_DEFINE(qpcr, MLXSW_REG_QPCR_ID, MLXSW_REG_QPCR_LEN);

क्रमागत mlxsw_reg_qpcr_g अणु
	MLXSW_REG_QPCR_G_GLOBAL = 2,
	MLXSW_REG_QPCR_G_STORM_CONTROL = 3,
पूर्ण;

/* reg_qpcr_g
 * The policer type.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpcr, g, 0x00, 14, 2);

/* reg_qpcr_pid
 * Policer ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpcr, pid, 0x00, 0, 14);

/* reg_qpcr_clear_counter
 * Clear counters.
 * Access: OP
 */
MLXSW_ITEM32(reg, qpcr, clear_counter, 0x04, 31, 1);

/* reg_qpcr_color_aware
 * Is the policer aware of colors.
 * Must be 0 (unaware) क्रम cpu port.
 * Access: RW क्रम unbounded policer. RO क्रम bounded policer.
 */
MLXSW_ITEM32(reg, qpcr, color_aware, 0x04, 15, 1);

/* reg_qpcr_bytes
 * Is policer limit is क्रम bytes per sec or packets per sec.
 * 0 - packets
 * 1 - bytes
 * Access: RW क्रम unbounded policer. RO क्रम bounded policer.
 */
MLXSW_ITEM32(reg, qpcr, bytes, 0x04, 14, 1);

क्रमागत mlxsw_reg_qpcr_ir_units अणु
	MLXSW_REG_QPCR_IR_UNITS_M,
	MLXSW_REG_QPCR_IR_UNITS_K,
पूर्ण;

/* reg_qpcr_ir_units
 * Policer's units क्रम cir and eir fields (क्रम bytes limits only)
 * 1 - 10^3
 * 0 - 10^6
 * Access: OP
 */
MLXSW_ITEM32(reg, qpcr, ir_units, 0x04, 12, 1);

क्रमागत mlxsw_reg_qpcr_rate_type अणु
	MLXSW_REG_QPCR_RATE_TYPE_SINGLE = 1,
	MLXSW_REG_QPCR_RATE_TYPE_DOUBLE = 2,
पूर्ण;

/* reg_qpcr_rate_type
 * Policer can have one limit (single rate) or 2 limits with specअगरic operation
 * क्रम packets that exceed the lower rate but not the upper one.
 * (For cpu port must be single rate)
 * Access: RW क्रम unbounded policer. RO क्रम bounded policer.
 */
MLXSW_ITEM32(reg, qpcr, rate_type, 0x04, 8, 2);

/* reg_qpc_cbs
 * Policer's committed burst size.
 * The policer is working with समय slices of 50 nano sec. By शेष every
 * slice is granted the proportionate share of the committed rate. If we want to
 * allow a slice to exceed that share (जबतक still keeping the rate per sec) we
 * can allow burst. The burst size is between the शेष proportionate share
 * (and no lower than 8) to 32Gb. (Even though giving a number higher than the
 * committed rate will result in exceeding the rate). The burst size must be a
 * log of 2 and will be determined by 2^cbs.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpcr, cbs, 0x08, 24, 6);

/* reg_qpcr_cir
 * Policer's committed rate.
 * The rate used क्रम sungle rate, the lower rate क्रम द्विगुन rate.
 * For bytes limits, the rate will be this value * the unit from ir_units.
 * (Resolution error is up to 1%).
 * Access: RW
 */
MLXSW_ITEM32(reg, qpcr, cir, 0x0C, 0, 32);

/* reg_qpcr_eir
 * Policer's exceed rate.
 * The higher rate क्रम द्विगुन rate, reserved क्रम single rate.
 * Lower rate क्रम द्विगुन rate policer.
 * For bytes limits, the rate will be this value * the unit from ir_units.
 * (Resolution error is up to 1%).
 * Access: RW
 */
MLXSW_ITEM32(reg, qpcr, eir, 0x10, 0, 32);

#घोषणा MLXSW_REG_QPCR_DOUBLE_RATE_ACTION 2

/* reg_qpcr_exceed_action.
 * What to करो with packets between the 2 limits क्रम द्विगुन rate.
 * Access: RW क्रम unbounded policer. RO क्रम bounded policer.
 */
MLXSW_ITEM32(reg, qpcr, exceed_action, 0x14, 0, 4);

क्रमागत mlxsw_reg_qpcr_action अणु
	/* Discard */
	MLXSW_REG_QPCR_ACTION_DISCARD = 1,
	/* Forward and set color to red.
	 * If the packet is पूर्णांकended to cpu port, it will be dropped.
	 */
	MLXSW_REG_QPCR_ACTION_FORWARD = 2,
पूर्ण;

/* reg_qpcr_violate_action
 * What to करो with packets that cross the cir limit (क्रम single rate) or the eir
 * limit (क्रम द्विगुन rate).
 * Access: RW क्रम unbounded policer. RO क्रम bounded policer.
 */
MLXSW_ITEM32(reg, qpcr, violate_action, 0x18, 0, 4);

/* reg_qpcr_violate_count
 * Counts the number of बार violate_action happened on this PID.
 * Access: RW
 */
MLXSW_ITEM64(reg, qpcr, violate_count, 0x20, 0, 64);

/* Packets */
#घोषणा MLXSW_REG_QPCR_LOWEST_CIR	1
#घोषणा MLXSW_REG_QPCR_HIGHEST_CIR	(2 * 1000 * 1000 * 1000) /* 2Gpps */
#घोषणा MLXSW_REG_QPCR_LOWEST_CBS	4
#घोषणा MLXSW_REG_QPCR_HIGHEST_CBS	24

/* Bandwidth */
#घोषणा MLXSW_REG_QPCR_LOWEST_CIR_BITS		1024 /* bps */
#घोषणा MLXSW_REG_QPCR_HIGHEST_CIR_BITS		2000000000000ULL /* 2Tbps */
#घोषणा MLXSW_REG_QPCR_LOWEST_CBS_BITS_SP1	4
#घोषणा MLXSW_REG_QPCR_LOWEST_CBS_BITS_SP2	4
#घोषणा MLXSW_REG_QPCR_HIGHEST_CBS_BITS_SP1	25
#घोषणा MLXSW_REG_QPCR_HIGHEST_CBS_BITS_SP2	31

अटल अंतरभूत व्योम mlxsw_reg_qpcr_pack(अक्षर *payload, u16 pid,
				       क्रमागत mlxsw_reg_qpcr_ir_units ir_units,
				       bool bytes, u32 cir, u16 cbs)
अणु
	MLXSW_REG_ZERO(qpcr, payload);
	mlxsw_reg_qpcr_pid_set(payload, pid);
	mlxsw_reg_qpcr_g_set(payload, MLXSW_REG_QPCR_G_GLOBAL);
	mlxsw_reg_qpcr_rate_type_set(payload, MLXSW_REG_QPCR_RATE_TYPE_SINGLE);
	mlxsw_reg_qpcr_violate_action_set(payload,
					  MLXSW_REG_QPCR_ACTION_DISCARD);
	mlxsw_reg_qpcr_cir_set(payload, cir);
	mlxsw_reg_qpcr_ir_units_set(payload, ir_units);
	mlxsw_reg_qpcr_bytes_set(payload, bytes);
	mlxsw_reg_qpcr_cbs_set(payload, cbs);
पूर्ण

/* QTCT - QoS Switch Traffic Class Table
 * -------------------------------------
 * Configures the mapping between the packet चयन priority and the
 * traffic class on the transmit port.
 */
#घोषणा MLXSW_REG_QTCT_ID 0x400A
#घोषणा MLXSW_REG_QTCT_LEN 0x08

MLXSW_REG_DEFINE(qtct, MLXSW_REG_QTCT_ID, MLXSW_REG_QTCT_LEN);

/* reg_qtct_local_port
 * Local port number.
 * Access: Index
 *
 * Note: CPU port is not supported.
 */
MLXSW_ITEM32(reg, qtct, local_port, 0x00, 16, 8);

/* reg_qtct_sub_port
 * Virtual port within the physical port.
 * Should be set to 0 when भव ports are not enabled on the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, qtct, sub_port, 0x00, 8, 8);

/* reg_qtct_चयन_prio
 * Switch priority.
 * Access: Index
 */
MLXSW_ITEM32(reg, qtct, चयन_prio, 0x00, 0, 4);

/* reg_qtct_tclass
 * Traffic class.
 * Default values:
 * चयन_prio 0 : tclass 1
 * चयन_prio 1 : tclass 0
 * चयन_prio i : tclass i, क्रम i > 1
 * Access: RW
 */
MLXSW_ITEM32(reg, qtct, tclass, 0x04, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_qtct_pack(अक्षर *payload, u8 local_port,
				       u8 चयन_prio, u8 tclass)
अणु
	MLXSW_REG_ZERO(qtct, payload);
	mlxsw_reg_qtct_local_port_set(payload, local_port);
	mlxsw_reg_qtct_चयन_prio_set(payload, चयन_prio);
	mlxsw_reg_qtct_tclass_set(payload, tclass);
पूर्ण

/* QEEC - QoS ETS Element Configuration Register
 * ---------------------------------------------
 * Configures the ETS elements.
 */
#घोषणा MLXSW_REG_QEEC_ID 0x400D
#घोषणा MLXSW_REG_QEEC_LEN 0x20

MLXSW_REG_DEFINE(qeec, MLXSW_REG_QEEC_ID, MLXSW_REG_QEEC_LEN);

/* reg_qeec_local_port
 * Local port number.
 * Access: Index
 *
 * Note: CPU port is supported.
 */
MLXSW_ITEM32(reg, qeec, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_qeec_hr अणु
	MLXSW_REG_QEEC_HR_PORT,
	MLXSW_REG_QEEC_HR_GROUP,
	MLXSW_REG_QEEC_HR_SUBGROUP,
	MLXSW_REG_QEEC_HR_TC,
पूर्ण;

/* reg_qeec_element_hierarchy
 * 0 - Port
 * 1 - Group
 * 2 - Subgroup
 * 3 - Traffic Class
 * Access: Index
 */
MLXSW_ITEM32(reg, qeec, element_hierarchy, 0x04, 16, 4);

/* reg_qeec_element_index
 * The index of the element in the hierarchy.
 * Access: Index
 */
MLXSW_ITEM32(reg, qeec, element_index, 0x04, 0, 8);

/* reg_qeec_next_element_index
 * The index of the next (lower) element in the hierarchy.
 * Access: RW
 *
 * Note: Reserved क्रम element_hierarchy 0.
 */
MLXSW_ITEM32(reg, qeec, next_element_index, 0x08, 0, 8);

/* reg_qeec_mise
 * Min shaper configuration enable. Enables configuration of the min
 * shaper on this ETS element
 * 0 - Disable
 * 1 - Enable
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, mise, 0x0C, 31, 1);

/* reg_qeec_ptps
 * PTP shaper
 * 0: regular shaper mode
 * 1: PTP oriented shaper
 * Allowed only क्रम hierarchy 0
 * Not supported क्रम CPU port
 * Note that ptps mode may affect the shaper rates of all hierarchies
 * Supported only on Spectrum-1
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, ptps, 0x0C, 29, 1);

क्रमागत अणु
	MLXSW_REG_QEEC_BYTES_MODE,
	MLXSW_REG_QEEC_PACKETS_MODE,
पूर्ण;

/* reg_qeec_pb
 * Packets or bytes mode.
 * 0 - Bytes mode
 * 1 - Packets mode
 * Access: RW
 *
 * Note: Used क्रम max shaper configuration. For Spectrum, packets mode
 * is supported only क्रम traffic classes of CPU port.
 */
MLXSW_ITEM32(reg, qeec, pb, 0x0C, 28, 1);

/* The smallest permitted min shaper rate. */
#घोषणा MLXSW_REG_QEEC_MIS_MIN	200000		/* Kbps */

/* reg_qeec_min_shaper_rate
 * Min shaper inक्रमmation rate.
 * For CPU port, can only be configured क्रम port hierarchy.
 * When in bytes mode, value is specअगरied in units of 1000bps.
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, min_shaper_rate, 0x0C, 0, 28);

/* reg_qeec_mase
 * Max shaper configuration enable. Enables configuration of the max
 * shaper on this ETS element.
 * 0 - Disable
 * 1 - Enable
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, mase, 0x10, 31, 1);

/* The largest max shaper value possible to disable the shaper. */
#घोषणा MLXSW_REG_QEEC_MAS_DIS	((1u << 31) - 1)	/* Kbps */

/* reg_qeec_max_shaper_rate
 * Max shaper inक्रमmation rate.
 * For CPU port, can only be configured क्रम port hierarchy.
 * When in bytes mode, value is specअगरied in units of 1000bps.
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, max_shaper_rate, 0x10, 0, 31);

/* reg_qeec_de
 * DWRR configuration enable. Enables configuration of the dwrr and
 * dwrr_weight.
 * 0 - Disable
 * 1 - Enable
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, de, 0x18, 31, 1);

/* reg_qeec_dwrr
 * Transmission selection algorithm to use on the link going करोwn from
 * the ETS element.
 * 0 - Strict priority
 * 1 - DWRR
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, dwrr, 0x18, 15, 1);

/* reg_qeec_dwrr_weight
 * DWRR weight on the link going करोwn from the ETS element. The
 * percentage of bandwidth guaranteed to an ETS element within
 * its hierarchy. The sum of all weights across all ETS elements
 * within one hierarchy should be equal to 100. Reserved when
 * transmission selection algorithm is strict priority.
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, dwrr_weight, 0x18, 0, 8);

/* reg_qeec_max_shaper_bs
 * Max shaper burst size
 * Burst size is 2^max_shaper_bs * 512 bits
 * For Spectrum-1: Range is: 5..25
 * For Spectrum-2: Range is: 11..25
 * Reserved when ptps = 1
 * Access: RW
 */
MLXSW_ITEM32(reg, qeec, max_shaper_bs, 0x1C, 0, 6);

#घोषणा MLXSW_REG_QEEC_HIGHEST_SHAPER_BS	25
#घोषणा MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP1	5
#घोषणा MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP2	11
#घोषणा MLXSW_REG_QEEC_LOWEST_SHAPER_BS_SP3	11

अटल अंतरभूत व्योम mlxsw_reg_qeec_pack(अक्षर *payload, u8 local_port,
				       क्रमागत mlxsw_reg_qeec_hr hr, u8 index,
				       u8 next_index)
अणु
	MLXSW_REG_ZERO(qeec, payload);
	mlxsw_reg_qeec_local_port_set(payload, local_port);
	mlxsw_reg_qeec_element_hierarchy_set(payload, hr);
	mlxsw_reg_qeec_element_index_set(payload, index);
	mlxsw_reg_qeec_next_element_index_set(payload, next_index);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_qeec_ptps_pack(अक्षर *payload, u8 local_port,
					    bool ptps)
अणु
	MLXSW_REG_ZERO(qeec, payload);
	mlxsw_reg_qeec_local_port_set(payload, local_port);
	mlxsw_reg_qeec_element_hierarchy_set(payload, MLXSW_REG_QEEC_HR_PORT);
	mlxsw_reg_qeec_ptps_set(payload, ptps);
पूर्ण

/* QRWE - QoS ReWrite Enable
 * -------------------------
 * This रेजिस्टर configures the reग_लिखो enable per receive port.
 */
#घोषणा MLXSW_REG_QRWE_ID 0x400F
#घोषणा MLXSW_REG_QRWE_LEN 0x08

MLXSW_REG_DEFINE(qrwe, MLXSW_REG_QRWE_ID, MLXSW_REG_QRWE_LEN);

/* reg_qrwe_local_port
 * Local port number.
 * Access: Index
 *
 * Note: CPU port is supported. No support क्रम router port.
 */
MLXSW_ITEM32(reg, qrwe, local_port, 0x00, 16, 8);

/* reg_qrwe_dscp
 * Whether to enable DSCP reग_लिखो (शेष is 0, करोn't reग_लिखो).
 * Access: RW
 */
MLXSW_ITEM32(reg, qrwe, dscp, 0x04, 1, 1);

/* reg_qrwe_pcp
 * Whether to enable PCP and DEI reग_लिखो (शेष is 0, करोn't reग_लिखो).
 * Access: RW
 */
MLXSW_ITEM32(reg, qrwe, pcp, 0x04, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_qrwe_pack(अक्षर *payload, u8 local_port,
				       bool reग_लिखो_pcp, bool reग_लिखो_dscp)
अणु
	MLXSW_REG_ZERO(qrwe, payload);
	mlxsw_reg_qrwe_local_port_set(payload, local_port);
	mlxsw_reg_qrwe_pcp_set(payload, reग_लिखो_pcp);
	mlxsw_reg_qrwe_dscp_set(payload, reग_लिखो_dscp);
पूर्ण

/* QPDSM - QoS Priority to DSCP Mapping
 * ------------------------------------
 * QoS Priority to DSCP Mapping Register
 */
#घोषणा MLXSW_REG_QPDSM_ID 0x4011
#घोषणा MLXSW_REG_QPDSM_BASE_LEN 0x04 /* base length, without records */
#घोषणा MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN 0x4 /* record length */
#घोषणा MLXSW_REG_QPDSM_PRIO_ENTRY_REC_MAX_COUNT 16
#घोषणा MLXSW_REG_QPDSM_LEN (MLXSW_REG_QPDSM_BASE_LEN +			\
			     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN *	\
			     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_MAX_COUNT)

MLXSW_REG_DEFINE(qpdsm, MLXSW_REG_QPDSM_ID, MLXSW_REG_QPDSM_LEN);

/* reg_qpdsm_local_port
 * Local Port. Supported क्रम data packets from CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpdsm, local_port, 0x00, 16, 8);

/* reg_qpdsm_prio_entry_color0_e
 * Enable update of the entry क्रम color 0 and a given port.
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color0_e,
		     MLXSW_REG_QPDSM_BASE_LEN, 31, 1,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdsm_prio_entry_color0_dscp
 * DSCP field in the outer label of the packet क्रम color 0 and a given port.
 * Reserved when e=0.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color0_dscp,
		     MLXSW_REG_QPDSM_BASE_LEN, 24, 6,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdsm_prio_entry_color1_e
 * Enable update of the entry क्रम color 1 and a given port.
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color1_e,
		     MLXSW_REG_QPDSM_BASE_LEN, 23, 1,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdsm_prio_entry_color1_dscp
 * DSCP field in the outer label of the packet क्रम color 1 and a given port.
 * Reserved when e=0.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color1_dscp,
		     MLXSW_REG_QPDSM_BASE_LEN, 16, 6,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdsm_prio_entry_color2_e
 * Enable update of the entry क्रम color 2 and a given port.
 * Access: WO
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color2_e,
		     MLXSW_REG_QPDSM_BASE_LEN, 15, 1,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdsm_prio_entry_color2_dscp
 * DSCP field in the outer label of the packet क्रम color 2 and a given port.
 * Reserved when e=0.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, qpdsm, prio_entry_color2_dscp,
		     MLXSW_REG_QPDSM_BASE_LEN, 8, 6,
		     MLXSW_REG_QPDSM_PRIO_ENTRY_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_qpdsm_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(qpdsm, payload);
	mlxsw_reg_qpdsm_local_port_set(payload, local_port);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_qpdsm_prio_pack(अक्षर *payload, अचिन्हित लघु prio, u8 dscp)
अणु
	mlxsw_reg_qpdsm_prio_entry_color0_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color0_dscp_set(payload, prio, dscp);
	mlxsw_reg_qpdsm_prio_entry_color1_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color1_dscp_set(payload, prio, dscp);
	mlxsw_reg_qpdsm_prio_entry_color2_e_set(payload, prio, 1);
	mlxsw_reg_qpdsm_prio_entry_color2_dscp_set(payload, prio, dscp);
पूर्ण

/* QPDP - QoS Port DSCP to Priority Mapping Register
 * -------------------------------------------------
 * This रेजिस्टर controls the port शेष Switch Priority and Color. The
 * शेष Switch Priority and Color are used क्रम frames where the trust state
 * uses शेष values. All member ports of a LAG should be configured with the
 * same शेष values.
 */
#घोषणा MLXSW_REG_QPDP_ID 0x4007
#घोषणा MLXSW_REG_QPDP_LEN 0x8

MLXSW_REG_DEFINE(qpdp, MLXSW_REG_QPDP_ID, MLXSW_REG_QPDP_LEN);

/* reg_qpdp_local_port
 * Local Port. Supported क्रम data packets from CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpdp, local_port, 0x00, 16, 8);

/* reg_qpdp_चयन_prio
 * Default port Switch Priority (शेष 0)
 * Access: RW
 */
MLXSW_ITEM32(reg, qpdp, चयन_prio, 0x04, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_qpdp_pack(अक्षर *payload, u8 local_port,
				       u8 चयन_prio)
अणु
	MLXSW_REG_ZERO(qpdp, payload);
	mlxsw_reg_qpdp_local_port_set(payload, local_port);
	mlxsw_reg_qpdp_चयन_prio_set(payload, चयन_prio);
पूर्ण

/* QPDPM - QoS Port DSCP to Priority Mapping Register
 * --------------------------------------------------
 * This रेजिस्टर controls the mapping from DSCP field to
 * Switch Priority क्रम IP packets.
 */
#घोषणा MLXSW_REG_QPDPM_ID 0x4013
#घोषणा MLXSW_REG_QPDPM_BASE_LEN 0x4 /* base length, without records */
#घोषणा MLXSW_REG_QPDPM_DSCP_ENTRY_REC_LEN 0x2 /* record length */
#घोषणा MLXSW_REG_QPDPM_DSCP_ENTRY_REC_MAX_COUNT 64
#घोषणा MLXSW_REG_QPDPM_LEN (MLXSW_REG_QPDPM_BASE_LEN +			\
			     MLXSW_REG_QPDPM_DSCP_ENTRY_REC_LEN *	\
			     MLXSW_REG_QPDPM_DSCP_ENTRY_REC_MAX_COUNT)

MLXSW_REG_DEFINE(qpdpm, MLXSW_REG_QPDPM_ID, MLXSW_REG_QPDPM_LEN);

/* reg_qpdpm_local_port
 * Local Port. Supported क्रम data packets from CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpdpm, local_port, 0x00, 16, 8);

/* reg_qpdpm_dscp_e
 * Enable update of the specअगरic entry. When cleared, the चयन_prio and color
 * fields are ignored and the previous चयन_prio and color values are
 * preserved.
 * Access: WO
 */
MLXSW_ITEM16_INDEXED(reg, qpdpm, dscp_entry_e, MLXSW_REG_QPDPM_BASE_LEN, 15, 1,
		     MLXSW_REG_QPDPM_DSCP_ENTRY_REC_LEN, 0x00, false);

/* reg_qpdpm_dscp_prio
 * The new Switch Priority value क्रम the relevant DSCP value.
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, qpdpm, dscp_entry_prio,
		     MLXSW_REG_QPDPM_BASE_LEN, 0, 4,
		     MLXSW_REG_QPDPM_DSCP_ENTRY_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_qpdpm_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(qpdpm, payload);
	mlxsw_reg_qpdpm_local_port_set(payload, local_port);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_qpdpm_dscp_pack(अक्षर *payload, अचिन्हित लघु dscp, u8 prio)
अणु
	mlxsw_reg_qpdpm_dscp_entry_e_set(payload, dscp, 1);
	mlxsw_reg_qpdpm_dscp_entry_prio_set(payload, dscp, prio);
पूर्ण

/* QTCTM - QoS Switch Traffic Class Table is Multicast-Aware Register
 * ------------------------------------------------------------------
 * This रेजिस्टर configures अगर the Switch Priority to Traffic Class mapping is
 * based on Multicast packet indication. If so, then multicast packets will get
 * a Traffic Class that is plus (cap_max_tclass_data/2) the value configured by
 * QTCT.
 * By शेष, Switch Priority to Traffic Class mapping is not based on
 * Multicast packet indication.
 */
#घोषणा MLXSW_REG_QTCTM_ID 0x401A
#घोषणा MLXSW_REG_QTCTM_LEN 0x08

MLXSW_REG_DEFINE(qtcपंचांग, MLXSW_REG_QTCTM_ID, MLXSW_REG_QTCTM_LEN);

/* reg_qtcपंचांग_local_port
 * Local port number.
 * No support क्रम CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, qtcपंचांग, local_port, 0x00, 16, 8);

/* reg_qtcपंचांग_mc
 * Multicast Mode
 * Whether Switch Priority to Traffic Class mapping is based on Multicast packet
 * indication (शेष is 0, not based on Multicast packet indication).
 */
MLXSW_ITEM32(reg, qtcपंचांग, mc, 0x04, 0, 1);

अटल अंतरभूत व्योम
mlxsw_reg_qtcपंचांग_pack(अक्षर *payload, u8 local_port, bool mc)
अणु
	MLXSW_REG_ZERO(qtcपंचांग, payload);
	mlxsw_reg_qtcपंचांग_local_port_set(payload, local_port);
	mlxsw_reg_qtcपंचांग_mc_set(payload, mc);
पूर्ण

/* QPSC - QoS PTP Shaper Configuration Register
 * --------------------------------------------
 * The QPSC allows advanced configuration of the shapers when QEEC.ptps=1.
 * Supported only on Spectrum-1.
 */
#घोषणा MLXSW_REG_QPSC_ID 0x401B
#घोषणा MLXSW_REG_QPSC_LEN 0x28

MLXSW_REG_DEFINE(qpsc, MLXSW_REG_QPSC_ID, MLXSW_REG_QPSC_LEN);

क्रमागत mlxsw_reg_qpsc_port_speed अणु
	MLXSW_REG_QPSC_PORT_SPEED_100M,
	MLXSW_REG_QPSC_PORT_SPEED_1G,
	MLXSW_REG_QPSC_PORT_SPEED_10G,
	MLXSW_REG_QPSC_PORT_SPEED_25G,
पूर्ण;

/* reg_qpsc_port_speed
 * Port speed.
 * Access: Index
 */
MLXSW_ITEM32(reg, qpsc, port_speed, 0x00, 0, 4);

/* reg_qpsc_shaper_समय_exp
 * The base-समय-पूर्णांकerval क्रम updating the shapers tokens (क्रम all hierarchies).
 * shaper_update_rate = 2 ^ shaper_समय_exp * (1 + shaper_समय_mantissa) * 32nSec
 * shaper_rate = 64bit * shaper_inc / shaper_update_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, shaper_समय_exp, 0x04, 16, 4);

/* reg_qpsc_shaper_समय_mantissa
 * The base-समय-पूर्णांकerval क्रम updating the shapers tokens (क्रम all hierarchies).
 * shaper_update_rate = 2 ^ shaper_समय_exp * (1 + shaper_समय_mantissa) * 32nSec
 * shaper_rate = 64bit * shaper_inc / shaper_update_rate
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, shaper_समय_mantissa, 0x04, 0, 5);

/* reg_qpsc_shaper_inc
 * Number of tokens added to shaper on each update.
 * Units of 8B.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, shaper_inc, 0x08, 0, 5);

/* reg_qpsc_shaper_bs
 * Max shaper Burst size.
 * Burst size is 2 ^ max_shaper_bs * 512 [bits]
 * Range is: 5..25 (from 2KB..2GB)
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, shaper_bs, 0x0C, 0, 6);

/* reg_qpsc_ptsc_we
 * Write enable to port_to_shaper_credits.
 * Access: WO
 */
MLXSW_ITEM32(reg, qpsc, ptsc_we, 0x10, 31, 1);

/* reg_qpsc_port_to_shaper_credits
 * For split ports: range 1..57
 * For non-split ports: range 1..112
 * Written only when ptsc_we is set.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, port_to_shaper_credits, 0x10, 0, 8);

/* reg_qpsc_ing_बारtamp_inc
 * Ingress बारtamp increment.
 * 2's complement.
 * The बारtamp of MTPPTR at ingress will be incremented by this value. Global
 * value क्रम all ports.
 * Same units as used by MTPPTR.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, ing_बारtamp_inc, 0x20, 0, 32);

/* reg_qpsc_egr_बारtamp_inc
 * Egress बारtamp increment.
 * 2's complement.
 * The बारtamp of MTPPTR at egress will be incremented by this value. Global
 * value क्रम all ports.
 * Same units as used by MTPPTR.
 * Access: RW
 */
MLXSW_ITEM32(reg, qpsc, egr_बारtamp_inc, 0x24, 0, 32);

अटल अंतरभूत व्योम
mlxsw_reg_qpsc_pack(अक्षर *payload, क्रमागत mlxsw_reg_qpsc_port_speed port_speed,
		    u8 shaper_समय_exp, u8 shaper_समय_mantissa, u8 shaper_inc,
		    u8 shaper_bs, u8 port_to_shaper_credits,
		    पूर्णांक ing_बारtamp_inc, पूर्णांक egr_बारtamp_inc)
अणु
	MLXSW_REG_ZERO(qpsc, payload);
	mlxsw_reg_qpsc_port_speed_set(payload, port_speed);
	mlxsw_reg_qpsc_shaper_समय_exp_set(payload, shaper_समय_exp);
	mlxsw_reg_qpsc_shaper_समय_mantissa_set(payload, shaper_समय_mantissa);
	mlxsw_reg_qpsc_shaper_inc_set(payload, shaper_inc);
	mlxsw_reg_qpsc_shaper_bs_set(payload, shaper_bs);
	mlxsw_reg_qpsc_ptsc_we_set(payload, true);
	mlxsw_reg_qpsc_port_to_shaper_credits_set(payload, port_to_shaper_credits);
	mlxsw_reg_qpsc_ing_बारtamp_inc_set(payload, ing_बारtamp_inc);
	mlxsw_reg_qpsc_egr_बारtamp_inc_set(payload, egr_बारtamp_inc);
पूर्ण

/* PMLP - Ports Module to Local Port Register
 * ------------------------------------------
 * Configures the assignment of modules to local ports.
 */
#घोषणा MLXSW_REG_PMLP_ID 0x5002
#घोषणा MLXSW_REG_PMLP_LEN 0x40

MLXSW_REG_DEFINE(pmlp, MLXSW_REG_PMLP_ID, MLXSW_REG_PMLP_LEN);

/* reg_pmlp_rxtx
 * 0 - Tx value is used क्रम both Tx and Rx.
 * 1 - Rx value is taken from a separte field.
 * Access: RW
 */
MLXSW_ITEM32(reg, pmlp, rxtx, 0x00, 31, 1);

/* reg_pmlp_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmlp, local_port, 0x00, 16, 8);

/* reg_pmlp_width
 * 0 - Unmap local port.
 * 1 - Lane 0 is used.
 * 2 - Lanes 0 and 1 are used.
 * 4 - Lanes 0, 1, 2 and 3 are used.
 * 8 - Lanes 0-7 are used.
 * Access: RW
 */
MLXSW_ITEM32(reg, pmlp, width, 0x00, 0, 8);

/* reg_pmlp_module
 * Module number.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmlp, module, 0x04, 0, 8, 0x04, 0x00, false);

/* reg_pmlp_tx_lane
 * Tx Lane. When rxtx field is cleared, this field is used क्रम Rx as well.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmlp, tx_lane, 0x04, 16, 4, 0x04, 0x00, false);

/* reg_pmlp_rx_lane
 * Rx Lane. When rxtx field is cleared, this field is ignored and Rx lane is
 * equal to Tx lane.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pmlp, rx_lane, 0x04, 24, 4, 0x04, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_pmlp_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(pmlp, payload);
	mlxsw_reg_pmlp_local_port_set(payload, local_port);
पूर्ण

/* PMTU - Port MTU Register
 * ------------------------
 * Configures and reports the port MTU.
 */
#घोषणा MLXSW_REG_PMTU_ID 0x5003
#घोषणा MLXSW_REG_PMTU_LEN 0x10

MLXSW_REG_DEFINE(pmtu, MLXSW_REG_PMTU_ID, MLXSW_REG_PMTU_LEN);

/* reg_pmtu_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmtu, local_port, 0x00, 16, 8);

/* reg_pmtu_max_mtu
 * Maximum MTU.
 * When port type (e.g. Ethernet) is configured, the relevant MTU is
 * reported, otherwise the minimum between the max_mtu of the dअगरferent
 * types is reported.
 * Access: RO
 */
MLXSW_ITEM32(reg, pmtu, max_mtu, 0x04, 16, 16);

/* reg_pmtu_admin_mtu
 * MTU value to set port to. Must be smaller or equal to max_mtu.
 * Note: If port type is Infiniband, then port must be disabled, when its
 * MTU is set.
 * Access: RW
 */
MLXSW_ITEM32(reg, pmtu, admin_mtu, 0x08, 16, 16);

/* reg_pmtu_oper_mtu
 * The actual MTU configured on the port. Packets exceeding this size
 * will be dropped.
 * Note: In Ethernet and FC oper_mtu == admin_mtu, however, in Infiniband
 * oper_mtu might be smaller than admin_mtu.
 * Access: RO
 */
MLXSW_ITEM32(reg, pmtu, oper_mtu, 0x0C, 16, 16);

अटल अंतरभूत व्योम mlxsw_reg_pmtu_pack(अक्षर *payload, u8 local_port,
				       u16 new_mtu)
अणु
	MLXSW_REG_ZERO(pmtu, payload);
	mlxsw_reg_pmtu_local_port_set(payload, local_port);
	mlxsw_reg_pmtu_max_mtu_set(payload, 0);
	mlxsw_reg_pmtu_admin_mtu_set(payload, new_mtu);
	mlxsw_reg_pmtu_oper_mtu_set(payload, 0);
पूर्ण

/* PTYS - Port Type and Speed Register
 * -----------------------------------
 * Configures and reports the port speed type.
 *
 * Note: When set जबतक the link is up, the changes will not take effect
 * until the port transitions from करोwn to up state.
 */
#घोषणा MLXSW_REG_PTYS_ID 0x5004
#घोषणा MLXSW_REG_PTYS_LEN 0x40

MLXSW_REG_DEFINE(ptys, MLXSW_REG_PTYS_ID, MLXSW_REG_PTYS_LEN);

/* an_disable_admin
 * Auto negotiation disable administrative configuration
 * 0 - Device करोesn't support AN disable.
 * 1 - Device supports AN disable.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, an_disable_admin, 0x00, 30, 1);

/* reg_ptys_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptys, local_port, 0x00, 16, 8);

#घोषणा MLXSW_REG_PTYS_PROTO_MASK_IB	BIT(0)
#घोषणा MLXSW_REG_PTYS_PROTO_MASK_ETH	BIT(2)

/* reg_ptys_proto_mask
 * Protocol mask. Indicates which protocol is used.
 * 0 - Infiniband.
 * 1 - Fibre Channel.
 * 2 - Ethernet.
 * Access: Index
 */
MLXSW_ITEM32(reg, ptys, proto_mask, 0x00, 0, 3);

क्रमागत अणु
	MLXSW_REG_PTYS_AN_STATUS_NA,
	MLXSW_REG_PTYS_AN_STATUS_OK,
	MLXSW_REG_PTYS_AN_STATUS_FAIL,
पूर्ण;

/* reg_ptys_an_status
 * Autonegotiation status.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, an_status, 0x04, 28, 4);

#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_SGMII_100M				BIT(0)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_1000BASE_X_SGMII			BIT(1)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_5GBASE_R				BIT(3)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_XFI_XAUI_1_10G			BIT(4)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_XLAUI_4_XLPPI_4_40G		BIT(5)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_25GAUI_1_25GBASE_CR_KR		BIT(6)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_50GAUI_2_LAUI_2_50GBASE_CR2_KR2	BIT(7)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_50GAUI_1_LAUI_1_50GBASE_CR_KR	BIT(8)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_CAUI_4_100GBASE_CR4_KR4		BIT(9)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_100GAUI_2_100GBASE_CR2_KR2		BIT(10)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_200GAUI_4_200GBASE_CR4_KR4		BIT(12)
#घोषणा MLXSW_REG_PTYS_EXT_ETH_SPEED_400GAUI_8				BIT(15)

/* reg_ptys_ext_eth_proto_cap
 * Extended Ethernet port supported speeds and protocols.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_cap, 0x08, 0, 32);

#घोषणा MLXSW_REG_PTYS_ETH_SPEED_SGMII			BIT(0)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX		BIT(1)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CX4		BIT(2)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4		BIT(3)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR		BIT(4)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4		BIT(6)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4		BIT(7)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR		BIT(12)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR		BIT(13)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_10GBASE_ER_LR		BIT(14)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4		BIT(15)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_40GBASE_LR4_ER4	BIT(16)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_50GBASE_SR2		BIT(18)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_50GBASE_KR4		BIT(19)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_100GBASE_CR4		BIT(20)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4		BIT(21)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4		BIT(22)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_100GBASE_LR4_ER4	BIT(23)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_25GBASE_CR		BIT(27)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_25GBASE_KR		BIT(28)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_25GBASE_SR		BIT(29)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_50GBASE_CR2		BIT(30)
#घोषणा MLXSW_REG_PTYS_ETH_SPEED_50GBASE_KR2		BIT(31)

/* reg_ptys_eth_proto_cap
 * Ethernet port supported speeds and protocols.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_cap, 0x0C, 0, 32);

/* reg_ptys_ib_link_width_cap
 * IB port supported widths.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ib_link_width_cap, 0x10, 16, 16);

#घोषणा MLXSW_REG_PTYS_IB_SPEED_SDR	BIT(0)
#घोषणा MLXSW_REG_PTYS_IB_SPEED_DDR	BIT(1)
#घोषणा MLXSW_REG_PTYS_IB_SPEED_QDR	BIT(2)
#घोषणा MLXSW_REG_PTYS_IB_SPEED_FDR10	BIT(3)
#घोषणा MLXSW_REG_PTYS_IB_SPEED_FDR	BIT(4)
#घोषणा MLXSW_REG_PTYS_IB_SPEED_EDR	BIT(5)

/* reg_ptys_ib_proto_cap
 * IB port supported speeds and protocols.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ib_proto_cap, 0x10, 0, 16);

/* reg_ptys_ext_eth_proto_admin
 * Extended speed and protocol to set port to.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_admin, 0x14, 0, 32);

/* reg_ptys_eth_proto_admin
 * Speed and protocol to set port to.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, eth_proto_admin, 0x18, 0, 32);

/* reg_ptys_ib_link_width_admin
 * IB width to set port to.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, ib_link_width_admin, 0x1C, 16, 16);

/* reg_ptys_ib_proto_admin
 * IB speeds and protocols to set port to.
 * Access: RW
 */
MLXSW_ITEM32(reg, ptys, ib_proto_admin, 0x1C, 0, 16);

/* reg_ptys_ext_eth_proto_oper
 * The extended current speed and protocol configured क्रम the port.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ext_eth_proto_oper, 0x20, 0, 32);

/* reg_ptys_eth_proto_oper
 * The current speed and protocol configured क्रम the port.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, eth_proto_oper, 0x24, 0, 32);

/* reg_ptys_ib_link_width_oper
 * The current IB width to set port to.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ib_link_width_oper, 0x28, 16, 16);

/* reg_ptys_ib_proto_oper
 * The current IB speed and protocol.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, ib_proto_oper, 0x28, 0, 16);

क्रमागत mlxsw_reg_ptys_connector_type अणु
	MLXSW_REG_PTYS_CONNECTOR_TYPE_UNKNOWN_OR_NO_CONNECTOR,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_NONE,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_TP,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_AUI,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_BNC,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_MII,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_FIBRE,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_DA,
	MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_OTHER,
पूर्ण;

/* reg_ptys_connector_type
 * Connector type indication.
 * Access: RO
 */
MLXSW_ITEM32(reg, ptys, connector_type, 0x2C, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_ptys_eth_pack(अक्षर *payload, u8 local_port,
					   u32 proto_admin, bool स्वतःneg)
अणु
	MLXSW_REG_ZERO(ptys, payload);
	mlxsw_reg_ptys_local_port_set(payload, local_port);
	mlxsw_reg_ptys_proto_mask_set(payload, MLXSW_REG_PTYS_PROTO_MASK_ETH);
	mlxsw_reg_ptys_eth_proto_admin_set(payload, proto_admin);
	mlxsw_reg_ptys_an_disable_admin_set(payload, !स्वतःneg);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptys_ext_eth_pack(अक्षर *payload, u8 local_port,
					       u32 proto_admin, bool स्वतःneg)
अणु
	MLXSW_REG_ZERO(ptys, payload);
	mlxsw_reg_ptys_local_port_set(payload, local_port);
	mlxsw_reg_ptys_proto_mask_set(payload, MLXSW_REG_PTYS_PROTO_MASK_ETH);
	mlxsw_reg_ptys_ext_eth_proto_admin_set(payload, proto_admin);
	mlxsw_reg_ptys_an_disable_admin_set(payload, !स्वतःneg);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptys_eth_unpack(अक्षर *payload,
					     u32 *p_eth_proto_cap,
					     u32 *p_eth_proto_admin,
					     u32 *p_eth_proto_oper)
अणु
	अगर (p_eth_proto_cap)
		*p_eth_proto_cap =
			mlxsw_reg_ptys_eth_proto_cap_get(payload);
	अगर (p_eth_proto_admin)
		*p_eth_proto_admin =
			mlxsw_reg_ptys_eth_proto_admin_get(payload);
	अगर (p_eth_proto_oper)
		*p_eth_proto_oper =
			mlxsw_reg_ptys_eth_proto_oper_get(payload);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptys_ext_eth_unpack(अक्षर *payload,
						 u32 *p_eth_proto_cap,
						 u32 *p_eth_proto_admin,
						 u32 *p_eth_proto_oper)
अणु
	अगर (p_eth_proto_cap)
		*p_eth_proto_cap =
			mlxsw_reg_ptys_ext_eth_proto_cap_get(payload);
	अगर (p_eth_proto_admin)
		*p_eth_proto_admin =
			mlxsw_reg_ptys_ext_eth_proto_admin_get(payload);
	अगर (p_eth_proto_oper)
		*p_eth_proto_oper =
			mlxsw_reg_ptys_ext_eth_proto_oper_get(payload);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptys_ib_pack(अक्षर *payload, u8 local_port,
					  u16 proto_admin, u16 link_width)
अणु
	MLXSW_REG_ZERO(ptys, payload);
	mlxsw_reg_ptys_local_port_set(payload, local_port);
	mlxsw_reg_ptys_proto_mask_set(payload, MLXSW_REG_PTYS_PROTO_MASK_IB);
	mlxsw_reg_ptys_ib_proto_admin_set(payload, proto_admin);
	mlxsw_reg_ptys_ib_link_width_admin_set(payload, link_width);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ptys_ib_unpack(अक्षर *payload, u16 *p_ib_proto_cap,
					    u16 *p_ib_link_width_cap,
					    u16 *p_ib_proto_oper,
					    u16 *p_ib_link_width_oper)
अणु
	अगर (p_ib_proto_cap)
		*p_ib_proto_cap = mlxsw_reg_ptys_ib_proto_cap_get(payload);
	अगर (p_ib_link_width_cap)
		*p_ib_link_width_cap =
			mlxsw_reg_ptys_ib_link_width_cap_get(payload);
	अगर (p_ib_proto_oper)
		*p_ib_proto_oper = mlxsw_reg_ptys_ib_proto_oper_get(payload);
	अगर (p_ib_link_width_oper)
		*p_ib_link_width_oper =
			mlxsw_reg_ptys_ib_link_width_oper_get(payload);
पूर्ण

/* PPAD - Port Physical Address Register
 * -------------------------------------
 * The PPAD रेजिस्टर configures the per port physical MAC address.
 */
#घोषणा MLXSW_REG_PPAD_ID 0x5005
#घोषणा MLXSW_REG_PPAD_LEN 0x10

MLXSW_REG_DEFINE(ppad, MLXSW_REG_PPAD_ID, MLXSW_REG_PPAD_LEN);

/* reg_ppad_single_base_mac
 * 0: base_mac, local port should be 0 and mac[7:0] is
 * reserved. HW will set incremental
 * 1: single_mac - mac of the local_port
 * Access: RW
 */
MLXSW_ITEM32(reg, ppad, single_base_mac, 0x00, 28, 1);

/* reg_ppad_local_port
 * port number, अगर single_base_mac = 0 then local_port is reserved
 * Access: RW
 */
MLXSW_ITEM32(reg, ppad, local_port, 0x00, 16, 8);

/* reg_ppad_mac
 * If single_base_mac = 0 - base MAC address, mac[7:0] is reserved.
 * If single_base_mac = 1 - the per port MAC address
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ppad, mac, 0x02, 6);

अटल अंतरभूत व्योम mlxsw_reg_ppad_pack(अक्षर *payload, bool single_base_mac,
				       u8 local_port)
अणु
	MLXSW_REG_ZERO(ppad, payload);
	mlxsw_reg_ppad_single_base_mac_set(payload, !!single_base_mac);
	mlxsw_reg_ppad_local_port_set(payload, local_port);
पूर्ण

/* PAOS - Ports Administrative and Operational Status Register
 * -----------------------------------------------------------
 * Configures and retrieves per port administrative and operational status.
 */
#घोषणा MLXSW_REG_PAOS_ID 0x5006
#घोषणा MLXSW_REG_PAOS_LEN 0x10

MLXSW_REG_DEFINE(paos, MLXSW_REG_PAOS_ID, MLXSW_REG_PAOS_LEN);

/* reg_paos_swid
 * Switch partition ID with which to associate the port.
 * Note: जबतक बाह्यal ports uses unique local port numbers (and thus swid is
 * redundant), router ports use the same local port number where swid is the
 * only indication क्रम the relevant port.
 * Access: Index
 */
MLXSW_ITEM32(reg, paos, swid, 0x00, 24, 8);

/* reg_paos_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, paos, local_port, 0x00, 16, 8);

/* reg_paos_admin_status
 * Port administrative state (the desired state of the port):
 * 1 - Up.
 * 2 - Down.
 * 3 - Up once. This means that in हाल of link failure, the port won't go
 *     पूर्णांकo polling mode, but will रुको to be re-enabled by software.
 * 4 - Disabled by प्रणाली. Can only be set by hardware.
 * Access: RW
 */
MLXSW_ITEM32(reg, paos, admin_status, 0x00, 8, 4);

/* reg_paos_oper_status
 * Port operational state (the current state):
 * 1 - Up.
 * 2 - Down.
 * 3 - Down by port failure. This means that the device will not let the
 *     port up again until explicitly specअगरied by software.
 * Access: RO
 */
MLXSW_ITEM32(reg, paos, oper_status, 0x00, 0, 4);

/* reg_paos_ase
 * Admin state update enabled.
 * Access: WO
 */
MLXSW_ITEM32(reg, paos, ase, 0x04, 31, 1);

/* reg_paos_ee
 * Event update enable. If this bit is set, event generation will be
 * updated based on the e field.
 * Access: WO
 */
MLXSW_ITEM32(reg, paos, ee, 0x04, 30, 1);

/* reg_paos_e
 * Event generation on operational state change:
 * 0 - Do not generate event.
 * 1 - Generate Event.
 * 2 - Generate Single Event.
 * Access: RW
 */
MLXSW_ITEM32(reg, paos, e, 0x04, 0, 2);

अटल अंतरभूत व्योम mlxsw_reg_paos_pack(अक्षर *payload, u8 local_port,
				       क्रमागत mlxsw_port_admin_status status)
अणु
	MLXSW_REG_ZERO(paos, payload);
	mlxsw_reg_paos_swid_set(payload, 0);
	mlxsw_reg_paos_local_port_set(payload, local_port);
	mlxsw_reg_paos_admin_status_set(payload, status);
	mlxsw_reg_paos_oper_status_set(payload, 0);
	mlxsw_reg_paos_ase_set(payload, 1);
	mlxsw_reg_paos_ee_set(payload, 1);
	mlxsw_reg_paos_e_set(payload, 1);
पूर्ण

/* PFCC - Ports Flow Control Configuration Register
 * ------------------------------------------------
 * Configures and retrieves the per port flow control configuration.
 */
#घोषणा MLXSW_REG_PFCC_ID 0x5007
#घोषणा MLXSW_REG_PFCC_LEN 0x20

MLXSW_REG_DEFINE(pfcc, MLXSW_REG_PFCC_ID, MLXSW_REG_PFCC_LEN);

/* reg_pfcc_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pfcc, local_port, 0x00, 16, 8);

/* reg_pfcc_pnat
 * Port number access type. Determines the way local_port is पूर्णांकerpreted:
 * 0 - Local port number.
 * 1 - IB / label port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pfcc, pnat, 0x00, 14, 2);

/* reg_pfcc_shl_cap
 * Send to higher layers capabilities:
 * 0 - No capability of sending Pause and PFC frames to higher layers.
 * 1 - Device has capability of sending Pause and PFC frames to higher
 *     layers.
 * Access: RO
 */
MLXSW_ITEM32(reg, pfcc, shl_cap, 0x00, 1, 1);

/* reg_pfcc_shl_opr
 * Send to higher layers operation:
 * 0 - Pause and PFC frames are handled by the port (शेष).
 * 1 - Pause and PFC frames are handled by the port and also sent to
 *     higher layers. Only valid अगर shl_cap = 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, pfcc, shl_opr, 0x00, 0, 1);

/* reg_pfcc_ppan
 * Pause policy स्वतः negotiation.
 * 0 - Disabled. Generate / ignore Pause frames based on pptx / pprtx.
 * 1 - Enabled. When स्वतः-negotiation is perक्रमmed, set the Pause policy
 *     based on the स्वतः-negotiation resolution.
 * Access: RW
 *
 * Note: The स्वतः-negotiation advertisement is set according to pptx and
 * pprtx. When PFC is set on Tx / Rx, ppan must be set to 0.
 */
MLXSW_ITEM32(reg, pfcc, ppan, 0x04, 28, 4);

/* reg_pfcc_prio_mask_tx
 * Bit per priority indicating अगर Tx flow control policy should be
 * updated based on bit pfctx.
 * Access: WO
 */
MLXSW_ITEM32(reg, pfcc, prio_mask_tx, 0x04, 16, 8);

/* reg_pfcc_prio_mask_rx
 * Bit per priority indicating अगर Rx flow control policy should be
 * updated based on bit pfcrx.
 * Access: WO
 */
MLXSW_ITEM32(reg, pfcc, prio_mask_rx, 0x04, 0, 8);

/* reg_pfcc_pptx
 * Admin Pause policy on Tx.
 * 0 - Never generate Pause frames (शेष).
 * 1 - Generate Pause frames according to Rx buffer threshold.
 * Access: RW
 */
MLXSW_ITEM32(reg, pfcc, pptx, 0x08, 31, 1);

/* reg_pfcc_aptx
 * Active (operational) Pause policy on Tx.
 * 0 - Never generate Pause frames.
 * 1 - Generate Pause frames according to Rx buffer threshold.
 * Access: RO
 */
MLXSW_ITEM32(reg, pfcc, aptx, 0x08, 30, 1);

/* reg_pfcc_pfctx
 * Priority based flow control policy on Tx[7:0]. Per-priority bit mask:
 * 0 - Never generate priority Pause frames on the specअगरied priority
 *     (शेष).
 * 1 - Generate priority Pause frames according to Rx buffer threshold on
 *     the specअगरied priority.
 * Access: RW
 *
 * Note: pfctx and pptx must be mutually exclusive.
 */
MLXSW_ITEM32(reg, pfcc, pfctx, 0x08, 16, 8);

/* reg_pfcc_pprx
 * Admin Pause policy on Rx.
 * 0 - Ignore received Pause frames (शेष).
 * 1 - Respect received Pause frames.
 * Access: RW
 */
MLXSW_ITEM32(reg, pfcc, pprx, 0x0C, 31, 1);

/* reg_pfcc_aprx
 * Active (operational) Pause policy on Rx.
 * 0 - Ignore received Pause frames.
 * 1 - Respect received Pause frames.
 * Access: RO
 */
MLXSW_ITEM32(reg, pfcc, aprx, 0x0C, 30, 1);

/* reg_pfcc_pfcrx
 * Priority based flow control policy on Rx[7:0]. Per-priority bit mask:
 * 0 - Ignore incoming priority Pause frames on the specअगरied priority
 *     (शेष).
 * 1 - Respect incoming priority Pause frames on the specअगरied priority.
 * Access: RW
 */
MLXSW_ITEM32(reg, pfcc, pfcrx, 0x0C, 16, 8);

#घोषणा MLXSW_REG_PFCC_ALL_PRIO 0xFF

अटल अंतरभूत व्योम mlxsw_reg_pfcc_prio_pack(अक्षर *payload, u8 pfc_en)
अणु
	mlxsw_reg_pfcc_prio_mask_tx_set(payload, MLXSW_REG_PFCC_ALL_PRIO);
	mlxsw_reg_pfcc_prio_mask_rx_set(payload, MLXSW_REG_PFCC_ALL_PRIO);
	mlxsw_reg_pfcc_pfctx_set(payload, pfc_en);
	mlxsw_reg_pfcc_pfcrx_set(payload, pfc_en);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pfcc_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(pfcc, payload);
	mlxsw_reg_pfcc_local_port_set(payload, local_port);
पूर्ण

/* PPCNT - Ports Perक्रमmance Counters Register
 * -------------------------------------------
 * The PPCNT रेजिस्टर retrieves per port perक्रमmance counters.
 */
#घोषणा MLXSW_REG_PPCNT_ID 0x5008
#घोषणा MLXSW_REG_PPCNT_LEN 0x100
#घोषणा MLXSW_REG_PPCNT_COUNTERS_OFFSET 0x08

MLXSW_REG_DEFINE(ppcnt, MLXSW_REG_PPCNT_ID, MLXSW_REG_PPCNT_LEN);

/* reg_ppcnt_swid
 * For HCA: must be always 0.
 * Switch partition ID to associate port with.
 * Switch partitions are numbered from 0 to 7 inclusively.
 * Switch partition 254 indicates stacking ports.
 * Switch partition 255 indicates all चयन partitions.
 * Only valid on Set() operation with local_port=255.
 * Access: Index
 */
MLXSW_ITEM32(reg, ppcnt, swid, 0x00, 24, 8);

/* reg_ppcnt_local_port
 * Local port number.
 * 255 indicates all ports on the device, and is only allowed
 * क्रम Set() operation.
 * Access: Index
 */
MLXSW_ITEM32(reg, ppcnt, local_port, 0x00, 16, 8);

/* reg_ppcnt_pnat
 * Port number access type:
 * 0 - Local port number
 * 1 - IB port number
 * Access: Index
 */
MLXSW_ITEM32(reg, ppcnt, pnat, 0x00, 14, 2);

क्रमागत mlxsw_reg_ppcnt_grp अणु
	MLXSW_REG_PPCNT_IEEE_8023_CNT = 0x0,
	MLXSW_REG_PPCNT_RFC_2863_CNT = 0x1,
	MLXSW_REG_PPCNT_RFC_2819_CNT = 0x2,
	MLXSW_REG_PPCNT_RFC_3635_CNT = 0x3,
	MLXSW_REG_PPCNT_EXT_CNT = 0x5,
	MLXSW_REG_PPCNT_DISCARD_CNT = 0x6,
	MLXSW_REG_PPCNT_PRIO_CNT = 0x10,
	MLXSW_REG_PPCNT_TC_CNT = 0x11,
	MLXSW_REG_PPCNT_TC_CONG_TC = 0x13,
पूर्ण;

/* reg_ppcnt_grp
 * Perक्रमmance counter group.
 * Group 63 indicates all groups. Only valid on Set() operation with
 * clr bit set.
 * 0x0: IEEE 802.3 Counters
 * 0x1: RFC 2863 Counters
 * 0x2: RFC 2819 Counters
 * 0x3: RFC 3635 Counters
 * 0x5: Ethernet Extended Counters
 * 0x6: Ethernet Discard Counters
 * 0x8: Link Level Retransmission Counters
 * 0x10: Per Priority Counters
 * 0x11: Per Traffic Class Counters
 * 0x12: Physical Layer Counters
 * 0x13: Per Traffic Class Congestion Counters
 * Access: Index
 */
MLXSW_ITEM32(reg, ppcnt, grp, 0x00, 0, 6);

/* reg_ppcnt_clr
 * Clear counters. Setting the clr bit will reset the counter value
 * क्रम all counters in the counter group. This bit can be set
 * क्रम both Set() and Get() operation.
 * Access: OP
 */
MLXSW_ITEM32(reg, ppcnt, clr, 0x04, 31, 1);

/* reg_ppcnt_prio_tc
 * Priority क्रम counter set that support per priority, valid values: 0-7.
 * Traffic class क्रम counter set that support per traffic class,
 * valid values: 0- cap_max_tclass-1 .
 * For HCA: cap_max_tclass is always 8.
 * Otherwise must be 0.
 * Access: Index
 */
MLXSW_ITEM32(reg, ppcnt, prio_tc, 0x04, 0, 5);

/* Ethernet IEEE 802.3 Counter Group */

/* reg_ppcnt_a_frames_transmitted_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_frames_transmitted_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x00, 0, 64);

/* reg_ppcnt_a_frames_received_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_frames_received_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x08, 0, 64);

/* reg_ppcnt_a_frame_check_sequence_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_frame_check_sequence_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x10, 0, 64);

/* reg_ppcnt_a_alignment_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_alignment_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x18, 0, 64);

/* reg_ppcnt_a_octets_transmitted_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_octets_transmitted_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x20, 0, 64);

/* reg_ppcnt_a_octets_received_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_octets_received_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x28, 0, 64);

/* reg_ppcnt_a_multicast_frames_xmitted_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_multicast_frames_xmitted_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x30, 0, 64);

/* reg_ppcnt_a_broadcast_frames_xmitted_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_broadcast_frames_xmitted_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x38, 0, 64);

/* reg_ppcnt_a_multicast_frames_received_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_multicast_frames_received_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x40, 0, 64);

/* reg_ppcnt_a_broadcast_frames_received_ok
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_broadcast_frames_received_ok,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x48, 0, 64);

/* reg_ppcnt_a_in_range_length_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_in_range_length_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x50, 0, 64);

/* reg_ppcnt_a_out_of_range_length_field
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_out_of_range_length_field,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x58, 0, 64);

/* reg_ppcnt_a_frame_too_दीर्घ_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_frame_too_दीर्घ_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x60, 0, 64);

/* reg_ppcnt_a_symbol_error_during_carrier
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_symbol_error_during_carrier,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x68, 0, 64);

/* reg_ppcnt_a_mac_control_frames_transmitted
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_mac_control_frames_transmitted,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x70, 0, 64);

/* reg_ppcnt_a_mac_control_frames_received
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_mac_control_frames_received,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x78, 0, 64);

/* reg_ppcnt_a_unsupported_opcodes_received
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_unsupported_opcodes_received,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x80, 0, 64);

/* reg_ppcnt_a_छोड़ो_mac_ctrl_frames_received
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_छोड़ो_mac_ctrl_frames_received,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x88, 0, 64);

/* reg_ppcnt_a_छोड़ो_mac_ctrl_frames_transmitted
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, a_छोड़ो_mac_ctrl_frames_transmitted,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x90, 0, 64);

/* Ethernet RFC 2863 Counter Group */

/* reg_ppcnt_अगर_in_discards
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, अगर_in_discards,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x10, 0, 64);

/* reg_ppcnt_अगर_out_discards
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, अगर_out_discards,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x38, 0, 64);

/* reg_ppcnt_अगर_out_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, अगर_out_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x40, 0, 64);

/* Ethernet RFC 2819 Counter Group */

/* reg_ppcnt_ether_stats_undersize_pkts
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_undersize_pkts,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x30, 0, 64);

/* reg_ppcnt_ether_stats_oversize_pkts
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_oversize_pkts,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x38, 0, 64);

/* reg_ppcnt_ether_stats_fragments
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_fragments,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x40, 0, 64);

/* reg_ppcnt_ether_stats_pkts64octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts64octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x58, 0, 64);

/* reg_ppcnt_ether_stats_pkts65to127octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts65to127octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x60, 0, 64);

/* reg_ppcnt_ether_stats_pkts128to255octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts128to255octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x68, 0, 64);

/* reg_ppcnt_ether_stats_pkts256to511octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts256to511octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x70, 0, 64);

/* reg_ppcnt_ether_stats_pkts512to1023octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts512to1023octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x78, 0, 64);

/* reg_ppcnt_ether_stats_pkts1024to1518octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts1024to1518octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x80, 0, 64);

/* reg_ppcnt_ether_stats_pkts1519to2047octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts1519to2047octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x88, 0, 64);

/* reg_ppcnt_ether_stats_pkts2048to4095octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts2048to4095octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x90, 0, 64);

/* reg_ppcnt_ether_stats_pkts4096to8191octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts4096to8191octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x98, 0, 64);

/* reg_ppcnt_ether_stats_pkts8192to10239octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ether_stats_pkts8192to10239octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0xA0, 0, 64);

/* Ethernet RFC 3635 Counter Group */

/* reg_ppcnt_करोt3stats_fcs_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, करोt3stats_fcs_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x08, 0, 64);

/* reg_ppcnt_करोt3stats_symbol_errors
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, करोt3stats_symbol_errors,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x60, 0, 64);

/* reg_ppcnt_करोt3control_in_unknown_opcodes
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, करोt3control_in_unknown_opcodes,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x68, 0, 64);

/* reg_ppcnt_करोt3in_छोड़ो_frames
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, करोt3in_छोड़ो_frames,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x70, 0, 64);

/* Ethernet Extended Counter Group Counters */

/* reg_ppcnt_ecn_marked
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ecn_marked,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x08, 0, 64);

/* Ethernet Discard Counter Group Counters */

/* reg_ppcnt_ingress_general
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ingress_general,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x00, 0, 64);

/* reg_ppcnt_ingress_policy_engine
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ingress_policy_engine,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x08, 0, 64);

/* reg_ppcnt_ingress_vlan_membership
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ingress_vlan_membership,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x10, 0, 64);

/* reg_ppcnt_ingress_tag_frame_type
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ingress_tag_frame_type,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x18, 0, 64);

/* reg_ppcnt_egress_vlan_membership
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_vlan_membership,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x20, 0, 64);

/* reg_ppcnt_loopback_filter
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, loopback_filter,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x28, 0, 64);

/* reg_ppcnt_egress_general
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_general,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x30, 0, 64);

/* reg_ppcnt_egress_hoq
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_hoq,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x40, 0, 64);

/* reg_ppcnt_egress_policy_engine
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_policy_engine,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x50, 0, 64);

/* reg_ppcnt_ingress_tx_link_करोwn
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, ingress_tx_link_करोwn,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x58, 0, 64);

/* reg_ppcnt_egress_stp_filter
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_stp_filter,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x60, 0, 64);

/* reg_ppcnt_egress_sll
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, egress_sll,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x70, 0, 64);

/* Ethernet Per Priority Group Counters */

/* reg_ppcnt_rx_octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, rx_octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x00, 0, 64);

/* reg_ppcnt_rx_frames
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, rx_frames,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x20, 0, 64);

/* reg_ppcnt_tx_octets
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tx_octets,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x28, 0, 64);

/* reg_ppcnt_tx_frames
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tx_frames,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x48, 0, 64);

/* reg_ppcnt_rx_छोड़ो
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, rx_छोड़ो,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x50, 0, 64);

/* reg_ppcnt_rx_छोड़ो_duration
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, rx_छोड़ो_duration,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x58, 0, 64);

/* reg_ppcnt_tx_छोड़ो
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tx_छोड़ो,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x60, 0, 64);

/* reg_ppcnt_tx_छोड़ो_duration
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tx_छोड़ो_duration,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x68, 0, 64);

/* reg_ppcnt_rx_छोड़ो_transition
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tx_छोड़ो_transition,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x70, 0, 64);

/* Ethernet Per Traffic Group Counters */

/* reg_ppcnt_tc_transmit_queue
 * Contains the transmit queue depth in cells of traffic class
 * selected by prio_tc and the port selected by local_port.
 * The field cannot be cleared.
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tc_transmit_queue,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x00, 0, 64);

/* reg_ppcnt_tc_no_buffer_discard_uc
 * The number of unicast packets dropped due to lack of shared
 * buffer resources.
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, tc_no_buffer_discard_uc,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x08, 0, 64);

/* Ethernet Per Traffic Class Congestion Group Counters */

/* reg_ppcnt_wred_discard
 * Access: RO
 */
MLXSW_ITEM64(reg, ppcnt, wred_discard,
	     MLXSW_REG_PPCNT_COUNTERS_OFFSET + 0x00, 0, 64);

अटल अंतरभूत व्योम mlxsw_reg_ppcnt_pack(अक्षर *payload, u8 local_port,
					क्रमागत mlxsw_reg_ppcnt_grp grp,
					u8 prio_tc)
अणु
	MLXSW_REG_ZERO(ppcnt, payload);
	mlxsw_reg_ppcnt_swid_set(payload, 0);
	mlxsw_reg_ppcnt_local_port_set(payload, local_port);
	mlxsw_reg_ppcnt_pnat_set(payload, 0);
	mlxsw_reg_ppcnt_grp_set(payload, grp);
	mlxsw_reg_ppcnt_clr_set(payload, 0);
	mlxsw_reg_ppcnt_prio_tc_set(payload, prio_tc);
पूर्ण

/* PLIB - Port Local to InfiniBand Port
 * ------------------------------------
 * The PLIB रेजिस्टर perक्रमms mapping from Local Port पूर्णांकo InfiniBand Port.
 */
#घोषणा MLXSW_REG_PLIB_ID 0x500A
#घोषणा MLXSW_REG_PLIB_LEN 0x10

MLXSW_REG_DEFINE(plib, MLXSW_REG_PLIB_ID, MLXSW_REG_PLIB_LEN);

/* reg_plib_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, plib, local_port, 0x00, 16, 8);

/* reg_plib_ib_port
 * InfiniBand port remapping क्रम local_port.
 * Access: RW
 */
MLXSW_ITEM32(reg, plib, ib_port, 0x00, 0, 8);

/* PPTB - Port Prio To Buffer Register
 * -----------------------------------
 * Configures the चयन priority to buffer table.
 */
#घोषणा MLXSW_REG_PPTB_ID 0x500B
#घोषणा MLXSW_REG_PPTB_LEN 0x10

MLXSW_REG_DEFINE(pptb, MLXSW_REG_PPTB_ID, MLXSW_REG_PPTB_LEN);

क्रमागत अणु
	MLXSW_REG_PPTB_MM_UM,
	MLXSW_REG_PPTB_MM_UNICAST,
	MLXSW_REG_PPTB_MM_MULTICAST,
पूर्ण;

/* reg_pptb_mm
 * Mapping mode.
 * 0 - Map both unicast and multicast packets to the same buffer.
 * 1 - Map only unicast packets.
 * 2 - Map only multicast packets.
 * Access: Index
 *
 * Note: SwitchX-2 only supports the first option.
 */
MLXSW_ITEM32(reg, pptb, mm, 0x00, 28, 2);

/* reg_pptb_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pptb, local_port, 0x00, 16, 8);

/* reg_pptb_um
 * Enables the update of the untagged_buf field.
 * Access: RW
 */
MLXSW_ITEM32(reg, pptb, um, 0x00, 8, 1);

/* reg_pptb_pm
 * Enables the update of the prio_to_buff field.
 * Bit <i> is a flag क्रम updating the mapping क्रम चयन priority <i>.
 * Access: RW
 */
MLXSW_ITEM32(reg, pptb, pm, 0x00, 0, 8);

/* reg_pptb_prio_to_buff
 * Mapping of चयन priority <i> to one of the allocated receive port
 * buffers.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, pptb, prio_to_buff, 0x04, 0x04, 4);

/* reg_pptb_pm_msb
 * Enables the update of the prio_to_buff field.
 * Bit <i> is a flag क्रम updating the mapping क्रम चयन priority <i+8>.
 * Access: RW
 */
MLXSW_ITEM32(reg, pptb, pm_msb, 0x08, 24, 8);

/* reg_pptb_untagged_buff
 * Mapping of untagged frames to one of the allocated receive port buffers.
 * Access: RW
 *
 * Note: In SwitchX-2 this field must be mapped to buffer 8. Reserved क्रम
 * Spectrum, as it maps untagged packets based on the शेष चयन priority.
 */
MLXSW_ITEM32(reg, pptb, untagged_buff, 0x08, 0, 4);

/* reg_pptb_prio_to_buff_msb
 * Mapping of चयन priority <i+8> to one of the allocated receive port
 * buffers.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, pptb, prio_to_buff_msb, 0x0C, 0x04, 4);

#घोषणा MLXSW_REG_PPTB_ALL_PRIO 0xFF

अटल अंतरभूत व्योम mlxsw_reg_pptb_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(pptb, payload);
	mlxsw_reg_pptb_mm_set(payload, MLXSW_REG_PPTB_MM_UM);
	mlxsw_reg_pptb_local_port_set(payload, local_port);
	mlxsw_reg_pptb_pm_set(payload, MLXSW_REG_PPTB_ALL_PRIO);
	mlxsw_reg_pptb_pm_msb_set(payload, MLXSW_REG_PPTB_ALL_PRIO);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pptb_prio_to_buff_pack(अक्षर *payload, u8 prio,
						    u8 buff)
अणु
	mlxsw_reg_pptb_prio_to_buff_set(payload, prio, buff);
	mlxsw_reg_pptb_prio_to_buff_msb_set(payload, prio, buff);
पूर्ण

/* PBMC - Port Buffer Management Control Register
 * ----------------------------------------------
 * The PBMC रेजिस्टर configures and retrieves the port packet buffer
 * allocation क्रम dअगरferent Prios, and the Pause threshold management.
 */
#घोषणा MLXSW_REG_PBMC_ID 0x500C
#घोषणा MLXSW_REG_PBMC_LEN 0x6C

MLXSW_REG_DEFINE(pbmc, MLXSW_REG_PBMC_ID, MLXSW_REG_PBMC_LEN);

/* reg_pbmc_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pbmc, local_port, 0x00, 16, 8);

/* reg_pbmc_xoff_समयr_value
 * When device generates a छोड़ो frame, it uses this value as the छोड़ो
 * समयr (समय क्रम the peer port to छोड़ो in quota-512 bit समय).
 * Access: RW
 */
MLXSW_ITEM32(reg, pbmc, xoff_समयr_value, 0x04, 16, 16);

/* reg_pbmc_xoff_refresh
 * The समय beक्रमe a new छोड़ो frame should be sent to refresh the छोड़ो RW
 * state. Using the same units as xoff_समयr_value above (in quota-512 bit
 * समय).
 * Access: RW
 */
MLXSW_ITEM32(reg, pbmc, xoff_refresh, 0x04, 0, 16);

#घोषणा MLXSW_REG_PBMC_PORT_SHARED_BUF_IDX 11

/* reg_pbmc_buf_lossy
 * The field indicates अगर the buffer is lossy.
 * 0 - Lossless
 * 1 - Lossy
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pbmc, buf_lossy, 0x0C, 25, 1, 0x08, 0x00, false);

/* reg_pbmc_buf_epsb
 * Eligible क्रम Port Shared buffer.
 * If epsb is set, packets asचिन्हित to buffer are allowed to insert the port
 * shared buffer.
 * When buf_lossy is MLXSW_REG_PBMC_LOSSY_LOSSY this field is reserved.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pbmc, buf_epsb, 0x0C, 24, 1, 0x08, 0x00, false);

/* reg_pbmc_buf_size
 * The part of the packet buffer array is allocated क्रम the specअगरic buffer.
 * Units are represented in cells.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, pbmc, buf_size, 0x0C, 0, 16, 0x08, 0x00, false);

/* reg_pbmc_buf_xoff_threshold
 * Once the amount of data in the buffer goes above this value, device
 * starts sending PFC frames क्रम all priorities associated with the
 * buffer. Units are represented in cells. Reserved in हाल of lossy
 * buffer.
 * Access: RW
 *
 * Note: In Spectrum, reserved क्रम buffer[9].
 */
MLXSW_ITEM32_INDEXED(reg, pbmc, buf_xoff_threshold, 0x0C, 16, 16,
		     0x08, 0x04, false);

/* reg_pbmc_buf_xon_threshold
 * When the amount of data in the buffer goes below this value, device
 * stops sending PFC frames क्रम the priorities associated with the
 * buffer. Units are represented in cells. Reserved in हाल of lossy
 * buffer.
 * Access: RW
 *
 * Note: In Spectrum, reserved क्रम buffer[9].
 */
MLXSW_ITEM32_INDEXED(reg, pbmc, buf_xon_threshold, 0x0C, 0, 16,
		     0x08, 0x04, false);

अटल अंतरभूत व्योम mlxsw_reg_pbmc_pack(अक्षर *payload, u8 local_port,
				       u16 xoff_समयr_value, u16 xoff_refresh)
अणु
	MLXSW_REG_ZERO(pbmc, payload);
	mlxsw_reg_pbmc_local_port_set(payload, local_port);
	mlxsw_reg_pbmc_xoff_समयr_value_set(payload, xoff_समयr_value);
	mlxsw_reg_pbmc_xoff_refresh_set(payload, xoff_refresh);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pbmc_lossy_buffer_pack(अक्षर *payload,
						    पूर्णांक buf_index,
						    u16 size)
अणु
	mlxsw_reg_pbmc_buf_lossy_set(payload, buf_index, 1);
	mlxsw_reg_pbmc_buf_epsb_set(payload, buf_index, 0);
	mlxsw_reg_pbmc_buf_size_set(payload, buf_index, size);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_pbmc_lossless_buffer_pack(अक्षर *payload,
						       पूर्णांक buf_index, u16 size,
						       u16 threshold)
अणु
	mlxsw_reg_pbmc_buf_lossy_set(payload, buf_index, 0);
	mlxsw_reg_pbmc_buf_epsb_set(payload, buf_index, 0);
	mlxsw_reg_pbmc_buf_size_set(payload, buf_index, size);
	mlxsw_reg_pbmc_buf_xoff_threshold_set(payload, buf_index, threshold);
	mlxsw_reg_pbmc_buf_xon_threshold_set(payload, buf_index, threshold);
पूर्ण

/* PSPA - Port Switch Partition Allocation
 * ---------------------------------------
 * Controls the association of a port with a चयन partition and enables
 * configuring ports as stacking ports.
 */
#घोषणा MLXSW_REG_PSPA_ID 0x500D
#घोषणा MLXSW_REG_PSPA_LEN 0x8

MLXSW_REG_DEFINE(pspa, MLXSW_REG_PSPA_ID, MLXSW_REG_PSPA_LEN);

/* reg_pspa_swid
 * Switch partition ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, pspa, swid, 0x00, 24, 8);

/* reg_pspa_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pspa, local_port, 0x00, 16, 8);

/* reg_pspa_sub_port
 * Virtual port within the local port. Set to 0 when भव ports are
 * disabled on the local port.
 * Access: Index
 */
MLXSW_ITEM32(reg, pspa, sub_port, 0x00, 8, 8);

अटल अंतरभूत व्योम mlxsw_reg_pspa_pack(अक्षर *payload, u8 swid, u8 local_port)
अणु
	MLXSW_REG_ZERO(pspa, payload);
	mlxsw_reg_pspa_swid_set(payload, swid);
	mlxsw_reg_pspa_local_port_set(payload, local_port);
	mlxsw_reg_pspa_sub_port_set(payload, 0);
पूर्ण

/* PMAOS - Ports Module Administrative and Operational Status
 * ----------------------------------------------------------
 * This रेजिस्टर configures and retrieves the per module status.
 */
#घोषणा MLXSW_REG_PMAOS_ID 0x5012
#घोषणा MLXSW_REG_PMAOS_LEN 0x10

MLXSW_REG_DEFINE(pmaos, MLXSW_REG_PMAOS_ID, MLXSW_REG_PMAOS_LEN);

/* reg_pmaos_slot_index
 * Slot index.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmaos, slot_index, 0x00, 24, 4);

/* reg_pmaos_module
 * Module number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmaos, module, 0x00, 16, 8);

/* reg_pmaos_ase
 * Admin state update enable.
 * If this bit is set, admin state will be updated based on admin_state field.
 * Only relevant on Set() operations.
 * Access: WO
 */
MLXSW_ITEM32(reg, pmaos, ase, 0x04, 31, 1);

/* reg_pmaos_ee
 * Event update enable.
 * If this bit is set, event generation will be updated based on the e field.
 * Only relevant on Set operations.
 * Access: WO
 */
MLXSW_ITEM32(reg, pmaos, ee, 0x04, 30, 1);

क्रमागत mlxsw_reg_pmaos_e अणु
	MLXSW_REG_PMAOS_E_DO_NOT_GENERATE_EVENT,
	MLXSW_REG_PMAOS_E_GENERATE_EVENT,
	MLXSW_REG_PMAOS_E_GENERATE_SINGLE_EVENT,
पूर्ण;

/* reg_pmaos_e
 * Event Generation on operational state change.
 * Access: RW
 */
MLXSW_ITEM32(reg, pmaos, e, 0x04, 0, 2);

अटल अंतरभूत व्योम mlxsw_reg_pmaos_pack(अक्षर *payload, u8 module,
					क्रमागत mlxsw_reg_pmaos_e e)
अणु
	MLXSW_REG_ZERO(pmaos, payload);
	mlxsw_reg_pmaos_module_set(payload, module);
	mlxsw_reg_pmaos_e_set(payload, e);
	mlxsw_reg_pmaos_ee_set(payload, true);
पूर्ण

/* PPLR - Port Physical Loopback Register
 * --------------------------------------
 * This रेजिस्टर allows configuration of the port's loopback mode.
 */
#घोषणा MLXSW_REG_PPLR_ID 0x5018
#घोषणा MLXSW_REG_PPLR_LEN 0x8

MLXSW_REG_DEFINE(pplr, MLXSW_REG_PPLR_ID, MLXSW_REG_PPLR_LEN);

/* reg_pplr_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pplr, local_port, 0x00, 16, 8);

/* Phy local loopback. When set the port's egress traffic is looped back
 * to the receiver and the port transmitter is disabled.
 */
#घोषणा MLXSW_REG_PPLR_LB_TYPE_BIT_PHY_LOCAL BIT(1)

/* reg_pplr_lb_en
 * Loopback enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, pplr, lb_en, 0x04, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_pplr_pack(अक्षर *payload, u8 local_port,
				       bool phy_local)
अणु
	MLXSW_REG_ZERO(pplr, payload);
	mlxsw_reg_pplr_local_port_set(payload, local_port);
	mlxsw_reg_pplr_lb_en_set(payload,
				 phy_local ?
				 MLXSW_REG_PPLR_LB_TYPE_BIT_PHY_LOCAL : 0);
पूर्ण

/* PMPE - Port Module Plug/Unplug Event Register
 * ---------------------------------------------
 * This रेजिस्टर reports any operational status change of a module.
 * A change in the moduleै s state will generate an event only अगर the change
 * happens after arming the event mechanism. Any changes to the module state
 * जबतक the event mechanism is not armed will not be reported. Software can
 * query the PMPE रेजिस्टर क्रम module status.
 */
#घोषणा MLXSW_REG_PMPE_ID 0x5024
#घोषणा MLXSW_REG_PMPE_LEN 0x10

MLXSW_REG_DEFINE(pmpe, MLXSW_REG_PMPE_ID, MLXSW_REG_PMPE_LEN);

/* reg_pmpe_slot_index
 * Slot index.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmpe, slot_index, 0x00, 24, 4);

/* reg_pmpe_module
 * Module number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmpe, module, 0x00, 16, 8);

क्रमागत mlxsw_reg_pmpe_module_status अणु
	MLXSW_REG_PMPE_MODULE_STATUS_PLUGGED_ENABLED = 1,
	MLXSW_REG_PMPE_MODULE_STATUS_UNPLUGGED,
	MLXSW_REG_PMPE_MODULE_STATUS_PLUGGED_ERROR,
	MLXSW_REG_PMPE_MODULE_STATUS_PLUGGED_DISABLED,
पूर्ण;

/* reg_pmpe_module_status
 * Module status.
 * Access: RO
 */
MLXSW_ITEM32(reg, pmpe, module_status, 0x00, 0, 4);

/* reg_pmpe_error_type
 * Module error details.
 * Access: RO
 */
MLXSW_ITEM32(reg, pmpe, error_type, 0x04, 8, 4);

/* PDDR - Port Diagnostics Database Register
 * -----------------------------------------
 * The PDDR enables to पढ़ो the Phy debug database
 */
#घोषणा MLXSW_REG_PDDR_ID 0x5031
#घोषणा MLXSW_REG_PDDR_LEN 0x100

MLXSW_REG_DEFINE(pddr, MLXSW_REG_PDDR_ID, MLXSW_REG_PDDR_LEN);

/* reg_pddr_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pddr, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_pddr_page_select अणु
	MLXSW_REG_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO = 1,
पूर्ण;

/* reg_pddr_page_select
 * Page select index.
 * Access: Index
 */
MLXSW_ITEM32(reg, pddr, page_select, 0x04, 0, 8);

क्रमागत mlxsw_reg_pddr_trblsh_group_opcode अणु
	/* Monitor opcodes */
	MLXSW_REG_PDDR_TRBLSH_GROUP_OPCODE_MONITOR,
पूर्ण;

/* reg_pddr_group_opcode
 * Group selector.
 * Access: Index
 */
MLXSW_ITEM32(reg, pddr, trblsh_group_opcode, 0x08, 0, 16);

/* reg_pddr_status_opcode
 * Group selector.
 * Access: RO
 */
MLXSW_ITEM32(reg, pddr, trblsh_status_opcode, 0x0C, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_pddr_pack(अक्षर *payload, u8 local_port,
				       u8 page_select)
अणु
	MLXSW_REG_ZERO(pddr, payload);
	mlxsw_reg_pddr_local_port_set(payload, local_port);
	mlxsw_reg_pddr_page_select_set(payload, page_select);
पूर्ण

/* PMTM - Port Module Type Mapping Register
 * ----------------------------------------
 * The PMTM allows query or configuration of module types.
 */
#घोषणा MLXSW_REG_PMTM_ID 0x5067
#घोषणा MLXSW_REG_PMTM_LEN 0x10

MLXSW_REG_DEFINE(pmपंचांग, MLXSW_REG_PMTM_ID, MLXSW_REG_PMTM_LEN);

/* reg_pmपंचांग_module
 * Module number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pmपंचांग, module, 0x00, 16, 8);

क्रमागत mlxsw_reg_pmपंचांग_module_type अणु
	/* Backplane with 4 lanes */
	MLXSW_REG_PMTM_MODULE_TYPE_BP_4X,
	/* QSFP */
	MLXSW_REG_PMTM_MODULE_TYPE_QSFP,
	/* SFP */
	MLXSW_REG_PMTM_MODULE_TYPE_SFP,
	/* Backplane with single lane */
	MLXSW_REG_PMTM_MODULE_TYPE_BP_1X = 4,
	/* Backplane with two lane */
	MLXSW_REG_PMTM_MODULE_TYPE_BP_2X = 8,
	/* Chip2Chip4x */
	MLXSW_REG_PMTM_MODULE_TYPE_C2C4X = 10,
	/* Chip2Chip2x */
	MLXSW_REG_PMTM_MODULE_TYPE_C2C2X,
	/* Chip2Chip1x */
	MLXSW_REG_PMTM_MODULE_TYPE_C2C1X,
	/* QSFP-DD */
	MLXSW_REG_PMTM_MODULE_TYPE_QSFP_DD = 14,
	/* OSFP */
	MLXSW_REG_PMTM_MODULE_TYPE_OSFP,
	/* SFP-DD */
	MLXSW_REG_PMTM_MODULE_TYPE_SFP_DD,
	/* DSFP */
	MLXSW_REG_PMTM_MODULE_TYPE_DSFP,
	/* Chip2Chip8x */
	MLXSW_REG_PMTM_MODULE_TYPE_C2C8X,
पूर्ण;

/* reg_pmपंचांग_module_type
 * Module type.
 * Access: RW
 */
MLXSW_ITEM32(reg, pmपंचांग, module_type, 0x04, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_pmपंचांग_pack(अक्षर *payload, u8 module)
अणु
	MLXSW_REG_ZERO(pmपंचांग, payload);
	mlxsw_reg_pmपंचांग_module_set(payload, module);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_pmपंचांग_unpack(अक्षर *payload,
		      क्रमागत mlxsw_reg_pmपंचांग_module_type *module_type)
अणु
	*module_type = mlxsw_reg_pmपंचांग_module_type_get(payload);
पूर्ण

/* HTGT - Host Trap Group Table
 * ----------------------------
 * Configures the properties क्रम क्रमwarding to CPU.
 */
#घोषणा MLXSW_REG_HTGT_ID 0x7002
#घोषणा MLXSW_REG_HTGT_LEN 0x20

MLXSW_REG_DEFINE(htgt, MLXSW_REG_HTGT_ID, MLXSW_REG_HTGT_LEN);

/* reg_htgt_swid
 * Switch partition ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, htgt, swid, 0x00, 24, 8);

#घोषणा MLXSW_REG_HTGT_PATH_TYPE_LOCAL 0x0	/* For locally attached CPU */

/* reg_htgt_type
 * CPU path type.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, type, 0x00, 8, 4);

क्रमागत mlxsw_reg_htgt_trap_group अणु
	MLXSW_REG_HTGT_TRAP_GROUP_EMAD,
	MLXSW_REG_HTGT_TRAP_GROUP_MFDE,
	MLXSW_REG_HTGT_TRAP_GROUP_MTWE,
	MLXSW_REG_HTGT_TRAP_GROUP_PMPE,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_STP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_LACP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_LLDP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_MC_SNOOPING,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_BGP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_OSPF,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_PIM,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_MULTICAST,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_NEIGH_DISCOVERY,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_ROUTER_EXP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_EXTERNAL_ROUTE,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_IP2ME,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_DHCP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_EVENT,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_IPV6,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_LBERROR,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP0,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_PTP1,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_VRRP,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_PKT_SAMPLE,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_FLOW_LOGGING,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_FID_MISS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_BFD,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_DUMMY,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_L2_DISCARDS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_L3_DISCARDS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_L3_EXCEPTIONS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_TUNNEL_DISCARDS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_ACL_DISCARDS,
	MLXSW_REG_HTGT_TRAP_GROUP_SP_BUFFER_DISCARDS,

	__MLXSW_REG_HTGT_TRAP_GROUP_MAX,
	MLXSW_REG_HTGT_TRAP_GROUP_MAX = __MLXSW_REG_HTGT_TRAP_GROUP_MAX - 1
पूर्ण;

/* reg_htgt_trap_group
 * Trap group number. User defined number specअगरying which trap groups
 * should be क्रमwarded to the CPU. The mapping between trap IDs and trap
 * groups is configured using HPKT रेजिस्टर.
 * Access: Index
 */
MLXSW_ITEM32(reg, htgt, trap_group, 0x00, 0, 8);

क्रमागत अणु
	MLXSW_REG_HTGT_POLICER_DISABLE,
	MLXSW_REG_HTGT_POLICER_ENABLE,
पूर्ण;

/* reg_htgt_pide
 * Enable policer ID specअगरied using 'pid' field.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, pide, 0x04, 15, 1);

#घोषणा MLXSW_REG_HTGT_INVALID_POLICER 0xff

/* reg_htgt_pid
 * Policer ID क्रम the trap group.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, pid, 0x04, 0, 8);

#घोषणा MLXSW_REG_HTGT_TRAP_TO_CPU 0x0

/* reg_htgt_mirror_action
 * Mirror action to use.
 * 0 - Trap to CPU.
 * 1 - Trap to CPU and mirror to a mirroring agent.
 * 2 - Mirror to a mirroring agent and करो not trap to CPU.
 * Access: RW
 *
 * Note: Mirroring to a mirroring agent is only supported in Spectrum.
 */
MLXSW_ITEM32(reg, htgt, mirror_action, 0x08, 8, 2);

/* reg_htgt_mirroring_agent
 * Mirroring agent.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, mirroring_agent, 0x08, 0, 3);

#घोषणा MLXSW_REG_HTGT_DEFAULT_PRIORITY 0

/* reg_htgt_priority
 * Trap group priority.
 * In हाल a packet matches multiple classअगरication rules, the packet will
 * only be trapped once, based on the trap ID associated with the group (via
 * रेजिस्टर HPKT) with the highest priority.
 * Supported values are 0-7, with 7 represnting the highest priority.
 * Access: RW
 *
 * Note: In SwitchX-2 this field is ignored and the priority value is replaced
 * by the 'trap_group' field.
 */
MLXSW_ITEM32(reg, htgt, priority, 0x0C, 0, 4);

#घोषणा MLXSW_REG_HTGT_DEFAULT_TC 7

/* reg_htgt_local_path_cpu_tclass
 * CPU ingress traffic class क्रम the trap group.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, local_path_cpu_tclass, 0x10, 16, 6);

क्रमागत mlxsw_reg_htgt_local_path_rdq अणु
	MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_CTRL = 0x13,
	MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_RX = 0x14,
	MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SX2_EMAD = 0x15,
	MLXSW_REG_HTGT_LOCAL_PATH_RDQ_SIB_EMAD = 0x15,
पूर्ण;
/* reg_htgt_local_path_rdq
 * Receive descriptor queue (RDQ) to use क्रम the trap group.
 * Access: RW
 */
MLXSW_ITEM32(reg, htgt, local_path_rdq, 0x10, 0, 6);

अटल अंतरभूत व्योम mlxsw_reg_htgt_pack(अक्षर *payload, u8 group, u8 policer_id,
				       u8 priority, u8 tc)
अणु
	MLXSW_REG_ZERO(htgt, payload);

	अगर (policer_id == MLXSW_REG_HTGT_INVALID_POLICER) अणु
		mlxsw_reg_htgt_pide_set(payload,
					MLXSW_REG_HTGT_POLICER_DISABLE);
	पूर्ण अन्यथा अणु
		mlxsw_reg_htgt_pide_set(payload,
					MLXSW_REG_HTGT_POLICER_ENABLE);
		mlxsw_reg_htgt_pid_set(payload, policer_id);
	पूर्ण

	mlxsw_reg_htgt_type_set(payload, MLXSW_REG_HTGT_PATH_TYPE_LOCAL);
	mlxsw_reg_htgt_trap_group_set(payload, group);
	mlxsw_reg_htgt_mirror_action_set(payload, MLXSW_REG_HTGT_TRAP_TO_CPU);
	mlxsw_reg_htgt_mirroring_agent_set(payload, 0);
	mlxsw_reg_htgt_priority_set(payload, priority);
	mlxsw_reg_htgt_local_path_cpu_tclass_set(payload, tc);
	mlxsw_reg_htgt_local_path_rdq_set(payload, group);
पूर्ण

/* HPKT - Host Packet Trap
 * -----------------------
 * Configures trap IDs inside trap groups.
 */
#घोषणा MLXSW_REG_HPKT_ID 0x7003
#घोषणा MLXSW_REG_HPKT_LEN 0x10

MLXSW_REG_DEFINE(hpkt, MLXSW_REG_HPKT_ID, MLXSW_REG_HPKT_LEN);

क्रमागत अणु
	MLXSW_REG_HPKT_ACK_NOT_REQUIRED,
	MLXSW_REG_HPKT_ACK_REQUIRED,
पूर्ण;

/* reg_hpkt_ack
 * Require acknowledgements from the host क्रम events.
 * If set, then the device will रुको क्रम the event it sent to be acknowledged
 * by the host. This option is only relevant क्रम event trap IDs.
 * Access: RW
 *
 * Note: Currently not supported by firmware.
 */
MLXSW_ITEM32(reg, hpkt, ack, 0x00, 24, 1);

क्रमागत mlxsw_reg_hpkt_action अणु
	MLXSW_REG_HPKT_ACTION_FORWARD,
	MLXSW_REG_HPKT_ACTION_TRAP_TO_CPU,
	MLXSW_REG_HPKT_ACTION_MIRROR_TO_CPU,
	MLXSW_REG_HPKT_ACTION_DISCARD,
	MLXSW_REG_HPKT_ACTION_SOFT_DISCARD,
	MLXSW_REG_HPKT_ACTION_TRAP_AND_SOFT_DISCARD,
	MLXSW_REG_HPKT_ACTION_TRAP_EXCEPTION_TO_CPU,
	MLXSW_REG_HPKT_ACTION_SET_FW_DEFAULT = 15,
पूर्ण;

/* reg_hpkt_action
 * Action to perक्रमm on packet when trapped.
 * 0 - No action. Forward to CPU based on चयनing rules.
 * 1 - Trap to CPU (CPU receives sole copy).
 * 2 - Mirror to CPU (CPU receives a replica of the packet).
 * 3 - Discard.
 * 4 - Soft discard (allow other traps to act on the packet).
 * 5 - Trap and soft discard (allow other traps to overग_लिखो this trap).
 * 6 - Trap to CPU (CPU receives sole copy) and count it as error.
 * 15 - Restore the firmware's शेष action.
 * Access: RW
 *
 * Note: Must be set to 0 (क्रमward) क्रम event trap IDs, as they are alपढ़ोy
 * addressed to the CPU.
 */
MLXSW_ITEM32(reg, hpkt, action, 0x00, 20, 3);

/* reg_hpkt_trap_group
 * Trap group to associate the trap with.
 * Access: RW
 */
MLXSW_ITEM32(reg, hpkt, trap_group, 0x00, 12, 6);

/* reg_hpkt_trap_id
 * Trap ID.
 * Access: Index
 *
 * Note: A trap ID can only be associated with a single trap group. The device
 * will associate the trap ID with the last trap group configured.
 */
MLXSW_ITEM32(reg, hpkt, trap_id, 0x00, 0, 10);

क्रमागत अणु
	MLXSW_REG_HPKT_CTRL_PACKET_DEFAULT,
	MLXSW_REG_HPKT_CTRL_PACKET_NO_BUFFER,
	MLXSW_REG_HPKT_CTRL_PACKET_USE_BUFFER,
पूर्ण;

/* reg_hpkt_ctrl
 * Configure dedicated buffer resources क्रम control packets.
 * Ignored by SwitchX-2.
 * 0 - Keep factory शेषs.
 * 1 - Do not use control buffer क्रम this trap ID.
 * 2 - Use control buffer क्रम this trap ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, hpkt, ctrl, 0x04, 16, 2);

अटल अंतरभूत व्योम mlxsw_reg_hpkt_pack(अक्षर *payload, u8 action, u16 trap_id,
				       क्रमागत mlxsw_reg_htgt_trap_group trap_group,
				       bool is_ctrl)
अणु
	MLXSW_REG_ZERO(hpkt, payload);
	mlxsw_reg_hpkt_ack_set(payload, MLXSW_REG_HPKT_ACK_NOT_REQUIRED);
	mlxsw_reg_hpkt_action_set(payload, action);
	mlxsw_reg_hpkt_trap_group_set(payload, trap_group);
	mlxsw_reg_hpkt_trap_id_set(payload, trap_id);
	mlxsw_reg_hpkt_ctrl_set(payload, is_ctrl ?
				MLXSW_REG_HPKT_CTRL_PACKET_USE_BUFFER :
				MLXSW_REG_HPKT_CTRL_PACKET_NO_BUFFER);
पूर्ण

/* RGCR - Router General Configuration Register
 * --------------------------------------------
 * The रेजिस्टर is used क्रम setting up the router configuration.
 */
#घोषणा MLXSW_REG_RGCR_ID 0x8001
#घोषणा MLXSW_REG_RGCR_LEN 0x28

MLXSW_REG_DEFINE(rgcr, MLXSW_REG_RGCR_ID, MLXSW_REG_RGCR_LEN);

/* reg_rgcr_ipv4_en
 * IPv4 router enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, rgcr, ipv4_en, 0x00, 31, 1);

/* reg_rgcr_ipv6_en
 * IPv6 router enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, rgcr, ipv6_en, 0x00, 30, 1);

/* reg_rgcr_max_router_पूर्णांकerfaces
 * Defines the maximum number of active router पूर्णांकerfaces क्रम all भव
 * routers.
 * Access: RW
 */
MLXSW_ITEM32(reg, rgcr, max_router_पूर्णांकerfaces, 0x10, 0, 16);

/* reg_rgcr_usp
 * Update चयन priority and packet color.
 * 0 - Preserve the value of Switch Priority and packet color.
 * 1 - Recalculate the value of Switch Priority and packet color.
 * Access: RW
 *
 * Note: Not supported by SwitchX and SwitchX-2.
 */
MLXSW_ITEM32(reg, rgcr, usp, 0x18, 20, 1);

/* reg_rgcr_pcp_rw
 * Indicates how to handle the pcp_reग_लिखो_en value:
 * 0 - Preserve the value of pcp_reग_लिखो_en.
 * 2 - Disable PCP reग_लिखो.
 * 3 - Enable PCP reग_लिखो.
 * Access: RW
 *
 * Note: Not supported by SwitchX and SwitchX-2.
 */
MLXSW_ITEM32(reg, rgcr, pcp_rw, 0x18, 16, 2);

/* reg_rgcr_activity_dis
 * Activity disable:
 * 0 - Activity will be set when an entry is hit (शेष).
 * 1 - Activity will not be set when an entry is hit.
 *
 * Bit 0 - Disable activity bit in Router Algorithmic LPM Unicast Entry
 * (RALUE).
 * Bit 1 - Disable activity bit in Router Algorithmic LPM Unicast Host
 * Entry (RAUHT).
 * Bits 2:7 are reserved.
 * Access: RW
 *
 * Note: Not supported by SwitchX, SwitchX-2 and Switch-IB.
 */
MLXSW_ITEM32(reg, rgcr, activity_dis, 0x20, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_rgcr_pack(अक्षर *payload, bool ipv4_en,
				       bool ipv6_en)
अणु
	MLXSW_REG_ZERO(rgcr, payload);
	mlxsw_reg_rgcr_ipv4_en_set(payload, ipv4_en);
	mlxsw_reg_rgcr_ipv6_en_set(payload, ipv6_en);
पूर्ण

/* RITR - Router Interface Table Register
 * --------------------------------------
 * The रेजिस्टर is used to configure the router पूर्णांकerface table.
 */
#घोषणा MLXSW_REG_RITR_ID 0x8002
#घोषणा MLXSW_REG_RITR_LEN 0x40

MLXSW_REG_DEFINE(ritr, MLXSW_REG_RITR_ID, MLXSW_REG_RITR_LEN);

/* reg_ritr_enable
 * Enables routing on the router पूर्णांकerface.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, enable, 0x00, 31, 1);

/* reg_ritr_ipv4
 * IPv4 routing enable. Enables routing of IPv4 traffic on the router
 * पूर्णांकerface.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv4, 0x00, 29, 1);

/* reg_ritr_ipv6
 * IPv6 routing enable. Enables routing of IPv6 traffic on the router
 * पूर्णांकerface.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv6, 0x00, 28, 1);

/* reg_ritr_ipv4_mc
 * IPv4 multicast routing enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv4_mc, 0x00, 27, 1);

/* reg_ritr_ipv6_mc
 * IPv6 multicast routing enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv6_mc, 0x00, 26, 1);

क्रमागत mlxsw_reg_ritr_अगर_type अणु
	/* VLAN पूर्णांकerface. */
	MLXSW_REG_RITR_VLAN_IF,
	/* FID पूर्णांकerface. */
	MLXSW_REG_RITR_FID_IF,
	/* Sub-port पूर्णांकerface. */
	MLXSW_REG_RITR_SP_IF,
	/* Loopback Interface. */
	MLXSW_REG_RITR_LOOPBACK_IF,
पूर्ण;

/* reg_ritr_type
 * Router पूर्णांकerface type as per क्रमागत mlxsw_reg_ritr_अगर_type.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, type, 0x00, 23, 3);

क्रमागत अणु
	MLXSW_REG_RITR_RIF_CREATE,
	MLXSW_REG_RITR_RIF_DEL,
पूर्ण;

/* reg_ritr_op
 * Opcode:
 * 0 - Create or edit RIF.
 * 1 - Delete RIF.
 * Reserved क्रम SwitchX-2. For Spectrum, editing of पूर्णांकerface properties
 * is not supported. An पूर्णांकerface must be deleted and re-created in order
 * to update properties.
 * Access: WO
 */
MLXSW_ITEM32(reg, ritr, op, 0x00, 20, 2);

/* reg_ritr_rअगर
 * Router पूर्णांकerface index. A poपूर्णांकer to the Router Interface Table.
 * Access: Index
 */
MLXSW_ITEM32(reg, ritr, rअगर, 0x00, 0, 16);

/* reg_ritr_ipv4_fe
 * IPv4 Forwarding Enable.
 * Enables routing of IPv4 traffic on the router पूर्णांकerface. When disabled,
 * क्रमwarding is blocked but local traffic (traps and IP2ME) will be enabled.
 * Not supported in SwitchX-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv4_fe, 0x04, 29, 1);

/* reg_ritr_ipv6_fe
 * IPv6 Forwarding Enable.
 * Enables routing of IPv6 traffic on the router पूर्णांकerface. When disabled,
 * क्रमwarding is blocked but local traffic (traps and IP2ME) will be enabled.
 * Not supported in SwitchX-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv6_fe, 0x04, 28, 1);

/* reg_ritr_ipv4_mc_fe
 * IPv4 Multicast Forwarding Enable.
 * When disabled, क्रमwarding is blocked but local traffic (traps and IP to me)
 * will be enabled.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv4_mc_fe, 0x04, 27, 1);

/* reg_ritr_ipv6_mc_fe
 * IPv6 Multicast Forwarding Enable.
 * When disabled, क्रमwarding is blocked but local traffic (traps and IP to me)
 * will be enabled.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ipv6_mc_fe, 0x04, 26, 1);

/* reg_ritr_lb_en
 * Loop-back filter enable क्रम unicast packets.
 * If the flag is set then loop-back filter क्रम unicast packets is
 * implemented on the RIF. Multicast packets are always subject to
 * loop-back filtering.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, lb_en, 0x04, 24, 1);

/* reg_ritr_भव_router
 * Virtual router ID associated with the router पूर्णांकerface.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, भव_router, 0x04, 0, 16);

/* reg_ritr_mtu
 * Router पूर्णांकerface MTU.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, mtu, 0x34, 0, 16);

/* reg_ritr_अगर_swid
 * Switch partition ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, अगर_swid, 0x08, 24, 8);

/* reg_ritr_अगर_mac
 * Router पूर्णांकerface MAC address.
 * In Spectrum, all MAC addresses must have the same 38 MSBits.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ritr, अगर_mac, 0x12, 6);

/* reg_ritr_अगर_vrrp_id_ipv6
 * VRRP ID क्रम IPv6
 * Note: Reserved क्रम RIF types other than VLAN, FID and Sub-port.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, अगर_vrrp_id_ipv6, 0x1C, 8, 8);

/* reg_ritr_अगर_vrrp_id_ipv4
 * VRRP ID क्रम IPv4
 * Note: Reserved क्रम RIF types other than VLAN, FID and Sub-port.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, अगर_vrrp_id_ipv4, 0x1C, 0, 8);

/* VLAN Interface */

/* reg_ritr_vlan_अगर_vid
 * VLAN ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, vlan_अगर_vid, 0x08, 0, 12);

/* FID Interface */

/* reg_ritr_fid_अगर_fid
 * Filtering ID. Used to connect a bridge to the router. Only FIDs from
 * the vFID range are supported.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, fid_अगर_fid, 0x08, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_ritr_fid_set(अक्षर *payload,
					  क्रमागत mlxsw_reg_ritr_अगर_type rअगर_type,
					  u16 fid)
अणु
	अगर (rअगर_type == MLXSW_REG_RITR_FID_IF)
		mlxsw_reg_ritr_fid_अगर_fid_set(payload, fid);
	अन्यथा
		mlxsw_reg_ritr_vlan_अगर_vid_set(payload, fid);
पूर्ण

/* Sub-port Interface */

/* reg_ritr_sp_अगर_lag
 * LAG indication. When this bit is set the प्रणाली_port field holds the
 * LAG identअगरier.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, sp_अगर_lag, 0x08, 24, 1);

/* reg_ritr_sp_प्रणाली_port
 * Port unique indentअगरier. When lag bit is set, this field holds the
 * lag_id in bits 0:9.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, sp_अगर_प्रणाली_port, 0x08, 0, 16);

/* reg_ritr_sp_अगर_vid
 * VLAN ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, sp_अगर_vid, 0x18, 0, 12);

/* Loopback Interface */

क्रमागत mlxsw_reg_ritr_loopback_protocol अणु
	/* IPinIP IPv4 underlay Unicast */
	MLXSW_REG_RITR_LOOPBACK_PROTOCOL_IPIP_IPV4,
	/* IPinIP IPv6 underlay Unicast */
	MLXSW_REG_RITR_LOOPBACK_PROTOCOL_IPIP_IPV6,
	/* IPinIP generic - used क्रम Spectrum-2 underlay RIF */
	MLXSW_REG_RITR_LOOPBACK_GENERIC,
पूर्ण;

/* reg_ritr_loopback_protocol
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_protocol, 0x08, 28, 4);

क्रमागत mlxsw_reg_ritr_loopback_ipip_type अणु
	/* Tunnel is IPinIP. */
	MLXSW_REG_RITR_LOOPBACK_IPIP_TYPE_IP_IN_IP,
	/* Tunnel is GRE, no key. */
	MLXSW_REG_RITR_LOOPBACK_IPIP_TYPE_IP_IN_GRE_IN_IP,
	/* Tunnel is GRE, with a key. */
	MLXSW_REG_RITR_LOOPBACK_IPIP_TYPE_IP_IN_GRE_KEY_IN_IP,
पूर्ण;

/* reg_ritr_loopback_ipip_type
 * Encapsulation type.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_ipip_type, 0x10, 24, 4);

क्रमागत mlxsw_reg_ritr_loopback_ipip_options अणु
	/* The key is defined by gre_key. */
	MLXSW_REG_RITR_LOOPBACK_IPIP_OPTIONS_GRE_KEY_PRESET,
पूर्ण;

/* reg_ritr_loopback_ipip_options
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_ipip_options, 0x10, 20, 4);

/* reg_ritr_loopback_ipip_uvr
 * Underlay Virtual Router ID.
 * Range is 0..cap_max_भव_routers-1.
 * Reserved क्रम Spectrum-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_ipip_uvr, 0x10, 0, 16);

/* reg_ritr_loopback_ipip_underlay_rअगर
 * Underlay ingress router पूर्णांकerface.
 * Reserved क्रम Spectrum.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_ipip_underlay_rअगर, 0x14, 0, 16);

/* reg_ritr_loopback_ipip_usip*
 * Encapsulation Underlay source IP.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ritr, loopback_ipip_usip6, 0x18, 16);
MLXSW_ITEM32(reg, ritr, loopback_ipip_usip4, 0x24, 0, 32);

/* reg_ritr_loopback_ipip_gre_key
 * GRE Key.
 * Reserved when ipip_type is not IP_IN_GRE_KEY_IN_IP.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, loopback_ipip_gre_key, 0x28, 0, 32);

/* Shared between ingress/egress */
क्रमागत mlxsw_reg_ritr_counter_set_type अणु
	/* No Count. */
	MLXSW_REG_RITR_COUNTER_SET_TYPE_NO_COUNT = 0x0,
	/* Basic. Used क्रम router पूर्णांकerfaces, counting the following:
	 *	- Error and Discard counters.
	 *	- Unicast, Multicast and Broadcast counters. Sharing the
	 *	  same set of counters क्रम the dअगरferent type of traffic
	 *	  (IPv4, IPv6 and mpls).
	 */
	MLXSW_REG_RITR_COUNTER_SET_TYPE_BASIC = 0x9,
पूर्ण;

/* reg_ritr_ingress_counter_index
 * Counter Index क्रम flow counter.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ingress_counter_index, 0x38, 0, 24);

/* reg_ritr_ingress_counter_set_type
 * Igress Counter Set Type क्रम router पूर्णांकerface counter.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, ingress_counter_set_type, 0x38, 24, 8);

/* reg_ritr_egress_counter_index
 * Counter Index क्रम flow counter.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, egress_counter_index, 0x3C, 0, 24);

/* reg_ritr_egress_counter_set_type
 * Egress Counter Set Type क्रम router पूर्णांकerface counter.
 * Access: RW
 */
MLXSW_ITEM32(reg, ritr, egress_counter_set_type, 0x3C, 24, 8);

अटल अंतरभूत व्योम mlxsw_reg_ritr_counter_pack(अक्षर *payload, u32 index,
					       bool enable, bool egress)
अणु
	क्रमागत mlxsw_reg_ritr_counter_set_type set_type;

	अगर (enable)
		set_type = MLXSW_REG_RITR_COUNTER_SET_TYPE_BASIC;
	अन्यथा
		set_type = MLXSW_REG_RITR_COUNTER_SET_TYPE_NO_COUNT;
	mlxsw_reg_ritr_egress_counter_set_type_set(payload, set_type);

	अगर (egress)
		mlxsw_reg_ritr_egress_counter_index_set(payload, index);
	अन्यथा
		mlxsw_reg_ritr_ingress_counter_index_set(payload, index);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ritr_rअगर_pack(अक्षर *payload, u16 rअगर)
अणु
	MLXSW_REG_ZERO(ritr, payload);
	mlxsw_reg_ritr_rअगर_set(payload, rअगर);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ritr_sp_अगर_pack(अक्षर *payload, bool lag,
					     u16 प्रणाली_port, u16 vid)
अणु
	mlxsw_reg_ritr_sp_अगर_lag_set(payload, lag);
	mlxsw_reg_ritr_sp_अगर_प्रणाली_port_set(payload, प्रणाली_port);
	mlxsw_reg_ritr_sp_अगर_vid_set(payload, vid);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ritr_pack(अक्षर *payload, bool enable,
				       क्रमागत mlxsw_reg_ritr_अगर_type type,
				       u16 rअगर, u16 vr_id, u16 mtu)
अणु
	bool op = enable ? MLXSW_REG_RITR_RIF_CREATE : MLXSW_REG_RITR_RIF_DEL;

	MLXSW_REG_ZERO(ritr, payload);
	mlxsw_reg_ritr_enable_set(payload, enable);
	mlxsw_reg_ritr_ipv4_set(payload, 1);
	mlxsw_reg_ritr_ipv6_set(payload, 1);
	mlxsw_reg_ritr_ipv4_mc_set(payload, 1);
	mlxsw_reg_ritr_ipv6_mc_set(payload, 1);
	mlxsw_reg_ritr_type_set(payload, type);
	mlxsw_reg_ritr_op_set(payload, op);
	mlxsw_reg_ritr_rअगर_set(payload, rअगर);
	mlxsw_reg_ritr_ipv4_fe_set(payload, 1);
	mlxsw_reg_ritr_ipv6_fe_set(payload, 1);
	mlxsw_reg_ritr_ipv4_mc_fe_set(payload, 1);
	mlxsw_reg_ritr_ipv6_mc_fe_set(payload, 1);
	mlxsw_reg_ritr_lb_en_set(payload, 1);
	mlxsw_reg_ritr_भव_router_set(payload, vr_id);
	mlxsw_reg_ritr_mtu_set(payload, mtu);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ritr_mac_pack(अक्षर *payload, स्थिर अक्षर *mac)
अणु
	mlxsw_reg_ritr_अगर_mac_स_नकल_to(payload, mac);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ritr_loopback_ipip_common_pack(अक्षर *payload,
			    क्रमागत mlxsw_reg_ritr_loopback_ipip_type ipip_type,
			    क्रमागत mlxsw_reg_ritr_loopback_ipip_options options,
			    u16 uvr_id, u16 underlay_rअगर, u32 gre_key)
अणु
	mlxsw_reg_ritr_loopback_ipip_type_set(payload, ipip_type);
	mlxsw_reg_ritr_loopback_ipip_options_set(payload, options);
	mlxsw_reg_ritr_loopback_ipip_uvr_set(payload, uvr_id);
	mlxsw_reg_ritr_loopback_ipip_underlay_rअगर_set(payload, underlay_rअगर);
	mlxsw_reg_ritr_loopback_ipip_gre_key_set(payload, gre_key);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ritr_loopback_ipip4_pack(अक्षर *payload,
			    क्रमागत mlxsw_reg_ritr_loopback_ipip_type ipip_type,
			    क्रमागत mlxsw_reg_ritr_loopback_ipip_options options,
			    u16 uvr_id, u16 underlay_rअगर, u32 usip, u32 gre_key)
अणु
	mlxsw_reg_ritr_loopback_protocol_set(payload,
				    MLXSW_REG_RITR_LOOPBACK_PROTOCOL_IPIP_IPV4);
	mlxsw_reg_ritr_loopback_ipip_common_pack(payload, ipip_type, options,
						 uvr_id, underlay_rअगर, gre_key);
	mlxsw_reg_ritr_loopback_ipip_usip4_set(payload, usip);
पूर्ण

/* RTAR - Router TCAM Allocation Register
 * --------------------------------------
 * This रेजिस्टर is used क्रम allocation of regions in the TCAM table.
 */
#घोषणा MLXSW_REG_RTAR_ID 0x8004
#घोषणा MLXSW_REG_RTAR_LEN 0x20

MLXSW_REG_DEFINE(rtar, MLXSW_REG_RTAR_ID, MLXSW_REG_RTAR_LEN);

क्रमागत mlxsw_reg_rtar_op अणु
	MLXSW_REG_RTAR_OP_ALLOCATE,
	MLXSW_REG_RTAR_OP_RESIZE,
	MLXSW_REG_RTAR_OP_DEALLOCATE,
पूर्ण;

/* reg_rtar_op
 * Access: WO
 */
MLXSW_ITEM32(reg, rtar, op, 0x00, 28, 4);

क्रमागत mlxsw_reg_rtar_key_type अणु
	MLXSW_REG_RTAR_KEY_TYPE_IPV4_MULTICAST = 1,
	MLXSW_REG_RTAR_KEY_TYPE_IPV6_MULTICAST = 3
पूर्ण;

/* reg_rtar_key_type
 * TCAM key type क्रम the region.
 * Access: WO
 */
MLXSW_ITEM32(reg, rtar, key_type, 0x00, 0, 8);

/* reg_rtar_region_size
 * TCAM region size. When allocating/resizing this is the requested
 * size, the response is the actual size.
 * Note: Actual size may be larger than requested.
 * Reserved क्रम op = Deallocate
 * Access: WO
 */
MLXSW_ITEM32(reg, rtar, region_size, 0x04, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_rtar_pack(अक्षर *payload,
				       क्रमागत mlxsw_reg_rtar_op op,
				       क्रमागत mlxsw_reg_rtar_key_type key_type,
				       u16 region_size)
अणु
	MLXSW_REG_ZERO(rtar, payload);
	mlxsw_reg_rtar_op_set(payload, op);
	mlxsw_reg_rtar_key_type_set(payload, key_type);
	mlxsw_reg_rtar_region_size_set(payload, region_size);
पूर्ण

/* RATR - Router Adjacency Table Register
 * --------------------------------------
 * The RATR रेजिस्टर is used to configure the Router Adjacency (next-hop)
 * Table.
 */
#घोषणा MLXSW_REG_RATR_ID 0x8008
#घोषणा MLXSW_REG_RATR_LEN 0x2C

MLXSW_REG_DEFINE(ratr, MLXSW_REG_RATR_ID, MLXSW_REG_RATR_LEN);

क्रमागत mlxsw_reg_ratr_op अणु
	/* Read */
	MLXSW_REG_RATR_OP_QUERY_READ = 0,
	/* Read and clear activity */
	MLXSW_REG_RATR_OP_QUERY_READ_CLEAR = 2,
	/* Write Adjacency entry */
	MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY = 1,
	/* Write Adjacency entry only अगर the activity is cleared.
	 * The ग_लिखो may not succeed अगर the activity is set. There is not
	 * direct feedback अगर the ग_लिखो has succeeded or not, however
	 * the get will reveal the actual entry (SW can compare the get
	 * response to the set command).
	 */
	MLXSW_REG_RATR_OP_WRITE_WRITE_ENTRY_ON_ACTIVITY = 3,
पूर्ण;

/* reg_ratr_op
 * Note that Write operation may also be used क्रम updating
 * counter_set_type and counter_index. In this हाल all other
 * fields must not be updated.
 * Access: OP
 */
MLXSW_ITEM32(reg, ratr, op, 0x00, 28, 4);

/* reg_ratr_v
 * Valid bit. Indicates अगर the adjacency entry is valid.
 * Note: the device may need some समय beक्रमe reusing an invalidated
 * entry. During this समय the entry can not be reused. It is
 * recommended to use another entry beक्रमe reusing an invalidated
 * entry (e.g. software can put it at the end of the list क्रम
 * reusing). Trying to access an invalidated entry not yet cleared
 * by the device results with failure indicating "Try Again" status.
 * When valid is '0' then egress_router_पूर्णांकerface,trap_action,
 * adjacency_parameters and counters are reserved
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, v, 0x00, 24, 1);

/* reg_ratr_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on
 * the specअगरic entry. To clear the a bit, use "clear activity".
 * Access: RO
 */
MLXSW_ITEM32(reg, ratr, a, 0x00, 16, 1);

क्रमागत mlxsw_reg_ratr_type अणु
	/* Ethernet */
	MLXSW_REG_RATR_TYPE_ETHERNET,
	/* IPoIB Unicast without GRH.
	 * Reserved क्रम Spectrum.
	 */
	MLXSW_REG_RATR_TYPE_IPOIB_UC,
	/* IPoIB Unicast with GRH. Supported only in table 0 (Ethernet unicast
	 * adjacency).
	 * Reserved क्रम Spectrum.
	 */
	MLXSW_REG_RATR_TYPE_IPOIB_UC_W_GRH,
	/* IPoIB Multicast.
	 * Reserved क्रम Spectrum.
	 */
	MLXSW_REG_RATR_TYPE_IPOIB_MC,
	/* MPLS.
	 * Reserved क्रम SwitchX/-2.
	 */
	MLXSW_REG_RATR_TYPE_MPLS,
	/* IPinIP Encap.
	 * Reserved क्रम SwitchX/-2.
	 */
	MLXSW_REG_RATR_TYPE_IPIP,
पूर्ण;

/* reg_ratr_type
 * Adjacency entry type.
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, type, 0x04, 28, 4);

/* reg_ratr_adjacency_index_low
 * Bits 15:0 of index पूर्णांकo the adjacency table.
 * For SwitchX and SwitchX-2, the adjacency table is linear and
 * used क्रम adjacency entries only.
 * For Spectrum, the index is to the KVD linear.
 * Access: Index
 */
MLXSW_ITEM32(reg, ratr, adjacency_index_low, 0x04, 0, 16);

/* reg_ratr_egress_router_पूर्णांकerface
 * Range is 0 .. cap_max_router_पूर्णांकerfaces - 1
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, egress_router_पूर्णांकerface, 0x08, 0, 16);

क्रमागत mlxsw_reg_ratr_trap_action अणु
	MLXSW_REG_RATR_TRAP_ACTION_NOP,
	MLXSW_REG_RATR_TRAP_ACTION_TRAP,
	MLXSW_REG_RATR_TRAP_ACTION_MIRROR_TO_CPU,
	MLXSW_REG_RATR_TRAP_ACTION_MIRROR,
	MLXSW_REG_RATR_TRAP_ACTION_DISCARD_ERRORS,
पूर्ण;

/* reg_ratr_trap_action
 * see mlxsw_reg_ratr_trap_action
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, trap_action, 0x0C, 28, 4);

/* reg_ratr_adjacency_index_high
 * Bits 23:16 of the adjacency_index.
 * Access: Index
 */
MLXSW_ITEM32(reg, ratr, adjacency_index_high, 0x0C, 16, 8);

क्रमागत mlxsw_reg_ratr_trap_id अणु
	MLXSW_REG_RATR_TRAP_ID_RTR_EGRESS0,
	MLXSW_REG_RATR_TRAP_ID_RTR_EGRESS1,
पूर्ण;

/* reg_ratr_trap_id
 * Trap ID to be reported to CPU.
 * Trap-ID is RTR_EGRESS0 or RTR_EGRESS1.
 * For trap_action of NOP, MIRROR and DISCARD_ERROR
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, trap_id, 0x0C, 0, 8);

/* reg_ratr_eth_destination_mac
 * MAC address of the destination next-hop.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, ratr, eth_destination_mac, 0x12, 6);

क्रमागत mlxsw_reg_ratr_ipip_type अणु
	/* IPv4, address set by mlxsw_reg_ratr_ipip_ipv4_udip. */
	MLXSW_REG_RATR_IPIP_TYPE_IPV4,
	/* IPv6, address set by mlxsw_reg_ratr_ipip_ipv6_ptr. */
	MLXSW_REG_RATR_IPIP_TYPE_IPV6,
पूर्ण;

/* reg_ratr_ipip_type
 * Underlay destination ip type.
 * Note: the type field must match the protocol of the router पूर्णांकerface.
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, ipip_type, 0x10, 16, 4);

/* reg_ratr_ipip_ipv4_udip
 * Underlay ipv4 dip.
 * Reserved when ipip_type is IPv6.
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, ipip_ipv4_udip, 0x18, 0, 32);

/* reg_ratr_ipip_ipv6_ptr
 * Poपूर्णांकer to IPv6 underlay destination ip address.
 * For Spectrum: Poपूर्णांकer to KVD linear space.
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, ipip_ipv6_ptr, 0x1C, 0, 24);

क्रमागत mlxsw_reg_flow_counter_set_type अणु
	/* No count */
	MLXSW_REG_FLOW_COUNTER_SET_TYPE_NO_COUNT = 0x00,
	/* Count packets and bytes */
	MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES = 0x03,
	/* Count only packets */
	MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS = 0x05,
पूर्ण;

/* reg_ratr_counter_set_type
 * Counter set type क्रम flow counters
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, counter_set_type, 0x28, 24, 8);

/* reg_ratr_counter_index
 * Counter index क्रम flow counters
 * Access: RW
 */
MLXSW_ITEM32(reg, ratr, counter_index, 0x28, 0, 24);

अटल अंतरभूत व्योम
mlxsw_reg_ratr_pack(अक्षर *payload,
		    क्रमागत mlxsw_reg_ratr_op op, bool valid,
		    क्रमागत mlxsw_reg_ratr_type type,
		    u32 adjacency_index, u16 egress_rअगर)
अणु
	MLXSW_REG_ZERO(ratr, payload);
	mlxsw_reg_ratr_op_set(payload, op);
	mlxsw_reg_ratr_v_set(payload, valid);
	mlxsw_reg_ratr_type_set(payload, type);
	mlxsw_reg_ratr_adjacency_index_low_set(payload, adjacency_index);
	mlxsw_reg_ratr_adjacency_index_high_set(payload, adjacency_index >> 16);
	mlxsw_reg_ratr_egress_router_पूर्णांकerface_set(payload, egress_rअगर);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ratr_eth_entry_pack(अक्षर *payload,
						 स्थिर अक्षर *dest_mac)
अणु
	mlxsw_reg_ratr_eth_destination_mac_स_नकल_to(payload, dest_mac);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ratr_ipip4_entry_pack(अक्षर *payload, u32 ipv4_udip)
अणु
	mlxsw_reg_ratr_ipip_type_set(payload, MLXSW_REG_RATR_IPIP_TYPE_IPV4);
	mlxsw_reg_ratr_ipip_ipv4_udip_set(payload, ipv4_udip);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ratr_counter_pack(अक्षर *payload, u64 counter_index,
					       bool counter_enable)
अणु
	क्रमागत mlxsw_reg_flow_counter_set_type set_type;

	अगर (counter_enable)
		set_type = MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES;
	अन्यथा
		set_type = MLXSW_REG_FLOW_COUNTER_SET_TYPE_NO_COUNT;

	mlxsw_reg_ratr_counter_index_set(payload, counter_index);
	mlxsw_reg_ratr_counter_set_type_set(payload, set_type);
पूर्ण

/* RDPM - Router DSCP to Priority Mapping
 * --------------------------------------
 * Controls the mapping from DSCP field to चयन priority on routed packets
 */
#घोषणा MLXSW_REG_RDPM_ID 0x8009
#घोषणा MLXSW_REG_RDPM_BASE_LEN 0x00
#घोषणा MLXSW_REG_RDPM_DSCP_ENTRY_REC_LEN 0x01
#घोषणा MLXSW_REG_RDPM_DSCP_ENTRY_REC_MAX_COUNT 64
#घोषणा MLXSW_REG_RDPM_LEN 0x40
#घोषणा MLXSW_REG_RDPM_LAST_ENTRY (MLXSW_REG_RDPM_BASE_LEN + \
				   MLXSW_REG_RDPM_LEN - \
				   MLXSW_REG_RDPM_DSCP_ENTRY_REC_LEN)

MLXSW_REG_DEFINE(rdpm, MLXSW_REG_RDPM_ID, MLXSW_REG_RDPM_LEN);

/* reg_dscp_entry_e
 * Enable update of the specअगरic entry
 * Access: Index
 */
MLXSW_ITEM8_INDEXED(reg, rdpm, dscp_entry_e, MLXSW_REG_RDPM_LAST_ENTRY, 7, 1,
		    -MLXSW_REG_RDPM_DSCP_ENTRY_REC_LEN, 0x00, false);

/* reg_dscp_entry_prio
 * Switch Priority
 * Access: RW
 */
MLXSW_ITEM8_INDEXED(reg, rdpm, dscp_entry_prio, MLXSW_REG_RDPM_LAST_ENTRY, 0, 4,
		    -MLXSW_REG_RDPM_DSCP_ENTRY_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_rdpm_pack(अक्षर *payload, अचिन्हित लघु index,
				       u8 prio)
अणु
	mlxsw_reg_rdpm_dscp_entry_e_set(payload, index, 1);
	mlxsw_reg_rdpm_dscp_entry_prio_set(payload, index, prio);
पूर्ण

/* RICNT - Router Interface Counter Register
 * -----------------------------------------
 * The RICNT रेजिस्टर retrieves per port perक्रमmance counters
 */
#घोषणा MLXSW_REG_RICNT_ID 0x800B
#घोषणा MLXSW_REG_RICNT_LEN 0x100

MLXSW_REG_DEFINE(ricnt, MLXSW_REG_RICNT_ID, MLXSW_REG_RICNT_LEN);

/* reg_ricnt_counter_index
 * Counter index
 * Access: RW
 */
MLXSW_ITEM32(reg, ricnt, counter_index, 0x04, 0, 24);

क्रमागत mlxsw_reg_ricnt_counter_set_type अणु
	/* No Count. */
	MLXSW_REG_RICNT_COUNTER_SET_TYPE_NO_COUNT = 0x00,
	/* Basic. Used क्रम router पूर्णांकerfaces, counting the following:
	 *	- Error and Discard counters.
	 *	- Unicast, Multicast and Broadcast counters. Sharing the
	 *	  same set of counters क्रम the dअगरferent type of traffic
	 *	  (IPv4, IPv6 and mpls).
	 */
	MLXSW_REG_RICNT_COUNTER_SET_TYPE_BASIC = 0x09,
पूर्ण;

/* reg_ricnt_counter_set_type
 * Counter Set Type क्रम router पूर्णांकerface counter
 * Access: RW
 */
MLXSW_ITEM32(reg, ricnt, counter_set_type, 0x04, 24, 8);

क्रमागत mlxsw_reg_ricnt_opcode अणु
	/* Nop. Supported only क्रम पढ़ो access*/
	MLXSW_REG_RICNT_OPCODE_NOP = 0x00,
	/* Clear. Setting the clr bit will reset the counter value क्रम
	 * all counters of the specअगरied Router Interface.
	 */
	MLXSW_REG_RICNT_OPCODE_CLEAR = 0x08,
पूर्ण;

/* reg_ricnt_opcode
 * Opcode
 * Access: RW
 */
MLXSW_ITEM32(reg, ricnt, op, 0x00, 28, 4);

/* reg_ricnt_good_unicast_packets
 * good unicast packets.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_unicast_packets, 0x08, 0, 64);

/* reg_ricnt_good_multicast_packets
 * good multicast packets.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_multicast_packets, 0x10, 0, 64);

/* reg_ricnt_good_broadcast_packets
 * good broadcast packets
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_broadcast_packets, 0x18, 0, 64);

/* reg_ricnt_good_unicast_bytes
 * A count of L3 data and padding octets not including L2 headers
 * क्रम good unicast frames.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_unicast_bytes, 0x20, 0, 64);

/* reg_ricnt_good_multicast_bytes
 * A count of L3 data and padding octets not including L2 headers
 * क्रम good multicast frames.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_multicast_bytes, 0x28, 0, 64);

/* reg_ritr_good_broadcast_bytes
 * A count of L3 data and padding octets not including L2 headers
 * क्रम good broadcast frames.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, good_broadcast_bytes, 0x30, 0, 64);

/* reg_ricnt_error_packets
 * A count of errored frames that करो not pass the router checks.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, error_packets, 0x38, 0, 64);

/* reg_ricnt_discrad_packets
 * A count of non-errored frames that करो not pass the router checks.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, discard_packets, 0x40, 0, 64);

/* reg_ricnt_error_bytes
 * A count of L3 data and padding octets not including L2 headers
 * क्रम errored frames.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, error_bytes, 0x48, 0, 64);

/* reg_ricnt_discard_bytes
 * A count of L3 data and padding octets not including L2 headers
 * क्रम non-errored frames that करो not pass the router checks.
 * Access: RW
 */
MLXSW_ITEM64(reg, ricnt, discard_bytes, 0x50, 0, 64);

अटल अंतरभूत व्योम mlxsw_reg_ricnt_pack(अक्षर *payload, u32 index,
					क्रमागत mlxsw_reg_ricnt_opcode op)
अणु
	MLXSW_REG_ZERO(ricnt, payload);
	mlxsw_reg_ricnt_op_set(payload, op);
	mlxsw_reg_ricnt_counter_index_set(payload, index);
	mlxsw_reg_ricnt_counter_set_type_set(payload,
					     MLXSW_REG_RICNT_COUNTER_SET_TYPE_BASIC);
पूर्ण

/* RRCR - Router Rules Copy Register Layout
 * ----------------------------------------
 * This रेजिस्टर is used क्रम moving and copying route entry rules.
 */
#घोषणा MLXSW_REG_RRCR_ID 0x800F
#घोषणा MLXSW_REG_RRCR_LEN 0x24

MLXSW_REG_DEFINE(rrcr, MLXSW_REG_RRCR_ID, MLXSW_REG_RRCR_LEN);

क्रमागत mlxsw_reg_rrcr_op अणु
	/* Move rules */
	MLXSW_REG_RRCR_OP_MOVE,
	/* Copy rules */
	MLXSW_REG_RRCR_OP_COPY,
पूर्ण;

/* reg_rrcr_op
 * Access: WO
 */
MLXSW_ITEM32(reg, rrcr, op, 0x00, 28, 4);

/* reg_rrcr_offset
 * Offset within the region from which to copy/move.
 * Access: Index
 */
MLXSW_ITEM32(reg, rrcr, offset, 0x00, 0, 16);

/* reg_rrcr_size
 * The number of rules to copy/move.
 * Access: WO
 */
MLXSW_ITEM32(reg, rrcr, size, 0x04, 0, 16);

/* reg_rrcr_table_id
 * Identअगरier of the table on which to perक्रमm the operation. Encoding is the
 * same as in RTAR.key_type
 * Access: Index
 */
MLXSW_ITEM32(reg, rrcr, table_id, 0x10, 0, 4);

/* reg_rrcr_dest_offset
 * Offset within the region to which to copy/move
 * Access: Index
 */
MLXSW_ITEM32(reg, rrcr, dest_offset, 0x20, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_rrcr_pack(अक्षर *payload, क्रमागत mlxsw_reg_rrcr_op op,
				       u16 offset, u16 size,
				       क्रमागत mlxsw_reg_rtar_key_type table_id,
				       u16 dest_offset)
अणु
	MLXSW_REG_ZERO(rrcr, payload);
	mlxsw_reg_rrcr_op_set(payload, op);
	mlxsw_reg_rrcr_offset_set(payload, offset);
	mlxsw_reg_rrcr_size_set(payload, size);
	mlxsw_reg_rrcr_table_id_set(payload, table_id);
	mlxsw_reg_rrcr_dest_offset_set(payload, dest_offset);
पूर्ण

/* RALTA - Router Algorithmic LPM Tree Allocation Register
 * -------------------------------------------------------
 * RALTA is used to allocate the LPM trees of the SHSPM method.
 */
#घोषणा MLXSW_REG_RALTA_ID 0x8010
#घोषणा MLXSW_REG_RALTA_LEN 0x04

MLXSW_REG_DEFINE(ralta, MLXSW_REG_RALTA_ID, MLXSW_REG_RALTA_LEN);

/* reg_ralta_op
 * opcode (valid क्रम Write, must be 0 on Read)
 * 0 - allocate a tree
 * 1 - deallocate a tree
 * Access: OP
 */
MLXSW_ITEM32(reg, ralta, op, 0x00, 28, 2);

क्रमागत mlxsw_reg_ralxx_protocol अणु
	MLXSW_REG_RALXX_PROTOCOL_IPV4,
	MLXSW_REG_RALXX_PROTOCOL_IPV6,
पूर्ण;

/* reg_ralta_protocol
 * Protocol.
 * Deallocation opcode: Reserved.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralta, protocol, 0x00, 24, 4);

/* reg_ralta_tree_id
 * An identअगरier (numbered from 1..cap_shspm_max_trees-1) representing
 * the tree identअगरier (managed by software).
 * Note that tree_id 0 is allocated क्रम a शेष-route tree.
 * Access: Index
 */
MLXSW_ITEM32(reg, ralta, tree_id, 0x00, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_ralta_pack(अक्षर *payload, bool alloc,
					क्रमागत mlxsw_reg_ralxx_protocol protocol,
					u8 tree_id)
अणु
	MLXSW_REG_ZERO(ralta, payload);
	mlxsw_reg_ralta_op_set(payload, !alloc);
	mlxsw_reg_ralta_protocol_set(payload, protocol);
	mlxsw_reg_ralta_tree_id_set(payload, tree_id);
पूर्ण

/* RALST - Router Algorithmic LPM Structure Tree Register
 * ------------------------------------------------------
 * RALST is used to set and query the काष्ठाure of an LPM tree.
 * The काष्ठाure of the tree must be sorted as a sorted binary tree, जबतक
 * each node is a bin that is tagged as the length of the prefixes the lookup
 * will refer to. Thereक्रमe, bin X refers to a set of entries with prefixes
 * of X bits to match with the destination address. The bin 0 indicates
 * the शेष action, when there is no match of any prefix.
 */
#घोषणा MLXSW_REG_RALST_ID 0x8011
#घोषणा MLXSW_REG_RALST_LEN 0x104

MLXSW_REG_DEFINE(ralst, MLXSW_REG_RALST_ID, MLXSW_REG_RALST_LEN);

/* reg_ralst_root_bin
 * The bin number of the root bin.
 * 0<root_bin=<(length of IP address)
 * For a शेष-route tree configure 0xff
 * Access: RW
 */
MLXSW_ITEM32(reg, ralst, root_bin, 0x00, 16, 8);

/* reg_ralst_tree_id
 * Tree identअगरier numbered from 1..(cap_shspm_max_trees-1).
 * Access: Index
 */
MLXSW_ITEM32(reg, ralst, tree_id, 0x00, 0, 8);

#घोषणा MLXSW_REG_RALST_BIN_NO_CHILD 0xff
#घोषणा MLXSW_REG_RALST_BIN_OFFSET 0x04
#घोषणा MLXSW_REG_RALST_BIN_COUNT 128

/* reg_ralst_left_child_bin
 * Holding the children of the bin according to the stored tree's काष्ठाure.
 * For trees composed of less than 4 blocks, the bins in excess are reserved.
 * Note that tree_id 0 is allocated क्रम a शेष-route tree, bins are 0xff
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ralst, left_child_bin, 0x04, 8, 8, 0x02, 0x00, false);

/* reg_ralst_right_child_bin
 * Holding the children of the bin according to the stored tree's काष्ठाure.
 * For trees composed of less than 4 blocks, the bins in excess are reserved.
 * Note that tree_id 0 is allocated क्रम a शेष-route tree, bins are 0xff
 * Access: RW
 */
MLXSW_ITEM16_INDEXED(reg, ralst, right_child_bin, 0x04, 0, 8, 0x02, 0x00,
		     false);

अटल अंतरभूत व्योम mlxsw_reg_ralst_pack(अक्षर *payload, u8 root_bin, u8 tree_id)
अणु
	MLXSW_REG_ZERO(ralst, payload);

	/* Initialize all bins to have no left or right child */
	स_रखो(payload + MLXSW_REG_RALST_BIN_OFFSET,
	       MLXSW_REG_RALST_BIN_NO_CHILD, MLXSW_REG_RALST_BIN_COUNT * 2);

	mlxsw_reg_ralst_root_bin_set(payload, root_bin);
	mlxsw_reg_ralst_tree_id_set(payload, tree_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ralst_bin_pack(अक्षर *payload, u8 bin_number,
					    u8 left_child_bin,
					    u8 right_child_bin)
अणु
	पूर्णांक bin_index = bin_number - 1;

	mlxsw_reg_ralst_left_child_bin_set(payload, bin_index, left_child_bin);
	mlxsw_reg_ralst_right_child_bin_set(payload, bin_index,
					    right_child_bin);
पूर्ण

/* RALTB - Router Algorithmic LPM Tree Binding Register
 * ----------------------------------------------------
 * RALTB is used to bind भव router and protocol to an allocated LPM tree.
 */
#घोषणा MLXSW_REG_RALTB_ID 0x8012
#घोषणा MLXSW_REG_RALTB_LEN 0x04

MLXSW_REG_DEFINE(raltb, MLXSW_REG_RALTB_ID, MLXSW_REG_RALTB_LEN);

/* reg_raltb_भव_router
 * Virtual Router ID
 * Range is 0..cap_max_भव_routers-1
 * Access: Index
 */
MLXSW_ITEM32(reg, raltb, भव_router, 0x00, 16, 16);

/* reg_raltb_protocol
 * Protocol.
 * Access: Index
 */
MLXSW_ITEM32(reg, raltb, protocol, 0x00, 12, 4);

/* reg_raltb_tree_id
 * Tree to be used क्रम the अणुभव_router, protocolपूर्ण
 * Tree identअगरier numbered from 1..(cap_shspm_max_trees-1).
 * By शेष, all Unicast IPv4 and IPv6 are bound to tree_id 0.
 * Access: RW
 */
MLXSW_ITEM32(reg, raltb, tree_id, 0x00, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_raltb_pack(अक्षर *payload, u16 भव_router,
					क्रमागत mlxsw_reg_ralxx_protocol protocol,
					u8 tree_id)
अणु
	MLXSW_REG_ZERO(raltb, payload);
	mlxsw_reg_raltb_भव_router_set(payload, भव_router);
	mlxsw_reg_raltb_protocol_set(payload, protocol);
	mlxsw_reg_raltb_tree_id_set(payload, tree_id);
पूर्ण

/* RALUE - Router Algorithmic LPM Unicast Entry Register
 * -----------------------------------------------------
 * RALUE is used to configure and query LPM entries that serve
 * the Unicast protocols.
 */
#घोषणा MLXSW_REG_RALUE_ID 0x8013
#घोषणा MLXSW_REG_RALUE_LEN 0x38

MLXSW_REG_DEFINE(ralue, MLXSW_REG_RALUE_ID, MLXSW_REG_RALUE_LEN);

/* reg_ralue_protocol
 * Protocol.
 * Access: Index
 */
MLXSW_ITEM32(reg, ralue, protocol, 0x00, 24, 4);

क्रमागत mlxsw_reg_ralue_op अणु
	/* Read operation. If entry करोesn't exist, the operation fails. */
	MLXSW_REG_RALUE_OP_QUERY_READ = 0,
	/* Clear on पढ़ो operation. Used to पढ़ो entry and
	 * clear Activity bit.
	 */
	MLXSW_REG_RALUE_OP_QUERY_CLEAR = 1,
	/* Write operation. Used to ग_लिखो a new entry to the table. All RW
	 * fields are written क्रम new entry. Activity bit is set
	 * क्रम new entries.
	 */
	MLXSW_REG_RALUE_OP_WRITE_WRITE = 0,
	/* Update operation. Used to update an existing route entry and
	 * only update the RW fields that are detailed in the field
	 * op_u_mask. If entry करोesn't exist, the operation fails.
	 */
	MLXSW_REG_RALUE_OP_WRITE_UPDATE = 1,
	/* Clear activity. The Activity bit (the field a) is cleared
	 * क्रम the entry.
	 */
	MLXSW_REG_RALUE_OP_WRITE_CLEAR = 2,
	/* Delete operation. Used to delete an existing entry. If entry
	 * करोesn't exist, the operation fails.
	 */
	MLXSW_REG_RALUE_OP_WRITE_DELETE = 3,
पूर्ण;

/* reg_ralue_op
 * Operation.
 * Access: OP
 */
MLXSW_ITEM32(reg, ralue, op, 0x00, 20, 3);

/* reg_ralue_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on the
 * specअगरic entry, only अगर the entry is a route. To clear the a bit, use
 * "clear activity" op.
 * Enabled by activity_dis in RGCR
 * Access: RO
 */
MLXSW_ITEM32(reg, ralue, a, 0x00, 16, 1);

/* reg_ralue_भव_router
 * Virtual Router ID
 * Range is 0..cap_max_भव_routers-1
 * Access: Index
 */
MLXSW_ITEM32(reg, ralue, भव_router, 0x04, 16, 16);

#घोषणा MLXSW_REG_RALUE_OP_U_MASK_ENTRY_TYPE	BIT(0)
#घोषणा MLXSW_REG_RALUE_OP_U_MASK_BMP_LEN	BIT(1)
#घोषणा MLXSW_REG_RALUE_OP_U_MASK_ACTION	BIT(2)

/* reg_ralue_op_u_mask
 * opcode update mask.
 * On पढ़ो operation, this field is reserved.
 * This field is valid क्रम update opcode, otherwise - reserved.
 * This field is a biपंचांगask of the fields that should be updated.
 * Access: WO
 */
MLXSW_ITEM32(reg, ralue, op_u_mask, 0x04, 8, 3);

/* reg_ralue_prefix_len
 * Number of bits in the prefix of the LPM route.
 * Note that क्रम IPv6 prefixes, अगर prefix_len>64 the entry consumes
 * two entries in the physical HW table.
 * Access: Index
 */
MLXSW_ITEM32(reg, ralue, prefix_len, 0x08, 0, 8);

/* reg_ralue_dip*
 * The prefix of the route or of the marker that the object of the LPM
 * is compared with. The most signअगरicant bits of the dip are the prefix.
 * The least signअगरicant bits must be '0' अगर the prefix_len is smaller
 * than 128 क्रम IPv6 or smaller than 32 क्रम IPv4.
 * IPv4 address uses bits dip[31:0] and bits dip[127:32] are reserved.
 * Access: Index
 */
MLXSW_ITEM32(reg, ralue, dip4, 0x18, 0, 32);
MLXSW_ITEM_BUF(reg, ralue, dip6, 0x0C, 16);

क्रमागत mlxsw_reg_ralue_entry_type अणु
	MLXSW_REG_RALUE_ENTRY_TYPE_MARKER_ENTRY = 1,
	MLXSW_REG_RALUE_ENTRY_TYPE_ROUTE_ENTRY = 2,
	MLXSW_REG_RALUE_ENTRY_TYPE_MARKER_AND_ROUTE_ENTRY = 3,
पूर्ण;

/* reg_ralue_entry_type
 * Entry type.
 * Note - क्रम Marker entries, the action_type and action fields are reserved.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, entry_type, 0x1C, 30, 2);

/* reg_ralue_bmp_len
 * The best match prefix length in the हाल that there is no match क्रम
 * दीर्घer prefixes.
 * If (entry_type != MARKER_ENTRY), bmp_len must be equal to prefix_len
 * Note क्रम any update operation with entry_type modअगरication this
 * field must be set.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, bmp_len, 0x1C, 16, 8);

क्रमागत mlxsw_reg_ralue_action_type अणु
	MLXSW_REG_RALUE_ACTION_TYPE_REMOTE,
	MLXSW_REG_RALUE_ACTION_TYPE_LOCAL,
	MLXSW_REG_RALUE_ACTION_TYPE_IP2ME,
पूर्ण;

/* reg_ralue_action_type
 * Action Type
 * Indicates how the IP address is connected.
 * It can be connected to a local subnet through local_erअगर or can be
 * on a remote subnet connected through a next-hop router,
 * or transmitted to the CPU.
 * Reserved when entry_type = MARKER_ENTRY
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, action_type, 0x1C, 0, 2);

क्रमागत mlxsw_reg_ralue_trap_action अणु
	MLXSW_REG_RALUE_TRAP_ACTION_NOP,
	MLXSW_REG_RALUE_TRAP_ACTION_TRAP,
	MLXSW_REG_RALUE_TRAP_ACTION_MIRROR_TO_CPU,
	MLXSW_REG_RALUE_TRAP_ACTION_MIRROR,
	MLXSW_REG_RALUE_TRAP_ACTION_DISCARD_ERROR,
पूर्ण;

/* reg_ralue_trap_action
 * Trap action.
 * For IP2ME action, only NOP and MIRROR are possible.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, trap_action, 0x20, 28, 4);

/* reg_ralue_trap_id
 * Trap ID to be reported to CPU.
 * Trap ID is RTR_INGRESS0 or RTR_INGRESS1.
 * For trap_action of NOP, MIRROR and DISCARD_ERROR, trap_id is reserved.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, trap_id, 0x20, 0, 9);

/* reg_ralue_adjacency_index
 * Poपूर्णांकs to the first entry of the group-based ECMP.
 * Only relevant in हाल of REMOTE action.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, adjacency_index, 0x24, 0, 24);

/* reg_ralue_ecmp_size
 * Amount of sequential entries starting
 * from the adjacency_index (the number of ECMPs).
 * The valid range is 1-64, 512, 1024, 2048 and 4096.
 * Reserved when trap_action is TRAP or DISCARD_ERROR.
 * Only relevant in हाल of REMOTE action.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, ecmp_size, 0x28, 0, 13);

/* reg_ralue_local_erअगर
 * Egress Router Interface.
 * Only relevant in हाल of LOCAL action.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, local_erअगर, 0x24, 0, 16);

/* reg_ralue_ip2me_v
 * Valid bit क्रम the tunnel_ptr field.
 * If valid = 0 then trap to CPU as IP2ME trap ID.
 * If valid = 1 and the packet क्रमmat allows NVE or IPinIP tunnel
 * decapsulation then tunnel decapsulation is करोne.
 * If valid = 1 and packet क्रमmat करोes not allow NVE or IPinIP tunnel
 * decapsulation then trap as IP2ME trap ID.
 * Only relevant in हाल of IP2ME action.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, ip2me_v, 0x24, 31, 1);

/* reg_ralue_ip2me_tunnel_ptr
 * Tunnel Poपूर्णांकer क्रम NVE or IPinIP tunnel decapsulation.
 * For Spectrum, poपूर्णांकer to KVD Linear.
 * Only relevant in हाल of IP2ME action.
 * Access: RW
 */
MLXSW_ITEM32(reg, ralue, ip2me_tunnel_ptr, 0x24, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_ralue_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_ralxx_protocol protocol,
					क्रमागत mlxsw_reg_ralue_op op,
					u16 भव_router, u8 prefix_len)
अणु
	MLXSW_REG_ZERO(ralue, payload);
	mlxsw_reg_ralue_protocol_set(payload, protocol);
	mlxsw_reg_ralue_op_set(payload, op);
	mlxsw_reg_ralue_भव_router_set(payload, भव_router);
	mlxsw_reg_ralue_prefix_len_set(payload, prefix_len);
	mlxsw_reg_ralue_entry_type_set(payload,
				       MLXSW_REG_RALUE_ENTRY_TYPE_ROUTE_ENTRY);
	mlxsw_reg_ralue_bmp_len_set(payload, prefix_len);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ralue_pack4(अक्षर *payload,
					 क्रमागत mlxsw_reg_ralxx_protocol protocol,
					 क्रमागत mlxsw_reg_ralue_op op,
					 u16 भव_router, u8 prefix_len,
					 u32 *dip)
अणु
	mlxsw_reg_ralue_pack(payload, protocol, op, भव_router, prefix_len);
	अगर (dip)
		mlxsw_reg_ralue_dip4_set(payload, *dip);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_ralue_pack6(अक्षर *payload,
					 क्रमागत mlxsw_reg_ralxx_protocol protocol,
					 क्रमागत mlxsw_reg_ralue_op op,
					 u16 भव_router, u8 prefix_len,
					 स्थिर व्योम *dip)
अणु
	mlxsw_reg_ralue_pack(payload, protocol, op, भव_router, prefix_len);
	अगर (dip)
		mlxsw_reg_ralue_dip6_स_नकल_to(payload, dip);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ralue_act_remote_pack(अक्षर *payload,
				क्रमागत mlxsw_reg_ralue_trap_action trap_action,
				u16 trap_id, u32 adjacency_index, u16 ecmp_size)
अणु
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_REMOTE);
	mlxsw_reg_ralue_trap_action_set(payload, trap_action);
	mlxsw_reg_ralue_trap_id_set(payload, trap_id);
	mlxsw_reg_ralue_adjacency_index_set(payload, adjacency_index);
	mlxsw_reg_ralue_ecmp_size_set(payload, ecmp_size);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ralue_act_local_pack(अक्षर *payload,
			       क्रमागत mlxsw_reg_ralue_trap_action trap_action,
			       u16 trap_id, u16 local_erअगर)
अणु
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_LOCAL);
	mlxsw_reg_ralue_trap_action_set(payload, trap_action);
	mlxsw_reg_ralue_trap_id_set(payload, trap_id);
	mlxsw_reg_ralue_local_erअगर_set(payload, local_erअगर);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ralue_act_ip2me_pack(अक्षर *payload)
अणु
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_IP2ME);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_ralue_act_ip2me_tun_pack(अक्षर *payload, u32 tunnel_ptr)
अणु
	mlxsw_reg_ralue_action_type_set(payload,
					MLXSW_REG_RALUE_ACTION_TYPE_IP2ME);
	mlxsw_reg_ralue_ip2me_v_set(payload, 1);
	mlxsw_reg_ralue_ip2me_tunnel_ptr_set(payload, tunnel_ptr);
पूर्ण

/* RAUHT - Router Algorithmic LPM Unicast Host Table Register
 * ----------------------------------------------------------
 * The RAUHT रेजिस्टर is used to configure and query the Unicast Host table in
 * devices that implement the Algorithmic LPM.
 */
#घोषणा MLXSW_REG_RAUHT_ID 0x8014
#घोषणा MLXSW_REG_RAUHT_LEN 0x74

MLXSW_REG_DEFINE(rauht, MLXSW_REG_RAUHT_ID, MLXSW_REG_RAUHT_LEN);

क्रमागत mlxsw_reg_rauht_type अणु
	MLXSW_REG_RAUHT_TYPE_IPV4,
	MLXSW_REG_RAUHT_TYPE_IPV6,
पूर्ण;

/* reg_rauht_type
 * Access: Index
 */
MLXSW_ITEM32(reg, rauht, type, 0x00, 24, 2);

क्रमागत mlxsw_reg_rauht_op अणु
	MLXSW_REG_RAUHT_OP_QUERY_READ = 0,
	/* Read operation */
	MLXSW_REG_RAUHT_OP_QUERY_CLEAR_ON_READ = 1,
	/* Clear on पढ़ो operation. Used to पढ़ो entry and clear
	 * activity bit.
	 */
	MLXSW_REG_RAUHT_OP_WRITE_ADD = 0,
	/* Add. Used to ग_लिखो a new entry to the table. All R/W fields are
	 * relevant क्रम new entry. Activity bit is set क्रम new entries.
	 */
	MLXSW_REG_RAUHT_OP_WRITE_UPDATE = 1,
	/* Update action. Used to update an existing route entry and
	 * only update the following fields:
	 * trap_action, trap_id, mac, counter_set_type, counter_index
	 */
	MLXSW_REG_RAUHT_OP_WRITE_CLEAR_ACTIVITY = 2,
	/* Clear activity. A bit is cleared क्रम the entry. */
	MLXSW_REG_RAUHT_OP_WRITE_DELETE = 3,
	/* Delete entry */
	MLXSW_REG_RAUHT_OP_WRITE_DELETE_ALL = 4,
	/* Delete all host entries on a RIF. In this command, dip
	 * field is reserved.
	 */
पूर्ण;

/* reg_rauht_op
 * Access: OP
 */
MLXSW_ITEM32(reg, rauht, op, 0x00, 20, 3);

/* reg_rauht_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on
 * the specअगरic entry.
 * To clear the a bit, use "clear activity" op.
 * Enabled by activity_dis in RGCR
 * Access: RO
 */
MLXSW_ITEM32(reg, rauht, a, 0x00, 16, 1);

/* reg_rauht_rअगर
 * Router Interface
 * Access: Index
 */
MLXSW_ITEM32(reg, rauht, rअगर, 0x00, 0, 16);

/* reg_rauht_dip*
 * Destination address.
 * Access: Index
 */
MLXSW_ITEM32(reg, rauht, dip4, 0x1C, 0x0, 32);
MLXSW_ITEM_BUF(reg, rauht, dip6, 0x10, 16);

क्रमागत mlxsw_reg_rauht_trap_action अणु
	MLXSW_REG_RAUHT_TRAP_ACTION_NOP,
	MLXSW_REG_RAUHT_TRAP_ACTION_TRAP,
	MLXSW_REG_RAUHT_TRAP_ACTION_MIRROR_TO_CPU,
	MLXSW_REG_RAUHT_TRAP_ACTION_MIRROR,
	MLXSW_REG_RAUHT_TRAP_ACTION_DISCARD_ERRORS,
पूर्ण;

/* reg_rauht_trap_action
 * Access: RW
 */
MLXSW_ITEM32(reg, rauht, trap_action, 0x60, 28, 4);

क्रमागत mlxsw_reg_rauht_trap_id अणु
	MLXSW_REG_RAUHT_TRAP_ID_RTR_EGRESS0,
	MLXSW_REG_RAUHT_TRAP_ID_RTR_EGRESS1,
पूर्ण;

/* reg_rauht_trap_id
 * Trap ID to be reported to CPU.
 * Trap-ID is RTR_EGRESS0 or RTR_EGRESS1.
 * For trap_action of NOP, MIRROR and DISCARD_ERROR,
 * trap_id is reserved.
 * Access: RW
 */
MLXSW_ITEM32(reg, rauht, trap_id, 0x60, 0, 9);

/* reg_rauht_counter_set_type
 * Counter set type क्रम flow counters
 * Access: RW
 */
MLXSW_ITEM32(reg, rauht, counter_set_type, 0x68, 24, 8);

/* reg_rauht_counter_index
 * Counter index क्रम flow counters
 * Access: RW
 */
MLXSW_ITEM32(reg, rauht, counter_index, 0x68, 0, 24);

/* reg_rauht_mac
 * MAC address.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rauht, mac, 0x6E, 6);

अटल अंतरभूत व्योम mlxsw_reg_rauht_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_rauht_op op, u16 rअगर,
					स्थिर अक्षर *mac)
अणु
	MLXSW_REG_ZERO(rauht, payload);
	mlxsw_reg_rauht_op_set(payload, op);
	mlxsw_reg_rauht_rअगर_set(payload, rअगर);
	mlxsw_reg_rauht_mac_स_नकल_to(payload, mac);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rauht_pack4(अक्षर *payload,
					 क्रमागत mlxsw_reg_rauht_op op, u16 rअगर,
					 स्थिर अक्षर *mac, u32 dip)
अणु
	mlxsw_reg_rauht_pack(payload, op, rअगर, mac);
	mlxsw_reg_rauht_dip4_set(payload, dip);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rauht_pack6(अक्षर *payload,
					 क्रमागत mlxsw_reg_rauht_op op, u16 rअगर,
					 स्थिर अक्षर *mac, स्थिर अक्षर *dip)
अणु
	mlxsw_reg_rauht_pack(payload, op, rअगर, mac);
	mlxsw_reg_rauht_type_set(payload, MLXSW_REG_RAUHT_TYPE_IPV6);
	mlxsw_reg_rauht_dip6_स_नकल_to(payload, dip);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rauht_pack_counter(अक्षर *payload,
						u64 counter_index)
अणु
	mlxsw_reg_rauht_counter_index_set(payload, counter_index);
	mlxsw_reg_rauht_counter_set_type_set(payload,
					     MLXSW_REG_FLOW_COUNTER_SET_TYPE_PACKETS_BYTES);
पूर्ण

/* RALEU - Router Algorithmic LPM ECMP Update Register
 * ---------------------------------------------------
 * The रेजिस्टर enables updating the ECMP section in the action क्रम multiple
 * LPM Unicast entries in a single operation. The update is executed to
 * all entries of a अणुभव router, protocolपूर्ण tuple using the same ECMP group.
 */
#घोषणा MLXSW_REG_RALEU_ID 0x8015
#घोषणा MLXSW_REG_RALEU_LEN 0x28

MLXSW_REG_DEFINE(raleu, MLXSW_REG_RALEU_ID, MLXSW_REG_RALEU_LEN);

/* reg_raleu_protocol
 * Protocol.
 * Access: Index
 */
MLXSW_ITEM32(reg, raleu, protocol, 0x00, 24, 4);

/* reg_raleu_भव_router
 * Virtual Router ID
 * Range is 0..cap_max_भव_routers-1
 * Access: Index
 */
MLXSW_ITEM32(reg, raleu, भव_router, 0x00, 0, 16);

/* reg_raleu_adjacency_index
 * Adjacency Index used क्रम matching on the existing entries.
 * Access: Index
 */
MLXSW_ITEM32(reg, raleu, adjacency_index, 0x10, 0, 24);

/* reg_raleu_ecmp_size
 * ECMP Size used क्रम matching on the existing entries.
 * Access: Index
 */
MLXSW_ITEM32(reg, raleu, ecmp_size, 0x14, 0, 13);

/* reg_raleu_new_adjacency_index
 * New Adjacency Index.
 * Access: WO
 */
MLXSW_ITEM32(reg, raleu, new_adjacency_index, 0x20, 0, 24);

/* reg_raleu_new_ecmp_size
 * New ECMP Size.
 * Access: WO
 */
MLXSW_ITEM32(reg, raleu, new_ecmp_size, 0x24, 0, 13);

अटल अंतरभूत व्योम mlxsw_reg_raleu_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_ralxx_protocol protocol,
					u16 भव_router,
					u32 adjacency_index, u16 ecmp_size,
					u32 new_adjacency_index,
					u16 new_ecmp_size)
अणु
	MLXSW_REG_ZERO(raleu, payload);
	mlxsw_reg_raleu_protocol_set(payload, protocol);
	mlxsw_reg_raleu_भव_router_set(payload, भव_router);
	mlxsw_reg_raleu_adjacency_index_set(payload, adjacency_index);
	mlxsw_reg_raleu_ecmp_size_set(payload, ecmp_size);
	mlxsw_reg_raleu_new_adjacency_index_set(payload, new_adjacency_index);
	mlxsw_reg_raleu_new_ecmp_size_set(payload, new_ecmp_size);
पूर्ण

/* RAUHTD - Router Algorithmic LPM Unicast Host Table Dump Register
 * ----------------------------------------------------------------
 * The RAUHTD रेजिस्टर allows dumping entries from the Router Unicast Host
 * Table. For a given session an entry is dumped no more than one समय. The
 * first RAUHTD access after reset is a new session. A session ends when the
 * num_rec response is smaller than num_rec request or क्रम IPv4 when the
 * num_entries is smaller than 4. The clear activity affect the current session
 * or the last session अगर a new session has not started.
 */
#घोषणा MLXSW_REG_RAUHTD_ID 0x8018
#घोषणा MLXSW_REG_RAUHTD_BASE_LEN 0x20
#घोषणा MLXSW_REG_RAUHTD_REC_LEN 0x20
#घोषणा MLXSW_REG_RAUHTD_REC_MAX_NUM 32
#घोषणा MLXSW_REG_RAUHTD_LEN (MLXSW_REG_RAUHTD_BASE_LEN + \
		MLXSW_REG_RAUHTD_REC_MAX_NUM * MLXSW_REG_RAUHTD_REC_LEN)
#घोषणा MLXSW_REG_RAUHTD_IPV4_ENT_PER_REC 4

MLXSW_REG_DEFINE(rauhtd, MLXSW_REG_RAUHTD_ID, MLXSW_REG_RAUHTD_LEN);

#घोषणा MLXSW_REG_RAUHTD_FILTER_A BIT(0)
#घोषणा MLXSW_REG_RAUHTD_FILTER_RIF BIT(3)

/* reg_rauhtd_filter_fields
 * अगर a bit is '0' then the relevant field is ignored and dump is करोne
 * regardless of the field value
 * Bit0 - filter by activity: entry_a
 * Bit3 - filter by entry rip: entry_rअगर
 * Access: Index
 */
MLXSW_ITEM32(reg, rauhtd, filter_fields, 0x00, 0, 8);

क्रमागत mlxsw_reg_rauhtd_op अणु
	MLXSW_REG_RAUHTD_OP_DUMP,
	MLXSW_REG_RAUHTD_OP_DUMP_AND_CLEAR,
पूर्ण;

/* reg_rauhtd_op
 * Access: OP
 */
MLXSW_ITEM32(reg, rauhtd, op, 0x04, 24, 2);

/* reg_rauhtd_num_rec
 * At request: number of records requested
 * At response: number of records dumped
 * For IPv4, each record has 4 entries at request and up to 4 entries
 * at response
 * Range is 0..MLXSW_REG_RAUHTD_REC_MAX_NUM
 * Access: Index
 */
MLXSW_ITEM32(reg, rauhtd, num_rec, 0x04, 0, 8);

/* reg_rauhtd_entry_a
 * Dump only अगर activity has value of entry_a
 * Reserved अगर filter_fields bit0 is '0'
 * Access: Index
 */
MLXSW_ITEM32(reg, rauhtd, entry_a, 0x08, 16, 1);

क्रमागत mlxsw_reg_rauhtd_type अणु
	MLXSW_REG_RAUHTD_TYPE_IPV4,
	MLXSW_REG_RAUHTD_TYPE_IPV6,
पूर्ण;

/* reg_rauhtd_type
 * Dump only अगर record type is:
 * 0 - IPv4
 * 1 - IPv6
 * Access: Index
 */
MLXSW_ITEM32(reg, rauhtd, type, 0x08, 0, 4);

/* reg_rauhtd_entry_rअगर
 * Dump only अगर RIF has value of entry_rअगर
 * Reserved अगर filter_fields bit3 is '0'
 * Access: Index
 */
MLXSW_ITEM32(reg, rauhtd, entry_rअगर, 0x0C, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_rauhtd_pack(अक्षर *payload,
					 क्रमागत mlxsw_reg_rauhtd_type type)
अणु
	MLXSW_REG_ZERO(rauhtd, payload);
	mlxsw_reg_rauhtd_filter_fields_set(payload, MLXSW_REG_RAUHTD_FILTER_A);
	mlxsw_reg_rauhtd_op_set(payload, MLXSW_REG_RAUHTD_OP_DUMP_AND_CLEAR);
	mlxsw_reg_rauhtd_num_rec_set(payload, MLXSW_REG_RAUHTD_REC_MAX_NUM);
	mlxsw_reg_rauhtd_entry_a_set(payload, 1);
	mlxsw_reg_rauhtd_type_set(payload, type);
पूर्ण

/* reg_rauhtd_ipv4_rec_num_entries
 * Number of valid entries in this record:
 * 0 - 1 valid entry
 * 1 - 2 valid entries
 * 2 - 3 valid entries
 * 3 - 4 valid entries
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv4_rec_num_entries,
		     MLXSW_REG_RAUHTD_BASE_LEN, 28, 2,
		     MLXSW_REG_RAUHTD_REC_LEN, 0x00, false);

/* reg_rauhtd_rec_type
 * Record type.
 * 0 - IPv4
 * 1 - IPv6
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, rec_type, MLXSW_REG_RAUHTD_BASE_LEN, 24, 2,
		     MLXSW_REG_RAUHTD_REC_LEN, 0x00, false);

#घोषणा MLXSW_REG_RAUHTD_IPV4_ENT_LEN 0x8

/* reg_rauhtd_ipv4_ent_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on the
 * specअगरic entry.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv4_ent_a, MLXSW_REG_RAUHTD_BASE_LEN, 16, 1,
		     MLXSW_REG_RAUHTD_IPV4_ENT_LEN, 0x00, false);

/* reg_rauhtd_ipv4_ent_rअगर
 * Router पूर्णांकerface.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv4_ent_rअगर, MLXSW_REG_RAUHTD_BASE_LEN, 0,
		     16, MLXSW_REG_RAUHTD_IPV4_ENT_LEN, 0x00, false);

/* reg_rauhtd_ipv4_ent_dip
 * Destination IPv4 address.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv4_ent_dip, MLXSW_REG_RAUHTD_BASE_LEN, 0,
		     32, MLXSW_REG_RAUHTD_IPV4_ENT_LEN, 0x04, false);

#घोषणा MLXSW_REG_RAUHTD_IPV6_ENT_LEN 0x20

/* reg_rauhtd_ipv6_ent_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on the
 * specअगरic entry.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv6_ent_a, MLXSW_REG_RAUHTD_BASE_LEN, 16, 1,
		     MLXSW_REG_RAUHTD_IPV6_ENT_LEN, 0x00, false);

/* reg_rauhtd_ipv6_ent_rअगर
 * Router पूर्णांकerface.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, rauhtd, ipv6_ent_rअगर, MLXSW_REG_RAUHTD_BASE_LEN, 0,
		     16, MLXSW_REG_RAUHTD_IPV6_ENT_LEN, 0x00, false);

/* reg_rauhtd_ipv6_ent_dip
 * Destination IPv6 address.
 * Access: RO
 */
MLXSW_ITEM_BUF_INDEXED(reg, rauhtd, ipv6_ent_dip, MLXSW_REG_RAUHTD_BASE_LEN,
		       16, MLXSW_REG_RAUHTD_IPV6_ENT_LEN, 0x10);

अटल अंतरभूत व्योम mlxsw_reg_rauhtd_ent_ipv4_unpack(अक्षर *payload,
						    पूर्णांक ent_index, u16 *p_rअगर,
						    u32 *p_dip)
अणु
	*p_rअगर = mlxsw_reg_rauhtd_ipv4_ent_rअगर_get(payload, ent_index);
	*p_dip = mlxsw_reg_rauhtd_ipv4_ent_dip_get(payload, ent_index);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rauhtd_ent_ipv6_unpack(अक्षर *payload,
						    पूर्णांक rec_index, u16 *p_rअगर,
						    अक्षर *p_dip)
अणु
	*p_rअगर = mlxsw_reg_rauhtd_ipv6_ent_rअगर_get(payload, rec_index);
	mlxsw_reg_rauhtd_ipv6_ent_dip_स_नकल_from(payload, rec_index, p_dip);
पूर्ण

/* RTDP - Routing Tunnel Decap Properties Register
 * -----------------------------------------------
 * The RTDP रेजिस्टर is used क्रम configuring the tunnel decap properties of NVE
 * and IPinIP.
 */
#घोषणा MLXSW_REG_RTDP_ID 0x8020
#घोषणा MLXSW_REG_RTDP_LEN 0x44

MLXSW_REG_DEFINE(rtdp, MLXSW_REG_RTDP_ID, MLXSW_REG_RTDP_LEN);

क्रमागत mlxsw_reg_rtdp_type अणु
	MLXSW_REG_RTDP_TYPE_NVE,
	MLXSW_REG_RTDP_TYPE_IPIP,
पूर्ण;

/* reg_rtdp_type
 * Type of the RTDP entry as per क्रमागत mlxsw_reg_rtdp_type.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, type, 0x00, 28, 4);

/* reg_rtdp_tunnel_index
 * Index to the Decap entry.
 * For Spectrum, Index to KVD Linear.
 * Access: Index
 */
MLXSW_ITEM32(reg, rtdp, tunnel_index, 0x00, 0, 24);

/* reg_rtdp_egress_router_पूर्णांकerface
 * Underlay egress router पूर्णांकerface.
 * Valid range is from 0 to cap_max_router_पूर्णांकerfaces - 1
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, egress_router_पूर्णांकerface, 0x40, 0, 16);

/* IPinIP */

/* reg_rtdp_ipip_irअगर
 * Ingress Router Interface क्रम the overlay router
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_irअगर, 0x04, 16, 16);

क्रमागत mlxsw_reg_rtdp_ipip_sip_check अणु
	/* No sip checks. */
	MLXSW_REG_RTDP_IPIP_SIP_CHECK_NO,
	/* Filter packet अगर underlay is not IPv4 or अगर underlay SIP करोes not
	 * equal ipv4_usip.
	 */
	MLXSW_REG_RTDP_IPIP_SIP_CHECK_FILTER_IPV4,
	/* Filter packet अगर underlay is not IPv6 or अगर underlay SIP करोes not
	 * equal ipv6_usip.
	 */
	MLXSW_REG_RTDP_IPIP_SIP_CHECK_FILTER_IPV6 = 3,
पूर्ण;

/* reg_rtdp_ipip_sip_check
 * SIP check to perक्रमm. If decapsulation failed due to these configurations
 * then trap_id is IPIP_DECAP_ERROR.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_sip_check, 0x04, 0, 3);

/* If set, allow decapsulation of IPinIP (without GRE). */
#घोषणा MLXSW_REG_RTDP_IPIP_TYPE_CHECK_ALLOW_IPIP	BIT(0)
/* If set, allow decapsulation of IPinGREinIP without a key. */
#घोषणा MLXSW_REG_RTDP_IPIP_TYPE_CHECK_ALLOW_GRE	BIT(1)
/* If set, allow decapsulation of IPinGREinIP with a key. */
#घोषणा MLXSW_REG_RTDP_IPIP_TYPE_CHECK_ALLOW_GRE_KEY	BIT(2)

/* reg_rtdp_ipip_type_check
 * Flags as per MLXSW_REG_RTDP_IPIP_TYPE_CHECK_*. If decapsulation failed due to
 * these configurations then trap_id is IPIP_DECAP_ERROR.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_type_check, 0x08, 24, 3);

/* reg_rtdp_ipip_gre_key_check
 * Whether GRE key should be checked. When check is enabled:
 * - A packet received as IPinIP (without GRE) will always pass.
 * - A packet received as IPinGREinIP without a key will not pass the check.
 * - A packet received as IPinGREinIP with a key will pass the check only अगर the
 *   key in the packet is equal to expected_gre_key.
 * If decapsulation failed due to GRE key then trap_id is IPIP_DECAP_ERROR.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_gre_key_check, 0x08, 23, 1);

/* reg_rtdp_ipip_ipv4_usip
 * Underlay IPv4 address क्रम ipv4 source address check.
 * Reserved when sip_check is not '1'.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_ipv4_usip, 0x0C, 0, 32);

/* reg_rtdp_ipip_ipv6_usip_ptr
 * This field is valid when sip_check is "sipv6 check explicitly". This is a
 * poपूर्णांकer to the IPv6 DIP which is configured by RIPS. For Spectrum, the index
 * is to the KVD linear.
 * Reserved when sip_check is not MLXSW_REG_RTDP_IPIP_SIP_CHECK_FILTER_IPV6.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_ipv6_usip_ptr, 0x10, 0, 24);

/* reg_rtdp_ipip_expected_gre_key
 * GRE key क्रम checking.
 * Reserved when gre_key_check is '0'.
 * Access: RW
 */
MLXSW_ITEM32(reg, rtdp, ipip_expected_gre_key, 0x14, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_rtdp_pack(अक्षर *payload,
				       क्रमागत mlxsw_reg_rtdp_type type,
				       u32 tunnel_index)
अणु
	MLXSW_REG_ZERO(rtdp, payload);
	mlxsw_reg_rtdp_type_set(payload, type);
	mlxsw_reg_rtdp_tunnel_index_set(payload, tunnel_index);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_rtdp_ipip4_pack(अक्षर *payload, u16 irअगर,
			  क्रमागत mlxsw_reg_rtdp_ipip_sip_check sip_check,
			  अचिन्हित पूर्णांक type_check, bool gre_key_check,
			  u32 ipv4_usip, u32 expected_gre_key)
अणु
	mlxsw_reg_rtdp_ipip_irअगर_set(payload, irअगर);
	mlxsw_reg_rtdp_ipip_sip_check_set(payload, sip_check);
	mlxsw_reg_rtdp_ipip_type_check_set(payload, type_check);
	mlxsw_reg_rtdp_ipip_gre_key_check_set(payload, gre_key_check);
	mlxsw_reg_rtdp_ipip_ipv4_usip_set(payload, ipv4_usip);
	mlxsw_reg_rtdp_ipip_expected_gre_key_set(payload, expected_gre_key);
पूर्ण

/* RATRAD - Router Adjacency Table Activity Dump Register
 * ------------------------------------------------------
 * The RATRAD रेजिस्टर is used to dump and optionally clear activity bits of
 * router adjacency table entries.
 */
#घोषणा MLXSW_REG_RATRAD_ID 0x8022
#घोषणा MLXSW_REG_RATRAD_LEN 0x210

MLXSW_REG_DEFINE(ratrad, MLXSW_REG_RATRAD_ID, MLXSW_REG_RATRAD_LEN);

क्रमागत अणु
	/* Read activity */
	MLXSW_REG_RATRAD_OP_READ_ACTIVITY,
	/* Read and clear activity */
	MLXSW_REG_RATRAD_OP_READ_CLEAR_ACTIVITY,
पूर्ण;

/* reg_ratrad_op
 * Access: Operation
 */
MLXSW_ITEM32(reg, ratrad, op, 0x00, 30, 2);

/* reg_ratrad_ecmp_size
 * ecmp_size is the amount of sequential entries from adjacency_index. Valid
 * ranges:
 * Spectrum-1: 32-64, 512, 1024, 2048, 4096
 * Spectrum-2/3: 32-128, 256, 512, 1024, 2048, 4096
 * Access: Index
 */
MLXSW_ITEM32(reg, ratrad, ecmp_size, 0x00, 0, 13);

/* reg_ratrad_adjacency_index
 * Index पूर्णांकo the adjacency table.
 * Access: Index
 */
MLXSW_ITEM32(reg, ratrad, adjacency_index, 0x04, 0, 24);

/* reg_ratrad_activity_vector
 * Activity bit per adjacency index.
 * Bits higher than ecmp_size are reserved.
 * Access: RO
 */
MLXSW_ITEM_BIT_ARRAY(reg, ratrad, activity_vector, 0x10, 0x200, 1);

अटल अंतरभूत व्योम mlxsw_reg_ratrad_pack(अक्षर *payload, u32 adjacency_index,
					 u16 ecmp_size)
अणु
	MLXSW_REG_ZERO(ratrad, payload);
	mlxsw_reg_ratrad_op_set(payload,
				MLXSW_REG_RATRAD_OP_READ_CLEAR_ACTIVITY);
	mlxsw_reg_ratrad_ecmp_size_set(payload, ecmp_size);
	mlxsw_reg_ratrad_adjacency_index_set(payload, adjacency_index);
पूर्ण

/* RIGR-V2 - Router Interface Group Register Version 2
 * ---------------------------------------------------
 * The RIGR_V2 रेजिस्टर is used to add, हटाओ and query egress पूर्णांकerface list
 * of a multicast क्रमwarding entry.
 */
#घोषणा MLXSW_REG_RIGR2_ID 0x8023
#घोषणा MLXSW_REG_RIGR2_LEN 0xB0

#घोषणा MLXSW_REG_RIGR2_MAX_ERIFS 32

MLXSW_REG_DEFINE(rigr2, MLXSW_REG_RIGR2_ID, MLXSW_REG_RIGR2_LEN);

/* reg_rigr2_rigr_index
 * KVD Linear index.
 * Access: Index
 */
MLXSW_ITEM32(reg, rigr2, rigr_index, 0x04, 0, 24);

/* reg_rigr2_vnext
 * Next RIGR Index is valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr2, vnext, 0x08, 31, 1);

/* reg_rigr2_next_rigr_index
 * Next RIGR Index. The index is to the KVD linear.
 * Reserved when vnxet = '0'.
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr2, next_rigr_index, 0x08, 0, 24);

/* reg_rigr2_vrmid
 * RMID Index is valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr2, vrmid, 0x20, 31, 1);

/* reg_rigr2_rmid_index
 * RMID Index.
 * Range 0 .. max_mid - 1
 * Reserved when vrmid = '0'.
 * The index is to the Port Group Table (PGT)
 * Access: RW
 */
MLXSW_ITEM32(reg, rigr2, rmid_index, 0x20, 0, 16);

/* reg_rigr2_erअगर_entry_v
 * Egress Router Interface is valid.
 * Note that low-entries must be set अगर high-entries are set. For
 * example: अगर erअगर_entry[2].v is set then erअगर_entry[1].v and
 * erअगर_entry[0].v must be set.
 * Index can be from 0 to cap_mc_erअगर_list_entries-1
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rigr2, erअगर_entry_v, 0x24, 31, 1, 4, 0, false);

/* reg_rigr2_erअगर_entry_erअगर
 * Egress Router Interface.
 * Valid range is from 0 to cap_max_router_पूर्णांकerfaces - 1
 * Index can be from 0 to MLXSW_REG_RIGR2_MAX_ERIFS - 1
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, rigr2, erअगर_entry_erअगर, 0x24, 0, 16, 4, 0, false);

अटल अंतरभूत व्योम mlxsw_reg_rigr2_pack(अक्षर *payload, u32 rigr_index,
					bool vnext, u32 next_rigr_index)
अणु
	MLXSW_REG_ZERO(rigr2, payload);
	mlxsw_reg_rigr2_rigr_index_set(payload, rigr_index);
	mlxsw_reg_rigr2_vnext_set(payload, vnext);
	mlxsw_reg_rigr2_next_rigr_index_set(payload, next_rigr_index);
	mlxsw_reg_rigr2_vrmid_set(payload, 0);
	mlxsw_reg_rigr2_rmid_index_set(payload, 0);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rigr2_erअगर_entry_pack(अक्षर *payload, पूर्णांक index,
						   bool v, u16 erअगर)
अणु
	mlxsw_reg_rigr2_erअगर_entry_v_set(payload, index, v);
	mlxsw_reg_rigr2_erअगर_entry_erअगर_set(payload, index, erअगर);
पूर्ण

/* RECR-V2 - Router ECMP Configuration Version 2 Register
 * ------------------------------------------------------
 */
#घोषणा MLXSW_REG_RECR2_ID 0x8025
#घोषणा MLXSW_REG_RECR2_LEN 0x38

MLXSW_REG_DEFINE(recr2, MLXSW_REG_RECR2_ID, MLXSW_REG_RECR2_LEN);

/* reg_recr2_pp
 * Per-port configuration
 * Access: Index
 */
MLXSW_ITEM32(reg, recr2, pp, 0x00, 24, 1);

/* reg_recr2_sh
 * Symmetric hash
 * Access: RW
 */
MLXSW_ITEM32(reg, recr2, sh, 0x00, 8, 1);

/* reg_recr2_seed
 * Seed
 * Access: RW
 */
MLXSW_ITEM32(reg, recr2, seed, 0x08, 0, 32);

क्रमागत अणु
	/* Enable IPv4 fields अगर packet is not TCP and not UDP */
	MLXSW_REG_RECR2_IPV4_EN_NOT_TCP_NOT_UDP	= 3,
	/* Enable IPv4 fields अगर packet is TCP or UDP */
	MLXSW_REG_RECR2_IPV4_EN_TCP_UDP		= 4,
	/* Enable IPv6 fields अगर packet is not TCP and not UDP */
	MLXSW_REG_RECR2_IPV6_EN_NOT_TCP_NOT_UDP	= 5,
	/* Enable IPv6 fields अगर packet is TCP or UDP */
	MLXSW_REG_RECR2_IPV6_EN_TCP_UDP		= 6,
	/* Enable TCP/UDP header fields अगर packet is IPv4 */
	MLXSW_REG_RECR2_TCP_UDP_EN_IPV4		= 7,
	/* Enable TCP/UDP header fields अगर packet is IPv6 */
	MLXSW_REG_RECR2_TCP_UDP_EN_IPV6		= 8,
पूर्ण;

/* reg_recr2_outer_header_enables
 * Bit mask where each bit enables a specअगरic layer to be included in
 * the hash calculation.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, recr2, outer_header_enables, 0x10, 0x04, 1);

क्रमागत अणु
	/* IPv4 Source IP */
	MLXSW_REG_RECR2_IPV4_SIP0			= 9,
	MLXSW_REG_RECR2_IPV4_SIP3			= 12,
	/* IPv4 Destination IP */
	MLXSW_REG_RECR2_IPV4_DIP0			= 13,
	MLXSW_REG_RECR2_IPV4_DIP3			= 16,
	/* IP Protocol */
	MLXSW_REG_RECR2_IPV4_PROTOCOL			= 17,
	/* IPv6 Source IP */
	MLXSW_REG_RECR2_IPV6_SIP0_7			= 21,
	MLXSW_REG_RECR2_IPV6_SIP8			= 29,
	MLXSW_REG_RECR2_IPV6_SIP15			= 36,
	/* IPv6 Destination IP */
	MLXSW_REG_RECR2_IPV6_DIP0_7			= 37,
	MLXSW_REG_RECR2_IPV6_DIP8			= 45,
	MLXSW_REG_RECR2_IPV6_DIP15			= 52,
	/* IPv6 Next Header */
	MLXSW_REG_RECR2_IPV6_NEXT_HEADER		= 53,
	/* IPv6 Flow Label */
	MLXSW_REG_RECR2_IPV6_FLOW_LABEL			= 57,
	/* TCP/UDP Source Port */
	MLXSW_REG_RECR2_TCP_UDP_SPORT			= 74,
	/* TCP/UDP Destination Port */
	MLXSW_REG_RECR2_TCP_UDP_DPORT			= 75,
पूर्ण;

/* reg_recr2_outer_header_fields_enable
 * Packet fields to enable क्रम ECMP hash subject to outer_header_enable.
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, recr2, outer_header_fields_enable, 0x14, 0x14, 1);

अटल अंतरभूत व्योम mlxsw_reg_recr2_ipv4_sip_enable(अक्षर *payload)
अणु
	पूर्णांक i;

	क्रम (i = MLXSW_REG_RECR2_IPV4_SIP0; i <= MLXSW_REG_RECR2_IPV4_SIP3; i++)
		mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i,
							       true);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_recr2_ipv4_dip_enable(अक्षर *payload)
अणु
	पूर्णांक i;

	क्रम (i = MLXSW_REG_RECR2_IPV4_DIP0; i <= MLXSW_REG_RECR2_IPV4_DIP3; i++)
		mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i,
							       true);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_recr2_ipv6_sip_enable(अक्षर *payload)
अणु
	पूर्णांक i = MLXSW_REG_RECR2_IPV6_SIP0_7;

	mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i, true);

	i = MLXSW_REG_RECR2_IPV6_SIP8;
	क्रम (; i <= MLXSW_REG_RECR2_IPV6_SIP15; i++)
		mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i,
							       true);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_recr2_ipv6_dip_enable(अक्षर *payload)
अणु
	पूर्णांक i = MLXSW_REG_RECR2_IPV6_DIP0_7;

	mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i, true);

	i = MLXSW_REG_RECR2_IPV6_DIP8;
	क्रम (; i <= MLXSW_REG_RECR2_IPV6_DIP15; i++)
		mlxsw_reg_recr2_outer_header_fields_enable_set(payload, i,
							       true);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_recr2_pack(अक्षर *payload, u32 seed)
अणु
	MLXSW_REG_ZERO(recr2, payload);
	mlxsw_reg_recr2_pp_set(payload, false);
	mlxsw_reg_recr2_sh_set(payload, true);
	mlxsw_reg_recr2_seed_set(payload, seed);
पूर्ण

/* RMFT-V2 - Router Multicast Forwarding Table Version 2 Register
 * --------------------------------------------------------------
 * The RMFT_V2 रेजिस्टर is used to configure and query the multicast table.
 */
#घोषणा MLXSW_REG_RMFT2_ID 0x8027
#घोषणा MLXSW_REG_RMFT2_LEN 0x174

MLXSW_REG_DEFINE(rmft2, MLXSW_REG_RMFT2_ID, MLXSW_REG_RMFT2_LEN);

/* reg_rmft2_v
 * Valid
 * Access: RW
 */
MLXSW_ITEM32(reg, rmft2, v, 0x00, 31, 1);

क्रमागत mlxsw_reg_rmft2_type अणु
	MLXSW_REG_RMFT2_TYPE_IPV4,
	MLXSW_REG_RMFT2_TYPE_IPV6
पूर्ण;

/* reg_rmft2_type
 * Access: Index
 */
MLXSW_ITEM32(reg, rmft2, type, 0x00, 28, 2);

क्रमागत mlxsw_sp_reg_rmft2_op अणु
	/* For Write:
	 * Write operation. Used to ग_लिखो a new entry to the table. All RW
	 * fields are relevant क्रम new entry. Activity bit is set क्रम new
	 * entries - Note ग_लिखो with v (Valid) 0 will delete the entry.
	 * For Query:
	 * Read operation
	 */
	MLXSW_REG_RMFT2_OP_READ_WRITE,
पूर्ण;

/* reg_rmft2_op
 * Operation.
 * Access: OP
 */
MLXSW_ITEM32(reg, rmft2, op, 0x00, 20, 2);

/* reg_rmft2_a
 * Activity. Set क्रम new entries. Set अगर a packet lookup has hit on the specअगरic
 * entry.
 * Access: RO
 */
MLXSW_ITEM32(reg, rmft2, a, 0x00, 16, 1);

/* reg_rmft2_offset
 * Offset within the multicast क्रमwarding table to ग_लिखो to.
 * Access: Index
 */
MLXSW_ITEM32(reg, rmft2, offset, 0x00, 0, 16);

/* reg_rmft2_भव_router
 * Virtual Router ID. Range from 0..cap_max_भव_routers-1
 * Access: RW
 */
MLXSW_ITEM32(reg, rmft2, भव_router, 0x04, 0, 16);

क्रमागत mlxsw_reg_rmft2_irअगर_mask अणु
	MLXSW_REG_RMFT2_IRIF_MASK_IGNORE,
	MLXSW_REG_RMFT2_IRIF_MASK_COMPARE
पूर्ण;

/* reg_rmft2_irअगर_mask
 * Ingress RIF mask.
 * Access: RW
 */
MLXSW_ITEM32(reg, rmft2, irअगर_mask, 0x08, 24, 1);

/* reg_rmft2_irअगर
 * Ingress RIF index.
 * Access: RW
 */
MLXSW_ITEM32(reg, rmft2, irअगर, 0x08, 0, 16);

/* reg_rmft2_dipअणु4,6पूर्ण
 * Destination IPv4/6 address
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rmft2, dip6, 0x10, 16);
MLXSW_ITEM32(reg, rmft2, dip4, 0x1C, 0, 32);

/* reg_rmft2_dipअणु4,6पूर्ण_mask
 * A bit that is set directs the TCAM to compare the corresponding bit in key. A
 * bit that is clear directs the TCAM to ignore the corresponding bit in key.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rmft2, dip6_mask, 0x20, 16);
MLXSW_ITEM32(reg, rmft2, dip4_mask, 0x2C, 0, 32);

/* reg_rmft2_sipअणु4,6पूर्ण
 * Source IPv4/6 address
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rmft2, sip6, 0x30, 16);
MLXSW_ITEM32(reg, rmft2, sip4, 0x3C, 0, 32);

/* reg_rmft2_sipअणु4,6पूर्ण_mask
 * A bit that is set directs the TCAM to compare the corresponding bit in key. A
 * bit that is clear directs the TCAM to ignore the corresponding bit in key.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rmft2, sip6_mask, 0x40, 16);
MLXSW_ITEM32(reg, rmft2, sip4_mask, 0x4C, 0, 32);

/* reg_rmft2_flexible_action_set
 * ACL action set. The only supported action types in this field and in any
 * action-set poपूर्णांकed from here are as follows:
 * 00h: ACTION_शून्य
 * 01h: ACTION_MAC_TTL, only TTL configuration is supported.
 * 03h: ACTION_TRAP
 * 06h: ACTION_QOS
 * 08h: ACTION_POLICING_MONITORING
 * 10h: ACTION_ROUTER_MC
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, rmft2, flexible_action_set, 0x80,
	       MLXSW_REG_FLEX_ACTION_SET_LEN);

अटल अंतरभूत व्योम
mlxsw_reg_rmft2_common_pack(अक्षर *payload, bool v, u16 offset,
			    u16 भव_router,
			    क्रमागत mlxsw_reg_rmft2_irअगर_mask irअगर_mask, u16 irअगर,
			    स्थिर अक्षर *flex_action_set)
अणु
	MLXSW_REG_ZERO(rmft2, payload);
	mlxsw_reg_rmft2_v_set(payload, v);
	mlxsw_reg_rmft2_op_set(payload, MLXSW_REG_RMFT2_OP_READ_WRITE);
	mlxsw_reg_rmft2_offset_set(payload, offset);
	mlxsw_reg_rmft2_भव_router_set(payload, भव_router);
	mlxsw_reg_rmft2_irअगर_mask_set(payload, irअगर_mask);
	mlxsw_reg_rmft2_irअगर_set(payload, irअगर);
	अगर (flex_action_set)
		mlxsw_reg_rmft2_flexible_action_set_स_नकल_to(payload,
							      flex_action_set);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_rmft2_ipv4_pack(अक्षर *payload, bool v, u16 offset, u16 भव_router,
			  क्रमागत mlxsw_reg_rmft2_irअगर_mask irअगर_mask, u16 irअगर,
			  u32 dip4, u32 dip4_mask, u32 sip4, u32 sip4_mask,
			  स्थिर अक्षर *flexible_action_set)
अणु
	mlxsw_reg_rmft2_common_pack(payload, v, offset, भव_router,
				    irअगर_mask, irअगर, flexible_action_set);
	mlxsw_reg_rmft2_type_set(payload, MLXSW_REG_RMFT2_TYPE_IPV4);
	mlxsw_reg_rmft2_dip4_set(payload, dip4);
	mlxsw_reg_rmft2_dip4_mask_set(payload, dip4_mask);
	mlxsw_reg_rmft2_sip4_set(payload, sip4);
	mlxsw_reg_rmft2_sip4_mask_set(payload, sip4_mask);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_rmft2_ipv6_pack(अक्षर *payload, bool v, u16 offset, u16 भव_router,
			  क्रमागत mlxsw_reg_rmft2_irअगर_mask irअगर_mask, u16 irअगर,
			  काष्ठा in6_addr dip6, काष्ठा in6_addr dip6_mask,
			  काष्ठा in6_addr sip6, काष्ठा in6_addr sip6_mask,
			  स्थिर अक्षर *flexible_action_set)
अणु
	mlxsw_reg_rmft2_common_pack(payload, v, offset, भव_router,
				    irअगर_mask, irअगर, flexible_action_set);
	mlxsw_reg_rmft2_type_set(payload, MLXSW_REG_RMFT2_TYPE_IPV6);
	mlxsw_reg_rmft2_dip6_स_नकल_to(payload, (व्योम *)&dip6);
	mlxsw_reg_rmft2_dip6_mask_स_नकल_to(payload, (व्योम *)&dip6_mask);
	mlxsw_reg_rmft2_sip6_स_नकल_to(payload, (व्योम *)&sip6);
	mlxsw_reg_rmft2_sip6_mask_स_नकल_to(payload, (व्योम *)&sip6_mask);
पूर्ण

/* RXLTE - Router XLT Enable Register
 * ----------------------------------
 * The RXLTE enables XLT (eXtended Lookup Table) LPM lookups अगर a capable
 * XM is present on the प्रणाली.
 */

#घोषणा MLXSW_REG_RXLTE_ID 0x8050
#घोषणा MLXSW_REG_RXLTE_LEN 0x0C

MLXSW_REG_DEFINE(rxlte, MLXSW_REG_RXLTE_ID, MLXSW_REG_RXLTE_LEN);

/* reg_rxlte_भव_router
 * Virtual router ID associated with the router पूर्णांकerface.
 * Range is 0..cap_max_भव_routers-1
 * Access: Index
 */
MLXSW_ITEM32(reg, rxlte, भव_router, 0x00, 0, 16);

क्रमागत mlxsw_reg_rxlte_protocol अणु
	MLXSW_REG_RXLTE_PROTOCOL_IPV4,
	MLXSW_REG_RXLTE_PROTOCOL_IPV6,
पूर्ण;

/* reg_rxlte_protocol
 * Access: Index
 */
MLXSW_ITEM32(reg, rxlte, protocol, 0x04, 0, 4);

/* reg_rxlte_lpm_xlt_en
 * Access: RW
 */
MLXSW_ITEM32(reg, rxlte, lpm_xlt_en, 0x08, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_rxlte_pack(अक्षर *payload, u16 भव_router,
					क्रमागत mlxsw_reg_rxlte_protocol protocol,
					bool lpm_xlt_en)
अणु
	MLXSW_REG_ZERO(rxlte, payload);
	mlxsw_reg_rxlte_भव_router_set(payload, भव_router);
	mlxsw_reg_rxlte_protocol_set(payload, protocol);
	mlxsw_reg_rxlte_lpm_xlt_en_set(payload, lpm_xlt_en);
पूर्ण

/* RXLTM - Router XLT M select Register
 * ------------------------------------
 * The RXLTM configures and selects the M क्रम the XM lookups.
 */

#घोषणा MLXSW_REG_RXLTM_ID 0x8051
#घोषणा MLXSW_REG_RXLTM_LEN 0x14

MLXSW_REG_DEFINE(rxlपंचांग, MLXSW_REG_RXLTM_ID, MLXSW_REG_RXLTM_LEN);

/* reg_rxlपंचांग_m0_val_v6
 * Global M0 value For IPv6.
 * Range 0..128
 * Access: RW
 */
MLXSW_ITEM32(reg, rxlपंचांग, m0_val_v6, 0x10, 16, 8);

/* reg_rxlपंचांग_m0_val_v4
 * Global M0 value For IPv4.
 * Range 0..32
 * Access: RW
 */
MLXSW_ITEM32(reg, rxlपंचांग, m0_val_v4, 0x10, 0, 6);

अटल अंतरभूत व्योम mlxsw_reg_rxlपंचांग_pack(अक्षर *payload, u8 m0_val_v4, u8 m0_val_v6)
अणु
	MLXSW_REG_ZERO(rxlपंचांग, payload);
	mlxsw_reg_rxlपंचांग_m0_val_v6_set(payload, m0_val_v6);
	mlxsw_reg_rxlपंचांग_m0_val_v4_set(payload, m0_val_v4);
पूर्ण

/* RLCMLD - Router LPM Cache ML Delete Register
 * --------------------------------------------
 * The RLCMLD रेजिस्टर is used to bulk delete the XLT-LPM cache ML entries.
 * This can be used by SW when L is increased or decreased, thus need to
 * हटाओ entries with old ML values.
 */

#घोषणा MLXSW_REG_RLCMLD_ID 0x8055
#घोषणा MLXSW_REG_RLCMLD_LEN 0x30

MLXSW_REG_DEFINE(rlcmld, MLXSW_REG_RLCMLD_ID, MLXSW_REG_RLCMLD_LEN);

क्रमागत mlxsw_reg_rlcmld_select अणु
	MLXSW_REG_RLCMLD_SELECT_ML_ENTRIES,
	MLXSW_REG_RLCMLD_SELECT_M_ENTRIES,
	MLXSW_REG_RLCMLD_SELECT_M_AND_ML_ENTRIES,
पूर्ण;

/* reg_rlcmld_select
 * Which entries to delete.
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, select, 0x00, 16, 2);

क्रमागत mlxsw_reg_rlcmld_filter_fields अणु
	MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_PROTOCOL = 0x04,
	MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_VIRTUAL_ROUTER = 0x08,
	MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_DIP = 0x10,
पूर्ण;

/* reg_rlcmld_filter_fields
 * If a bit is '0' then the relevant field is ignored.
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, filter_fields, 0x00, 0, 8);

क्रमागत mlxsw_reg_rlcmld_protocol अणु
	MLXSW_REG_RLCMLD_PROTOCOL_UC_IPV4,
	MLXSW_REG_RLCMLD_PROTOCOL_UC_IPV6,
पूर्ण;

/* reg_rlcmld_protocol
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, protocol, 0x08, 0, 4);

/* reg_rlcmld_भव_router
 * Virtual router ID.
 * Range is 0..cap_max_भव_routers-1
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, भव_router, 0x0C, 0, 16);

/* reg_rlcmld_dip
 * The prefix of the route or of the marker that the object of the LPM
 * is compared with. The most signअगरicant bits of the dip are the prefix.
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, dip4, 0x1C, 0, 32);
MLXSW_ITEM_BUF(reg, rlcmld, dip6, 0x10, 16);

/* reg_rlcmld_dip_mask
 * per bit:
 * 0: no match
 * 1: match
 * Access: Index
 */
MLXSW_ITEM32(reg, rlcmld, dip_mask4, 0x2C, 0, 32);
MLXSW_ITEM_BUF(reg, rlcmld, dip_mask6, 0x20, 16);

अटल अंतरभूत व्योम __mlxsw_reg_rlcmld_pack(अक्षर *payload,
					   क्रमागत mlxsw_reg_rlcmld_select select,
					   क्रमागत mlxsw_reg_rlcmld_protocol protocol,
					   u16 भव_router)
अणु
	u8 filter_fields = MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_PROTOCOL |
			   MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_VIRTUAL_ROUTER |
			   MLXSW_REG_RLCMLD_FILTER_FIELDS_BY_DIP;

	MLXSW_REG_ZERO(rlcmld, payload);
	mlxsw_reg_rlcmld_select_set(payload, select);
	mlxsw_reg_rlcmld_filter_fields_set(payload, filter_fields);
	mlxsw_reg_rlcmld_protocol_set(payload, protocol);
	mlxsw_reg_rlcmld_भव_router_set(payload, भव_router);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rlcmld_pack4(अक्षर *payload,
					  क्रमागत mlxsw_reg_rlcmld_select select,
					  u16 भव_router,
					  u32 dip, u32 dip_mask)
अणु
	__mlxsw_reg_rlcmld_pack(payload, select,
				MLXSW_REG_RLCMLD_PROTOCOL_UC_IPV4,
				भव_router);
	mlxsw_reg_rlcmld_dip4_set(payload, dip);
	mlxsw_reg_rlcmld_dip_mask4_set(payload, dip_mask);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_rlcmld_pack6(अक्षर *payload,
					  क्रमागत mlxsw_reg_rlcmld_select select,
					  u16 भव_router,
					  स्थिर व्योम *dip, स्थिर व्योम *dip_mask)
अणु
	__mlxsw_reg_rlcmld_pack(payload, select,
				MLXSW_REG_RLCMLD_PROTOCOL_UC_IPV6,
				भव_router);
	mlxsw_reg_rlcmld_dip6_स_नकल_to(payload, dip);
	mlxsw_reg_rlcmld_dip_mask6_स_नकल_to(payload, dip_mask);
पूर्ण

/* RLPMCE - Router LPM Cache Enable Register
 * -----------------------------------------
 * Allows disabling the LPM cache. Can be changed on the fly.
 */

#घोषणा MLXSW_REG_RLPMCE_ID 0x8056
#घोषणा MLXSW_REG_RLPMCE_LEN 0x4

MLXSW_REG_DEFINE(rlpmce, MLXSW_REG_RLPMCE_ID, MLXSW_REG_RLPMCE_LEN);

/* reg_rlpmce_flush
 * Flush:
 * 0: करो not flush the cache (शेष)
 * 1: flush (clear) the cache
 * Access: WO
 */
MLXSW_ITEM32(reg, rlpmce, flush, 0x00, 4, 1);

/* reg_rlpmce_disable
 * LPM cache:
 * 0: enabled (शेष)
 * 1: disabled
 * Access: RW
 */
MLXSW_ITEM32(reg, rlpmce, disable, 0x00, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_rlpmce_pack(अक्षर *payload, bool flush,
					 bool disable)
अणु
	MLXSW_REG_ZERO(rlpmce, payload);
	mlxsw_reg_rlpmce_flush_set(payload, flush);
	mlxsw_reg_rlpmce_disable_set(payload, disable);
पूर्ण

/* Note that XLTQ, XMDR, XRMT and XRALXX रेजिस्टर positions violate the rule
 * of ordering रेजिस्टर definitions by the ID. However, XRALXX pack helpers are
 * using RALXX pack helpers, RALXX रेजिस्टरs have higher IDs.
 * Also XMDR is using RALUE क्रमागतs. XLRQ and XRMT are just put aदीर्घside with the
 * related रेजिस्टरs.
 */

/* XLTQ - XM Lookup Table Query Register
 * -------------------------------------
 */
#घोषणा MLXSW_REG_XLTQ_ID 0x7802
#घोषणा MLXSW_REG_XLTQ_LEN 0x2C

MLXSW_REG_DEFINE(xltq, MLXSW_REG_XLTQ_ID, MLXSW_REG_XLTQ_LEN);

क्रमागत mlxsw_reg_xltq_xm_device_id अणु
	MLXSW_REG_XLTQ_XM_DEVICE_ID_UNKNOWN,
	MLXSW_REG_XLTQ_XM_DEVICE_ID_XLT = 0xCF71,
पूर्ण;

/* reg_xltq_xm_device_id
 * XM device ID.
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, xm_device_id, 0x04, 0, 16);

/* reg_xltq_xlt_cap_ipv4_lpm
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, xlt_cap_ipv4_lpm, 0x10, 0, 1);

/* reg_xltq_xlt_cap_ipv6_lpm
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, xlt_cap_ipv6_lpm, 0x10, 1, 1);

/* reg_xltq_cap_xlt_entries
 * Number of XLT entries
 * Note: SW must not fill more than 80% in order to aव्योम overflow
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, cap_xlt_entries, 0x20, 0, 32);

/* reg_xltq_cap_xlt_mtable
 * XLT M-Table max size
 * Access: RO
 */
MLXSW_ITEM32(reg, xltq, cap_xlt_mtable, 0x24, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_xltq_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(xltq, payload);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_xltq_unpack(अक्षर *payload, u16 *xm_device_id, bool *xlt_cap_ipv4_lpm,
					 bool *xlt_cap_ipv6_lpm, u32 *cap_xlt_entries,
					 u32 *cap_xlt_mtable)
अणु
	*xm_device_id = mlxsw_reg_xltq_xm_device_id_get(payload);
	*xlt_cap_ipv4_lpm = mlxsw_reg_xltq_xlt_cap_ipv4_lpm_get(payload);
	*xlt_cap_ipv6_lpm = mlxsw_reg_xltq_xlt_cap_ipv6_lpm_get(payload);
	*cap_xlt_entries = mlxsw_reg_xltq_cap_xlt_entries_get(payload);
	*cap_xlt_mtable = mlxsw_reg_xltq_cap_xlt_mtable_get(payload);
पूर्ण

/* XMDR - XM Direct Register
 * -------------------------
 * The XMDR allows direct access to the XM device via the चयन.
 * Working in synchronous mode. FW रुकोs क्रम response from the XLT
 * क्रम each command. FW acks the XMDR accordingly.
 */
#घोषणा MLXSW_REG_XMDR_ID 0x7803
#घोषणा MLXSW_REG_XMDR_BASE_LEN 0x20
#घोषणा MLXSW_REG_XMDR_TRANS_LEN 0x80
#घोषणा MLXSW_REG_XMDR_LEN (MLXSW_REG_XMDR_BASE_LEN + \
			    MLXSW_REG_XMDR_TRANS_LEN)

MLXSW_REG_DEFINE(xmdr, MLXSW_REG_XMDR_ID, MLXSW_REG_XMDR_LEN);

/* reg_xmdr_bulk_entry
 * Bulk_entry
 * 0: Last entry - immediate flush of XRT-cache
 * 1: Bulk entry - करो not flush the XRT-cache
 * Access: OP
 */
MLXSW_ITEM32(reg, xmdr, bulk_entry, 0x04, 8, 1);

/* reg_xmdr_num_rec
 * Number of records क्रम Direct access to XM
 * Supported: 0..4 commands (except NOP which is a filler)
 * 0 commands is reserved when bulk_entry = 1.
 * 0 commands is allowed when bulk_entry = 0 क्रम immediate XRT-cache flush.
 * Access: OP
 */
MLXSW_ITEM32(reg, xmdr, num_rec, 0x04, 0, 4);

/* reg_xmdr_reply_vect
 * Reply Vector
 * Bit i क्रम command index i+1
 * values per bit:
 * 0: failed
 * 1: succeeded
 * e.g. अगर commands 1, 2, 4 succeeded and command 3 failed then binary
 * value will be 0b1011
 * Access: RO
 */
MLXSW_ITEM_BIT_ARRAY(reg, xmdr, reply_vect, 0x08, 4, 1);

अटल अंतरभूत व्योम mlxsw_reg_xmdr_pack(अक्षर *payload, bool bulk_entry)
अणु
	MLXSW_REG_ZERO(xmdr, payload);
	mlxsw_reg_xmdr_bulk_entry_set(payload, bulk_entry);
पूर्ण

क्रमागत mlxsw_reg_xmdr_c_cmd_id अणु
	MLXSW_REG_XMDR_C_CMD_ID_LT_ROUTE_V4 = 0x30,
	MLXSW_REG_XMDR_C_CMD_ID_LT_ROUTE_V6 = 0x31,
पूर्ण;

#घोषणा MLXSW_REG_XMDR_C_LT_ROUTE_V4_LEN 32
#घोषणा MLXSW_REG_XMDR_C_LT_ROUTE_V6_LEN 48

/* reg_xmdr_c_cmd_id
 */
MLXSW_ITEM32(reg, xmdr_c, cmd_id, 0x00, 24, 8);

/* reg_xmdr_c_seq_number
 */
MLXSW_ITEM32(reg, xmdr_c, seq_number, 0x00, 12, 12);

क्रमागत mlxsw_reg_xmdr_c_ltr_op अणु
	/* Activity is set */
	MLXSW_REG_XMDR_C_LTR_OP_WRITE = 0,
	/* There is no update mask. All fields are updated. */
	MLXSW_REG_XMDR_C_LTR_OP_UPDATE = 1,
	MLXSW_REG_XMDR_C_LTR_OP_DELETE = 2,
पूर्ण;

/* reg_xmdr_c_ltr_op
 * Operation.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_op, 0x04, 24, 8);

/* reg_xmdr_c_ltr_trap_action
 * Trap action.
 * Values are defined in क्रमागत mlxsw_reg_ralue_trap_action.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_trap_action, 0x04, 20, 4);

क्रमागत mlxsw_reg_xmdr_c_ltr_trap_id_num अणु
	MLXSW_REG_XMDR_C_LTR_TRAP_ID_NUM_RTR_INGRESS0,
	MLXSW_REG_XMDR_C_LTR_TRAP_ID_NUM_RTR_INGRESS1,
	MLXSW_REG_XMDR_C_LTR_TRAP_ID_NUM_RTR_INGRESS2,
	MLXSW_REG_XMDR_C_LTR_TRAP_ID_NUM_RTR_INGRESS3,
पूर्ण;

/* reg_xmdr_c_ltr_trap_id_num
 * Trap-ID number.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_trap_id_num, 0x04, 16, 4);

/* reg_xmdr_c_ltr_भव_router
 * Virtual Router ID.
 * Range is 0..cap_max_भव_routers-1
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_भव_router, 0x04, 0, 16);

/* reg_xmdr_c_ltr_prefix_len
 * Number of bits in the prefix of the LPM route.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_prefix_len, 0x08, 24, 8);

/* reg_xmdr_c_ltr_bmp_len
 * The best match prefix length in the हाल that there is no match क्रम
 * दीर्घer prefixes.
 * If (entry_type != MARKER_ENTRY), bmp_len must be equal to prefix_len
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_bmp_len, 0x08, 16, 8);

/* reg_xmdr_c_ltr_entry_type
 * Entry type.
 * Values are defined in क्रमागत mlxsw_reg_ralue_entry_type.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_entry_type, 0x08, 4, 4);

क्रमागत mlxsw_reg_xmdr_c_ltr_action_type अणु
	MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_LOCAL,
	MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_REMOTE,
	MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_IP2ME,
पूर्ण;

/* reg_xmdr_c_ltr_action_type
 * Action Type.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_action_type, 0x08, 0, 4);

/* reg_xmdr_c_ltr_erअगर
 * Egress Router Interface.
 * Only relevant in हाल of LOCAL action.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_erअगर, 0x10, 0, 16);

/* reg_xmdr_c_ltr_adjacency_index
 * Poपूर्णांकs to the first entry of the group-based ECMP.
 * Only relevant in हाल of REMOTE action.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_adjacency_index, 0x10, 0, 24);

#घोषणा MLXSW_REG_XMDR_C_LTR_POINTER_TO_TUNNEL_DISABLED_MAGIC 0xFFFFFF

/* reg_xmdr_c_ltr_poपूर्णांकer_to_tunnel
 * Only relevant in हाल of IP2ME action.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_poपूर्णांकer_to_tunnel, 0x10, 0, 24);

/* reg_xmdr_c_ltr_ecmp_size
 * Amount of sequential entries starting
 * from the adjacency_index (the number of ECMPs).
 * The valid range is 1-64, 512, 1024, 2048 and 4096.
 * Only relevant in हाल of REMOTE action.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_ecmp_size, 0x14, 0, 32);

/* reg_xmdr_c_ltr_dip*
 * The prefix of the route or of the marker that the object of the LPM
 * is compared with. The most signअगरicant bits of the dip are the prefix.
 * The least signअगरicant bits must be '0' अगर the prefix_len is smaller
 * than 128 क्रम IPv6 or smaller than 32 क्रम IPv4.
 */
MLXSW_ITEM32(reg, xmdr_c, ltr_dip4, 0x1C, 0, 32);
MLXSW_ITEM_BUF(reg, xmdr_c, ltr_dip6, 0x1C, 16);

अटल अंतरभूत व्योम
mlxsw_reg_xmdr_c_ltr_pack(अक्षर *xmdr_payload, अचिन्हित पूर्णांक trans_offset,
			  क्रमागत mlxsw_reg_xmdr_c_cmd_id cmd_id, u16 seq_number,
			  क्रमागत mlxsw_reg_xmdr_c_ltr_op op, u16 भव_router,
			  u8 prefix_len)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;
	u8 num_rec = mlxsw_reg_xmdr_num_rec_get(xmdr_payload);

	mlxsw_reg_xmdr_num_rec_set(xmdr_payload, num_rec + 1);

	mlxsw_reg_xmdr_c_cmd_id_set(payload, cmd_id);
	mlxsw_reg_xmdr_c_seq_number_set(payload, seq_number);
	mlxsw_reg_xmdr_c_ltr_op_set(payload, op);
	mlxsw_reg_xmdr_c_ltr_भव_router_set(payload, भव_router);
	mlxsw_reg_xmdr_c_ltr_prefix_len_set(payload, prefix_len);
	mlxsw_reg_xmdr_c_ltr_entry_type_set(payload,
					    MLXSW_REG_RALUE_ENTRY_TYPE_ROUTE_ENTRY);
	mlxsw_reg_xmdr_c_ltr_bmp_len_set(payload, prefix_len);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_reg_xmdr_c_ltr_pack4(अक्षर *xmdr_payload, अचिन्हित पूर्णांक trans_offset,
			   u16 seq_number, क्रमागत mlxsw_reg_xmdr_c_ltr_op op,
			   u16 भव_router, u8 prefix_len, u32 *dip)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_pack(xmdr_payload, trans_offset,
				  MLXSW_REG_XMDR_C_CMD_ID_LT_ROUTE_V4,
				  seq_number, op, भव_router, prefix_len);
	अगर (dip)
		mlxsw_reg_xmdr_c_ltr_dip4_set(payload, *dip);
	वापस MLXSW_REG_XMDR_C_LT_ROUTE_V4_LEN;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mlxsw_reg_xmdr_c_ltr_pack6(अक्षर *xmdr_payload, अचिन्हित पूर्णांक trans_offset,
			   u16 seq_number, क्रमागत mlxsw_reg_xmdr_c_ltr_op op,
			   u16 भव_router, u8 prefix_len, स्थिर व्योम *dip)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_pack(xmdr_payload, trans_offset,
				  MLXSW_REG_XMDR_C_CMD_ID_LT_ROUTE_V6,
				  seq_number, op, भव_router, prefix_len);
	अगर (dip)
		mlxsw_reg_xmdr_c_ltr_dip6_स_नकल_to(payload, dip);
	वापस MLXSW_REG_XMDR_C_LT_ROUTE_V6_LEN;
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_xmdr_c_ltr_act_remote_pack(अक्षर *xmdr_payload, अचिन्हित पूर्णांक trans_offset,
				     क्रमागत mlxsw_reg_ralue_trap_action trap_action,
				     क्रमागत mlxsw_reg_xmdr_c_ltr_trap_id_num trap_id_num,
				     u32 adjacency_index, u16 ecmp_size)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_action_type_set(payload, MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_REMOTE);
	mlxsw_reg_xmdr_c_ltr_trap_action_set(payload, trap_action);
	mlxsw_reg_xmdr_c_ltr_trap_id_num_set(payload, trap_id_num);
	mlxsw_reg_xmdr_c_ltr_adjacency_index_set(payload, adjacency_index);
	mlxsw_reg_xmdr_c_ltr_ecmp_size_set(payload, ecmp_size);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_xmdr_c_ltr_act_local_pack(अक्षर *xmdr_payload, अचिन्हित पूर्णांक trans_offset,
				    क्रमागत mlxsw_reg_ralue_trap_action trap_action,
				    क्रमागत mlxsw_reg_xmdr_c_ltr_trap_id_num trap_id_num, u16 erअगर)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_action_type_set(payload, MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_LOCAL);
	mlxsw_reg_xmdr_c_ltr_trap_action_set(payload, trap_action);
	mlxsw_reg_xmdr_c_ltr_trap_id_num_set(payload, trap_id_num);
	mlxsw_reg_xmdr_c_ltr_erअगर_set(payload, erअगर);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_xmdr_c_ltr_act_ip2me_pack(अक्षर *xmdr_payload,
						       अचिन्हित पूर्णांक trans_offset)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_action_type_set(payload, MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_IP2ME);
	mlxsw_reg_xmdr_c_ltr_poपूर्णांकer_to_tunnel_set(payload,
						   MLXSW_REG_XMDR_C_LTR_POINTER_TO_TUNNEL_DISABLED_MAGIC);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_xmdr_c_ltr_act_ip2me_tun_pack(अक्षर *xmdr_payload,
							   अचिन्हित पूर्णांक trans_offset,
							   u32 poपूर्णांकer_to_tunnel)
अणु
	अक्षर *payload = xmdr_payload + MLXSW_REG_XMDR_BASE_LEN + trans_offset;

	mlxsw_reg_xmdr_c_ltr_action_type_set(payload, MLXSW_REG_XMDR_C_LTR_ACTION_TYPE_IP2ME);
	mlxsw_reg_xmdr_c_ltr_poपूर्णांकer_to_tunnel_set(payload, poपूर्णांकer_to_tunnel);
पूर्ण

/* XRMT - XM Router M Table Register
 * ---------------------------------
 * The XRMT configures the M-Table क्रम the XLT-LPM.
 */
#घोषणा MLXSW_REG_XRMT_ID 0x7810
#घोषणा MLXSW_REG_XRMT_LEN 0x14

MLXSW_REG_DEFINE(xrmt, MLXSW_REG_XRMT_ID, MLXSW_REG_XRMT_LEN);

/* reg_xrmt_index
 * Index in M-Table.
 * Range 0..cap_xlt_mtable-1
 * Access: Index
 */
MLXSW_ITEM32(reg, xrmt, index, 0x04, 0, 20);

/* reg_xrmt_l0_val
 * Access: RW
 */
MLXSW_ITEM32(reg, xrmt, l0_val, 0x10, 24, 8);

अटल अंतरभूत व्योम mlxsw_reg_xrmt_pack(अक्षर *payload, u32 index, u8 l0_val)
अणु
	MLXSW_REG_ZERO(xrmt, payload);
	mlxsw_reg_xrmt_index_set(payload, index);
	mlxsw_reg_xrmt_l0_val_set(payload, l0_val);
पूर्ण

/* XRALTA - XM Router Algorithmic LPM Tree Allocation Register
 * -----------------------------------------------------------
 * The XRALTA is used to allocate the XLT LPM trees.
 *
 * This रेजिस्टर embeds original RALTA रेजिस्टर.
 */
#घोषणा MLXSW_REG_XRALTA_ID 0x7811
#घोषणा MLXSW_REG_XRALTA_LEN 0x08
#घोषणा MLXSW_REG_XRALTA_RALTA_OFFSET 0x04

MLXSW_REG_DEFINE(xralta, MLXSW_REG_XRALTA_ID, MLXSW_REG_XRALTA_LEN);

अटल अंतरभूत व्योम mlxsw_reg_xralta_pack(अक्षर *payload, bool alloc,
					 क्रमागत mlxsw_reg_ralxx_protocol protocol,
					 u8 tree_id)
अणु
	अक्षर *ralta_payload = payload + MLXSW_REG_XRALTA_RALTA_OFFSET;

	MLXSW_REG_ZERO(xralta, payload);
	mlxsw_reg_ralta_pack(ralta_payload, alloc, protocol, tree_id);
पूर्ण

/* XRALST - XM Router Algorithmic LPM Structure Tree Register
 * ----------------------------------------------------------
 * The XRALST is used to set and query the काष्ठाure of an XLT LPM tree.
 *
 * This रेजिस्टर embeds original RALST रेजिस्टर.
 */
#घोषणा MLXSW_REG_XRALST_ID 0x7812
#घोषणा MLXSW_REG_XRALST_LEN 0x108
#घोषणा MLXSW_REG_XRALST_RALST_OFFSET 0x04

MLXSW_REG_DEFINE(xralst, MLXSW_REG_XRALST_ID, MLXSW_REG_XRALST_LEN);

अटल अंतरभूत व्योम mlxsw_reg_xralst_pack(अक्षर *payload, u8 root_bin, u8 tree_id)
अणु
	अक्षर *ralst_payload = payload + MLXSW_REG_XRALST_RALST_OFFSET;

	MLXSW_REG_ZERO(xralst, payload);
	mlxsw_reg_ralst_pack(ralst_payload, root_bin, tree_id);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_xralst_bin_pack(अक्षर *payload, u8 bin_number,
					     u8 left_child_bin,
					     u8 right_child_bin)
अणु
	अक्षर *ralst_payload = payload + MLXSW_REG_XRALST_RALST_OFFSET;

	mlxsw_reg_ralst_bin_pack(ralst_payload, bin_number, left_child_bin,
				 right_child_bin);
पूर्ण

/* XRALTB - XM Router Algorithmic LPM Tree Binding Register
 * --------------------------------------------------------
 * The XRALTB रेजिस्टर is used to bind भव router and protocol
 * to an allocated LPM tree.
 *
 * This रेजिस्टर embeds original RALTB रेजिस्टर.
 */
#घोषणा MLXSW_REG_XRALTB_ID 0x7813
#घोषणा MLXSW_REG_XRALTB_LEN 0x08
#घोषणा MLXSW_REG_XRALTB_RALTB_OFFSET 0x04

MLXSW_REG_DEFINE(xraltb, MLXSW_REG_XRALTB_ID, MLXSW_REG_XRALTB_LEN);

अटल अंतरभूत व्योम mlxsw_reg_xraltb_pack(अक्षर *payload, u16 भव_router,
					 क्रमागत mlxsw_reg_ralxx_protocol protocol,
					 u8 tree_id)
अणु
	अक्षर *raltb_payload = payload + MLXSW_REG_XRALTB_RALTB_OFFSET;

	MLXSW_REG_ZERO(xraltb, payload);
	mlxsw_reg_raltb_pack(raltb_payload, भव_router, protocol, tree_id);
पूर्ण

/* MFCR - Management Fan Control Register
 * --------------------------------------
 * This रेजिस्टर controls the settings of the Fan Speed PWM mechanism.
 */
#घोषणा MLXSW_REG_MFCR_ID 0x9001
#घोषणा MLXSW_REG_MFCR_LEN 0x08

MLXSW_REG_DEFINE(mfcr, MLXSW_REG_MFCR_ID, MLXSW_REG_MFCR_LEN);

क्रमागत mlxsw_reg_mfcr_pwm_frequency अणु
	MLXSW_REG_MFCR_PWM_FEQ_11HZ = 0x00,
	MLXSW_REG_MFCR_PWM_FEQ_14_7HZ = 0x01,
	MLXSW_REG_MFCR_PWM_FEQ_22_1HZ = 0x02,
	MLXSW_REG_MFCR_PWM_FEQ_1_4KHZ = 0x40,
	MLXSW_REG_MFCR_PWM_FEQ_5KHZ = 0x41,
	MLXSW_REG_MFCR_PWM_FEQ_20KHZ = 0x42,
	MLXSW_REG_MFCR_PWM_FEQ_22_5KHZ = 0x43,
	MLXSW_REG_MFCR_PWM_FEQ_25KHZ = 0x44,
पूर्ण;

/* reg_mfcr_pwm_frequency
 * Controls the frequency of the PWM संकेत.
 * Access: RW
 */
MLXSW_ITEM32(reg, mfcr, pwm_frequency, 0x00, 0, 7);

#घोषणा MLXSW_MFCR_TACHOS_MAX 10

/* reg_mfcr_tacho_active
 * Indicates which of the tachometer is active (bit per tachometer).
 * Access: RO
 */
MLXSW_ITEM32(reg, mfcr, tacho_active, 0x04, 16, MLXSW_MFCR_TACHOS_MAX);

#घोषणा MLXSW_MFCR_PWMS_MAX 5

/* reg_mfcr_pwm_active
 * Indicates which of the PWM control is active (bit per PWM).
 * Access: RO
 */
MLXSW_ITEM32(reg, mfcr, pwm_active, 0x04, 0, MLXSW_MFCR_PWMS_MAX);

अटल अंतरभूत व्योम
mlxsw_reg_mfcr_pack(अक्षर *payload,
		    क्रमागत mlxsw_reg_mfcr_pwm_frequency pwm_frequency)
अणु
	MLXSW_REG_ZERO(mfcr, payload);
	mlxsw_reg_mfcr_pwm_frequency_set(payload, pwm_frequency);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mfcr_unpack(अक्षर *payload,
		      क्रमागत mlxsw_reg_mfcr_pwm_frequency *p_pwm_frequency,
		      u16 *p_tacho_active, u8 *p_pwm_active)
अणु
	*p_pwm_frequency = mlxsw_reg_mfcr_pwm_frequency_get(payload);
	*p_tacho_active = mlxsw_reg_mfcr_tacho_active_get(payload);
	*p_pwm_active = mlxsw_reg_mfcr_pwm_active_get(payload);
पूर्ण

/* MFSC - Management Fan Speed Control Register
 * --------------------------------------------
 * This रेजिस्टर controls the settings of the Fan Speed PWM mechanism.
 */
#घोषणा MLXSW_REG_MFSC_ID 0x9002
#घोषणा MLXSW_REG_MFSC_LEN 0x08

MLXSW_REG_DEFINE(mfsc, MLXSW_REG_MFSC_ID, MLXSW_REG_MFSC_LEN);

/* reg_mfsc_pwm
 * Fan pwm to control / monitor.
 * Access: Index
 */
MLXSW_ITEM32(reg, mfsc, pwm, 0x00, 24, 3);

/* reg_mfsc_pwm_duty_cycle
 * Controls the duty cycle of the PWM. Value range from 0..255 to
 * represent duty cycle of 0%...100%.
 * Access: RW
 */
MLXSW_ITEM32(reg, mfsc, pwm_duty_cycle, 0x04, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_mfsc_pack(अक्षर *payload, u8 pwm,
				       u8 pwm_duty_cycle)
अणु
	MLXSW_REG_ZERO(mfsc, payload);
	mlxsw_reg_mfsc_pwm_set(payload, pwm);
	mlxsw_reg_mfsc_pwm_duty_cycle_set(payload, pwm_duty_cycle);
पूर्ण

/* MFSM - Management Fan Speed Measurement
 * ---------------------------------------
 * This रेजिस्टर controls the settings of the Tacho measurements and
 * enables पढ़ोing the Tachometer measurements.
 */
#घोषणा MLXSW_REG_MFSM_ID 0x9003
#घोषणा MLXSW_REG_MFSM_LEN 0x08

MLXSW_REG_DEFINE(mfsm, MLXSW_REG_MFSM_ID, MLXSW_REG_MFSM_LEN);

/* reg_mfsm_tacho
 * Fan tachometer index.
 * Access: Index
 */
MLXSW_ITEM32(reg, mfsm, tacho, 0x00, 24, 4);

/* reg_mfsm_rpm
 * Fan speed (round per minute).
 * Access: RO
 */
MLXSW_ITEM32(reg, mfsm, rpm, 0x04, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mfsm_pack(अक्षर *payload, u8 tacho)
अणु
	MLXSW_REG_ZERO(mfsm, payload);
	mlxsw_reg_mfsm_tacho_set(payload, tacho);
पूर्ण

/* MFSL - Management Fan Speed Limit Register
 * ------------------------------------------
 * The Fan Speed Limit रेजिस्टर is used to configure the fan speed
 * event / पूर्णांकerrupt notअगरication mechanism. Fan speed threshold are
 * defined क्रम both under-speed and over-speed.
 */
#घोषणा MLXSW_REG_MFSL_ID 0x9004
#घोषणा MLXSW_REG_MFSL_LEN 0x0C

MLXSW_REG_DEFINE(mfsl, MLXSW_REG_MFSL_ID, MLXSW_REG_MFSL_LEN);

/* reg_mfsl_tacho
 * Fan tachometer index.
 * Access: Index
 */
MLXSW_ITEM32(reg, mfsl, tacho, 0x00, 24, 4);

/* reg_mfsl_tach_min
 * Tachometer minimum value (minimum RPM).
 * Access: RW
 */
MLXSW_ITEM32(reg, mfsl, tach_min, 0x04, 0, 16);

/* reg_mfsl_tach_max
 * Tachometer maximum value (maximum RPM).
 * Access: RW
 */
MLXSW_ITEM32(reg, mfsl, tach_max, 0x08, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mfsl_pack(अक्षर *payload, u8 tacho,
				       u16 tach_min, u16 tach_max)
अणु
	MLXSW_REG_ZERO(mfsl, payload);
	mlxsw_reg_mfsl_tacho_set(payload, tacho);
	mlxsw_reg_mfsl_tach_min_set(payload, tach_min);
	mlxsw_reg_mfsl_tach_max_set(payload, tach_max);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_mfsl_unpack(अक्षर *payload, u8 tacho,
					 u16 *p_tach_min, u16 *p_tach_max)
अणु
	अगर (p_tach_min)
		*p_tach_min = mlxsw_reg_mfsl_tach_min_get(payload);

	अगर (p_tach_max)
		*p_tach_max = mlxsw_reg_mfsl_tach_max_get(payload);
पूर्ण

/* FORE - Fan Out of Range Event Register
 * --------------------------------------
 * This रेजिस्टर reports the status of the controlled fans compared to the
 * range defined by the MFSL रेजिस्टर.
 */
#घोषणा MLXSW_REG_FORE_ID 0x9007
#घोषणा MLXSW_REG_FORE_LEN 0x0C

MLXSW_REG_DEFINE(क्रमe, MLXSW_REG_FORE_ID, MLXSW_REG_FORE_LEN);

/* fan_under_limit
 * Fan speed is below the low limit defined in MFSL रेजिस्टर. Each bit relates
 * to a single tachometer and indicates the specअगरic tachometer पढ़ोing is
 * below the threshold.
 * Access: RO
 */
MLXSW_ITEM32(reg, क्रमe, fan_under_limit, 0x00, 16, 10);

अटल अंतरभूत व्योम mlxsw_reg_क्रमe_unpack(अक्षर *payload, u8 tacho,
					 bool *fault)
अणु
	u16 limit;

	अगर (fault) अणु
		limit = mlxsw_reg_क्रमe_fan_under_limit_get(payload);
		*fault = limit & BIT(tacho);
	पूर्ण
पूर्ण

/* MTCAP - Management Temperature Capabilities
 * -------------------------------------------
 * This रेजिस्टर exposes the capabilities of the device and
 * प्रणाली temperature sensing.
 */
#घोषणा MLXSW_REG_MTCAP_ID 0x9009
#घोषणा MLXSW_REG_MTCAP_LEN 0x08

MLXSW_REG_DEFINE(mtcap, MLXSW_REG_MTCAP_ID, MLXSW_REG_MTCAP_LEN);

/* reg_mtcap_sensor_count
 * Number of sensors supported by the device.
 * This includes the QSFP module sensors (अगर exists in the QSFP module).
 * Access: RO
 */
MLXSW_ITEM32(reg, mtcap, sensor_count, 0x00, 0, 7);

/* MTMP - Management Temperature
 * -----------------------------
 * This रेजिस्टर controls the settings of the temperature measurements
 * and enables पढ़ोing the temperature measurements. Note that temperature
 * is in 0.125 degrees Celsius.
 */
#घोषणा MLXSW_REG_MTMP_ID 0x900A
#घोषणा MLXSW_REG_MTMP_LEN 0x20

MLXSW_REG_DEFINE(mपंचांगp, MLXSW_REG_MTMP_ID, MLXSW_REG_MTMP_LEN);

#घोषणा MLXSW_REG_MTMP_MODULE_INDEX_MIN 64
#घोषणा MLXSW_REG_MTMP_GBOX_INDEX_MIN 256
/* reg_mपंचांगp_sensor_index
 * Sensors index to access.
 * 64-127 of sensor_index are mapped to the SFP+/QSFP modules sequentially
 * (module 0 is mapped to sensor_index 64).
 * Access: Index
 */
MLXSW_ITEM32(reg, mपंचांगp, sensor_index, 0x00, 0, 12);

/* Convert to milli degrees Celsius */
#घोषणा MLXSW_REG_MTMP_TEMP_TO_MC(val) (अणु typeof(val) v_ = (val); \
					  ((v_) >= 0) ? ((v_) * 125) : \
					  ((s16)((GENMASK(15, 0) + (v_) + 1) \
					   * 125)); पूर्ण)

/* reg_mपंचांगp_temperature
 * Temperature पढ़ोing from the sensor. Reading is in 0.125 Celsius
 * degrees units.
 * Access: RO
 */
MLXSW_ITEM32(reg, mपंचांगp, temperature, 0x04, 0, 16);

/* reg_mपंचांगp_mte
 * Max Temperature Enable - enables measuring the max temperature on a sensor.
 * Access: RW
 */
MLXSW_ITEM32(reg, mपंचांगp, mte, 0x08, 31, 1);

/* reg_mपंचांगp_mtr
 * Max Temperature Reset - clears the value of the max temperature रेजिस्टर.
 * Access: WO
 */
MLXSW_ITEM32(reg, mपंचांगp, mtr, 0x08, 30, 1);

/* reg_mपंचांगp_max_temperature
 * The highest measured temperature from the sensor.
 * When the bit mte is cleared, the field max_temperature is reserved.
 * Access: RO
 */
MLXSW_ITEM32(reg, mपंचांगp, max_temperature, 0x08, 0, 16);

/* reg_mपंचांगp_tee
 * Temperature Event Enable.
 * 0 - Do not generate event
 * 1 - Generate event
 * 2 - Generate single event
 * Access: RW
 */

क्रमागत mlxsw_reg_mपंचांगp_tee अणु
	MLXSW_REG_MTMP_TEE_NO_EVENT,
	MLXSW_REG_MTMP_TEE_GENERATE_EVENT,
	MLXSW_REG_MTMP_TEE_GENERATE_SINGLE_EVENT,
पूर्ण;

MLXSW_ITEM32(reg, mपंचांगp, tee, 0x0C, 30, 2);

#घोषणा MLXSW_REG_MTMP_THRESH_HI 0x348	/* 105 Celsius */

/* reg_mपंचांगp_temperature_threshold_hi
 * High threshold क्रम Temperature Warning Event. In 0.125 Celsius.
 * Access: RW
 */
MLXSW_ITEM32(reg, mपंचांगp, temperature_threshold_hi, 0x0C, 0, 16);

#घोषणा MLXSW_REG_MTMP_HYSTERESIS_TEMP 0x28 /* 5 Celsius */
/* reg_mपंचांगp_temperature_threshold_lo
 * Low threshold क्रम Temperature Warning Event. In 0.125 Celsius.
 * Access: RW
 */
MLXSW_ITEM32(reg, mपंचांगp, temperature_threshold_lo, 0x10, 0, 16);

#घोषणा MLXSW_REG_MTMP_SENSOR_NAME_SIZE 8

/* reg_mपंचांगp_sensor_name
 * Sensor Name
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mपंचांगp, sensor_name, 0x18, MLXSW_REG_MTMP_SENSOR_NAME_SIZE);

अटल अंतरभूत व्योम mlxsw_reg_mपंचांगp_pack(अक्षर *payload, u16 sensor_index,
				       bool max_temp_enable,
				       bool max_temp_reset)
अणु
	MLXSW_REG_ZERO(mपंचांगp, payload);
	mlxsw_reg_mपंचांगp_sensor_index_set(payload, sensor_index);
	mlxsw_reg_mपंचांगp_mte_set(payload, max_temp_enable);
	mlxsw_reg_mपंचांगp_mtr_set(payload, max_temp_reset);
	mlxsw_reg_mपंचांगp_temperature_threshold_hi_set(payload,
						    MLXSW_REG_MTMP_THRESH_HI);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_mपंचांगp_unpack(अक्षर *payload, पूर्णांक *p_temp,
					 पूर्णांक *p_max_temp, अक्षर *sensor_name)
अणु
	s16 temp;

	अगर (p_temp) अणु
		temp = mlxsw_reg_mपंचांगp_temperature_get(payload);
		*p_temp = MLXSW_REG_MTMP_TEMP_TO_MC(temp);
	पूर्ण
	अगर (p_max_temp) अणु
		temp = mlxsw_reg_mपंचांगp_max_temperature_get(payload);
		*p_max_temp = MLXSW_REG_MTMP_TEMP_TO_MC(temp);
	पूर्ण
	अगर (sensor_name)
		mlxsw_reg_mपंचांगp_sensor_name_स_नकल_from(payload, sensor_name);
पूर्ण

/* MTWE - Management Temperature Warning Event
 * -------------------------------------------
 * This रेजिस्टर is used क्रम over temperature warning.
 */
#घोषणा MLXSW_REG_MTWE_ID 0x900B
#घोषणा MLXSW_REG_MTWE_LEN 0x10

MLXSW_REG_DEFINE(mtwe, MLXSW_REG_MTWE_ID, MLXSW_REG_MTWE_LEN);

/* reg_mtwe_sensor_warning
 * Bit vector indicating which of the sensor पढ़ोing is above threshold.
 * Address 00h bit31 is sensor_warning[127].
 * Address 0Ch bit0 is sensor_warning[0].
 * Access: RO
 */
MLXSW_ITEM_BIT_ARRAY(reg, mtwe, sensor_warning, 0x0, 0x10, 1);

/* MTBR - Management Temperature Bulk Register
 * -------------------------------------------
 * This रेजिस्टर is used क्रम bulk temperature पढ़ोing.
 */
#घोषणा MLXSW_REG_MTBR_ID 0x900F
#घोषणा MLXSW_REG_MTBR_BASE_LEN 0x10 /* base length, without records */
#घोषणा MLXSW_REG_MTBR_REC_LEN 0x04 /* record length */
#घोषणा MLXSW_REG_MTBR_REC_MAX_COUNT 47 /* firmware limitation */
#घोषणा MLXSW_REG_MTBR_LEN (MLXSW_REG_MTBR_BASE_LEN +	\
			    MLXSW_REG_MTBR_REC_LEN *	\
			    MLXSW_REG_MTBR_REC_MAX_COUNT)

MLXSW_REG_DEFINE(mtbr, MLXSW_REG_MTBR_ID, MLXSW_REG_MTBR_LEN);

/* reg_mtbr_base_sensor_index
 * Base sensors index to access (0 - ASIC sensor, 1-63 - ambient sensors,
 * 64-127 are mapped to the SFP+/QSFP modules sequentially).
 * Access: Index
 */
MLXSW_ITEM32(reg, mtbr, base_sensor_index, 0x00, 0, 12);

/* reg_mtbr_num_rec
 * Request: Number of records to पढ़ो
 * Response: Number of records पढ़ो
 * See above description क्रम more details.
 * Range 1..255
 * Access: RW
 */
MLXSW_ITEM32(reg, mtbr, num_rec, 0x04, 0, 8);

/* reg_mtbr_rec_max_temp
 * The highest measured temperature from the sensor.
 * When the bit mte is cleared, the field max_temperature is reserved.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtbr, rec_max_temp, MLXSW_REG_MTBR_BASE_LEN, 16,
		     16, MLXSW_REG_MTBR_REC_LEN, 0x00, false);

/* reg_mtbr_rec_temp
 * Temperature पढ़ोing from the sensor. Reading is in 0..125 Celsius
 * degrees units.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtbr, rec_temp, MLXSW_REG_MTBR_BASE_LEN, 0, 16,
		     MLXSW_REG_MTBR_REC_LEN, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_mtbr_pack(अक्षर *payload, u16 base_sensor_index,
				       u8 num_rec)
अणु
	MLXSW_REG_ZERO(mtbr, payload);
	mlxsw_reg_mtbr_base_sensor_index_set(payload, base_sensor_index);
	mlxsw_reg_mtbr_num_rec_set(payload, num_rec);
पूर्ण

/* Error codes from temperatute पढ़ोing */
क्रमागत mlxsw_reg_mtbr_temp_status अणु
	MLXSW_REG_MTBR_NO_CONN		= 0x8000,
	MLXSW_REG_MTBR_NO_TEMP_SENS	= 0x8001,
	MLXSW_REG_MTBR_INDEX_NA		= 0x8002,
	MLXSW_REG_MTBR_BAD_SENS_INFO	= 0x8003,
पूर्ण;

/* Base index क्रम पढ़ोing modules temperature */
#घोषणा MLXSW_REG_MTBR_BASE_MODULE_INDEX 64

अटल अंतरभूत व्योम mlxsw_reg_mtbr_temp_unpack(अक्षर *payload, पूर्णांक rec_ind,
					      u16 *p_temp, u16 *p_max_temp)
अणु
	अगर (p_temp)
		*p_temp = mlxsw_reg_mtbr_rec_temp_get(payload, rec_ind);
	अगर (p_max_temp)
		*p_max_temp = mlxsw_reg_mtbr_rec_max_temp_get(payload, rec_ind);
पूर्ण

/* MCIA - Management Cable Info Access
 * -----------------------------------
 * MCIA रेजिस्टर is used to access the SFP+ and QSFP connector's EPROM.
 */

#घोषणा MLXSW_REG_MCIA_ID 0x9014
#घोषणा MLXSW_REG_MCIA_LEN 0x40

MLXSW_REG_DEFINE(mcia, MLXSW_REG_MCIA_ID, MLXSW_REG_MCIA_LEN);

/* reg_mcia_l
 * Lock bit. Setting this bit will lock the access to the specअगरic
 * cable. Used क्रम updating a full page in a cable EPROM. Any access
 * other then subsequence ग_लिखोs will fail जबतक the port is locked.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcia, l, 0x00, 31, 1);

/* reg_mcia_module
 * Module number.
 * Access: Index
 */
MLXSW_ITEM32(reg, mcia, module, 0x00, 16, 8);

/* reg_mcia_status
 * Module status.
 * Access: RO
 */
MLXSW_ITEM32(reg, mcia, status, 0x00, 0, 8);

/* reg_mcia_i2c_device_address
 * I2C device address.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcia, i2c_device_address, 0x04, 24, 8);

/* reg_mcia_page_number
 * Page number.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcia, page_number, 0x04, 16, 8);

/* reg_mcia_device_address
 * Device address.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcia, device_address, 0x04, 0, 16);

/* reg_mcia_size
 * Number of bytes to पढ़ो/ग_लिखो (up to 48 bytes).
 * Access: RW
 */
MLXSW_ITEM32(reg, mcia, size, 0x08, 0, 16);

#घोषणा MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH	256
#घोषणा MLXSW_REG_MCIA_EEPROM_UP_PAGE_LENGTH	128
#घोषणा MLXSW_REG_MCIA_EEPROM_SIZE		48
#घोषणा MLXSW_REG_MCIA_I2C_ADDR_LOW		0x50
#घोषणा MLXSW_REG_MCIA_I2C_ADDR_HIGH		0x51
#घोषणा MLXSW_REG_MCIA_PAGE0_LO_OFF		0xa0
#घोषणा MLXSW_REG_MCIA_TH_ITEM_SIZE		2
#घोषणा MLXSW_REG_MCIA_TH_PAGE_NUM		3
#घोषणा MLXSW_REG_MCIA_TH_PAGE_CMIS_NUM		2
#घोषणा MLXSW_REG_MCIA_PAGE0_LO			0
#घोषणा MLXSW_REG_MCIA_TH_PAGE_OFF		0x80
#घोषणा MLXSW_REG_MCIA_EEPROM_CMIS_FLAT_MEMORY	BIT(7)

क्रमागत mlxsw_reg_mcia_eeprom_module_info_rev_id अणु
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_UNSPC	= 0x00,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_8436	= 0x01,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID_8636	= 0x03,
पूर्ण;

क्रमागत mlxsw_reg_mcia_eeprom_module_info_id अणु
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_SFP	= 0x03,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP	= 0x0C,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_PLUS	= 0x0D,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP28	= 0x11,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID_QSFP_DD	= 0x18,
पूर्ण;

क्रमागत mlxsw_reg_mcia_eeprom_module_info अणु
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_ID,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_REV_ID,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_TYPE_ID,
	MLXSW_REG_MCIA_EEPROM_MODULE_INFO_SIZE,
पूर्ण;

/* reg_mcia_eeprom
 * Bytes to पढ़ो/ग_लिखो.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mcia, eeprom, 0x10, MLXSW_REG_MCIA_EEPROM_SIZE);

/* This is used to access the optional upper pages (1-3) in the QSFP+
 * memory map. Page 1 is available on offset 256 through 383, page 2 -
 * on offset 384 through 511, page 3 - on offset 512 through 639.
 */
#घोषणा MLXSW_REG_MCIA_PAGE_GET(off) (((off) - \
				MLXSW_REG_MCIA_EEPROM_PAGE_LENGTH) / \
				MLXSW_REG_MCIA_EEPROM_UP_PAGE_LENGTH + 1)

अटल अंतरभूत व्योम mlxsw_reg_mcia_pack(अक्षर *payload, u8 module, u8 lock,
				       u8 page_number, u16 device_addr,
				       u8 size, u8 i2c_device_addr)
अणु
	MLXSW_REG_ZERO(mcia, payload);
	mlxsw_reg_mcia_module_set(payload, module);
	mlxsw_reg_mcia_l_set(payload, lock);
	mlxsw_reg_mcia_page_number_set(payload, page_number);
	mlxsw_reg_mcia_device_address_set(payload, device_addr);
	mlxsw_reg_mcia_size_set(payload, size);
	mlxsw_reg_mcia_i2c_device_address_set(payload, i2c_device_addr);
पूर्ण

/* MPAT - Monitoring Port Analyzer Table
 * -------------------------------------
 * MPAT Register is used to query and configure the Switch PortAnalyzer Table.
 * For an enabled analyzer, all fields except e (enable) cannot be modअगरied.
 */
#घोषणा MLXSW_REG_MPAT_ID 0x901A
#घोषणा MLXSW_REG_MPAT_LEN 0x78

MLXSW_REG_DEFINE(mpat, MLXSW_REG_MPAT_ID, MLXSW_REG_MPAT_LEN);

/* reg_mpat_pa_id
 * Port Analyzer ID.
 * Access: Index
 */
MLXSW_ITEM32(reg, mpat, pa_id, 0x00, 28, 4);

/* reg_mpat_session_id
 * Mirror Session ID.
 * Used क्रम MIRROR_SESSION<i> trap.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, session_id, 0x00, 24, 4);

/* reg_mpat_प्रणाली_port
 * A unique port identअगरier क्रम the final destination of the packet.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, प्रणाली_port, 0x00, 0, 16);

/* reg_mpat_e
 * Enable. Indicating the Port Analyzer is enabled.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, e, 0x04, 31, 1);

/* reg_mpat_qos
 * Quality Of Service Mode.
 * 0: CONFIGURED - QoS parameters (Switch Priority, and encapsulation
 * PCP, DEI, DSCP or VL) are configured.
 * 1: MAINTAIN - QoS parameters (Switch Priority, Color) are the
 * same as in the original packet that has triggered the mirroring. For
 * SPAN also the pcp,dei are मुख्यtained.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, qos, 0x04, 26, 1);

/* reg_mpat_be
 * Best efक्रमt mode. Indicates mirroring traffic should not cause packet
 * drop or back pressure, but will discard the mirrored packets. Mirrored
 * packets will be क्रमwarded on a best efक्रमt manner.
 * 0: Do not discard mirrored packets
 * 1: Discard mirrored packets अगर causing congestion
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, be, 0x04, 25, 1);

क्रमागत mlxsw_reg_mpat_span_type अणु
	/* Local SPAN Ethernet.
	 * The original packet is not encapsulated.
	 */
	MLXSW_REG_MPAT_SPAN_TYPE_LOCAL_ETH = 0x0,

	/* Remote SPAN Ethernet VLAN.
	 * The packet is क्रमwarded to the monitoring port on the monitoring
	 * VLAN.
	 */
	MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH = 0x1,

	/* Encapsulated Remote SPAN Ethernet L3 GRE.
	 * The packet is encapsulated with GRE header.
	 */
	MLXSW_REG_MPAT_SPAN_TYPE_REMOTE_ETH_L3 = 0x3,
पूर्ण;

/* reg_mpat_span_type
 * SPAN type.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, span_type, 0x04, 0, 4);

/* reg_mpat_pide
 * Policer enable.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, pide, 0x0C, 15, 1);

/* reg_mpat_pid
 * Policer ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, pid, 0x0C, 0, 14);

/* Remote SPAN - Ethernet VLAN
 * - - - - - - - - - - - - - -
 */

/* reg_mpat_eth_rspan_vid
 * Encapsulation header VLAN ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_vid, 0x18, 0, 12);

/* Encapsulated Remote SPAN - Ethernet L2
 * - - - - - - - - - - - - - - - - - - -
 */

क्रमागत mlxsw_reg_mpat_eth_rspan_version अणु
	MLXSW_REG_MPAT_ETH_RSPAN_VERSION_NO_HEADER = 15,
पूर्ण;

/* reg_mpat_eth_rspan_version
 * RSPAN mirror header version.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_version, 0x10, 18, 4);

/* reg_mpat_eth_rspan_mac
 * Destination MAC address.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mpat, eth_rspan_mac, 0x12, 6);

/* reg_mpat_eth_rspan_tp
 * Tag Packet. Indicates whether the mirroring header should be VLAN tagged.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_tp, 0x18, 16, 1);

/* Encapsulated Remote SPAN - Ethernet L3
 * - - - - - - - - - - - - - - - - - - -
 */

क्रमागत mlxsw_reg_mpat_eth_rspan_protocol अणु
	MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV4,
	MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV6,
पूर्ण;

/* reg_mpat_eth_rspan_protocol
 * SPAN encapsulation protocol.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_protocol, 0x18, 24, 4);

/* reg_mpat_eth_rspan_ttl
 * Encapsulation header Time-to-Live/HopLimit.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_ttl, 0x1C, 4, 8);

/* reg_mpat_eth_rspan_smac
 * Source MAC address
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, mpat, eth_rspan_smac, 0x22, 6);

/* reg_mpat_eth_rspan_dip*
 * Destination IP address. The IP version is configured by protocol.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_dip4, 0x4C, 0, 32);
MLXSW_ITEM_BUF(reg, mpat, eth_rspan_dip6, 0x40, 16);

/* reg_mpat_eth_rspan_sip*
 * Source IP address. The IP version is configured by protocol.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpat, eth_rspan_sip4, 0x5C, 0, 32);
MLXSW_ITEM_BUF(reg, mpat, eth_rspan_sip6, 0x50, 16);

अटल अंतरभूत व्योम mlxsw_reg_mpat_pack(अक्षर *payload, u8 pa_id,
				       u16 प्रणाली_port, bool e,
				       क्रमागत mlxsw_reg_mpat_span_type span_type)
अणु
	MLXSW_REG_ZERO(mpat, payload);
	mlxsw_reg_mpat_pa_id_set(payload, pa_id);
	mlxsw_reg_mpat_प्रणाली_port_set(payload, प्रणाली_port);
	mlxsw_reg_mpat_e_set(payload, e);
	mlxsw_reg_mpat_qos_set(payload, 1);
	mlxsw_reg_mpat_be_set(payload, 1);
	mlxsw_reg_mpat_span_type_set(payload, span_type);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_mpat_eth_rspan_pack(अक्षर *payload, u16 vid)
अणु
	mlxsw_reg_mpat_eth_rspan_vid_set(payload, vid);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mpat_eth_rspan_l2_pack(अक्षर *payload,
				 क्रमागत mlxsw_reg_mpat_eth_rspan_version version,
				 स्थिर अक्षर *mac,
				 bool tp)
अणु
	mlxsw_reg_mpat_eth_rspan_version_set(payload, version);
	mlxsw_reg_mpat_eth_rspan_mac_स_नकल_to(payload, mac);
	mlxsw_reg_mpat_eth_rspan_tp_set(payload, tp);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mpat_eth_rspan_l3_ipv4_pack(अक्षर *payload, u8 ttl,
				      स्थिर अक्षर *smac,
				      u32 sip, u32 dip)
अणु
	mlxsw_reg_mpat_eth_rspan_ttl_set(payload, ttl);
	mlxsw_reg_mpat_eth_rspan_smac_स_नकल_to(payload, smac);
	mlxsw_reg_mpat_eth_rspan_protocol_set(payload,
				    MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV4);
	mlxsw_reg_mpat_eth_rspan_sip4_set(payload, sip);
	mlxsw_reg_mpat_eth_rspan_dip4_set(payload, dip);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mpat_eth_rspan_l3_ipv6_pack(अक्षर *payload, u8 ttl,
				      स्थिर अक्षर *smac,
				      काष्ठा in6_addr sip, काष्ठा in6_addr dip)
अणु
	mlxsw_reg_mpat_eth_rspan_ttl_set(payload, ttl);
	mlxsw_reg_mpat_eth_rspan_smac_स_नकल_to(payload, smac);
	mlxsw_reg_mpat_eth_rspan_protocol_set(payload,
				    MLXSW_REG_MPAT_ETH_RSPAN_PROTOCOL_IPV6);
	mlxsw_reg_mpat_eth_rspan_sip6_स_नकल_to(payload, (व्योम *)&sip);
	mlxsw_reg_mpat_eth_rspan_dip6_स_नकल_to(payload, (व्योम *)&dip);
पूर्ण

/* MPAR - Monitoring Port Analyzer Register
 * ----------------------------------------
 * MPAR रेजिस्टर is used to query and configure the port analyzer port mirroring
 * properties.
 */
#घोषणा MLXSW_REG_MPAR_ID 0x901B
#घोषणा MLXSW_REG_MPAR_LEN 0x0C

MLXSW_REG_DEFINE(mpar, MLXSW_REG_MPAR_ID, MLXSW_REG_MPAR_LEN);

/* reg_mpar_local_port
 * The local port to mirror the packets from.
 * Access: Index
 */
MLXSW_ITEM32(reg, mpar, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_mpar_i_e अणु
	MLXSW_REG_MPAR_TYPE_EGRESS,
	MLXSW_REG_MPAR_TYPE_INGRESS,
पूर्ण;

/* reg_mpar_i_e
 * Ingress/Egress
 * Access: Index
 */
MLXSW_ITEM32(reg, mpar, i_e, 0x00, 0, 4);

/* reg_mpar_enable
 * Enable mirroring
 * By शेष, port mirroring is disabled क्रम all ports.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpar, enable, 0x04, 31, 1);

/* reg_mpar_pa_id
 * Port Analyzer ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpar, pa_id, 0x04, 0, 4);

#घोषणा MLXSW_REG_MPAR_RATE_MAX 3500000000UL

/* reg_mpar_probability_rate
 * Sampling rate.
 * Valid values are: 1 to 3.5*10^9
 * Value of 1 means "sample all". Default is 1.
 * Reserved when Spectrum-1.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpar, probability_rate, 0x08, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_mpar_pack(अक्षर *payload, u8 local_port,
				       क्रमागत mlxsw_reg_mpar_i_e i_e,
				       bool enable, u8 pa_id,
				       u32 probability_rate)
अणु
	MLXSW_REG_ZERO(mpar, payload);
	mlxsw_reg_mpar_local_port_set(payload, local_port);
	mlxsw_reg_mpar_enable_set(payload, enable);
	mlxsw_reg_mpar_i_e_set(payload, i_e);
	mlxsw_reg_mpar_pa_id_set(payload, pa_id);
	mlxsw_reg_mpar_probability_rate_set(payload, probability_rate);
पूर्ण

/* MGIR - Management General Inक्रमmation Register
 * ----------------------------------------------
 * MGIR रेजिस्टर allows software to query the hardware and firmware general
 * inक्रमmation.
 */
#घोषणा MLXSW_REG_MGIR_ID 0x9020
#घोषणा MLXSW_REG_MGIR_LEN 0x9C

MLXSW_REG_DEFINE(mgir, MLXSW_REG_MGIR_ID, MLXSW_REG_MGIR_LEN);

/* reg_mgir_hw_info_device_hw_revision
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, hw_info_device_hw_revision, 0x0, 16, 16);

#घोषणा MLXSW_REG_MGIR_FW_INFO_PSID_SIZE 16

/* reg_mgir_fw_info_psid
 * PSID (ASCII string).
 * Access: RO
 */
MLXSW_ITEM_BUF(reg, mgir, fw_info_psid, 0x30, MLXSW_REG_MGIR_FW_INFO_PSID_SIZE);

/* reg_mgir_fw_info_extended_major
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_major, 0x44, 0, 32);

/* reg_mgir_fw_info_extended_minor
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_minor, 0x48, 0, 32);

/* reg_mgir_fw_info_extended_sub_minor
 * Access: RO
 */
MLXSW_ITEM32(reg, mgir, fw_info_extended_sub_minor, 0x4C, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_mgir_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(mgir, payload);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mgir_unpack(अक्षर *payload, u32 *hw_rev, अक्षर *fw_info_psid,
		      u32 *fw_major, u32 *fw_minor, u32 *fw_sub_minor)
अणु
	*hw_rev = mlxsw_reg_mgir_hw_info_device_hw_revision_get(payload);
	mlxsw_reg_mgir_fw_info_psid_स_नकल_from(payload, fw_info_psid);
	*fw_major = mlxsw_reg_mgir_fw_info_extended_major_get(payload);
	*fw_minor = mlxsw_reg_mgir_fw_info_extended_minor_get(payload);
	*fw_sub_minor = mlxsw_reg_mgir_fw_info_extended_sub_minor_get(payload);
पूर्ण

/* MRSR - Management Reset and Shutकरोwn Register
 * ---------------------------------------------
 * MRSR रेजिस्टर is used to reset or shutकरोwn the चयन or
 * the entire प्रणाली (when applicable).
 */
#घोषणा MLXSW_REG_MRSR_ID 0x9023
#घोषणा MLXSW_REG_MRSR_LEN 0x08

MLXSW_REG_DEFINE(mrsr, MLXSW_REG_MRSR_ID, MLXSW_REG_MRSR_LEN);

/* reg_mrsr_command
 * Reset/shutकरोwn command
 * 0 - करो nothing
 * 1 - software reset
 * Access: WO
 */
MLXSW_ITEM32(reg, mrsr, command, 0x00, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_mrsr_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(mrsr, payload);
	mlxsw_reg_mrsr_command_set(payload, 1);
पूर्ण

/* MLCR - Management LED Control Register
 * --------------------------------------
 * Controls the प्रणाली LEDs.
 */
#घोषणा MLXSW_REG_MLCR_ID 0x902B
#घोषणा MLXSW_REG_MLCR_LEN 0x0C

MLXSW_REG_DEFINE(mlcr, MLXSW_REG_MLCR_ID, MLXSW_REG_MLCR_LEN);

/* reg_mlcr_local_port
 * Local port number.
 * Access: RW
 */
MLXSW_ITEM32(reg, mlcr, local_port, 0x00, 16, 8);

#घोषणा MLXSW_REG_MLCR_DURATION_MAX 0xFFFF

/* reg_mlcr_beacon_duration
 * Duration of the beacon to be active, in seconds.
 * 0x0 - Will turn off the beacon.
 * 0xFFFF - Will turn on the beacon until explicitly turned off.
 * Access: RW
 */
MLXSW_ITEM32(reg, mlcr, beacon_duration, 0x04, 0, 16);

/* reg_mlcr_beacon_reमुख्य
 * Reमुख्यing duration of the beacon, in seconds.
 * 0xFFFF indicates an infinite amount of समय.
 * Access: RO
 */
MLXSW_ITEM32(reg, mlcr, beacon_reमुख्य, 0x08, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mlcr_pack(अक्षर *payload, u8 local_port,
				       bool active)
अणु
	MLXSW_REG_ZERO(mlcr, payload);
	mlxsw_reg_mlcr_local_port_set(payload, local_port);
	mlxsw_reg_mlcr_beacon_duration_set(payload, active ?
					   MLXSW_REG_MLCR_DURATION_MAX : 0);
पूर्ण

/* MTPPS - Management Pulse Per Second Register
 * --------------------------------------------
 * This रेजिस्टर provides the device PPS capabilities, configure the PPS in and
 * out modules and holds the PPS in समय stamp.
 */
#घोषणा MLXSW_REG_MTPPS_ID 0x9053
#घोषणा MLXSW_REG_MTPPS_LEN 0x3C

MLXSW_REG_DEFINE(mtpps, MLXSW_REG_MTPPS_ID, MLXSW_REG_MTPPS_LEN);

/* reg_mtpps_enable
 * Enables the PPS functionality the specअगरic pin.
 * A boolean variable.
 * Access: RW
 */
MLXSW_ITEM32(reg, mtpps, enable, 0x20, 31, 1);

क्रमागत mlxsw_reg_mtpps_pin_mode अणु
	MLXSW_REG_MTPPS_PIN_MODE_VIRTUAL_PIN = 0x2,
पूर्ण;

/* reg_mtpps_pin_mode
 * Pin mode to be used. The mode must comply with the supported modes of the
 * requested pin.
 * Access: RW
 */
MLXSW_ITEM32(reg, mtpps, pin_mode, 0x20, 8, 4);

#घोषणा MLXSW_REG_MTPPS_PIN_SP_VIRTUAL_PIN	7

/* reg_mtpps_pin
 * Pin to be configured or queried out of the supported pins.
 * Access: Index
 */
MLXSW_ITEM32(reg, mtpps, pin, 0x20, 0, 8);

/* reg_mtpps_समय_stamp
 * When pin_mode = pps_in, the latched device समय when it was triggered from
 * the बाह्यal GPIO pin.
 * When pin_mode = pps_out or भव_pin or pps_out_and_भव_pin, the target
 * समय to generate next output संकेत.
 * Time is in units of device घड़ी.
 * Access: RW
 */
MLXSW_ITEM64(reg, mtpps, समय_stamp, 0x28, 0, 64);

अटल अंतरभूत व्योम
mlxsw_reg_mtpps_vpin_pack(अक्षर *payload, u64 समय_stamp)
अणु
	MLXSW_REG_ZERO(mtpps, payload);
	mlxsw_reg_mtpps_pin_set(payload, MLXSW_REG_MTPPS_PIN_SP_VIRTUAL_PIN);
	mlxsw_reg_mtpps_pin_mode_set(payload,
				     MLXSW_REG_MTPPS_PIN_MODE_VIRTUAL_PIN);
	mlxsw_reg_mtpps_enable_set(payload, true);
	mlxsw_reg_mtpps_समय_stamp_set(payload, समय_stamp);
पूर्ण

/* MTUTC - Management UTC Register
 * -------------------------------
 * Configures the HW UTC counter.
 */
#घोषणा MLXSW_REG_MTUTC_ID 0x9055
#घोषणा MLXSW_REG_MTUTC_LEN 0x1C

MLXSW_REG_DEFINE(mtutc, MLXSW_REG_MTUTC_ID, MLXSW_REG_MTUTC_LEN);

क्रमागत mlxsw_reg_mtutc_operation अणु
	MLXSW_REG_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC = 0,
	MLXSW_REG_MTUTC_OPERATION_ADJUST_FREQ = 3,
पूर्ण;

/* reg_mtutc_operation
 * Operation.
 * Access: OP
 */
MLXSW_ITEM32(reg, mtutc, operation, 0x00, 0, 4);

/* reg_mtutc_freq_adjusपंचांगent
 * Frequency adjusपंचांगent: Every PPS the HW frequency will be
 * adjusted by this value. Units of HW घड़ी, where HW counts
 * 10^9 HW घड़ीs क्रम 1 HW second.
 * Access: RW
 */
MLXSW_ITEM32(reg, mtutc, freq_adjusपंचांगent, 0x04, 0, 32);

/* reg_mtutc_utc_sec
 * UTC seconds.
 * Access: WO
 */
MLXSW_ITEM32(reg, mtutc, utc_sec, 0x10, 0, 32);

अटल अंतरभूत व्योम
mlxsw_reg_mtutc_pack(अक्षर *payload, क्रमागत mlxsw_reg_mtutc_operation oper,
		     u32 freq_adj, u32 utc_sec)
अणु
	MLXSW_REG_ZERO(mtutc, payload);
	mlxsw_reg_mtutc_operation_set(payload, oper);
	mlxsw_reg_mtutc_freq_adjusपंचांगent_set(payload, freq_adj);
	mlxsw_reg_mtutc_utc_sec_set(payload, utc_sec);
पूर्ण

/* MCQI - Management Component Query Inक्रमmation
 * ---------------------------------------------
 * This रेजिस्टर allows querying inक्रमmation about firmware components.
 */
#घोषणा MLXSW_REG_MCQI_ID 0x9061
#घोषणा MLXSW_REG_MCQI_BASE_LEN 0x18
#घोषणा MLXSW_REG_MCQI_CAP_LEN 0x14
#घोषणा MLXSW_REG_MCQI_LEN (MLXSW_REG_MCQI_BASE_LEN + MLXSW_REG_MCQI_CAP_LEN)

MLXSW_REG_DEFINE(mcqi, MLXSW_REG_MCQI_ID, MLXSW_REG_MCQI_LEN);

/* reg_mcqi_component_index
 * Index of the accessed component.
 * Access: Index
 */
MLXSW_ITEM32(reg, mcqi, component_index, 0x00, 0, 16);

क्रमागत mlxfw_reg_mcqi_info_type अणु
	MLXSW_REG_MCQI_INFO_TYPE_CAPABILITIES,
पूर्ण;

/* reg_mcqi_info_type
 * Component properties set.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, info_type, 0x08, 0, 5);

/* reg_mcqi_offset
 * The requested/वापसed data offset from the section start, given in bytes.
 * Must be DWORD aligned.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, offset, 0x10, 0, 32);

/* reg_mcqi_data_size
 * The requested/वापसed data size, given in bytes. If data_size is not DWORD
 * aligned, the last bytes are zero padded.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcqi, data_size, 0x14, 0, 16);

/* reg_mcqi_cap_max_component_size
 * Maximum size क्रम this component, given in bytes.
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, cap_max_component_size, 0x20, 0, 32);

/* reg_mcqi_cap_log_mcda_word_size
 * Log 2 of the access word size in bytes. Read and ग_लिखो access must be aligned
 * to the word size. Write access must be करोne क्रम an पूर्णांकeger number of words.
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, cap_log_mcda_word_size, 0x24, 28, 4);

/* reg_mcqi_cap_mcda_max_ग_लिखो_size
 * Maximal ग_लिखो size क्रम MCDA रेजिस्टर
 * Access: RO
 */
MLXSW_ITEM32(reg, mcqi, cap_mcda_max_ग_लिखो_size, 0x24, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mcqi_pack(अक्षर *payload, u16 component_index)
अणु
	MLXSW_REG_ZERO(mcqi, payload);
	mlxsw_reg_mcqi_component_index_set(payload, component_index);
	mlxsw_reg_mcqi_info_type_set(payload,
				     MLXSW_REG_MCQI_INFO_TYPE_CAPABILITIES);
	mlxsw_reg_mcqi_offset_set(payload, 0);
	mlxsw_reg_mcqi_data_size_set(payload, MLXSW_REG_MCQI_CAP_LEN);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_mcqi_unpack(अक्षर *payload,
					 u32 *p_cap_max_component_size,
					 u8 *p_cap_log_mcda_word_size,
					 u16 *p_cap_mcda_max_ग_लिखो_size)
अणु
	*p_cap_max_component_size =
		mlxsw_reg_mcqi_cap_max_component_size_get(payload);
	*p_cap_log_mcda_word_size =
		mlxsw_reg_mcqi_cap_log_mcda_word_size_get(payload);
	*p_cap_mcda_max_ग_लिखो_size =
		mlxsw_reg_mcqi_cap_mcda_max_ग_लिखो_size_get(payload);
पूर्ण

/* MCC - Management Component Control
 * ----------------------------------
 * Controls the firmware component and updates the FSM.
 */
#घोषणा MLXSW_REG_MCC_ID 0x9062
#घोषणा MLXSW_REG_MCC_LEN 0x1C

MLXSW_REG_DEFINE(mcc, MLXSW_REG_MCC_ID, MLXSW_REG_MCC_LEN);

क्रमागत mlxsw_reg_mcc_inकाष्ठाion अणु
	MLXSW_REG_MCC_INSTRUCTION_LOCK_UPDATE_HANDLE = 0x01,
	MLXSW_REG_MCC_INSTRUCTION_RELEASE_UPDATE_HANDLE = 0x02,
	MLXSW_REG_MCC_INSTRUCTION_UPDATE_COMPONENT = 0x03,
	MLXSW_REG_MCC_INSTRUCTION_VERIFY_COMPONENT = 0x04,
	MLXSW_REG_MCC_INSTRUCTION_ACTIVATE = 0x06,
	MLXSW_REG_MCC_INSTRUCTION_CANCEL = 0x08,
पूर्ण;

/* reg_mcc_inकाष्ठाion
 * Command to be executed by the FSM.
 * Applicable क्रम ग_लिखो operation only.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcc, inकाष्ठाion, 0x00, 0, 8);

/* reg_mcc_component_index
 * Index of the accessed component. Applicable only क्रम commands that
 * refer to components. Otherwise, this field is reserved.
 * Access: Index
 */
MLXSW_ITEM32(reg, mcc, component_index, 0x04, 0, 16);

/* reg_mcc_update_handle
 * Token representing the current flow executed by the FSM.
 * Access: WO
 */
MLXSW_ITEM32(reg, mcc, update_handle, 0x08, 0, 24);

/* reg_mcc_error_code
 * Indicates the successful completion of the inकाष्ठाion, or the reason it
 * failed
 * Access: RO
 */
MLXSW_ITEM32(reg, mcc, error_code, 0x0C, 8, 8);

/* reg_mcc_control_state
 * Current FSM state
 * Access: RO
 */
MLXSW_ITEM32(reg, mcc, control_state, 0x0C, 0, 4);

/* reg_mcc_component_size
 * Component size in bytes. Valid क्रम UPDATE_COMPONENT inकाष्ठाion. Specअगरying
 * the size may लघुen the update समय. Value 0x0 means that size is
 * unspecअगरied.
 * Access: WO
 */
MLXSW_ITEM32(reg, mcc, component_size, 0x10, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_mcc_pack(अक्षर *payload,
				      क्रमागत mlxsw_reg_mcc_inकाष्ठाion instr,
				      u16 component_index, u32 update_handle,
				      u32 component_size)
अणु
	MLXSW_REG_ZERO(mcc, payload);
	mlxsw_reg_mcc_inकाष्ठाion_set(payload, instr);
	mlxsw_reg_mcc_component_index_set(payload, component_index);
	mlxsw_reg_mcc_update_handle_set(payload, update_handle);
	mlxsw_reg_mcc_component_size_set(payload, component_size);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_mcc_unpack(अक्षर *payload, u32 *p_update_handle,
					u8 *p_error_code, u8 *p_control_state)
अणु
	अगर (p_update_handle)
		*p_update_handle = mlxsw_reg_mcc_update_handle_get(payload);
	अगर (p_error_code)
		*p_error_code = mlxsw_reg_mcc_error_code_get(payload);
	अगर (p_control_state)
		*p_control_state = mlxsw_reg_mcc_control_state_get(payload);
पूर्ण

/* MCDA - Management Component Data Access
 * ---------------------------------------
 * This रेजिस्टर allows पढ़ोing and writing a firmware component.
 */
#घोषणा MLXSW_REG_MCDA_ID 0x9063
#घोषणा MLXSW_REG_MCDA_BASE_LEN 0x10
#घोषणा MLXSW_REG_MCDA_MAX_DATA_LEN 0x80
#घोषणा MLXSW_REG_MCDA_LEN \
		(MLXSW_REG_MCDA_BASE_LEN + MLXSW_REG_MCDA_MAX_DATA_LEN)

MLXSW_REG_DEFINE(mcda, MLXSW_REG_MCDA_ID, MLXSW_REG_MCDA_LEN);

/* reg_mcda_update_handle
 * Token representing the current flow executed by the FSM.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcda, update_handle, 0x00, 0, 24);

/* reg_mcda_offset
 * Offset of accessed address relative to component start. Accesses must be in
 * accordance to log_mcda_word_size in MCQI reg.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcda, offset, 0x04, 0, 32);

/* reg_mcda_size
 * Size of the data accessed, given in bytes.
 * Access: RW
 */
MLXSW_ITEM32(reg, mcda, size, 0x08, 0, 16);

/* reg_mcda_data
 * Data block accessed.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, mcda, data, 0x10, 0, 32, 4, 0, false);

अटल अंतरभूत व्योम mlxsw_reg_mcda_pack(अक्षर *payload, u32 update_handle,
				       u32 offset, u16 size, u8 *data)
अणु
	पूर्णांक i;

	MLXSW_REG_ZERO(mcda, payload);
	mlxsw_reg_mcda_update_handle_set(payload, update_handle);
	mlxsw_reg_mcda_offset_set(payload, offset);
	mlxsw_reg_mcda_size_set(payload, size);

	क्रम (i = 0; i < size / 4; i++)
		mlxsw_reg_mcda_data_set(payload, i, *(u32 *) &data[i * 4]);
पूर्ण

/* MPSC - Monitoring Packet Sampling Configuration Register
 * --------------------------------------------------------
 * MPSC Register is used to configure the Packet Sampling mechanism.
 */
#घोषणा MLXSW_REG_MPSC_ID 0x9080
#घोषणा MLXSW_REG_MPSC_LEN 0x1C

MLXSW_REG_DEFINE(mpsc, MLXSW_REG_MPSC_ID, MLXSW_REG_MPSC_LEN);

/* reg_mpsc_local_port
 * Local port number
 * Not supported क्रम CPU port
 * Access: Index
 */
MLXSW_ITEM32(reg, mpsc, local_port, 0x00, 16, 8);

/* reg_mpsc_e
 * Enable sampling on port local_port
 * Access: RW
 */
MLXSW_ITEM32(reg, mpsc, e, 0x04, 30, 1);

#घोषणा MLXSW_REG_MPSC_RATE_MAX 3500000000UL

/* reg_mpsc_rate
 * Sampling rate = 1 out of rate packets (with अक्रमomization around
 * the poपूर्णांक). Valid values are: 1 to MLXSW_REG_MPSC_RATE_MAX
 * Access: RW
 */
MLXSW_ITEM32(reg, mpsc, rate, 0x08, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_mpsc_pack(अक्षर *payload, u8 local_port, bool e,
				       u32 rate)
अणु
	MLXSW_REG_ZERO(mpsc, payload);
	mlxsw_reg_mpsc_local_port_set(payload, local_port);
	mlxsw_reg_mpsc_e_set(payload, e);
	mlxsw_reg_mpsc_rate_set(payload, rate);
पूर्ण

/* MGPC - Monitoring General Purpose Counter Set Register
 * The MGPC रेजिस्टर retrieves and sets the General Purpose Counter Set.
 */
#घोषणा MLXSW_REG_MGPC_ID 0x9081
#घोषणा MLXSW_REG_MGPC_LEN 0x18

MLXSW_REG_DEFINE(mgpc, MLXSW_REG_MGPC_ID, MLXSW_REG_MGPC_LEN);

/* reg_mgpc_counter_set_type
 * Counter set type.
 * Access: OP
 */
MLXSW_ITEM32(reg, mgpc, counter_set_type, 0x00, 24, 8);

/* reg_mgpc_counter_index
 * Counter index.
 * Access: Index
 */
MLXSW_ITEM32(reg, mgpc, counter_index, 0x00, 0, 24);

क्रमागत mlxsw_reg_mgpc_opcode अणु
	/* Nop */
	MLXSW_REG_MGPC_OPCODE_NOP = 0x00,
	/* Clear counters */
	MLXSW_REG_MGPC_OPCODE_CLEAR = 0x08,
पूर्ण;

/* reg_mgpc_opcode
 * Opcode.
 * Access: OP
 */
MLXSW_ITEM32(reg, mgpc, opcode, 0x04, 28, 4);

/* reg_mgpc_byte_counter
 * Byte counter value.
 * Access: RW
 */
MLXSW_ITEM64(reg, mgpc, byte_counter, 0x08, 0, 64);

/* reg_mgpc_packet_counter
 * Packet counter value.
 * Access: RW
 */
MLXSW_ITEM64(reg, mgpc, packet_counter, 0x10, 0, 64);

अटल अंतरभूत व्योम mlxsw_reg_mgpc_pack(अक्षर *payload, u32 counter_index,
				       क्रमागत mlxsw_reg_mgpc_opcode opcode,
				       क्रमागत mlxsw_reg_flow_counter_set_type set_type)
अणु
	MLXSW_REG_ZERO(mgpc, payload);
	mlxsw_reg_mgpc_counter_index_set(payload, counter_index);
	mlxsw_reg_mgpc_counter_set_type_set(payload, set_type);
	mlxsw_reg_mgpc_opcode_set(payload, opcode);
पूर्ण

/* MPRS - Monitoring Parsing State Register
 * ----------------------------------------
 * The MPRS रेजिस्टर is used क्रम setting up the parsing क्रम hash,
 * policy-engine and routing.
 */
#घोषणा MLXSW_REG_MPRS_ID 0x9083
#घोषणा MLXSW_REG_MPRS_LEN 0x14

MLXSW_REG_DEFINE(mprs, MLXSW_REG_MPRS_ID, MLXSW_REG_MPRS_LEN);

/* reg_mprs_parsing_depth
 * Minimum parsing depth.
 * Need to enlarge parsing depth according to L3, MPLS, tunnels, ACL
 * rules, traps, hash, etc. Default is 96 bytes. Reserved when SwitchX-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, mprs, parsing_depth, 0x00, 0, 16);

/* reg_mprs_parsing_en
 * Parsing enable.
 * Bit 0 - Enable parsing of NVE of types VxLAN, VxLAN-GPE, GENEVE and
 * NVGRE. Default is enabled. Reserved when SwitchX-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, mprs, parsing_en, 0x04, 0, 16);

/* reg_mprs_vxlan_udp_dport
 * VxLAN UDP destination port.
 * Used क्रम identअगरying VxLAN packets and क्रम dport field in
 * encapsulation. Default is 4789.
 * Access: RW
 */
MLXSW_ITEM32(reg, mprs, vxlan_udp_dport, 0x10, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mprs_pack(अक्षर *payload, u16 parsing_depth,
				       u16 vxlan_udp_dport)
अणु
	MLXSW_REG_ZERO(mprs, payload);
	mlxsw_reg_mprs_parsing_depth_set(payload, parsing_depth);
	mlxsw_reg_mprs_parsing_en_set(payload, true);
	mlxsw_reg_mprs_vxlan_udp_dport_set(payload, vxlan_udp_dport);
पूर्ण

/* MOGCR - Monitoring Global Configuration Register
 * ------------------------------------------------
 */
#घोषणा MLXSW_REG_MOGCR_ID 0x9086
#घोषणा MLXSW_REG_MOGCR_LEN 0x20

MLXSW_REG_DEFINE(mogcr, MLXSW_REG_MOGCR_ID, MLXSW_REG_MOGCR_LEN);

/* reg_mogcr_ptp_अगरtc
 * PTP Ingress FIFO Trap Clear
 * The PTP_ING_FIFO trap provides MTPPTR with clr according
 * to this value. Default 0.
 * Reserved when IB चयनes and when SwitchX/-2, Spectrum-2
 * Access: RW
 */
MLXSW_ITEM32(reg, mogcr, ptp_अगरtc, 0x00, 1, 1);

/* reg_mogcr_ptp_eftc
 * PTP Egress FIFO Trap Clear
 * The PTP_EGR_FIFO trap provides MTPPTR with clr according
 * to this value. Default 0.
 * Reserved when IB चयनes and when SwitchX/-2, Spectrum-2
 * Access: RW
 */
MLXSW_ITEM32(reg, mogcr, ptp_eftc, 0x00, 0, 1);

/* reg_mogcr_mirroring_pid_base
 * Base policer id क्रम mirroring policers.
 * Must have an even value (e.g. 1000, not 1001).
 * Reserved when SwitchX/-2, Switch-IB/2, Spectrum-1 and Quantum.
 * Access: RW
 */
MLXSW_ITEM32(reg, mogcr, mirroring_pid_base, 0x0C, 0, 14);

/* MPAGR - Monitoring Port Analyzer Global Register
 * ------------------------------------------------
 * This रेजिस्टर is used क्रम global port analyzer configurations.
 * Note: This रेजिस्टर is not supported by current FW versions क्रम Spectrum-1.
 */
#घोषणा MLXSW_REG_MPAGR_ID 0x9089
#घोषणा MLXSW_REG_MPAGR_LEN 0x0C

MLXSW_REG_DEFINE(mpagr, MLXSW_REG_MPAGR_ID, MLXSW_REG_MPAGR_LEN);

क्रमागत mlxsw_reg_mpagr_trigger अणु
	MLXSW_REG_MPAGR_TRIGGER_EGRESS,
	MLXSW_REG_MPAGR_TRIGGER_INGRESS,
	MLXSW_REG_MPAGR_TRIGGER_INGRESS_WRED,
	MLXSW_REG_MPAGR_TRIGGER_INGRESS_SHARED_BUFFER,
	MLXSW_REG_MPAGR_TRIGGER_INGRESS_ING_CONG,
	MLXSW_REG_MPAGR_TRIGGER_INGRESS_EGR_CONG,
	MLXSW_REG_MPAGR_TRIGGER_EGRESS_ECN,
	MLXSW_REG_MPAGR_TRIGGER_EGRESS_HIGH_LATENCY,
पूर्ण;

/* reg_mpagr_trigger
 * Mirror trigger.
 * Access: Index
 */
MLXSW_ITEM32(reg, mpagr, trigger, 0x00, 0, 4);

/* reg_mpagr_pa_id
 * Port analyzer ID.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpagr, pa_id, 0x04, 0, 4);

#घोषणा MLXSW_REG_MPAGR_RATE_MAX 3500000000UL

/* reg_mpagr_probability_rate
 * Sampling rate.
 * Valid values are: 1 to 3.5*10^9
 * Value of 1 means "sample all". Default is 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, mpagr, probability_rate, 0x08, 0, 32);

अटल अंतरभूत व्योम mlxsw_reg_mpagr_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_mpagr_trigger trigger,
					u8 pa_id, u32 probability_rate)
अणु
	MLXSW_REG_ZERO(mpagr, payload);
	mlxsw_reg_mpagr_trigger_set(payload, trigger);
	mlxsw_reg_mpagr_pa_id_set(payload, pa_id);
	mlxsw_reg_mpagr_probability_rate_set(payload, probability_rate);
पूर्ण

/* MOMTE - Monitoring Mirror Trigger Enable Register
 * -------------------------------------------------
 * This रेजिस्टर is used to configure the mirror enable क्रम dअगरferent mirror
 * reasons.
 */
#घोषणा MLXSW_REG_MOMTE_ID 0x908D
#घोषणा MLXSW_REG_MOMTE_LEN 0x10

MLXSW_REG_DEFINE(momte, MLXSW_REG_MOMTE_ID, MLXSW_REG_MOMTE_LEN);

/* reg_momte_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, momte, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_momte_type अणु
	MLXSW_REG_MOMTE_TYPE_WRED = 0x20,
	MLXSW_REG_MOMTE_TYPE_SHARED_BUFFER_TCLASS = 0x31,
	MLXSW_REG_MOMTE_TYPE_SHARED_BUFFER_TCLASS_DESCRIPTORS = 0x32,
	MLXSW_REG_MOMTE_TYPE_SHARED_BUFFER_EGRESS_PORT = 0x33,
	MLXSW_REG_MOMTE_TYPE_ING_CONG = 0x40,
	MLXSW_REG_MOMTE_TYPE_EGR_CONG = 0x50,
	MLXSW_REG_MOMTE_TYPE_ECN = 0x60,
	MLXSW_REG_MOMTE_TYPE_HIGH_LATENCY = 0x70,
पूर्ण;

/* reg_momte_type
 * Type of mirroring.
 * Access: Index
 */
MLXSW_ITEM32(reg, momte, type, 0x04, 0, 8);

/* reg_momte_tclass_en
 * TClass/PG mirror enable. Each bit represents corresponding tclass.
 * 0: disable (शेष)
 * 1: enable
 * Access: RW
 */
MLXSW_ITEM_BIT_ARRAY(reg, momte, tclass_en, 0x08, 0x08, 1);

अटल अंतरभूत व्योम mlxsw_reg_momte_pack(अक्षर *payload, u8 local_port,
					क्रमागत mlxsw_reg_momte_type type)
अणु
	MLXSW_REG_ZERO(momte, payload);
	mlxsw_reg_momte_local_port_set(payload, local_port);
	mlxsw_reg_momte_type_set(payload, type);
पूर्ण

/* MTPPPC - Time Precision Packet Port Configuration
 * -------------------------------------------------
 * This रेजिस्टर serves क्रम configuration of which PTP messages should be
 * बारtamped. This is a global configuration, despite the रेजिस्टर name.
 *
 * Reserved when Spectrum-2.
 */
#घोषणा MLXSW_REG_MTPPPC_ID 0x9090
#घोषणा MLXSW_REG_MTPPPC_LEN 0x28

MLXSW_REG_DEFINE(mtpppc, MLXSW_REG_MTPPPC_ID, MLXSW_REG_MTPPPC_LEN);

/* reg_mtpppc_ing_बारtamp_message_type
 * Bitwise vector of PTP message types to बारtamp at ingress.
 * MessageType field as defined by IEEE 1588
 * Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)
 * Default all 0
 * Access: RW
 */
MLXSW_ITEM32(reg, mtpppc, ing_बारtamp_message_type, 0x08, 0, 16);

/* reg_mtpppc_egr_बारtamp_message_type
 * Bitwise vector of PTP message types to बारtamp at egress.
 * MessageType field as defined by IEEE 1588
 * Each bit corresponds to a value (e.g. Bit0: Sync, Bit1: Delay_Req)
 * Default all 0
 * Access: RW
 */
MLXSW_ITEM32(reg, mtpppc, egr_बारtamp_message_type, 0x0C, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mtpppc_pack(अक्षर *payload, u16 ing, u16 egr)
अणु
	MLXSW_REG_ZERO(mtpppc, payload);
	mlxsw_reg_mtpppc_ing_बारtamp_message_type_set(payload, ing);
	mlxsw_reg_mtpppc_egr_बारtamp_message_type_set(payload, egr);
पूर्ण

/* MTPPTR - Time Precision Packet Timestamping Reading
 * ---------------------------------------------------
 * The MTPPTR is used क्रम पढ़ोing the per port PTP बारtamp FIFO.
 * There is a trap क्रम packets which are latched to the बारtamp FIFO, thus the
 * SW knows which FIFO to पढ़ो. Note that packets enter the FIFO beक्रमe been
 * trapped. The sequence number is used to synchronize the बारtamp FIFO
 * entries and the trapped packets.
 * Reserved when Spectrum-2.
 */

#घोषणा MLXSW_REG_MTPPTR_ID 0x9091
#घोषणा MLXSW_REG_MTPPTR_BASE_LEN 0x10 /* base length, without records */
#घोषणा MLXSW_REG_MTPPTR_REC_LEN 0x10 /* record length */
#घोषणा MLXSW_REG_MTPPTR_REC_MAX_COUNT 4
#घोषणा MLXSW_REG_MTPPTR_LEN (MLXSW_REG_MTPPTR_BASE_LEN +		\
		    MLXSW_REG_MTPPTR_REC_LEN * MLXSW_REG_MTPPTR_REC_MAX_COUNT)

MLXSW_REG_DEFINE(mtpptr, MLXSW_REG_MTPPTR_ID, MLXSW_REG_MTPPTR_LEN);

/* reg_mtpptr_local_port
 * Not supported क्रम CPU port.
 * Access: Index
 */
MLXSW_ITEM32(reg, mtpptr, local_port, 0x00, 16, 8);

क्रमागत mlxsw_reg_mtpptr_dir अणु
	MLXSW_REG_MTPPTR_सूची_INGRESS,
	MLXSW_REG_MTPPTR_सूची_EGRESS,
पूर्ण;

/* reg_mtpptr_dir
 * Direction.
 * Access: Index
 */
MLXSW_ITEM32(reg, mtpptr, dir, 0x00, 0, 1);

/* reg_mtpptr_clr
 * Clear the records.
 * Access: OP
 */
MLXSW_ITEM32(reg, mtpptr, clr, 0x04, 31, 1);

/* reg_mtpptr_num_rec
 * Number of valid records in the response
 * Range 0.. cap_ptp_बारtamp_fअगरo
 * Access: RO
 */
MLXSW_ITEM32(reg, mtpptr, num_rec, 0x08, 0, 4);

/* reg_mtpptr_rec_message_type
 * MessageType field as defined by IEEE 1588 Each bit corresponds to a value
 * (e.g. Bit0: Sync, Bit1: Delay_Req)
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtpptr, rec_message_type,
		     MLXSW_REG_MTPPTR_BASE_LEN, 8, 4,
		     MLXSW_REG_MTPPTR_REC_LEN, 0, false);

/* reg_mtpptr_rec_करोमुख्य_number
 * Doमुख्यNumber field as defined by IEEE 1588
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtpptr, rec_करोमुख्य_number,
		     MLXSW_REG_MTPPTR_BASE_LEN, 0, 8,
		     MLXSW_REG_MTPPTR_REC_LEN, 0, false);

/* reg_mtpptr_rec_sequence_id
 * SequenceId field as defined by IEEE 1588
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtpptr, rec_sequence_id,
		     MLXSW_REG_MTPPTR_BASE_LEN, 0, 16,
		     MLXSW_REG_MTPPTR_REC_LEN, 0x4, false);

/* reg_mtpptr_rec_बारtamp_high
 * Timestamp of when the PTP packet has passed through the port Units of PLL
 * घड़ी समय.
 * For Spectrum-1 the PLL घड़ी is 156.25Mhz and PLL घड़ी समय is 6.4nSec.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtpptr, rec_बारtamp_high,
		     MLXSW_REG_MTPPTR_BASE_LEN, 0, 32,
		     MLXSW_REG_MTPPTR_REC_LEN, 0x8, false);

/* reg_mtpptr_rec_बारtamp_low
 * See rec_बारtamp_high.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, mtpptr, rec_बारtamp_low,
		     MLXSW_REG_MTPPTR_BASE_LEN, 0, 32,
		     MLXSW_REG_MTPPTR_REC_LEN, 0xC, false);

अटल अंतरभूत व्योम mlxsw_reg_mtpptr_unpack(स्थिर अक्षर *payload,
					   अचिन्हित पूर्णांक rec,
					   u8 *p_message_type,
					   u8 *p_करोमुख्य_number,
					   u16 *p_sequence_id,
					   u64 *p_बारtamp)
अणु
	u32 बारtamp_high, बारtamp_low;

	*p_message_type = mlxsw_reg_mtpptr_rec_message_type_get(payload, rec);
	*p_करोमुख्य_number = mlxsw_reg_mtpptr_rec_करोमुख्य_number_get(payload, rec);
	*p_sequence_id = mlxsw_reg_mtpptr_rec_sequence_id_get(payload, rec);
	बारtamp_high = mlxsw_reg_mtpptr_rec_बारtamp_high_get(payload, rec);
	बारtamp_low = mlxsw_reg_mtpptr_rec_बारtamp_low_get(payload, rec);
	*p_बारtamp = (u64)बारtamp_high << 32 | बारtamp_low;
पूर्ण

/* MTPTPT - Monitoring Precision Time Protocol Trap Register
 * ---------------------------------------------------------
 * This रेजिस्टर is used क्रम configuring under which trap to deliver PTP
 * packets depending on type of the packet.
 */
#घोषणा MLXSW_REG_MTPTPT_ID 0x9092
#घोषणा MLXSW_REG_MTPTPT_LEN 0x08

MLXSW_REG_DEFINE(mtptpt, MLXSW_REG_MTPTPT_ID, MLXSW_REG_MTPTPT_LEN);

क्रमागत mlxsw_reg_mtptpt_trap_id अणु
	MLXSW_REG_MTPTPT_TRAP_ID_PTP0,
	MLXSW_REG_MTPTPT_TRAP_ID_PTP1,
पूर्ण;

/* reg_mtptpt_trap_id
 * Trap id.
 * Access: Index
 */
MLXSW_ITEM32(reg, mtptpt, trap_id, 0x00, 0, 4);

/* reg_mtptpt_message_type
 * Bitwise vector of PTP message types to trap. This is a necessary but
 * non-sufficient condition since need to enable also per port. See MTPPPC.
 * Message types are defined by IEEE 1588 Each bit corresponds to a value (e.g.
 * Bit0: Sync, Bit1: Delay_Req)
 */
MLXSW_ITEM32(reg, mtptpt, message_type, 0x04, 0, 16);

अटल अंतरभूत व्योम mlxsw_reg_mtptptp_pack(अक्षर *payload,
					  क्रमागत mlxsw_reg_mtptpt_trap_id trap_id,
					  u16 message_type)
अणु
	MLXSW_REG_ZERO(mtptpt, payload);
	mlxsw_reg_mtptpt_trap_id_set(payload, trap_id);
	mlxsw_reg_mtptpt_message_type_set(payload, message_type);
पूर्ण

/* MFGD - Monitoring FW General Debug Register
 * -------------------------------------------
 */
#घोषणा MLXSW_REG_MFGD_ID 0x90F0
#घोषणा MLXSW_REG_MFGD_LEN 0x0C

MLXSW_REG_DEFINE(mfgd, MLXSW_REG_MFGD_ID, MLXSW_REG_MFGD_LEN);

/* reg_mfgd_fw_fatal_event_mode
 * 0 - करोn't check FW fatal (शेष)
 * 1 - check FW fatal - enable MFDE trap
 * Access: RW
 */
MLXSW_ITEM32(reg, mfgd, fatal_event_mode, 0x00, 9, 2);

/* reg_mfgd_trigger_test
 * Access: WO
 */
MLXSW_ITEM32(reg, mfgd, trigger_test, 0x00, 11, 1);

/* MGPIR - Management General Peripheral Inक्रमmation Register
 * ----------------------------------------------------------
 * MGPIR रेजिस्टर allows software to query the hardware and
 * firmware general inक्रमmation of peripheral entities.
 */
#घोषणा MLXSW_REG_MGPIR_ID 0x9100
#घोषणा MLXSW_REG_MGPIR_LEN 0xA0

MLXSW_REG_DEFINE(mgpir, MLXSW_REG_MGPIR_ID, MLXSW_REG_MGPIR_LEN);

क्रमागत mlxsw_reg_mgpir_device_type अणु
	MLXSW_REG_MGPIR_DEVICE_TYPE_NONE,
	MLXSW_REG_MGPIR_DEVICE_TYPE_GEARBOX_DIE,
पूर्ण;

/* device_type
 * Access: RO
 */
MLXSW_ITEM32(reg, mgpir, device_type, 0x00, 24, 4);

/* devices_per_flash
 * Number of devices of device_type per flash (can be shared by few devices).
 * Access: RO
 */
MLXSW_ITEM32(reg, mgpir, devices_per_flash, 0x00, 16, 8);

/* num_of_devices
 * Number of devices of device_type.
 * Access: RO
 */
MLXSW_ITEM32(reg, mgpir, num_of_devices, 0x00, 0, 8);

/* num_of_modules
 * Number of modules.
 * Access: RO
 */
MLXSW_ITEM32(reg, mgpir, num_of_modules, 0x04, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_mgpir_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(mgpir, payload);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_reg_mgpir_unpack(अक्षर *payload, u8 *num_of_devices,
		       क्रमागत mlxsw_reg_mgpir_device_type *device_type,
		       u8 *devices_per_flash, u8 *num_of_modules)
अणु
	अगर (num_of_devices)
		*num_of_devices = mlxsw_reg_mgpir_num_of_devices_get(payload);
	अगर (device_type)
		*device_type = mlxsw_reg_mgpir_device_type_get(payload);
	अगर (devices_per_flash)
		*devices_per_flash =
				mlxsw_reg_mgpir_devices_per_flash_get(payload);
	अगर (num_of_modules)
		*num_of_modules = mlxsw_reg_mgpir_num_of_modules_get(payload);
पूर्ण

/* MFDE - Monitoring FW Debug Register
 * -----------------------------------
 */
#घोषणा MLXSW_REG_MFDE_ID 0x9200
#घोषणा MLXSW_REG_MFDE_LEN 0x18

MLXSW_REG_DEFINE(mfde, MLXSW_REG_MFDE_ID, MLXSW_REG_MFDE_LEN);

/* reg_mfde_irisc_id
 * Which irisc triggered the event
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, irisc_id, 0x00, 24, 8);

क्रमागत mlxsw_reg_mfde_event_id अणु
	MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO = 1,
	/* KVD insertion machine stopped */
	MLXSW_REG_MFDE_EVENT_ID_KVD_IM_STOP,
पूर्ण;

/* reg_mfde_event_id
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, event_id, 0x00, 0, 16);

क्रमागत mlxsw_reg_mfde_method अणु
	MLXSW_REG_MFDE_METHOD_QUERY,
	MLXSW_REG_MFDE_METHOD_WRITE,
पूर्ण;

/* reg_mfde_method
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, method, 0x04, 29, 1);

/* reg_mfde_दीर्घ_process
 * Indicates अगर the command is in दीर्घ_process mode.
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, दीर्घ_process, 0x04, 28, 1);

क्रमागत mlxsw_reg_mfde_command_type अणु
	MLXSW_REG_MFDE_COMMAND_TYPE_MAD,
	MLXSW_REG_MFDE_COMMAND_TYPE_EMAD,
	MLXSW_REG_MFDE_COMMAND_TYPE_CMDIF,
पूर्ण;

/* reg_mfde_command_type
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, command_type, 0x04, 24, 2);

/* reg_mfde_reg_attr_id
 * EMAD - रेजिस्टर id, MAD - attibute id
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, reg_attr_id, 0x04, 0, 16);

/* reg_mfde_log_address
 * crspace address accessed, which resulted in समयout.
 * Valid in हाल event_id == MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, log_address, 0x10, 0, 32);

/* reg_mfde_log_id
 * Which irisc triggered the समयout.
 * Valid in हाल event_id == MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, log_id, 0x14, 0, 4);

/* reg_mfde_log_ip
 * IP (inकाष्ठाion poपूर्णांकer) that triggered the समयout.
 * Valid in हाल event_id == MLXSW_REG_MFDE_EVENT_ID_CRSPACE_TO
 * Access: RO
 */
MLXSW_ITEM64(reg, mfde, log_ip, 0x18, 0, 64);

/* reg_mfde_pipes_mask
 * Bit per kvh pipe.
 * Access: RO
 */
MLXSW_ITEM32(reg, mfde, pipes_mask, 0x10, 0, 16);

/* TNGCR - Tunneling NVE General Configuration Register
 * ----------------------------------------------------
 * The TNGCR रेजिस्टर is used क्रम setting up the NVE Tunneling configuration.
 */
#घोषणा MLXSW_REG_TNGCR_ID 0xA001
#घोषणा MLXSW_REG_TNGCR_LEN 0x44

MLXSW_REG_DEFINE(tngcr, MLXSW_REG_TNGCR_ID, MLXSW_REG_TNGCR_LEN);

क्रमागत mlxsw_reg_tngcr_type अणु
	MLXSW_REG_TNGCR_TYPE_VXLAN,
	MLXSW_REG_TNGCR_TYPE_VXLAN_GPE,
	MLXSW_REG_TNGCR_TYPE_GENEVE,
	MLXSW_REG_TNGCR_TYPE_NVGRE,
पूर्ण;

/* reg_tngcr_type
 * Tunnel type क्रम encapsulation and decapsulation. The types are mutually
 * exclusive.
 * Note: For Spectrum the NVE parsing must be enabled in MPRS.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, type, 0x00, 0, 4);

/* reg_tngcr_nve_valid
 * The VTEP is valid. Allows adding FDB entries क्रम tunnel encapsulation.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_valid, 0x04, 31, 1);

/* reg_tngcr_nve_ttl_uc
 * The TTL क्रम NVE tunnel encapsulation underlay unicast packets.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_ttl_uc, 0x04, 0, 8);

/* reg_tngcr_nve_ttl_mc
 * The TTL क्रम NVE tunnel encapsulation underlay multicast packets.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_ttl_mc, 0x08, 0, 8);

क्रमागत अणु
	/* Do not copy flow label. Calculate flow label using nve_flh. */
	MLXSW_REG_TNGCR_FL_NO_COPY,
	/* Copy flow label from inner packet अगर packet is IPv6 and
	 * encapsulation is by IPv6. Otherwise, calculate flow label using
	 * nve_flh.
	 */
	MLXSW_REG_TNGCR_FL_COPY,
पूर्ण;

/* reg_tngcr_nve_flc
 * For NVE tunnel encapsulation: Flow label copy from inner packet.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_flc, 0x0C, 25, 1);

क्रमागत अणु
	/* Flow label is अटल. In Spectrum this means '0'. Spectrum-2
	 * uses अणुnve_fl_prefix, nve_fl_suffixपूर्ण.
	 */
	MLXSW_REG_TNGCR_FL_NO_HASH,
	/* 8 LSBs of the flow label are calculated from ECMP hash of the
	 * inner packet. 12 MSBs are configured by nve_fl_prefix.
	 */
	MLXSW_REG_TNGCR_FL_HASH,
पूर्ण;

/* reg_tngcr_nve_flh
 * NVE flow label hash.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_flh, 0x0C, 24, 1);

/* reg_tngcr_nve_fl_prefix
 * NVE flow label prefix. Constant 12 MSBs of the flow label.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_fl_prefix, 0x0C, 8, 12);

/* reg_tngcr_nve_fl_suffix
 * NVE flow label suffix. Constant 8 LSBs of the flow label.
 * Reserved when nve_flh=1 and क्रम Spectrum.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_fl_suffix, 0x0C, 0, 8);

क्रमागत अणु
	/* Source UDP port is fixed (शेष '0') */
	MLXSW_REG_TNGCR_UDP_SPORT_NO_HASH,
	/* Source UDP port is calculated based on hash */
	MLXSW_REG_TNGCR_UDP_SPORT_HASH,
पूर्ण;

/* reg_tngcr_nve_udp_sport_type
 * NVE UDP source port type.
 * Spectrum uses LAG hash (SLCRv2). Spectrum-2 uses ECMP hash (RECRv2).
 * When the source UDP port is calculated based on hash, then the 8 LSBs
 * are calculated from hash the 8 MSBs are configured by
 * nve_udp_sport_prefix.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_udp_sport_type, 0x10, 24, 1);

/* reg_tngcr_nve_udp_sport_prefix
 * NVE UDP source port prefix. Constant 8 MSBs of the UDP source port.
 * Reserved when NVE type is NVGRE.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_udp_sport_prefix, 0x10, 8, 8);

/* reg_tngcr_nve_group_size_mc
 * The amount of sequential linked lists of MC entries. The first linked
 * list is configured by SFD.underlay_mc_ptr.
 * Valid values: 1, 2, 4, 8, 16, 32, 64
 * The linked list are configured by TNUMT.
 * The hash is set by LAG hash.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_group_size_mc, 0x18, 0, 8);

/* reg_tngcr_nve_group_size_flood
 * The amount of sequential linked lists of flooding entries. The first
 * linked list is configured by SFMR.nve_tunnel_flood_ptr
 * Valid values: 1, 2, 4, 8, 16, 32, 64
 * The linked list are configured by TNUMT.
 * The hash is set by LAG hash.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, nve_group_size_flood, 0x1C, 0, 8);

/* reg_tngcr_learn_enable
 * During decapsulation, whether to learn from NVE port.
 * Reserved when Spectrum-2. See TNPC.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, learn_enable, 0x20, 31, 1);

/* reg_tngcr_underlay_भव_router
 * Underlay भव router.
 * Reserved when Spectrum-2.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, underlay_भव_router, 0x20, 0, 16);

/* reg_tngcr_underlay_rअगर
 * Underlay ingress router पूर्णांकerface. RIF type should be loopback generic.
 * Reserved when Spectrum.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, underlay_rअगर, 0x24, 0, 16);

/* reg_tngcr_usipv4
 * Underlay source IPv4 address of the NVE.
 * Access: RW
 */
MLXSW_ITEM32(reg, tngcr, usipv4, 0x28, 0, 32);

/* reg_tngcr_usipv6
 * Underlay source IPv6 address of the NVE. For Spectrum, must not be
 * modअगरied under traffic of NVE tunneling encapsulation.
 * Access: RW
 */
MLXSW_ITEM_BUF(reg, tngcr, usipv6, 0x30, 16);

अटल अंतरभूत व्योम mlxsw_reg_tngcr_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_tngcr_type type,
					bool valid, u8 ttl)
अणु
	MLXSW_REG_ZERO(tngcr, payload);
	mlxsw_reg_tngcr_type_set(payload, type);
	mlxsw_reg_tngcr_nve_valid_set(payload, valid);
	mlxsw_reg_tngcr_nve_ttl_uc_set(payload, ttl);
	mlxsw_reg_tngcr_nve_ttl_mc_set(payload, ttl);
	mlxsw_reg_tngcr_nve_flc_set(payload, MLXSW_REG_TNGCR_FL_NO_COPY);
	mlxsw_reg_tngcr_nve_flh_set(payload, 0);
	mlxsw_reg_tngcr_nve_udp_sport_type_set(payload,
					       MLXSW_REG_TNGCR_UDP_SPORT_HASH);
	mlxsw_reg_tngcr_nve_udp_sport_prefix_set(payload, 0);
	mlxsw_reg_tngcr_nve_group_size_mc_set(payload, 1);
	mlxsw_reg_tngcr_nve_group_size_flood_set(payload, 1);
पूर्ण

/* TNUMT - Tunneling NVE Underlay Multicast Table Register
 * -------------------------------------------------------
 * The TNUMT रेजिस्टर is क्रम building the underlay MC table. It is used
 * क्रम MC, flooding and BC traffic पूर्णांकo the NVE tunnel.
 */
#घोषणा MLXSW_REG_TNUMT_ID 0xA003
#घोषणा MLXSW_REG_TNUMT_LEN 0x20

MLXSW_REG_DEFINE(tnumt, MLXSW_REG_TNUMT_ID, MLXSW_REG_TNUMT_LEN);

क्रमागत mlxsw_reg_tnumt_record_type अणु
	MLXSW_REG_TNUMT_RECORD_TYPE_IPV4,
	MLXSW_REG_TNUMT_RECORD_TYPE_IPV6,
	MLXSW_REG_TNUMT_RECORD_TYPE_LABEL,
पूर्ण;

/* reg_tnumt_record_type
 * Record type.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, record_type, 0x00, 28, 4);

/* reg_tnumt_tunnel_port
 * Tunnel port.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, tunnel_port, 0x00, 24, 4);

/* reg_tnumt_underlay_mc_ptr
 * Index to the underlay multicast table.
 * For Spectrum the index is to the KVD linear.
 * Access: Index
 */
MLXSW_ITEM32(reg, tnumt, underlay_mc_ptr, 0x00, 0, 24);

/* reg_tnumt_vnext
 * The next_underlay_mc_ptr is valid.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, vnext, 0x04, 31, 1);

/* reg_tnumt_next_underlay_mc_ptr
 * The next index to the underlay multicast table.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, next_underlay_mc_ptr, 0x04, 0, 24);

/* reg_tnumt_record_size
 * Number of IP addresses in the record.
 * Range is 1..cap_max_nve_mc_entries_ipvअणु4,6पूर्ण
 * Access: RW
 */
MLXSW_ITEM32(reg, tnumt, record_size, 0x08, 0, 3);

/* reg_tnumt_udip
 * The underlay IPv4 addresses. udip[i] is reserved अगर i >= size
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, udip, 0x0C, 0, 32, 0x04, 0x00, false);

/* reg_tnumt_udip_ptr
 * The poपूर्णांकer to the underlay IPv6 addresses. udip_ptr[i] is reserved अगर
 * i >= size. The IPv6 addresses are configured by RIPS.
 * Access: RW
 */
MLXSW_ITEM32_INDEXED(reg, tnumt, udip_ptr, 0x0C, 0, 24, 0x04, 0x00, false);

अटल अंतरभूत व्योम mlxsw_reg_tnumt_pack(अक्षर *payload,
					क्रमागत mlxsw_reg_tnumt_record_type type,
					क्रमागत mlxsw_reg_tunnel_port tport,
					u32 underlay_mc_ptr, bool vnext,
					u32 next_underlay_mc_ptr,
					u8 record_size)
अणु
	MLXSW_REG_ZERO(tnumt, payload);
	mlxsw_reg_tnumt_record_type_set(payload, type);
	mlxsw_reg_tnumt_tunnel_port_set(payload, tport);
	mlxsw_reg_tnumt_underlay_mc_ptr_set(payload, underlay_mc_ptr);
	mlxsw_reg_tnumt_vnext_set(payload, vnext);
	mlxsw_reg_tnumt_next_underlay_mc_ptr_set(payload, next_underlay_mc_ptr);
	mlxsw_reg_tnumt_record_size_set(payload, record_size);
पूर्ण

/* TNQCR - Tunneling NVE QoS Configuration Register
 * ------------------------------------------------
 * The TNQCR रेजिस्टर configures how QoS is set in encapsulation पूर्णांकo the
 * underlay network.
 */
#घोषणा MLXSW_REG_TNQCR_ID 0xA010
#घोषणा MLXSW_REG_TNQCR_LEN 0x0C

MLXSW_REG_DEFINE(tnqcr, MLXSW_REG_TNQCR_ID, MLXSW_REG_TNQCR_LEN);

/* reg_tnqcr_enc_set_dscp
 * For encapsulation: How to set DSCP field:
 * 0 - Copy the DSCP from the overlay (inner) IP header to the underlay
 * (outer) IP header. If there is no IP header, use TNQDR.dscp
 * 1 - Set the DSCP field as TNQDR.dscp
 * Access: RW
 */
MLXSW_ITEM32(reg, tnqcr, enc_set_dscp, 0x04, 28, 1);

अटल अंतरभूत व्योम mlxsw_reg_tnqcr_pack(अक्षर *payload)
अणु
	MLXSW_REG_ZERO(tnqcr, payload);
	mlxsw_reg_tnqcr_enc_set_dscp_set(payload, 0);
पूर्ण

/* TNQDR - Tunneling NVE QoS Default Register
 * ------------------------------------------
 * The TNQDR रेजिस्टर configures the शेष QoS settings क्रम NVE
 * encapsulation.
 */
#घोषणा MLXSW_REG_TNQDR_ID 0xA011
#घोषणा MLXSW_REG_TNQDR_LEN 0x08

MLXSW_REG_DEFINE(tnqdr, MLXSW_REG_TNQDR_ID, MLXSW_REG_TNQDR_LEN);

/* reg_tnqdr_local_port
 * Local port number (receive port). CPU port is supported.
 * Access: Index
 */
MLXSW_ITEM32(reg, tnqdr, local_port, 0x00, 16, 8);

/* reg_tnqdr_dscp
 * For encapsulation, the शेष DSCP.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnqdr, dscp, 0x04, 0, 6);

अटल अंतरभूत व्योम mlxsw_reg_tnqdr_pack(अक्षर *payload, u8 local_port)
अणु
	MLXSW_REG_ZERO(tnqdr, payload);
	mlxsw_reg_tnqdr_local_port_set(payload, local_port);
	mlxsw_reg_tnqdr_dscp_set(payload, 0);
पूर्ण

/* TNEEM - Tunneling NVE Encapsulation ECN Mapping Register
 * --------------------------------------------------------
 * The TNEEM रेजिस्टर maps ECN of the IP header at the ingress to the
 * encapsulation to the ECN of the underlay network.
 */
#घोषणा MLXSW_REG_TNEEM_ID 0xA012
#घोषणा MLXSW_REG_TNEEM_LEN 0x0C

MLXSW_REG_DEFINE(tneem, MLXSW_REG_TNEEM_ID, MLXSW_REG_TNEEM_LEN);

/* reg_tneem_overlay_ecn
 * ECN of the IP header in the overlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tneem, overlay_ecn, 0x04, 24, 2);

/* reg_tneem_underlay_ecn
 * ECN of the IP header in the underlay network.
 * Access: RW
 */
MLXSW_ITEM32(reg, tneem, underlay_ecn, 0x04, 16, 2);

अटल अंतरभूत व्योम mlxsw_reg_tneem_pack(अक्षर *payload, u8 overlay_ecn,
					u8 underlay_ecn)
अणु
	MLXSW_REG_ZERO(tneem, payload);
	mlxsw_reg_tneem_overlay_ecn_set(payload, overlay_ecn);
	mlxsw_reg_tneem_underlay_ecn_set(payload, underlay_ecn);
पूर्ण

/* TNDEM - Tunneling NVE Decapsulation ECN Mapping Register
 * --------------------------------------------------------
 * The TNDEM रेजिस्टर configures the actions that are करोne in the
 * decapsulation.
 */
#घोषणा MLXSW_REG_TNDEM_ID 0xA013
#घोषणा MLXSW_REG_TNDEM_LEN 0x0C

MLXSW_REG_DEFINE(tndem, MLXSW_REG_TNDEM_ID, MLXSW_REG_TNDEM_LEN);

/* reg_tndem_underlay_ecn
 * ECN field of the IP header in the underlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tndem, underlay_ecn, 0x04, 24, 2);

/* reg_tndem_overlay_ecn
 * ECN field of the IP header in the overlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tndem, overlay_ecn, 0x04, 16, 2);

/* reg_tndem_eip_ecn
 * Egress IP ECN. ECN field of the IP header of the packet which goes out
 * from the decapsulation.
 * Access: RW
 */
MLXSW_ITEM32(reg, tndem, eip_ecn, 0x04, 8, 2);

/* reg_tndem_trap_en
 * Trap enable:
 * 0 - No trap due to decap ECN
 * 1 - Trap enable with trap_id
 * Access: RW
 */
MLXSW_ITEM32(reg, tndem, trap_en, 0x08, 28, 4);

/* reg_tndem_trap_id
 * Trap ID. Either DECAP_ECN0 or DECAP_ECN1.
 * Reserved when trap_en is '0'.
 * Access: RW
 */
MLXSW_ITEM32(reg, tndem, trap_id, 0x08, 0, 9);

अटल अंतरभूत व्योम mlxsw_reg_tndem_pack(अक्षर *payload, u8 underlay_ecn,
					u8 overlay_ecn, u8 ecn, bool trap_en,
					u16 trap_id)
अणु
	MLXSW_REG_ZERO(tndem, payload);
	mlxsw_reg_tndem_underlay_ecn_set(payload, underlay_ecn);
	mlxsw_reg_tndem_overlay_ecn_set(payload, overlay_ecn);
	mlxsw_reg_tndem_eip_ecn_set(payload, ecn);
	mlxsw_reg_tndem_trap_en_set(payload, trap_en);
	mlxsw_reg_tndem_trap_id_set(payload, trap_id);
पूर्ण

/* TNPC - Tunnel Port Configuration Register
 * -----------------------------------------
 * The TNPC रेजिस्टर is used क्रम tunnel port configuration.
 * Reserved when Spectrum.
 */
#घोषणा MLXSW_REG_TNPC_ID 0xA020
#घोषणा MLXSW_REG_TNPC_LEN 0x18

MLXSW_REG_DEFINE(tnpc, MLXSW_REG_TNPC_ID, MLXSW_REG_TNPC_LEN);

/* reg_tnpc_tunnel_port
 * Tunnel port.
 * Access: Index
 */
MLXSW_ITEM32(reg, tnpc, tunnel_port, 0x00, 0, 4);

/* reg_tnpc_learn_enable_v6
 * During IPv6 underlay decapsulation, whether to learn from tunnel port.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnpc, learn_enable_v6, 0x04, 1, 1);

/* reg_tnpc_learn_enable_v4
 * During IPv4 underlay decapsulation, whether to learn from tunnel port.
 * Access: RW
 */
MLXSW_ITEM32(reg, tnpc, learn_enable_v4, 0x04, 0, 1);

अटल अंतरभूत व्योम mlxsw_reg_tnpc_pack(अक्षर *payload,
				       क्रमागत mlxsw_reg_tunnel_port tport,
				       bool learn_enable)
अणु
	MLXSW_REG_ZERO(tnpc, payload);
	mlxsw_reg_tnpc_tunnel_port_set(payload, tport);
	mlxsw_reg_tnpc_learn_enable_v4_set(payload, learn_enable);
	mlxsw_reg_tnpc_learn_enable_v6_set(payload, learn_enable);
पूर्ण

/* TIGCR - Tunneling IPinIP General Configuration Register
 * -------------------------------------------------------
 * The TIGCR रेजिस्टर is used क्रम setting up the IPinIP Tunnel configuration.
 */
#घोषणा MLXSW_REG_TIGCR_ID 0xA801
#घोषणा MLXSW_REG_TIGCR_LEN 0x10

MLXSW_REG_DEFINE(tigcr, MLXSW_REG_TIGCR_ID, MLXSW_REG_TIGCR_LEN);

/* reg_tigcr_ipip_ttlc
 * For IPinIP Tunnel encapsulation: whether to copy the ttl from the packet
 * header.
 * Access: RW
 */
MLXSW_ITEM32(reg, tigcr, ttlc, 0x04, 8, 1);

/* reg_tigcr_ipip_ttl_uc
 * The TTL क्रम IPinIP Tunnel encapsulation of unicast packets अगर
 * reg_tigcr_ipip_ttlc is unset.
 * Access: RW
 */
MLXSW_ITEM32(reg, tigcr, ttl_uc, 0x04, 0, 8);

अटल अंतरभूत व्योम mlxsw_reg_tigcr_pack(अक्षर *payload, bool ttlc, u8 ttl_uc)
अणु
	MLXSW_REG_ZERO(tigcr, payload);
	mlxsw_reg_tigcr_ttlc_set(payload, ttlc);
	mlxsw_reg_tigcr_ttl_uc_set(payload, ttl_uc);
पूर्ण

/* TIEEM - Tunneling IPinIP Encapsulation ECN Mapping Register
 * -----------------------------------------------------------
 * The TIEEM रेजिस्टर maps ECN of the IP header at the ingress to the
 * encapsulation to the ECN of the underlay network.
 */
#घोषणा MLXSW_REG_TIEEM_ID 0xA812
#घोषणा MLXSW_REG_TIEEM_LEN 0x0C

MLXSW_REG_DEFINE(tieem, MLXSW_REG_TIEEM_ID, MLXSW_REG_TIEEM_LEN);

/* reg_tieem_overlay_ecn
 * ECN of the IP header in the overlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tieem, overlay_ecn, 0x04, 24, 2);

/* reg_tineem_underlay_ecn
 * ECN of the IP header in the underlay network.
 * Access: RW
 */
MLXSW_ITEM32(reg, tieem, underlay_ecn, 0x04, 16, 2);

अटल अंतरभूत व्योम mlxsw_reg_tieem_pack(अक्षर *payload, u8 overlay_ecn,
					u8 underlay_ecn)
अणु
	MLXSW_REG_ZERO(tieem, payload);
	mlxsw_reg_tieem_overlay_ecn_set(payload, overlay_ecn);
	mlxsw_reg_tieem_underlay_ecn_set(payload, underlay_ecn);
पूर्ण

/* TIDEM - Tunneling IPinIP Decapsulation ECN Mapping Register
 * -----------------------------------------------------------
 * The TIDEM रेजिस्टर configures the actions that are करोne in the
 * decapsulation.
 */
#घोषणा MLXSW_REG_TIDEM_ID 0xA813
#घोषणा MLXSW_REG_TIDEM_LEN 0x0C

MLXSW_REG_DEFINE(tidem, MLXSW_REG_TIDEM_ID, MLXSW_REG_TIDEM_LEN);

/* reg_tidem_underlay_ecn
 * ECN field of the IP header in the underlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tidem, underlay_ecn, 0x04, 24, 2);

/* reg_tidem_overlay_ecn
 * ECN field of the IP header in the overlay network.
 * Access: Index
 */
MLXSW_ITEM32(reg, tidem, overlay_ecn, 0x04, 16, 2);

/* reg_tidem_eip_ecn
 * Egress IP ECN. ECN field of the IP header of the packet which goes out
 * from the decapsulation.
 * Access: RW
 */
MLXSW_ITEM32(reg, tidem, eip_ecn, 0x04, 8, 2);

/* reg_tidem_trap_en
 * Trap enable:
 * 0 - No trap due to decap ECN
 * 1 - Trap enable with trap_id
 * Access: RW
 */
MLXSW_ITEM32(reg, tidem, trap_en, 0x08, 28, 4);

/* reg_tidem_trap_id
 * Trap ID. Either DECAP_ECN0 or DECAP_ECN1.
 * Reserved when trap_en is '0'.
 * Access: RW
 */
MLXSW_ITEM32(reg, tidem, trap_id, 0x08, 0, 9);

अटल अंतरभूत व्योम mlxsw_reg_tidem_pack(अक्षर *payload, u8 underlay_ecn,
					u8 overlay_ecn, u8 eip_ecn,
					bool trap_en, u16 trap_id)
अणु
	MLXSW_REG_ZERO(tidem, payload);
	mlxsw_reg_tidem_underlay_ecn_set(payload, underlay_ecn);
	mlxsw_reg_tidem_overlay_ecn_set(payload, overlay_ecn);
	mlxsw_reg_tidem_eip_ecn_set(payload, eip_ecn);
	mlxsw_reg_tidem_trap_en_set(payload, trap_en);
	mlxsw_reg_tidem_trap_id_set(payload, trap_id);
पूर्ण

/* SBPR - Shared Buffer Pools Register
 * -----------------------------------
 * The SBPR configures and retrieves the shared buffer pools and configuration.
 */
#घोषणा MLXSW_REG_SBPR_ID 0xB001
#घोषणा MLXSW_REG_SBPR_LEN 0x14

MLXSW_REG_DEFINE(sbpr, MLXSW_REG_SBPR_ID, MLXSW_REG_SBPR_LEN);

/* shared direstion क्रमागत क्रम SBPR, SBCM, SBPM */
क्रमागत mlxsw_reg_sbxx_dir अणु
	MLXSW_REG_SBXX_सूची_INGRESS,
	MLXSW_REG_SBXX_सूची_EGRESS,
पूर्ण;

/* reg_sbpr_dir
 * Direction.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbpr, dir, 0x00, 24, 2);

/* reg_sbpr_pool
 * Pool index.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbpr, pool, 0x00, 0, 4);

/* reg_sbpr_infi_size
 * Size is infinite.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbpr, infi_size, 0x04, 31, 1);

/* reg_sbpr_size
 * Pool size in buffer cells.
 * Reserved when infi_size = 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbpr, size, 0x04, 0, 24);

क्रमागत mlxsw_reg_sbpr_mode अणु
	MLXSW_REG_SBPR_MODE_STATIC,
	MLXSW_REG_SBPR_MODE_DYNAMIC,
पूर्ण;

/* reg_sbpr_mode
 * Pool quota calculation mode.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbpr, mode, 0x08, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_sbpr_pack(अक्षर *payload, u8 pool,
				       क्रमागत mlxsw_reg_sbxx_dir dir,
				       क्रमागत mlxsw_reg_sbpr_mode mode, u32 size,
				       bool infi_size)
अणु
	MLXSW_REG_ZERO(sbpr, payload);
	mlxsw_reg_sbpr_pool_set(payload, pool);
	mlxsw_reg_sbpr_dir_set(payload, dir);
	mlxsw_reg_sbpr_mode_set(payload, mode);
	mlxsw_reg_sbpr_size_set(payload, size);
	mlxsw_reg_sbpr_infi_size_set(payload, infi_size);
पूर्ण

/* SBCM - Shared Buffer Class Management Register
 * ----------------------------------------------
 * The SBCM रेजिस्टर configures and retrieves the shared buffer allocation
 * and configuration according to Port-PG, including the binding to pool
 * and definition of the associated quota.
 */
#घोषणा MLXSW_REG_SBCM_ID 0xB002
#घोषणा MLXSW_REG_SBCM_LEN 0x28

MLXSW_REG_DEFINE(sbcm, MLXSW_REG_SBCM_ID, MLXSW_REG_SBCM_LEN);

/* reg_sbcm_local_port
 * Local port number.
 * For Ingress: excludes CPU port and Router port
 * For Egress: excludes IP Router
 * Access: Index
 */
MLXSW_ITEM32(reg, sbcm, local_port, 0x00, 16, 8);

/* reg_sbcm_pg_buff
 * PG buffer - Port PG (dir=ingress) / traffic class (dir=egress)
 * For PG buffer: range is 0..cap_max_pg_buffers - 1
 * For traffic class: range is 0..cap_max_tclass - 1
 * Note that when traffic class is in MC aware mode then the traffic
 * classes which are MC aware cannot be configured.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbcm, pg_buff, 0x00, 8, 6);

/* reg_sbcm_dir
 * Direction.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbcm, dir, 0x00, 0, 2);

/* reg_sbcm_min_buff
 * Minimum buffer size क्रम the limiter, in cells.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbcm, min_buff, 0x18, 0, 24);

/* shared max_buff limits क्रम dynamic threshold क्रम SBCM, SBPM */
#घोषणा MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN 1
#घोषणा MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX 14

/* reg_sbcm_infi_max
 * Max buffer is infinite.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbcm, infi_max, 0x1C, 31, 1);

/* reg_sbcm_max_buff
 * When the pool associated to the port-pg/tclass is configured to
 * अटल, Maximum buffer size क्रम the limiter configured in cells.
 * When the pool associated to the port-pg/tclass is configured to
 * dynamic, the max_buff holds the "alpha" parameter, supporting
 * the following values:
 * 0: 0
 * i: (1/128)*2^(i-1), क्रम i=1..14
 * 0xFF: Infinity
 * Reserved when infi_max = 1.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbcm, max_buff, 0x1C, 0, 24);

/* reg_sbcm_pool
 * Association of the port-priority to a pool.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbcm, pool, 0x24, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_sbcm_pack(अक्षर *payload, u8 local_port, u8 pg_buff,
				       क्रमागत mlxsw_reg_sbxx_dir dir,
				       u32 min_buff, u32 max_buff,
				       bool infi_max, u8 pool)
अणु
	MLXSW_REG_ZERO(sbcm, payload);
	mlxsw_reg_sbcm_local_port_set(payload, local_port);
	mlxsw_reg_sbcm_pg_buff_set(payload, pg_buff);
	mlxsw_reg_sbcm_dir_set(payload, dir);
	mlxsw_reg_sbcm_min_buff_set(payload, min_buff);
	mlxsw_reg_sbcm_max_buff_set(payload, max_buff);
	mlxsw_reg_sbcm_infi_max_set(payload, infi_max);
	mlxsw_reg_sbcm_pool_set(payload, pool);
पूर्ण

/* SBPM - Shared Buffer Port Management Register
 * ---------------------------------------------
 * The SBPM रेजिस्टर configures and retrieves the shared buffer allocation
 * and configuration according to Port-Pool, including the definition
 * of the associated quota.
 */
#घोषणा MLXSW_REG_SBPM_ID 0xB003
#घोषणा MLXSW_REG_SBPM_LEN 0x28

MLXSW_REG_DEFINE(sbpm, MLXSW_REG_SBPM_ID, MLXSW_REG_SBPM_LEN);

/* reg_sbpm_local_port
 * Local port number.
 * For Ingress: excludes CPU port and Router port
 * For Egress: excludes IP Router
 * Access: Index
 */
MLXSW_ITEM32(reg, sbpm, local_port, 0x00, 16, 8);

/* reg_sbpm_pool
 * The pool associated to quota counting on the local_port.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbpm, pool, 0x00, 8, 4);

/* reg_sbpm_dir
 * Direction.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbpm, dir, 0x00, 0, 2);

/* reg_sbpm_buff_occupancy
 * Current buffer occupancy in cells.
 * Access: RO
 */
MLXSW_ITEM32(reg, sbpm, buff_occupancy, 0x10, 0, 24);

/* reg_sbpm_clr
 * Clear Max Buffer Occupancy
 * When this bit is set, max_buff_occupancy field is cleared (and a
 * new max value is tracked from the समय the clear was perक्रमmed).
 * Access: OP
 */
MLXSW_ITEM32(reg, sbpm, clr, 0x14, 31, 1);

/* reg_sbpm_max_buff_occupancy
 * Maximum value of buffer occupancy in cells monitored. Cleared by
 * writing to the clr field.
 * Access: RO
 */
MLXSW_ITEM32(reg, sbpm, max_buff_occupancy, 0x14, 0, 24);

/* reg_sbpm_min_buff
 * Minimum buffer size क्रम the limiter, in cells.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbpm, min_buff, 0x18, 0, 24);

/* reg_sbpm_max_buff
 * When the pool associated to the port-pg/tclass is configured to
 * अटल, Maximum buffer size क्रम the limiter configured in cells.
 * When the pool associated to the port-pg/tclass is configured to
 * dynamic, the max_buff holds the "alpha" parameter, supporting
 * the following values:
 * 0: 0
 * i: (1/128)*2^(i-1), क्रम i=1..14
 * 0xFF: Infinity
 * Access: RW
 */
MLXSW_ITEM32(reg, sbpm, max_buff, 0x1C, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_sbpm_pack(अक्षर *payload, u8 local_port, u8 pool,
				       क्रमागत mlxsw_reg_sbxx_dir dir, bool clr,
				       u32 min_buff, u32 max_buff)
अणु
	MLXSW_REG_ZERO(sbpm, payload);
	mlxsw_reg_sbpm_local_port_set(payload, local_port);
	mlxsw_reg_sbpm_pool_set(payload, pool);
	mlxsw_reg_sbpm_dir_set(payload, dir);
	mlxsw_reg_sbpm_clr_set(payload, clr);
	mlxsw_reg_sbpm_min_buff_set(payload, min_buff);
	mlxsw_reg_sbpm_max_buff_set(payload, max_buff);
पूर्ण

अटल अंतरभूत व्योम mlxsw_reg_sbpm_unpack(अक्षर *payload, u32 *p_buff_occupancy,
					 u32 *p_max_buff_occupancy)
अणु
	*p_buff_occupancy = mlxsw_reg_sbpm_buff_occupancy_get(payload);
	*p_max_buff_occupancy = mlxsw_reg_sbpm_max_buff_occupancy_get(payload);
पूर्ण

/* SBMM - Shared Buffer Multicast Management Register
 * --------------------------------------------------
 * The SBMM रेजिस्टर configures and retrieves the shared buffer allocation
 * and configuration क्रम MC packets according to Switch-Priority, including
 * the binding to pool and definition of the associated quota.
 */
#घोषणा MLXSW_REG_SBMM_ID 0xB004
#घोषणा MLXSW_REG_SBMM_LEN 0x28

MLXSW_REG_DEFINE(sbmm, MLXSW_REG_SBMM_ID, MLXSW_REG_SBMM_LEN);

/* reg_sbmm_prio
 * Switch Priority.
 * Access: Index
 */
MLXSW_ITEM32(reg, sbmm, prio, 0x00, 8, 4);

/* reg_sbmm_min_buff
 * Minimum buffer size क्रम the limiter, in cells.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbmm, min_buff, 0x18, 0, 24);

/* reg_sbmm_max_buff
 * When the pool associated to the port-pg/tclass is configured to
 * अटल, Maximum buffer size क्रम the limiter configured in cells.
 * When the pool associated to the port-pg/tclass is configured to
 * dynamic, the max_buff holds the "alpha" parameter, supporting
 * the following values:
 * 0: 0
 * i: (1/128)*2^(i-1), क्रम i=1..14
 * 0xFF: Infinity
 * Access: RW
 */
MLXSW_ITEM32(reg, sbmm, max_buff, 0x1C, 0, 24);

/* reg_sbmm_pool
 * Association of the port-priority to a pool.
 * Access: RW
 */
MLXSW_ITEM32(reg, sbmm, pool, 0x24, 0, 4);

अटल अंतरभूत व्योम mlxsw_reg_sbmm_pack(अक्षर *payload, u8 prio, u32 min_buff,
				       u32 max_buff, u8 pool)
अणु
	MLXSW_REG_ZERO(sbmm, payload);
	mlxsw_reg_sbmm_prio_set(payload, prio);
	mlxsw_reg_sbmm_min_buff_set(payload, min_buff);
	mlxsw_reg_sbmm_max_buff_set(payload, max_buff);
	mlxsw_reg_sbmm_pool_set(payload, pool);
पूर्ण

/* SBSR - Shared Buffer Status Register
 * ------------------------------------
 * The SBSR रेजिस्टर retrieves the shared buffer occupancy according to
 * Port-Pool. Note that this रेजिस्टर enables पढ़ोing a large amount of data.
 * It is the user's responsibility to limit the amount of data to ensure the
 * response can match the maximum transfer unit. In हाल the response exceeds
 * the maximum transport unit, it will be truncated with no special notice.
 */
#घोषणा MLXSW_REG_SBSR_ID 0xB005
#घोषणा MLXSW_REG_SBSR_BASE_LEN 0x5C /* base length, without records */
#घोषणा MLXSW_REG_SBSR_REC_LEN 0x8 /* record length */
#घोषणा MLXSW_REG_SBSR_REC_MAX_COUNT 120
#घोषणा MLXSW_REG_SBSR_LEN (MLXSW_REG_SBSR_BASE_LEN +	\
			    MLXSW_REG_SBSR_REC_LEN *	\
			    MLXSW_REG_SBSR_REC_MAX_COUNT)

MLXSW_REG_DEFINE(sbsr, MLXSW_REG_SBSR_ID, MLXSW_REG_SBSR_LEN);

/* reg_sbsr_clr
 * Clear Max Buffer Occupancy. When this bit is set, the max_buff_occupancy
 * field is cleared (and a new max value is tracked from the समय the clear
 * was perक्रमmed).
 * Access: OP
 */
MLXSW_ITEM32(reg, sbsr, clr, 0x00, 31, 1);

/* reg_sbsr_ingress_port_mask
 * Bit vector क्रम all ingress network ports.
 * Indicates which of the ports (क्रम which the relevant bit is set)
 * are affected by the set operation. Configuration of any other port
 * करोes not change.
 * Access: Index
 */
MLXSW_ITEM_BIT_ARRAY(reg, sbsr, ingress_port_mask, 0x10, 0x20, 1);

/* reg_sbsr_pg_buff_mask
 * Bit vector क्रम all चयन priority groups.
 * Indicates which of the priorities (क्रम which the relevant bit is set)
 * are affected by the set operation. Configuration of any other priority
 * करोes not change.
 * Range is 0..cap_max_pg_buffers - 1
 * Access: Index
 */
MLXSW_ITEM_BIT_ARRAY(reg, sbsr, pg_buff_mask, 0x30, 0x4, 1);

/* reg_sbsr_egress_port_mask
 * Bit vector क्रम all egress network ports.
 * Indicates which of the ports (क्रम which the relevant bit is set)
 * are affected by the set operation. Configuration of any other port
 * करोes not change.
 * Access: Index
 */
MLXSW_ITEM_BIT_ARRAY(reg, sbsr, egress_port_mask, 0x34, 0x20, 1);

/* reg_sbsr_tclass_mask
 * Bit vector क्रम all traffic classes.
 * Indicates which of the traffic classes (क्रम which the relevant bit is
 * set) are affected by the set operation. Configuration of any other
 * traffic class करोes not change.
 * Range is 0..cap_max_tclass - 1
 * Access: Index
 */
MLXSW_ITEM_BIT_ARRAY(reg, sbsr, tclass_mask, 0x54, 0x8, 1);

अटल अंतरभूत व्योम mlxsw_reg_sbsr_pack(अक्षर *payload, bool clr)
अणु
	MLXSW_REG_ZERO(sbsr, payload);
	mlxsw_reg_sbsr_clr_set(payload, clr);
पूर्ण

/* reg_sbsr_rec_buff_occupancy
 * Current buffer occupancy in cells.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sbsr, rec_buff_occupancy, MLXSW_REG_SBSR_BASE_LEN,
		     0, 24, MLXSW_REG_SBSR_REC_LEN, 0x00, false);

/* reg_sbsr_rec_max_buff_occupancy
 * Maximum value of buffer occupancy in cells monitored. Cleared by
 * writing to the clr field.
 * Access: RO
 */
MLXSW_ITEM32_INDEXED(reg, sbsr, rec_max_buff_occupancy, MLXSW_REG_SBSR_BASE_LEN,
		     0, 24, MLXSW_REG_SBSR_REC_LEN, 0x04, false);

अटल अंतरभूत व्योम mlxsw_reg_sbsr_rec_unpack(अक्षर *payload, पूर्णांक rec_index,
					     u32 *p_buff_occupancy,
					     u32 *p_max_buff_occupancy)
अणु
	*p_buff_occupancy =
		mlxsw_reg_sbsr_rec_buff_occupancy_get(payload, rec_index);
	*p_max_buff_occupancy =
		mlxsw_reg_sbsr_rec_max_buff_occupancy_get(payload, rec_index);
पूर्ण

/* SBIB - Shared Buffer Internal Buffer Register
 * ---------------------------------------------
 * The SBIB रेजिस्टर configures per port buffers क्रम पूर्णांकernal use. The पूर्णांकernal
 * buffers consume memory on the port buffers (note that the port buffers are
 * used also by PBMC).
 *
 * For Spectrum this is used क्रम egress mirroring.
 */
#घोषणा MLXSW_REG_SBIB_ID 0xB006
#घोषणा MLXSW_REG_SBIB_LEN 0x10

MLXSW_REG_DEFINE(sbib, MLXSW_REG_SBIB_ID, MLXSW_REG_SBIB_LEN);

/* reg_sbib_local_port
 * Local port number
 * Not supported क्रम CPU port and router port
 * Access: Index
 */
MLXSW_ITEM32(reg, sbib, local_port, 0x00, 16, 8);

/* reg_sbib_buff_size
 * Units represented in cells
 * Allowed range is 0 to (cap_max_headroom_size - 1)
 * Default is 0
 * Access: RW
 */
MLXSW_ITEM32(reg, sbib, buff_size, 0x08, 0, 24);

अटल अंतरभूत व्योम mlxsw_reg_sbib_pack(अक्षर *payload, u8 local_port,
				       u32 buff_size)
अणु
	MLXSW_REG_ZERO(sbib, payload);
	mlxsw_reg_sbib_local_port_set(payload, local_port);
	mlxsw_reg_sbib_buff_size_set(payload, buff_size);
पूर्ण

अटल स्थिर काष्ठा mlxsw_reg_info *mlxsw_reg_infos[] = अणु
	MLXSW_REG(sgcr),
	MLXSW_REG(spad),
	MLXSW_REG(smid),
	MLXSW_REG(sspr),
	MLXSW_REG(sfdat),
	MLXSW_REG(sfd),
	MLXSW_REG(sfn),
	MLXSW_REG(spms),
	MLXSW_REG(spvid),
	MLXSW_REG(spvm),
	MLXSW_REG(spaft),
	MLXSW_REG(sfgc),
	MLXSW_REG(sftr),
	MLXSW_REG(sfdf),
	MLXSW_REG(sldr),
	MLXSW_REG(slcr),
	MLXSW_REG(slcor),
	MLXSW_REG(spmlr),
	MLXSW_REG(svfa),
	MLXSW_REG(spvtr),
	MLXSW_REG(svpe),
	MLXSW_REG(sfmr),
	MLXSW_REG(spvmlr),
	MLXSW_REG(spvc),
	MLXSW_REG(spevet),
	MLXSW_REG(cwtp),
	MLXSW_REG(cwtpm),
	MLXSW_REG(pgcr),
	MLXSW_REG(ppbt),
	MLXSW_REG(pacl),
	MLXSW_REG(pagt),
	MLXSW_REG(ptar),
	MLXSW_REG(ppbs),
	MLXSW_REG(prcr),
	MLXSW_REG(pefa),
	MLXSW_REG(pemrbt),
	MLXSW_REG(ptce2),
	MLXSW_REG(perpt),
	MLXSW_REG(peabfe),
	MLXSW_REG(perar),
	MLXSW_REG(ptce3),
	MLXSW_REG(percr),
	MLXSW_REG(pererp),
	MLXSW_REG(iedr),
	MLXSW_REG(qpts),
	MLXSW_REG(qpcr),
	MLXSW_REG(qtct),
	MLXSW_REG(qeec),
	MLXSW_REG(qrwe),
	MLXSW_REG(qpdsm),
	MLXSW_REG(qpdp),
	MLXSW_REG(qpdpm),
	MLXSW_REG(qtcपंचांग),
	MLXSW_REG(qpsc),
	MLXSW_REG(pmlp),
	MLXSW_REG(pmtu),
	MLXSW_REG(ptys),
	MLXSW_REG(ppad),
	MLXSW_REG(paos),
	MLXSW_REG(pfcc),
	MLXSW_REG(ppcnt),
	MLXSW_REG(plib),
	MLXSW_REG(pptb),
	MLXSW_REG(pbmc),
	MLXSW_REG(pspa),
	MLXSW_REG(pmaos),
	MLXSW_REG(pplr),
	MLXSW_REG(pmpe),
	MLXSW_REG(pddr),
	MLXSW_REG(pmपंचांग),
	MLXSW_REG(htgt),
	MLXSW_REG(hpkt),
	MLXSW_REG(rgcr),
	MLXSW_REG(ritr),
	MLXSW_REG(rtar),
	MLXSW_REG(ratr),
	MLXSW_REG(rtdp),
	MLXSW_REG(ratrad),
	MLXSW_REG(rdpm),
	MLXSW_REG(ricnt),
	MLXSW_REG(rrcr),
	MLXSW_REG(ralta),
	MLXSW_REG(ralst),
	MLXSW_REG(raltb),
	MLXSW_REG(ralue),
	MLXSW_REG(rauht),
	MLXSW_REG(raleu),
	MLXSW_REG(rauhtd),
	MLXSW_REG(rigr2),
	MLXSW_REG(recr2),
	MLXSW_REG(rmft2),
	MLXSW_REG(rxlte),
	MLXSW_REG(rxlपंचांग),
	MLXSW_REG(rlcmld),
	MLXSW_REG(rlpmce),
	MLXSW_REG(xltq),
	MLXSW_REG(xmdr),
	MLXSW_REG(xrmt),
	MLXSW_REG(xralta),
	MLXSW_REG(xralst),
	MLXSW_REG(xraltb),
	MLXSW_REG(mfcr),
	MLXSW_REG(mfsc),
	MLXSW_REG(mfsm),
	MLXSW_REG(mfsl),
	MLXSW_REG(क्रमe),
	MLXSW_REG(mtcap),
	MLXSW_REG(mपंचांगp),
	MLXSW_REG(mtwe),
	MLXSW_REG(mtbr),
	MLXSW_REG(mcia),
	MLXSW_REG(mpat),
	MLXSW_REG(mpar),
	MLXSW_REG(mgir),
	MLXSW_REG(mrsr),
	MLXSW_REG(mlcr),
	MLXSW_REG(mtpps),
	MLXSW_REG(mtutc),
	MLXSW_REG(mpsc),
	MLXSW_REG(mcqi),
	MLXSW_REG(mcc),
	MLXSW_REG(mcda),
	MLXSW_REG(mgpc),
	MLXSW_REG(mprs),
	MLXSW_REG(mogcr),
	MLXSW_REG(mpagr),
	MLXSW_REG(momte),
	MLXSW_REG(mtpppc),
	MLXSW_REG(mtpptr),
	MLXSW_REG(mtptpt),
	MLXSW_REG(mfgd),
	MLXSW_REG(mgpir),
	MLXSW_REG(mfde),
	MLXSW_REG(tngcr),
	MLXSW_REG(tnumt),
	MLXSW_REG(tnqcr),
	MLXSW_REG(tnqdr),
	MLXSW_REG(tneem),
	MLXSW_REG(tndem),
	MLXSW_REG(tnpc),
	MLXSW_REG(tigcr),
	MLXSW_REG(tieem),
	MLXSW_REG(tidem),
	MLXSW_REG(sbpr),
	MLXSW_REG(sbcm),
	MLXSW_REG(sbpm),
	MLXSW_REG(sbmm),
	MLXSW_REG(sbsr),
	MLXSW_REG(sbib),
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *mlxsw_reg_id_str(u16 reg_id)
अणु
	स्थिर काष्ठा mlxsw_reg_info *reg_info;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_reg_infos); i++) अणु
		reg_info = mlxsw_reg_infos[i];
		अगर (reg_info->id == reg_id)
			वापस reg_info->name;
	पूर्ण
	वापस "*UNKNOWN*";
पूर्ण

/* PUDE - Port Up / Down Event
 * ---------------------------
 * Reports the operational state change of a port.
 */
#घोषणा MLXSW_REG_PUDE_LEN 0x10

/* reg_pude_swid
 * Switch partition ID with which to associate the port.
 * Access: Index
 */
MLXSW_ITEM32(reg, pude, swid, 0x00, 24, 8);

/* reg_pude_local_port
 * Local port number.
 * Access: Index
 */
MLXSW_ITEM32(reg, pude, local_port, 0x00, 16, 8);

/* reg_pude_admin_status
 * Port administrative state (the desired state).
 * 1 - Up.
 * 2 - Down.
 * 3 - Up once. This means that in हाल of link failure, the port won't go
 *     पूर्णांकo polling mode, but will रुको to be re-enabled by software.
 * 4 - Disabled by प्रणाली. Can only be set by hardware.
 * Access: RO
 */
MLXSW_ITEM32(reg, pude, admin_status, 0x00, 8, 4);

/* reg_pude_oper_status
 * Port operatioanl state.
 * 1 - Up.
 * 2 - Down.
 * 3 - Down by port failure. This means that the device will not let the
 *     port up again until explicitly specअगरied by software.
 * Access: RO
 */
MLXSW_ITEM32(reg, pude, oper_status, 0x00, 0, 4);

#पूर्ण_अगर
