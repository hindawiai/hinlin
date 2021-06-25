<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_S390_SIE_H
#घोषणा _UAPI_ASM_S390_SIE_H

#घोषणा diagnose_codes						\
	अणु 0x10, "DIAG (0x10) release pages" पूर्ण,			\
	अणु 0x44, "DIAG (0x44) time slice end" पूर्ण,			\
	अणु 0x9c, "DIAG (0x9c) time slice end directed" पूर्ण,	\
	अणु 0x204, "DIAG (0x204) logical-cpu utilization" पूर्ण,	\
	अणु 0x258, "DIAG (0x258) page-reference services" पूर्ण,	\
	अणु 0x288, "DIAG (0x288) watchdog functions" पूर्ण,		\
	अणु 0x308, "DIAG (0x308) ipl functions" पूर्ण,		\
	अणु 0x500, "DIAG (0x500) KVM virtio functions" पूर्ण,		\
	अणु 0x501, "DIAG (0x501) KVM breakpoint" पूर्ण

#घोषणा sigp_order_codes					\
	अणु 0x01, "SIGP sense" पूर्ण,					\
	अणु 0x02, "SIGP external call" पूर्ण,				\
	अणु 0x03, "SIGP emergency signal" पूर्ण,			\
	अणु 0x04, "SIGP start" पूर्ण,					\
	अणु 0x05, "SIGP stop" पूर्ण,					\
	अणु 0x06, "SIGP restart" पूर्ण,				\
	अणु 0x09, "SIGP stop and store status" पूर्ण,			\
	अणु 0x0b, "SIGP initial cpu reset" पूर्ण,			\
	अणु 0x0c, "SIGP cpu reset" पूर्ण,				\
	अणु 0x0d, "SIGP set prefix" पूर्ण,				\
	अणु 0x0e, "SIGP store status at address" पूर्ण,		\
	अणु 0x12, "SIGP set architecture" पूर्ण,			\
	अणु 0x13, "SIGP conditional emergency signal" पूर्ण,		\
	अणु 0x15, "SIGP sense running" पूर्ण,				\
	अणु 0x16, "SIGP set multithreading"पूर्ण,			\
	अणु 0x17, "SIGP store additional status at address"पूर्ण

#घोषणा icpt_prog_codes						\
	अणु 0x0001, "Prog Operation" पूर्ण,				\
	अणु 0x0002, "Prog Privileged Operation" पूर्ण,		\
	अणु 0x0003, "Prog Execute" पूर्ण,				\
	अणु 0x0004, "Prog Protection" पूर्ण,				\
	अणु 0x0005, "Prog Addressing" पूर्ण,				\
	अणु 0x0006, "Prog Specification" पूर्ण,			\
	अणु 0x0007, "Prog Data" पूर्ण,				\
	अणु 0x0008, "Prog Fixedpoint overflow" पूर्ण,			\
	अणु 0x0009, "Prog Fixedpoint divide" पूर्ण,			\
	अणु 0x000A, "Prog Decimal overflow" पूर्ण,			\
	अणु 0x000B, "Prog Decimal divide" पूर्ण,			\
	अणु 0x000C, "Prog HFP exponent overflow" पूर्ण,		\
	अणु 0x000D, "Prog HFP exponent underflow" पूर्ण,		\
	अणु 0x000E, "Prog HFP significance" पूर्ण,			\
	अणु 0x000F, "Prog HFP divide" पूर्ण,				\
	अणु 0x0010, "Prog Segment translation" पूर्ण,			\
	अणु 0x0011, "Prog Page translation" पूर्ण,			\
	अणु 0x0012, "Prog Translation specification" पूर्ण,		\
	अणु 0x0013, "Prog Special operation" पूर्ण,			\
	अणु 0x0015, "Prog Operand" पूर्ण,				\
	अणु 0x0016, "Prog Trace table" पूर्ण,				\
	अणु 0x0017, "Prog ASNtranslation specification" पूर्ण,	\
	अणु 0x001C, "Prog Spaceswitch event" पूर्ण,			\
	अणु 0x001D, "Prog HFP square root" पूर्ण,			\
	अणु 0x001F, "Prog PCtranslation specification" पूर्ण,		\
	अणु 0x0020, "Prog AFX translation" पूर्ण,			\
	अणु 0x0021, "Prog ASX translation" पूर्ण,			\
	अणु 0x0022, "Prog LX translation" पूर्ण,			\
	अणु 0x0023, "Prog EX translation" पूर्ण,			\
	अणु 0x0024, "Prog Primary authority" पूर्ण,			\
	अणु 0x0025, "Prog Secondary authority" पूर्ण,			\
	अणु 0x0026, "Prog LFXtranslation exception" पूर्ण,		\
	अणु 0x0027, "Prog LSXtranslation exception" पूर्ण,		\
	अणु 0x0028, "Prog ALET specification" पूर्ण,			\
	अणु 0x0029, "Prog ALEN translation" पूर्ण,			\
	अणु 0x002A, "Prog ALE sequence" पूर्ण,			\
	अणु 0x002B, "Prog ASTE validity" पूर्ण,			\
	अणु 0x002C, "Prog ASTE sequence" पूर्ण,			\
	अणु 0x002D, "Prog Extended authority" पूर्ण,			\
	अणु 0x002E, "Prog LSTE sequence" पूर्ण,			\
	अणु 0x002F, "Prog ASTE instance" पूर्ण,			\
	अणु 0x0030, "Prog Stack full" पूर्ण,				\
	अणु 0x0031, "Prog Stack empty" पूर्ण,				\
	अणु 0x0032, "Prog Stack specification" पूर्ण,			\
	अणु 0x0033, "Prog Stack type" पूर्ण,				\
	अणु 0x0034, "Prog Stack operation" पूर्ण,			\
	अणु 0x0039, "Prog Region first translation" पूर्ण,		\
	अणु 0x003A, "Prog Region second translation" पूर्ण,		\
	अणु 0x003B, "Prog Region third translation" पूर्ण,		\
	अणु 0x0040, "Prog Monitor event" पूर्ण,			\
	अणु 0x0080, "Prog PER event" पूर्ण,				\
	अणु 0x0119, "Prog Crypto operation" पूर्ण

