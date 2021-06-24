<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_TXHEADER_H
#घोषणा _MLXSW_TXHEADER_H

#घोषणा MLXSW_TXHDR_LEN 0x10
#घोषणा MLXSW_TXHDR_VERSION_0 0
#घोषणा MLXSW_TXHDR_VERSION_1 1

क्रमागत अणु
	MLXSW_TXHDR_ETH_CTL,
	MLXSW_TXHDR_ETH_DATA,
पूर्ण;

#घोषणा MLXSW_TXHDR_PROTO_ETH 1

क्रमागत अणु
	MLXSW_TXHDR_ETCLASS_0,
	MLXSW_TXHDR_ETCLASS_1,
	MLXSW_TXHDR_ETCLASS_2,
	MLXSW_TXHDR_ETCLASS_3,
	MLXSW_TXHDR_ETCLASS_4,
	MLXSW_TXHDR_ETCLASS_5,
	MLXSW_TXHDR_ETCLASS_6,
	MLXSW_TXHDR_ETCLASS_7,
पूर्ण;

क्रमागत अणु
	MLXSW_TXHDR_RDQ_OTHER,
	MLXSW_TXHDR_RDQ_EMAD = 0x1f,
पूर्ण;

#घोषणा MLXSW_TXHDR_CTCLASS3 0
#घोषणा MLXSW_TXHDR_CPU_SIG 0
#घोषणा MLXSW_TXHDR_SIG 0xE0E0
#घोषणा MLXSW_TXHDR_STCLASS_NONE 0

क्रमागत अणु
	MLXSW_TXHDR_NOT_EMAD,
	MLXSW_TXHDR_EMAD,
पूर्ण;

क्रमागत अणु
	MLXSW_TXHDR_TYPE_DATA,
	MLXSW_TXHDR_TYPE_CONTROL = 6,
पूर्ण;

#पूर्ण_अगर
