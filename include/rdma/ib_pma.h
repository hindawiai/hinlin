<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010 QLogic Corporation.
 * All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
 */

#अगर_अघोषित IB_PMA_H
#घोषणा IB_PMA_H

#समावेश <rdma/ib_mad.h>

/*
 * PMA class portinfo capability mask bits
 */
#घोषणा IB_PMA_CLASS_CAP_ALLPORTSELECT  cpu_to_be16(1 << 8)
#घोषणा IB_PMA_CLASS_CAP_EXT_WIDTH      cpu_to_be16(1 << 9)
#घोषणा IB_PMA_CLASS_CAP_EXT_WIDTH_NOIETF cpu_to_be16(1 << 10)
#घोषणा IB_PMA_CLASS_CAP_XMIT_WAIT      cpu_to_be16(1 << 12)

#घोषणा IB_PMA_CLASS_PORT_INFO          cpu_to_be16(0x0001)
#घोषणा IB_PMA_PORT_SAMPLES_CONTROL     cpu_to_be16(0x0010)
#घोषणा IB_PMA_PORT_SAMPLES_RESULT      cpu_to_be16(0x0011)
#घोषणा IB_PMA_PORT_COUNTERS            cpu_to_be16(0x0012)
#घोषणा IB_PMA_PORT_COUNTERS_EXT        cpu_to_be16(0x001D)
#घोषणा IB_PMA_PORT_SAMPLES_RESULT_EXT  cpu_to_be16(0x001E)

काष्ठा ib_pma_mad अणु
	काष्ठा ib_mad_hdr mad_hdr;
	u8 reserved[40];
	u8 data[192];
पूर्ण __packed;

काष्ठा ib_pma_portsamplescontrol अणु
	u8 opcode;
	u8 port_select;
	u8 tick;
	u8 counter_width;		/* resv: 7:3, counter width: 2:0 */
	__be32 counter_mask0_9;		/* 2, 10 3-bit fields */
	__be16 counter_mask10_14;	/* 1, 5 3-bit fields */
	u8 sample_mechanisms;
	u8 sample_status;		/* only lower 2 bits */
	__be64 option_mask;
	__be64 venकरोr_mask;
	__be32 sample_start;
	__be32 sample_पूर्णांकerval;
	__be16 tag;
	__be16 counter_select[15];
	__be32 reserved1;
	__be64 samples_only_option_mask;
	__be32 reserved2[28];
पूर्ण;

काष्ठा ib_pma_portsamplesresult अणु
	__be16 tag;
	__be16 sample_status;   /* only lower 2 bits */
	__be32 counter[15];
पूर्ण;

काष्ठा ib_pma_portsamplesresult_ext अणु
	__be16 tag;
	__be16 sample_status;   /* only lower 2 bits */
	__be32 extended_width;  /* only upper 2 bits */
	__be64 counter[15];
पूर्ण;

काष्ठा ib_pma_portcounters अणु
	u8 reserved;
	u8 port_select;
	__be16 counter_select;
	__be16 symbol_error_counter;
	u8 link_error_recovery_counter;
	u8 link_करोwned_counter;
	__be16 port_rcv_errors;
	__be16 port_rcv_remphys_errors;
	__be16 port_rcv_चयन_relay_errors;
	__be16 port_xmit_discards;
	u8 port_xmit_स्थिरraपूर्णांक_errors;
	u8 port_rcv_स्थिरraपूर्णांक_errors;
	u8 reserved1;
	u8 link_overrun_errors; /* LocalLink: 7:4, BufferOverrun: 3:0 */
	__be16 reserved2;
	__be16 vl15_dropped;
	__be32 port_xmit_data;
	__be32 port_rcv_data;
	__be32 port_xmit_packets;
	__be32 port_rcv_packets;
	__be32 port_xmit_रुको;
पूर्ण __packed;


#घोषणा IB_PMA_SEL_SYMBOL_ERROR                 cpu_to_be16(0x0001)
#घोषणा IB_PMA_SEL_LINK_ERROR_RECOVERY          cpu_to_be16(0x0002)
#घोषणा IB_PMA_SEL_LINK_DOWNED                  cpu_to_be16(0x0004)
#घोषणा IB_PMA_SEL_PORT_RCV_ERRORS              cpu_to_be16(0x0008)
#घोषणा IB_PMA_SEL_PORT_RCV_REMPHYS_ERRORS      cpu_to_be16(0x0010)
#घोषणा IB_PMA_SEL_PORT_XMIT_DISCARDS           cpu_to_be16(0x0040)
#घोषणा IB_PMA_SEL_LOCAL_LINK_INTEGRITY_ERRORS  cpu_to_be16(0x0200)
#घोषणा IB_PMA_SEL_EXCESSIVE_BUFFER_OVERRUNS    cpu_to_be16(0x0400)
#घोषणा IB_PMA_SEL_PORT_VL15_DROPPED            cpu_to_be16(0x0800)
#घोषणा IB_PMA_SEL_PORT_XMIT_DATA               cpu_to_be16(0x1000)
#घोषणा IB_PMA_SEL_PORT_RCV_DATA                cpu_to_be16(0x2000)
#घोषणा IB_PMA_SEL_PORT_XMIT_PACKETS            cpu_to_be16(0x4000)
#घोषणा IB_PMA_SEL_PORT_RCV_PACKETS             cpu_to_be16(0x8000)

काष्ठा ib_pma_portcounters_ext अणु
	u8 reserved;
	u8 port_select;
	__be16 counter_select;
	__be32 reserved1;
	__be64 port_xmit_data;
	__be64 port_rcv_data;
	__be64 port_xmit_packets;
	__be64 port_rcv_packets;
	__be64 port_unicast_xmit_packets;
	__be64 port_unicast_rcv_packets;
	__be64 port_multicast_xmit_packets;
	__be64 port_multicast_rcv_packets;
पूर्ण __packed;

#घोषणा IB_PMA_SELX_PORT_XMIT_DATA              cpu_to_be16(0x0001)
#घोषणा IB_PMA_SELX_PORT_RCV_DATA               cpu_to_be16(0x0002)
#घोषणा IB_PMA_SELX_PORT_XMIT_PACKETS           cpu_to_be16(0x0004)
#घोषणा IB_PMA_SELX_PORT_RCV_PACKETS            cpu_to_be16(0x0008)
#घोषणा IB_PMA_SELX_PORT_UNI_XMIT_PACKETS       cpu_to_be16(0x0010)
#घोषणा IB_PMA_SELX_PORT_UNI_RCV_PACKETS        cpu_to_be16(0x0020)
#घोषणा IB_PMA_SELX_PORT_MULTI_XMIT_PACKETS     cpu_to_be16(0x0040)
#घोषणा IB_PMA_SELX_PORT_MULTI_RCV_PACKETS      cpu_to_be16(0x0080)

#पूर्ण_अगर /* IB_PMA_H */
