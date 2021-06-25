<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL871X_IO_H_
#घोषणा _RTL871X_IO_H_

#समावेश "osdep_service.h"
#समावेश "osdep_intf.h"

#घोषणा NUM_IOREQ		8

#घोषणा MAX_PROT_SZ	(64-16)

#घोषणा _IOREADY			0
#घोषणा _IO_WAIT_COMPLETE   1
#घोषणा _IO_WAIT_RSP        2

/* IO COMMAND TYPE */
#घोषणा _IOSZ_MASK_		(0x7F)
#घोषणा _IO_WRITE_		BIT(7)
#घोषणा _IO_FIXED_		BIT(8)
#घोषणा _IO_BURST_		BIT(9)
#घोषणा _IO_BYTE_		BIT(10)
#घोषणा _IO_HW_			BIT(11)
#घोषणा _IO_WORD_		BIT(12)
#घोषणा _IO_SYNC_		BIT(13)
#घोषणा _IO_CMDMASK_	(0x1F80)

/*
 *	For prompt mode accessing, caller shall मुक्त io_req
 *	Otherwise, io_handler will मुक्त io_req
 */
/* IO STATUS TYPE */
#घोषणा _IO_ERR_		BIT(2)
#घोषणा _IO_SUCCESS_	BIT(1)
#घोषणा _IO_DONE_		BIT(0)
#घोषणा IO_RD32			(_IO_SYNC_ | _IO_WORD_)
#घोषणा IO_RD16			(_IO_SYNC_ | _IO_HW_)
#घोषणा IO_RD8			(_IO_SYNC_ | _IO_BYTE_)
#घोषणा IO_RD32_ASYNC	(_IO_WORD_)
#घोषणा IO_RD16_ASYNC	(_IO_HW_)
#घोषणा IO_RD8_ASYNC	(_IO_BYTE_)
#घोषणा IO_WR32			(_IO_WRITE_ | _IO_SYNC_ | _IO_WORD_)
#घोषणा IO_WR16			(_IO_WRITE_ | _IO_SYNC_ | _IO_HW_)
#घोषणा IO_WR8			(_IO_WRITE_ | _IO_SYNC_ | _IO_BYTE_)
#घोषणा IO_WR32_ASYNC	(_IO_WRITE_ | _IO_WORD_)
#घोषणा IO_WR16_ASYNC	(_IO_WRITE_ | _IO_HW_)
#घोषणा IO_WR8_ASYNC	(_IO_WRITE_ | _IO_BYTE_)
/*
 *	Only Sync. burst accessing is provided.
 */
#घोषणा IO_WR_BURST(x)		(IO_WRITE_ | _IO_SYNC_ | _IO_BURST_ | \
				((x) & _IOSZ_MASK_))
#घोषणा IO_RD_BURST(x)		(_IO_SYNC_ | _IO_BURST_ | ((x) & _IOSZ_MASK_))
/*below is क्रम the पूर्णांकf_option bit defition...*/
#घोषणा _INTF_ASYNC_	BIT(0)	/*support async io*/
काष्ठा पूर्णांकf_priv;
काष्ठा	पूर्णांकf_hdl;
काष्ठा io_queue;
काष्ठा	_io_ops अणु
	uपूर्णांक (*_sdbus_पढ़ो_bytes_to_membuf)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv,
					    u32 addr, u32 cnt, u8 *pbuf);
	uपूर्णांक (*_sdbus_पढ़ो_blocks_to_membuf)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv,
					     u32 addr, u32 cnt, u8 *pbuf);
	u8 (*_पढ़ो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
	u16 (*_पढ़ो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
	u32 (*_पढ़ो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
	uपूर्णांक (*_sdbus_ग_लिखो_blocks_from_membuf)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv,
						u32 addr, u32 cnt, u8 *pbuf,
						u8 async);
	uपूर्णांक (*_sdbus_ग_लिखो_bytes_from_membuf)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv,
					       u32 addr, u32 cnt, u8 *pbuf);
	u8 (*_cmd52r)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u32 addr);
	व्योम (*_cmd52w)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u32 addr, u8 val8);
	u8 (*_cmdfunc152r)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u32 addr);
	व्योम (*_cmdfunc152w)(काष्ठा पूर्णांकf_priv *pपूर्णांकfpriv, u32 addr, u8 val8);
	व्योम (*_ग_लिखो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 val);
	व्योम (*_ग_लिखो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u16 val);
	व्योम (*_ग_लिखो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 val);
	व्योम (*_पढ़ो_mem)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt,
			  u8 *pmem);
	व्योम (*_ग_लिखो_mem)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt,
			   u8 *pmem);
	व्योम (*_sync_irp_protocol_rw)(काष्ठा io_queue *pio_q);
	u32 (*_पढ़ो_port)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt,
			  u8 *pmem);
	u32 (*_ग_लिखो_port)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt,
			   u8 *pmem);
पूर्ण;

काष्ठा io_req अणु
	काष्ठा list_head list;
	u32	addr;
	/*अस्थिर*/ u32	val;
	u32	command;
	u32	status;
	u8	*pbuf;
	व्योम (*_async_io_callback)(काष्ठा _adapter *padapter,
				   काष्ठा io_req *pio_req, u8 *cnxt);
	u8 *cnxt;
