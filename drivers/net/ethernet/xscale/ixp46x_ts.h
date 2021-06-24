<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PTP 1588 घड़ी using the IXP46X
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */

#अगर_अघोषित _IXP46X_TS_H_
#घोषणा _IXP46X_TS_H_

#घोषणा DEFAULT_ADDEND 0xF0000029
#घोषणा TICKS_NS_SHIFT 4

काष्ठा ixp46x_channel_ctl अणु
	u32 ch_control;  /* 0x40 Time Synchronization Channel Control */
	u32 ch_event;    /* 0x44 Time Synchronization Channel Event */
	u32 tx_snap_lo;  /* 0x48 Transmit Snapshot Low Register */
	u32 tx_snap_hi;  /* 0x4C Transmit Snapshot High Register */
	u32 rx_snap_lo;  /* 0x50 Receive Snapshot Low Register */
	u32 rx_snap_hi;  /* 0x54 Receive Snapshot High Register */
	u32 src_uuid_lo; /* 0x58 Source UUID0 Low Register */
	u32 src_uuid_hi; /* 0x5C Sequence Identअगरier/Source UUID0 High */
पूर्ण;

काष्ठा ixp46x_ts_regs अणु
	u32 control;     /* 0x00 Time Sync Control Register */
	u32 event;       /* 0x04 Time Sync Event Register */
	u32 addend;      /* 0x08 Time Sync Addend Register */
	u32 accum;       /* 0x0C Time Sync Accumulator Register */
	u32 test;        /* 0x10 Time Sync Test Register */
	u32 unused;      /* 0x14 */
	u32 rsysसमय_lo; /* 0x18 RawSystemTime_Low Register */
	u32 rsysसमय_hi; /* 0x1C RawSystemTime_High Register */
	u32 sysसमय_lo;  /* 0x20 SystemTime_Low Register */
	u32 sysसमय_hi;  /* 0x24 SystemTime_High Register */
	u32 trgt_lo;     /* 0x28 TargetTime_Low Register */
	u32 trgt_hi;     /* 0x2C TargetTime_High Register */
	u32 यंत्रs_lo;     /* 0x30 Auxiliary Slave Mode Snapshot Low  */
	u32 यंत्रs_hi;     /* 0x34 Auxiliary Slave Mode Snapshot High */
	u32 amms_lo;     /* 0x38 Auxiliary Master Mode Snapshot Low */
	u32 amms_hi;     /* 0x3C Auxiliary Master Mode Snapshot High */

	काष्ठा ixp46x_channel_ctl channel[3];
पूर्ण;

/* 0x00 Time Sync Control Register Bits */
#घोषणा TSCR_AMM (1<<3)
#घोषणा TSCR_ASM (1<<2)
#घोषणा TSCR_TTM (1<<1)
#घोषणा TSCR_RST (1<<0)

/* 0x04 Time Sync Event Register Bits */
#घोषणा TSER_SNM (1<<3)
#घोषणा TSER_SNS (1<<2)
#घोषणा TTIPEND  (1<<1)

/* 0x40 Time Synchronization Channel Control Register Bits */
#घोषणा MASTER_MODE   (1<<0)
#घोषणा TIMESTAMP_ALL (1<<1)

/* 0x44 Time Synchronization Channel Event Register Bits */
#घोषणा TX_SNAPSHOT_LOCKED (1<<0)
#घोषणा RX_SNAPSHOT_LOCKED (1<<1)

/* The ptp_ixp46x module will set this variable */
बाह्य पूर्णांक ixp46x_phc_index;

#पूर्ण_अगर
