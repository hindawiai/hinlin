<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich, Marek Lindner
 */

#अगर_अघोषित _NET_BATMAN_ADV_BITARRAY_H_
#घोषणा _NET_BATMAN_ADV_BITARRAY_H_

#समावेश "main.h"

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

/**
 * batadv_test_bit() - check अगर bit is set in the current winकरोw
 *
 * @seq_bits: poपूर्णांकer to the sequence number receive packet
 * @last_seqno: latest sequence number in seq_bits
 * @curr_seqno: sequence number to test क्रम
 *
 * Return: true अगर the corresponding bit in the given seq_bits indicates true
 * and curr_seqno is within range of last_seqno. Otherwise वापसs false.
 */
अटल अंतरभूत bool batadv_test_bit(स्थिर अचिन्हित दीर्घ *seq_bits,
				   u32 last_seqno, u32 curr_seqno)
अणु
	s32 dअगरf;

	dअगरf = last_seqno - curr_seqno;
	अगर (dअगरf < 0 || dअगरf >= BATADV_TQ_LOCAL_WINDOW_SIZE)
		वापस false;
	वापस test_bit(dअगरf, seq_bits) != 0;
पूर्ण

/**
 * batadv_set_bit() - Turn corresponding bit on, so we can remember that we got
 *  the packet
 * @seq_bits: biपंचांगap of the packet receive winकरोw
 * @n: relative sequence number of newly received packet
 */
अटल अंतरभूत व्योम batadv_set_bit(अचिन्हित दीर्घ *seq_bits, s32 n)
अणु
	/* अगर too old, just drop it */
	अगर (n < 0 || n >= BATADV_TQ_LOCAL_WINDOW_SIZE)
		वापस;

	set_bit(n, seq_bits); /* turn the position on */
पूर्ण

bool batadv_bit_get_packet(व्योम *priv, अचिन्हित दीर्घ *seq_bits,
			   s32 seq_num_dअगरf, पूर्णांक set_mark);

#पूर्ण_अगर /* _NET_BATMAN_ADV_BITARRAY_H_ */
