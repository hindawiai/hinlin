<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ------------------------------------------------------------
 * ibmvscsi.h
 * (C) Copyright IBM Corporation 1994, 2003
 * Authors: Colin DeVilbiss (devilbis@us.ibm.com)
 *          Santiago Leon (santil@us.ibm.com)
 *          Dave Boutcher (sledकरोg@us.ibm.com)
 *
 * ------------------------------------------------------------
 * Emulation of a SCSI host adapter क्रम Virtual I/O devices
 *
 * This driver allows the Linux SCSI peripheral drivers to directly
 * access devices in the hosting partition, either on an iSeries
 * hypervisor प्रणाली or a converged hypervisor प्रणाली.
 */
#अगर_अघोषित IBMVSCSI_H
#घोषणा IBMVSCSI_H
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <scsi/viosrp.h>

काष्ठा scsi_cmnd;
काष्ठा Scsi_Host;

/* Number of indirect bufs...the list of these has to fit in the
 * additional data of the srp_cmd काष्ठा aदीर्घ with the indirect
 * descriptor
 */
#घोषणा MAX_INसूचीECT_BUFS 10

#घोषणा IBMVSCSI_MAX_REQUESTS_DEFAULT 100
#घोषणा IBMVSCSI_CMDS_PER_LUN_DEFAULT 16
#घोषणा IBMVSCSI_MAX_SECTORS_DEFAULT 256 /* 32 * 8 = शेष max I/O 32 pages */
#घोषणा IBMVSCSI_MAX_CMDS_PER_LUN 64
#घोषणा IBMVSCSI_MAX_LUN 32

/* ------------------------------------------------------------
 * Data Structures
 */
/* an RPA command/response transport queue */
काष्ठा crq_queue अणु
	काष्ठा viosrp_crq *msgs;
	पूर्णांक size, cur;
	dma_addr_t msg_token;
	spinlock_t lock;
पूर्ण;

/* a unit of work क्रम the hosting partition */
काष्ठा srp_event_काष्ठा अणु
	जोड़ viosrp_iu *xfer_iu;
	काष्ठा scsi_cmnd *cmnd;
	काष्ठा list_head list;
	व्योम (*करोne) (काष्ठा srp_event_काष्ठा *);
	काष्ठा viosrp_crq crq;
	काष्ठा ibmvscsi_host_data *hostdata;
	atomic_t मुक्त;
	जोड़ viosrp_iu iu;
	व्योम (*cmnd_करोne) (काष्ठा scsi_cmnd *);
	काष्ठा completion comp;
	काष्ठा समयr_list समयr;
	जोड़ viosrp_iu *sync_srp;
	काष्ठा srp_direct_buf *ext_list;
	dma_addr_t ext_list_token;
पूर्ण;

/* a pool of event काष्ठाs क्रम use */
काष्ठा event_pool अणु
	काष्ठा srp_event_काष्ठा *events;
	u32 size;
	पूर्णांक next;
	जोड़ viosrp_iu *iu_storage;
	dma_addr_t iu_token;
पूर्ण;

क्रमागत ibmvscsi_host_action अणु
	IBMVSCSI_HOST_ACTION_NONE = 0,
	IBMVSCSI_HOST_ACTION_RESET,
	IBMVSCSI_HOST_ACTION_REENABLE,
	IBMVSCSI_HOST_ACTION_UNBLOCK,
पूर्ण;

/* all driver data associated with a host adapter */
काष्ठा ibmvscsi_host_data अणु
	काष्ठा list_head host_list;
	atomic_t request_limit;
	पूर्णांक client_migrated;
	क्रमागत ibmvscsi_host_action action;
	काष्ठा device *dev;
	काष्ठा event_pool pool;
	काष्ठा crq_queue queue;
	काष्ठा tasklet_काष्ठा srp_task;
	काष्ठा list_head sent;
	काष्ठा Scsi_Host *host;
	काष्ठा task_काष्ठा *work_thपढ़ो;
	रुको_queue_head_t work_रुको_q;
	काष्ठा mad_adapter_info_data madapter_info;
	काष्ठा capabilities caps;
	dma_addr_t caps_addr;
	dma_addr_t adapter_info_addr;
पूर्ण;

#पूर्ण_अगर				/* IBMVSCSI_H */
