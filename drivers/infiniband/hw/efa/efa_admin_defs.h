<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2021 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_ADMIN_H_
#घोषणा _EFA_ADMIN_H_

क्रमागत efa_admin_aq_completion_status अणु
	EFA_ADMIN_SUCCESS                           = 0,
	EFA_ADMIN_RESOURCE_ALLOCATION_FAILURE       = 1,
	EFA_ADMIN_BAD_OPCODE                        = 2,
	EFA_ADMIN_UNSUPPORTED_OPCODE                = 3,
	EFA_ADMIN_MALFORMED_REQUEST                 = 4,
	/* Additional status is provided in ACQ entry extended_status */
	EFA_ADMIN_ILLEGAL_PARAMETER                 = 5,
	EFA_ADMIN_UNKNOWN_ERROR                     = 6,
	EFA_ADMIN_RESOURCE_BUSY                     = 7,
पूर्ण;

काष्ठा efa_admin_aq_common_desc अणु
	/*
	 * 11:0 : command_id
	 * 15:12 : reserved12
	 */
	u16 command_id;

	/* as appears in efa_admin_aq_opcode */
	u8 opcode;

	/*
	 * 0 : phase
	 * 1 : ctrl_data - control buffer address valid
	 * 2 : ctrl_data_indirect - control buffer address
	 *    poपूर्णांकs to list of pages with addresses of control
	 *    buffers
	 * 7:3 : reserved3
	 */
	u8 flags;
पूर्ण;

/*
 * used in efa_admin_aq_entry. Can poपूर्णांक directly to control data, or to a
 * page list chunk. Used also at the end of indirect mode page list chunks,
 * क्रम chaining.
 */
काष्ठा efa_admin_ctrl_buff_info अणु
	u32 length;

	काष्ठा efa_common_mem_addr address;
पूर्ण;

काष्ठा efa_admin_aq_entry अणु
	काष्ठा efa_admin_aq_common_desc aq_common_descriptor;

	जोड़ अणु
		u32 अंतरभूत_data_w1[3];

		काष्ठा efa_admin_ctrl_buff_info control_buffer;
	पूर्ण u;

	u32 अंतरभूत_data_w4[12];
पूर्ण;

काष्ठा efa_admin_acq_common_desc अणु
	/*
	 * command identअगरier to associate it with the aq descriptor
	 * 11:0 : command_id
	 * 15:12 : reserved12
	 */
	u16 command;

	u8 status;

	/*
	 * 0 : phase
	 * 7:1 : reserved1
	 */
	u8 flags;

	u16 extended_status;

	/*
	 * indicates to the driver which AQ entry has been consumed by the
	 * device and could be reused
	 */
	u16 sq_head_indx;
पूर्ण;

काष्ठा efa_admin_acq_entry अणु
	काष्ठा efa_admin_acq_common_desc acq_common_descriptor;

	u32 response_specअगरic_data[14];
पूर्ण;

काष्ठा efa_admin_aenq_common_desc अणु
	u16 group;

	u16 syndrom;

	/*
	 * 0 : phase
	 * 7:1 : reserved - MBZ
	 */
	u8 flags;

	u8 reserved1[3];

	u32 बारtamp_low;

	u32 बारtamp_high;
पूर्ण;

काष्ठा efa_admin_aenq_entry अणु
	काष्ठा efa_admin_aenq_common_desc aenq_common_desc;

	/* command specअगरic अंतरभूत data */
	u32 अंतरभूत_data_w4[12];
पूर्ण;

/* aq_common_desc */
#घोषणा EFA_ADMIN_AQ_COMMON_DESC_COMMAND_ID_MASK            GENMASK(11, 0)
#घोषणा EFA_ADMIN_AQ_COMMON_DESC_PHASE_MASK                 BIT(0)
#घोषणा EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_MASK             BIT(1)
#घोषणा EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INसूचीECT_MASK    BIT(2)

/* acq_common_desc */
#घोषणा EFA_ADMIN_ACQ_COMMON_DESC_COMMAND_ID_MASK           GENMASK(11, 0)
#घोषणा EFA_ADMIN_ACQ_COMMON_DESC_PHASE_MASK                BIT(0)

/* aenq_common_desc */
#घोषणा EFA_ADMIN_AENQ_COMMON_DESC_PHASE_MASK               BIT(0)

#पूर्ण_अगर /* _EFA_ADMIN_H_ */
