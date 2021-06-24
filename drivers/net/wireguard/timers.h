<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_TIMERS_H
#घोषणा _WG_TIMERS_H

#समावेश <linux/kसमय.स>

काष्ठा wg_peer;

व्योम wg_समयrs_init(काष्ठा wg_peer *peer);
व्योम wg_समयrs_stop(काष्ठा wg_peer *peer);
व्योम wg_समयrs_data_sent(काष्ठा wg_peer *peer);
व्योम wg_समयrs_data_received(काष्ठा wg_peer *peer);
व्योम wg_समयrs_any_authenticated_packet_sent(काष्ठा wg_peer *peer);
व्योम wg_समयrs_any_authenticated_packet_received(काष्ठा wg_peer *peer);
व्योम wg_समयrs_handshake_initiated(काष्ठा wg_peer *peer);
व्योम wg_समयrs_handshake_complete(काष्ठा wg_peer *peer);
व्योम wg_समयrs_session_derived(काष्ठा wg_peer *peer);
व्योम wg_समयrs_any_authenticated_packet_traversal(काष्ठा wg_peer *peer);

अटल अंतरभूत bool wg_birthdate_has_expired(u64 birthday_nanoseconds,
					    u64 expiration_seconds)
अणु
	वापस (s64)(birthday_nanoseconds + expiration_seconds * NSEC_PER_SEC)
		<= (s64)kसमय_get_coarse_bootसमय_ns();
पूर्ण

#पूर्ण_अगर /* _WG_TIMERS_H */
