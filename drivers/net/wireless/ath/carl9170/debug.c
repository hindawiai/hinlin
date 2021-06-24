<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * debug(fs) probing
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2008-2009 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "carl9170.h"
#समावेश "cmd.h"

#घोषणा ADD(buf, off, max, fmt, args...)				\
	off += scnम_लिखो(&buf[off], max - off, fmt, ##args)


काष्ठा carl9170_debugfs_fops अणु
	अचिन्हित पूर्णांक पढ़ो_bufsize;
	umode_t attr;
	अक्षर *(*पढ़ो)(काष्ठा ar9170 *ar, अक्षर *buf, माप_प्रकार bufsize,
		      sमाप_प्रकार *len);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा ar9170 *aru, स्थिर अक्षर *buf, माप_प्रकार size);
	स्थिर काष्ठा file_operations fops;

	क्रमागत carl9170_device_state req_dev_state;
पूर्ण;

अटल sमाप_प्रकार carl9170_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा carl9170_debugfs_fops *dfops;
	काष्ठा ar9170 *ar;
	अक्षर *buf = शून्य, *res_buf = शून्य;
	sमाप_प्रकार ret = 0;
	पूर्णांक err = 0;

	अगर (!count)
		वापस 0;

	ar = file->निजी_data;

	अगर (!ar)
		वापस -ENODEV;
	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा carl9170_debugfs_fops, fops);

	अगर (!dfops->पढ़ो)
		वापस -ENOSYS;

	अगर (dfops->पढ़ो_bufsize) अणु
		buf = vदो_स्मृति(dfops->पढ़ो_bufsize);
		अगर (!buf)
			वापस -ENOMEM;
	पूर्ण

	mutex_lock(&ar->mutex);
	अगर (!CHK_DEV_STATE(ar, dfops->req_dev_state)) अणु
		err = -ENODEV;
		res_buf = buf;
		जाओ out_मुक्त;
	पूर्ण

	res_buf = dfops->पढ़ो(ar, buf, dfops->पढ़ो_bufsize, &ret);

	अगर (ret > 0)
		err = simple_पढ़ो_from_buffer(userbuf, count, ppos,
					      res_buf, ret);
	अन्यथा
		err = ret;

	WARN_ON_ONCE(dfops->पढ़ो_bufsize && (res_buf != buf));

out_मुक्त:
	vमुक्त(res_buf);
	mutex_unlock(&ar->mutex);
	वापस err;
पूर्ण

अटल sमाप_प्रकार carl9170_debugfs_ग_लिखो(काष्ठा file *file,
	स्थिर अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा carl9170_debugfs_fops *dfops;
	काष्ठा ar9170 *ar;
	अक्षर *buf = शून्य;
	पूर्णांक err = 0;

	अगर (!count)
		वापस 0;

	अगर (count > PAGE_SIZE)
		वापस -E2BIG;

	ar = file->निजी_data;

	अगर (!ar)
		वापस -ENODEV;
	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा carl9170_debugfs_fops, fops);

	अगर (!dfops->ग_लिखो)
		वापस -ENOSYS;

	buf = vदो_स्मृति(count);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_user(buf, userbuf, count)) अणु
		err = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	अगर (mutex_trylock(&ar->mutex) == 0) अणु
		err = -EAGAIN;
		जाओ out_मुक्त;
	पूर्ण

	अगर (!CHK_DEV_STATE(ar, dfops->req_dev_state)) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	err = dfops->ग_लिखो(ar, buf, count);
	अगर (err)
		जाओ out_unlock;

out_unlock:
	mutex_unlock(&ar->mutex);

out_मुक्त:
	vमुक्त(buf);
	वापस err;
पूर्ण

#घोषणा __DEBUGFS_DECLARE_खाता(name, _पढ़ो, _ग_लिखो, _पढ़ो_bufsize,	\
			       _attr, _dstate)				\
अटल स्थिर काष्ठा carl9170_debugfs_fops carl_debugfs_##name ##_ops = अणु\
	.पढ़ो_bufsize = _पढ़ो_bufsize,					\
	.पढ़ो = _पढ़ो,							\
	.ग_लिखो = _ग_लिखो,						\
	.attr = _attr,							\
	.req_dev_state = _dstate,					\
	.fops = अणु							\
		.खोलो	= simple_खोलो,					\
		.पढ़ो	= carl9170_debugfs_पढ़ो,			\
		.ग_लिखो	= carl9170_debugfs_ग_लिखो,			\
		.owner	= THIS_MODULE					\
	पूर्ण,								\