#घोषणा निकास_code_ipa0(ipa0, opcode, mnemonic)		\
	अणु (ipa0 << 8 | opcode), #ipa0 " " mnemonic पूर्ण
#घोषणा निकास_code(opcode, mnemonic)			\
	अणु opcode, mnemonic पूर्ण

#घोषणा icpt_insn_codes				\
	निकास_code_ipa0(0x01, 0x01, "PR"),	\
	निकास_code_ipa0(0x01, 0x04, "PTFF"),	\
	निकास_code_ipa0(0x01, 0x07, "SCKPF"),	\
	निकास_code_ipa0(0xAA, 0x00, "RINEXT"),	\
	निकास_code_ipa0(0xAA, 0x01, "RION"),	\
	निकास_code_ipa0(0xAA, 0x02, "TRIC"),	\
	निकास_code_ipa0(0xAA, 0x03, "RIOFF"),	\
	निकास_code_ipa0(0xAA, 0x04, "RIEMIT"),	\
	निकास_code_ipa0(0xB2, 0x02, "STIDP"),	\
	निकास_code_ipa0(0xB2, 0x04, "SCK"),	\
	निकास_code_ipa0(0xB2, 0x05, "STCK"),	\
	निकास_code_ipa0(0xB2, 0x06, "SCKC"),	\
	निकास_code_ipa0(0xB2, 0x07, "STCKC"),	\
	निकास_code_ipa0(0xB2, 0x08, "SPT"),	\
	निकास_code_ipa0(0xB2, 0x09, "STPT"),	\
	निकास_code_ipa0(0xB2, 0x0d, "PTLB"),	\
	निकास_code_ipa0(0xB2, 0x10, "SPX"),	\
	निकास_code_ipa0(0xB2, 0x11, "STPX"),	\
	निकास_code_ipa0(0xB2, 0x12, "STAP"),	\
	निकास_code_ipa0(0xB2, 0x14, "SIE"),	\
	निकास_code_ipa0(0xB2, 0x16, "SETR"),	\
	निकास_code_ipa0(0xB2, 0x17, "STETR"),	\
	निकास_code_ipa0(0xB2, 0x18, "PC"),	\
	निकास_code_ipa0(0xB2, 0x20, "SERVC"),	\
	निकास_code_ipa0(0xB2, 0x21, "IPTE"),	\
	निकास_code_ipa0(0xB2, 0x28, "PT"),	\
	निकास_code_ipa0(0xB2, 0x29, "ISKE"),	\
	निकास_code_ipa0(0xB2, 0x2a, "RRBE"),	\
	निकास_code_ipa0(0xB2, 0x2b, "SSKE"),	\
	निकास_code_ipa0(0xB2, 0x2c, "TB"),	\
	निकास_code_ipa0(0xB2, 0x2e, "PGIN"),	\
	निकास_code_ipa0(0xB2, 0x2f, "PGOUT"),	\
	निकास_code_ipa0(0xB2, 0x30, "CSCH"),	\
	निकास_code_ipa0(0xB2, 0x31, "HSCH"),	\
	निकास_code_ipa0(0xB2, 0x32, "MSCH"),	\
	निकास_code_ipa0(0xB2, 0x33, "SSCH"),	\
	निकास_code_ipa0(0xB2, 0x34, "STSCH"),	\
	निकास_code_ipa0(0xB2, 0x35, "TSCH"),	\
	निकास_code_ipa0(0xB2, 0x36, "TPI"),	\
	निकास_code_ipa0(0xB2, 0x37, "SAL"),	\
	निकास_code_ipa0(0xB2, 0x38, "RSCH"),	\
	निकास_code_ipa0(0xB2, 0x39, "STCRW"),	\
	निकास_code_ipa0(0xB2, 0x3a, "STCPS"),	\
	निकास_code_ipa0(0xB2, 0x3b, "RCHP"),	\
	निकास_code_ipa0(0xB2, 0x3c, "SCHM"),	\
	निकास_code_ipa0(0xB2, 0x40, "BAKR"),	\
	निकास_code_ipa0(0xB2, 0x48, "PALB"),	\
	निकास_code_ipa0(0xB2, 0x4c, "TAR"),	\
	निकास_code_ipa0(0xB2, 0x50, "CSP"),	\
	निकास_code_ipa0(0xB2, 0x54, "MVPG"),	\
	निकास_code_ipa0(0xB2, 0x56, "STHYI"),	\
	निकास_code_ipa0(0xB2, 0x58, "BSG"),	\
	निकास_code_ipa0(0xB2, 0x5a, "BSA"),	\
	निकास_code_ipa0(0xB2, 0x5f, "CHSC"),	\
	निकास_code_ipa0(0xB2, 0x74, "SIGA"),	\
	निकास_code_ipa0(0xB2, 0x76, "XSCH"),	\
	निकास_code_ipa0(0xB2, 0x78, "STCKE"),	\
	निकास_code_ipa0(0xB2, 0x7c, "STCKF"),	\
	निकास_code_ipa0(0xB2, 0x7d, "STSI"),	\
	निकास_code_ipa0(0xB2, 0xb0, "STFLE"),	\
	निकास_code_ipa0(0xB2, 0xb1, "STFL"),	\
	निकास_code_ipa0(0xB2, 0xb2, "LPSWE"),	\
	निकास_code_ipa0(0xB2, 0xf8, "TEND"),	\
	निकास_code_ipa0(0xB2, 0xfc, "TABORT"),	\
	निकास_code_ipa0(0xB9, 0x1e, "KMAC"),	\
	निकास_code_ipa0(0xB9, 0x28, "PCKMO"),	\
	निकास_code_ipa0(0xB9, 0x2a, "KMF"),	\
	निकास_code_ipa0(0xB9, 0x2b, "KMO"),	\
	निकास_code_ipa0(0xB9, 0x2d, "KMCTR"),	\
	निकास_code_ipa0(0xB9, 0x2e, "KM"),	\
	निकास_code_ipa0(0xB9, 0x2f, "KMC"),	\
	निकास_code_ipa0(0xB9, 0x3e, "KIMD"),	\
	निकास_code_ipa0(0xB9, 0x3f, "KLMD"),	\
	निकास_code_ipa0(0xB9, 0x8a, "CSPG"),	\
	निकास_code_ipa0(0xB9, 0x8d, "EPSW"),	\
	निकास_code_ipa0(0xB9, 0x8e, "IDTE"),	\
	निकास_code_ipa0(0xB9, 0x8f, "CRDTE"),	\
	निकास_code_ipa0(0xB9, 0x9c, "EQBS"),	\
	निकास_code_ipa0(0xB9, 0xa2, "PTF"),	\
	निकास_code_ipa0(0xB9, 0xab, "ESSA"),	\
	निकास_code_ipa0(0xB9, 0xae, "RRBM"),	\
	निकास_code_ipa0(0xB9, 0xaf, "PFMF"),	\
	निकास_code_ipa0(0xE3, 0x03, "LRAG"),	\
	निकास_code_ipa0(0xE3, 0x13, "LRAY"),	\
	निकास_code_ipa0(0xE3, 0x25, "NTSTG"),	\
	निकास_code_ipa0(0xE5, 0x00, "LASP"),	\
	निकास_code_ipa0(0xE5, 0x01, "TPROT"),	\
	निकास_code_ipa0(0xE5, 0x60, "TBEGIN"),	\
	निकास_code_ipa0(0xE5, 0x61, "TBEGINC"),	\
	निकास_code_ipa0(0xEB, 0x25, "STCTG"),	\
	निकास_code_ipa0(0xEB, 0x2f, "LCTLG"),	\
	निकास_code_ipa0(0xEB, 0x60, "LRIC"),	\
	निकास_code_ipa0(0xEB, 0x61, "STRIC"),	\
	निकास_code_ipa0(0xEB, 0x62, "MRIC"),	\
	निकास_code_ipa0(0xEB, 0x8a, "SQBS"),	\
	निकास_code_ipa0(0xC8, 0x01, "ECTG"),	\
	निकास_code(0x0a, "SVC"),			\
	निकास_code(0x80, "SSM"),			\
	निकास_code(0x82, "LPSW"),		\
	निकास_code(0x83, "DIAG"),		\
	निकास_code(0xae, "SIGP"),		\
	निकास_code(0xac, "STNSM"),		\
	निकास_code(0xad, "STOSM"),		\
	निकास_code(0xb1, "LRA"),			\
	निकास_code(0xb6, "STCTL"),		\
	निकास_code(0xb7, "LCTL"),		\
	निकास_code(0xee, "PLO")

