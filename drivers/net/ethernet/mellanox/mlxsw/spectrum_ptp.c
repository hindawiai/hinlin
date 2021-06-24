<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019 Mellanox Technologies. All rights reserved */

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/net_tstamp.h>

#समावेश "spectrum.h"
#समावेश "spectrum_ptp.h"
#समावेश "core.h"

#घोषणा MLXSW_SP1_PTP_CLOCK_CYCLES_SHIFT	29
#घोषणा MLXSW_SP1_PTP_CLOCK_FREQ_KHZ		156257 /* 6.4nSec */
#घोषणा MLXSW_SP1_PTP_CLOCK_MASK		64

#घोषणा MLXSW_SP1_PTP_HT_GC_INTERVAL		500 /* ms */

/* How दीर्घ, approximately, should the unmatched entries stay in the hash table
 * beक्रमe they are collected. Should be evenly भागisible by the GC पूर्णांकerval.
 */
#घोषणा MLXSW_SP1_PTP_HT_GC_TIMEOUT		1000 /* ms */

काष्ठा mlxsw_sp_ptp_state अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा rhltable unmatched_ht;
	spinlock_t unmatched_lock; /* protects the HT */
	काष्ठा delayed_work ht_gc_dw;
	u32 gc_cycle;
पूर्ण;

काष्ठा mlxsw_sp1_ptp_key अणु
	u8 local_port;
	u8 message_type;
	u16 sequence_id;
	u8 करोमुख्य_number;
	bool ingress;
पूर्ण;

काष्ठा mlxsw_sp1_ptp_unmatched अणु
	काष्ठा mlxsw_sp1_ptp_key key;
	काष्ठा rhlist_head ht_node;
	काष्ठा rcu_head rcu;
	काष्ठा sk_buff *skb;
	u64 बारtamp;
	u32 gc_cycle;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp1_ptp_unmatched_ht_params = अणु
	.key_len = माप_field(काष्ठा mlxsw_sp1_ptp_unmatched, key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp1_ptp_unmatched, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp1_ptp_unmatched, ht_node),
पूर्ण;

काष्ठा mlxsw_sp_ptp_घड़ी अणु
	काष्ठा mlxsw_core *core;
	spinlock_t lock; /* protect this काष्ठाure */
	काष्ठा cyclecounter cycles;
	काष्ठा समयcounter tc;
	u32 nominal_c_mult;
	काष्ठा ptp_घड़ी *ptp;
	काष्ठा ptp_घड़ी_info ptp_info;
	अचिन्हित दीर्घ overflow_period;
	काष्ठा delayed_work overflow_work;
पूर्ण;

