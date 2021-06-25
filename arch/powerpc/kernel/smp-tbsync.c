<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Smp समयbase synchronization क्रम ppc.
 *
 * Copyright (C) 2003 Samuel Rydh (samuel@ibrium.se)
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/समय.स>

#घोषणा NUM_ITER		300

क्रमागत अणु
	kExit=0, kSetAndTest, kTest
पूर्ण;

अटल काष्ठा अणु
	अस्थिर u64		tb;
	अस्थिर u64		mark;
	अस्थिर पूर्णांक		cmd;
	अस्थिर पूर्णांक		handshake;
	पूर्णांक			filler[2];

	अस्थिर पूर्णांक		ack;
	पूर्णांक			filler2[7];

	अस्थिर पूर्णांक		race_result;
पूर्ण *tbsync;

अटल अस्थिर पूर्णांक		running;

अटल व्योम enter_contest(u64 mark, दीर्घ add)
अणु
	जबतक (get_tb() < mark)
		tbsync->race_result = add;
पूर्ण

व्योम smp_generic_take_समयbase(व्योम)
अणु
	पूर्णांक cmd;
	u64 tb;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	जबतक (!running)
		barrier();
	rmb();

	क्रम (;;) अणु
		tbsync->ack = 1;
		जबतक (!tbsync->handshake)
			barrier();
		rmb();

		cmd = tbsync->cmd;
		tb = tbsync->tb;
		mb();
		tbsync->ack = 0;
		अगर (cmd == kExit)
			अवरोध;

		जबतक (tbsync->handshake)
			barrier();
		अगर (cmd == kSetAndTest)
			set_tb(tb >> 32, tb & 0xfffffffful);
		enter_contest(tbsync->mark, -1);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक start_contest(पूर्णांक cmd, दीर्घ offset, पूर्णांक num)
अणु
	पूर्णांक i, score=0;
	u64 tb;
	u64 mark;

	tbsync->cmd = cmd;

	local_irq_disable();
	क्रम (i = -3; i < num; ) अणु
		tb = get_tb() + 400;
		tbsync->tb = tb + offset;
		tbsync->mark = mark = tb + 400;

		wmb();

		tbsync->handshake = 1;
		जबतक (tbsync->ack)
			barrier();

		जबतक (get_tb() <= tb)
			barrier();
		tbsync->handshake = 0;
		enter_contest(mark, 1);

		जबतक (!tbsync->ack)
			barrier();

		अगर (i++ > 0)
			score += tbsync->race_result;
	पूर्ण
	local_irq_enable();
	वापस score;
पूर्ण

व्योम smp_generic_give_समयbase(व्योम)
अणु
	पूर्णांक i, score, score2, old, min=0, max=5000, offset=1000;

	pr_debug("Software timebase sync\n");

	/* अगर this fails then this kernel won't work anyway... */
	tbsync = kzalloc( माप(*tbsync), GFP_KERNEL );
	mb();
	running = 1;

	जबतक (!tbsync->ack)
		barrier();

	pr_debug("Got ack\n");

	/* binary search */
	क्रम (old = -1; old != offset ; offset = (min+max) / 2) अणु
		score = start_contest(kSetAndTest, offset, NUM_ITER);

		pr_debug("score %d, offset %d\n", score, offset );

		अगर( score > 0 )
			max = offset;
		अन्यथा
			min = offset;
		old = offset;
	पूर्ण
	score = start_contest(kSetAndTest, min, NUM_ITER);
	score2 = start_contest(kSetAndTest, max, NUM_ITER);

	pr_debug("Min %d (score %d), Max %d (score %d)\n",
		 min, score, max, score2);
	score = असल(score);
	score2 = असल(score2);
	offset = (score < score2) ? min : max;

	/* guard against inaccurate mttb */
	क्रम (i = 0; i < 10; i++) अणु
		start_contest(kSetAndTest, offset, NUM_ITER/10);

		अगर ((score2 = start_contest(kTest, offset, NUM_ITER)) < 0)
			score2 = -score2;
		अगर (score2 <= score || score2 < 20)
			अवरोध;
	पूर्ण
	pr_debug("Final offset: %d (%d/%d)\n", offset, score2, NUM_ITER );

	/* निकासing */
	tbsync->cmd = kExit;
	wmb();
	tbsync->handshake = 1;
	जबतक (tbsync->ack)
		barrier();
	tbsync->handshake = 0;
	kमुक्त(tbsync);
	tbsync = शून्य;
	running = 0;
पूर्ण
