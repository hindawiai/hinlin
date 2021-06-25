<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_CLIENT_H_
#घोषणा _I40E_CLIENT_H_

#घोषणा I40E_CLIENT_STR_LENGTH 10

/* Client पूर्णांकerface version should be updated anyसमय there is a change in the
 * existing APIs or data काष्ठाures.
 */
#घोषणा I40E_CLIENT_VERSION_MAJOR 0
#घोषणा I40E_CLIENT_VERSION_MINOR 01
#घोषणा I40E_CLIENT_VERSION_BUILD 00
#घोषणा I40E_CLIENT_VERSION_STR     \
	__stringअगरy(I40E_CLIENT_VERSION_MAJOR) "." \
	__stringअगरy(I40E_CLIENT_VERSION_MINOR) "." \
	__stringअगरy(I40E_CLIENT_VERSION_BUILD)

काष्ठा i40e_client_version अणु
	u8 major;
	u8 minor;
	u8 build;
	u8 rsvd;
पूर्ण;

क्रमागत i40e_client_state अणु
	__I40E_CLIENT_शून्य,
	__I40E_CLIENT_REGISTERED
पूर्ण;

क्रमागत i40e_client_instance_state अणु
	__I40E_CLIENT_INSTANCE_NONE,
	__I40E_CLIENT_INSTANCE_OPENED,
पूर्ण;

काष्ठा i40e_ops;
काष्ठा i40e_client;

#घोषणा I40E_QUEUE_INVALID_IDX	0xFFFF

काष्ठा i40e_qv_info अणु
	u32 v_idx; /* msix_vector */
	u16 ceq_idx;
	u16 aeq_idx;
	u8 itr_idx;
पूर्ण;

काष्ठा i40e_qvlist_info अणु
	u32 num_vectors;
	काष्ठा i40e_qv_info qv_info[1];
पूर्ण;


/* set of LAN parameters useful क्रम clients managed by LAN */

/* Struct to hold per priority info */
काष्ठा i40e_prio_qos_params अणु
	u16 qs_handle; /* qs handle क्रम prio */
	u8 tc; /* TC mapped to prio */
	u8 reserved;
पूर्ण;

#घोषणा I40E_CLIENT_MAX_USER_PRIORITY        8
/* Struct to hold Client QoS */
काष्ठा i40e_qos_params अणु
	काष्ठा i40e_prio_qos_params prio_qos[I40E_CLIENT_MAX_USER_PRIORITY];
पूर्ण;

काष्ठा i40e_params अणु
	काष्ठा i40e_qos_params qos;
	u16 mtu;
पूर्ण;

/* Structure to hold Lan device info क्रम a client device */
काष्ठा i40e_info अणु
	काष्ठा i40e_client_version version;
	u8 lanmac[6];
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pcidev;
	u8 __iomem *hw_addr;
	u8 fid;	/* function id, PF id or VF id */
#घोषणा I40E_CLIENT_FTYPE_PF 0
	u8 ftype; /* function type, PF or VF */
	व्योम *pf;

	/* All L2 params that could change during the lअगरe span of the PF
	 * and needs to be communicated to the client when they change
	 */
	काष्ठा i40e_qvlist_info *qvlist_info;
	काष्ठा i40e_params params;
	काष्ठा i40e_ops *ops;

	u16 msix_count;	 /* number of msix vectors*/
	/* Array करोwn below will be dynamically allocated based on msix_count */
	काष्ठा msix_entry *msix_entries;
	u16 itr_index; /* Which ITR index the PE driver is suppose to use */
	u16 fw_maj_ver;                 /* firmware major version */
	u16 fw_min_ver;                 /* firmware minor version */
	u32 fw_build;                   /* firmware build number */
पूर्ण;

#घोषणा I40E_CLIENT_RESET_LEVEL_PF   1
#घोषणा I40E_CLIENT_RESET_LEVEL_CORE 2
#घोषणा I40E_CLIENT_VSI_FLAG_TCP_ENABLE  BIT(1)

