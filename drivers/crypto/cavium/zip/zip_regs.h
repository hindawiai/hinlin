<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#अगर_अघोषित __ZIP_REGS_H__
#घोषणा __ZIP_REGS_H__

/*
 * Configuration and status रेजिस्टर (CSR) address and type definitions क्रम
 * Cavium ZIP.
 */

#समावेश <linux/kern_levels.h>

/* ZIP invocation result completion status codes */
#घोषणा ZIP_CMD_NOTDONE        0x0

/* Successful completion. */
#घोषणा ZIP_CMD_SUCCESS        0x1

/* Output truncated */
#घोषणा ZIP_CMD_DTRUNC         0x2

/* Dynamic Stop */
#घोषणा ZIP_CMD_DYNAMIC_STOP   0x3

/* Uncompress ran out of input data when IWORD0[EF] was set */
#घोषणा ZIP_CMD_ITRUNC         0x4

/* Uncompress found the reserved block type 3 */
#घोषणा ZIP_CMD_RBLOCK         0x5

/*
 * Uncompress found LEN != ZIP_CMD_NLEN in an uncompressed block in the input.
 */
#घोषणा ZIP_CMD_NLEN           0x6

/* Uncompress found a bad code in the मुख्य Huffman codes. */
#घोषणा ZIP_CMD_BADCODE        0x7

/* Uncompress found a bad code in the 19 Huffman codes encoding lengths. */
#घोषणा ZIP_CMD_BADCODE2       0x8

/* Compress found a zero-length input. */
#घोषणा ZIP_CMD_ZERO_LEN       0x9

/* The compress or decompress encountered an पूर्णांकernal parity error. */
#घोषणा ZIP_CMD_PARITY         0xA

/*
 * Uncompress found a string identअगरier that precedes the uncompressed data and
 * decompression history.
 */
#घोषणा ZIP_CMD_FATAL          0xB

/**
 * क्रमागत zip_पूर्णांक_vec_e - ZIP MSI-X Vector Enumeration, क्रमागतerates the MSI-X
 * पूर्णांकerrupt vectors.
 */
क्रमागत zip_पूर्णांक_vec_e अणु
	ZIP_INT_VEC_E_ECCE = 0x10,
	ZIP_INT_VEC_E_FIFE = 0x11,
	ZIP_INT_VEC_E_QUE0_DONE = 0x0,
	ZIP_INT_VEC_E_QUE0_ERR = 0x8,
	ZIP_INT_VEC_E_QUE1_DONE = 0x1,
	ZIP_INT_VEC_E_QUE1_ERR = 0x9,
	ZIP_INT_VEC_E_QUE2_DONE = 0x2,
	ZIP_INT_VEC_E_QUE2_ERR = 0xa,
	ZIP_INT_VEC_E_QUE3_DONE = 0x3,
	ZIP_INT_VEC_E_QUE3_ERR = 0xb,
	ZIP_INT_VEC_E_QUE4_DONE = 0x4,
	ZIP_INT_VEC_E_QUE4_ERR = 0xc,
	ZIP_INT_VEC_E_QUE5_DONE = 0x5,
	ZIP_INT_VEC_E_QUE5_ERR = 0xd,
	ZIP_INT_VEC_E_QUE6_DONE = 0x6,
	ZIP_INT_VEC_E_QUE6_ERR = 0xe,
	ZIP_INT_VEC_E_QUE7_DONE = 0x7,
	ZIP_INT_VEC_E_QUE7_ERR = 0xf,
	ZIP_INT_VEC_E_ENUM_LAST = 0x12,
पूर्ण;

/**
 * जोड़ zip_zptr_addr_s - ZIP Generic Poपूर्णांकer Structure क्रम ADDR.
 *
 * It is the generic क्रमmat of poपूर्णांकers in ZIP_INST_S.
 */
जोड़ zip_zptr_addr_s अणु
	u64 u_reg64;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_49_63              : 15;
		u64 addr                        : 49;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 addr                        : 49;
		u64 reserved_49_63              : 15;
#पूर्ण_अगर
	पूर्ण s;

पूर्ण;

/**
 * जोड़ zip_zptr_ctl_s - ZIP Generic Poपूर्णांकer Structure क्रम CTL.
 *
 * It is the generic क्रमmat of poपूर्णांकers in ZIP_INST_S.
 */