अटल u64 __mlxsw_sp1_ptp_पढ़ो_frc(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी,
				    काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा mlxsw_core *mlxsw_core = घड़ी->core;
	u32 frc_h1, frc_h2, frc_l;

	frc_h1 = mlxsw_core_पढ़ो_frc_h(mlxsw_core);
	ptp_पढ़ो_प्रणाली_prets(sts);
	frc_l = mlxsw_core_पढ़ो_frc_l(mlxsw_core);
	ptp_पढ़ो_प्रणाली_postts(sts);
	frc_h2 = mlxsw_core_पढ़ो_frc_h(mlxsw_core);

	अगर (frc_h1 != frc_h2) अणु
		/* wrap around */
		ptp_पढ़ो_प्रणाली_prets(sts);
		frc_l = mlxsw_core_पढ़ो_frc_l(mlxsw_core);
		ptp_पढ़ो_प्रणाली_postts(sts);
	पूर्ण

	वापस (u64) frc_l | (u64) frc_h2 << 32;
पूर्ण

अटल u64 mlxsw_sp1_ptp_पढ़ो_frc(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी =
		container_of(cc, काष्ठा mlxsw_sp_ptp_घड़ी, cycles);

	वापस __mlxsw_sp1_ptp_पढ़ो_frc(घड़ी, शून्य) & cc->mask;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_ptp_phc_adjfreq(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी, पूर्णांक freq_adj)
अणु
	काष्ठा mlxsw_core *mlxsw_core = घड़ी->core;
	अक्षर mtutc_pl[MLXSW_REG_MTUTC_LEN];

	mlxsw_reg_mtutc_pack(mtutc_pl, MLXSW_REG_MTUTC_OPERATION_ADJUST_FREQ,
			     freq_adj, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mtutc), mtutc_pl);
पूर्ण

अटल u64 mlxsw_sp1_ptp_ns2cycles(स्थिर काष्ठा समयcounter *tc, u64 nsec)
अणु
	u64 cycles = (u64) nsec;

	cycles <<= tc->cc->shअगरt;
	cycles = भाग_u64(cycles, tc->cc->mult);

	वापस cycles;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_ptp_phc_समय_रखो(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी, u64 nsec)
अणु
	काष्ठा mlxsw_core *mlxsw_core = घड़ी->core;
	u64 next_sec, next_sec_in_nsec, cycles;
	अक्षर mtutc_pl[MLXSW_REG_MTUTC_LEN];
	अक्षर mtpps_pl[MLXSW_REG_MTPPS_LEN];
	पूर्णांक err;

	next_sec = भाग_u64(nsec, NSEC_PER_SEC) + 1;
	next_sec_in_nsec = next_sec * NSEC_PER_SEC;

	spin_lock_bh(&घड़ी->lock);
	cycles = mlxsw_sp1_ptp_ns2cycles(&घड़ी->tc, next_sec_in_nsec);
	spin_unlock_bh(&घड़ी->lock);

	mlxsw_reg_mtpps_vpin_pack(mtpps_pl, cycles);
	err = mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mtpps), mtpps_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mtutc_pack(mtutc_pl,
			     MLXSW_REG_MTUTC_OPERATION_SET_TIME_AT_NEXT_SEC,
			     0, next_sec);
	वापस mlxsw_reg_ग_लिखो(mlxsw_core, MLXSW_REG(mtutc), mtutc_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी =
		container_of(ptp, काष्ठा mlxsw_sp_ptp_घड़ी, ptp_info);
	पूर्णांक neg_adj = 0;
	u32 dअगरf;
	u64 adj;
	s32 ppb;

	ppb = scaled_ppm_to_ppb(scaled_ppm);

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण

	adj = घड़ी->nominal_c_mult;
	adj *= ppb;
	dअगरf = भाग_u64(adj, NSEC_PER_SEC);

	spin_lock_bh(&घड़ी->lock);
	समयcounter_पढ़ो(&घड़ी->tc);
	घड़ी->cycles.mult = neg_adj ? घड़ी->nominal_c_mult - dअगरf :
				       घड़ी->nominal_c_mult + dअगरf;
	spin_unlock_bh(&घड़ी->lock);

	वापस mlxsw_sp1_ptp_phc_adjfreq(घड़ी, neg_adj ? -ppb : ppb);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी =
		container_of(ptp, काष्ठा mlxsw_sp_ptp_घड़ी, ptp_info);
	u64 nsec;

	spin_lock_bh(&घड़ी->lock);
	समयcounter_adjसमय(&घड़ी->tc, delta);
	nsec = समयcounter_पढ़ो(&घड़ी->tc);
	spin_unlock_bh(&घड़ी->lock);

	वापस mlxsw_sp1_ptp_phc_समय_रखो(घड़ी, nsec);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा बारpec64 *ts,
				  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी =
		container_of(ptp, काष्ठा mlxsw_sp_ptp_घड़ी, ptp_info);
	u64 cycles, nsec;

	spin_lock_bh(&घड़ी->lock);
	cycles = __mlxsw_sp1_ptp_पढ़ो_frc(घड़ी, sts);
	nsec = समयcounter_cyc2समय(&घड़ी->tc, cycles);
	spin_unlock_bh(&घड़ी->lock);

	*ts = ns_to_बारpec64(nsec);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
				 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी =
		container_of(ptp, काष्ठा mlxsw_sp_ptp_घड़ी, ptp_info);
	u64 nsec = बारpec64_to_ns(ts);

	spin_lock_bh(&घड़ी->lock);
	समयcounter_init(&घड़ी->tc, &घड़ी->cycles, nsec);
	nsec = समयcounter_पढ़ो(&घड़ी->tc);
	spin_unlock_bh(&घड़ी->lock);

	वापस mlxsw_sp1_ptp_phc_समय_रखो(घड़ी, nsec);
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info mlxsw_sp1_ptp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= "mlxsw_sp_clock",
	.max_adj	= 100000000,
	.adjfine	= mlxsw_sp1_ptp_adjfine,
	.adjसमय	= mlxsw_sp1_ptp_adjसमय,
	.समय_लोx64	= mlxsw_sp1_ptp_समय_लोx,
	.समय_रखो64	= mlxsw_sp1_ptp_समय_रखो,
पूर्ण;

अटल व्योम mlxsw_sp1_ptp_घड़ी_overflow(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी;

	घड़ी = container_of(dwork, काष्ठा mlxsw_sp_ptp_घड़ी, overflow_work);

	spin_lock_bh(&घड़ी->lock);
	समयcounter_पढ़ो(&घड़ी->tc);
	spin_unlock_bh(&घड़ी->lock);
	mlxsw_core_schedule_dw(&घड़ी->overflow_work, घड़ी->overflow_period);
पूर्ण

काष्ठा mlxsw_sp_ptp_घड़ी *
mlxsw_sp1_ptp_घड़ी_init(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा device *dev)
अणु
	u64 overflow_cycles, nsec, frac = 0;
	काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी;
	पूर्णांक err;

	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&घड़ी->lock);
	घड़ी->cycles.पढ़ो = mlxsw_sp1_ptp_पढ़ो_frc;
	घड़ी->cycles.shअगरt = MLXSW_SP1_PTP_CLOCK_CYCLES_SHIFT;
	घड़ी->cycles.mult = घड़ीsource_khz2mult(MLXSW_SP1_PTP_CLOCK_FREQ_KHZ,
						  घड़ी->cycles.shअगरt);
	घड़ी->nominal_c_mult = घड़ी->cycles.mult;
	घड़ी->cycles.mask = CLOCKSOURCE_MASK(MLXSW_SP1_PTP_CLOCK_MASK);
	घड़ी->core = mlxsw_sp->core;

	समयcounter_init(&घड़ी->tc, &घड़ी->cycles,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	/* Calculate period in seconds to call the overflow watchकरोg - to make
	 * sure counter is checked at least twice every wrap around.
	 * The period is calculated as the minimum between max HW cycles count
	 * (The घड़ी source mask) and max amount of cycles that can be
	 * multiplied by घड़ी multiplier where the result करोesn't exceed
	 * 64bits.
	 */
	overflow_cycles = भाग64_u64(~0ULL >> 1, घड़ी->cycles.mult);
	overflow_cycles = min(overflow_cycles, भाग_u64(घड़ी->cycles.mask, 3));

	nsec = cyclecounter_cyc2ns(&घड़ी->cycles, overflow_cycles, 0, &frac);
	घड़ी->overflow_period = nsecs_to_jअगरfies(nsec);

	INIT_DELAYED_WORK(&घड़ी->overflow_work, mlxsw_sp1_ptp_घड़ी_overflow);
	mlxsw_core_schedule_dw(&घड़ी->overflow_work, 0);

	घड़ी->ptp_info = mlxsw_sp1_ptp_घड़ी_info;
	घड़ी->ptp = ptp_घड़ी_रेजिस्टर(&घड़ी->ptp_info, dev);
	अगर (IS_ERR(घड़ी->ptp)) अणु
		err = PTR_ERR(घड़ी->ptp);
		dev_err(dev, "ptp_clock_register failed %d\n", err);
		जाओ err_ptp_घड़ी_रेजिस्टर;
	पूर्ण

	वापस घड़ी;

err_ptp_घड़ी_रेजिस्टर:
	cancel_delayed_work_sync(&घड़ी->overflow_work);
	kमुक्त(घड़ी);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp1_ptp_घड़ी_fini(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी)
अणु
	ptp_घड़ी_unरेजिस्टर(घड़ी->ptp);
	cancel_delayed_work_sync(&घड़ी->overflow_work);
	kमुक्त(घड़ी);
पूर्ण

अटल पूर्णांक mlxsw_sp_ptp_parse(काष्ठा sk_buff *skb,
			      u8 *p_करोमुख्य_number,
			      u8 *p_message_type,
			      u16 *p_sequence_id)
अणु
	अचिन्हित पूर्णांक ptp_class;
	काष्ठा ptp_header *hdr;

	ptp_class = ptp_classअगरy_raw(skb);

	चयन (ptp_class & PTP_CLASS_VMASK) अणु
	हाल PTP_CLASS_V1:
	हाल PTP_CLASS_V2:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस -EINVAL;

	*p_message_type	 = ptp_get_msgtype(hdr, ptp_class);
	*p_करोमुख्य_number = hdr->करोमुख्य_number;
	*p_sequence_id	 = be16_to_cpu(hdr->sequence_id);

	वापस 0;
पूर्ण

/* Returns शून्य on successful insertion, a poपूर्णांकer on conflict, or an ERR_PTR on
 * error.
 */
अटल पूर्णांक
mlxsw_sp1_ptp_unmatched_save(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp1_ptp_key key,
			     काष्ठा sk_buff *skb,
			     u64 बारtamp)
अणु
	पूर्णांक cycles = MLXSW_SP1_PTP_HT_GC_TIMEOUT / MLXSW_SP1_PTP_HT_GC_INTERVAL;
	काष्ठा mlxsw_sp_ptp_state *ptp_state = mlxsw_sp->ptp_state;
	काष्ठा mlxsw_sp1_ptp_unmatched *unmatched;
	पूर्णांक err;

	unmatched = kzalloc(माप(*unmatched), GFP_ATOMIC);
	अगर (!unmatched)
		वापस -ENOMEM;

	unmatched->key = key;
	unmatched->skb = skb;
	unmatched->बारtamp = बारtamp;
	unmatched->gc_cycle = mlxsw_sp->ptp_state->gc_cycle + cycles;

	err = rhltable_insert(&ptp_state->unmatched_ht, &unmatched->ht_node,
			      mlxsw_sp1_ptp_unmatched_ht_params);
	अगर (err)
		kमुक्त(unmatched);

	वापस err;
पूर्ण

अटल काष्ठा mlxsw_sp1_ptp_unmatched *
mlxsw_sp1_ptp_unmatched_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp1_ptp_key key, पूर्णांक *p_length)
अणु
	काष्ठा mlxsw_sp1_ptp_unmatched *unmatched, *last = शून्य;
	काष्ठा rhlist_head *पंचांगp, *list;
	पूर्णांक length = 0;

	list = rhltable_lookup(&mlxsw_sp->ptp_state->unmatched_ht, &key,
			       mlxsw_sp1_ptp_unmatched_ht_params);
	rhl_क्रम_each_entry_rcu(unmatched, पंचांगp, list, ht_node) अणु
		last = unmatched;
		length++;
	पूर्ण

	*p_length = length;
	वापस last;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_ptp_unmatched_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp1_ptp_unmatched *unmatched)
