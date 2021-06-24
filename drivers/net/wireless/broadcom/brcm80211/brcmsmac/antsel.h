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

#अगर_अघोषित _BRCM_ANTSEL_H_
#घोषणा _BRCM_ANTSEL_H_

काष्ठा antsel_info *brcms_c_antsel_attach(काष्ठा brcms_c_info *wlc);
व्योम brcms_c_antsel_detach(काष्ठा antsel_info *asi);
व्योम brcms_c_antsel_init(काष्ठा antsel_info *asi);
व्योम brcms_c_antsel_antcfg_get(काष्ठा antsel_info *asi, bool usedef, bool sel,
			       u8 id, u8 fbid, u8 *antcfg, u8 *fbantcfg);
u8 brcms_c_antsel_antsel2id(काष्ठा antsel_info *asi, u16 antsel);

#पूर्ण_अगर /* _BRCM_ANTSEL_H_ */
