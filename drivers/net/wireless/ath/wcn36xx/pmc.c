<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "wcn36xx.h"

पूर्णांक wcn36xx_pmc_enter_bmps_state(काष्ठा wcn36xx *wcn,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret = 0;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	अगर (!vअगर_priv->allow_bmps)
		वापस -ENOTSUPP;

	ret = wcn36xx_smd_enter_bmps(wcn, vअगर);
	अगर (!ret) अणु
		wcn36xx_dbg(WCN36XX_DBG_PMC, "Entered BMPS\n");
		vअगर_priv->pw_state = WCN36XX_BMPS;
		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;
	पूर्ण अन्यथा अणु
		/*
		 * One of the reasons why HW will not enter BMPS is because
		 * driver is trying to enter bmps beक्रमe first beacon was
		 * received just after auth complete
		 */
		wcn36xx_err("Can not enter BMPS!\n");
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_pmc_निकास_bmps_state(काष्ठा wcn36xx *wcn,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	अगर (WCN36XX_BMPS != vअगर_priv->pw_state) अणु
		/* Unbalanced call or last BMPS enter failed */
		wcn36xx_dbg(WCN36XX_DBG_PMC,
			    "Not in BMPS mode, no need to exit\n");
		वापस -EALREADY;
	पूर्ण
	wcn36xx_smd_निकास_bmps(wcn, vअगर);
	vअगर_priv->pw_state = WCN36XX_FULL_POWER;
	vअगर->driver_flags &= ~IEEE80211_VIF_BEACON_FILTER;
	वापस 0;
पूर्ण

पूर्णांक wcn36xx_enable_keep_alive_null_packet(काष्ठा wcn36xx *wcn,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	wcn36xx_dbg(WCN36XX_DBG_PMC, "%s\n", __func__);
	वापस wcn36xx_smd_keep_alive_req(wcn, vअगर,
					  WCN36XX_HAL_KEEP_ALIVE_शून्य_PKT);
पूर्ण
