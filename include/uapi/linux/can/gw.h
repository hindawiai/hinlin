<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0-only WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * linux/can/gw.h
 *
 * Definitions क्रम CAN frame Gateway/Router/Bridge
 *
 * Author: Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 * Copyright (c) 2011 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#अगर_अघोषित _UAPI_CAN_GW_H
#घोषणा _UAPI_CAN_GW_H

#समावेश <linux/types.h>
#समावेश <linux/can.h>

काष्ठा rtcanmsg अणु
	__u8  can_family;
	__u8  gwtype;
	__u16 flags;
पूर्ण;

/* CAN gateway types */
क्रमागत अणु
	CGW_TYPE_UNSPEC,
	CGW_TYPE_CAN_CAN,	/* CAN->CAN routing */
	__CGW_TYPE_MAX
पूर्ण;

#घोषणा CGW_TYPE_MAX (__CGW_TYPE_MAX - 1)

/* CAN rtnetlink attribute definitions */
क्रमागत अणु
	CGW_UNSPEC,
	CGW_MOD_AND,	/* CAN frame modअगरication binary AND */
	CGW_MOD_OR,	/* CAN frame modअगरication binary OR */
	CGW_MOD_XOR,	/* CAN frame modअगरication binary XOR */
	CGW_MOD_SET,	/* CAN frame modअगरication set alternate values */
	CGW_CS_XOR,	/* set data[] XOR checksum पूर्णांकo data[index] */
	CGW_CS_CRC8,	/* set data[] CRC8 checksum पूर्णांकo data[index] */
	CGW_HANDLED,	/* number of handled CAN frames */
	CGW_DROPPED,	/* number of dropped CAN frames */
	CGW_SRC_IF,	/* अगरindex of source network पूर्णांकerface */
	CGW_DST_IF,	/* अगरindex of destination network पूर्णांकerface */
	CGW_FILTER,	/* specअगरy काष्ठा can_filter on source CAN device */
	CGW_DELETED,	/* number of deleted CAN frames (see max_hops param) */
	CGW_LIM_HOPS,	/* limit the number of hops of this specअगरic rule */
	CGW_MOD_UID,	/* user defined identअगरier क्रम modअगरication updates */
	CGW_FDMOD_AND,	/* CAN FD frame modअगरication binary AND */
	CGW_FDMOD_OR,	/* CAN FD frame modअगरication binary OR */
	CGW_FDMOD_XOR,	/* CAN FD frame modअगरication binary XOR */
	CGW_FDMOD_SET,	/* CAN FD frame modअगरication set alternate values */
	__CGW_MAX
पूर्ण;

#घोषणा CGW_MAX (__CGW_MAX - 1)

#घोषणा CGW_FLAGS_CAN_ECHO 0x01
#घोषणा CGW_FLAGS_CAN_SRC_TSTAMP 0x02
#घोषणा CGW_FLAGS_CAN_IIF_TX_OK 0x04
#घोषणा CGW_FLAGS_CAN_FD 0x08

#घोषणा CGW_MOD_FUNCS 4 /* AND OR XOR SET */

/* CAN frame elements that are affected by curr. 3 CAN frame modअगरications */
#घोषणा CGW_MOD_ID	0x01
#घोषणा CGW_MOD_DLC	0x02		/* Classical CAN data length code */
#घोषणा CGW_MOD_LEN	CGW_MOD_DLC	/* CAN FD (plain) data length */
#घोषणा CGW_MOD_DATA	0x04
#घोषणा CGW_MOD_FLAGS	0x08		/* CAN FD flags */

#घोषणा CGW_FRAME_MODS 4 /* ID DLC/LEN DATA FLAGS */

#घोषणा MAX_MODFUNCTIONS (CGW_MOD_FUNCS * CGW_FRAME_MODS)

काष्ठा cgw_frame_mod अणु
	काष्ठा can_frame cf;
	__u8 modtype;
पूर्ण __attribute__((packed));

काष्ठा cgw_fdframe_mod अणु
	काष्ठा canfd_frame cf;
	__u8 modtype;
पूर्ण __attribute__((packed));

#घोषणा CGW_MODATTR_LEN माप(काष्ठा cgw_frame_mod)
#घोषणा CGW_FDMODATTR_LEN माप(काष्ठा cgw_fdframe_mod)

काष्ठा cgw_csum_xor अणु
	__s8 from_idx;
	__s8 to_idx;
	__s8 result_idx;
	__u8 init_xor_val;
