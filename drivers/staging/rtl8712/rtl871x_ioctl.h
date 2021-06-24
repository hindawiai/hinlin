<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IOCTL_H
#घोषणा __IOCTL_H

#समावेश "osdep_service.h"
#समावेश "drv_types.h"

#अगर_अघोषित OID_802_11_CAPABILITY
	#घोषणा OID_802_11_CAPABILITY                   0x0d010122
#पूर्ण_अगर

#अगर_अघोषित OID_802_11_PMKID
	#घोषणा OID_802_11_PMKID                        0x0d010123
#पूर्ण_अगर


/* For DDK-defined OIDs*/
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

/* For Realtek-defined OIDs*/
#घोषणा OID_MP_SEG1	0xFF871100
#घोषणा OID_MP_SEG2	0xFF818000
#घोषणा OID_MP_SEG3	0xFF818700
#घोषणा OID_MP_SEG4	0xFF011100

क्रमागत oid_type अणु
	QUERY_OID,
	SET_OID
पूर्ण;

काष्ठा oid_funs_node अणु
	अचिन्हित पूर्णांक oid_start; /*the starting number क्रम OID*/
	अचिन्हित पूर्णांक oid_end; /*the ending number क्रम OID*/
	काष्ठा oid_obj_priv *node_array;
	अचिन्हित पूर्णांक array_sz; /*the size of node_array*/
	पूर्णांक query_counter; /*count the number of query hits क्रम this segment*/
	पूर्णांक set_counter; /*count the number of set hits क्रम this segment*/
पूर्ण;

काष्ठा oid_par_priv अणु
	व्योम	*adapter_context;
	uपूर्णांक oid;
	व्योम *inक्रमmation_buf;
	अचिन्हित दीर्घ inक्रमmation_buf_len;
	अचिन्हित दीर्घ *bytes_rw;
	अचिन्हित दीर्घ *bytes_needed;
	क्रमागत oid_type	type_of_oid;
	अचिन्हित पूर्णांक dbg;
पूर्ण;

काष्ठा oid_obj_priv अणु
	अचिन्हित अक्षर	dbg; /* 0: without OID debug message
			      * 1: with OID debug message
			      */
	uपूर्णांक (*oidfuns)(काष्ठा oid_par_priv *poid_par_priv);
पूर्ण;

uपूर्णांक oid_null_function(काष्ठा oid_par_priv *poid_par_priv);

बाह्य काष्ठा iw_handler_def  r871x_handlers_def;

uपूर्णांक drv_query_info(काष्ठा net_device *MiniportAdapterContext,
		    uपूर्णांक Oid,
		    व्योम *Inक्रमmationBuffer,
		    u32 Inक्रमmationBufferLength,
		    u32 *BytesWritten,
		    u32 *BytesNeeded);

uपूर्णांक drv_set_info(काष्ठा net_device *MiniportAdapterContext,
		  uपूर्णांक Oid,
		  व्योम *Inक्रमmationBuffer,
		  u32 Inक्रमmationBufferLength,
		  u32 *BytesRead,
		  u32 *BytesNeeded);

#पूर्ण_अगर