अणु
	वापस rhltable_हटाओ(&mlxsw_sp->ptp_state->unmatched_ht,
			       &unmatched->ht_node,
			       mlxsw_sp1_ptp_unmatched_ht_params);
पूर्ण

/* This function is called in the following scenarios:
 *
 * 1) When a packet is matched with its बारtamp.
 * 2) In several situation when it is necessary to immediately pass on
 *    an SKB without a बारtamp.
 * 3) From GC indirectly through mlxsw_sp1_ptp_unmatched_finish().
 *    This हाल is similar to 2) above.
 */
अटल व्योम mlxsw_sp1_ptp_packet_finish(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा sk_buff *skb, u8 local_port,
					bool ingress,
					काष्ठा skb_shared_hwtstamps *hwtstamps)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;

	/* Between capturing the packet and finishing it, there is a winकरोw of
	 * opportunity क्रम the originating port to go away (e.g. due to a
	 * split). Also make sure the SKB device reference is still valid.
	 */
	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	अगर (!(mlxsw_sp_port && (!skb->dev || skb->dev == mlxsw_sp_port->dev))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर (ingress) अणु
		अगर (hwtstamps)
			*skb_hwtstamps(skb) = *hwtstamps;
		mlxsw_sp_rx_listener_no_mark_func(skb, local_port, mlxsw_sp);
	पूर्ण अन्यथा अणु
		/* skb_tstamp_tx() allows hwtstamps to be शून्य. */
		skb_tstamp_tx(skb, hwtstamps);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp1_packet_बारtamp(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp1_ptp_key key,
				       काष्ठा sk_buff *skb,
				       u64 बारtamp)
अणु
	काष्ठा skb_shared_hwtstamps hwtstamps;
	u64 nsec;

	spin_lock_bh(&mlxsw_sp->घड़ी->lock);
	nsec = समयcounter_cyc2समय(&mlxsw_sp->घड़ी->tc, बारtamp);
	spin_unlock_bh(&mlxsw_sp->घड़ी->lock);

	hwtstamps.hwtstamp = ns_to_kसमय(nsec);
	mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb,
				    key.local_port, key.ingress, &hwtstamps);
