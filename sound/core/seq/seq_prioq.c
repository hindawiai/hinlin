<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer Priority Queue
 *   Copyright (c) 1998-1999 by Frank van de Pol <fvdpol@coil.demon.nl>
 */

#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश "seq_timer.h"
#समावेश "seq_prioq.h"


/* Implementation is a simple linked list क्रम now...

   This priority queue orders the events on बारtamp. For events with an
   equeal बारtamp the queue behaves as a FIFO. 

   *
   *           +-------+
   *  Head --> | first |
   *           +-------+
   *                 |next
   *           +-----v-+
   *           |       |
   *           +-------+
   *                 |
   *           +-----v-+
   *           |       |
   *           +-------+
   *                 |
   *           +-----v-+
   *  Tail --> | last  |
   *           +-------+
   *

 */



/* create new prioq (स्थिरructor) */
काष्ठा snd_seq_prioq *snd_seq_prioq_new(व्योम)
अणु
	काष्ठा snd_seq_prioq *f;

	f = kzalloc(माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस शून्य;
	
	spin_lock_init(&f->lock);
	f->head = शून्य;
	f->tail = शून्य;
	f->cells = 0;
	
	वापस f;
पूर्ण

/* delete prioq (deकाष्ठाor) */
व्योम snd_seq_prioq_delete(काष्ठा snd_seq_prioq **fअगरo)
अणु
	काष्ठा snd_seq_prioq *f = *fअगरo;
	*fअगरo = शून्य;

	अगर (f == शून्य) अणु
		pr_debug("ALSA: seq: snd_seq_prioq_delete() called with NULL prioq\n");
		वापस;
	पूर्ण

	/* release resources...*/
	/*....................*/
	
	अगर (f->cells > 0) अणु
		/* drain prioQ */
		जबतक (f->cells > 0)
			snd_seq_cell_मुक्त(snd_seq_prioq_cell_out(f, शून्य));
	पूर्ण
	
	kमुक्त(f);
पूर्ण




/* compare बारtamp between events */
/* वापस 1 अगर a >= b; 0 */
अटल अंतरभूत पूर्णांक compare_बारtamp(काष्ठा snd_seq_event *a,
				    काष्ठा snd_seq_event *b)
अणु
	अगर ((a->flags & SNDRV_SEQ_TIME_STAMP_MASK) == SNDRV_SEQ_TIME_STAMP_TICK) अणु
		/* compare ticks */
		वापस (snd_seq_compare_tick_समय(&a->समय.tick, &b->समय.tick));
	पूर्ण अन्यथा अणु
		/* compare real समय */
		वापस (snd_seq_compare_real_समय(&a->समय.समय, &b->समय.समय));
	पूर्ण
पूर्ण

/* compare बारtamp between events */
/* वापस negative अगर a < b;
 *        zero     अगर a = b;
 *        positive अगर a > b;
 */
अटल अंतरभूत पूर्णांक compare_बारtamp_rel(काष्ठा snd_seq_event *a,
					काष्ठा snd_seq_event *b)
अणु
	अगर ((a->flags & SNDRV_SEQ_TIME_STAMP_MASK) == SNDRV_SEQ_TIME_STAMP_TICK) अणु
		/* compare ticks */
		अगर (a->समय.tick > b->समय.tick)
			वापस 1;
		अन्यथा अगर (a->समय.tick == b->समय.tick)
			वापस 0;
		अन्यथा
			वापस -1;
	पूर्ण अन्यथा अणु
		/* compare real समय */
		अगर (a->समय.समय.tv_sec > b->समय.समय.tv_sec)
			वापस 1;
		अन्यथा अगर (a->समय.समय.tv_sec == b->समय.समय.tv_sec) अणु
			अगर (a->समय.समय.tv_nsec > b->समय.समय.tv_nsec)
				वापस 1;
			अन्यथा अगर (a->समय.समय.tv_nsec == b->समय.समय.tv_nsec)
				वापस 0;
			अन्यथा
				वापस -1;
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण
पूर्ण

/* enqueue cell to prioq */
पूर्णांक snd_seq_prioq_cell_in(काष्ठा snd_seq_prioq * f,
			  काष्ठा snd_seq_event_cell * cell)
अणु
	काष्ठा snd_seq_event_cell *cur, *prev;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	पूर्णांक prior;

	अगर (snd_BUG_ON(!f || !cell))
		वापस -EINVAL;
	
	/* check flags */
	prior = (cell->event.flags & SNDRV_SEQ_PRIORITY_MASK);

	spin_lock_irqsave(&f->lock, flags);

	/* check अगर this element needs to inserted at the end (ie. ordered 
	   data is inserted) This will be very likeley अगर a sequencer 
	   application or midi file player is feeding us (sequential) data */
	अगर (f->tail && !prior) अणु
		अगर (compare_बारtamp(&cell->event, &f->tail->event)) अणु
			/* add new cell to tail of the fअगरo */
			f->tail->next = cell;
			f->tail = cell;
			cell->next = शून्य;
			f->cells++;
			spin_unlock_irqrestore(&f->lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण
	/* traverse list of elements to find the place where the new cell is
	   to be inserted... Note that this is a order n process ! */

	prev = शून्य;		/* previous cell */
	cur = f->head;		/* cursor */

	count = 10000; /* FIXME: enough big, isn't it? */
	जबतक (cur != शून्य) अणु
		/* compare बारtamps */
		पूर्णांक rel = compare_बारtamp_rel(&cell->event, &cur->event);
		अगर (rel < 0)
			/* new cell has earlier schedule समय, */
			अवरोध;
		अन्यथा अगर (rel == 0 && prior)
			/* equal schedule समय and prior to others */
			अवरोध;
		/* new cell has equal or larger schedule समय, */
		/* move cursor to next cell */
		prev = cur;
		cur = cur->next;
		अगर (! --count) अणु
			spin_unlock_irqrestore(&f->lock, flags);
			pr_err("ALSA: seq: cannot find a pointer.. infinite loop?\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* insert it beक्रमe cursor */
	अगर (prev != शून्य)
		prev->next = cell;
	cell->next = cur;

	अगर (f->head == cur) /* this is the first cell, set head to it */
		f->head = cell;
	अगर (cur == शून्य) /* reached end of the list */
		f->tail = cell;
	f->cells++;
	spin_unlock_irqrestore(&f->lock, flags);
	वापस 0;
पूर्ण

/* वापस 1 अगर the current समय >= event बारtamp */
अटल पूर्णांक event_is_पढ़ोy(काष्ठा snd_seq_event *ev, व्योम *current_समय)
अणु
	अगर ((ev->flags & SNDRV_SEQ_TIME_STAMP_MASK) == SNDRV_SEQ_TIME_STAMP_TICK)
		वापस snd_seq_compare_tick_समय(current_समय, &ev->समय.tick);
	अन्यथा
		वापस snd_seq_compare_real_समय(current_समय, &ev->समय.समय);
पूर्ण

/* dequeue cell from prioq */
काष्ठा snd_seq_event_cell *snd_seq_prioq_cell_out(काष्ठा snd_seq_prioq *f,
						  व्योम *current_समय)
अणु
	काष्ठा snd_seq_event_cell *cell;
	अचिन्हित दीर्घ flags;

	अगर (f == शून्य) अणु
		pr_debug("ALSA: seq: snd_seq_prioq_cell_in() called with NULL prioq\n");
		वापस शून्य;
	पूर्ण
	spin_lock_irqsave(&f->lock, flags);

	cell = f->head;
	अगर (cell && current_समय && !event_is_पढ़ोy(&cell->event, current_समय))
		cell = शून्य;
	अगर (cell) अणु
		f->head = cell->next;

		/* reset tail अगर this was the last element */
		अगर (f->tail == cell)
			f->tail = शून्य;

		cell->next = शून्य;
		f->cells--;
	पूर्ण

	spin_unlock_irqrestore(&f->lock, flags);
	वापस cell;
पूर्ण

/* वापस number of events available in prioq */
पूर्णांक snd_seq_prioq_avail(काष्ठा snd_seq_prioq * f)
अणु
	अगर (f == शून्य) अणु
		pr_debug("ALSA: seq: snd_seq_prioq_cell_in() called with NULL prioq\n");
		वापस 0;
	पूर्ण
	वापस f->cells;
पूर्ण

अटल अंतरभूत पूर्णांक prioq_match(काष्ठा snd_seq_event_cell *cell,
			      पूर्णांक client, पूर्णांक बारtamp)
अणु
	अगर (cell->event.source.client == client ||
	    cell->event.dest.client == client)
		वापस 1;
	अगर (!बारtamp)
		वापस 0;
	चयन (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) अणु
	हाल SNDRV_SEQ_TIME_STAMP_TICK:
		अगर (cell->event.समय.tick)
			वापस 1;
		अवरोध;
	हाल SNDRV_SEQ_TIME_STAMP_REAL:
		अगर (cell->event.समय.समय.tv_sec ||
		    cell->event.समय.समय.tv_nsec)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* हटाओ cells क्रम left client */
व्योम snd_seq_prioq_leave(काष्ठा snd_seq_prioq * f, पूर्णांक client, पूर्णांक बारtamp)
अणु
	रेजिस्टर काष्ठा snd_seq_event_cell *cell, *next;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_event_cell *prev = शून्य;
	काष्ठा snd_seq_event_cell *मुक्तfirst = शून्य, *मुक्तprev = शून्य, *मुक्तnext;

	/* collect all हटाओd cells */
	spin_lock_irqsave(&f->lock, flags);
	cell = f->head;
	जबतक (cell) अणु
		next = cell->next;
		अगर (prioq_match(cell, client, बारtamp)) अणु
			/* हटाओ cell from prioq */
			अगर (cell == f->head) अणु
				f->head = cell->next;
			पूर्ण अन्यथा अणु
				prev->next = cell->next;
			पूर्ण
			अगर (cell == f->tail)
				f->tail = cell->next;
			f->cells--;
			/* add cell to मुक्त list */
			cell->next = शून्य;
			अगर (मुक्तfirst == शून्य) अणु
				मुक्तfirst = cell;
			पूर्ण अन्यथा अणु
				मुक्तprev->next = cell;
			पूर्ण
			मुक्तprev = cell;
		पूर्ण अन्यथा अणु
#अगर 0
			pr_debug("ALSA: seq: type = %i, source = %i, dest = %i, "
			       "client = %i\n",
				cell->event.type,
				cell->event.source.client,
				cell->event.dest.client,
				client);
#पूर्ण_अगर
			prev = cell;
		पूर्ण
		cell = next;		
	पूर्ण
	spin_unlock_irqrestore(&f->lock, flags);	

	/* हटाओ selected cells */
	जबतक (मुक्तfirst) अणु
		मुक्तnext = मुक्तfirst->next;
		snd_seq_cell_मुक्त(मुक्तfirst);
		मुक्तfirst = मुक्तnext;
	पूर्ण
पूर्ण

अटल पूर्णांक prioq_हटाओ_match(काष्ठा snd_seq_हटाओ_events *info,
			      काष्ठा snd_seq_event *ev)
अणु
	पूर्णांक res;

	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_DEST) अणु
		अगर (ev->dest.client != info->dest.client ||
				ev->dest.port != info->dest.port)
			वापस 0;
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_DEST_CHANNEL) अणु
		अगर (! snd_seq_ev_is_channel_type(ev))
			वापस 0;
		/* data.note.channel and data.control.channel are identical */
		अगर (ev->data.note.channel != info->channel)
			वापस 0;
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_TIME_AFTER) अणु
		अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_TIME_TICK)
			res = snd_seq_compare_tick_समय(&ev->समय.tick, &info->समय.tick);
		अन्यथा
			res = snd_seq_compare_real_समय(&ev->समय.समय, &info->समय.समय);
		अगर (!res)
			वापस 0;
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_TIME_BEFORE) अणु
		अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_TIME_TICK)
			res = snd_seq_compare_tick_समय(&ev->समय.tick, &info->समय.tick);
		अन्यथा
			res = snd_seq_compare_real_समय(&ev->समय.समय, &info->समय.समय);
		अगर (res)
			वापस 0;
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_EVENT_TYPE) अणु
		अगर (ev->type != info->type)
			वापस 0;
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_IGNORE_OFF) अणु
		/* Do not हटाओ off events */
		चयन (ev->type) अणु
		हाल SNDRV_SEQ_EVENT_NOTखातापूर्णF:
		/* हाल SNDRV_SEQ_EVENT_SAMPLE_STOP: */
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (info->हटाओ_mode & SNDRV_SEQ_REMOVE_TAG_MATCH) अणु
		अगर (info->tag != ev->tag)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* हटाओ cells matching हटाओ criteria */