काष्ठा i40e_ops अणु
	/* setup_q_vector_list enables queues with a particular vector */
	पूर्णांक (*setup_qvlist)(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client,
			    काष्ठा i40e_qvlist_info *qv_info);

	पूर्णांक (*virtchnl_send)(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client,
			     u32 vf_id, u8 *msg, u16 len);

	/* If the PE Engine is unresponsive, RDMA driver can request a reset.
	 * The level helps determine the level of reset being requested.
	 */
	व्योम (*request_reset)(काष्ठा i40e_info *ldev,
			      काष्ठा i40e_client *client, u32 level);

	/* API क्रम the RDMA driver to set certain VSI flags that control
	 * PE Engine.
	 */
	पूर्णांक (*update_vsi_ctxt)(काष्ठा i40e_info *ldev,
			       काष्ठा i40e_client *client,
			       bool is_vf, u32 vf_id,
			       u32 flag, u32 valid_flag);
पूर्ण;

काष्ठा i40e_client_ops अणु
	/* Should be called from रेजिस्टर_client() or whenever PF is पढ़ोy
	 * to create a specअगरic client instance.
	 */
	पूर्णांक (*खोलो)(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client);

	/* Should be called when netdev is unavailable or when unरेजिस्टर
	 * call comes in. If the बंद is happenening due to a reset being
	 * triggered set the reset bit to true.
	 */
	व्योम (*बंद)(काष्ठा i40e_info *ldev, काष्ठा i40e_client *client,
		      bool reset);

	/* called when some l2 managed parameters changes - mtu */
	व्योम (*l2_param_change)(काष्ठा i40e_info *ldev,
				काष्ठा i40e_client *client,
				काष्ठा i40e_params *params);

	पूर्णांक (*virtchnl_receive)(काष्ठा i40e_info *ldev,
				काष्ठा i40e_client *client, u32 vf_id,
				u8 *msg, u16 len);

	/* called when a VF is reset by the PF */
	व्योम (*vf_reset)(काष्ठा i40e_info *ldev,
			 काष्ठा i40e_client *client, u32 vf_id);

	/* called when the number of VFs changes */
	व्योम (*vf_enable)(काष्ठा i40e_info *ldev,
			  काष्ठा i40e_client *client, u32 num_vfs);

	/* वापसs true अगर VF is capable of specअगरied offload */
	पूर्णांक (*vf_capable)(काष्ठा i40e_info *ldev,
			  काष्ठा i40e_client *client, u32 vf_id);
पूर्ण;

/* Client device */
काष्ठा i40e_client_instance अणु
	काष्ठा list_head list;
	काष्ठा i40e_info lan_info;
	काष्ठा i40e_client *client;
	अचिन्हित दीर्घ  state;
पूर्ण;

काष्ठा i40e_client अणु
	काष्ठा list_head list;		/* list of रेजिस्टरed clients */
	अक्षर name[I40E_CLIENT_STR_LENGTH];
	काष्ठा i40e_client_version version;
	अचिन्हित दीर्घ state;		/* client state */
	atomic_t ref_cnt;  /* Count of all the client devices of this kind */
	u32 flags;
	u8 type;
#घोषणा I40E_CLIENT_IWARP 0
	स्थिर काष्ठा i40e_client_ops *ops; /* client ops provided by the client */
पूर्ण;

अटल अंतरभूत bool i40e_client_is_रेजिस्टरed(काष्ठा i40e_client *client)
अणु
	वापस test_bit(__I40E_CLIENT_REGISTERED, &client->state);
पूर्ण

/* used by clients */
पूर्णांक i40e_रेजिस्टर_client(काष्ठा i40e_client *client);
पूर्णांक i40e_unरेजिस्टर_client(काष्ठा i40e_client *client);

#पूर्ण_अगर /* _I40E_CLIENT_H_ */
