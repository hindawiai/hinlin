<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * linux/drivers/misc/ibmvmc.h
 *
 * IBM Power Systems Virtual Management Channel Support.
 *
 * Copyright (c) 2004, 2018 IBM Corp.
 *   Dave Engebretsen engebret@us.ibm.com
 *   Steven Royer seroyer@linux.vnet.ibm.com
 *   Adam Reznechek adreznec@linux.vnet.ibm.com
 *   Bryant G. Ly <bryantly@linux.vnet.ibm.com>
 */
#अगर_अघोषित IBMVMC_H
#घोषणा IBMVMC_H

#समावेश <linux/types.h>
#समावेश <linux/cdev.h>

#समावेश <यंत्र/vपन.स>

#घोषणा IBMVMC_PROTOCOL_VERSION    0x0101

#घोषणा MIN_BUF_POOL_SIZE 16
#घोषणा MIN_HMCS          1
#घोषणा MIN_MTU           4096
#घोषणा MAX_BUF_POOL_SIZE 64
#घोषणा MAX_HMCS          2
#घोषणा MAX_MTU           (4 * 4096)
#घोषणा DEFAULT_BUF_POOL_SIZE 32
#घोषणा DEFAULT_HMCS          1
#घोषणा DEFAULT_MTU           4096
#घोषणा HMC_ID_LEN        32

#घोषणा VMC_INVALID_BUFFER_ID 0xFFFF

/* ioctl numbers */
#घोषणा VMC_BASE	     0xCC
#घोषणा VMC_IOCTL_SETHMCID   _IOW(VMC_BASE, 0x00, अचिन्हित अक्षर *)
#घोषणा VMC_IOCTL_QUERY      _IOR(VMC_BASE, 0x01, काष्ठा ibmvmc_query_काष्ठा)
#घोषणा VMC_IOCTL_REQUESTVMC _IOR(VMC_BASE, 0x02, u32)

#घोषणा VMC_MSG_CAP          0x01
#घोषणा VMC_MSG_CAP_RESP     0x81
#घोषणा VMC_MSG_OPEN         0x02
#घोषणा VMC_MSG_OPEN_RESP    0x82
#घोषणा VMC_MSG_CLOSE        0x03
#घोषणा VMC_MSG_CLOSE_RESP   0x83
#घोषणा VMC_MSG_ADD_BUF      0x04
#घोषणा VMC_MSG_ADD_BUF_RESP 0x84
#घोषणा VMC_MSG_REM_BUF      0x05
#घोषणा VMC_MSG_REM_BUF_RESP 0x85
#घोषणा VMC_MSG_SIGNAL       0x06

#घोषणा VMC_MSG_SUCCESS 0
#घोषणा VMC_MSG_INVALID_HMC_INDEX 1
#घोषणा VMC_MSG_INVALID_BUFFER_ID 2
#घोषणा VMC_MSG_CLOSED_HMC        3
#घोषणा VMC_MSG_INTERFACE_FAILURE 4
#घोषणा VMC_MSG_NO_BUFFER         5

#घोषणा VMC_BUF_OWNER_ALPHA 0
#घोषणा VMC_BUF_OWNER_HV    1

क्रमागत ibmvmc_states अणु
	ibmvmc_state_sched_reset  = -1,
	ibmvmc_state_initial      = 0,
	ibmvmc_state_crqinit      = 1,
	ibmvmc_state_capabilities = 2,
	ibmvmc_state_पढ़ोy        = 3,
	ibmvmc_state_failed       = 4,
पूर्ण;

क्रमागत ibmhmc_states अणु
	/* HMC connection not established */
	ibmhmc_state_मुक्त    = 0,

	/* HMC connection established (खोलो called) */
	ibmhmc_state_initial = 1,

	/* खोलो msg sent to HV, due to ioctl(1) call */
	ibmhmc_state_खोलोing = 2,

	/* HMC connection पढ़ोy, खोलो resp msg from HV */
	ibmhmc_state_पढ़ोy   = 3,

	/* HMC connection failure */
	ibmhmc_state_failed  = 4,
पूर्ण;

