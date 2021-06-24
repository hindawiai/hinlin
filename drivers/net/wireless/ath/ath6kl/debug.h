<शैली गुरु>
/*
 * Copyright (c) 2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित DEBUG_H
#घोषणा DEBUG_H

#समावेश "hif.h"
#समावेश "trace.h"

क्रमागत ATH6K_DEBUG_MASK अणु
	ATH6KL_DBG_CREDIT	= BIT(0),
	/* hole */
	ATH6KL_DBG_WLAN_TX      = BIT(2),     /* wlan tx */
	ATH6KL_DBG_WLAN_RX      = BIT(3),     /* wlan rx */
	ATH6KL_DBG_BMI		= BIT(4),     /* bmi tracing */
	ATH6KL_DBG_HTC		= BIT(5),
	ATH6KL_DBG_HIF		= BIT(6),
	ATH6KL_DBG_IRQ		= BIT(7),     /* पूर्णांकerrupt processing */
	/* hole */
	/* hole */
	ATH6KL_DBG_WMI          = BIT(10),    /* wmi tracing */
	ATH6KL_DBG_TRC	        = BIT(11),    /* generic func tracing */
	ATH6KL_DBG_SCATTER	= BIT(12),    /* hअगर scatter tracing */
	ATH6KL_DBG_WLAN_CFG     = BIT(13),    /* cfg80211 i/f file tracing */
	ATH6KL_DBG_RAW_BYTES    = BIT(14),    /* dump tx/rx frames */
	ATH6KL_DBG_AGGR		= BIT(15),    /* aggregation */
	ATH6KL_DBG_SDIO		= BIT(16),
	ATH6KL_DBG_SDIO_DUMP	= BIT(17),
	ATH6KL_DBG_BOOT		= BIT(18),    /* driver init and fw boot */
	ATH6KL_DBG_WMI_DUMP	= BIT(19),
	ATH6KL_DBG_SUSPEND	= BIT(20),
	ATH6KL_DBG_USB		= BIT(21),
	ATH6KL_DBG_USB_BULK	= BIT(22),
	ATH6KL_DBG_RECOVERY	= BIT(23),
	ATH6KL_DBG_ANY	        = 0xffffffff  /* enable all logs */
पूर्ण;

बाह्य अचिन्हित पूर्णांक debug_mask;
__म_लिखो(2, 3) व्योम ath6kl_prपूर्णांकk(स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम ath6kl_info(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम ath6kl_err(स्थिर अक्षर *fmt, ...);
__म_लिखो(1, 2) व्योम ath6kl_warn(स्थिर अक्षर *fmt, ...);

क्रमागत ath6kl_war अणु
	ATH6KL_WAR_INVALID_RATE,
पूर्ण;

पूर्णांक ath6kl_पढ़ो_tgt_stats(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर);

#अगर_घोषित CONFIG_ATH6KL_DEBUG

__म_लिखो(2, 3)
व्योम ath6kl_dbg(क्रमागत ATH6K_DEBUG_MASK mask, स्थिर अक्षर *fmt, ...);
व्योम ath6kl_dbg_dump(क्रमागत ATH6K_DEBUG_MASK mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len);

व्योम ath6kl_dump_रेजिस्टरs(काष्ठा ath6kl_device *dev,
			   काष्ठा ath6kl_irq_proc_रेजिस्टरs *irq_proc_reg,
			   काष्ठा ath6kl_irq_enable_reg *irq_en_reg);
व्योम dump_cred_dist_stats(काष्ठा htc_target *target);
व्योम ath6kl_debug_fwlog_event(काष्ठा ath6kl *ar, स्थिर व्योम *buf, माप_प्रकार len);
व्योम ath6kl_debug_war(काष्ठा ath6kl *ar, क्रमागत ath6kl_war war);
पूर्णांक ath6kl_debug_roam_tbl_event(काष्ठा ath6kl *ar, स्थिर व्योम *buf,
				माप_प्रकार len);
व्योम ath6kl_debug_set_keepalive(काष्ठा ath6kl *ar, u8 keepalive);
व्योम ath6kl_debug_set_disconnect_समयout(काष्ठा ath6kl *ar, u8 समयout);
व्योम ath6kl_debug_init(काष्ठा ath6kl *ar);
पूर्णांक ath6kl_debug_init_fs(काष्ठा ath6kl *ar);
व्योम ath6kl_debug_cleanup(काष्ठा ath6kl *ar);

#अन्यथा
__म_लिखो(2, 3)
अटल अंतरभूत व्योम ath6kl_dbg(क्रमागत ATH6K_DEBUG_MASK dbg_mask,
			      स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_dbg_dump(क्रमागत ATH6K_DEBUG_MASK mask,
				   स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
				   स्थिर व्योम *buf, माप_प्रकार len)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_dump_रेजिस्टरs(काष्ठा ath6kl_device *dev,
		काष्ठा ath6kl_irq_proc_रेजिस्टरs *irq_proc_reg,
		काष्ठा ath6kl_irq_enable_reg *irq_en_reg)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_cred_dist_stats(काष्ठा htc_target *target)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_fwlog_event(काष्ठा ath6kl *ar,
					    स्थिर व्योम *buf, माप_प्रकार len)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_war(काष्ठा ath6kl *ar, क्रमागत ath6kl_war war)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_debug_roam_tbl_event(काष्ठा ath6kl *ar,
					      स्थिर व्योम *buf, माप_प्रकार len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_set_keepalive(काष्ठा ath6kl *ar, u8 keepalive)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_set_disconnect_समयout(काष्ठा ath6kl *ar,
						       u8 समयout)
अणु
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_init(काष्ठा ath6kl *ar)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_debug_init_fs(काष्ठा ath6kl *ar)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath6kl_debug_cleanup(काष्ठा ath6kl *ar)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
