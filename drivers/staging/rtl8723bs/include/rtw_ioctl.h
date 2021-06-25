<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_IOCTL_H_
#घोषणा _RTW_IOCTL_H_

/* 	00 - Success */
/* 	11 - Error */
#घोषणा STATUS_SUCCESS				(0x00000000L)
#घोषणा STATUS_PENDING				(0x00000103L)

#घोषणा STATUS_UNSUCCESSFUL			(0xC0000001L)
#घोषणा STATUS_INSUFFICIENT_RESOURCES		(0xC000009AL)
#घोषणा STATUS_NOT_SUPPORTED			(0xC00000BBL)

#घोषणा NDIS_STATUS_SUCCESS			((uपूर्णांक)STATUS_SUCCESS)
#घोषणा NDIS_STATUS_PENDING			((uपूर्णांक)STATUS_PENDING)
#घोषणा NDIS_STATUS_NOT_RECOGNIZED		((uपूर्णांक)0x00010001L)
#घोषणा NDIS_STATUS_NOT_COPIED			((uपूर्णांक)0x00010002L)
#घोषणा NDIS_STATUS_NOT_ACCEPTED		((uपूर्णांक)0x00010003L)
#घोषणा NDIS_STATUS_CALL_ACTIVE			((uपूर्णांक)0x00010007L)

#घोषणा NDIS_STATUS_FAILURE			((uपूर्णांक)STATUS_UNSUCCESSFUL)
#घोषणा NDIS_STATUS_RESOURCES			((uपूर्णांक)STATUS_INSUFFICIENT_RESOURCES)
#घोषणा NDIS_STATUS_CLOSING			((uपूर्णांक)0xC0010002L)
#घोषणा NDIS_STATUS_BAD_VERSION			((uपूर्णांक)0xC0010004L)
#घोषणा NDIS_STATUS_BAD_CHARACTERISTICS		((uपूर्णांक)0xC0010005L)
#घोषणा NDIS_STATUS_ADAPTER_NOT_FOUND		((uपूर्णांक)0xC0010006L)
#घोषणा NDIS_STATUS_OPEN_FAILED			((uपूर्णांक)0xC0010007L)
#घोषणा NDIS_STATUS_DEVICE_FAILED		((uपूर्णांक)0xC0010008L)
#घोषणा NDIS_STATUS_MULTICAST_FULL		((uपूर्णांक)0xC0010009L)
#घोषणा NDIS_STATUS_MULTICAST_EXISTS		((uपूर्णांक)0xC001000AL)
#घोषणा NDIS_STATUS_MULTICAST_NOT_FOUND		((uपूर्णांक)0xC001000BL)
#घोषणा NDIS_STATUS_REQUEST_ABORTED		((uपूर्णांक)0xC001000CL)
#घोषणा NDIS_STATUS_RESET_IN_PROGRESS		((uपूर्णांक)0xC001000DL)
#घोषणा NDIS_STATUS_CLOSING_INDICATING		((uपूर्णांक)0xC001000EL)
#घोषणा NDIS_STATUS_NOT_SUPPORTED		((uपूर्णांक)STATUS_NOT_SUPPORTED)
#घोषणा NDIS_STATUS_INVALID_PACKET		((uपूर्णांक)0xC001000FL)
#घोषणा NDIS_STATUS_OPEN_LIST_FULL		((uपूर्णांक)0xC0010010L)
#घोषणा NDIS_STATUS_ADAPTER_NOT_READY		((uपूर्णांक)0xC0010011L)
#घोषणा NDIS_STATUS_ADAPTER_NOT_OPEN		((uपूर्णांक)0xC0010012L)
#घोषणा NDIS_STATUS_NOT_INDICATING		((uपूर्णांक)0xC0010013L)
#घोषणा NDIS_STATUS_INVALID_LENGTH		((uपूर्णांक)0xC0010014L)
#घोषणा NDIS_STATUS_INVALID_DATA		((uपूर्णांक)0xC0010015L)
#घोषणा NDIS_STATUS_BUFFER_TOO_SHORT		((uपूर्णांक)0xC0010016L)
#घोषणा NDIS_STATUS_INVALID_OID			((uपूर्णांक)0xC0010017L)
#घोषणा NDIS_STATUS_ADAPTER_REMOVED		((uपूर्णांक)0xC0010018L)
#घोषणा NDIS_STATUS_UNSUPPORTED_MEDIA		((uपूर्णांक)0xC0010019L)
#घोषणा NDIS_STATUS_GROUP_ADDRESS_IN_USE	((uपूर्णांक)0xC001001AL)
#घोषणा NDIS_STATUS_खाता_NOT_FOUND		((uपूर्णांक)0xC001001BL)
#घोषणा NDIS_STATUS_ERROR_READING_खाता		((uपूर्णांक)0xC001001CL)
#घोषणा NDIS_STATUS_ALREADY_MAPPED		((uपूर्णांक)0xC001001DL)
#घोषणा NDIS_STATUS_RESOURCE_CONFLICT		((uपूर्णांक)0xC001001EL)
#घोषणा NDIS_STATUS_NO_CABLE			((uपूर्णांक)0xC001001FL)

#घोषणा NDIS_STATUS_INVALID_SAP			((uपूर्णांक)0xC0010020L)
#घोषणा NDIS_STATUS_SAP_IN_USE			((uपूर्णांक)0xC0010021L)
#घोषणा NDIS_STATUS_INVALID_ADDRESS		((uपूर्णांक)0xC0010022L)
#घोषणा NDIS_STATUS_VC_NOT_ACTIVATED		((uपूर्णांक)0xC0010023L)
#घोषणा NDIS_STATUS_DEST_OUT_OF_ORDER		((uपूर्णांक)0xC0010024L)  /*  cause 27 */
#घोषणा NDIS_STATUS_VC_NOT_AVAILABLE		((uपूर्णांक)0xC0010025L)  /*  cause 35, 45 */
#घोषणा NDIS_STATUS_CELLRATE_NOT_AVAILABLE	((uपूर्णांक)0xC0010026L)  /*  cause 37 */
#घोषणा NDIS_STATUS_INCOMPATABLE_QOS		((uपूर्णांक)0xC0010027L)  /*  cause 49 */
#घोषणा NDIS_STATUS_AAL_PARAMS_UNSUPPORTED	((uपूर्णांक)0xC0010028L)  /*  cause 93 */
#घोषणा NDIS_STATUS_NO_ROUTE_TO_DESTINATION	((uपूर्णांक)0xC0010029L)  /*  cause 3 */

बाह्य काष्ठा iw_handler_def  rtw_handlers_def;

#पूर्ण_अगर /*  #अगर_अघोषित __INC_CEINFO_ */