पूर्ण

#घोषणा DEBUGFS_DECLARE_खाता(name, _पढ़ो, _ग_लिखो, _पढ़ो_bufsize, _attr)	\
	__DEBUGFS_DECLARE_खाता(name, _पढ़ो, _ग_लिखो, _पढ़ो_bufsize,	\
			       _attr, CARL9170_STARTED)			\

#घोषणा DEBUGFS_DECLARE_RO_खाता(name, _पढ़ो_bufsize)			\
	DEBUGFS_DECLARE_खाता(name, carl9170_debugfs_##name ##_पढ़ो,	\
			     शून्य, _पढ़ो_bufsize, 0400)

#घोषणा DEBUGFS_DECLARE_WO_खाता(name)					\
	DEBUGFS_DECLARE_खाता(name, शून्य, carl9170_debugfs_##name ##_ग_लिखो,\
			     0, 0200)

#घोषणा DEBUGFS_DECLARE_RW_खाता(name, _पढ़ो_bufsize)			\
	DEBUGFS_DECLARE_खाता(name, carl9170_debugfs_##name ##_पढ़ो,	\
			     carl9170_debugfs_##name ##_ग_लिखो,		\
			     _पढ़ो_bufsize, 0600)

#घोषणा __DEBUGFS_DECLARE_RW_खाता(name, _पढ़ो_bufsize, _dstate)		\
	__DEBUGFS_DECLARE_खाता(name, carl9170_debugfs_##name ##_पढ़ो,	\
			     carl9170_debugfs_##name ##_ग_लिखो,		\
			     _पढ़ो_bufsize, 0600, _dstate)

#घोषणा DEBUGFS_READONLY_खाता(name, _पढ़ो_bufsize, fmt, value...)	\
अटल अक्षर *carl9170_debugfs_ ##name ## _पढ़ो(काष्ठा ar9170 *ar,	\
					     अक्षर *buf, माप_प्रकार buf_size,\
					     sमाप_प्रकार *len)		\
