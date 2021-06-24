<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Neratec Solutions AG
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


#अगर_अघोषित ATH9K_DFS_DEBUG_H
#घोषणा ATH9K_DFS_DEBUG_H

#समावेश "hw.h"

काष्ठा ath_softc;

/**
 * काष्ठा ath_dfs_stats - DFS Statistics per wiphy
 * @pulses_total:     pulses reported by HW
 * @pulses_no_dfs:    pulses wrongly reported as DFS
 * @pulses_detected:  pulses detected so far
 * @datalen_discards: pulses discarded due to invalid datalen
 * @rssi_discards:    pulses discarded due to invalid RSSI
 * @bwinfo_discards:  pulses discarded due to invalid BW info
 * @pri_phy_errors:   pulses reported क्रम primary channel
 * @ext_phy_errors:   pulses reported क्रम extension channel
 * @dc_phy_errors:    pulses reported क्रम primary + extension channel
 * @pulses_processed: pulses क्रमwarded to detector
 * @radar_detected:   radars detected
 */
काष्ठा ath_dfs_stats अणु
	/* pulse stats */
	u32 pulses_total;
	u32 pulses_no_dfs;
	u32 pulses_detected;
	u32 datalen_discards;
	u32 rssi_discards;
	u32 bwinfo_discards;
	u32 pri_phy_errors;
	u32 ext_phy_errors;
	u32 dc_phy_errors;
	/* pattern detection stats */
	u32 pulses_processed;
	u32 radar_detected;
पूर्ण;

#अगर defined(CONFIG_ATH9K_DFS_DEBUGFS)

#घोषणा DFS_STAT_INC(sc, c) (sc->debug.stats.dfs_stats.c++)
व्योम ath9k_dfs_init_debug(काष्ठा ath_softc *sc);

बाह्य काष्ठा ath_dfs_pool_stats global_dfs_pool_stats;

#अन्यथा

#घोषणा DFS_STAT_INC(sc, c) करो अणु पूर्ण जबतक (0)
अटल अंतरभूत व्योम ath9k_dfs_init_debug(काष्ठा ath_softc *sc) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_DFS_DEBUGFS */

#पूर्ण_अगर /* ATH9K_DFS_DEBUG_H */
