<शैली गुरु>
#अगर_अघोषित	_ASM_X86_INTEL_PCONFIG_H
#घोषणा	_ASM_X86_INTEL_PCONFIG_H

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/processor.h>

क्रमागत pconfig_target अणु
	INVALID_TARGET	= 0,
	MKTME_TARGET	= 1,
	PCONFIG_TARGET_NR
पूर्ण;

पूर्णांक pconfig_target_supported(क्रमागत pconfig_target target);

क्रमागत pconfig_leaf अणु
	MKTME_KEY_PROGRAM	= 0,
	PCONFIG_LEAF_INVALID,
पूर्ण;

#घोषणा PCONFIG ".byte 0x0f, 0x01, 0xc5"

/* Defines and काष्ठाure क्रम MKTME_KEY_PROGRAM of PCONFIG inकाष्ठाion */

/* mkपंचांगe_key_program::keyid_ctrl COMMAND, bits [7:0] */
#घोषणा MKTME_KEYID_SET_KEY_सूचीECT	0
#घोषणा MKTME_KEYID_SET_KEY_RANDOM	1
#घोषणा MKTME_KEYID_CLEAR_KEY		2
#घोषणा MKTME_KEYID_NO_ENCRYPT		3

/* mkपंचांगe_key_program::keyid_ctrl ENC_ALG, bits [23:8] */
#घोषणा MKTME_AES_XTS_128	(1 << 8)

/* Return codes from the PCONFIG MKTME_KEY_PROGRAM */
#घोषणा MKTME_PROG_SUCCESS	0
#घोषणा MKTME_INVALID_PROG_CMD	1
#घोषणा MKTME_ENTROPY_ERROR	2
#घोषणा MKTME_INVALID_KEYID	3
#घोषणा MKTME_INVALID_ENC_ALG	4
#घोषणा MKTME_DEVICE_BUSY	5

/* Hardware requires the काष्ठाure to be 256 byte aligned. Otherwise #GP(0). */
काष्ठा mkपंचांगe_key_program अणु
	u16 keyid;
	u32 keyid_ctrl;
	u8 __rsvd[58];
	u8 key_field_1[64];
	u8 key_field_2[64];
पूर्ण __packed __aligned(256);

अटल अंतरभूत पूर्णांक mkपंचांगe_key_program(काष्ठा mkपंचांगe_key_program *key_program)
अणु
	अचिन्हित दीर्घ rax = MKTME_KEY_PROGRAM;

	अगर (!pconfig_target_supported(MKTME_TARGET))
		वापस -ENXIO;

	यंत्र अस्थिर(PCONFIG
		: "=a" (rax), "=b" (key_program)
		: "0" (rax), "1" (key_program)
		: "memory", "cc");

	वापस rax;
पूर्ण

#पूर्ण_अगर	/* _ASM_X86_INTEL_PCONFIG_H */
