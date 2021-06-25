<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित RELOCS_H
#घोषणा RELOCS_H

#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <elf.h>
#समावेश <byteswap.h>
#घोषणा USE_BSD
#समावेश <endian.h>
#समावेश <regex.h>

व्योम die(अक्षर *fmt, ...);

/*
 * Introduced क्रम MIPSr6
 */
#अगर_अघोषित R_MIPS_PC21_S2
#घोषणा R_MIPS_PC21_S2		60
#पूर्ण_अगर

#अगर_अघोषित R_MIPS_PC26_S2
#घोषणा R_MIPS_PC26_S2		61
#पूर्ण_अगर

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

क्रमागत symtype अणु
	S_ABS,
	S_REL,
	S_SEG,
	S_LIN,
	S_NSYMTYPES
पूर्ण;

व्योम process_32(खाता *fp, पूर्णांक as_text, पूर्णांक as_bin,
		पूर्णांक show_reloc_info, पूर्णांक keep_relocs);
व्योम process_64(खाता *fp, पूर्णांक as_text, पूर्णांक as_bin,
		पूर्णांक show_reloc_info, पूर्णांक keep_relocs);
#पूर्ण_अगर /* RELOCS_H */
