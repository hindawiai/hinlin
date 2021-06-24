<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RAS_H__
#घोषणा __RAS_H__

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/uuid.h>
#समावेश <linux/cper.h>

#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक ras_userspace_consumers(व्योम);
व्योम ras_debugfs_init(व्योम);
पूर्णांक ras_add_daemon_trace(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक ras_userspace_consumers(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ras_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक ras_add_daemon_trace(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RAS_CEC
पूर्णांक __init parse_cec_param(अक्षर *str);
#पूर्ण_अगर

#अगर_घोषित CONFIG_RAS
व्योम log_non_standard_event(स्थिर guid_t *sec_type,
			    स्थिर guid_t *fru_id, स्थिर अक्षर *fru_text,
			    स्थिर u8 sev, स्थिर u8 *err, स्थिर u32 len);
व्योम log_arm_hw_error(काष्ठा cper_sec_proc_arm *err);
#अन्यथा
अटल अंतरभूत व्योम
log_non_standard_event(स्थिर guid_t *sec_type,
		       स्थिर guid_t *fru_id, स्थिर अक्षर *fru_text,
		       स्थिर u8 sev, स्थिर u8 *err, स्थिर u32 len)
अणु वापस; पूर्ण
अटल अंतरभूत व्योम
log_arm_hw_error(काष्ठा cper_sec_proc_arm *err) अणु वापस; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __RAS_H__ */
