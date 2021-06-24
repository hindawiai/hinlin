<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

#अगर_अघोषित _venकरोr_h_
#घोषणा _venकरोr_h_

#घोषणा BROADCOM_OUI	0x001018

क्रमागत brcmf_vndr_cmds अणु
	BRCMF_VNDR_CMDS_UNSPEC,
	BRCMF_VNDR_CMDS_DCMD,
	BRCMF_VNDR_CMDS_LAST
पूर्ण;

/**
 * क्रमागत brcmf_nlattrs - nl80211 message attributes
 *
 * @BRCMF_NLATTR_LEN: message body length
 * @BRCMF_NLATTR_DATA: message body
 */
क्रमागत brcmf_nlattrs अणु
	BRCMF_NLATTR_UNSPEC,

	BRCMF_NLATTR_LEN,
	BRCMF_NLATTR_DATA,

	__BRCMF_NLATTR_AFTER_LAST,
	BRCMF_NLATTR_MAX = __BRCMF_NLATTR_AFTER_LAST - 1
पूर्ण;

/**
 * काष्ठा brcmf_vndr_dcmd_hdr - message header क्रम cfg80211 venकरोr command dcmd
 *				support
 *
 * @cmd: common करोngle cmd definition
 * @len: length of expecting वापस buffer
 * @offset: offset of data buffer
 * @set: get or set request(optional)
 * @magic: magic number क्रम verअगरication
 */
काष्ठा brcmf_vndr_dcmd_hdr अणु
	uपूर्णांक cmd;
	पूर्णांक len;
	uपूर्णांक offset;
	uपूर्णांक set;
	uपूर्णांक magic;
पूर्ण;

बाह्य स्थिर काष्ठा wiphy_venकरोr_command brcmf_venकरोr_cmds[];

#पूर्ण_अगर /* _venकरोr_h_ */