पूर्ण

अटल व्योम
mlxsw_sp1_ptp_unmatched_finish(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp1_ptp_unmatched *unmatched)
अणु
	अगर (unmatched->skb && unmatched->बारtamp)
		mlxsw_sp1_packet_बारtamp(mlxsw_sp, unmatched->key,
					   unmatched->skb,
					   unmatched->बारtamp);
	अन्यथा अगर (unmatched->skb)
		mlxsw_sp1_ptp_packet_finish(mlxsw_sp, unmatched->skb,
					    unmatched->key.local_port,
					    unmatched->key.ingress, शून्य);
	kमुक्त_rcu(unmatched, rcu);
पूर्ण

अटल व्योम mlxsw_sp1_ptp_unmatched_मुक्त_fn(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा mlxsw_sp1_ptp_unmatched *unmatched = ptr;

	/* This is invoked at a poपूर्णांक where the ports are gone alपढ़ोy. Nothing
	 * to करो with whatever is left in the HT but to मुक्त it.
	 */
	अगर (unmatched->skb)
		dev_kमुक्त_skb_any(unmatched->skb);
	kमुक्त_rcu(unmatched, rcu);
पूर्ण

अटल व्योम mlxsw_sp1_ptp_got_piece(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp1_ptp_key key,
				    काष्ठा sk_buff *skb, u64 बारtamp)
अणु
	काष्ठा mlxsw_sp1_ptp_unmatched *unmatched;
	पूर्णांक length;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	spin_lock(&mlxsw_sp->ptp_state->unmatched_lock);

	unmatched = mlxsw_sp1_ptp_unmatched_lookup(mlxsw_sp, key, &length);
	अगर (skb && unmatched && unmatched->बारtamp) अणु
		unmatched->skb = skb;
	पूर्ण अन्यथा अगर (बारtamp && unmatched && unmatched->skb) अणु
		unmatched->बारtamp = बारtamp;
	पूर्ण अन्यथा अणु
		/* Either there is no entry to match, or one that is there is
		 * incompatible.
		 */
		अगर (length < 100)
			err = mlxsw_sp1_ptp_unmatched_save(mlxsw_sp, key,
							   skb, बारtamp);
		अन्यथा
			err = -E2BIG;
		अगर (err && skb)
			mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb,
						    key.local_port,
						    key.ingress, शून्य);
		unmatched = शून्य;
	पूर्ण

	अगर (unmatched) अणु
		err = mlxsw_sp1_ptp_unmatched_हटाओ(mlxsw_sp, unmatched);
		WARN_ON_ONCE(err);
	पूर्ण

	spin_unlock(&mlxsw_sp->ptp_state->unmatched_lock);

	अगर (unmatched)
		mlxsw_sp1_ptp_unmatched_finish(mlxsw_sp, unmatched);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम mlxsw_sp1_ptp_got_packet(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा sk_buff *skb, u8 local_port,
				     bool ingress)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp1_ptp_key key;
	u8 types;
	पूर्णांक err;

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	अगर (!mlxsw_sp_port)
		जाओ immediate;

	types = ingress ? mlxsw_sp_port->ptp.ing_types :
			  mlxsw_sp_port->ptp.egr_types;
	अगर (!types)
		जाओ immediate;

	स_रखो(&key, 0, माप(key));
	key.local_port = local_port;
	key.ingress = ingress;

	err = mlxsw_sp_ptp_parse(skb, &key.करोमुख्य_number, &key.message_type,
				 &key.sequence_id);
	अगर (err)
		जाओ immediate;

	/* For packets whose बारtamping was not enabled on this port, करोn't
	 * bother trying to match the बारtamp.
	 */
	अगर (!((1 << key.message_type) & types))
		जाओ immediate;

	mlxsw_sp1_ptp_got_piece(mlxsw_sp, key, skb, 0);
	वापस;

