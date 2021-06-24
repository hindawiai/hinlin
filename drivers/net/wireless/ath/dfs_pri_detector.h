<शैली गुरु>
/*
 * Copyright (c) 2012 Neratec Solutions AG
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

#अगर_अघोषित DFS_PRI_DETECTOR_H
#घोषणा DFS_PRI_DETECTOR_H

#समावेश <linux/list.h>

बाह्य काष्ठा ath_dfs_pool_stats global_dfs_pool_stats;

/**
 * काष्ठा pri_sequence - sequence of pulses matching one PRI
 * @head: list_head
 * @pri: pulse repetition पूर्णांकerval (PRI) in usecs
 * @dur: duration of sequence in usecs
 * @count: number of pulses in this sequence
 * @count_falses: number of not matching pulses in this sequence
 * @first_ts: समय stamp of first pulse in usecs
 * @last_ts: समय stamp of last pulse in usecs
 * @deadline_ts: deadline when this sequence becomes invalid (first_ts + dur)
 */
काष्ठा pri_sequence अणु
	काष्ठा list_head head;
	u32 pri;
	u32 dur;
	u32 count;
	u32 count_falses;
	u64 first_ts;
	u64 last_ts;
	u64 deadline_ts;
पूर्ण;

/**
 * काष्ठा pri_detector - PRI detector element क्रम a dedicated radar type
 * @निकास(): deकाष्ठाor
 * @add_pulse(): add pulse event, वापसs pri_sequence अगर pattern was detected
 * @reset(): clear states and reset to given समय stamp
 * @rs: detector specs क्रम this detector element
 * @last_ts: last pulse समय stamp considered क्रम this element in usecs
 * @sequences: list_head holding potential pulse sequences
 * @pulses: list connecting pulse_elem objects
 * @count: number of pulses in queue
 * @max_count: maximum number of pulses to be queued
 * @winकरोw_size: winकरोw size back from newest pulse समय stamp in usecs
 */
काष्ठा pri_detector अणु
	व्योम (*निकास)     (काष्ठा pri_detector *de);
	काष्ठा pri_sequence *
	     (*add_pulse)(काष्ठा pri_detector *de, काष्ठा pulse_event *e);
	व्योम (*reset)    (काष्ठा pri_detector *de, u64 ts);

	स्थिर काष्ठा radar_detector_specs *rs;

/* निजी: पूर्णांकernal use only */
	u64 last_ts;
	काष्ठा list_head sequences;
	काष्ठा list_head pulses;
	u32 count;
	u32 max_count;
	u32 winकरोw_size;
पूर्ण;

काष्ठा pri_detector *pri_detector_init(स्थिर काष्ठा radar_detector_specs *rs);

#पूर्ण_अगर /* DFS_PRI_DETECTOR_H */