#घोषणा sie_पूर्णांकercept_code					\
	अणु 0x00, "Host interruption" पूर्ण,				\
	अणु 0x04, "Instruction" पूर्ण,				\
	अणु 0x08, "Program interruption" पूर्ण,			\
	अणु 0x0c, "Instruction and program interruption" पूर्ण,	\
	अणु 0x10, "External request" पूर्ण,				\
	अणु 0x14, "External interruption" पूर्ण,			\
	अणु 0x18, "I/O request" पूर्ण,				\
	अणु 0x1c, "Wait state" पूर्ण,					\
	अणु 0x20, "Validity" पूर्ण,					\
	अणु 0x28, "Stop request" पूर्ण,				\
	अणु 0x2c, "Operation exception" पूर्ण,			\
	अणु 0x38, "Partial-execution" पूर्ण,				\
	अणु 0x3c, "I/O interruption" पूर्ण,				\
	अणु 0x40, "I/O instruction" पूर्ण,				\
	अणु 0x48, "Timing subset" पूर्ण

/*
 * This is the simple पूर्णांकerceptable inकाष्ठाions decoder.
 *
 * It will be used as userspace पूर्णांकerface and it can be used in places
 * that करोes not allow to use general decoder functions,
 * such as trace events declarations.
 *
 * Some userspace tools may want to parse this code
 * and would be confused by चयन(), अगर() and other statements,
 * but they can understand conditional चालक.
 */