immediate:
	mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb, local_port, ingress, शून्य);
पूर्ण

व्योम mlxsw_sp1_ptp_got_बारtamp(काष्ठा mlxsw_sp *mlxsw_sp, bool ingress,
				 u8 local_port, u8 message_type,
				 u8 करोमुख्य_number, u16 sequence_id,
				 u64 बारtamp)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा mlxsw_sp1_ptp_key key;
	u8 types;

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	अगर (!mlxsw_sp_port)
		वापस;

	types = ingress ? mlxsw_sp_port->ptp.ing_types :
			  mlxsw_sp_port->ptp.egr_types;

	/* For message types whose बारtamping was not enabled on this port,
	 * करोn't bother with the बारtamp.
	 */
	अगर (!((1 << message_type) & types))
		वापस;

	स_रखो(&key, 0, माप(key));
	key.local_port = local_port;
	key.करोमुख्य_number = करोमुख्य_number;
	key.message_type = message_type;
	key.sequence_id = sequence_id;
	key.ingress = ingress;

	mlxsw_sp1_ptp_got_piece(mlxsw_sp, key, शून्य, बारtamp);
पूर्ण

व्योम mlxsw_sp1_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			   u8 local_port)
अणु
	skb_reset_mac_header(skb);
	mlxsw_sp1_ptp_got_packet(mlxsw_sp, skb, local_port, true);
पूर्ण

व्योम mlxsw_sp1_ptp_transmitted(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा sk_buff *skb, u8 local_port)
अणु
	mlxsw_sp1_ptp_got_packet(mlxsw_sp, skb, local_port, false);
पूर्ण

अटल व्योम
mlxsw_sp1_ptp_ht_gc_collect(काष्ठा mlxsw_sp_ptp_state *ptp_state,
			    काष्ठा mlxsw_sp1_ptp_unmatched *unmatched)
अणु
	काष्ठा mlxsw_sp_ptp_port_dir_stats *stats;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक err;

	/* If an unmatched entry has an SKB, it has to be handed over to the
	 * networking stack. This is usually करोne from a trap handler, which is
	 * invoked in a softirq context. Here we are going to करो it in process
	 * context. If that were to be पूर्णांकerrupted by a softirq, it could cause
	 * a deadlock when an attempt is made to take an alपढ़ोy-taken lock
	 * somewhere aदीर्घ the sending path. Disable softirqs to prevent this.
	 */
	local_bh_disable();

	spin_lock(&ptp_state->unmatched_lock);
	err = rhltable_हटाओ(&ptp_state->unmatched_ht, &unmatched->ht_node,
			      mlxsw_sp1_ptp_unmatched_ht_params);
	spin_unlock(&ptp_state->unmatched_lock);

	अगर (err)
		/* The packet was matched with बारtamp during the walk. */
		जाओ out;

	mlxsw_sp_port = ptp_state->mlxsw_sp->ports[unmatched->key.local_port];
	अगर (mlxsw_sp_port) अणु
		stats = unmatched->key.ingress ?
			&mlxsw_sp_port->ptp.stats.rx_gcd :
			&mlxsw_sp_port->ptp.stats.tx_gcd;
		अगर (unmatched->skb)
			stats->packets++;
		अन्यथा
			stats->बारtamps++;
	पूर्ण

	/* mlxsw_sp1_ptp_unmatched_finish() invokes netअगर_receive_skb(). While
	 * the comment at that function states that it can only be called in
	 * soft IRQ context, this pattern of local_bh_disable() +
	 * netअगर_receive_skb(), in process context, is seen अन्यथाwhere in the
	 * kernel, notably in pktgen.
	 */
	mlxsw_sp1_ptp_unmatched_finish(ptp_state->mlxsw_sp, unmatched);

out:
	local_bh_enable();
पूर्ण

अटल व्योम mlxsw_sp1_ptp_ht_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा mlxsw_sp1_ptp_unmatched *unmatched;
	काष्ठा mlxsw_sp_ptp_state *ptp_state;
	काष्ठा rhashtable_iter iter;
	u32 gc_cycle;
	व्योम *obj;

	ptp_state = container_of(dwork, काष्ठा mlxsw_sp_ptp_state, ht_gc_dw);
	gc_cycle = ptp_state->gc_cycle++;

	rhltable_walk_enter(&ptp_state->unmatched_ht, &iter);
	rhashtable_walk_start(&iter);
	जबतक ((obj = rhashtable_walk_next(&iter))) अणु
		अगर (IS_ERR(obj))
			जारी;

		unmatched = obj;
		अगर (unmatched->gc_cycle <= gc_cycle)
			mlxsw_sp1_ptp_ht_gc_collect(ptp_state, unmatched);
	पूर्ण
	rhashtable_walk_stop(&iter);
	rhashtable_walk_निकास(&iter);

	mlxsw_core_schedule_dw(&ptp_state->ht_gc_dw,
			       MLXSW_SP1_PTP_HT_GC_INTERVAL);