जोड़ zip_zptr_ctl_s अणु
	u64 u_reg64;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_112_127            : 16;
		u64 length                      : 16;
		u64 reserved_67_95              : 29;
		u64 fw                          : 1;
		u64 nc                          : 1;
		u64 data_be                     : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 data_be                     : 1;
		u64 nc                          : 1;
		u64 fw                          : 1;
		u64 reserved_67_95              : 29;
		u64 length                      : 16;
		u64 reserved_112_127            : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * जोड़ zip_inst_s - ZIP Inकाष्ठाion Structure.
 * Each ZIP inकाष्ठाion has 16 words (they are called IWORD0 to IWORD15 within
 * the काष्ठाure).
 */
जोड़ zip_inst_s अणु
	u64 u_reg64[16];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 करोneपूर्णांक                     : 1;
		u64 reserved_56_62              : 7;
		u64 totaloutputlength           : 24;
		u64 reserved_27_31              : 5;
		u64 exn                         : 3;
		u64 reserved_23_23              : 1;
		u64 exbits                      : 7;
		u64 reserved_12_15              : 4;
		u64 sf                          : 1;
		u64 ss                          : 2;
		u64 cc                          : 2;
		u64 ef                          : 1;
		u64 bf                          : 1;
		u64 ce                          : 1;
		u64 reserved_3_3                : 1;
		u64 ds                          : 1;
		u64 dg                          : 1;
		u64 hg                          : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 hg                          : 1;
		u64 dg                          : 1;
		u64 ds                          : 1;
		u64 reserved_3_3                : 1;
		u64 ce                          : 1;
		u64 bf                          : 1;
		u64 ef                          : 1;
		u64 cc                          : 2;
		u64 ss                          : 2;
		u64 sf                          : 1;
		u64 reserved_12_15              : 4;
		u64 exbits                      : 7;
		u64 reserved_23_23              : 1;
		u64 exn                         : 3;
		u64 reserved_27_31              : 5;
		u64 totaloutputlength           : 24;
		u64 reserved_56_62              : 7;
		u64 करोneपूर्णांक                     : 1;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 historylength               : 16;
		u64 reserved_96_111             : 16;
		u64 adlercrc32                  : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 adlercrc32                  : 32;
		u64 reserved_96_111             : 16;
		u64 historylength               : 16;
#पूर्ण_अगर
		जोड़ zip_zptr_addr_s ctx_ptr_addr;
		जोड़ zip_zptr_ctl_s ctx_ptr_ctl;
		जोड़ zip_zptr_addr_s his_ptr_addr;
		जोड़ zip_zptr_ctl_s his_ptr_ctl;
		जोड़ zip_zptr_addr_s inp_ptr_addr;
		जोड़ zip_zptr_ctl_s inp_ptr_ctl;
		जोड़ zip_zptr_addr_s out_ptr_addr;
		जोड़ zip_zptr_ctl_s out_ptr_ctl;
		जोड़ zip_zptr_addr_s res_ptr_addr;
		जोड़ zip_zptr_ctl_s res_ptr_ctl;
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_817_831            : 15;
		u64 wq_ptr                      : 49;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 wq_ptr                      : 49;
		u64 reserved_817_831            : 15;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_882_895            : 14;
		u64 tt                          : 2;
		u64 reserved_874_879            : 6;
		u64 grp                         : 10;
		u64 tag                         : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 tag                         : 32;
		u64 grp                         : 10;
		u64 reserved_874_879            : 6;
		u64 tt                          : 2;
		u64 reserved_882_895            : 14;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_896_959            : 64;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 reserved_896_959            : 64;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_960_1023           : 64;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 reserved_960_1023           : 64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * जोड़ zip_nptr_s - ZIP Inकाष्ठाion Next-Chunk-Buffer Poपूर्णांकer (NPTR)
 * Structure
 *
 * ZIP_NPTR काष्ठाure is used to chain all the zip inकाष्ठाion buffers
 * together. ZIP inकाष्ठाion buffers are managed (allocated and released) by
 * the software.
 */
जोड़ zip_nptr_s अणु
	u64 u_reg64;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_49_63              : 15;
		u64 addr                        : 49;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 addr                        : 49;
		u64 reserved_49_63              : 15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * जोड़ zip_zptr_s - ZIP Generic Poपूर्णांकer Structure.
 *
 * It is the generic क्रमmat of poपूर्णांकers in ZIP_INST_S.
 */
