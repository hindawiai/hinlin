<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_IOCTL_H_
#घोषणा _RTW_IOCTL_H_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>

#अगर_अघोषित OID_802_11_CAPABILITY
	#घोषणा OID_802_11_CAPABILITY	0x0d010122
#पूर्ण_अगर

#अगर_अघोषित OID_802_11_PMKID
	#घोषणा OID_802_11_PMKID	0x0d010123
#पूर्ण_अगर

/*  For DDK-defined OIDs */
#घोषणा OID_NDIS_SEG1	0x00010100
#घोषणा OID_NDIS_SEG2	0x00010200
#घोषणा OID_NDIS_SEG3	0x00020100
#घोषणा OID_NDIS_SEG4	0x01010100
#घोषणा OID_NDIS_SEG5	0x01020100
#घोषणा OID_NDIS_SEG6	0x01020200
#घोषणा OID_NDIS_SEG7	0xFD010100
#घोषणा OID_NDIS_SEG8	0x0D010100
#घोषणा OID_NDIS_SEG9	0x0D010200
#घोषणा OID_NDIS_SEG10	0x0D020200

#घोषणा SZ_OID_NDIS_SEG1	23
#घोषणा SZ_OID_NDIS_SEG2	3
#घोषणा SZ_OID_NDIS_SEG3	6
#घोषणा SZ_OID_NDIS_SEG4	6
#घोषणा SZ_OID_NDIS_SEG5	4
#घोषणा SZ_OID_NDIS_SEG6	8
#घोषणा SZ_OID_NDIS_SEG7	7
#घोषणा SZ_OID_NDIS_SEG8	36
#घोषणा SZ_OID_NDIS_SEG9	24
#घोषणा SZ_OID_NDIS_SEG10	19

/*  For Realtek-defined OIDs */
#घोषणा OID_MP_SEG1		0xFF871100
#घोषणा OID_MP_SEG2		0xFF818000

#घोषणा OID_MP_SEG3		0xFF818700
#घोषणा OID_MP_SEG4		0xFF011100

क्रमागत oid_type अणु
	QUERY_OID,
	SET_OID
पूर्ण;

काष्ठा oid_par_priv अणु
	व्योम		*adapter_context;
	NDIS_OID	oid;
	व्योम		*inक्रमmation_buf;
	u32		inक्रमmation_buf_len;
	u32		*bytes_rw;
	u32		*bytes_needed;
	क्रमागत oid_type	type_of_oid;
	u32		dbg;
पूर्ण;

#अगर defined(_RTW_MP_IOCTL_C_)
अटल पूर्णांक oid_null_function(काष्ठा oid_par_priv *poid_par_priv)
अणु
	वापस NDIS_STATUS_SUCCESS;
पूर्ण
#पूर्ण_अगर

बाह्य काष्ठा iw_handler_def  rtw_handlers_def;

पूर्णांक drv_query_info(काष्ठा  net_device *miniportadaptercontext, NDIS_OID oid,
		   व्योम *inक्रमmationbuffer, u32 inक्रमmationbufferlength,
		   u32 *byteswritten, u32 *bytesneeded);

पूर्णांक drv_set_info(काष्ठा  net_device *MiniportAdapterContext,
		 NDIS_OID oid, व्योम *inक्रमmationbuffer,
		 u32 inक्रमmationbufferlength, u32 *bytesपढ़ो,
		 u32 *bytesneeded);

#पूर्ण_अगर /*  #अगर_अघोषित __INC_CEINFO_ */