पूर्ण

अटल पूर्णांक mlxsw_sp_ptp_mtptpt_set(काष्ठा mlxsw_sp *mlxsw_sp,
				   क्रमागत mlxsw_reg_mtptpt_trap_id trap_id,
				   u16 message_type)
अणु
	अक्षर mtptpt_pl[MLXSW_REG_MTPTPT_LEN];

	mlxsw_reg_mtptptp_pack(mtptpt_pl, trap_id, message_type);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mtptpt), mtptpt_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_set_fअगरo_clr_on_trap(काष्ठा mlxsw_sp *mlxsw_sp,
					      bool clr)
अणु
	अक्षर mogcr_pl[MLXSW_REG_MOGCR_LEN] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(mogcr), mogcr_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mogcr_ptp_अगरtc_set(mogcr_pl, clr);
	mlxsw_reg_mogcr_ptp_eftc_set(mogcr_pl, clr);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mogcr), mogcr_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_mtpppc_set(काष्ठा mlxsw_sp *mlxsw_sp,
				    u16 ing_types, u16 egr_types)
अणु
	अक्षर mtpppc_pl[MLXSW_REG_MTPPPC_LEN];

	mlxsw_reg_mtpppc_pack(mtpppc_pl, ing_types, egr_types);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mtpppc), mtpppc_pl);
पूर्ण

काष्ठा mlxsw_sp1_ptp_shaper_params अणु
	u32 ethtool_speed;
	क्रमागत mlxsw_reg_qpsc_port_speed port_speed;
	u8 shaper_समय_exp;
	u8 shaper_समय_mantissa;
	u8 shaper_inc;
	u8 shaper_bs;
	u8 port_to_shaper_credits;
	पूर्णांक ing_बारtamp_inc;
	पूर्णांक egr_बारtamp_inc;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp1_ptp_shaper_params
mlxsw_sp1_ptp_shaper_params[] = अणु
	अणु
		.ethtool_speed		= SPEED_100,
		.port_speed		= MLXSW_REG_QPSC_PORT_SPEED_100M,
		.shaper_समय_exp	= 4,
		.shaper_समय_mantissa	= 12,
		.shaper_inc		= 9,
		.shaper_bs		= 1,
		.port_to_shaper_credits	= 1,
		.ing_बारtamp_inc	= -313,
		.egr_बारtamp_inc	= 313,
	पूर्ण,
	अणु
		.ethtool_speed		= SPEED_1000,
		.port_speed		= MLXSW_REG_QPSC_PORT_SPEED_1G,
		.shaper_समय_exp	= 0,
		.shaper_समय_mantissa	= 12,
		.shaper_inc		= 6,
		.shaper_bs		= 0,
		.port_to_shaper_credits	= 1,
		.ing_बारtamp_inc	= -35,
		.egr_बारtamp_inc	= 35,
	पूर्ण,
	अणु
		.ethtool_speed		= SPEED_10000,
		.port_speed		= MLXSW_REG_QPSC_PORT_SPEED_10G,
		.shaper_समय_exp	= 0,
		.shaper_समय_mantissa	= 2,
		.shaper_inc		= 14,
		.shaper_bs		= 1,
		.port_to_shaper_credits	= 1,
		.ing_बारtamp_inc	= -11,
		.egr_बारtamp_inc	= 11,
	पूर्ण,
	अणु
		.ethtool_speed		= SPEED_25000,
		.port_speed		= MLXSW_REG_QPSC_PORT_SPEED_25G,
		.shaper_समय_exp	= 0,
		.shaper_समय_mantissa	= 0,
		.shaper_inc		= 11,
		.shaper_bs		= 1,
		.port_to_shaper_credits	= 1,
		.ing_बारtamp_inc	= -14,
		.egr_बारtamp_inc	= 14,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP1_PTP_SHAPER_PARAMS_LEN ARRAY_SIZE(mlxsw_sp1_ptp_shaper_params)