अणु									\
	ADD(buf, *len, buf_size, fmt "\n", ##value);			\
	वापस buf;							\
पूर्ण									\
DEBUGFS_DECLARE_RO_खाता(name, _पढ़ो_bufsize)

अटल अक्षर *carl9170_debugfs_mem_usage_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					     माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	spin_lock_bh(&ar->mem_lock);

	ADD(buf, *len, bufsize, "jar: [%*pb]\n",
	    ar->fw.mem_blocks, ar->mem_biपंचांगap);

	ADD(buf, *len, bufsize, "cookies: used:%3d / total:%3d, allocs:%d\n",
	    biपंचांगap_weight(ar->mem_biपंचांगap, ar->fw.mem_blocks),
	    ar->fw.mem_blocks, atomic_पढ़ो(&ar->mem_allocs));

	ADD(buf, *len, bufsize, "memory: free:%3d (%3d KiB) / total:%3d KiB)\n",
	    atomic_पढ़ो(&ar->mem_मुक्त_blocks),
	    (atomic_पढ़ो(&ar->mem_मुक्त_blocks) * ar->fw.mem_block_size) / 1024,
	    (ar->fw.mem_blocks * ar->fw.mem_block_size) / 1024);

	spin_unlock_bh(&ar->mem_lock);

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(mem_usage, 512);

अटल अक्षर *carl9170_debugfs_qos_stat_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					    माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	ADD(buf, *len, bufsize, "%s QoS AC\n", modparam_noht ? "Hardware" :
	    "Software");

	ADD(buf, *len, bufsize, "[     VO            VI       "
				 "     BE            BK      ]\n");

	spin_lock_bh(&ar->tx_stats_lock);
	ADD(buf, *len, bufsize, "[length/limit  length/limit  "
				 "length/limit  length/limit ]\n"
				"[   %3d/%3d       %3d/%3d    "
				 "   %3d/%3d       %3d/%3d   ]\n\n",
	    ar->tx_stats[0].len, ar->tx_stats[0].limit,
	    ar->tx_stats[1].len, ar->tx_stats[1].limit,
	    ar->tx_stats[2].len, ar->tx_stats[2].limit,
	    ar->tx_stats[3].len, ar->tx_stats[3].limit);

	ADD(buf, *len, bufsize, "[    total         total     "
				 "    total         total    ]\n"
				"[%10d    %10d    %10d    %10d   ]\n\n",
	    ar->tx_stats[0].count, ar->tx_stats[1].count,
	    ar->tx_stats[2].count, ar->tx_stats[3].count);

	spin_unlock_bh(&ar->tx_stats_lock);

	ADD(buf, *len, bufsize, "[  pend/waittx   pend/waittx "
				 "  pend/waittx   pend/waittx]\n"
				"[   %3d/%3d       %3d/%3d    "
				 "   %3d/%3d       %3d/%3d   ]\n\n",
	    skb_queue_len(&ar->tx_pending[0]),
	    skb_queue_len(&ar->tx_status[0]),
	    skb_queue_len(&ar->tx_pending[1]),
	    skb_queue_len(&ar->tx_status[1]),
	    skb_queue_len(&ar->tx_pending[2]),
	    skb_queue_len(&ar->tx_status[2]),
	    skb_queue_len(&ar->tx_pending[3]),
	    skb_queue_len(&ar->tx_status[3]));

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(qos_stat, 512);

अटल व्योम carl9170_debugfs_क्रमmat_frame(काष्ठा ar9170 *ar,
	काष्ठा sk_buff *skb, स्थिर अक्षर *prefix, अक्षर *buf,
	sमाप_प्रकार *off, sमाप_प्रकार bufsize)
अणु
	काष्ठा _carl9170_tx_superframe *txc = (व्योम *) skb->data;
	काष्ठा ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);
	काष्ठा carl9170_tx_info *arinfo = (व्योम *) txinfo->rate_driver_data;
	काष्ठा ieee80211_hdr *hdr = (व्योम *) txc->frame_data;

	ADD(buf, *off, bufsize, "%s %p, c:%2x, DA:%pM, sq:%4d, mc:%.4x, "
	    "pc:%.8x, to:%d ms\n", prefix, skb, txc->s.cookie,
	    ieee80211_get_DA(hdr), get_seq_h(hdr),
	    le16_to_cpu(txc->f.mac_control), le32_to_cpu(txc->f.phy_control),
	    jअगरfies_to_msecs(jअगरfies - arinfo->समयout));
पूर्ण


अटल अक्षर *carl9170_debugfs_ampdu_state_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					       माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	काष्ठा carl9170_sta_tid *iter;
	काष्ठा sk_buff *skb;
	पूर्णांक cnt = 0, fc;
	पूर्णांक offset;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter, &ar->tx_ampdu_list, list) अणु

		spin_lock_bh(&iter->lock);
		ADD(buf, *len, bufsize, "Entry: #%2d TID:%1d, BSN:%4d, "
		    "SNX:%4d, HSN:%4d, BAW:%2d, state:%1d, toggles:%d\n",
		    cnt, iter->tid, iter->bsn, iter->snx, iter->hsn,
		    iter->max, iter->state, iter->counter);

		ADD(buf, *len, bufsize, "\tWindow:  [%*pb,W]\n",
		    CARL9170_BAW_BITS, iter->biपंचांगap);

#घोषणा BM_STR_OFF(offset)					\
	((CARL9170_BAW_BITS - (offset) - 1) / 4 +		\
	 (CARL9170_BAW_BITS - (offset) - 1) / 32 + 1)

		offset = BM_STR_OFF(0);
		ADD(buf, *len, bufsize, "\tBase Seq: %*s\n", offset, "T");

		offset = BM_STR_OFF(SEQ_DIFF(iter->snx, iter->bsn));
		ADD(buf, *len, bufsize, "\tNext Seq: %*s\n", offset, "W");

		offset = BM_STR_OFF(((पूर्णांक)iter->hsn - (पूर्णांक)iter->bsn) %
				     CARL9170_BAW_BITS);
		ADD(buf, *len, bufsize, "\tLast Seq: %*s\n", offset, "N");

		ADD(buf, *len, bufsize, "\tPre-Aggregation reorder buffer: "
		    " currently queued:%d\n", skb_queue_len(&iter->queue));

		fc = 0;
		skb_queue_walk(&iter->queue, skb) अणु
			अक्षर prefix[32];

			snम_लिखो(prefix, माप(prefix), "\t\t%3d :", fc);
			carl9170_debugfs_क्रमmat_frame(ar, skb, prefix, buf,
						      len, bufsize);

			fc++;
		पूर्ण
		spin_unlock_bh(&iter->lock);
		cnt++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(ampdu_state, 8000);

