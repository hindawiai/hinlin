<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित _RTW_IO_H_
#घोषणा _RTW_IO_H_

#घोषणा NUM_IOREQ		8

#घोषणा MAX_PROT_SZ	(64-16)

#घोषणा _IOREADY			0
#घोषणा _IO_WAIT_COMPLETE   1
#घोषणा _IO_WAIT_RSP        2

/*  IO COMMAND TYPE */
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
	For prompt mode accessing, caller shall मुक्त io_req
	Otherwise, io_handler will मुक्त io_req
*/



/*  IO STATUS TYPE */
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

	Only Sync. burst accessing is provided.

*/

#घोषणा IO_WR_BURST(x)		(_IO_WRITE_ | _IO_SYNC_ | _IO_BURST_ | ((x) & _IOSZ_MASK_))
#घोषणा IO_RD_BURST(x)		(_IO_SYNC_ | _IO_BURST_ | ((x) & _IOSZ_MASK_))



/* below is क्रम the पूर्णांकf_option bit defition... */

#घोषणा _INTF_ASYNC_	BIT(0)	/* support async io */

काष्ठा पूर्णांकf_priv;
काष्ठा पूर्णांकf_hdl;
काष्ठा io_queue;

काष्ठा _io_ops अणु
		u8 (*_पढ़ो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
		u16 (*_पढ़ो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
		u32 (*_पढ़ो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

		पूर्णांक (*_ग_लिखो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 val);
		पूर्णांक (*_ग_लिखो16)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u16 val);
		पूर्णांक (*_ग_लिखो32)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 val);
		पूर्णांक (*_ग_लिखोN)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 length, u8 *pdata);

		पूर्णांक (*_ग_लिखो8_async)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u8 val);
		पूर्णांक (*_ग_लिखो16_async)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u16 val);
		पूर्णांक (*_ग_लिखो32_async)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 val);

		व्योम (*_पढ़ो_mem)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pmem);
		व्योम (*_ग_लिखो_mem)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pmem);

		व्योम (*_sync_irp_protocol_rw)(काष्ठा io_queue *pio_q);

		u32 (*_पढ़ो_पूर्णांकerrupt)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);

		u32 (*_पढ़ो_port)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pmem);
		u32 (*_ग_लिखो_port)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr, u32 cnt, u8 *pmem);

		u32 (*_ग_लिखो_scsi)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 cnt, u8 *pmem);

		व्योम (*_पढ़ो_port_cancel)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl);
		व्योम (*_ग_लिखो_port_cancel)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl);

		u8 (*_sd_f0_पढ़ो8)(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl, u32 addr);
पूर्ण;

काष्ठा io_req अणु
	काष्ठा list_head	list;
	u32 addr;
	अस्थिर u32 val;
	u32 command;
	u32 status;
	u8 *pbuf;

	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt);
	u8 *cnxt;
पूर्ण;

काष्ठा	पूर्णांकf_hdl अणु
	काष्ठा adapter *padapter;
	काष्ठा dvobj_priv *pपूर्णांकf_dev;/* 	poपूर्णांकer to &(padapter->dvobjpriv); */

	काष्ठा _io_ops	io_ops;
पूर्ण;

#घोषणा SD_IO_TRY_CNT (8)
#घोषणा MAX_CONTINUAL_IO_ERR SD_IO_TRY_CNT

पूर्णांक rtw_inc_and_chk_continual_io_error(काष्ठा dvobj_priv *dvobj);
व्योम rtw_reset_continual_io_error(काष्ठा dvobj_priv *dvobj);

/*
Below is the data काष्ठाure used by _io_handler

*/

काष्ठा io_queue अणु
	spinlock_t	lock;
	काष्ठा list_head	मुक्त_ioreqs;
	काष्ठा list_head		pending;		/* The io_req list that will be served in the single protocol पढ़ो/ग_लिखो. */
	काष्ठा list_head		processing;
	u8 *मुक्त_ioreqs_buf; /*  4-byte aligned */
	u8 *pallocated_मुक्त_ioreqs_buf;
	काष्ठा	पूर्णांकf_hdl	पूर्णांकf;
पूर्ण;

काष्ठा io_priv अणु

	काष्ठा adapter *padapter;

	काष्ठा पूर्णांकf_hdl पूर्णांकf;

पूर्ण;

बाह्य uपूर्णांक ioreq_flush(काष्ठा adapter *adapter, काष्ठा io_queue *ioqueue);
बाह्य व्योम sync_ioreq_enqueue(काष्ठा io_req *preq, काष्ठा io_queue *ioqueue);
बाह्य uपूर्णांक sync_ioreq_flush(काष्ठा adapter *adapter, काष्ठा io_queue *ioqueue);


बाह्य uपूर्णांक मुक्त_ioreq(काष्ठा io_req *preq, काष्ठा io_queue *pio_queue);
बाह्य काष्ठा io_req *alloc_ioreq(काष्ठा io_queue *pio_q);

बाह्य uपूर्णांक रेजिस्टर_पूर्णांकf_hdl(u8 *dev, काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl);
बाह्य व्योम unरेजिस्टर_पूर्णांकf_hdl(काष्ठा पूर्णांकf_hdl *pपूर्णांकfhdl);