अटल पूर्णांक mlxsw_sp1_ptp_shaper_params_set(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	स्थिर काष्ठा mlxsw_sp1_ptp_shaper_params *params;
	अक्षर qpsc_pl[MLXSW_REG_QPSC_LEN];
	पूर्णांक i, err;

	क्रम (i = 0; i < MLXSW_SP1_PTP_SHAPER_PARAMS_LEN; i++) अणु
		params = &mlxsw_sp1_ptp_shaper_params[i];
		mlxsw_reg_qpsc_pack(qpsc_pl, params->port_speed,
				    params->shaper_समय_exp,
				    params->shaper_समय_mantissa,
				    params->shaper_inc, params->shaper_bs,
				    params->port_to_shaper_credits,
				    params->ing_बारtamp_inc,
				    params->egr_बारtamp_inc);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qpsc), qpsc_pl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mlxsw_sp_ptp_state *mlxsw_sp1_ptp_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_ptp_state *ptp_state;
	u16 message_type;
	पूर्णांक err;

	err = mlxsw_sp1_ptp_shaper_params_set(mlxsw_sp);
	अगर (err)
		वापस ERR_PTR(err);

	ptp_state = kzalloc(माप(*ptp_state), GFP_KERNEL);
	अगर (!ptp_state)
		वापस ERR_PTR(-ENOMEM);
	ptp_state->mlxsw_sp = mlxsw_sp;

	spin_lock_init(&ptp_state->unmatched_lock);

	err = rhltable_init(&ptp_state->unmatched_ht,
			    &mlxsw_sp1_ptp_unmatched_ht_params);
	अगर (err)
		जाओ err_hashtable_init;

	/* Delive these message types as PTP0. */
	message_type = BIT(PTP_MSGTYPE_SYNC) |
		       BIT(PTP_MSGTYPE_DELAY_REQ) |
		       BIT(PTP_MSGTYPE_PDELAY_REQ) |
		       BIT(PTP_MSGTYPE_PDELAY_RESP);
	err = mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0,
				      message_type);
	अगर (err)
		जाओ err_mtptpt_set;

	/* Everything अन्यथा is PTP1. */
	message_type = ~message_type;
	err = mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1,
				      message_type);
	अगर (err)
		जाओ err_mtptpt1_set;

	err = mlxsw_sp1_ptp_set_fअगरo_clr_on_trap(mlxsw_sp, true);
	अगर (err)
		जाओ err_fअगरo_clr;

	INIT_DELAYED_WORK(&ptp_state->ht_gc_dw, mlxsw_sp1_ptp_ht_gc);
	mlxsw_core_schedule_dw(&ptp_state->ht_gc_dw,
			       MLXSW_SP1_PTP_HT_GC_INTERVAL);
	वापस ptp_state;

err_fअगरo_clr:
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1, 0);
err_mtptpt1_set:
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0, 0);
err_mtptpt_set:
	rhltable_destroy(&ptp_state->unmatched_ht);
err_hashtable_init:
	kमुक्त(ptp_state);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp1_ptp_fini(काष्ठा mlxsw_sp_ptp_state *ptp_state)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = ptp_state->mlxsw_sp;

	cancel_delayed_work_sync(&ptp_state->ht_gc_dw);
	mlxsw_sp1_ptp_mtpppc_set(mlxsw_sp, 0, 0);
	mlxsw_sp1_ptp_set_fअगरo_clr_on_trap(mlxsw_sp, false);
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP1, 0);
	mlxsw_sp_ptp_mtptpt_set(mlxsw_sp, MLXSW_REG_MTPTPT_TRAP_ID_PTP0, 0);
	rhltable_मुक्त_and_destroy(&ptp_state->unmatched_ht,
				  &mlxsw_sp1_ptp_unmatched_मुक्त_fn, शून्य);
	kमुक्त(ptp_state);
पूर्ण

पूर्णांक mlxsw_sp1_ptp_hwtstamp_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा hwtstamp_config *config)
अणु
	*config = mlxsw_sp_port->ptp.hwtstamp_config;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_ptp_get_message_types(स्थिर काष्ठा hwtstamp_config *config,
					  u16 *p_ing_types, u16 *p_egr_types,
					  क्रमागत hwtstamp_rx_filters *p_rx_filter)
अणु
	क्रमागत hwtstamp_rx_filters rx_filter = config->rx_filter;
	क्रमागत hwtstamp_tx_types tx_type = config->tx_type;
	u16 ing_types = 0x00;
	u16 egr_types = 0x00;

	चयन (tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		egr_types = 0x00;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		egr_types = 0xff;
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		वापस -दुस्फल;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		ing_types = 0x00;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
		ing_types = 0x01;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		ing_types = 0x02;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		ing_types = 0x0f;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
		ing_types = 0xff;
		अवरोध;
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		वापस -दुस्फल;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*p_ing_types = ing_types;
	*p_egr_types = egr_types;
	*p_rx_filter = rx_filter;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_mtpppc_update(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       u16 ing_types, u16 egr_types)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_port *पंचांगp;
	u16 orig_ing_types = 0;
	u16 orig_egr_types = 0;
	पूर्णांक err;
	पूर्णांक i;

	/* MTPPPC configures बारtamping globally, not per port. Find the
	 * configuration that contains all configured बारtamping requests.
	 */
	क्रम (i = 1; i < mlxsw_core_max_ports(mlxsw_sp->core); i++) अणु
		पंचांगp = mlxsw_sp->ports[i];
		अगर (पंचांगp) अणु
			orig_ing_types |= पंचांगp->ptp.ing_types;
			orig_egr_types |= पंचांगp->ptp.egr_types;
		पूर्ण
		अगर (पंचांगp && पंचांगp != mlxsw_sp_port) अणु
			ing_types |= पंचांगp->ptp.ing_types;
			egr_types |= पंचांगp->ptp.egr_types;
		पूर्ण
	पूर्ण

	अगर ((ing_types || egr_types) && !(orig_ing_types || orig_egr_types)) अणु
		err = mlxsw_sp_nve_inc_parsing_depth_get(mlxsw_sp);
		अगर (err) अणु
			netdev_err(mlxsw_sp_port->dev, "Failed to increase parsing depth");
			वापस err;
		पूर्ण
	पूर्ण
	अगर (!(ing_types || egr_types) && (orig_ing_types || orig_egr_types))
		mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp);

	वापस mlxsw_sp1_ptp_mtpppc_set(mlxsw_sp_port->mlxsw_sp,
				       ing_types, egr_types);
