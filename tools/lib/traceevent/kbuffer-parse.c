<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "kbuffer.h"

#घोषणा MISSING_EVENTS (1UL << 31)
#घोषणा MISSING_STORED (1UL << 30)

#घोषणा COMMIT_MASK ((1 << 27) - 1)

क्रमागत अणु
	KBUFFER_FL_HOST_BIG_ENDIAN	= (1<<0),
	KBUFFER_FL_BIG_ENDIAN		= (1<<1),
	KBUFFER_FL_LONG_8		= (1<<2),
	KBUFFER_FL_OLD_FORMAT		= (1<<3),
पूर्ण;

#घोषणा ENDIAN_MASK (KBUFFER_FL_HOST_BIG_ENDIAN | KBUFFER_FL_BIG_ENDIAN)

/** kbuffer
 * @बारtamp		- बारtamp of current event
 * @lost_events		- # of lost events between this subbuffer and previous
 * @flags		- special flags of the kbuffer
 * @subbuffer		- poपूर्णांकer to the sub-buffer page
 * @data		- poपूर्णांकer to the start of data on the sub-buffer page
 * @index		- index from @data to the @curr event data
 * @curr		- offset from @data to the start of current event
 *			   (includes metadata)
 * @next		- offset from @data to the start of next event
 * @size		- The size of data on @data
 * @start		- The offset from @subbuffer where @data lives
 *
 * @पढ़ो_4		- Function to पढ़ो 4 raw bytes (may swap)
 * @पढ़ो_8		- Function to पढ़ो 8 raw bytes (may swap)
 * @पढ़ो_दीर्घ		- Function to पढ़ो a दीर्घ word (4 or 8 bytes with needed swap)
 */
काष्ठा kbuffer अणु
	अचिन्हित दीर्घ दीर्घ 	बारtamp;
	दीर्घ दीर्घ		lost_events;
	अचिन्हित दीर्घ		flags;
	व्योम			*subbuffer;
	व्योम			*data;
	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		curr;
	अचिन्हित पूर्णांक		next;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		start;

	अचिन्हित पूर्णांक (*पढ़ो_4)(व्योम *ptr);
	अचिन्हित दीर्घ दीर्घ (*पढ़ो_8)(व्योम *ptr);
	अचिन्हित दीर्घ दीर्घ (*पढ़ो_दीर्घ)(काष्ठा kbuffer *kbuf, व्योम *ptr);
	पूर्णांक (*next_event)(काष्ठा kbuffer *kbuf);
पूर्ण;

अटल व्योम *zदो_स्मृति(माप_प्रकार size)
अणु
	वापस सुस्मृति(1, size);
पूर्ण

अटल पूर्णांक host_is_bigendian(व्योम)
अणु
	अचिन्हित अक्षर str[] = अणु 0x1, 0x2, 0x3, 0x4 पूर्ण;
	अचिन्हित पूर्णांक *ptr;

	ptr = (अचिन्हित पूर्णांक *)str;
	वापस *ptr == 0x01020304;
पूर्ण

अटल पूर्णांक करो_swap(काष्ठा kbuffer *kbuf)
अणु
	वापस ((kbuf->flags & KBUFFER_FL_HOST_BIG_ENDIAN) + kbuf->flags) &
		ENDIAN_MASK;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ __पढ़ो_8(व्योम *ptr)
अणु
	अचिन्हित दीर्घ दीर्घ data = *(अचिन्हित दीर्घ दीर्घ *)ptr;

	वापस data;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ __पढ़ो_8_sw(व्योम *ptr)
अणु
	अचिन्हित दीर्घ दीर्घ data = *(अचिन्हित दीर्घ दीर्घ *)ptr;
	अचिन्हित दीर्घ दीर्घ swap;

	swap = ((data & 0xffULL) << 56) |
		((data & (0xffULL << 8)) << 40) |
		((data & (0xffULL << 16)) << 24) |
		((data & (0xffULL << 24)) << 8) |
		((data & (0xffULL << 32)) >> 8) |
		((data & (0xffULL << 40)) >> 24) |
		((data & (0xffULL << 48)) >> 40) |
		((data & (0xffULL << 56)) >> 56);

	वापस swap;
