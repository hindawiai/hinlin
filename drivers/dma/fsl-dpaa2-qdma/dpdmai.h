<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 NXP */

#अगर_अघोषित __FSL_DPDMAI_H
#घोषणा __FSL_DPDMAI_H

/* DPDMAI Version */
#घोषणा DPDMAI_VER_MAJOR	2
#घोषणा DPDMAI_VER_MINOR	2

#घोषणा DPDMAI_CMD_BASE_VERSION	0
#घोषणा DPDMAI_CMD_ID_OFFSET	4

#घोषणा DPDMAI_CMDID_FORMAT(x)	(((x) << DPDMAI_CMD_ID_OFFSET) | \
				DPDMAI_CMD_BASE_VERSION)

/* Command IDs */
#घोषणा DPDMAI_CMDID_CLOSE		DPDMAI_CMDID_FORMAT(0x800)
#घोषणा DPDMAI_CMDID_OPEN               DPDMAI_CMDID_FORMAT(0x80E)
#घोषणा DPDMAI_CMDID_CREATE             DPDMAI_CMDID_FORMAT(0x90E)
#घोषणा DPDMAI_CMDID_DESTROY            DPDMAI_CMDID_FORMAT(0x900)

#घोषणा DPDMAI_CMDID_ENABLE             DPDMAI_CMDID_FORMAT(0x002)
#घोषणा DPDMAI_CMDID_DISABLE            DPDMAI_CMDID_FORMAT(0x003)
#घोषणा DPDMAI_CMDID_GET_ATTR           DPDMAI_CMDID_FORMAT(0x004)
#घोषणा DPDMAI_CMDID_RESET              DPDMAI_CMDID_FORMAT(0x005)
#घोषणा DPDMAI_CMDID_IS_ENABLED         DPDMAI_CMDID_FORMAT(0x006)

#घोषणा DPDMAI_CMDID_SET_IRQ            DPDMAI_CMDID_FORMAT(0x010)
#घोषणा DPDMAI_CMDID_GET_IRQ            DPDMAI_CMDID_FORMAT(0x011)
#घोषणा DPDMAI_CMDID_SET_IRQ_ENABLE     DPDMAI_CMDID_FORMAT(0x012)
#घोषणा DPDMAI_CMDID_GET_IRQ_ENABLE     DPDMAI_CMDID_FORMAT(0x013)
#घोषणा DPDMAI_CMDID_SET_IRQ_MASK       DPDMAI_CMDID_FORMAT(0x014)
#घोषणा DPDMAI_CMDID_GET_IRQ_MASK       DPDMAI_CMDID_FORMAT(0x015)
#घोषणा DPDMAI_CMDID_GET_IRQ_STATUS     DPDMAI_CMDID_FORMAT(0x016)
#घोषणा DPDMAI_CMDID_CLEAR_IRQ_STATUS	DPDMAI_CMDID_FORMAT(0x017)

#घोषणा DPDMAI_CMDID_SET_RX_QUEUE	DPDMAI_CMDID_FORMAT(0x1A0)
#घोषणा DPDMAI_CMDID_GET_RX_QUEUE       DPDMAI_CMDID_FORMAT(0x1A1)
#घोषणा DPDMAI_CMDID_GET_TX_QUEUE       DPDMAI_CMDID_FORMAT(0x1A2)

#घोषणा MC_CMD_HDR_TOKEN_O 32  /* Token field offset */
#घोषणा MC_CMD_HDR_TOKEN_S 16  /* Token field size */

#घोषणा MAKE_UMASK64(_width) \
	((u64)((_width) < 64 ? ((u64)1 << (_width)) - 1 : (u64)-1))

/* Data Path DMA Interface API
 * Contains initialization APIs and runसमय control APIs क्रम DPDMAI
 */

/**
 * Maximum number of Tx/Rx priorities per DPDMAI object
 */
#घोषणा DPDMAI_PRIO_NUM		2

/* DPDMAI queue modअगरication options */

/**
 * Select to modअगरy the user's context associated with the queue
 */
#घोषणा DPDMAI_QUEUE_OPT_USER_CTX	0x1

/**
 * Select to modअगरy the queue's destination
 */
#घोषणा DPDMAI_QUEUE_OPT_DEST		0x2

/**
 * काष्ठा dpdmai_cfg - Structure representing DPDMAI configuration
 * @priorities: Priorities क्रम the DMA hardware processing; valid priorities are
 *	configured with values 1-8; the entry following last valid entry
 *	should be configured with 0
 */
काष्ठा dpdmai_cfg अणु
	u8 priorities[DPDMAI_PRIO_NUM];
पूर्ण;

