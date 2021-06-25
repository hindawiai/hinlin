<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_proc.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#समावेश <linux/module.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/drbd.h>
#समावेश "drbd_int.h"

काष्ठा proc_dir_entry *drbd_proc;

अटल व्योम seq_म_लिखो_with_thousands_grouping(काष्ठा seq_file *seq, दीर्घ v)
अणु
	/* v is in kB/sec. We करोn't expect TiByte/sec yet. */
	अगर (unlikely(v >= 1000000)) अणु
		/* cool: > GiByte/s */
		seq_म_लिखो(seq, "%ld,", v / 1000000);
		v %= 1000000;
		seq_म_लिखो(seq, "%03ld,%03ld", v/1000, v % 1000);
	पूर्ण अन्यथा अगर (likely(v >= 1000))
		seq_म_लिखो(seq, "%ld,%03ld", v/1000, v % 1000);
	अन्यथा
		seq_म_लिखो(seq, "%ld", v);
पूर्ण

अटल व्योम drbd_get_syncer_progress(काष्ठा drbd_device *device,
		जोड़ drbd_dev_state state, अचिन्हित दीर्घ *rs_total,
		अचिन्हित दीर्घ *bits_left, अचिन्हित पूर्णांक *per_mil_करोne)
अणु
	/* this is to अवरोध it at compile समय when we change that, in हाल we
	 * want to support more than (1<<32) bits on a 32bit arch. */
	typecheck(अचिन्हित दीर्घ, device->rs_total);
	*rs_total = device->rs_total;

	/* note: both rs_total and rs_left are in bits, i.e. in
	 * units of BM_BLOCK_SIZE.
	 * क्रम the percentage, we करोn't care. */

	अगर (state.conn == C_VERIFY_S || state.conn == C_VERIFY_T)
		*bits_left = device->ov_left;
	अन्यथा
		*bits_left = drbd_bm_total_weight(device) - device->rs_failed;
	/* >> 10 to prevent overflow,
	 * +1 to prevent भागision by zero */
	अगर (*bits_left > *rs_total) अणु
		/* D'oh. Maybe a logic bug somewhere.  More likely just a race
		 * between state change and reset of rs_total.
		 */
		*bits_left = *rs_total;
		*per_mil_करोne = *rs_total ? 0 : 1000;
	पूर्ण अन्यथा अणु
		/* Make sure the भागision happens in दीर्घ context.
		 * We allow up to one petabyte storage right now,
		 * at a granularity of 4k per bit that is 2**38 bits.
		 * After shअगरt right and multiplication by 1000,
		 * this should still fit easily पूर्णांकo a 32bit दीर्घ,
		 * so we करोn't need a 64bit भागision on 32bit arch.
		 * Note: currently we करोn't support such large biपंचांगaps on 32bit
		 * arch anyways, but no harm करोne to be prepared क्रम it here.
		 */
		अचिन्हित पूर्णांक shअगरt = *rs_total > अच_पूर्णांक_उच्च ? 16 : 10;
		अचिन्हित दीर्घ left = *bits_left >> shअगरt;
		अचिन्हित दीर्घ total = 1UL + (*rs_total >> shअगरt);
		अचिन्हित दीर्घ पंचांगp = 1000UL - left * 1000UL/total;
		*per_mil_करोne = पंचांगp;
	पूर्ण
पूर्ण


/*lge
 * progress bars shamelessly adapted from driver/md/md.c
 * output looks like
 *	[=====>..............] 33.5% (23456/123456)
 *	finish: 2:20:20 speed: 6,345 (6,456) K/sec
 */
अटल व्योम drbd_syncer_progress(काष्ठा drbd_device *device, काष्ठा seq_file *seq,
		जोड़ drbd_dev_state state)