पूर्ण __attribute__((packed));

काष्ठा cgw_csum_crc8 अणु
	__s8 from_idx;
	__s8 to_idx;
	__s8 result_idx;
	__u8 init_crc_val;
	__u8 final_xor_val;
	__u8 crctab[256];
	__u8 profile;
	__u8 profile_data[20];
पूर्ण __attribute__((packed));

/* length of checksum operation parameters. idx = index in CAN frame data[] */
#घोषणा CGW_CS_XOR_LEN  माप(काष्ठा cgw_csum_xor)
#घोषणा CGW_CS_CRC8_LEN  माप(काष्ठा cgw_csum_crc8)

/* CRC8 profiles (compute CRC क्रम additional data elements - see below) */
क्रमागत अणु
	CGW_CRC8PRF_UNSPEC,
	CGW_CRC8PRF_1U8,	/* compute one additional u8 value */
	CGW_CRC8PRF_16U8,	/* u8 value table indexed by data[1] & 0xF */
	CGW_CRC8PRF_SFFID_XOR,	/* (can_id & 0xFF) ^ (can_id >> 8 & 0xFF) */
	__CGW_CRC8PRF_MAX
पूर्ण;

#घोषणा CGW_CRC8PRF_MAX (__CGW_CRC8PRF_MAX - 1)

/*
 * CAN rtnetlink attribute contents in detail
 *
 * CGW_XXX_IF (length 4 bytes):
 * Sets an पूर्णांकerface index क्रम source/destination network पूर्णांकerfaces.
 * For the CAN->CAN gwtype the indices of _two_ CAN पूर्णांकerfaces are mandatory.
 *
 * CGW_FILTER (length 8 bytes):
 * Sets a CAN receive filter क्रम the gateway job specअगरied by the
 * काष्ठा can_filter described in include/linux/can.h
 *
 * CGW_MOD_(AND|OR|XOR|SET) (length 17 bytes):
 * Specअगरies a modअगरication that's करोne to a received CAN frame beक्रमe it is
 * send out to the destination पूर्णांकerface.
 *
 * <काष्ठा can_frame> data used as चालक
 * <u8> affected CAN frame elements
 *
 * CGW_LIM_HOPS (length 1 byte):
 * Limit the number of hops of this specअगरic rule. Usually the received CAN
 * frame can be processed as much as 'max_hops' बार (which is given at module
 * load समय of the can-gw module). This value is used to reduce the number of
 * possible hops क्रम this gateway rule to a value smaller then max_hops.
 *
 * CGW_MOD_UID (length 4 bytes):
 * Optional non-zero user defined routing job identअगरier to alter existing
 * modअगरication settings at runसमय.
 *
 * CGW_CS_XOR (length 4 bytes):
 * Set a simple XOR checksum starting with an initial value पूर्णांकo
 * data[result-idx] using data[start-idx] .. data[end-idx]
 *
 * The XOR checksum is calculated like this:
 *
 * xor = init_xor_val
 *
 * क्रम (i = from_idx .. to_idx)
 *      xor ^= can_frame.data[i]
 *
 * can_frame.data[ result_idx ] = xor
 *
 * CGW_CS_CRC8 (length 282 bytes):
 * Set a CRC8 value पूर्णांकo data[result-idx] using a given 256 byte CRC8 table,
 * a given initial value and a defined input data[start-idx] .. data[end-idx].
 * Finally the result value is XOR'ed with the final_xor_val.
 *
 * The CRC8 checksum is calculated like this:
 *
 * crc = init_crc_val
 *
 * क्रम (i = from_idx .. to_idx)
 *      crc = crctab[ crc ^ can_frame.data[i] ]
 *
 * can_frame.data[ result_idx ] = crc ^ final_xor_val
 *
 * The calculated CRC may contain additional source data elements that can be
 * defined in the handling of 'checksum profiles' e.g. shown in AUTOSAR specs
 * like http://www.स्वतःsar.org/करोwnload/R4.0/AUTOSAR_SWS_E2ELibrary.pdf
 * E.g. the profile_data[] may contain additional u8 values (called DATA_IDs)
 * that are used depending on counter values inside the CAN frame data[].
 * So far only three profiles have been implemented क्रम illustration.
 *
 * Remark: In general the attribute data is a linear buffer.
 *         Beware of sending unpacked or aligned काष्ठाs!
 */

#पूर्ण_अगर /* !_UAPI_CAN_GW_H */
