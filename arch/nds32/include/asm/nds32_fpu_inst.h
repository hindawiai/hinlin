<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2005-2018 Andes Technology Corporation */

#अगर_अघोषित __NDS32_FPU_INST_H
#घोषणा __NDS32_FPU_INST_H

#घोषणा cop0_op	0x35

/*
 * COP0 field of opcodes.
 */
#घोषणा fs1_op	0x0
#घोषणा fs2_op  0x4
#घोषणा fd1_op  0x8
#घोषणा fd2_op  0xc

/*
 * FS1 opcode.
 */
क्रमागत fs1 अणु
	fadds_op, fsubs_op, fcpynss_op, fcpyss_op,
	fmadds_op, fmsubs_op, fcmovns_op, fcmovzs_op,
	fnmadds_op, fnmsubs_op,
	fmuls_op = 0xc, fभागs_op,
	fs1_f2op_op = 0xf
पूर्ण;

/*
 * FS1/F2OP opcode.
 */
क्रमागत fs1_f2 अणु
	fs2d_op, fवर्ग_मूलs_op,
	fui2s_op = 0x8, fsi2s_op = 0xc,
	fs2ui_op = 0x10, fs2ui_z_op = 0x14,
	fs2si_op = 0x18, fs2si_z_op = 0x1c
पूर्ण;

/*
 * FS2 opcode.
 */
क्रमागत fs2 अणु
	fcmpeqs_op, fcmpeqs_e_op, fcmplts_op, fcmplts_e_op,
	fcmples_op, fcmples_e_op, fcmpuns_op, fcmpuns_e_op
पूर्ण;

/*
 * FD1 opcode.
 */
क्रमागत fd1 अणु
	faddd_op, fsubd_op, fcpynsd_op, fcpysd_op,
	fmaddd_op, fmsubd_op, fcmovnd_op, fcmovzd_op,
	fnmaddd_op, fnmsubd_op,
	fmuld_op = 0xc, fभागd_op, fd1_f2op_op = 0xf
पूर्ण;

/*
 * FD1/F2OP opcode.
 */
क्रमागत fd1_f2 अणु
	fd2s_op, fवर्ग_मूलd_op,
	fui2d_op = 0x8, fsi2d_op = 0xc,
	fd2ui_op = 0x10, fd2ui_z_op = 0x14,
	fd2si_op = 0x18, fd2si_z_op = 0x1c
पूर्ण;

/*
 * FD2 opcode.
 */
क्रमागत fd2 अणु
	fcmpeqd_op, fcmpeqd_e_op, fcmpltd_op, fcmpltd_e_op,
	fcmpled_op, fcmpled_e_op, fcmpund_op, fcmpund_e_op
पूर्ण;

#घोषणा NDS32Insn(x) x

#घोषणा I_OPCODE_off			25
#घोषणा NDS32Insn_OPCODE(x)		(NDS32Insn(x) >> I_OPCODE_off)

#घोषणा I_OPCODE_offRt			20
#घोषणा I_OPCODE_mskRt			(0x1fUL << I_OPCODE_offRt)
#घोषणा NDS32Insn_OPCODE_Rt(x) \
	((NDS32Insn(x) & I_OPCODE_mskRt) >> I_OPCODE_offRt)

#घोषणा I_OPCODE_offRa			15
#घोषणा I_OPCODE_mskRa			(0x1fUL << I_OPCODE_offRa)
#घोषणा NDS32Insn_OPCODE_Ra(x) \
	((NDS32Insn(x) & I_OPCODE_mskRa) >> I_OPCODE_offRa)

#घोषणा I_OPCODE_offRb			10
#घोषणा I_OPCODE_mskRb			(0x1fUL << I_OPCODE_offRb)
#घोषणा NDS32Insn_OPCODE_Rb(x) \
	((NDS32Insn(x) & I_OPCODE_mskRb) >> I_OPCODE_offRb)

#घोषणा I_OPCODE_offbit1014		10
#घोषणा I_OPCODE_mskbit1014		(0x1fUL << I_OPCODE_offbit1014)
#घोषणा NDS32Insn_OPCODE_BIT1014(x) \
	((NDS32Insn(x) & I_OPCODE_mskbit1014) >> I_OPCODE_offbit1014)

#घोषणा I_OPCODE_offbit69		6
#घोषणा I_OPCODE_mskbit69		(0xfUL << I_OPCODE_offbit69)
#घोषणा NDS32Insn_OPCODE_BIT69(x) \
	((NDS32Insn(x) & I_OPCODE_mskbit69) >> I_OPCODE_offbit69)

#घोषणा I_OPCODE_offCOP0		0
#घोषणा I_OPCODE_mskCOP0		(0x3fUL << I_OPCODE_offCOP0)
#घोषणा NDS32Insn_OPCODE_COP0(x) \
	((NDS32Insn(x) & I_OPCODE_mskCOP0) >> I_OPCODE_offCOP0)

#पूर्ण_अगर /* __NDS32_FPU_INST_H */
