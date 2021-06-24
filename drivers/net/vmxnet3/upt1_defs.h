<शैली गुरु>
/*
 * Linux driver क्रम VMware's vmxnet3 ethernet NIC.
 *
 * Copyright (C) 2008-2020, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Maपूर्णांकained by: pv-drivers@vmware.com
 *
 */

#अगर_अघोषित _UPT1_DEFS_H
#घोषणा _UPT1_DEFS_H

काष्ठा UPT1_TxStats अणु
	u64			TSOPktsTxOK;  /* TSO pkts post-segmentation */
	u64			TSOBytesTxOK;
	u64			ucastPktsTxOK;
	u64			ucastBytesTxOK;
	u64			mcastPktsTxOK;
	u64			mcastBytesTxOK;
	u64			bcastPktsTxOK;
	u64			bcastBytesTxOK;
	u64			pktsTxError;
	u64			pktsTxDiscard;
पूर्ण;

काष्ठा UPT1_RxStats अणु
	u64			LROPktsRxOK;    /* LRO pkts */
	u64			LROBytesRxOK;   /* bytes from LRO pkts */
	/* the following counters are क्रम pkts from the wire, i.e., pre-LRO */
	u64			ucastPktsRxOK;
	u64			ucastBytesRxOK;
	u64			mcastPktsRxOK;
	u64			mcastBytesRxOK;
	u64			bcastPktsRxOK;
	u64			bcastBytesRxOK;
	u64			pktsRxOutOfBuf;
	u64			pktsRxError;
पूर्ण;

/* पूर्णांकerrupt moderation level */
क्रमागत अणु
	UPT1_IML_NONE		= 0, /* no पूर्णांकerrupt moderation */
	UPT1_IML_HIGHEST	= 7, /* least पूर्णांकr generated */
	UPT1_IML_ADAPTIVE	= 8, /* adpative पूर्णांकr moderation */
पूर्ण;
/* values क्रम UPT1_RSSConf.hashFunc */
क्रमागत अणु
	UPT1_RSS_HASH_TYPE_NONE      = 0x0,
	UPT1_RSS_HASH_TYPE_IPV4      = 0x01,
	UPT1_RSS_HASH_TYPE_TCP_IPV4  = 0x02,
	UPT1_RSS_HASH_TYPE_IPV6      = 0x04,
	UPT1_RSS_HASH_TYPE_TCP_IPV6  = 0x08,
पूर्ण;

क्रमागत अणु
	UPT1_RSS_HASH_FUNC_NONE      = 0x0,
	UPT1_RSS_HASH_FUNC_TOEPLITZ  = 0x01,
पूर्ण;

#घोषणा UPT1_RSS_MAX_KEY_SIZE        40
#घोषणा UPT1_RSS_MAX_IND_TABLE_SIZE  128

काष्ठा UPT1_RSSConf अणु
	u16			hashType;
	u16			hashFunc;
	u16			hashKeySize;
	u16			indTableSize;
	u8			hashKey[UPT1_RSS_MAX_KEY_SIZE];
	u8			indTable[UPT1_RSS_MAX_IND_TABLE_SIZE];
पूर्ण;

/* features */
क्रमागत अणु
	UPT1_F_RXCSUM		= cpu_to_le64(0x0001),   /* rx csum verअगरication */
	UPT1_F_RSS		= cpu_to_le64(0x0002),
	UPT1_F_RXVLAN		= cpu_to_le64(0x0004),   /* VLAN tag stripping */
	UPT1_F_LRO		= cpu_to_le64(0x0008),
	UPT1_F_RXINNEROFLD      = cpu_to_le64(0x00010),  /* Geneve/Vxlan rx csum
							  * offloading
							  */
पूर्ण;
#पूर्ण_अगर
