<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Functions used by both the SCSI initiator code and the SCSI target code.
 */

#अगर_अघोषित _SCSI_COMMON_H_
#घोषणा _SCSI_COMMON_H_

#समावेश <linux/types.h>
#समावेश <scsi/scsi_proto.h>

अटल अंतरभूत अचिन्हित
scsi_varlen_cdb_length(स्थिर व्योम *hdr)
अणु
	वापस ((काष्ठा scsi_varlen_cdb_hdr *)hdr)->additional_cdb_length + 8;
पूर्ण

बाह्य स्थिर अचिन्हित अक्षर scsi_command_माप_प्रकारbl[8];
#घोषणा COMMAND_SIZE(opcode) scsi_command_माप_प्रकारbl[((opcode) >> 5) & 7]

अटल अंतरभूत अचिन्हित
scsi_command_size(स्थिर अचिन्हित अक्षर *cmnd)
अणु
	वापस (cmnd[0] == VARIABLE_LENGTH_CMD) ?
		scsi_varlen_cdb_length(cmnd) : COMMAND_SIZE(cmnd[0]);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
scsi_command_control(स्थिर अचिन्हित अक्षर *cmnd)
अणु
	वापस (cmnd[0] == VARIABLE_LENGTH_CMD) ?
		cmnd[1] : cmnd[COMMAND_SIZE(cmnd[0]) - 1];
पूर्ण

/* Returns a human-पढ़ोable name क्रम the device */
बाह्य स्थिर अक्षर *scsi_device_type(अचिन्हित type);

बाह्य व्योम पूर्णांक_to_scsilun(u64, काष्ठा scsi_lun *);
बाह्य u64 scsilun_to_पूर्णांक(काष्ठा scsi_lun *);

/*
 * This is a slightly modअगरied SCSI sense "descriptor" क्रमmat header.
 * The addition is to allow the 0x70 and 0x71 response codes. The idea
 * is to place the salient data from either "fixed" or "descriptor" sense
 * क्रमmat पूर्णांकo one काष्ठाure to ease application processing.
 *
 * The original sense buffer should be kept around क्रम those हालs
 * in which more inक्रमmation is required (e.g. the LBA of a MEDIUM ERROR).
 */
काष्ठा scsi_sense_hdr अणु		/* See SPC-3 section 4.5 */
	u8 response_code;	/* permit: 0x0, 0x70, 0x71, 0x72, 0x73 */
	u8 sense_key;
	u8 asc;
	u8 ascq;
	u8 byte4;
	u8 byte5;
	u8 byte6;
	u8 additional_length;	/* always 0 क्रम fixed sense क्रमmat */
पूर्ण;

अटल अंतरभूत bool scsi_sense_valid(स्थिर काष्ठा scsi_sense_hdr *sshdr)
अणु
	अगर (!sshdr)
		वापस false;

	वापस (sshdr->response_code & 0x70) == 0x70;
पूर्ण

बाह्य bool scsi_normalize_sense(स्थिर u8 *sense_buffer, पूर्णांक sb_len,
				 काष्ठा scsi_sense_hdr *sshdr);

बाह्य व्योम scsi_build_sense_buffer(पूर्णांक desc, u8 *buf, u8 key, u8 asc, u8 ascq);
पूर्णांक scsi_set_sense_inक्रमmation(u8 *buf, पूर्णांक buf_len, u64 info);
पूर्णांक scsi_set_sense_field_poपूर्णांकer(u8 *buf, पूर्णांक buf_len, u16 fp, u8 bp, bool cd);
बाह्य स्थिर u8 * scsi_sense_desc_find(स्थिर u8 * sense_buffer, पूर्णांक sb_len,
				       पूर्णांक desc_type);

#पूर्ण_अगर /* _SCSI_COMMON_H_ */
