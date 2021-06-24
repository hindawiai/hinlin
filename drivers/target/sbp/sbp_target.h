<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SBP_BASE_H
#घोषणा _SBP_BASE_H

#समावेश <linux/firewire.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <target/target_core_base.h>

#घोषणा SBP_VERSION  "v0.1"
#घोषणा SBP_NAMELEN 32

#घोषणा SBP_ORB_FETCH_SIZE	8

#घोषणा MANAGEMENT_AGENT_STATE_IDLE	0
#घोषणा MANAGEMENT_AGENT_STATE_BUSY	1

#घोषणा ORB_NOTIFY(v)			(((v) >> 31) & 0x01)
#घोषणा ORB_REQUEST_FORMAT(v)		(((v) >> 29) & 0x03)

#घोषणा MANAGEMENT_ORB_FUNCTION(v)	(((v) >> 16) & 0x0f)

#घोषणा MANAGEMENT_ORB_FUNCTION_LOGIN			0x0
#घोषणा MANAGEMENT_ORB_FUNCTION_QUERY_LOGINS		0x1
#घोषणा MANAGEMENT_ORB_FUNCTION_RECONNECT		0x3
#घोषणा MANAGEMENT_ORB_FUNCTION_SET_PASSWORD		0x4
#घोषणा MANAGEMENT_ORB_FUNCTION_LOGOUT			0x7
#घोषणा MANAGEMENT_ORB_FUNCTION_ABORT_TASK		0xb
#घोषणा MANAGEMENT_ORB_FUNCTION_ABORT_TASK_SET		0xc
#घोषणा MANAGEMENT_ORB_FUNCTION_LOGICAL_UNIT_RESET	0xe
#घोषणा MANAGEMENT_ORB_FUNCTION_TARGET_RESET		0xf

#घोषणा LOGIN_ORB_EXCLUSIVE(v)		(((v) >> 28) &   0x01)
#घोषणा LOGIN_ORB_RESERVED(v)		(((v) >> 24) &   0x0f)
#घोषणा LOGIN_ORB_RECONNECT(v)		(((v) >> 20) &   0x0f)
#घोषणा LOGIN_ORB_LUN(v)		(((v) >>  0) & 0xffff)
#घोषणा LOGIN_ORB_PASSWORD_LENGTH(v)	(((v) >> 16) & 0xffff)
#घोषणा LOGIN_ORB_RESPONSE_LENGTH(v)	(((v) >>  0) & 0xffff)

#घोषणा RECONNECT_ORB_LOGIN_ID(v)	(((v) >>  0) & 0xffff)
#घोषणा LOGOUT_ORB_LOGIN_ID(v)		(((v) >>  0) & 0xffff)

#घोषणा CMDBLK_ORB_सूचीECTION(v)		(((v) >> 27) &   0x01)
#घोषणा CMDBLK_ORB_SPEED(v)		(((v) >> 24) &   0x07)
#घोषणा CMDBLK_ORB_MAX_PAYLOAD(v)	(((v) >> 20) &   0x0f)
#घोषणा CMDBLK_ORB_PG_TBL_PRESENT(v)	(((v) >> 19) &   0x01)
#घोषणा CMDBLK_ORB_PG_SIZE(v)		(((v) >> 16) &   0x07)
#घोषणा CMDBLK_ORB_DATA_SIZE(v)		(((v) >>  0) & 0xffff)

#घोषणा STATUS_BLOCK_SRC(v)		(((v) &   0x03) << 30)
#घोषणा STATUS_BLOCK_RESP(v)		(((v) &   0x03) << 28)
#घोषणा STATUS_BLOCK_DEAD(v)		(((v) ? 1 : 0)  << 27)
#घोषणा STATUS_BLOCK_LEN(v)		(((v) &   0x07) << 24)
#घोषणा STATUS_BLOCK_SBP_STATUS(v)	(((v) &   0xff) << 16)
#घोषणा STATUS_BLOCK_ORB_OFFSET_HIGH(v)	(((v) & 0xffff) <<  0)

#घोषणा STATUS_SRC_ORB_CONTINUING	0
#घोषणा STATUS_SRC_ORB_FINISHED		1
#घोषणा STATUS_SRC_UNSOLICITED		2

#घोषणा STATUS_RESP_REQUEST_COMPLETE	0
#घोषणा STATUS_RESP_TRANSPORT_FAILURE	1
#घोषणा STATUS_RESP_ILLEGAL_REQUEST	2
#घोषणा STATUS_RESP_VENDOR_DEPENDENT	3

#घोषणा SBP_STATUS_OK			0
#घोषणा SBP_STATUS_REQ_TYPE_NOTSUPP	1
#घोषणा SBP_STATUS_SPEED_NOTSUPP	2
#घोषणा SBP_STATUS_PAGE_SIZE_NOTSUPP	3
#घोषणा SBP_STATUS_ACCESS_DENIED	4
#घोषणा SBP_STATUS_LUN_NOTSUPP		5
#घोषणा SBP_STATUS_PAYLOAD_TOO_SMALL	6
/* 7 is reserved */
#घोषणा SBP_STATUS_RESOURCES_UNAVAIL	8
#घोषणा SBP_STATUS_FUNCTION_REJECTED	9
#घोषणा SBP_STATUS_LOGIN_ID_UNKNOWN	10
#घोषणा SBP_STATUS_DUMMY_ORB_COMPLETE	11
#घोषणा SBP_STATUS_REQUEST_ABORTED	12
#घोषणा SBP_STATUS_UNSPECIFIED_ERROR	0xff

