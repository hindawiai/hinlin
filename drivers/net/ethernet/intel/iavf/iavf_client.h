<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _IAVF_CLIENT_H_
#घोषणा _IAVF_CLIENT_H_

#घोषणा IAVF_CLIENT_STR_LENGTH 10

/* Client पूर्णांकerface version should be updated anyसमय there is a change in the
 * existing APIs or data काष्ठाures.
 */
#घोषणा IAVF_CLIENT_VERSION_MAJOR 0
#घोषणा IAVF_CLIENT_VERSION_MINOR 01
#घोषणा IAVF_CLIENT_VERSION_BUILD 00
#घोषणा IAVF_CLIENT_VERSION_STR     \
	__stringअगरy(IAVF_CLIENT_VERSION_MAJOR) "." \
	__stringअगरy(IAVF_CLIENT_VERSION_MINOR) "." \
	__stringअगरy(IAVF_CLIENT_VERSION_BUILD)

काष्ठा iavf_client_version अणु
	u8 major;
	u8 minor;
	u8 build;
	u8 rsvd;
पूर्ण;

क्रमागत iavf_client_state अणु
	__IAVF_CLIENT_शून्य,
	__IAVF_CLIENT_REGISTERED
पूर्ण;

क्रमागत iavf_client_instance_state अणु
	__IAVF_CLIENT_INSTANCE_NONE,
	__IAVF_CLIENT_INSTANCE_OPENED,
पूर्ण;

काष्ठा iavf_ops;
काष्ठा iavf_client;

/* HW करोes not define a type value क्रम AEQ; only क्रम RX/TX and CEQ.
 * In order क्रम us to keep the पूर्णांकerface simple, SW will define a
 * unique type value क्रम AEQ.
 */
#घोषणा IAVF_QUEUE_TYPE_PE_AEQ	0x80
#घोषणा IAVF_QUEUE_INVALID_IDX	0xFFFF

काष्ठा iavf_qv_info अणु
	u32 v_idx; /* msix_vector */
	u16 ceq_idx;
	u16 aeq_idx;
	u8 itr_idx;
पूर्ण;

काष्ठा iavf_qvlist_info अणु
	u32 num_vectors;
	काष्ठा iavf_qv_info qv_info[1];
पूर्ण;

#घोषणा IAVF_CLIENT_MSIX_ALL 0xFFFFFFFF

/* set of LAN parameters useful क्रम clients managed by LAN */

/* Struct to hold per priority info */
काष्ठा iavf_prio_qos_params अणु
	u16 qs_handle; /* qs handle क्रम prio */
	u8 tc; /* TC mapped to prio */
	u8 reserved;
पूर्ण;

#घोषणा IAVF_CLIENT_MAX_USER_PRIORITY	8
/* Struct to hold Client QoS */
काष्ठा iavf_qos_params अणु
	काष्ठा iavf_prio_qos_params prio_qos[IAVF_CLIENT_MAX_USER_PRIORITY];
पूर्ण;

काष्ठा iavf_params अणु
	काष्ठा iavf_qos_params qos;
	u16 mtu;
	u16 link_up; /* boolean */
पूर्ण;

/* Structure to hold LAN device info क्रम a client device */
काष्ठा iavf_info अणु
	काष्ठा iavf_client_version version;
	u8 lanmac[6];
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pcidev;
	u8 __iomem *hw_addr;
	u8 fid;	/* function id, PF id or VF id */
#घोषणा IAVF_CLIENT_FTYPE_PF 0
#घोषणा IAVF_CLIENT_FTYPE_VF 1
	u8 ftype; /* function type, PF or VF */
	व्योम *vf; /* cast to iavf_adapter */

	/* All L2 params that could change during the lअगरe span of the device
	 * and needs to be communicated to the client when they change
	 */
	काष्ठा iavf_params params;
	काष्ठा iavf_ops *ops;

	u16 msix_count;	 /* number of msix vectors*/
	/* Array करोwn below will be dynamically allocated based on msix_count */
	काष्ठा msix_entry *msix_entries;
	u16 itr_index; /* Which ITR index the PE driver is suppose to use */
पूर्ण;

काष्ठा iavf_ops अणु
	/* setup_q_vector_list enables queues with a particular vector */
	पूर्णांक (*setup_qvlist)(काष्ठा iavf_info *ldev, काष्ठा iavf_client *client,
			    काष्ठा iavf_qvlist_info *qv_info);

	u32 (*virtchnl_send)(काष्ठा iavf_info *ldev, काष्ठा iavf_client *client,
			     u8 *msg, u16 len);

	/* If the PE Engine is unresponsive, RDMA driver can request a reset.*/
	व्योम (*request_reset)(काष्ठा iavf_info *ldev,
			      काष्ठा iavf_client *client);
पूर्ण;

काष्ठा iavf_client_ops अणु
	/* Should be called from रेजिस्टर_client() or whenever the driver is
	 * पढ़ोy to create a specअगरic client instance.
	 */
	पूर्णांक (*खोलो)(काष्ठा iavf_info *ldev, काष्ठा iavf_client *client);

	/* Should be बंदd when netdev is unavailable or when unरेजिस्टर
	 * call comes in. If the बंद happens due to a reset, set the reset
	 * bit to true.
	 */
	व्योम (*बंद)(काष्ठा iavf_info *ldev, काष्ठा iavf_client *client,
		      bool reset);

	/* called when some l2 managed parameters changes - mss */
	व्योम (*l2_param_change)(काष्ठा iavf_info *ldev,
				काष्ठा iavf_client *client,
				काष्ठा iavf_params *params);

	/* called when a message is received from the PF */
	पूर्णांक (*virtchnl_receive)(काष्ठा iavf_info *ldev,
				काष्ठा iavf_client *client,
				u8 *msg, u16 len);
पूर्ण;

/* Client device */
काष्ठा iavf_client_instance अणु
	काष्ठा list_head list;
	काष्ठा iavf_info lan_info;
	काष्ठा iavf_client *client;
	अचिन्हित दीर्घ  state;
पूर्ण;

काष्ठा iavf_client अणु
	काष्ठा list_head list;		/* list of रेजिस्टरed clients */
	अक्षर name[IAVF_CLIENT_STR_LENGTH];
	काष्ठा iavf_client_version version;
	अचिन्हित दीर्घ state;		/* client state */
	atomic_t ref_cnt;  /* Count of all the client devices of this kind */
	u32 flags;
#घोषणा IAVF_CLIENT_FLAGS_LAUNCH_ON_PROBE	BIT(0)
#घोषणा IAVF_TX_FLAGS_NOTIFY_OTHER_EVENTS	BIT(2)
	u8 type;
#घोषणा IAVF_CLIENT_IWARP 0
	काष्ठा iavf_client_ops *ops;	/* client ops provided by the client */
पूर्ण;

/* used by clients */
पूर्णांक iavf_रेजिस्टर_client(काष्ठा iavf_client *client);
पूर्णांक iavf_unरेजिस्टर_client(काष्ठा iavf_client *client);
#पूर्ण_अगर /* _IAVF_CLIENT_H_ */