अटल व्योम carl9170_debugfs_queue_dump(काष्ठा ar9170 *ar, अक्षर *buf,
	sमाप_प्रकार *len, माप_प्रकार bufsize, काष्ठा sk_buff_head *queue)
अणु
	काष्ठा sk_buff *skb;
	अक्षर prefix[16];
	पूर्णांक fc = 0;

	spin_lock_bh(&queue->lock);
	skb_queue_walk(queue, skb) अणु
		snम_लिखो(prefix, माप(prefix), "%3d :", fc);
		carl9170_debugfs_क्रमmat_frame(ar, skb, prefix, buf,
					      len, bufsize);
		fc++;
	पूर्ण
	spin_unlock_bh(&queue->lock);
पूर्ण

#घोषणा DEBUGFS_QUEUE_DUMP(q, qi)					\
अटल अक्षर *carl9170_debugfs_##q ##_##qi ##_पढ़ो(काष्ठा ar9170 *ar,	\
	अक्षर *buf, माप_प्रकार bufsize, sमाप_प्रकार *len)			\
अणु									\
	carl9170_debugfs_queue_dump(ar, buf, len, bufsize, &ar->q[qi]);	\
	वापस buf;							\
पूर्ण									\
DEBUGFS_DECLARE_RO_खाता(q##_##qi, 8000);

अटल अक्षर *carl9170_debugfs_sta_psm_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					   माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	ADD(buf, *len, bufsize, "psm state: %s\n", (ar->ps.off_override ?
	    "FORCE CAM" : (ar->ps.state ? "PSM" : "CAM")));

	ADD(buf, *len, bufsize, "sleep duration: %d ms.\n", ar->ps.sleep_ms);
	ADD(buf, *len, bufsize, "last power-state transition: %d ms ago.\n",
	    jअगरfies_to_msecs(jअगरfies - ar->ps.last_action));
	ADD(buf, *len, bufsize, "last CAM->PSM transition: %d ms ago.\n",
	    jअगरfies_to_msecs(jअगरfies - ar->ps.last_slept));

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(sta_psm, 160);

अटल अक्षर *carl9170_debugfs_tx_stuck_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					    माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ar->hw->queues; i++) अणु
		ADD(buf, *len, bufsize, "TX queue [%d]: %10d max:%10d ms.\n",
		    i, ieee80211_queue_stopped(ar->hw, i) ?
		    jअगरfies_to_msecs(jअगरfies - ar->queue_stop_समयout[i]) : 0,
		    jअगरfies_to_msecs(ar->max_queue_stop_समयout[i]));

		ar->max_queue_stop_समयout[i] = 0;
	पूर्ण

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(tx_stuck, 180);

अटल अक्षर *carl9170_debugfs_phy_noise_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					     माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	पूर्णांक err;

	err = carl9170_get_noiseन्यूनमान(ar);
	अगर (err) अणु
		*len = err;
		वापस buf;
	पूर्ण

	ADD(buf, *len, bufsize, "Chain 0: %10d dBm, ext. chan.:%10d dBm\n",
	    ar->noise[0], ar->noise[2]);
	ADD(buf, *len, bufsize, "Chain 2: %10d dBm, ext. chan.:%10d dBm\n",
	    ar->noise[1], ar->noise[3]);

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(phy_noise, 180);

अटल अक्षर *carl9170_debugfs_vअगर_dump_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					    माप_प्रकार bufsize, sमाप_प्रकार *len)
अणु
	काष्ठा carl9170_vअगर_info *iter;
	पूर्णांक i = 0;

	ADD(buf, *len, bufsize, "registered VIFs:%d \\ %d\n",
	    ar->vअगरs, ar->fw.vअगर_num);

	ADD(buf, *len, bufsize, "VIF bitmap: [%*pb]\n",
	    ar->fw.vअगर_num, &ar->vअगर_biपंचांगap);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter, &ar->vअगर_list, list) अणु
		काष्ठा ieee80211_vअगर *vअगर = carl9170_get_vअगर(iter);
		ADD(buf, *len, bufsize, "\t%d = [%s VIF, id:%d, type:%x "
		    " mac:%pM %s]\n", i, (carl9170_get_मुख्य_vअगर(ar) == vअगर ?
		    "Master" : " Slave"), iter->id, vअगर->type, vअगर->addr,
		    iter->enable_beacon ? "beaconing " : "");
		i++;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RO_खाता(vअगर_dump, 8000);