पूर्ण

अटल अचिन्हित पूर्णांक __पढ़ो_4(व्योम *ptr)
अणु
	अचिन्हित पूर्णांक data = *(अचिन्हित पूर्णांक *)ptr;

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक __पढ़ो_4_sw(व्योम *ptr)
अणु
	अचिन्हित पूर्णांक data = *(अचिन्हित पूर्णांक *)ptr;
	अचिन्हित पूर्णांक swap;

	swap = ((data & 0xffULL) << 24) |
		((data & (0xffULL << 8)) << 8) |
		((data & (0xffULL << 16)) >> 8) |
		((data & (0xffULL << 24)) >> 24);

	वापस swap;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ पढ़ो_8(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस kbuf->पढ़ो_8(ptr);
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_4(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस kbuf->पढ़ो_4(ptr);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ __पढ़ो_दीर्घ_8(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस kbuf->पढ़ो_8(ptr);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ __पढ़ो_दीर्घ_4(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस kbuf->पढ़ो_4(ptr);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ पढ़ो_दीर्घ(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस kbuf->पढ़ो_दीर्घ(kbuf, ptr);
पूर्ण

अटल पूर्णांक calc_index(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	वापस (अचिन्हित दीर्घ)ptr - (अचिन्हित दीर्घ)kbuf->data;
पूर्ण

अटल पूर्णांक __next_event(काष्ठा kbuffer *kbuf);

/**
 * kbuffer_alloc - allocat a new kbuffer
 * @size;	क्रमागत to denote size of word
 * @endian:	क्रमागत to denote endianness
 *
 * Allocates and वापसs a new kbuffer.
 */
काष्ठा kbuffer *
kbuffer_alloc(क्रमागत kbuffer_दीर्घ_size size, क्रमागत kbuffer_endian endian)
अणु
	काष्ठा kbuffer *kbuf;
	पूर्णांक flags = 0;

	चयन (size) अणु
	हाल KBUFFER_LSIZE_4:
		अवरोध;
	हाल KBUFFER_LSIZE_8:
		flags |= KBUFFER_FL_LONG_8;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	चयन (endian) अणु
	हाल KBUFFER_ENDIAN_LITTLE:
		अवरोध;
	हाल KBUFFER_ENDIAN_BIG:
		flags |= KBUFFER_FL_BIG_ENDIAN;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	kbuf = zदो_स्मृति(माप(*kbuf));
	अगर (!kbuf)
		वापस शून्य;

	kbuf->flags = flags;

	अगर (host_is_bigendian())
		kbuf->flags |= KBUFFER_FL_HOST_BIG_ENDIAN;

	अगर (करो_swap(kbuf)) अणु
		kbuf->पढ़ो_8 = __पढ़ो_8_sw;
		kbuf->पढ़ो_4 = __पढ़ो_4_sw;
	पूर्ण अन्यथा अणु
		kbuf->पढ़ो_8 = __पढ़ो_8;
		kbuf->पढ़ो_4 = __पढ़ो_4;
	पूर्ण

	अगर (kbuf->flags & KBUFFER_FL_LONG_8)
		kbuf->पढ़ो_दीर्घ = __पढ़ो_दीर्घ_8;
	अन्यथा
		kbuf->पढ़ो_दीर्घ = __पढ़ो_दीर्घ_4;

	/* May be changed by kbuffer_set_old_क्रमmat() */
	kbuf->next_event = __next_event;

	वापस kbuf;
पूर्ण

/** kbuffer_मुक्त - मुक्त an allocated kbuffer
 * @kbuf:	The kbuffer to मुक्त
 *
 * Can take शून्य as a parameter.
 */
व्योम kbuffer_मुक्त(काष्ठा kbuffer *kbuf)
अणु
	मुक्त(kbuf);
पूर्ण

अटल अचिन्हित पूर्णांक type4host(काष्ठा kbuffer *kbuf,
			      अचिन्हित पूर्णांक type_len_ts)
अणु
	अगर (kbuf->flags & KBUFFER_FL_BIG_ENDIAN)
		वापस (type_len_ts >> 29) & 3;
	अन्यथा
		वापस type_len_ts & 3;
पूर्ण

अटल अचिन्हित पूर्णांक len4host(काष्ठा kbuffer *kbuf,
			     अचिन्हित पूर्णांक type_len_ts)
अणु
	अगर (kbuf->flags & KBUFFER_FL_BIG_ENDIAN)
		वापस (type_len_ts >> 27) & 7;
	अन्यथा
		वापस (type_len_ts >> 2) & 7;
पूर्ण

अटल अचिन्हित पूर्णांक type_len4host(काष्ठा kbuffer *kbuf,
				  अचिन्हित पूर्णांक type_len_ts)
अणु
	अगर (kbuf->flags & KBUFFER_FL_BIG_ENDIAN)
		वापस (type_len_ts >> 27) & ((1 << 5) - 1);
	अन्यथा
		वापस type_len_ts & ((1 << 5) - 1);
पूर्ण

अटल अचिन्हित पूर्णांक ts4host(काष्ठा kbuffer *kbuf,
			    अचिन्हित पूर्णांक type_len_ts)
अणु
	अगर (kbuf->flags & KBUFFER_FL_BIG_ENDIAN)
		वापस type_len_ts & ((1 << 27) - 1);
	अन्यथा
		वापस type_len_ts >> 5;
पूर्ण

/*
 * Linux 2.6.30 and earlier (not much ealier) had a dअगरferent
 * ring buffer क्रमmat. It should be obsolete, but we handle it anyway.
 */
क्रमागत old_ring_buffer_type अणु
	OLD_RINGBUF_TYPE_PADDING,
	OLD_RINGBUF_TYPE_TIME_EXTEND,
	OLD_RINGBUF_TYPE_TIME_STAMP,
	OLD_RINGBUF_TYPE_DATA,
पूर्ण;

अटल अचिन्हित पूर्णांक old_update_poपूर्णांकers(काष्ठा kbuffer *kbuf)
अणु
	अचिन्हित दीर्घ दीर्घ extend;
	अचिन्हित पूर्णांक type_len_ts;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक delta;
	अचिन्हित पूर्णांक length;
	व्योम *ptr = kbuf->data + kbuf->curr;

	type_len_ts = पढ़ो_4(kbuf, ptr);
	ptr += 4;

	type = type4host(kbuf, type_len_ts);
	len = len4host(kbuf, type_len_ts);
	delta = ts4host(kbuf, type_len_ts);

	चयन (type) अणु
	हाल OLD_RINGBUF_TYPE_PADDING:
		kbuf->next = kbuf->size;
		वापस 0;

	हाल OLD_RINGBUF_TYPE_TIME_EXTEND:
		extend = पढ़ो_4(kbuf, ptr);
		extend <<= TS_SHIFT;
		extend += delta;
		delta = extend;
		ptr += 4;
		length = 0;
		अवरोध;

	हाल OLD_RINGBUF_TYPE_TIME_STAMP:
		/* should never happen! */
		kbuf->curr = kbuf->size;
		kbuf->next = kbuf->size;
		kbuf->index = kbuf->size;
		वापस -1;
	शेष:
		अगर (len)
			length = len * 4;
		अन्यथा अणु
			length = पढ़ो_4(kbuf, ptr);
			length -= 4;
			ptr += 4;
		पूर्ण
		अवरोध;
	पूर्ण

	kbuf->बारtamp += delta;
	kbuf->index = calc_index(kbuf, ptr);
	kbuf->next = kbuf->index + length;

	वापस type;
पूर्ण

अटल पूर्णांक __old_next_event(काष्ठा kbuffer *kbuf)
अणु
	पूर्णांक type;

	करो अणु
		kbuf->curr = kbuf->next;
		अगर (kbuf->next >= kbuf->size)
			वापस -1;
		type = old_update_poपूर्णांकers(kbuf);
	पूर्ण जबतक (type == OLD_RINGBUF_TYPE_TIME_EXTEND || type == OLD_RINGBUF_TYPE_PADDING);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
translate_data(काष्ठा kbuffer *kbuf, व्योम *data, व्योम **rptr,
	       अचिन्हित दीर्घ दीर्घ *delta, पूर्णांक *length)
अणु
	अचिन्हित दीर्घ दीर्घ extend;
	अचिन्हित पूर्णांक type_len_ts;
	अचिन्हित पूर्णांक type_len;

	type_len_ts = पढ़ो_4(kbuf, data);
	data += 4;

	type_len = type_len4host(kbuf, type_len_ts);
	*delta = ts4host(kbuf, type_len_ts);

	चयन (type_len) अणु
	हाल KBUFFER_TYPE_PADDING:
		*length = पढ़ो_4(kbuf, data);
		अवरोध;

	हाल KBUFFER_TYPE_TIME_EXTEND:
	हाल KBUFFER_TYPE_TIME_STAMP:
		extend = पढ़ो_4(kbuf, data);
		data += 4;
		extend <<= TS_SHIFT;
		extend += *delta;
		*delta = extend;
		*length = 0;
		अवरोध;

	हाल 0:
		*length = पढ़ो_4(kbuf, data) - 4;
		*length = (*length + 3) & ~3;
		data += 4;
		अवरोध;
	शेष:
		*length = type_len * 4;
		अवरोध;
	पूर्ण

	*rptr = data;

	वापस type_len;
पूर्ण

अटल अचिन्हित पूर्णांक update_poपूर्णांकers(काष्ठा kbuffer *kbuf)
अणु
	अचिन्हित दीर्घ दीर्घ delta;
	अचिन्हित पूर्णांक type_len;
	पूर्णांक length;
	व्योम *ptr = kbuf->data + kbuf->curr;

	type_len = translate_data(kbuf, ptr, &ptr, &delta, &length);

	अगर (type_len == KBUFFER_TYPE_TIME_STAMP)
		kbuf->बारtamp = delta;
	अन्यथा
		kbuf->बारtamp += delta;

	kbuf->index = calc_index(kbuf, ptr);
	kbuf->next = kbuf->index + length;

	वापस type_len;
पूर्ण

/**
 * kbuffer_translate_data - पढ़ो raw data to get a record
 * @swap:	Set to 1 अगर bytes in words need to be swapped when पढ़ो
 * @data:	The raw data to पढ़ो
 * @size:	Address to store the size of the event data.
 *
 * Returns a poपूर्णांकer to the event data. To determine the entire
 * record size (record metadata + data) just add the dअगरference between
 * @data and the वापसed value to @size.
 */
व्योम *kbuffer_translate_data(पूर्णांक swap, व्योम *data, अचिन्हित पूर्णांक *size)
अणु
	अचिन्हित दीर्घ दीर्घ delta;
	काष्ठा kbuffer kbuf;
	पूर्णांक type_len;
	पूर्णांक length;
	व्योम *ptr;

	अगर (swap) अणु
		kbuf.पढ़ो_8 = __पढ़ो_8_sw;
		kbuf.पढ़ो_4 = __पढ़ो_4_sw;
		kbuf.flags = host_is_bigendian() ? 0 : KBUFFER_FL_BIG_ENDIAN;
	पूर्ण अन्यथा अणु
		kbuf.पढ़ो_8 = __पढ़ो_8;
		kbuf.पढ़ो_4 = __पढ़ो_4;
		kbuf.flags = host_is_bigendian() ? KBUFFER_FL_BIG_ENDIAN: 0;
	पूर्ण

	type_len = translate_data(&kbuf, data, &ptr, &delta, &length);
	चयन (type_len) अणु
	हाल KBUFFER_TYPE_PADDING:
	हाल KBUFFER_TYPE_TIME_EXTEND:
	हाल KBUFFER_TYPE_TIME_STAMP:
		वापस शून्य;
	पूर्ण

	*size = length;

	वापस ptr;
पूर्ण

अटल पूर्णांक __next_event(काष्ठा kbuffer *kbuf)
अणु
	पूर्णांक type;

	करो अणु
		kbuf->curr = kbuf->next;
		अगर (kbuf->next >= kbuf->size)
			वापस -1;
		type = update_poपूर्णांकers(kbuf);
	पूर्ण जबतक (type == KBUFFER_TYPE_TIME_EXTEND ||
		 type == KBUFFER_TYPE_TIME_STAMP ||
		 type == KBUFFER_TYPE_PADDING);

	वापस 0;
पूर्ण

अटल पूर्णांक next_event(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->next_event(kbuf);
पूर्ण

/**
 * kbuffer_next_event - increment the current poपूर्णांकer
 * @kbuf:	The kbuffer to पढ़ो
 * @ts:		Address to store the next record's बारtamp (may be शून्य to ignore)
 *
 * Increments the poपूर्णांकers पूर्णांकo the subbuffer of the kbuffer to poपूर्णांक to the
 * next event so that the next kbuffer_पढ़ो_event() will वापस a
 * new event.
 *
 * Returns the data of the next event अगर a new event exists on the subbuffer,
 * शून्य otherwise.
 */
व्योम *kbuffer_next_event(काष्ठा kbuffer *kbuf, अचिन्हित दीर्घ दीर्घ *ts)
अणु
	पूर्णांक ret;

	अगर (!kbuf || !kbuf->subbuffer)
		वापस शून्य;

	ret = next_event(kbuf);
	अगर (ret < 0)
		वापस शून्य;

	अगर (ts)
		*ts = kbuf->बारtamp;

	वापस kbuf->data + kbuf->index;
पूर्ण

/**
 * kbuffer_load_subbuffer - load a new subbuffer पूर्णांकo the kbuffer
 * @kbuf:	The kbuffer to load
 * @subbuffer:	The subbuffer to load पूर्णांकo @kbuf.
 *
 * Load a new subbuffer (page) पूर्णांकo @kbuf. This will reset all
 * the poपूर्णांकers and update the @kbuf बारtamp. The next पढ़ो will
 * वापस the first event on @subbuffer.
 *
 * Returns 0 on succes, -1 otherwise.
 */
पूर्णांक kbuffer_load_subbuffer(काष्ठा kbuffer *kbuf, व्योम *subbuffer)
अणु
	अचिन्हित दीर्घ दीर्घ flags;
	व्योम *ptr = subbuffer;

	अगर (!kbuf || !subbuffer)
		वापस -1;

	kbuf->subbuffer = subbuffer;

	kbuf->बारtamp = पढ़ो_8(kbuf, ptr);
	ptr += 8;

	kbuf->curr = 0;

	अगर (kbuf->flags & KBUFFER_FL_LONG_8)
		kbuf->start = 16;
	अन्यथा
		kbuf->start = 12;

	kbuf->data = subbuffer + kbuf->start;

	flags = पढ़ो_दीर्घ(kbuf, ptr);
	kbuf->size = (अचिन्हित पूर्णांक)flags & COMMIT_MASK;

	अगर (flags & MISSING_EVENTS) अणु
		अगर (flags & MISSING_STORED) अणु
			ptr = kbuf->data + kbuf->size;
			kbuf->lost_events = पढ़ो_दीर्घ(kbuf, ptr);
		पूर्ण अन्यथा
			kbuf->lost_events = -1;
	पूर्ण अन्यथा
		kbuf->lost_events = 0;

	kbuf->index = 0;
	kbuf->next = 0;

	next_event(kbuf);

	वापस 0;
पूर्ण

/**
 * kbuffer_subbuf_बारtamp - पढ़ो the बारtamp from a sub buffer
 * @kbuf:      The kbuffer to load
 * @subbuf:    The subbuffer to पढ़ो from.
 *
 * Return the बारtamp from a subbuffer.
 */
अचिन्हित दीर्घ दीर्घ kbuffer_subbuf_बारtamp(काष्ठा kbuffer *kbuf, व्योम *subbuf)
अणु
	वापस kbuf->पढ़ो_8(subbuf);
पूर्ण

/**
 * kbuffer_ptr_delta - पढ़ो the delta field from a record
 * @kbuf:      The kbuffer to load
 * @ptr:       The record in the buffe.
 *
 * Return the बारtamp delta from a record
 */
अचिन्हित पूर्णांक kbuffer_ptr_delta(काष्ठा kbuffer *kbuf, व्योम *ptr)
अणु
	अचिन्हित पूर्णांक type_len_ts;

	type_len_ts = पढ़ो_4(kbuf, ptr);
	वापस ts4host(kbuf, type_len_ts);
पूर्ण


/**
 * kbuffer_पढ़ो_event - पढ़ो the next event in the kbuffer subbuffer
 * @kbuf:	The kbuffer to पढ़ो from
 * @ts:		The address to store the बारtamp of the event (may be शून्य to ignore)
 *
 * Returns a poपूर्णांकer to the data part of the current event.
 * शून्य अगर no event is left on the subbuffer.
 */
व्योम *kbuffer_पढ़ो_event(काष्ठा kbuffer *kbuf, अचिन्हित दीर्घ दीर्घ *ts)
अणु
	अगर (!kbuf || !kbuf->subbuffer)
		वापस शून्य;

	अगर (kbuf->curr >= kbuf->size)
		वापस शून्य;

	अगर (ts)
		*ts = kbuf->बारtamp;
	वापस kbuf->data + kbuf->index;
पूर्ण

/**
 * kbuffer_बारtamp - Return the बारtamp of the current event
 * @kbuf:	The kbuffer to पढ़ो from
 *
 * Returns the बारtamp of the current (next) event.
 */
अचिन्हित दीर्घ दीर्घ kbuffer_बारtamp(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->बारtamp;
पूर्ण

/**
 * kbuffer_पढ़ो_at_offset - पढ़ो the event that is at offset
 * @kbuf:	The kbuffer to पढ़ो from
 * @offset:	The offset पूर्णांकo the subbuffer
 * @ts:		The address to store the बारtamp of the event (may be शून्य to ignore)
 *
 * The @offset must be an index from the @kbuf subbuffer beginning.
 * If @offset is bigger than the stored subbuffer, शून्य will be वापसed.
 *
 * Returns the data of the record that is at @offset. Note, @offset करोes
 * not need to be the start of the record, the offset just needs to be
 * in the record (or beginning of it).
 *
 * Note, the kbuf बारtamp and poपूर्णांकers are updated to the
 * वापसed record. That is, kbuffer_पढ़ो_event() will वापस the same
 * data and बारtamp, and kbuffer_next_event() will increment from
 * this record.
 */
व्योम *kbuffer_पढ़ो_at_offset(काष्ठा kbuffer *kbuf, पूर्णांक offset,
			     अचिन्हित दीर्घ दीर्घ *ts)
अणु
	व्योम *data;

	अगर (offset < kbuf->start)
		offset = 0;
	अन्यथा
		offset -= kbuf->start;

	/* Reset the buffer */
	kbuffer_load_subbuffer(kbuf, kbuf->subbuffer);
	data = kbuffer_पढ़ो_event(kbuf, ts);

	जबतक (kbuf->curr < offset) अणु
		data = kbuffer_next_event(kbuf, ts);
		अगर (!data)
			अवरोध;
	पूर्ण

	वापस data;
पूर्ण

/**
 * kbuffer_subbuffer_size - the size of the loaded subbuffer
 * @kbuf:	The kbuffer to पढ़ो from
 *
 * Returns the size of the subbuffer. Note, this size is
 * where the last event resides. The stored subbuffer may actually be
 * bigger due to padding and such.
 */
पूर्णांक kbuffer_subbuffer_size(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->size;
पूर्ण

/**
 * kbuffer_curr_index - Return the index of the record
 * @kbuf:	The kbuffer to पढ़ो from
 *
 * Returns the index from the start of the data part of
 * the subbuffer to the current location. Note this is not
 * from the start of the subbuffer. An index of zero will
 * poपूर्णांक to the first record. Use kbuffer_curr_offset() क्रम
 * the actually offset (that can be used by kbuffer_पढ़ो_at_offset())
 */
पूर्णांक kbuffer_curr_index(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->curr;
पूर्ण

/**
 * kbuffer_curr_offset - Return the offset of the record
 * @kbuf:	The kbuffer to पढ़ो from
 *
 * Returns the offset from the start of the subbuffer to the
 * current location.
 */
पूर्णांक kbuffer_curr_offset(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->curr + kbuf->start;
पूर्ण

/**
 * kbuffer_event_size - वापस the size of the event data
 * @kbuf:	The kbuffer to पढ़ो
 *
 * Returns the size of the event data (the payload not counting
 * the meta data of the record) of the current event.
 */
पूर्णांक kbuffer_event_size(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->next - kbuf->index;
पूर्ण

/**
 * kbuffer_curr_size - वापस the size of the entire record
 * @kbuf:	The kbuffer to पढ़ो
 *
 * Returns the size of the entire record (meta data and payload)
 * of the current event.
 */
पूर्णांक kbuffer_curr_size(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->next - kbuf->curr;
पूर्ण

/**
 * kbuffer_missed_events - वापस the # of missed events from last event.
 * @kbuf: 	The kbuffer to पढ़ो from
 *
 * Returns the # of missed events (अगर recorded) beक्रमe the current
 * event. Note, only events on the beginning of a subbuffer can
 * have missed events, all other events within the buffer will be
 * zero.
 */
पूर्णांक kbuffer_missed_events(काष्ठा kbuffer *kbuf)
अणु
	/* Only the first event can have missed events */
	अगर (kbuf->curr)
		वापस 0;

	वापस kbuf->lost_events;
पूर्ण

/**
 * kbuffer_set_old_क्रमma - set the kbuffer to use the old क्रमmat parsing
 * @kbuf:	The kbuffer to set
 *
 * This is obsolete (or should be). The first kernels to use the
 * new ring buffer had a slightly dअगरferent ring buffer क्रमmat
 * (2.6.30 and earlier). It is still somewhat supported by kbuffer,
 * but should not be counted on in the future.
 */
व्योम kbuffer_set_old_क्रमmat(काष्ठा kbuffer *kbuf)
अणु
	kbuf->flags |= KBUFFER_FL_OLD_FORMAT;

	kbuf->next_event = __old_next_event;
पूर्ण

/**
 * kbuffer_start_of_data - वापस offset of where data starts on subbuffer
 * @kbuf:	The kbuffer
 *
 * Returns the location on the subbuffer where the data starts.
 */
पूर्णांक kbuffer_start_of_data(काष्ठा kbuffer *kbuf)
अणु
	वापस kbuf->start;
पूर्ण

/**
 * kbuffer_raw_get - get raw buffer info
 * @kbuf:	The kbuffer
 * @subbuf:	Start of mapped subbuffer
 * @info:	Info descriptor to fill in
 *
 * For debugging. This can वापस पूर्णांकernals of the ring buffer.
 * Expects to have info->next set to what it will पढ़ो.
 * The type, length and बारtamp delta will be filled in, and
 * @info->next will be updated to the next element.
 * The @subbuf is used to know अगर the info is passed the end of
 * data and शून्य will be वापसed अगर it is.
 */
काष्ठा kbuffer_raw_info *
kbuffer_raw_get(काष्ठा kbuffer *kbuf, व्योम *subbuf, काष्ठा kbuffer_raw_info *info)
अणु
	अचिन्हित दीर्घ दीर्घ flags;
	अचिन्हित दीर्घ दीर्घ delta;
	अचिन्हित पूर्णांक type_len;
	अचिन्हित पूर्णांक size;
	पूर्णांक start;
	पूर्णांक length;
	व्योम *ptr = info->next;

	अगर (!kbuf || !subbuf)
		वापस शून्य;

	अगर (kbuf->flags & KBUFFER_FL_LONG_8)
		start = 16;
	अन्यथा
		start = 12;

	flags = पढ़ो_दीर्घ(kbuf, subbuf + 8);
	size = (अचिन्हित पूर्णांक)flags & COMMIT_MASK;

	अगर (ptr < subbuf || ptr >= subbuf + start + size)
		वापस शून्य;

	type_len = translate_data(kbuf, ptr, &ptr, &delta, &length);

	info->next = ptr + length;

	info->type = type_len;
	info->delta = delta;
	info->length = length;

	वापस info;
पूर्ण