/**
 * काष्ठा dpdmai_attr - Structure representing DPDMAI attributes
 * @id: DPDMAI object ID
 * @version: DPDMAI version
 * @num_of_priorities: number of priorities
 */
काष्ठा dpdmai_attr अणु
	पूर्णांक	id;
	/**
	 * काष्ठा version - DPDMAI version
	 * @major: DPDMAI major version
	 * @minor: DPDMAI minor version
	 */
	काष्ठा अणु
		u16 major;
		u16 minor;
	पूर्ण version;
	u8 num_of_priorities;
पूर्ण;

/**
 * क्रमागत dpdmai_dest - DPDMAI destination types
 * @DPDMAI_DEST_NONE: Unasचिन्हित destination; The queue is set in parked mode
 *	and करोes not generate FQDAN notअगरications; user is expected to dequeue
 *	from the queue based on polling or other user-defined method
 * @DPDMAI_DEST_DPIO: The queue is set in schedule mode and generates FQDAN
 *	notअगरications to the specअगरied DPIO; user is expected to dequeue
 *	from the queue only after notअगरication is received
 * @DPDMAI_DEST_DPCON: The queue is set in schedule mode and करोes not generate
 *	FQDAN notअगरications, but is connected to the specअगरied DPCON object;
 *	user is expected to dequeue from the DPCON channel
 */
क्रमागत dpdmai_dest अणु
	DPDMAI_DEST_NONE = 0,
	DPDMAI_DEST_DPIO = 1,
	DPDMAI_DEST_DPCON = 2
पूर्ण;

/**
 * काष्ठा dpdmai_dest_cfg - Structure representing DPDMAI destination parameters
 * @dest_type: Destination type
 * @dest_id: Either DPIO ID or DPCON ID, depending on the destination type
 * @priority: Priority selection within the DPIO or DPCON channel; valid values
 *	are 0-1 or 0-7, depending on the number of priorities in that
 *	channel; not relevant क्रम 'DPDMAI_DEST_NONE' option
 */
काष्ठा dpdmai_dest_cfg अणु
	क्रमागत dpdmai_dest dest_type;
	पूर्णांक dest_id;
	u8 priority;
पूर्ण;

/**
 * काष्ठा dpdmai_rx_queue_cfg - DPDMAI RX queue configuration
 * @options: Flags representing the suggested modअगरications to the queue;
 *	Use any combination of 'DPDMAI_QUEUE_OPT_<X>' flags
 * @user_ctx: User context value provided in the frame descriptor of each
 *	dequeued frame;
 *	valid only अगर 'DPDMAI_QUEUE_OPT_USER_CTX' is contained in 'options'
 * @dest_cfg: Queue destination parameters;
 *	valid only अगर 'DPDMAI_QUEUE_OPT_DEST' is contained in 'options'
 */
काष्ठा dpdmai_rx_queue_cfg अणु
	काष्ठा dpdmai_dest_cfg dest_cfg;
	u32 options;
	u64 user_ctx;

पूर्ण;

/**
 * काष्ठा dpdmai_rx_queue_attr - Structure representing attributes of Rx queues
 * @user_ctx:  User context value provided in the frame descriptor of each
 *	 dequeued frame
 * @dest_cfg: Queue destination configuration
 * @fqid: Virtual FQID value to be used क्रम dequeue operations
 */
काष्ठा dpdmai_rx_queue_attr अणु
	काष्ठा dpdmai_dest_cfg	dest_cfg;
	u64 user_ctx;
	u32 fqid;
पूर्ण;

पूर्णांक dpdmai_खोलो(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
		पूर्णांक dpdmai_id, u16 *token);
पूर्णांक dpdmai_बंद(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);
पूर्णांक dpdmai_destroy(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);
पूर्णांक dpdmai_create(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
		  स्थिर काष्ठा dpdmai_cfg *cfg, u16 *token);
पूर्णांक dpdmai_enable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);
पूर्णांक dpdmai_disable(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);
पूर्णांक dpdmai_reset(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token);
पूर्णांक dpdmai_get_attributes(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			  u16 token, काष्ठा dpdmai_attr	*attr);
पूर्णांक dpdmai_set_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 priority, स्थिर काष्ठा dpdmai_rx_queue_cfg *cfg);
पूर्णांक dpdmai_get_rx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			u8 priority, काष्ठा dpdmai_rx_queue_attr *attr);
पूर्णांक dpdmai_get_tx_queue(काष्ठा fsl_mc_io *mc_io, u32 cmd_flags,
			u16 token, u8 priority, u32 *fqid);

#पूर्ण_अगर /* __FSL_DPDMAI_H */
