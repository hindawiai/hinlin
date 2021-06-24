<शैली गुरु>
/*
 * Copyright (c) 2009 Atheros Communications Inc.
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "ath.h"
#समावेश "trace.h"

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Shared library for Atheros wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

काष्ठा sk_buff *ath_rxbuf_alloc(काष्ठा ath_common *common,
				u32 len,
				gfp_t gfp_mask)
अणु
	काष्ठा sk_buff *skb;
	u32 off;

	/*
	 * Cache-line-align.  This is important (क्रम the
	 * 5210 at least) as not करोing so causes bogus data
	 * in rx'd frames.
	 */

	/* Note: the kernel can allocate a value greater than
	 * what we ask it to give us. We really only need 4 KB as that
	 * is this hardware supports and in fact we need at least 3849
	 * as that is the MAX AMSDU size this hardware supports.
	 * Unक्रमtunately this means we may get 8 KB here from the
	 * kernel... and that is actually what is observed on some
	 * प्रणालीs :( */
	skb = __dev_alloc_skb(len + common->cachelsz - 1, gfp_mask);
	अगर (skb != शून्य) अणु
		off = ((अचिन्हित दीर्घ) skb->data) % common->cachelsz;
		अगर (off != 0)
			skb_reserve(skb, common->cachelsz - off);
	पूर्ण अन्यथा अणु
		pr_err("skbuff alloc of size %u failed\n", len);
		वापस शून्य;
	पूर्ण

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ath_rxbuf_alloc);

bool ath_is_mybeacon(काष्ठा ath_common *common, काष्ठा ieee80211_hdr *hdr)
अणु
	वापस ieee80211_is_beacon(hdr->frame_control) &&
		!is_zero_ether_addr(common->curbssid) &&
		ether_addr_equal_64bits(hdr->addr3, common->curbssid);
पूर्ण
EXPORT_SYMBOL(ath_is_mybeacon);

व्योम ath_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा ath_common* common,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (common && common->hw && common->hw->wiphy) अणु
		prपूर्णांकk("%sath: %s: %pV",
		       level, wiphy_name(common->hw->wiphy), &vaf);
		trace_ath_log(common->hw->wiphy, &vaf);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%sath: %pV", level, &vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath_prपूर्णांकk);

स्थिर अक्षर *ath_bus_type_strings[] = अणु
	[ATH_PCI] = "pci",
	[ATH_AHB] = "ahb",
	[ATH_USB] = "usb",
पूर्ण;
EXPORT_SYMBOL(ath_bus_type_strings);
