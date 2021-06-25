<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_DBG_H
#घोषणा _SCSI_SCSI_DBG_H

काष्ठा scsi_cmnd;
काष्ठा scsi_device;
काष्ठा scsi_sense_hdr;

बाह्य व्योम scsi_prपूर्णांक_command(काष्ठा scsi_cmnd *);
बाह्य माप_प्रकार __scsi_क्रमmat_command(अक्षर *, माप_प्रकार,
				   स्थिर अचिन्हित अक्षर *, माप_प्रकार);
बाह्य व्योम scsi_prपूर्णांक_sense_hdr(स्थिर काष्ठा scsi_device *, स्थिर अक्षर *,
				 स्थिर काष्ठा scsi_sense_hdr *);
बाह्य व्योम scsi_prपूर्णांक_sense(स्थिर काष्ठा scsi_cmnd *);
बाह्य व्योम __scsi_prपूर्णांक_sense(स्थिर काष्ठा scsi_device *, स्थिर अक्षर *name,
			       स्थिर अचिन्हित अक्षर *sense_buffer,
			       पूर्णांक sense_len);
बाह्य व्योम scsi_prपूर्णांक_result(स्थिर काष्ठा scsi_cmnd *, स्थिर अक्षर *, पूर्णांक);

#अगर_घोषित CONFIG_SCSI_CONSTANTS
बाह्य bool scsi_opcode_sa_name(पूर्णांक, पूर्णांक, स्थिर अक्षर **, स्थिर अक्षर **);
बाह्य स्थिर अक्षर *scsi_sense_key_string(अचिन्हित अक्षर);
बाह्य स्थिर अक्षर *scsi_extd_sense_क्रमmat(अचिन्हित अक्षर, अचिन्हित अक्षर,
					  स्थिर अक्षर **);
बाह्य स्थिर अक्षर *scsi_mlवापस_string(पूर्णांक);
बाह्य स्थिर अक्षर *scsi_hostbyte_string(पूर्णांक);
बाह्य स्थिर अक्षर *scsi_driverbyte_string(पूर्णांक);
#अन्यथा
अटल अंतरभूत bool
scsi_opcode_sa_name(पूर्णांक cmd, पूर्णांक sa,
		    स्थिर अक्षर **cdb_name, स्थिर अक्षर **sa_name)
अणु
	*cdb_name = शून्य;
	चयन (cmd) अणु
	हाल VARIABLE_LENGTH_CMD:
	हाल MAINTEन_अंकCE_IN:
	हाल MAINTEन_अंकCE_OUT:
	हाल PERSISTENT_RESERVE_IN:
	हाल PERSISTENT_RESERVE_OUT:
	हाल SERVICE_ACTION_IN_12:
	हाल SERVICE_ACTION_OUT_12:
	हाल SERVICE_ACTION_BIसूचीECTIONAL:
	हाल SERVICE_ACTION_IN_16:
	हाल SERVICE_ACTION_OUT_16:
	हाल EXTENDED_COPY:
	हाल RECEIVE_COPY_RESULTS:
		*sa_name = शून्य;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
scsi_sense_key_string(अचिन्हित अक्षर key)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
scsi_extd_sense_क्रमmat(अचिन्हित अक्षर asc, अचिन्हित अक्षर ascq, स्थिर अक्षर **fmt)
अणु
	*fmt = शून्य;
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
scsi_mlवापस_string(पूर्णांक result)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
scsi_hostbyte_string(पूर्णांक result)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
scsi_driverbyte_string(पूर्णांक result)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _SCSI_SCSI_DBG_H */