#घोषणा AGENT_STATE_RESET	0
#घोषणा AGENT_STATE_ACTIVE	1
#घोषणा AGENT_STATE_SUSPENDED	2
#घोषणा AGENT_STATE_DEAD	3

काष्ठा sbp2_poपूर्णांकer अणु
	__be32 high;
	__be32 low;
पूर्ण;

काष्ठा sbp_command_block_orb अणु
	काष्ठा sbp2_poपूर्णांकer next_orb;
	काष्ठा sbp2_poपूर्णांकer data_descriptor;
	__be32 misc;
	u8 command_block[12];
पूर्ण;

काष्ठा sbp_page_table_entry अणु
	__be16 segment_length;
	__be16 segment_base_hi;
	__be32 segment_base_lo;
पूर्ण;

काष्ठा sbp_management_orb अणु
	काष्ठा sbp2_poपूर्णांकer ptr1;
	काष्ठा sbp2_poपूर्णांकer ptr2;
	__be32 misc;
	__be32 length;
	काष्ठा sbp2_poपूर्णांकer status_fअगरo;
पूर्ण;

काष्ठा sbp_status_block अणु
	__be32 status;
	__be32 orb_low;
	u8 data[24];
पूर्ण;

काष्ठा sbp_login_response_block अणु
	__be32 misc;
	काष्ठा sbp2_poपूर्णांकer command_block_agent;
	__be32 reconnect_hold;
पूर्ण;

काष्ठा sbp_login_descriptor अणु
	काष्ठा sbp_session *sess;
	काष्ठा list_head link;

	u32 login_lun;

	u64 status_fअगरo_addr;
	पूर्णांक exclusive;
	u16 login_id;

	काष्ठा sbp_target_agent *tgt_agt;
पूर्ण;

काष्ठा sbp_session अणु
	spinlock_t lock;
	काष्ठा se_session *se_sess;
	काष्ठा list_head login_list;
	काष्ठा delayed_work मुख्यt_work;

	u64 guid; /* login_owner_EUI_64 */
	पूर्णांक node_id; /* login_owner_ID */

	काष्ठा fw_card *card;
	पूर्णांक generation;
	पूर्णांक speed;

	पूर्णांक reconnect_hold;
	u64 reconnect_expires;
पूर्ण;

काष्ठा sbp_tpg अणु
	/* Target portal group tag क्रम TCM */
	u16 tport_tpgt;
	/* Poपूर्णांकer back to sbp_tport */
	काष्ठा sbp_tport *tport;
	/* Returned by sbp_make_tpg() */
	काष्ठा se_portal_group se_tpg;
पूर्ण;

काष्ठा sbp_tport अणु
	/* Target Unit Identअगरier (EUI-64) */
	u64 guid;
	/* Target port name */
	अक्षर tport_name[SBP_NAMELEN];
	/* Returned by sbp_make_tport() */
	काष्ठा se_wwn tport_wwn;

	काष्ठा sbp_tpg *tpg;

	/* FireWire unit directory */
	काष्ठा fw_descriptor unit_directory;

	/* SBP Management Agent */
	काष्ठा sbp_management_agent *mgt_agt;

	/* Parameters */
	पूर्णांक enable;
	s32 directory_id;
	पूर्णांक mgt_orb_समयout;
	पूर्णांक max_reconnect_समयout;
	पूर्णांक max_logins_per_lun;
पूर्ण;

अटल अंतरभूत u64 sbp2_poपूर्णांकer_to_addr(स्थिर काष्ठा sbp2_poपूर्णांकer *ptr)
अणु
	वापस (u64)(be32_to_cpu(ptr->high) & 0x0000ffff) << 32 |
		(be32_to_cpu(ptr->low) & 0xfffffffc);
पूर्ण

अटल अंतरभूत व्योम addr_to_sbp2_poपूर्णांकer(u64 addr, काष्ठा sbp2_poपूर्णांकer *ptr)
अणु
	ptr->high = cpu_to_be32(addr >> 32);
	ptr->low = cpu_to_be32(addr);
पूर्ण

काष्ठा sbp_target_agent अणु
	spinlock_t lock;
	काष्ठा fw_address_handler handler;
	काष्ठा sbp_login_descriptor *login;
	पूर्णांक state;
	काष्ठा work_काष्ठा work;
	u64 orb_poपूर्णांकer;
	bool करोorbell;
पूर्ण;

काष्ठा sbp_target_request अणु
	काष्ठा sbp_login_descriptor *login;
	u64 orb_poपूर्णांकer;
	काष्ठा sbp_command_block_orb orb;
	काष्ठा sbp_status_block status;
	काष्ठा work_काष्ठा work;

	काष्ठा se_cmd se_cmd;
	काष्ठा sbp_page_table_entry *pg_tbl;
	व्योम *cmd_buf;

	अचिन्हित अक्षर sense_buf[TRANSPORT_SENSE_BUFFER];
पूर्ण;

काष्ठा sbp_management_agent अणु
	spinlock_t lock;
	काष्ठा sbp_tport *tport;
	काष्ठा fw_address_handler handler;
	पूर्णांक state;
	काष्ठा work_काष्ठा work;
	u64 orb_offset;
	काष्ठा sbp_management_request *request;
पूर्ण;

काष्ठा sbp_management_request अणु
	काष्ठा sbp_management_orb orb;
	काष्ठा sbp_status_block status;
	काष्ठा fw_card *card;
	पूर्णांक generation;
	पूर्णांक node_addr;
	पूर्णांक speed;
पूर्ण;

#पूर्ण_अगर
