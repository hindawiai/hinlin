<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010 Cisco Systems, Inc.
 */
#अगर_अघोषित __TCM_FC_H__
#घोषणा __TCM_FC_H__

#समावेश <linux/types.h>
#समावेश <target/target_core_base.h>

#घोषणा FT_VERSION "0.4"

#घोषणा FT_NAMELEN 32		/* length of ASCII WWPNs including pad */
#घोषणा FT_TPG_NAMELEN 32	/* max length of TPG name */
#घोषणा FT_LUN_NAMELEN 32	/* max length of LUN name */
#घोषणा TCM_FC_DEFAULT_TAGS 512	/* tags used क्रम per-session pपुनः_स्मृतिation */

काष्ठा ft_transport_id अणु
	__u8	क्रमmat;
	__u8	__resvd1[7];
	__u8	wwpn[8];
	__u8	__resvd2[8];
पूर्ण __attribute__((__packed__));

/*
 * Session (remote port).
 */
काष्ठा ft_sess अणु
	u32 port_id;			/* क्रम hash lookup use only */
	u32 params;
	u16 max_frame;			/* maximum frame size */
	u64 port_name;			/* port name क्रम transport ID */
	काष्ठा ft_tport *tport;
	काष्ठा se_session *se_sess;
	काष्ठा hlist_node hash;		/* linkage in ft_sess_hash table */
	काष्ठा rcu_head rcu;
	काष्ठा kref kref;		/* ref क्रम hash and outstanding I/Os */
पूर्ण;

/*
 * Hash table of sessions per local port.
 * Hash lookup by remote port FC_ID.
 */
#घोषणा	FT_SESS_HASH_BITS	6
#घोषणा	FT_SESS_HASH_SIZE	(1 << FT_SESS_HASH_BITS)

/*
 * Per local port data.
 * This is created only after a TPG exists that allows target function
 * क्रम the local port.  If the TPG exists, this is allocated when
 * we're notअगरied that the local port has been created, or when
 * the first PRLI provider callback is received.
 */
काष्ठा ft_tport अणु
	काष्ठा fc_lport *lport;
	काष्ठा ft_tpg *tpg;		/* शून्य अगर TPG deleted beक्रमe tport */
	u32	sess_count;		/* number of sessions in hash */
	काष्ठा rcu_head rcu;
	काष्ठा hlist_head hash[FT_SESS_HASH_SIZE];	/* list of sessions */
पूर्ण;

/*
 * Node ID and authentication.
 */
काष्ठा ft_node_auth अणु
	u64	port_name;
	u64	node_name;
पूर्ण;

/*
 * Node ACL क्रम FC remote port session.
 */
काष्ठा ft_node_acl अणु
	काष्ठा se_node_acl se_node_acl;
	काष्ठा ft_node_auth node_auth;
पूर्ण;

काष्ठा ft_lun अणु
	u32 index;
	अक्षर name[FT_LUN_NAMELEN];
पूर्ण;

/*
 * Target portal group (local port).
 */
काष्ठा ft_tpg अणु
	u32 index;
	काष्ठा ft_lport_wwn *lport_wwn;
	काष्ठा ft_tport *tport;		/* active tport or शून्य */
	काष्ठा list_head lun_list;	/* head of LUNs */
	काष्ठा se_portal_group se_tpg;
	काष्ठा workqueue_काष्ठा *workqueue;
पूर्ण;

काष्ठा ft_lport_wwn अणु
	u64 wwpn;
	अक्षर name[FT_NAMELEN];
	काष्ठा list_head ft_wwn_node;
	काष्ठा ft_tpg *tpg;
	काष्ठा se_wwn se_wwn;
पूर्ण;

/*
 * Commands
 */
काष्ठा ft_cmd अणु
	काष्ठा ft_sess *sess;		/* session held क्रम cmd */
	काष्ठा fc_seq *seq;		/* sequence in exchange mgr */
	काष्ठा se_cmd se_cmd;		/* Local TCM I/O descriptor */
	काष्ठा fc_frame *req_frame;
	u32 ग_लिखो_data_len;		/* data received on ग_लिखोs */
	काष्ठा work_काष्ठा work;
	/* Local sense buffer */
	अचिन्हित अक्षर ft_sense_buffer[TRANSPORT_SENSE_BUFFER];
	u32 was_ddp_setup:1;		/* Set only अगर ddp is setup */
	u32 पातed:1;			/* Set अगर पातed by reset or समयout */
	काष्ठा scatterlist *sg;		/* Set only अगर DDP is setup */
	u32 sg_cnt;			/* No. of item in scatterlist */
पूर्ण;

बाह्य काष्ठा mutex ft_lport_lock;
बाह्य काष्ठा fc4_prov ft_prov;
बाह्य अचिन्हित पूर्णांक ft_debug_logging;

/*
 * Fabric methods.
 */

/*
 * Session ops.
 */
व्योम ft_sess_put(काष्ठा ft_sess *);
व्योम ft_sess_बंद(काष्ठा se_session *);
u32 ft_sess_get_index(काष्ठा se_session *);
u32 ft_sess_get_port_name(काष्ठा se_session *, अचिन्हित अक्षर *, u32);

व्योम ft_lport_add(काष्ठा fc_lport *, व्योम *);
व्योम ft_lport_del(काष्ठा fc_lport *, व्योम *);
पूर्णांक ft_lport_notअगरy(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);

/*
 * IO methods.
 */
पूर्णांक ft_check_stop_मुक्त(काष्ठा se_cmd *);
व्योम ft_release_cmd(काष्ठा se_cmd *);
पूर्णांक ft_queue_status(काष्ठा se_cmd *);
पूर्णांक ft_queue_data_in(काष्ठा se_cmd *);
पूर्णांक ft_ग_लिखो_pending(काष्ठा se_cmd *);
पूर्णांक ft_get_cmd_state(काष्ठा se_cmd *);
व्योम ft_queue_पंचांग_resp(काष्ठा se_cmd *);
व्योम ft_पातed_task(काष्ठा se_cmd *);

/*
 * other पूर्णांकernal functions.
 */
व्योम ft_recv_req(काष्ठा ft_sess *, काष्ठा fc_frame *);
काष्ठा ft_tpg *ft_lport_find_tpg(काष्ठा fc_lport *);

व्योम ft_recv_ग_लिखो_data(काष्ठा ft_cmd *, काष्ठा fc_frame *);
व्योम ft_dump_cmd(काष्ठा ft_cmd *, स्थिर अक्षर *caller);

sमाप_प्रकार ft_क्रमmat_wwn(अक्षर *, माप_प्रकार, u64);

/*
 * Underlying HW specअगरic helper function
 */
व्योम ft_invl_hw_context(काष्ठा ft_cmd *);

#पूर्ण_अगर /* __TCM_FC_H__ */