पूर्ण;

काष्ठा	पूर्णांकf_hdl अणु
	u32	पूर्णांकf_option;
	u8	*adapter;
	u8	*पूर्णांकf_dev;
	काष्ठा पूर्णांकf_priv	*pपूर्णांकfpriv;
	व्योम (*पूर्णांकf_hdl_init)(u8 *priv);
	व्योम (*पूर्णांकf_hdl_unload)(u8 *priv);
	व्योम (*पूर्णांकf_hdl_खोलो)(u8 *priv);
	व्योम (*पूर्णांकf_hdl_बंद)(u8 *priv);
	काष्ठा	_io_ops	io_ops;
पूर्ण;

काष्ठा reg_protocol_rd अणु
#अगर_घोषित __LITTLE_ENDIAN
	/* DW1 */
	u32		NumOfTrans:4;
	u32		Reserved1:4;
	u32		Reserved2:24;
	/* DW2 */
	u32		ByteCount:7;
	u32		WriteEnable:1;		/*0:पढ़ो, 1:ग_लिखो*/
	u32		FixOrContinuous:1;	/*0:continuous, 1: Fix*/
	u32		BurstMode:1;
	u32		Byte1Access:1;
	u32		Byte2Access:1;
	u32		Byte4Access:1;
	u32		Reserved3:3;
	u32		Reserved4:16;
	/*DW3*/
	u32		BusAddress;
	/*DW4*/
#अन्यथा
/*DW1*/
	u32 Reserved1:4;
	u32 NumOfTrans:4;
	u32 Reserved2:24;
	/*DW2*/
	u32 WriteEnable:1;
	u32 ByteCount:7;
	u32 Reserved3:3;
	u32 Byte4Access:1;
	u32 Byte2Access:1;
	u32 Byte1Access:1;
	u32 BurstMode:1;
	u32 FixOrContinuous:1;
	u32 Reserved4:16;
	/*DW3*/
	u32 BusAddress;
	/*DW4*/
#पूर्ण_अगर
पूर्ण;

काष्ठा reg_protocol_wt अणु
#अगर_घोषित __LITTLE_ENDIAN
	/*DW1*/
	u32 NumOfTrans:4;
	u32 Reserved1:4;
	u32 Reserved2:24;
	/*DW2*/
	u32 ByteCount:7;
	u32 WriteEnable:1;	/*0:पढ़ो, 1:ग_लिखो*/
	u32 FixOrContinuous:1;	/*0:continuous, 1: Fix*/
	u32 BurstMode:1;
	u32 Byte1Access:1;
	u32 Byte2Access:1;
	u32 Byte4Access:1;
	u32 Reserved3:3;
	u32 Reserved4:16;
	/*DW3*/
	u32 BusAddress;
	/*DW4*/
	u32 Value;
#अन्यथा
	/*DW1*/
	u32 Reserved1:4;
	u32 NumOfTrans:4;
	u32 Reserved2:24;
	/*DW2*/
	u32 WriteEnable:1;
	u32 ByteCount:7;
	u32 Reserved3:3;
	u32 Byte4Access:1;
	u32 Byte2Access:1;
	u32 Byte1Access:1;
	u32 BurstMode:1;
	u32 FixOrContinuous:1;
	u32 Reserved4:16;
	/*DW3*/
	u32 BusAddress;
	/*DW4*/
	u32 Value;
#पूर्ण_अगर
पूर्ण;

/*
 * Below is the data काष्ठाure used by _io_handler
 */

काष्ठा io_queue अणु
	spinlock_t lock;
	काष्ठा list_head मुक्त_ioreqs;
	/*The io_req list that will be served in the single protocol r/w.*/
	काष्ठा list_head pending;
	काष्ठा list_head processing;
	u8 *मुक्त_ioreqs_buf; /* 4-byte aligned */
	u8 *pallocated_मुक्त_ioreqs_buf;
	काष्ठा	पूर्णांकf_hdl पूर्णांकf;
पूर्ण;

u8 r8712_पढ़ो8(काष्ठा _adapter *adapter, u32 addr);
u16 r8712_पढ़ो16(काष्ठा _adapter *adapter, u32 addr);
u32 r8712_पढ़ो32(काष्ठा _adapter *adapter, u32 addr);
व्योम r8712_पढ़ो_mem(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
व्योम r8712_पढ़ो_port(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
व्योम r8712_ग_लिखो8(काष्ठा _adapter *adapter, u32 addr, u8 val);
व्योम r8712_ग_लिखो16(काष्ठा _adapter *adapter, u32 addr, u16 val);
व्योम r8712_ग_लिखो32(काष्ठा _adapter *adapter, u32 addr, u32 val);
व्योम r8712_ग_लिखो_mem(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
व्योम r8712_ग_लिखो_port(काष्ठा _adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
/*ioreq */
uपूर्णांक r8712_alloc_io_queue(काष्ठा _adapter *adapter);
व्योम r8712_मुक्त_io_queue(काष्ठा _adapter *adapter);

#पूर्ण_अगर	/*_RTL871X_IO_H_*/
