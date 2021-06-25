<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_pt_insn_decoder.h: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__INTEL_PT_INSN_DECODER_H__
#घोषणा INCLUDE__INTEL_PT_INSN_DECODER_H__

#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#घोषणा INTEL_PT_INSN_DESC_MAX		32
#घोषणा INTEL_PT_INSN_BUF_SZ		16

क्रमागत पूर्णांकel_pt_insn_op अणु
	INTEL_PT_OP_OTHER,
	INTEL_PT_OP_CALL,
	INTEL_PT_OP_RET,
	INTEL_PT_OP_JCC,
	INTEL_PT_OP_JMP,
	INTEL_PT_OP_LOOP,
	INTEL_PT_OP_IRET,
	INTEL_PT_OP_INT,
	INTEL_PT_OP_SYSCALL,
	INTEL_PT_OP_SYSRET,
	INTEL_PT_OP_VMENTRY,
पूर्ण;

क्रमागत पूर्णांकel_pt_insn_branch अणु
	INTEL_PT_BR_NO_BRANCH,
	INTEL_PT_BR_INसूचीECT,
	INTEL_PT_BR_CONDITIONAL,
	INTEL_PT_BR_UNCONDITIONAL,
पूर्ण;

काष्ठा पूर्णांकel_pt_insn अणु
	क्रमागत पूर्णांकel_pt_insn_op		op;
	क्रमागत पूर्णांकel_pt_insn_branch	branch;
	पूर्णांक				length;
	पूर्णांक32_t				rel;
	अचिन्हित अक्षर			buf[INTEL_PT_INSN_BUF_SZ];
पूर्ण;

पूर्णांक पूर्णांकel_pt_get_insn(स्थिर अचिन्हित अक्षर *buf, माप_प्रकार len, पूर्णांक x86_64,
		      काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn);

स्थिर अक्षर *पूर्णांकel_pt_insn_name(क्रमागत पूर्णांकel_pt_insn_op op);

पूर्णांक पूर्णांकel_pt_insn_desc(स्थिर काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn, अक्षर *buf,
		       माप_प्रकार buf_len);

पूर्णांक पूर्णांकel_pt_insn_type(क्रमागत पूर्णांकel_pt_insn_op op);

#पूर्ण_अगर
