<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित _WG_MESSAGES_H
#घोषणा _WG_MESSAGES_H

#समावेश <crypto/curve25519.h>
#समावेश <crypto/chacha20poly1305.h>
#समावेश <crypto/blake2s.h>

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/skbuff.h>

क्रमागत noise_lengths अणु
	NOISE_PUBLIC_KEY_LEN = CURVE25519_KEY_SIZE,
	NOISE_SYMMETRIC_KEY_LEN = CHACHA20POLY1305_KEY_SIZE,
	NOISE_TIMESTAMP_LEN = माप(u64) + माप(u32),
	NOISE_AUTHTAG_LEN = CHACHA20POLY1305_AUTHTAG_SIZE,
	NOISE_HASH_LEN = BLAKE2S_HASH_SIZE
पूर्ण;

#घोषणा noise_encrypted_len(plain_len) ((plain_len) + NOISE_AUTHTAG_LEN)

क्रमागत cookie_values अणु
	COOKIE_SECRET_MAX_AGE = 2 * 60,
	COOKIE_SECRET_LATENCY = 5,
	COOKIE_NONCE_LEN = XCHACHA20POLY1305_NONCE_SIZE,
	COOKIE_LEN = 16
पूर्ण;

क्रमागत counter_values अणु
	COUNTER_BITS_TOTAL = 8192,
	COUNTER_REDUNDANT_BITS = BITS_PER_LONG,
	COUNTER_WINDOW_SIZE = COUNTER_BITS_TOTAL - COUNTER_REDUNDANT_BITS
पूर्ण;

क्रमागत limits अणु
	REKEY_AFTER_MESSAGES = 1ULL << 60,
	REJECT_AFTER_MESSAGES = U64_MAX - COUNTER_WINDOW_SIZE - 1,
	REKEY_TIMEOUT = 5,
	REKEY_TIMEOUT_JITTER_MAX_JIFFIES = HZ / 3,
	REKEY_AFTER_TIME = 120,
	REJECT_AFTER_TIME = 180,
	INITIATIONS_PER_SECOND = 50,
	MAX_PEERS_PER_DEVICE = 1U << 20,
	KEEPALIVE_TIMEOUT = 10,
	MAX_TIMER_HANDSHAKES = 90 / REKEY_TIMEOUT,
	MAX_QUEUED_INCOMING_HANDSHAKES = 4096, /* TODO: replace this with DQL */
	MAX_STAGED_PACKETS = 128,
	MAX_QUEUED_PACKETS = 1024 /* TODO: replace this with DQL */
पूर्ण;

क्रमागत message_type अणु
	MESSAGE_INVALID = 0,
	MESSAGE_HANDSHAKE_INITIATION = 1,
	MESSAGE_HANDSHAKE_RESPONSE = 2,
	MESSAGE_HANDSHAKE_COOKIE = 3,
	MESSAGE_DATA = 4
पूर्ण;

काष्ठा message_header अणु
	/* The actual layout of this that we want is:
	 * u8 type
	 * u8 reserved_zero[3]
	 *
	 * But it turns out that by encoding this as little endian,
	 * we achieve the same thing, and it makes checking faster.
	 */
	__le32 type;
पूर्ण;

काष्ठा message_macs अणु
	u8 mac1[COOKIE_LEN];
	u8 mac2[COOKIE_LEN];
पूर्ण;

काष्ठा message_handshake_initiation अणु
	काष्ठा message_header header;
	__le32 sender_index;
	u8 unencrypted_ephemeral[NOISE_PUBLIC_KEY_LEN];
	u8 encrypted_अटल[noise_encrypted_len(NOISE_PUBLIC_KEY_LEN)];
	u8 encrypted_बारtamp[noise_encrypted_len(NOISE_TIMESTAMP_LEN)];
	काष्ठा message_macs macs;
पूर्ण;

काष्ठा message_handshake_response अणु
	काष्ठा message_header header;
	__le32 sender_index;
	__le32 receiver_index;
	u8 unencrypted_ephemeral[NOISE_PUBLIC_KEY_LEN];
	u8 encrypted_nothing[noise_encrypted_len(0)];
	काष्ठा message_macs macs;
पूर्ण;

काष्ठा message_handshake_cookie अणु
	काष्ठा message_header header;
	__le32 receiver_index;
	u8 nonce[COOKIE_NONCE_LEN];
	u8 encrypted_cookie[noise_encrypted_len(COOKIE_LEN)];
पूर्ण;

काष्ठा message_data अणु
	काष्ठा message_header header;
	__le32 key_idx;
	__le64 counter;
	u8 encrypted_data[];
पूर्ण;

#घोषणा message_data_len(plain_len) \
	(noise_encrypted_len(plain_len) + माप(काष्ठा message_data))

क्रमागत message_alignments अणु
	MESSAGE_PADDING_MULTIPLE = 16,
	MESSAGE_MINIMUM_LENGTH = message_data_len(0)
पूर्ण;

#घोषणा SKB_HEADER_LEN                                       \
	(max(माप(काष्ठा iphdr), माप(काष्ठा ipv6hdr)) + \
	 माप(काष्ठा udphdr) + NET_SKB_PAD)
#घोषणा DATA_PACKET_HEAD_ROOM \
	ALIGN(माप(काष्ठा message_data) + SKB_HEADER_LEN, 4)

क्रमागत अणु HANDSHAKE_DSCP = 0x88 /* AF41, plus 00 ECN */ पूर्ण;

#पूर्ण_अगर /* _WG_MESSAGES_H */
