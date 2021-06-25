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

#समावेश <linux/export.h>
#समावेश "ath.h"

स्थिर अक्षर *ath_opmode_to_string(क्रमागत nl80211_अगरtype opmode)
अणु
	चयन (opmode) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		वापस "UNSPEC";
	हाल NL80211_IFTYPE_ADHOC:
		वापस "ADHOC";
	हाल NL80211_IFTYPE_STATION:
		वापस "STATION";
	हाल NL80211_IFTYPE_AP:
		वापस "AP";
	हाल NL80211_IFTYPE_AP_VLAN:
		वापस "AP-VLAN";
	हाल NL80211_IFTYPE_WDS:
		वापस "WDS";
	हाल NL80211_IFTYPE_MONITOR:
		वापस "MONITOR";
	हाल NL80211_IFTYPE_MESH_POINT:
		वापस "MESH";
	हाल NL80211_IFTYPE_P2P_CLIENT:
		वापस "P2P-CLIENT";
	हाल NL80211_IFTYPE_P2P_GO:
		वापस "P2P-GO";
	हाल NL80211_IFTYPE_OCB:
		वापस "OCB";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath_opmode_to_string);
