<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_EH_H
#घोषणा _SCSI_SCSI_EH_H

#समावेश <linux/scatterlist.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_common.h>
काष्ठा scsi_device;
काष्ठा Scsi_Host;

बाह्य व्योम scsi_eh_finish_cmd(काष्ठा scsi_cmnd *scmd,
			       काष्ठा list_head *करोne_q);
बाह्य व्योम scsi_eh_flush_करोne_q(काष्ठा list_head *करोne_q);
बाह्य व्योम scsi_report_bus_reset(काष्ठा Scsi_Host *, पूर्णांक);
बाह्य व्योम scsi_report_device_reset(काष्ठा Scsi_Host *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक scsi_block_when_processing_errors(काष्ठा scsi_device *);
बाह्य bool scsi_command_normalize_sense(स्थिर काष्ठा scsi_cmnd *cmd,
					 काष्ठा scsi_sense_hdr *sshdr);
बाह्य क्रमागत scsi_disposition scsi_check_sense(काष्ठा scsi_cmnd *);

अटल अंतरभूत bool scsi_sense_is_deferred(स्थिर काष्ठा scsi_sense_hdr *sshdr)
अणु
	वापस ((sshdr->response_code >= 0x70) && (sshdr->response_code & 1));
पूर्ण

बाह्य bool scsi_get_sense_info_fld(स्थिर u8 *sense_buffer, पूर्णांक sb_len,
				    u64 *info_out);

बाह्य पूर्णांक scsi_ioctl_reset(काष्ठा scsi_device *, पूर्णांक __user *);

काष्ठा scsi_eh_save अणु
	/* saved state */
	पूर्णांक result;
	अचिन्हित पूर्णांक resid_len;
	पूर्णांक eh_eflags;
	क्रमागत dma_data_direction data_direction;
	अचिन्हित underflow;
	अचिन्हित अक्षर cmd_len;
	अचिन्हित अक्षर prot_op;
	अचिन्हित अक्षर *cmnd;
	काष्ठा scsi_data_buffer sdb;
	/* new command support */
	अचिन्हित अक्षर eh_cmnd[BLK_MAX_CDB];
	काष्ठा scatterlist sense_sgl;
पूर्ण;

बाह्य व्योम scsi_eh_prep_cmnd(काष्ठा scsi_cmnd *scmd,
		काष्ठा scsi_eh_save *ses, अचिन्हित अक्षर *cmnd,
		पूर्णांक cmnd_size, अचिन्हित sense_bytes);

बाह्य व्योम scsi_eh_restore_cmnd(काष्ठा scsi_cmnd* scmd,
		काष्ठा scsi_eh_save *ses);

#पूर्ण_अगर /* _SCSI_SCSI_EH_H */
