<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित	_BRCM_UCODE_H_
#घोषणा	_BRCM_UCODE_H_

#समावेश "types.h"		/* क्रमward काष्ठाure declarations */

#घोषणा MIN_FW_SIZE 40000	/* minimum firmware file size in bytes */
#घोषणा MAX_FW_SIZE 150000

#घोषणा UCODE_LOADER_API_VER 0

काष्ठा d11init;

काष्ठा brcms_ucode अणु
	काष्ठा d11init *d11lcn0bsinitvals24;
	काष्ठा d11init *d11lcn0initvals24;
	काष्ठा d11init *d11lcn1bsinitvals24;
	काष्ठा d11init *d11lcn1initvals24;
	काष्ठा d11init *d11lcn2bsinitvals24;
	काष्ठा d11init *d11lcn2initvals24;
	काष्ठा d11init *d11n0असलinitvals16;
	काष्ठा d11init *d11n0bsinitvals16;
	काष्ठा d11init *d11n0initvals16;
	__le32 *bcm43xx_16_mimo;
	माप_प्रकार bcm43xx_16_mimosz;
	__le32 *bcm43xx_24_lcn;
	माप_प्रकार bcm43xx_24_lcnsz;
	u32 *bcm43xx_bommajor;
	u32 *bcm43xx_bomminor;
पूर्ण;

पूर्णांक brcms_ucode_data_init(काष्ठा brcms_info *wl, काष्ठा brcms_ucode *ucode);

व्योम brcms_ucode_data_मुक्त(काष्ठा brcms_ucode *ucode);

पूर्णांक brcms_ucode_init_buf(काष्ठा brcms_info *wl, व्योम **pbuf, अचिन्हित पूर्णांक idx);
पूर्णांक brcms_ucode_init_uपूर्णांक(काष्ठा brcms_info *wl, माप_प्रकार *n_bytes,
			  अचिन्हित पूर्णांक idx);
व्योम brcms_ucode_मुक्त_buf(व्योम *);
पूर्णांक  brcms_check_firmwares(काष्ठा brcms_info *wl);

#पूर्ण_अगर	/* _BRCM_UCODE_H_ */