व्योम snd_seq_prioq_हटाओ_events(काष्ठा snd_seq_prioq * f, पूर्णांक client,
				 काष्ठा snd_seq_हटाओ_events *info)
अणु
	काष्ठा snd_seq_event_cell *cell, *next;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_seq_event_cell *prev = शून्य;
	काष्ठा snd_seq_event_cell *मुक्तfirst = शून्य, *मुक्तprev = शून्य, *मुक्तnext;

	/* collect all हटाओd cells */
	spin_lock_irqsave(&f->lock, flags);
	cell = f->head;

	जबतक (cell) अणु
		next = cell->next;
		अगर (cell->event.source.client == client &&
			prioq_हटाओ_match(info, &cell->event)) अणु

			/* हटाओ cell from prioq */
			अगर (cell == f->head) अणु
				f->head = cell->next;
			पूर्ण अन्यथा अणु
				prev->next = cell->next;
			पूर्ण

			अगर (cell == f->tail)
				f->tail = cell->next;
			f->cells--;

			/* add cell to मुक्त list */
			cell->next = शून्य;
			अगर (मुक्तfirst == शून्य) अणु
				मुक्तfirst = cell;
			पूर्ण अन्यथा अणु
				मुक्तprev->next = cell;
			पूर्ण

			मुक्तprev = cell;
		पूर्ण अन्यथा अणु
			prev = cell;
		पूर्ण
		cell = next;		
	पूर्ण
	spin_unlock_irqrestore(&f->lock, flags);	

	/* हटाओ selected cells */
	जबतक (मुक्तfirst) अणु
		मुक्तnext = मुक्तfirst->next;
		snd_seq_cell_मुक्त(मुक्तfirst);
		मुक्तfirst = मुक्तnext;
	पूर्ण
पूर्ण