#घोषणा INSN_DECODE_IPA0(ipa0, insn, rshअगरt, mask)		\
	(insn >> 56) == (ipa0) ?				\
		((ipa0 << 8) | ((insn >> rshअगरt) & mask)) :

#घोषणा INSN_DECODE(insn) (insn >> 56)

/*
 * The macro icpt_insn_decoder() takes an पूर्णांकercepted inकाष्ठाion
 * and वापसs a key, which can be used to find a mnemonic name
 * of the inकाष्ठाion in the icpt_insn_codes table.
 */
#घोषणा icpt_insn_decoder(insn) (		\
	INSN_DECODE_IPA0(0x01, insn, 48, 0xff)	\
	INSN_DECODE_IPA0(0xaa, insn, 48, 0x0f)	\
	INSN_DECODE_IPA0(0xb2, insn, 48, 0xff)	\
	INSN_DECODE_IPA0(0xb9, insn, 48, 0xff)	\
	INSN_DECODE_IPA0(0xe3, insn, 48, 0xff)	\
	INSN_DECODE_IPA0(0xe5, insn, 48, 0xff)	\
	INSN_DECODE_IPA0(0xeb, insn, 16, 0xff)	\
	INSN_DECODE_IPA0(0xc8, insn, 48, 0x0f)	\
	INSN_DECODE(insn))

#पूर्ण_अगर /* _UAPI_ASM_S390_SIE_H */