अणु
	अचिन्हित दीर्घ db, dt, dbdt, rt, rs_total, rs_left;
	अचिन्हित पूर्णांक res;
	पूर्णांक i, x, y;
	पूर्णांक stalled = 0;

	drbd_get_syncer_progress(device, state, &rs_total, &rs_left, &res);

	x = res/50;
	y = 20-x;
	seq_माला_दो(seq, "\t[");
	क्रम (i = 1; i < x; i++)
		seq_अ_दो(seq, '=');
	seq_अ_दो(seq, '>');
	क्रम (i = 0; i < y; i++)
		seq_अ_दो(seq, '.');
	seq_माला_दो(seq, "] ");

	अगर (state.conn == C_VERIFY_S || state.conn == C_VERIFY_T)
		seq_माला_दो(seq, "verified:");
	अन्यथा
		seq_माला_दो(seq, "sync'ed:");
	seq_म_लिखो(seq, "%3u.%u%% ", res / 10, res % 10);

	/* अगर more than a few GB, display in MB */
	अगर (rs_total > (4UL << (30 - BM_BLOCK_SHIFT)))
		seq_म_लिखो(seq, "(%lu/%lu)M",
			    (अचिन्हित दीर्घ) Bit2KB(rs_left >> 10),
			    (अचिन्हित दीर्घ) Bit2KB(rs_total >> 10));
	अन्यथा
		seq_म_लिखो(seq, "(%lu/%lu)K",
			    (अचिन्हित दीर्घ) Bit2KB(rs_left),
			    (अचिन्हित दीर्घ) Bit2KB(rs_total));

	seq_माला_दो(seq, "\n\t");

	/* see drivers/md/md.c
	 * We करो not want to overflow, so the order of opeअक्रमs and
	 * the * 100 / 100 trick are important. We करो a +1 to be
	 * safe against भागision by zero. We only estimate anyway.
	 *
	 * dt: समय from mark until now
	 * db: blocks written from mark until now
	 * rt: reमुख्यing समय
	 */
	/* Rolling marks. last_mark+1 may just now be modअगरied.  last_mark+2 is
	 * at least (DRBD_SYNC_MARKS-2)*DRBD_SYNC_MARK_STEP old, and has at
	 * least DRBD_SYNC_MARK_STEP समय beक्रमe it will be modअगरied. */
	/* ------------------------ ~18s average ------------------------ */
	i = (device->rs_last_mark + 2) % DRBD_SYNC_MARKS;
	dt = (jअगरfies - device->rs_mark_समय[i]) / HZ;
	अगर (dt > 180)
		stalled = 1;

	अगर (!dt)
		dt++;
	db = device->rs_mark_left[i] - rs_left;
	rt = (dt * (rs_left / (db/100+1)))/100; /* seconds */

	seq_म_लिखो(seq, "finish: %lu:%02lu:%02lu",
		rt / 3600, (rt % 3600) / 60, rt % 60);

	dbdt = Bit2KB(db/dt);
	seq_माला_दो(seq, " speed: ");
	seq_म_लिखो_with_thousands_grouping(seq, dbdt);
	seq_माला_दो(seq, " (");
	/* ------------------------- ~3s average ------------------------ */
	अगर (drbd_proc_details >= 1) अणु
		/* this is what drbd_rs_should_slow_करोwn() uses */
		i = (device->rs_last_mark + DRBD_SYNC_MARKS-1) % DRBD_SYNC_MARKS;
		dt = (jअगरfies - device->rs_mark_समय[i]) / HZ;
		अगर (!dt)
			dt++;
		db = device->rs_mark_left[i] - rs_left;
		dbdt = Bit2KB(db/dt);
		seq_म_लिखो_with_thousands_grouping(seq, dbdt);
		seq_माला_दो(seq, " -- ");
	पूर्ण

	/* --------------------- दीर्घ term average ---------------------- */
	/* mean speed since syncer started
	 * we करो account क्रम PausedSync periods */
	dt = (jअगरfies - device->rs_start - device->rs_छोड़ोd) / HZ;
	अगर (dt == 0)
		dt = 1;
	db = rs_total - rs_left;
	dbdt = Bit2KB(db/dt);
	seq_म_लिखो_with_thousands_grouping(seq, dbdt);
	seq_अ_दो(seq, ')');

	अगर (state.conn == C_SYNC_TARGET ||
	    state.conn == C_VERIFY_S) अणु
		seq_माला_दो(seq, " want: ");
		seq_म_लिखो_with_thousands_grouping(seq, device->c_sync_rate);
	पूर्ण
	seq_म_लिखो(seq, " K/sec%s\n", stalled ? " (stalled)" : "");

	अगर (drbd_proc_details >= 1) अणु
		/* 64 bit:
		 * we convert to sectors in the display below. */
		अचिन्हित दीर्घ bm_bits = drbd_bm_bits(device);
		अचिन्हित दीर्घ bit_pos;
		अचिन्हित दीर्घ दीर्घ stop_sector = 0;
		अगर (state.conn == C_VERIFY_S ||
		    state.conn == C_VERIFY_T) अणु
			bit_pos = bm_bits - device->ov_left;
			अगर (verअगरy_can_करो_stop_sector(device))
				stop_sector = device->ov_stop_sector;
		पूर्ण अन्यथा
			bit_pos = device->bm_resync_fo;
		/* Total sectors may be slightly off क्रम oddly
		 * sized devices. So what. */
		seq_म_लिखो(seq,
			"\t%3d%% sector pos: %llu/%llu",
			(पूर्णांक)(bit_pos / (bm_bits/100+1)),
			(अचिन्हित दीर्घ दीर्घ)bit_pos * BM_SECT_PER_BIT,
			(अचिन्हित दीर्घ दीर्घ)bm_bits * BM_SECT_PER_BIT);
		अगर (stop_sector != 0 && stop_sector != ULदीर्घ_उच्च)
			seq_म_लिखो(seq, " stop sector: %llu", stop_sector);
		seq_अ_दो(seq, '\n');
	पूर्ण