जोड़ zip_zptr_s अणु
	u64 u_reg64[2];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_49_63              : 15;
		u64 addr                        : 49;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 addr                        : 49;
		u64 reserved_49_63              : 15;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_112_127            : 16;
		u64 length                      : 16;
		u64 reserved_67_95              : 29;
		u64 fw                          : 1;
		u64 nc                          : 1;
		u64 data_be                     : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 data_be                     : 1;
		u64 nc                          : 1;
		u64 fw                          : 1;
		u64 reserved_67_95              : 29;
		u64 length                      : 16;
		u64 reserved_112_127            : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * जोड़ zip_zres_s - ZIP Result Structure
 *
 * The ZIP coprocessor ग_लिखोs the result काष्ठाure after it completes the
 * invocation. The result काष्ठाure is exactly 24 bytes, and each invocation of
 * the ZIP coprocessor produces exactly one result काष्ठाure.
 */
जोड़ zip_zres_s अणु
	u64 u_reg64[3];
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 crc32                       : 32;
		u64 adler32                     : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 adler32                     : 32;
		u64 crc32                       : 32;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 totalbyteswritten           : 32;
		u64 totalbytesपढ़ो              : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 totalbytesपढ़ो              : 32;
		u64 totalbyteswritten           : 32;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 totalbitsprocessed          : 32;
		u64 करोneपूर्णांक                     : 1;
		u64 reserved_155_158            : 4;
		u64 exn                         : 3;
		u64 reserved_151_151            : 1;
		u64 exbits                      : 7;
		u64 reserved_137_143            : 7;
		u64 ef                          : 1;

		अस्थिर u64 compcode           : 8;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)

		अस्थिर u64 compcode           : 8;
		u64 ef                          : 1;
		u64 reserved_137_143            : 7;
		u64 exbits                      : 7;
		u64 reserved_151_151            : 1;
		u64 exn                         : 3;
		u64 reserved_155_158            : 4;
		u64 करोneपूर्णांक                     : 1;
		u64 totalbitsprocessed          : 32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/**
 * जोड़ zip_cmd_ctl - Structure representing the रेजिस्टर that controls
 * घड़ी and reset.
 */
जोड़ zip_cmd_ctl अणु
	u64 u_reg64;
	काष्ठा zip_cmd_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_2_63               : 62;
		u64 क्रमceclk                    : 1;
		u64 reset                       : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 reset                       : 1;
		u64 क्रमceclk                    : 1;
		u64 reserved_2_63               : 62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_CMD_CTL 0x0ull

/**
 * जोड़ zip_स्थिरants - Data काष्ठाure representing the रेजिस्टर that contains
 * all of the current implementation-related parameters of the zip core in this
 * chip.
 */
जोड़ zip_स्थिरants अणु
	u64 u_reg64;
	काष्ठा zip_स्थिरants_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 nexec                       : 8;
		u64 reserved_49_55              : 7;
		u64 syncflush_capable           : 1;
		u64 depth                       : 16;
		u64 onfsize                     : 12;
		u64 ctxsize                     : 12;
		u64 reserved_1_7                : 7;
		u64 disabled                    : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 disabled                    : 1;
		u64 reserved_1_7                : 7;
		u64 ctxsize                     : 12;
		u64 onfsize                     : 12;
		u64 depth                       : 16;
		u64 syncflush_capable           : 1;
		u64 reserved_49_55              : 7;
		u64 nexec                       : 8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_CONSTANTS 0x00A0ull

/**
 * जोड़ zip_corex_bist_status - Represents रेजिस्टरs which have the BIST
 * status of memories in zip cores.
 *
 * Each bit is the BIST result of an inभागidual memory
 * (per bit, 0 = pass and 1 = fail).
 */
जोड़ zip_corex_bist_status अणु
	u64 u_reg64;
	काष्ठा zip_corex_bist_status_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_53_63              : 11;
		u64 bstatus                     : 53;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 bstatus                     : 53;
		u64 reserved_53_63              : 11;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_COREX_BIST_STATUS(u64 param1)
अणु
	अगर (param1 <= 1)
		वापस 0x0520ull + (param1 & 1) * 0x8ull;
	pr_err("ZIP_COREX_BIST_STATUS: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_ctl_bist_status - Represents रेजिस्टर that has the BIST status of
 * memories in ZIP_CTL (inकाष्ठाion buffer, G/S poपूर्णांकer FIFO, input data
 * buffer, output data buffers).
 *
 * Each bit is the BIST result of an inभागidual memory
 * (per bit, 0 = pass and 1 = fail).
 */
जोड़ zip_ctl_bist_status अणु
	u64 u_reg64;
	काष्ठा zip_ctl_bist_status_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_9_63               : 55;
		u64 bstatus                     : 9;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 bstatus                     : 9;
		u64 reserved_9_63               : 55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_CTL_BIST_STATUS 0x0510ull

/**
 * जोड़ zip_ctl_cfg - Represents the रेजिस्टर that controls the behavior of
 * the ZIP DMA engines.
 *
 * It is recommended to keep शेष values क्रम normal operation. Changing the
 * values of the fields may be useful क्रम diagnostics.
 */
जोड़ zip_ctl_cfg अणु
	u64 u_reg64;
	काष्ठा zip_ctl_cfg_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_52_63              : 12;
		u64 ildf                        : 4;
		u64 reserved_36_47              : 12;
		u64 drtf                        : 4;
		u64 reserved_27_31              : 5;
		u64 stcf                        : 3;
		u64 reserved_19_23              : 5;
		u64 ldf                         : 3;
		u64 reserved_2_15               : 14;
		u64 busy                        : 1;
		u64 reserved_0_0                : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 reserved_0_0                : 1;
		u64 busy                        : 1;
		u64 reserved_2_15               : 14;
		u64 ldf                         : 3;
		u64 reserved_19_23              : 5;
		u64 stcf                        : 3;
		u64 reserved_27_31              : 5;
		u64 drtf                        : 4;
		u64 reserved_36_47              : 12;
		u64 ildf                        : 4;
		u64 reserved_52_63              : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_CTL_CFG 0x0560ull

/**
 * जोड़ zip_dbg_corex_inst - Represents the रेजिस्टरs that reflect the status
 * of the current inकाष्ठाion that the ZIP core is executing or has executed.
 *
 * These रेजिस्टरs are only क्रम debug use.
 */
जोड़ zip_dbg_corex_inst अणु
	u64 u_reg64;
	काष्ठा zip_dbg_corex_inst_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 busy                        : 1;
		u64 reserved_35_62              : 28;
		u64 qid                         : 3;
		u64 iid                         : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 iid                         : 32;
		u64 qid                         : 3;
		u64 reserved_35_62              : 28;
		u64 busy                        : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_DBG_COREX_INST(u64 param1)
अणु
	अगर (param1 <= 1)
		वापस 0x0640ull + (param1 & 1) * 0x8ull;
	pr_err("ZIP_DBG_COREX_INST: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_dbg_corex_sta - Represents रेजिस्टरs that reflect the status of
 * the zip cores.
 *
 * They are क्रम debug use only.
 */
जोड़ zip_dbg_corex_sta अणु
	u64 u_reg64;
	काष्ठा zip_dbg_corex_sta_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 busy                        : 1;
		u64 reserved_37_62              : 26;
		u64 ist                         : 5;
		u64 nie                         : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 nie                         : 32;
		u64 ist                         : 5;
		u64 reserved_37_62              : 26;
		u64 busy                        : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_DBG_COREX_STA(u64 param1)
अणु
	अगर (param1 <= 1)
		वापस 0x0680ull + (param1 & 1) * 0x8ull;
	pr_err("ZIP_DBG_COREX_STA: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_dbg_quex_sta - Represets रेजिस्टरs that reflect status of the zip
 * inकाष्ठाion queues.
 *
 * They are क्रम debug use only.
 */
जोड़ zip_dbg_quex_sta अणु
	u64 u_reg64;
	काष्ठा zip_dbg_quex_sta_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 busy                        : 1;
		u64 reserved_56_62              : 7;
		u64 rqwc                        : 24;
		u64 nii                         : 32;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 nii                         : 32;
		u64 rqwc                        : 24;
		u64 reserved_56_62              : 7;
		u64 busy                        : 1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_DBG_QUEX_STA(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x1800ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_DBG_QUEX_STA: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_ecc_ctl - Represents the रेजिस्टर that enables ECC क्रम each
 * inभागidual पूर्णांकernal memory that requires ECC.
 *
 * For debug purpose, it can also flip one or two bits in the ECC data.
 */
जोड़ zip_ecc_ctl अणु
	u64 u_reg64;
	काष्ठा zip_ecc_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_19_63              : 45;
		u64 vmem_cdis                   : 1;
		u64 vmem_fs                     : 2;
		u64 reserved_15_15              : 1;
		u64 idf1_cdis                   : 1;
		u64 idf1_fs                     : 2;
		u64 reserved_11_11              : 1;
		u64 idf0_cdis                   : 1;
		u64 idf0_fs                     : 2;
		u64 reserved_7_7                : 1;
		u64 gspf_cdis                   : 1;
		u64 gspf_fs                     : 2;
		u64 reserved_3_3                : 1;
		u64 iqf_cdis                    : 1;
		u64 iqf_fs                      : 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 iqf_fs                      : 2;
		u64 iqf_cdis                    : 1;
		u64 reserved_3_3                : 1;
		u64 gspf_fs                     : 2;
		u64 gspf_cdis                   : 1;
		u64 reserved_7_7                : 1;
		u64 idf0_fs                     : 2;
		u64 idf0_cdis                   : 1;
		u64 reserved_11_11              : 1;
		u64 idf1_fs                     : 2;
		u64 idf1_cdis                   : 1;
		u64 reserved_15_15              : 1;
		u64 vmem_fs                     : 2;
		u64 vmem_cdis                   : 1;
		u64 reserved_19_63              : 45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_ECC_CTL 0x0568ull

/* NCB - zip_ecce_ena_w1c */
जोड़ zip_ecce_ena_w1c अणु
	u64 u_reg64;
	काष्ठा zip_ecce_ena_w1c_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_37_63              : 27;
		u64 dbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 sbe                         : 5;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 sbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 dbe                         : 5;
		u64 reserved_37_63              : 27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_ECCE_ENA_W1C 0x0598ull

/* NCB - zip_ecce_ena_w1s */
जोड़ zip_ecce_ena_w1s अणु
	u64 u_reg64;
	काष्ठा zip_ecce_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_37_63              : 27;
		u64 dbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 sbe                         : 5;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 sbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 dbe                         : 5;
		u64 reserved_37_63              : 27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_ECCE_ENA_W1S 0x0590ull

/**
 * जोड़ zip_ecce_पूर्णांक - Represents the रेजिस्टर that contains the status of the
 * ECC पूर्णांकerrupt sources.
 */
जोड़ zip_ecce_पूर्णांक अणु
	u64 u_reg64;
	काष्ठा zip_ecce_पूर्णांक_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_37_63              : 27;
		u64 dbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 sbe                         : 5;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 sbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 dbe                         : 5;
		u64 reserved_37_63              : 27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_ECCE_INT 0x0580ull

/* NCB - zip_ecce_पूर्णांक_w1s */
जोड़ zip_ecce_पूर्णांक_w1s अणु
	u64 u_reg64;
	काष्ठा zip_ecce_पूर्णांक_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_37_63              : 27;
		u64 dbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 sbe                         : 5;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 sbe                         : 5;
		u64 reserved_5_31               : 27;
		u64 dbe                         : 5;
		u64 reserved_37_63              : 27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_ECCE_INT_W1S 0x0588ull

/* NCB - zip_fअगरe_ena_w1c */
जोड़ zip_fअगरe_ena_w1c अणु
	u64 u_reg64;
	काष्ठा zip_fअगरe_ena_w1c_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_42_63              : 22;
		u64 निश्चितs                     : 42;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 निश्चितs                     : 42;
		u64 reserved_42_63              : 22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_FIFE_ENA_W1C 0x0090ull

/* NCB - zip_fअगरe_ena_w1s */
जोड़ zip_fअगरe_ena_w1s अणु
	u64 u_reg64;
	काष्ठा zip_fअगरe_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_42_63              : 22;
		u64 निश्चितs                     : 42;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 निश्चितs                     : 42;
		u64 reserved_42_63              : 22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_FIFE_ENA_W1S 0x0088ull

/* NCB - zip_fअगरe_पूर्णांक */
जोड़ zip_fअगरe_पूर्णांक अणु
	u64 u_reg64;
	काष्ठा zip_fअगरe_पूर्णांक_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_42_63              : 22;
		u64 निश्चितs                     : 42;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 निश्चितs                     : 42;
		u64 reserved_42_63              : 22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_FIFE_INT 0x0078ull

/* NCB - zip_fअगरe_पूर्णांक_w1s */
जोड़ zip_fअगरe_पूर्णांक_w1s अणु
	u64 u_reg64;
	काष्ठा zip_fअगरe_पूर्णांक_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_42_63              : 22;
		u64 निश्चितs                     : 42;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 निश्चितs                     : 42;
		u64 reserved_42_63              : 22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_FIFE_INT_W1S 0x0080ull

/**
 * जोड़ zip_msix_pbax - Represents the रेजिस्टर that is the MSI-X PBA table
 *
 * The bit number is indexed by the ZIP_INT_VEC_E क्रमागतeration.
 */
जोड़ zip_msix_pbax अणु
	u64 u_reg64;
	काष्ठा zip_msix_pbax_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 pend                        : 64;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 pend                        : 64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_MSIX_PBAX(u64 param1)
अणु
	अगर (param1 == 0)
		वापस 0x0000838000FF0000ull;
	pr_err("ZIP_MSIX_PBAX: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_msix_vecx_addr - Represents the रेजिस्टर that is the MSI-X vector
 * table, indexed by the ZIP_INT_VEC_E क्रमागतeration.
 */
जोड़ zip_msix_vecx_addr अणु
	u64 u_reg64;
	काष्ठा zip_msix_vecx_addr_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_49_63              : 15;
		u64 addr                        : 47;
		u64 reserved_1_1                : 1;
		u64 secvec                      : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 secvec                      : 1;
		u64 reserved_1_1                : 1;
		u64 addr                        : 47;
		u64 reserved_49_63              : 15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_MSIX_VECX_ADDR(u64 param1)
अणु
	अगर (param1 <= 17)
		वापस 0x0000838000F00000ull + (param1 & 31) * 0x10ull;
	pr_err("ZIP_MSIX_VECX_ADDR: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_msix_vecx_ctl - Represents the रेजिस्टर that is the MSI-X vector
 * table, indexed by the ZIP_INT_VEC_E क्रमागतeration.
 */
जोड़ zip_msix_vecx_ctl अणु
	u64 u_reg64;
	काष्ठा zip_msix_vecx_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_33_63              : 31;
		u64 mask                        : 1;
		u64 reserved_20_31              : 12;
		u64 data                        : 20;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 data                        : 20;
		u64 reserved_20_31              : 12;
		u64 mask                        : 1;
		u64 reserved_33_63              : 31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_MSIX_VECX_CTL(u64 param1)
अणु
	अगर (param1 <= 17)
		वापस 0x0000838000F00008ull + (param1 & 31) * 0x10ull;
	pr_err("ZIP_MSIX_VECX_CTL: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोne - Represents the रेजिस्टरs that contain the per-queue
 * inकाष्ठाion करोne count.
 */
जोड़ zip_quex_करोne अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोne_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_20_63              : 44;
		u64 करोne                        : 20;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोne                        : 20;
		u64 reserved_20_63              : 44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DONE(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x2000ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DONE: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोne_ack - Represents the रेजिस्टरs on ग_लिखो to which will
 * decrement the per-queue inकाष्ठाiona करोne count.
 */
जोड़ zip_quex_करोne_ack अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोne_ack_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_20_63              : 44;
		u64 करोne_ack                    : 20;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोne_ack                    : 20;
		u64 reserved_20_63              : 44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DONE_ACK(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x2200ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DONE_ACK: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोne_ena_w1c - Represents the रेजिस्टर which when written
 * 1 to will disable the DONEINT पूर्णांकerrupt क्रम the queue.
 */
जोड़ zip_quex_करोne_ena_w1c अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोne_ena_w1c_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_1_63               : 63;
		u64 करोne_ena                    : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोne_ena                    : 1;
		u64 reserved_1_63               : 63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DONE_ENA_W1C(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x2600ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DONE_ENA_W1C: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोne_ena_w1s - Represents the रेजिस्टर that when written 1 to
 * will enable the DONEINT पूर्णांकerrupt क्रम the queue.
 */
जोड़ zip_quex_करोne_ena_w1s अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोne_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_1_63               : 63;
		u64 करोne_ena                    : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोne_ena                    : 1;
		u64 reserved_1_63               : 63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DONE_ENA_W1S(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x2400ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DONE_ENA_W1S: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोne_रुको - Represents the रेजिस्टर that specअगरies the per
 * queue पूर्णांकerrupt coalescing settings.
 */
जोड़ zip_quex_करोne_रुको अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोne_रुको_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_48_63              : 16;
		u64 समय_रुको                   : 16;
		u64 reserved_20_31              : 12;
		u64 num_रुको                    : 20;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 num_रुको                    : 20;
		u64 reserved_20_31              : 12;
		u64 समय_रुको                   : 16;
		u64 reserved_48_63              : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DONE_WAIT(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x2800ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DONE_WAIT: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_करोorbell - Represents करोorbell रेजिस्टरs क्रम the ZIP
 * inकाष्ठाion queues.
 */
जोड़ zip_quex_करोorbell अणु
	u64 u_reg64;
	काष्ठा zip_quex_करोorbell_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_20_63              : 44;
		u64 dbell_cnt                   : 20;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 dbell_cnt                   : 20;
		u64 reserved_20_63              : 44;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_DOORBELL(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x4000ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_DOORBELL: %llu\n", param1);
	वापस 0;
पूर्ण

जोड़ zip_quex_err_ena_w1c अणु
	u64 u_reg64;
	काष्ठा zip_quex_err_ena_w1c_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwrp                        : 1;
		u64 nrrp                        : 1;
		u64 irde                        : 1;
		u64 करोvf                        : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोvf                        : 1;
		u64 irde                        : 1;
		u64 nrrp                        : 1;
		u64 nwrp                        : 1;
		u64 mdbe                        : 1;
		u64 reserved_5_63               : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_ERR_ENA_W1C(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x3600ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_ERR_ENA_W1C: %llu\n", param1);
	वापस 0;
पूर्ण

जोड़ zip_quex_err_ena_w1s अणु
	u64 u_reg64;
	काष्ठा zip_quex_err_ena_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwrp                        : 1;
		u64 nrrp                        : 1;
		u64 irde                        : 1;
		u64 करोvf                        : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोvf                        : 1;
		u64 irde                        : 1;
		u64 nrrp                        : 1;
		u64 nwrp                        : 1;
		u64 mdbe                        : 1;
		u64 reserved_5_63               : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_ERR_ENA_W1S(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x3400ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_ERR_ENA_W1S: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_err_पूर्णांक - Represents रेजिस्टरs that contain the per-queue
 * error पूर्णांकerrupts.
 */
जोड़ zip_quex_err_पूर्णांक अणु
	u64 u_reg64;
	काष्ठा zip_quex_err_पूर्णांक_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwrp                        : 1;
		u64 nrrp                        : 1;
		u64 irde                        : 1;
		u64 करोvf                        : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोvf                        : 1;
		u64 irde                        : 1;
		u64 nrrp                        : 1;
		u64 nwrp                        : 1;
		u64 mdbe                        : 1;
		u64 reserved_5_63               : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_ERR_INT(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x3000ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_ERR_INT: %llu\n", param1);
	वापस 0;
पूर्ण

/* NCB - zip_que#_err_पूर्णांक_w1s */
जोड़ zip_quex_err_पूर्णांक_w1s अणु
	u64 u_reg64;
	काष्ठा zip_quex_err_पूर्णांक_w1s_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwrp                        : 1;
		u64 nrrp                        : 1;
		u64 irde                        : 1;
		u64 करोvf                        : 1;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 करोvf                        : 1;
		u64 irde                        : 1;
		u64 nrrp                        : 1;
		u64 nwrp                        : 1;
		u64 mdbe                        : 1;
		u64 reserved_5_63               : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_ERR_INT_W1S(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x3200ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_ERR_INT_W1S: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_gcfg - Represents the रेजिस्टरs that reflect status of the
 * zip inकाष्ठाion queues,debug use only.
 */
जोड़ zip_quex_gcfg अणु
	u64 u_reg64;
	काष्ठा zip_quex_gcfg_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_4_63               : 60;
		u64 iqb_ldwb                    : 1;
		u64 cbw_sty                     : 1;
		u64 l2ld_cmd                    : 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 l2ld_cmd                    : 2;
		u64 cbw_sty                     : 1;
		u64 iqb_ldwb                    : 1;
		u64 reserved_4_63               : 60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_GCFG(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x1A00ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_GCFG: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_map - Represents the रेजिस्टरs that control how each
 * inकाष्ठाion queue maps to zip cores.
 */
जोड़ zip_quex_map अणु
	u64 u_reg64;
	काष्ठा zip_quex_map_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_2_63               : 62;
		u64 zce                         : 2;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 zce                         : 2;
		u64 reserved_2_63               : 62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_MAP(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x1400ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_MAP: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_sbuf_addr - Represents the रेजिस्टरs that set the buffer
 * parameters क्रम the inकाष्ठाion queues.
 *
 * When quiescent (i.e. outstanding करोorbell count is 0), it is safe to reग_लिखो
 * this रेजिस्टर to effectively reset the command buffer state machine.
 * These रेजिस्टरs must be programmed after SW programs the corresponding
 * ZIP_QUE(0..7)_SBUF_CTL.
 */
जोड़ zip_quex_sbuf_addr अणु
	u64 u_reg64;
	काष्ठा zip_quex_sbuf_addr_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_49_63              : 15;
		u64 ptr                         : 42;
		u64 off                         : 7;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 off                         : 7;
		u64 ptr                         : 42;
		u64 reserved_49_63              : 15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_SBUF_ADDR(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x1000ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_SBUF_ADDR: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_quex_sbuf_ctl - Represents the रेजिस्टरs that set the buffer
 * parameters क्रम the inकाष्ठाion queues.
 *
 * When quiescent (i.e. outstanding करोorbell count is 0), it is safe to reग_लिखो
 * this रेजिस्टर to effectively reset the command buffer state machine.
 * These रेजिस्टरs must be programmed beक्रमe SW programs the corresponding
 * ZIP_QUE(0..7)_SBUF_ADDR.
 */
जोड़ zip_quex_sbuf_ctl अणु
	u64 u_reg64;
	काष्ठा zip_quex_sbuf_ctl_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_45_63              : 19;
		u64 size                        : 13;
		u64 inst_be                     : 1;
		u64 reserved_24_30              : 7;
		u64 stream_id                   : 8;
		u64 reserved_12_15              : 4;
		u64 aura                        : 12;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 aura                        : 12;
		u64 reserved_12_15              : 4;
		u64 stream_id                   : 8;
		u64 reserved_24_30              : 7;
		u64 inst_be                     : 1;
		u64 size                        : 13;
		u64 reserved_45_63              : 19;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

अटल अंतरभूत u64 ZIP_QUEX_SBUF_CTL(u64 param1)
अणु
	अगर (param1 <= 7)
		वापस 0x1200ull + (param1 & 7) * 0x8ull;
	pr_err("ZIP_QUEX_SBUF_CTL: %llu\n", param1);
	वापस 0;
पूर्ण

/**
 * जोड़ zip_que_ena - Represents queue enable रेजिस्टर
 *
 * If a queue is disabled, ZIP_CTL stops fetching inकाष्ठाions from the queue.
 */
जोड़ zip_que_ena अणु
	u64 u_reg64;
	काष्ठा zip_que_ena_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_8_63               : 56;
		u64 ena                         : 8;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 ena                         : 8;
		u64 reserved_8_63               : 56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_QUE_ENA 0x0500ull

/**
 * जोड़ zip_que_pri - Represents the रेजिस्टर that defines the priority
 * between inकाष्ठाion queues.
 */
जोड़ zip_que_pri अणु
	u64 u_reg64;
	काष्ठा zip_que_pri_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_8_63               : 56;
		u64 pri                         : 8;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 pri                         : 8;
		u64 reserved_8_63               : 56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_QUE_PRI 0x0508ull

/**
 * जोड़ zip_throttle - Represents the रेजिस्टर that controls the maximum
 * number of in-flight X2I data fetch transactions.
 *
 * Writing 0 to this रेजिस्टर causes the ZIP module to temporarily suspend NCB
 * accesses; it is not recommended क्रम normal operation, but may be useful क्रम
 * diagnostics.
 */
जोड़ zip_throttle अणु
	u64 u_reg64;
	काष्ठा zip_throttle_s अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 reserved_6_63               : 58;
		u64 ld_infl                     : 6;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u64 ld_infl                     : 6;
		u64 reserved_6_63               : 58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#घोषणा ZIP_THROTTLE 0x0010ull

#पूर्ण_अगर /* _CSRS_ZIP__ */