पूर्ण

अटल bool mlxsw_sp1_ptp_hwtstamp_enabled(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	वापस mlxsw_sp_port->ptp.ing_types || mlxsw_sp_port->ptp.egr_types;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_ptp_port_shaper_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port, bool enable)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर qeec_pl[MLXSW_REG_QEEC_LEN];

	mlxsw_reg_qeec_ptps_pack(qeec_pl, mlxsw_sp_port->local_port, enable);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(qeec), qeec_pl);
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptp_port_shaper_check(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	bool ptps = false;
	पूर्णांक err, i;
	u32 speed;

	अगर (!mlxsw_sp1_ptp_hwtstamp_enabled(mlxsw_sp_port))
		वापस mlxsw_sp1_ptp_port_shaper_set(mlxsw_sp_port, false);

	err = mlxsw_sp_port_speed_get(mlxsw_sp_port, &speed);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLXSW_SP1_PTP_SHAPER_PARAMS_LEN; i++) अणु
		अगर (mlxsw_sp1_ptp_shaper_params[i].ethtool_speed == speed) अणु
			ptps = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mlxsw_sp1_ptp_port_shaper_set(mlxsw_sp_port, ptps);
पूर्ण

व्योम mlxsw_sp1_ptp_shaper_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक err;

	mlxsw_sp_port = container_of(dwork, काष्ठा mlxsw_sp_port,
				     ptp.shaper_dw);

	अगर (!mlxsw_sp1_ptp_hwtstamp_enabled(mlxsw_sp_port))
		वापस;

	err = mlxsw_sp1_ptp_port_shaper_check(mlxsw_sp_port);
	अगर (err)
		netdev_err(mlxsw_sp_port->dev, "Failed to set up PTP shaper\n");
पूर्ण

पूर्णांक mlxsw_sp1_ptp_hwtstamp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा hwtstamp_config *config)
अणु
	क्रमागत hwtstamp_rx_filters rx_filter;
	u16 ing_types;
	u16 egr_types;
	पूर्णांक err;

	err = mlxsw_sp_ptp_get_message_types(config, &ing_types, &egr_types,
					     &rx_filter);
	अगर (err)
		वापस err;

	err = mlxsw_sp1_ptp_mtpppc_update(mlxsw_sp_port, ing_types, egr_types);
	अगर (err)
		वापस err;

	mlxsw_sp_port->ptp.hwtstamp_config = *config;
	mlxsw_sp_port->ptp.ing_types = ing_types;
	mlxsw_sp_port->ptp.egr_types = egr_types;

	err = mlxsw_sp1_ptp_port_shaper_check(mlxsw_sp_port);
	अगर (err)
		वापस err;

	/* Notअगरy the ioctl caller what we are actually बारtamping. */
	config->rx_filter = rx_filter;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp1_ptp_get_ts_info(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा ethtool_ts_info *info)
अणु
	info->phc_index = ptp_घड़ी_index(mlxsw_sp->घड़ी->ptp);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

काष्ठा mlxsw_sp_ptp_port_stat अणु
	अक्षर str[ETH_GSTRING_LEN];
	सूचक_भेद_प्रकार offset;
पूर्ण;

#घोषणा MLXSW_SP_PTP_PORT_STAT(NAME, FIELD)				\
	अणु								\
		.str = NAME,						\
		.offset = दुरत्व(काष्ठा mlxsw_sp_ptp_port_stats,	\
				    FIELD),				\
	पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_ptp_port_stat mlxsw_sp_ptp_port_stats[] = अणु
	MLXSW_SP_PTP_PORT_STAT("ptp_rx_gcd_packets",    rx_gcd.packets),
	MLXSW_SP_PTP_PORT_STAT("ptp_rx_gcd_timestamps", rx_gcd.बारtamps),
	MLXSW_SP_PTP_PORT_STAT("ptp_tx_gcd_packets",    tx_gcd.packets),
	MLXSW_SP_PTP_PORT_STAT("ptp_tx_gcd_timestamps", tx_gcd.बारtamps),
पूर्ण;

#अघोषित MLXSW_SP_PTP_PORT_STAT

#घोषणा MLXSW_SP_PTP_PORT_STATS_LEN \
	ARRAY_SIZE(mlxsw_sp_ptp_port_stats)

पूर्णांक mlxsw_sp1_get_stats_count(व्योम)
अणु
	वापस MLXSW_SP_PTP_PORT_STATS_LEN;
पूर्ण

व्योम mlxsw_sp1_get_stats_strings(u8 **p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_PTP_PORT_STATS_LEN; i++) अणु
		स_नकल(*p, mlxsw_sp_ptp_port_stats[i].str,
		       ETH_GSTRING_LEN);
		*p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

व्योम mlxsw_sp1_get_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			 u64 *data, पूर्णांक data_index)
अणु
	व्योम *stats = &mlxsw_sp_port->ptp.stats;
	सूचक_भेद_प्रकार offset;
	पूर्णांक i;

	data += data_index;
	क्रम (i = 0; i < MLXSW_SP_PTP_PORT_STATS_LEN; i++) अणु
		offset = mlxsw_sp_ptp_port_stats[i].offset;
		*data++ = *(u64 *)(stats + offset);
	पूर्ण
पूर्ण
