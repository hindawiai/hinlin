<शैली गुरु>
/*
 * This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#अगर_अघोषित _LINUX_VIRTIO_SCSI_H
#घोषणा _LINUX_VIRTIO_SCSI_H

#समावेश <linux/virtio_types.h>

/* Default values of the CDB and sense data size configuration fields */
#घोषणा VIRTIO_SCSI_CDB_DEFAULT_SIZE   32
#घोषणा VIRTIO_SCSI_SENSE_DEFAULT_SIZE 96

#अगर_अघोषित VIRTIO_SCSI_CDB_SIZE
#घोषणा VIRTIO_SCSI_CDB_SIZE VIRTIO_SCSI_CDB_DEFAULT_SIZE
#पूर्ण_अगर
#अगर_अघोषित VIRTIO_SCSI_SENSE_SIZE
#घोषणा VIRTIO_SCSI_SENSE_SIZE VIRTIO_SCSI_SENSE_DEFAULT_SIZE
#पूर्ण_अगर

/* SCSI command request, followed by data-out */
काष्ठा virtio_scsi_cmd_req अणु
	__u8 lun[8];		/* Logical Unit Number */
	__virtio64 tag;		/* Command identअगरier */
	__u8 task_attr;		/* Task attribute */
	__u8 prio;		/* SAM command priority field */
	__u8 crn;
	__u8 cdb[VIRTIO_SCSI_CDB_SIZE];
पूर्ण __attribute__((packed));

/* SCSI command request, followed by protection inक्रमmation */
काष्ठा virtio_scsi_cmd_req_pi अणु
	__u8 lun[8];		/* Logical Unit Number */
	__virtio64 tag;		/* Command identअगरier */
	__u8 task_attr;		/* Task attribute */
	__u8 prio;		/* SAM command priority field */
	__u8 crn;
	__virtio32 pi_bytesout;	/* DataOUT PI Number of bytes */
	__virtio32 pi_bytesin;		/* DataIN PI Number of bytes */
	__u8 cdb[VIRTIO_SCSI_CDB_SIZE];
पूर्ण __attribute__((packed));

/* Response, followed by sense data and data-in */
काष्ठा virtio_scsi_cmd_resp अणु
	__virtio32 sense_len;		/* Sense data length */
	__virtio32 resid;		/* Residual bytes in data buffer */
	__virtio16 status_qualअगरier;	/* Status qualअगरier */
	__u8 status;		/* Command completion status */
	__u8 response;		/* Response values */
	__u8 sense[VIRTIO_SCSI_SENSE_SIZE];
पूर्ण __attribute__((packed));

/* Task Management Request */
काष्ठा virtio_scsi_ctrl_पंचांगf_req अणु
	__virtio32 type;
	__virtio32 subtype;
	__u8 lun[8];
	__virtio64 tag;
पूर्ण __attribute__((packed));

काष्ठा virtio_scsi_ctrl_पंचांगf_resp अणु
	__u8 response;
पूर्ण __attribute__((packed));

/* Asynchronous notअगरication query/subscription */
काष्ठा virtio_scsi_ctrl_an_req अणु
	__virtio32 type;
	__u8 lun[8];
	__virtio32 event_requested;
पूर्ण __attribute__((packed));

काष्ठा virtio_scsi_ctrl_an_resp अणु
	__virtio32 event_actual;
	__u8 response;
पूर्ण __attribute__((packed));

काष्ठा virtio_scsi_event अणु
	__virtio32 event;
	__u8 lun[8];
	__virtio32 reason;
पूर्ण __attribute__((packed));

काष्ठा virtio_scsi_config अणु
	__virtio32 num_queues;
	__virtio32 seg_max;
	__virtio32 max_sectors;
	__virtio32 cmd_per_lun;
	__virtio32 event_info_size;
	__virtio32 sense_size;
	__virtio32 cdb_size;
	__virtio16 max_channel;
	__virtio16 max_target;
	__virtio32 max_lun;
पूर्ण __attribute__((packed));

/* Feature Bits */
#घोषणा VIRTIO_SCSI_F_INOUT                    0
#घोषणा VIRTIO_SCSI_F_HOTPLUG                  1
#घोषणा VIRTIO_SCSI_F_CHANGE                   2
#घोषणा VIRTIO_SCSI_F_T10_PI                   3

/* Response codes */
#घोषणा VIRTIO_SCSI_S_OK                       0
#घोषणा VIRTIO_SCSI_S_OVERRUN                  1
#घोषणा VIRTIO_SCSI_S_ABORTED                  2
#घोषणा VIRTIO_SCSI_S_BAD_TARGET               3
#घोषणा VIRTIO_SCSI_S_RESET                    4
#घोषणा VIRTIO_SCSI_S_BUSY                     5
#घोषणा VIRTIO_SCSI_S_TRANSPORT_FAILURE        6
#घोषणा VIRTIO_SCSI_S_TARGET_FAILURE           7
#घोषणा VIRTIO_SCSI_S_NEXUS_FAILURE            8
#घोषणा VIRTIO_SCSI_S_FAILURE                  9
#घोषणा VIRTIO_SCSI_S_FUNCTION_SUCCEEDED       10
#घोषणा VIRTIO_SCSI_S_FUNCTION_REJECTED        11
#घोषणा VIRTIO_SCSI_S_INCORRECT_LUN            12

/* Controlq type codes.  */
#घोषणा VIRTIO_SCSI_T_TMF                      0
#घोषणा VIRTIO_SCSI_T_AN_QUERY                 1
#घोषणा VIRTIO_SCSI_T_AN_SUBSCRIBE             2

/* Valid TMF subtypes.  */
#घोषणा VIRTIO_SCSI_T_TMF_ABORT_TASK           0
#घोषणा VIRTIO_SCSI_T_TMF_ABORT_TASK_SET       1
#घोषणा VIRTIO_SCSI_T_TMF_CLEAR_ACA            2
#घोषणा VIRTIO_SCSI_T_TMF_CLEAR_TASK_SET       3
#घोषणा VIRTIO_SCSI_T_TMF_I_T_NEXUS_RESET      4
#घोषणा VIRTIO_SCSI_T_TMF_LOGICAL_UNIT_RESET   5
#घोषणा VIRTIO_SCSI_T_TMF_QUERY_TASK           6
#घोषणा VIRTIO_SCSI_T_TMF_QUERY_TASK_SET       7

/* Events.  */
#घोषणा VIRTIO_SCSI_T_EVENTS_MISSED            0x80000000
#घोषणा VIRTIO_SCSI_T_NO_EVENT                 0
#घोषणा VIRTIO_SCSI_T_TRANSPORT_RESET          1
#घोषणा VIRTIO_SCSI_T_ASYNC_NOTIFY             2
#घोषणा VIRTIO_SCSI_T_PARAM_CHANGE             3

/* Reasons of transport reset event */
#घोषणा VIRTIO_SCSI_EVT_RESET_HARD             0
#घोषणा VIRTIO_SCSI_EVT_RESET_RESCAN           1
#घोषणा VIRTIO_SCSI_EVT_RESET_REMOVED          2

#घोषणा VIRTIO_SCSI_S_SIMPLE                   0
#घोषणा VIRTIO_SCSI_S_ORDERED                  1
#घोषणा VIRTIO_SCSI_S_HEAD                     2
#घोषणा VIRTIO_SCSI_S_ACA                      3


#पूर्ण_अगर /* _LINUX_VIRTIO_SCSI_H */
