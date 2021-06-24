<शैली गुरु>
/*
 * This file is in the खुला करोमुख्य.
 */
#अगर_अघोषित	_SCSI_SCSI_IU_H
#घोषणा _SCSI_SCSI_IU_H 1

काष्ठा scsi_status_iu_header
अणु
	u_पूर्णांक8_t reserved[2];
	u_पूर्णांक8_t flags;
#घोषणा	SIU_SNSVALID 0x2
#घोषणा	SIU_RSPVALID 0x1
	u_पूर्णांक8_t status;
	u_पूर्णांक8_t sense_length[4];
	u_पूर्णांक8_t pkt_failures_length[4];
	u_पूर्णांक8_t pkt_failures[1];
पूर्ण;

#घोषणा SIU_PKTFAIL_OFFSET(siu) 12
#घोषणा SIU_PKTFAIL_CODE(siu) (scsi_4btoul((siu)->pkt_failures) & 0xFF)
#घोषणा		SIU_PFC_NONE			0
#घोषणा		SIU_PFC_CIU_FIELDS_INVALID	2
#घोषणा		SIU_PFC_TMF_NOT_SUPPORTED	4
#घोषणा		SIU_PFC_TMF_FAILED		5
#घोषणा		SIU_PFC_INVALID_TYPE_CODE	6
#घोषणा		SIU_PFC_ILLEGAL_REQUEST		7
#घोषणा SIU_SENSE_OFFSET(siu)				\
    (12 + (((siu)->flags & SIU_RSPVALID)		\
	? scsi_4btoul((siu)->pkt_failures_length)	\
	: 0))

#घोषणा	SIU_TASKMGMT_NONE		0x00
#घोषणा	SIU_TASKMGMT_ABORT_TASK		0x01
#घोषणा	SIU_TASKMGMT_ABORT_TASK_SET	0x02
#घोषणा	SIU_TASKMGMT_CLEAR_TASK_SET	0x04
#घोषणा	SIU_TASKMGMT_LUN_RESET		0x08
#घोषणा	SIU_TASKMGMT_TARGET_RESET	0x20
#घोषणा	SIU_TASKMGMT_CLEAR_ACA		0x40
#पूर्ण_अगर /*_SCSI_SCSI_IU_H*/
