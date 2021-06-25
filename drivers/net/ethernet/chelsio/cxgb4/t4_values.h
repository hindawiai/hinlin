<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __T4_VALUES_H__
#घोषणा __T4_VALUES_H__

/* This file contains definitions क्रम various T4 रेजिस्टर value hardware
 * स्थिरants.  The types of values encoded here are preकरोminantly those क्रम
 * रेजिस्टर fields which control "modal" behavior.  For the most part, we करो
 * not include definitions क्रम रेजिस्टर fields which are simple numeric
 * metrics, etc.
 */

/* SGE रेजिस्टर field values.
 */

/* CONTROL1 रेजिस्टर */
#घोषणा RXPKTCPLMODE_SPLIT_X		1

#घोषणा INGPCIEBOUNDARY_SHIFT_X		5
#घोषणा INGPCIEBOUNDARY_32B_X		0

#घोषणा INGPADBOUNDARY_SHIFT_X		5

#घोषणा T6_INGPADBOUNDARY_SHIFT_X	3
#घोषणा T6_INGPADBOUNDARY_8B_X		0
#घोषणा T6_INGPADBOUNDARY_32B_X		2

#घोषणा INGPADBOUNDARY_32B_X		0

/* CONTROL2 रेजिस्टर */
#घोषणा INGPACKBOUNDARY_SHIFT_X		5
#घोषणा INGPACKBOUNDARY_16B_X		0
#घोषणा INGPACKBOUNDARY_64B_X		1

/* GTS रेजिस्टर */
#घोषणा SGE_TIMERREGS			6
#घोषणा TIMERREG_COUNTER0_X		0

#घोषणा FETCHBURSTMIN_64B_X		2
#घोषणा FETCHBURSTMIN_128B_X		3

/* T6 and later use a single-bit encoding क्रम FetchBurstMin */
#घोषणा FETCHBURSTMIN_64B_T6_X		0
#घोषणा FETCHBURSTMIN_128B_T6_X		1

#घोषणा FETCHBURSTMAX_256B_X		2
#घोषणा FETCHBURSTMAX_512B_X		3

#घोषणा HOSTFCMODE_INGRESS_QUEUE_X	1
#घोषणा HOSTFCMODE_STATUS_PAGE_X	2

#घोषणा CIDXFLUSHTHRESH_32_X		5
#घोषणा CIDXFLUSHTHRESH_128_X		7

#घोषणा UPDATEDELIVERY_INTERRUPT_X	1

#घोषणा RSPD_TYPE_FLBUF_X		0
#घोषणा RSPD_TYPE_CPL_X			1
#घोषणा RSPD_TYPE_INTR_X		2

/* Congestion Manager Definitions.
 */
#घोषणा CONMCTXT_CNGTPMODE_S		19
#घोषणा CONMCTXT_CNGTPMODE_V(x)		((x) << CONMCTXT_CNGTPMODE_S)
#घोषणा CONMCTXT_CNGCHMAP_S		0
#घोषणा CONMCTXT_CNGCHMAP_V(x)		((x) << CONMCTXT_CNGCHMAP_S)
#घोषणा CONMCTXT_CNGTPMODE_CHANNEL_X	2
#घोषणा CONMCTXT_CNGTPMODE_QUEUE_X	1

/* T5 and later support a new BAR2-based करोorbell mechanism क्रम Egress Queues.
 * The User Doorbells are each 128 bytes in length with a Simple Doorbell at
 * offsets 8x and a Write Combining single 64-byte Egress Queue Unit
 * (IDXSIZE_UNIT_X) Gather Buffer पूर्णांकerface at offset 64.  For Ingress Queues,
 * we have a Going To Sleep रेजिस्टर at offsets 8x+4.
 *
 * As noted above, we have many instances of the Simple Doorbell and Going To
 * Sleep रेजिस्टरs at offsets 8x and 8x+4, respectively.  We want to use a
 * non-64-byte aligned offset क्रम the Simple Doorbell in order to attempt to
 * aव्योम buffering of the ग_लिखोs to the Simple Doorbell and we want to use a
 * non-contiguous offset क्रम the Going To Sleep ग_लिखोs in order to aव्योम
 * possible combining between them.
 */
#घोषणा SGE_UDB_SIZE		128
#घोषणा SGE_UDB_KDOORBELL	8
#घोषणा SGE_UDB_GTS		20
#घोषणा SGE_UDB_WCDOORBELL	64

/* CIM रेजिस्टर field values.
 */
#घोषणा X_MBOWNER_FW			1
#घोषणा X_MBOWNER_PL			2

/* PCI-E definitions */
#घोषणा WINDOW_SHIFT_X		10
#घोषणा PCIखातापूर्णST_SHIFT_X	10

/* TP_VLAN_PRI_MAP controls which subset of fields will be present in the
 * Compressed Filter Tuple क्रम LE filters.  Each bit set in TP_VLAN_PRI_MAP
 * selects क्रम a particular field being present.  These fields, when present
 * in the Compressed Filter Tuple, have the following widths in bits.
 */
#घोषणा FT_FCOE_W                       1
#घोषणा FT_PORT_W                       3
#घोषणा FT_VNIC_ID_W                    17
#घोषणा FT_VLAN_W                       17
#घोषणा FT_TOS_W                        8
#घोषणा FT_PROTOCOL_W                   8
#घोषणा FT_ETHERTYPE_W                  16
#घोषणा FT_MACMATCH_W                   9
#घोषणा FT_MPSHITTYPE_W                 3
#घोषणा FT_FRAGMENTATION_W              1

/* Some of the Compressed Filter Tuple fields have पूर्णांकernal काष्ठाure.  These
 * bit shअगरts/masks describe those काष्ठाures.  All shअगरts are relative to the
 * base position of the fields within the Compressed Filter Tuple
 */
#घोषणा FT_VLAN_VLD_S                   16
#घोषणा FT_VLAN_VLD_V(x)                ((x) << FT_VLAN_VLD_S)
#घोषणा FT_VLAN_VLD_F                   FT_VLAN_VLD_V(1U)

#घोषणा FT_VNID_ID_VF_S                 0
#घोषणा FT_VNID_ID_VF_V(x)              ((x) << FT_VNID_ID_VF_S)

#घोषणा FT_VNID_ID_PF_S                 7
#घोषणा FT_VNID_ID_PF_V(x)              ((x) << FT_VNID_ID_PF_S)

#घोषणा FT_VNID_ID_VLD_S                16
#घोषणा FT_VNID_ID_VLD_V(x)             ((x) << FT_VNID_ID_VLD_S)

#पूर्ण_अगर /* __T4_VALUES_H__ */