#घोषणा UPDATE_COUNTER(ar, name)	(अणु				\
	u32 __पंचांगp[ARRAY_SIZE(name##_regs)];				\
	अचिन्हित पूर्णांक __i, __err = -ENODEV;				\
									\
	क्रम (__i = 0; __i < ARRAY_SIZE(name##_regs); __i++) अणु		\
		__पंचांगp[__i] = name##_regs[__i].reg;			\
		ar->debug.stats.name##_counter[__i] = 0;		\
	पूर्ण								\
									\
	अगर (IS_STARTED(ar))						\
		__err = carl9170_पढ़ो_mreg(ar, ARRAY_SIZE(name##_regs),	\
			__पंचांगp, ar->debug.stats.name##_counter);		\
	(__err); पूर्ण)

#घोषणा TALLY_SUM_UP(ar, name)	करो अणु					\
	अचिन्हित पूर्णांक __i;						\
									\
	क्रम (__i = 0; __i < ARRAY_SIZE(name##_regs); __i++) अणु		\
		ar->debug.stats.name##_sum[__i] +=			\
			ar->debug.stats.name##_counter[__i];		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा DEBUGFS_HW_TALLY_खाता(name, f)					\
अटल अक्षर *carl9170_debugfs_##name ## _पढ़ो(काष्ठा ar9170 *ar,	\
	 अक्षर *dum, माप_प्रकार bufsize, sमाप_प्रकार *ret)			\
अणु									\
	अक्षर *buf;							\
	पूर्णांक i, max_len, err;						\
									\
	max_len = ARRAY_SIZE(name##_regs) * 80;				\
	buf = vदो_स्मृति(max_len);						\
	अगर (!buf)							\
		वापस शून्य;						\
									\
	err = UPDATE_COUNTER(ar, name);					\
	अगर (err) अणु							\
		*ret = err;						\
		वापस buf;						\
	पूर्ण								\
									\
	TALLY_SUM_UP(ar, name);						\
									\
	क्रम (i = 0; i < ARRAY_SIZE(name##_regs); i++) अणु			\
		ADD(buf, *ret, max_len, "%22s = %" f "[+%" f "]\n",	\
		    name##_regs[i].nreg, ar->debug.stats.name ##_sum[i],\
		    ar->debug.stats.name ##_counter[i]);		\
	पूर्ण								\
									\
	वापस buf;							\
पूर्ण									\
DEBUGFS_DECLARE_RO_खाता(name, 0);

#घोषणा DEBUGFS_HW_REG_खाता(name, f)					\
अटल अक्षर *carl9170_debugfs_##name ## _पढ़ो(काष्ठा ar9170 *ar,	\
	अक्षर *dum, माप_प्रकार bufsize, sमाप_प्रकार *ret)			\
अणु									\
	अक्षर *buf;							\
	पूर्णांक i, max_len, err;						\
									\
	max_len = ARRAY_SIZE(name##_regs) * 80;				\
	buf = vदो_स्मृति(max_len);						\
	अगर (!buf)							\
		वापस शून्य;						\
									\
	err = UPDATE_COUNTER(ar, name);					\
	अगर (err) अणु							\
		*ret = err;						\
		वापस buf;						\
	पूर्ण								\
									\
	क्रम (i = 0; i < ARRAY_SIZE(name##_regs); i++) अणु			\
		ADD(buf, *ret, max_len, "%22s = %" f "\n",		\
		    name##_regs[i].nreg,				\
		    ar->debug.stats.name##_counter[i]);			\
	पूर्ण								\
									\
	वापस buf;							\
पूर्ण									\
DEBUGFS_DECLARE_RO_खाता(name, 0);

अटल sमाप_प्रकार carl9170_debugfs_hw_ioपढ़ो32_ग_लिखो(काष्ठा ar9170 *ar,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err = 0, i, n = 0, max_len = 32, res;
	अचिन्हित पूर्णांक reg, पंचांगp;

	अगर (!count)
		वापस 0;

	अगर (count > max_len)
		वापस -E2BIG;

	res = माला_पूछो(buf, "0x%X %d", &reg, &n);
	अगर (res < 1) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (res == 1)
		n = 1;

	अगर (n > 15) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	अगर ((reg >= 0x280000) || ((reg + (n << 2)) >= 0x280000)) अणु
		err = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	अगर (reg & 3) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		err = carl9170_पढ़ो_reg(ar, reg + (i << 2), &पंचांगp);
		अगर (err)
			जाओ out;

		ar->debug.ring[ar->debug.ring_tail].reg = reg + (i << 2);
		ar->debug.ring[ar->debug.ring_tail].value = पंचांगp;
		ar->debug.ring_tail++;
		ar->debug.ring_tail %= CARL9170_DEBUG_RING_SIZE;
	पूर्ण

out:
	वापस err ? err : count;
पूर्ण

अटल अक्षर *carl9170_debugfs_hw_ioपढ़ो32_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
					       माप_प्रकार bufsize, sमाप_प्रकार *ret)
अणु
	पूर्णांक i = 0;

	जबतक (ar->debug.ring_head != ar->debug.ring_tail) अणु
		ADD(buf, *ret, bufsize, "%.8x = %.8x\n",
		    ar->debug.ring[ar->debug.ring_head].reg,
		    ar->debug.ring[ar->debug.ring_head].value);

		ar->debug.ring_head++;
		ar->debug.ring_head %= CARL9170_DEBUG_RING_SIZE;

		अगर (i++ == 64)
			अवरोध;
	पूर्ण
	ar->debug.ring_head = ar->debug.ring_tail;
	वापस buf;
पूर्ण
DEBUGFS_DECLARE_RW_खाता(hw_ioपढ़ो32, CARL9170_DEBUG_RING_SIZE * 40);

अटल sमाप_प्रकार carl9170_debugfs_bug_ग_लिखो(काष्ठा ar9170 *ar, स्थिर अक्षर *buf,
					  माप_प्रकार count)
अणु
	पूर्णांक err;

	अगर (count < 1)
		वापस -EINVAL;

	चयन (buf[0]) अणु
	हाल 'F':
		ar->needs_full_reset = true;
		अवरोध;

	हाल 'R':
		अगर (!IS_STARTED(ar)) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण

		ar->needs_full_reset = false;
		अवरोध;

	हाल 'M':
		err = carl9170_mac_reset(ar);
		अगर (err < 0)
			count = err;

		जाओ out;

	हाल 'P':
		err = carl9170_set_channel(ar, ar->hw->conf.chandef.chan,
			cfg80211_get_chandef_type(&ar->hw->conf.chandef));
		अगर (err < 0)
			count = err;

		जाओ out;

	शेष:
		वापस -EINVAL;
	पूर्ण

	carl9170_restart(ar, CARL9170_RR_USER_REQUEST);

out:
	वापस count;
पूर्ण

अटल अक्षर *carl9170_debugfs_bug_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
				       माप_प्रकार bufsize, sमाप_प्रकार *ret)
अणु
	ADD(buf, *ret, bufsize, "[P]hy reinit, [R]estart, [F]ull usb reset, "
	    "[M]ac reset\n");
	ADD(buf, *ret, bufsize, "firmware restarts:%d, last reason:%d\n",
		ar->restart_counter, ar->last_reason);
	ADD(buf, *ret, bufsize, "phy reinit errors:%d (%d)\n",
		ar->total_chan_fail, ar->chan_fail);
	ADD(buf, *ret, bufsize, "reported firmware errors:%d\n",
		ar->fw.err_counter);
	ADD(buf, *ret, bufsize, "reported firmware BUGs:%d\n",
		ar->fw.bug_counter);
	ADD(buf, *ret, bufsize, "pending restart requests:%d\n",
		atomic_पढ़ो(&ar->pending_restarts));
	वापस buf;
पूर्ण
__DEBUGFS_DECLARE_RW_खाता(bug, 400, CARL9170_STOPPED);

अटल स्थिर अक्षर *स्थिर erp_modes[] = अणु
	[CARL9170_ERP_INVALID] = "INVALID",
	[CARL9170_ERP_AUTO] = "Automatic",
	[CARL9170_ERP_MAC80211] = "Set by MAC80211",
	[CARL9170_ERP_OFF] = "Force Off",
	[CARL9170_ERP_RTS] = "Force RTS",
	[CARL9170_ERP_CTS] = "Force CTS"
पूर्ण;

अटल अक्षर *carl9170_debugfs_erp_पढ़ो(काष्ठा ar9170 *ar, अक्षर *buf,
				       माप_प्रकार bufsize, sमाप_प्रकार *ret)
अणु
	ADD(buf, *ret, bufsize, "ERP Setting: (%d) -> %s\n", ar->erp_mode,
	    erp_modes[ar->erp_mode]);
	वापस buf;
पूर्ण

अटल sमाप_प्रकार carl9170_debugfs_erp_ग_लिखो(काष्ठा ar9170 *ar, स्थिर अक्षर *buf,
					  माप_प्रकार count)
अणु
	पूर्णांक res, val;

	अगर (count < 1)
		वापस -EINVAL;

	res = माला_पूछो(buf, "%d", &val);
	अगर (res != 1)
		वापस -EINVAL;

	अगर (!((val > CARL9170_ERP_INVALID) &&
	      (val < __CARL9170_ERP_NUM)))
		वापस -EINVAL;

	ar->erp_mode = val;
	वापस count;
पूर्ण

DEBUGFS_DECLARE_RW_खाता(erp, 80);

अटल sमाप_प्रकार carl9170_debugfs_hw_ioग_लिखो32_ग_लिखो(काष्ठा ar9170 *ar,
	स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err = 0, max_len = 22, res;
	u32 reg, val;

	अगर (!count)
		वापस 0;

	अगर (count > max_len)
		वापस -E2BIG;

	res = माला_पूछो(buf, "0x%X 0x%X", &reg, &val);
	अगर (res != 2) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (reg <= 0x100000 || reg >= 0x280000) अणु
		err = -EADDRNOTAVAIL;
		जाओ out;
	पूर्ण

	अगर (reg & 3) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = carl9170_ग_लिखो_reg(ar, reg, val);
	अगर (err)
		जाओ out;

out:
	वापस err ? err : count;
पूर्ण
DEBUGFS_DECLARE_WO_खाता(hw_ioग_लिखो32);

DEBUGFS_HW_TALLY_खाता(hw_tx_tally, "u");
DEBUGFS_HW_TALLY_खाता(hw_rx_tally, "u");
DEBUGFS_HW_TALLY_खाता(hw_phy_errors, "u");
DEBUGFS_HW_REG_खाता(hw_wlan_queue, ".8x");
DEBUGFS_HW_REG_खाता(hw_pta_queue, ".8x");
DEBUGFS_HW_REG_खाता(hw_ampdu_info, ".8x");
DEBUGFS_QUEUE_DUMP(tx_status, 0);
DEBUGFS_QUEUE_DUMP(tx_status, 1);
DEBUGFS_QUEUE_DUMP(tx_status, 2);
DEBUGFS_QUEUE_DUMP(tx_status, 3);
DEBUGFS_QUEUE_DUMP(tx_pending, 0);
DEBUGFS_QUEUE_DUMP(tx_pending, 1);
DEBUGFS_QUEUE_DUMP(tx_pending, 2);
DEBUGFS_QUEUE_DUMP(tx_pending, 3);
DEBUGFS_READONLY_खाता(usb_tx_anch_urbs, 20, "%d",
		      atomic_पढ़ो(&ar->tx_anch_urbs));
DEBUGFS_READONLY_खाता(usb_rx_anch_urbs, 20, "%d",
		      atomic_पढ़ो(&ar->rx_anch_urbs));
DEBUGFS_READONLY_खाता(usb_rx_work_urbs, 20, "%d",
		      atomic_पढ़ो(&ar->rx_work_urbs));
DEBUGFS_READONLY_खाता(usb_rx_pool_urbs, 20, "%d",
		      atomic_पढ़ो(&ar->rx_pool_urbs));

DEBUGFS_READONLY_खाता(tx_total_queued, 20, "%d",
		      atomic_पढ़ो(&ar->tx_total_queued));
DEBUGFS_READONLY_खाता(tx_ampdu_scheduler, 20, "%d",
		      atomic_पढ़ो(&ar->tx_ampdu_scheduler));

DEBUGFS_READONLY_खाता(tx_total_pending, 20, "%d",
		      atomic_पढ़ो(&ar->tx_total_pending));

DEBUGFS_READONLY_खाता(tx_ampdu_list_len, 20, "%d",
		      ar->tx_ampdu_list_len);

DEBUGFS_READONLY_खाता(tx_ampdu_upload, 20, "%d",
		      atomic_पढ़ो(&ar->tx_ampdu_upload));

DEBUGFS_READONLY_खाता(tx_janitor_last_run, 64, "last run:%d ms ago",
	jअगरfies_to_msecs(jअगरfies - ar->tx_janitor_last_run));

DEBUGFS_READONLY_खाता(tx_dropped, 20, "%d", ar->tx_dropped);

DEBUGFS_READONLY_खाता(rx_dropped, 20, "%d", ar->rx_dropped);

DEBUGFS_READONLY_खाता(snअगरfer_enabled, 20, "%d", ar->snअगरfer_enabled);
DEBUGFS_READONLY_खाता(rx_software_decryption, 20, "%d",
		      ar->rx_software_decryption);
DEBUGFS_READONLY_खाता(ampdu_factor, 20, "%d",
		      ar->current_factor);
DEBUGFS_READONLY_खाता(ampdu_density, 20, "%d",
		      ar->current_density);

DEBUGFS_READONLY_खाता(beacon_पूर्णांक, 20, "%d TU", ar->global_beacon_पूर्णांक);
DEBUGFS_READONLY_खाता(pretbtt, 20, "%d TU", ar->global_pretbtt);

व्योम carl9170_debugfs_रेजिस्टर(काष्ठा ar9170 *ar)
अणु
	ar->debug_dir = debugfs_create_dir(KBUILD_MODNAME,
		ar->hw->wiphy->debugfsdir);

#घोषणा DEBUGFS_ADD(name)						\
	debugfs_create_file(#name, carl_debugfs_##name ##_ops.attr,	\
			    ar->debug_dir, ar,				\
			    &carl_debugfs_##name ## _ops.fops)

	DEBUGFS_ADD(usb_tx_anch_urbs);
	DEBUGFS_ADD(usb_rx_pool_urbs);
	DEBUGFS_ADD(usb_rx_anch_urbs);
	DEBUGFS_ADD(usb_rx_work_urbs);

	DEBUGFS_ADD(tx_total_queued);
	DEBUGFS_ADD(tx_total_pending);
	DEBUGFS_ADD(tx_dropped);
	DEBUGFS_ADD(tx_stuck);
	DEBUGFS_ADD(tx_ampdu_upload);
	DEBUGFS_ADD(tx_ampdu_scheduler);
	DEBUGFS_ADD(tx_ampdu_list_len);

	DEBUGFS_ADD(rx_dropped);
	DEBUGFS_ADD(snअगरfer_enabled);
	DEBUGFS_ADD(rx_software_decryption);

	DEBUGFS_ADD(mem_usage);
	DEBUGFS_ADD(qos_stat);
	DEBUGFS_ADD(sta_psm);
	DEBUGFS_ADD(ampdu_state);

	DEBUGFS_ADD(hw_tx_tally);
	DEBUGFS_ADD(hw_rx_tally);
	DEBUGFS_ADD(hw_phy_errors);
	DEBUGFS_ADD(phy_noise);

	DEBUGFS_ADD(hw_wlan_queue);
	DEBUGFS_ADD(hw_pta_queue);
	DEBUGFS_ADD(hw_ampdu_info);

	DEBUGFS_ADD(ampdu_density);
	DEBUGFS_ADD(ampdu_factor);

	DEBUGFS_ADD(tx_janitor_last_run);

	DEBUGFS_ADD(tx_status_0);
	DEBUGFS_ADD(tx_status_1);
	DEBUGFS_ADD(tx_status_2);
	DEBUGFS_ADD(tx_status_3);

	DEBUGFS_ADD(tx_pending_0);
	DEBUGFS_ADD(tx_pending_1);
	DEBUGFS_ADD(tx_pending_2);
	DEBUGFS_ADD(tx_pending_3);

	DEBUGFS_ADD(hw_ioपढ़ो32);
	DEBUGFS_ADD(hw_ioग_लिखो32);
	DEBUGFS_ADD(bug);

	DEBUGFS_ADD(erp);

	DEBUGFS_ADD(vअगर_dump);

	DEBUGFS_ADD(beacon_पूर्णांक);
	DEBUGFS_ADD(pretbtt);

#अघोषित DEBUGFS_ADD
पूर्ण

व्योम carl9170_debugfs_unरेजिस्टर(काष्ठा ar9170 *ar)
अणु
	debugfs_हटाओ_recursive(ar->debug_dir);
पूर्ण
