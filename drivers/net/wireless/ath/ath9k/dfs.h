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

#अगर_अघोषित ATH9K_DFS_H
#घोषणा ATH9K_DFS_H
#समावेश "../dfs_pattern_detector.h"

#अगर defined(CONFIG_ATH9K_DFS_CERTIFIED)
/**
 * ath9k_dfs_process_phyerr - process radar PHY error
 * @sc: ath_softc
 * @data: RX payload data
 * @rs: RX status after processing descriptor
 * @maस_समय: receive समय
 *
 * This function is called whenever the HW DFS module detects a radar
 * pulse and reports it as a PHY error.
 *
 * The radar inक्रमmation provided as raw payload data is validated and
 * filtered क्रम false pulses. Events passing all tests are क्रमwarded to
 * the DFS detector क्रम pattern detection.
 */
व्योम ath9k_dfs_process_phyerr(काष्ठा ath_softc *sc, व्योम *data,
			      काष्ठा ath_rx_status *rs, u64 maस_समय);
#अन्यथा
अटल अंतरभूत व्योम
ath9k_dfs_process_phyerr(काष्ठा ath_softc *sc, व्योम *data,
			 काष्ठा ath_rx_status *rs, u64 maस_समय) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* ATH9K_DFS_H */
