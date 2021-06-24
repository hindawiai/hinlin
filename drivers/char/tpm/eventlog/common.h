<शैली गुरु>
#अगर_अघोषित __TPM_EVENTLOG_COMMON_H__
#घोषणा __TPM_EVENTLOG_COMMON_H__

#समावेश "../tpm.h"

बाह्य स्थिर काष्ठा seq_operations tpm1_ascii_b_measurements_seqops;
बाह्य स्थिर काष्ठा seq_operations tpm1_binary_b_measurements_seqops;
बाह्य स्थिर काष्ठा seq_operations tpm2_binary_b_measurements_seqops;

#अगर defined(CONFIG_ACPI)
पूर्णांक tpm_पढ़ो_log_acpi(काष्ठा tpm_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक tpm_पढ़ो_log_acpi(काष्ठा tpm_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_OF)
पूर्णांक tpm_पढ़ो_log_of(काष्ठा tpm_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक tpm_पढ़ो_log_of(काष्ठा tpm_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_EFI)
पूर्णांक tpm_पढ़ो_log_efi(काष्ठा tpm_chip *chip);
#अन्यथा
अटल अंतरभूत पूर्णांक tpm_पढ़ो_log_efi(काष्ठा tpm_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