पूर्ण

पूर्णांक drbd_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i, prev_i = -1;
	स्थिर अक्षर *sn;
	काष्ठा drbd_device *device;
	काष्ठा net_conf *nc;
	जोड़ drbd_dev_state state;
	अक्षर wp;

	अटल अक्षर ग_लिखो_ordering_अक्षरs[] = अणु
		[WO_NONE] = 'n',
		[WO_DRAIN_IO] = 'd',
		[WO_BDEV_FLUSH] = 'f',
	पूर्ण;

	seq_म_लिखो(seq, "version: " REL_VERSION " (api:%d/proto:%d-%d)\n%s\n",
		   API_VERSION, PRO_VERSION_MIN, PRO_VERSION_MAX, drbd_buildtag());

	/*
	  cs .. connection state
	  ro .. node role (local/remote)
	  ds .. disk state (local/remote)
	     protocol
	     various flags
	  ns .. network send
	  nr .. network receive
	  dw .. disk ग_लिखो
	  dr .. disk पढ़ो
	  al .. activity log ग_लिखो count
	  bm .. biपंचांगap update ग_लिखो count
	  pe .. pending (रुकोing क्रम ack or data reply)
	  ua .. unack'd (still need to send ack or data reply)
	  ap .. application requests accepted, but not yet completed
	  ep .. number of epochs currently "on the fly", P_BARRIER_ACK pending
	  wo .. ग_लिखो ordering mode currently in use
	 oos .. known out-of-sync kB
	*/

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&drbd_devices, device, i) अणु
		अगर (prev_i != i - 1)
			seq_अ_दो(seq, '\n');
		prev_i = i;

		state = device->state;
		sn = drbd_conn_str(state.conn);

		अगर (state.conn == C_STANDALONE &&
		    state.disk == D_DISKLESS &&
		    state.role == R_SECONDARY) अणु
			seq_म_लिखो(seq, "%2d: cs:Unconfigured\n", i);
		पूर्ण अन्यथा अणु
			/* reset device->congestion_reason */

			nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
			wp = nc ? nc->wire_protocol - DRBD_PROT_A + 'A' : ' ';
			seq_म_लिखो(seq,
			   "%2d: cs:%s ro:%s/%s ds:%s/%s %c %c%c%c%c%c%c\n"
			   "    ns:%u nr:%u dw:%u dr:%u al:%u bm:%u "
			   "lo:%d pe:%d ua:%d ap:%d ep:%d wo:%c",
			   i, sn,
			   drbd_role_str(state.role),
			   drbd_role_str(state.peer),
			   drbd_disk_str(state.disk),
			   drbd_disk_str(state.pdsk),
			   wp,
			   drbd_suspended(device) ? 's' : 'r',
			   state.aftr_isp ? 'a' : '-',
			   state.peer_isp ? 'p' : '-',
			   state.user_isp ? 'u' : '-',
			   device->congestion_reason ?: '-',
			   test_bit(AL_SUSPENDED, &device->flags) ? 's' : '-',
			   device->send_cnt/2,
			   device->recv_cnt/2,
			   device->writ_cnt/2,
			   device->पढ़ो_cnt/2,
			   device->al_writ_cnt,
			   device->bm_writ_cnt,
			   atomic_पढ़ो(&device->local_cnt),
			   atomic_पढ़ो(&device->ap_pending_cnt) +
			   atomic_पढ़ो(&device->rs_pending_cnt),
			   atomic_पढ़ो(&device->unacked_cnt),
			   atomic_पढ़ो(&device->ap_bio_cnt),
			   first_peer_device(device)->connection->epochs,
			   ग_लिखो_ordering_अक्षरs[device->resource->ग_लिखो_ordering]
			);
			seq_म_लिखो(seq, " oos:%llu\n",
				   Bit2KB((अचिन्हित दीर्घ दीर्घ)
					   drbd_bm_total_weight(device)));
		पूर्ण
		अगर (state.conn == C_SYNC_SOURCE ||
		    state.conn == C_SYNC_TARGET ||
		    state.conn == C_VERIFY_S ||
		    state.conn == C_VERIFY_T)
			drbd_syncer_progress(device, seq, state);

		अगर (drbd_proc_details >= 1 && get_ldev_अगर_state(device, D_FAILED)) अणु
			lc_seq_म_लिखो_stats(seq, device->resync);
			lc_seq_म_लिखो_stats(seq, device->act_log);
			put_ldev(device);
		पूर्ण

		अगर (drbd_proc_details >= 2)
			seq_म_लिखो(seq, "\tblocked on activity log: %d\n", atomic_पढ़ो(&device->ap_actlog_cnt));
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण
