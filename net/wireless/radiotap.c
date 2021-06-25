<शैली गुरु>
/*
 * Radiotap parser
 *
 * Copyright 2007		Andy Green <andy@warmcat.com>
 * Copyright 2009		Johannes Berg <johannes@sipsolutions.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See COPYING क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <यंत्र/unaligned.h>

/* function prototypes and related defs are in include/net/cfg80211.h */

अटल स्थिर काष्ठा radiotap_align_size rtap_namespace_sizes[] = अणु
	[IEEE80211_RADIOTAP_TSFT] = अणु .align = 8, .size = 8, पूर्ण,
	[IEEE80211_RADIOTAP_FLAGS] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_RATE] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_CHANNEL] = अणु .align = 2, .size = 4, पूर्ण,
	[IEEE80211_RADIOTAP_FHSS] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_DBM_ANTNOISE] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_LOCK_QUALITY] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_TX_ATTENUATION] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_DBM_TX_POWER] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_ANTENNA] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_DB_ANTSIGNAL] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_DB_ANTNOISE] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_RX_FLAGS] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_TX_FLAGS] = अणु .align = 2, .size = 2, पूर्ण,
	[IEEE80211_RADIOTAP_RTS_RETRIES] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_DATA_RETRIES] = अणु .align = 1, .size = 1, पूर्ण,
	[IEEE80211_RADIOTAP_MCS] = अणु .align = 1, .size = 3, पूर्ण,
	[IEEE80211_RADIOTAP_AMPDU_STATUS] = अणु .align = 4, .size = 8, पूर्ण,
	[IEEE80211_RADIOTAP_VHT] = अणु .align = 2, .size = 12, पूर्ण,
	/*
	 * add more here as they are defined in radiotap.h
	 */
पूर्ण;

अटल स्थिर काष्ठा ieee80211_radiotap_namespace radiotap_ns = अणु
	.n_bits = ARRAY_SIZE(rtap_namespace_sizes),
	.align_size = rtap_namespace_sizes,
पूर्ण;

/**
 * ieee80211_radiotap_iterator_init - radiotap parser iterator initialization
 * @iterator: radiotap_iterator to initialize
 * @radiotap_header: radiotap header to parse
 * @max_length: total length we can parse पूर्णांकo (eg, whole packet length)
 * @vns: venकरोr namespaces to parse
 *
 * Returns: 0 or a negative error code अगर there is a problem.
 *
 * This function initializes an opaque iterator काष्ठा which can then
 * be passed to ieee80211_radiotap_iterator_next() to visit every radiotap
 * argument which is present in the header.  It knows about extended
 * present headers and handles them.
 *
 * How to use:
 * call __ieee80211_radiotap_iterator_init() to init a semi-opaque iterator
 * काष्ठा ieee80211_radiotap_iterator (no need to init the काष्ठा beक्रमehand)
 * checking क्रम a good 0 वापस code.  Then loop calling
 * __ieee80211_radiotap_iterator_next()... it वापसs either 0,
 * -ENOENT अगर there are no more args to parse, or -EINVAL अगर there is a problem.
 * The iterator's @this_arg member poपूर्णांकs to the start of the argument
 * associated with the current argument index that is present, which can be
 * found in the iterator's @this_arg_index member.  This arg index corresponds
 * to the IEEE80211_RADIOTAP_... defines.
 *
 * Radiotap header length:
 * You can find the CPU-endian total radiotap header length in
 * iterator->max_length after executing ieee80211_radiotap_iterator_init()
 * successfully.
 *
 * Alignment Gotcha:
 * You must take care when dereferencing iterator.this_arg
 * क्रम multibyte types... the poपूर्णांकer is not aligned.  Use
 * get_unaligned((type *)iterator.this_arg) to dereference
 * iterator.this_arg क्रम type "type" safely on all arches.
 *
 * Example code:
 * See Documentation/networking/radiotap-headers.rst
 */

पूर्णांक ieee80211_radiotap_iterator_init(
	काष्ठा ieee80211_radiotap_iterator *iterator,
	काष्ठा ieee80211_radiotap_header *radiotap_header,
	पूर्णांक max_length, स्थिर काष्ठा ieee80211_radiotap_venकरोr_namespaces *vns)
अणु
	/* check the radiotap header can actually be present */
	अगर (max_length < माप(काष्ठा ieee80211_radiotap_header))
		वापस -EINVAL;

	/* Linux only supports version 0 radiotap क्रमmat */
	अगर (radiotap_header->it_version)
		वापस -EINVAL;

	/* sanity check क्रम allowed length and radiotap length field */
	अगर (max_length < get_unaligned_le16(&radiotap_header->it_len))
		वापस -EINVAL;

	iterator->_rtheader = radiotap_header;
	iterator->_max_length = get_unaligned_le16(&radiotap_header->it_len);
	iterator->_arg_index = 0;
	iterator->_biपंचांगap_shअगरter = get_unaligned_le32(&radiotap_header->it_present);
	iterator->_arg = (uपूर्णांक8_t *)radiotap_header + माप(*radiotap_header);
	iterator->_reset_on_ext = 0;
	iterator->_next_biपंचांगap = &radiotap_header->it_present;
	iterator->_next_biपंचांगap++;
	iterator->_vns = vns;
	iterator->current_namespace = &radiotap_ns;
	iterator->is_radiotap_ns = 1;

	/* find payload start allowing क्रम extended biपंचांगap(s) */

	अगर (iterator->_biपंचांगap_shअगरter & (1<<IEEE80211_RADIOTAP_EXT)) अणु
		अगर ((अचिन्हित दीर्घ)iterator->_arg -
		    (अचिन्हित दीर्घ)iterator->_rtheader + माप(uपूर्णांक32_t) >
		    (अचिन्हित दीर्घ)iterator->_max_length)
			वापस -EINVAL;
		जबतक (get_unaligned_le32(iterator->_arg) &
					(1 << IEEE80211_RADIOTAP_EXT)) अणु
			iterator->_arg += माप(uपूर्णांक32_t);

			/*
			 * check क्रम insanity where the present biपंचांगaps
			 * keep claiming to extend up to or even beyond the
			 * stated radiotap header length
			 */

			अगर ((अचिन्हित दीर्घ)iterator->_arg -
			    (अचिन्हित दीर्घ)iterator->_rtheader +
			    माप(uपूर्णांक32_t) >
			    (अचिन्हित दीर्घ)iterator->_max_length)
				वापस -EINVAL;
		पूर्ण

		iterator->_arg += माप(uपूर्णांक32_t);

		/*
		 * no need to check again क्रम blowing past stated radiotap
		 * header length, because ieee80211_radiotap_iterator_next
		 * checks it beक्रमe it is dereferenced
		 */
	पूर्ण

	iterator->this_arg = iterator->_arg;

	/* we are all initialized happily */

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ieee80211_radiotap_iterator_init);

अटल व्योम find_ns(काष्ठा ieee80211_radiotap_iterator *iterator,
		    uपूर्णांक32_t oui, uपूर्णांक8_t subns)
अणु
	पूर्णांक i;

	iterator->current_namespace = शून्य;

	अगर (!iterator->_vns)
		वापस;

	क्रम (i = 0; i < iterator->_vns->n_ns; i++) अणु
		अगर (iterator->_vns->ns[i].oui != oui)
			जारी;
		अगर (iterator->_vns->ns[i].subns != subns)
			जारी;

		iterator->current_namespace = &iterator->_vns->ns[i];
		अवरोध;
	पूर्ण
पूर्ण



/**
 * ieee80211_radiotap_iterator_next - वापस next radiotap parser iterator arg
 * @iterator: radiotap_iterator to move to next arg (अगर any)
 *
 * Returns: 0 अगर there is an argument to handle,
 * -ENOENT अगर there are no more args or -EINVAL
 * अगर there is something अन्यथा wrong.
 *
 * This function provides the next radiotap arg index (IEEE80211_RADIOTAP_*)
 * in @this_arg_index and sets @this_arg to poपूर्णांक to the
 * payload क्रम the field.  It takes care of alignment handling and extended
 * present fields.  @this_arg can be changed by the caller (eg,
 * incremented to move inside a compound argument like
 * IEEE80211_RADIOTAP_CHANNEL).  The args poपूर्णांकed to are in
 * little-endian क्रमmat whatever the endianess of your CPU.
 *
 * Alignment Gotcha:
 * You must take care when dereferencing iterator.this_arg
 * क्रम multibyte types... the poपूर्णांकer is not aligned.  Use
 * get_unaligned((type *)iterator.this_arg) to dereference
 * iterator.this_arg क्रम type "type" safely on all arches.
 */

पूर्णांक ieee80211_radiotap_iterator_next(
	काष्ठा ieee80211_radiotap_iterator *iterator)
अणु
	जबतक (1) अणु
		पूर्णांक hit = 0;
		पूर्णांक pad, align, size, subns;
		uपूर्णांक32_t oui;

		/* अगर no more EXT bits, that's it */
		अगर ((iterator->_arg_index % 32) == IEEE80211_RADIOTAP_EXT &&
		    !(iterator->_biपंचांगap_shअगरter & 1))
			वापस -ENOENT;

		अगर (!(iterator->_biपंचांगap_shअगरter & 1))
			जाओ next_entry; /* arg not present */

		/* get alignment/size of data */
		चयन (iterator->_arg_index % 32) अणु
		हाल IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE:
		हाल IEEE80211_RADIOTAP_EXT:
			align = 1;
			size = 0;
			अवरोध;
		हाल IEEE80211_RADIOTAP_VENDOR_NAMESPACE:
			align = 2;
			size = 6;
			अवरोध;
		शेष:
			अगर (!iterator->current_namespace ||
			    iterator->_arg_index >= iterator->current_namespace->n_bits) अणु
				अगर (iterator->current_namespace == &radiotap_ns)
					वापस -ENOENT;
				align = 0;
			पूर्ण अन्यथा अणु
				align = iterator->current_namespace->align_size[iterator->_arg_index].align;
				size = iterator->current_namespace->align_size[iterator->_arg_index].size;
			पूर्ण
			अगर (!align) अणु
				/* skip all subsequent data */
				iterator->_arg = iterator->_next_ns_data;
				/* give up on this namespace */
				iterator->current_namespace = शून्य;
				जाओ next_entry;
			पूर्ण
			अवरोध;
		पूर्ण

		/*
		 * arg is present, account क्रम alignment padding
		 *
		 * Note that these alignments are relative to the start
		 * of the radiotap header.  There is no guarantee
		 * that the radiotap header itself is aligned on any
		 * kind of boundary.
		 *
		 * The above is why get_unaligned() is used to dereference
		 * multibyte elements from the radiotap area.
		 */

		pad = ((अचिन्हित दीर्घ)iterator->_arg -
		       (अचिन्हित दीर्घ)iterator->_rtheader) & (align - 1);

		अगर (pad)
			iterator->_arg += align - pad;

		अगर (iterator->_arg_index % 32 == IEEE80211_RADIOTAP_VENDOR_NAMESPACE) अणु
			पूर्णांक vnslen;

			अगर ((अचिन्हित दीर्घ)iterator->_arg + size -
			    (अचिन्हित दीर्घ)iterator->_rtheader >
			    (अचिन्हित दीर्घ)iterator->_max_length)
				वापस -EINVAL;

			oui = (*iterator->_arg << 16) |
				(*(iterator->_arg + 1) << 8) |
				*(iterator->_arg + 2);
			subns = *(iterator->_arg + 3);

			find_ns(iterator, oui, subns);

			vnslen = get_unaligned_le16(iterator->_arg + 4);
			iterator->_next_ns_data = iterator->_arg + size + vnslen;
			अगर (!iterator->current_namespace)
				size += vnslen;
		पूर्ण

		/*
		 * this is what we will वापस to user, but we need to
		 * move on first so next call has something fresh to test
		 */
		iterator->this_arg_index = iterator->_arg_index;
		iterator->this_arg = iterator->_arg;
		iterator->this_arg_size = size;

		/* पूर्णांकernally move on the size of this arg */
		iterator->_arg += size;

		/*
		 * check क्रम insanity where we are given a biपंचांगap that
		 * claims to have more arg content than the length of the
		 * radiotap section.  We will normally end up equalling this
		 * max_length on the last arg, never exceeding it.
		 */

		अगर ((अचिन्हित दीर्घ)iterator->_arg -
		    (अचिन्हित दीर्घ)iterator->_rtheader >
		    (अचिन्हित दीर्घ)iterator->_max_length)
			वापस -EINVAL;

		/* these special ones are valid in each biपंचांगap word */
		चयन (iterator->_arg_index % 32) अणु
		हाल IEEE80211_RADIOTAP_VENDOR_NAMESPACE:
			iterator->_reset_on_ext = 1;

			iterator->is_radiotap_ns = 0;
			/*
			 * If parser didn't रेजिस्टर this venकरोr
			 * namespace with us, allow it to show it
			 * as 'raw. Do करो that, set argument index
			 * to venकरोr namespace.
			 */
			iterator->this_arg_index =
				IEEE80211_RADIOTAP_VENDOR_NAMESPACE;
			अगर (!iterator->current_namespace)
				hit = 1;
			जाओ next_entry;
		हाल IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE:
			iterator->_reset_on_ext = 1;
			iterator->current_namespace = &radiotap_ns;
			iterator->is_radiotap_ns = 1;
			जाओ next_entry;
		हाल IEEE80211_RADIOTAP_EXT:
			/*
			 * bit 31 was set, there is more
			 * -- move to next u32 biपंचांगap
			 */
			iterator->_biपंचांगap_shअगरter =
				get_unaligned_le32(iterator->_next_biपंचांगap);
			iterator->_next_biपंचांगap++;
			अगर (iterator->_reset_on_ext)
				iterator->_arg_index = 0;
			अन्यथा
				iterator->_arg_index++;
			iterator->_reset_on_ext = 0;
			अवरोध;
		शेष:
			/* we've got a hit! */
			hit = 1;
 next_entry:
			iterator->_biपंचांगap_shअगरter >>= 1;
			iterator->_arg_index++;
		पूर्ण

		/* अगर we found a valid arg earlier, वापस it now */
		अगर (hit)
			वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_radiotap_iterator_next);