काष्ठा ibmvmc_buffer अणु
	u8 valid;	/* 1 when DMA storage allocated to buffer          */
	u8 मुक्त;	/* 1 when buffer available क्रम the Alpha Partition */
	u8 owner;
	u16 id;
	u32 size;
	u32 msg_len;
	dma_addr_t dma_addr_local;
	dma_addr_t dma_addr_remote;
	व्योम *real_addr_local;
पूर्ण;

काष्ठा ibmvmc_admin_crq_msg अणु
	u8 valid;	/* RPA Defined           */
	u8 type;	/* ibmvmc msg type       */
	u8 status;	/* Response msg status. Zero is success and on failure,
			 * either 1 - General Failure, or 2 - Invalid Version is
			 * वापसed.
			 */
	u8 rsvd[2];
	u8 max_hmc;	/* Max # of independent HMC connections supported */
	__be16 pool_size;	/* Maximum number of buffers supported per HMC
				 * connection
				 */
	__be32 max_mtu;		/* Maximum message size supported (bytes) */
	__be16 crq_size;	/* # of entries available in the CRQ क्रम the
				 * source partition. The target partition must
				 * limit the number of outstanding messages to
				 * one half or less.
				 */
	__be16 version;	/* Indicates the code level of the management partition
			 * or the hypervisor with the high-order byte
			 * indicating a major version and the low-order byte
			 * indicating a minor version.
			 */
पूर्ण;

काष्ठा ibmvmc_crq_msg अणु
	u8 valid;     /* RPA Defined           */
	u8 type;      /* ibmvmc msg type       */
	u8 status;    /* Response msg status   */
	जोड़ अणु
		u8 rsvd;  /* Reserved              */
		u8 owner;
	पूर्ण var1;
	u8 hmc_session;	/* Session Identअगरier क्रम the current VMC connection */
	u8 hmc_index;	/* A unique HMC Idx would be used अगर multiple management
			 * applications running concurrently were desired
			 */
	जोड़ अणु
		__be16 rsvd;
		__be16 buffer_id;
	पूर्ण var2;
	__be32 rsvd;
	जोड़ अणु
		__be32 rsvd;
		__be32 lioba;
		__be32 msg_len;
	पूर्ण var3;
पूर्ण;

/* an RPA command/response transport queue */
काष्ठा crq_queue अणु
	काष्ठा ibmvmc_crq_msg *msgs;
	पूर्णांक size, cur;
	dma_addr_t msg_token;
	spinlock_t lock;
पूर्ण;

/* VMC server adapter settings */
काष्ठा crq_server_adapter अणु
	काष्ठा device *dev;
	काष्ठा crq_queue queue;
	u32 liobn;
	u32 riobn;
	काष्ठा tasklet_काष्ठा work_task;
	रुको_queue_head_t reset_रुको_queue;
	काष्ठा task_काष्ठा *reset_task;
पूर्ण;

/* Driver wide settings */
काष्ठा ibmvmc_काष्ठा अणु
	u32 state;
	u32 max_mtu;
	u32 max_buffer_pool_size;
	u32 max_hmc_index;
	काष्ठा crq_server_adapter *adapter;
	काष्ठा cdev cdev;
	u32 vmc_drc_index;
पूर्ण;

काष्ठा ibmvmc_file_session;

/* Connection specअगरic settings */
काष्ठा ibmvmc_hmc अणु
	u8 session;
	u8 index;
	u32 state;
	काष्ठा crq_server_adapter *adapter;
	spinlock_t lock;
	अचिन्हित अक्षर hmc_id[HMC_ID_LEN];
	काष्ठा ibmvmc_buffer buffer[MAX_BUF_POOL_SIZE];
	अचिन्हित लघु queue_outbound_msgs[MAX_BUF_POOL_SIZE];
	पूर्णांक queue_head, queue_tail;
	काष्ठा ibmvmc_file_session *file_session;
पूर्ण;

काष्ठा ibmvmc_file_session अणु
	काष्ठा file *file;
	काष्ठा ibmvmc_hmc *hmc;
	bool valid;
पूर्ण;

काष्ठा ibmvmc_query_काष्ठा अणु
	पूर्णांक have_vmc;
	पूर्णांक state;
	पूर्णांक vmc_drc_index;
पूर्ण;

#पूर्ण_अगर /* __IBMVMC_H */
