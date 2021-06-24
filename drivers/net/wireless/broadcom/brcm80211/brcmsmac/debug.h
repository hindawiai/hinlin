<शैली गुरु>
/*
 * Copyright (c) 2012 Broadcom Corporation
 * Copyright (c) 2012 Canonical Ltd.
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
#अगर_अघोषित _BRCMS_DEBUG_H_
#घोषणा _BRCMS_DEBUG_H_

#समावेश <linux/device.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश "main.h"
#समावेश "mac80211_if.h"

__म_लिखो(2, 3)
व्योम __brcms_info(काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __brcms_warn(काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __brcms_err(काष्ठा device *dev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __brcms_crit(काष्ठा device *dev, स्थिर अक्षर *fmt, ...);

#अगर defined(CONFIG_BRCMDBG) || defined(CONFIG_BRCM_TRACING)
__म_लिखो(4, 5)
व्योम __brcms_dbg(काष्ठा device *dev, u32 level, स्थिर अक्षर *func,
		 स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत __म_लिखो(4, 5)
व्योम __brcms_dbg(काष्ठा device *dev, u32 level, स्थिर अक्षर *func,
		 स्थिर अक्षर *fmt, ...)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Debug macros cannot be used when wlc is uninitialized. Generally
 * this means any code that could run beक्रमe brcms_c_attach() has
 * वापसed successfully probably shouldn't use the following macros.
 */

#घोषणा brcms_dbg(core, l, f, a...)	__brcms_dbg(&(core)->dev, l, __func__, f, ##a)
#घोषणा brcms_info(core, f, a...)	__brcms_info(&(core)->dev, f, ##a)
#घोषणा brcms_warn(core, f, a...)	__brcms_warn(&(core)->dev, f, ##a)
#घोषणा brcms_err(core, f, a...)	__brcms_err(&(core)->dev, f, ##a)
#घोषणा brcms_crit(core, f, a...)	__brcms_crit(&(core)->dev, f, ##a)

#घोषणा brcms_dbg_info(core, f, a...)		brcms_dbg(core, BRCM_DL_INFO, f, ##a)
#घोषणा brcms_dbg_mac80211(core, f, a...)	brcms_dbg(core, BRCM_DL_MAC80211, f, ##a)
#घोषणा brcms_dbg_rx(core, f, a...)		brcms_dbg(core, BRCM_DL_RX, f, ##a)
#घोषणा brcms_dbg_tx(core, f, a...)		brcms_dbg(core, BRCM_DL_TX, f, ##a)
#घोषणा brcms_dbg_पूर्णांक(core, f, a...)		brcms_dbg(core, BRCM_DL_INT, f, ##a)
#घोषणा brcms_dbg_dma(core, f, a...)		brcms_dbg(core, BRCM_DL_DMA, f, ##a)
#घोषणा brcms_dbg_ht(core, f, a...)		brcms_dbg(core, BRCM_DL_HT, f, ##a)

काष्ठा brcms_pub;
व्योम brcms_debugfs_init(व्योम);
व्योम brcms_debugfs_निकास(व्योम);
व्योम brcms_debugfs_attach(काष्ठा brcms_pub *drvr);
व्योम brcms_debugfs_detach(काष्ठा brcms_pub *drvr);
काष्ठा dentry *brcms_debugfs_get_devdir(काष्ठा brcms_pub *drvr);
व्योम brcms_debugfs_create_files(काष्ठा brcms_pub *drvr);

#पूर्ण_अगर /* _BRCMS_DEBUG_H_ */