बाह्य व्योम _rtw_attrib_पढ़ो(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
बाह्य व्योम _rtw_attrib_ग_लिखो(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);

बाह्य u8 _rtw_पढ़ो8(काष्ठा adapter *adapter, u32 addr);
बाह्य u16 _rtw_पढ़ो16(काष्ठा adapter *adapter, u32 addr);
बाह्य u32 _rtw_पढ़ो32(काष्ठा adapter *adapter, u32 addr);

बाह्य पूर्णांक _rtw_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val);
बाह्य पूर्णांक _rtw_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val);
बाह्य पूर्णांक _rtw_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val);

बाह्य u8 _rtw_sd_f0_पढ़ो8(काष्ठा adapter *adapter, u32 addr);

बाह्य u32 _rtw_ग_लिखो_port(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);

#घोषणा rtw_पढ़ो8(adapter, addr) _rtw_पढ़ो8((adapter), (addr))
#घोषणा rtw_पढ़ो16(adapter, addr) _rtw_पढ़ो16((adapter), (addr))
#घोषणा rtw_पढ़ो32(adapter, addr) _rtw_पढ़ो32((adapter), (addr))

#घोषणा  rtw_ग_लिखो8(adapter, addr, val) _rtw_ग_लिखो8((adapter), (addr), (val))
#घोषणा  rtw_ग_लिखो16(adapter, addr, val) _rtw_ग_लिखो16((adapter), (addr), (val))
#घोषणा  rtw_ग_लिखो32(adapter, addr, val) _rtw_ग_लिखो32((adapter), (addr), (val))

#घोषणा rtw_ग_लिखो_port(adapter, addr, cnt, mem) _rtw_ग_लिखो_port((adapter), (addr), (cnt), (mem))

#घोषणा rtw_sd_f0_पढ़ो8(adapter, addr) _rtw_sd_f0_पढ़ो8((adapter), (addr))

बाह्य व्योम rtw_ग_लिखो_scsi(काष्ठा adapter *adapter, u32 cnt, u8 *pmem);

/* ioreq */
बाह्य व्योम ioreq_पढ़ो8(काष्ठा adapter *adapter, u32 addr, u8 *pval);
बाह्य व्योम ioreq_पढ़ो16(काष्ठा adapter *adapter, u32 addr, u16 *pval);
बाह्य व्योम ioreq_पढ़ो32(काष्ठा adapter *adapter, u32 addr, u32 *pval);
बाह्य व्योम ioreq_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val);
बाह्य व्योम ioreq_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val);
बाह्य व्योम ioreq_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val);


बाह्य uपूर्णांक async_पढ़ो8(काष्ठा adapter *adapter, u32 addr, u8 *pbuff,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);
बाह्य uपूर्णांक async_पढ़ो16(काष्ठा adapter *adapter, u32 addr,  u8 *pbuff,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);
बाह्य uपूर्णांक async_पढ़ो32(काष्ठा adapter *adapter, u32 addr,  u8 *pbuff,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);

बाह्य व्योम async_पढ़ो_mem(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
बाह्य व्योम async_पढ़ो_port(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);

बाह्य व्योम async_ग_लिखो8(काष्ठा adapter *adapter, u32 addr, u8 val,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);
बाह्य व्योम async_ग_लिखो16(काष्ठा adapter *adapter, u32 addr, u16 val,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);
बाह्य व्योम async_ग_लिखो32(काष्ठा adapter *adapter, u32 addr, u32 val,
	व्योम (*_async_io_callback)(काष्ठा adapter *padater, काष्ठा io_req *pio_req, u8 *cnxt), u8 *cnxt);

बाह्य व्योम async_ग_लिखो_mem(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);
बाह्य व्योम async_ग_लिखो_port(काष्ठा adapter *adapter, u32 addr, u32 cnt, u8 *pmem);


पूर्णांक rtw_init_io_priv(काष्ठा adapter *padapter, व्योम (*set_पूर्णांकf_ops)(काष्ठा adapter *padapter, काष्ठा _io_ops *pops));


बाह्य uपूर्णांक alloc_io_queue(काष्ठा adapter *adapter);
बाह्य व्योम मुक्त_io_queue(काष्ठा adapter *adapter);
बाह्य व्योम async_bus_io(काष्ठा io_queue *pio_q);
बाह्य व्योम bus_sync_io(काष्ठा io_queue *pio_q);
बाह्य u32 _ioreq2rwmem(काष्ठा io_queue *pio_q);
बाह्य व्योम dev_घातer_करोwn(काष्ठा adapter *Adapter, u8 bpwrup);

#घोषणा Platक्रमmEFIOWrite1Byte(_a, _b, _c)		\
	rtw_ग_लिखो8(_a, _b, _c)
#घोषणा Platक्रमmEFIOWrite2Byte(_a, _b, _c)		\
	rtw_ग_लिखो16(_a, _b, _c)
#घोषणा Platक्रमmEFIOWrite4Byte(_a, _b, _c)		\
	rtw_ग_लिखो32(_a, _b, _c)

#घोषणा Platक्रमmEFIORead1Byte(_a, _b)		\
		rtw_पढ़ो8(_a, _b)
#घोषणा Platक्रमmEFIORead2Byte(_a, _b)		\
		rtw_पढ़ो16(_a, _b)
#घोषणा Platक्रमmEFIORead4Byte(_a, _b)		\
		rtw_पढ़ो32(_a, _b)

#पूर्ण_अगर	/* _RTL8711_IO_H_ */
