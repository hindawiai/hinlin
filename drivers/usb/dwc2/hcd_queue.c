<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * hcd_queue.c - DesignWare HS OTG Controller host queuing routines
 *
 * Copyright (C) 2004-2013 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file contains the functions to manage Queue Heads and Queue
 * Transfer Descriptors क्रम Host mode
 */
#समावेश <linux/gcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ch11.h>

#समावेश "core.h"
#समावेश "hcd.h"

/* Wait this दीर्घ beक्रमe releasing periodic reservation */
#घोषणा DWC2_UNRESERVE_DELAY (msecs_to_jअगरfies(5))

/* If we get a NAK, रुको this दीर्घ beक्रमe retrying */
#घोषणा DWC2_RETRY_WAIT_DELAY (1 * 1E6L)

/**
 * dwc2_periodic_channel_available() - Checks that a channel is available क्रम a
 * periodic transfer
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
अटल पूर्णांक dwc2_periodic_channel_available(काष्ठा dwc2_hsotg *hsotg)
अणु
	/*
	 * Currently assuming that there is a dedicated host channel क्रम
	 * each periodic transaction plus at least one host channel क्रम
	 * non-periodic transactions
	 */
	पूर्णांक status;
	पूर्णांक num_channels;

	num_channels = hsotg->params.host_channels;
	अगर ((hsotg->periodic_channels + hsotg->non_periodic_channels <
	     num_channels) && (hsotg->periodic_channels < num_channels - 1)) अणु
		status = 0;
	पूर्ण अन्यथा अणु
		dev_dbg(hsotg->dev,
			"%s: Total channels: %d, Periodic: %d, Non-periodic: %d\n",
			__func__, num_channels,
			hsotg->periodic_channels, hsotg->non_periodic_channels);
		status = -ENOSPC;
	पूर्ण

	वापस status;
पूर्ण

/**
 * dwc2_check_periodic_bandwidth() - Checks that there is sufficient bandwidth
 * क्रम the specअगरied QH in the periodic schedule
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH containing periodic bandwidth required
 *
 * Return: 0 अगर successful, negative error code otherwise
 *
 * For simplicity, this calculation assumes that all the transfers in the
 * periodic schedule may occur in the same (micro)frame
 */
अटल पूर्णांक dwc2_check_periodic_bandwidth(काष्ठा dwc2_hsotg *hsotg,
					 काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक status;
	s16 max_claimed_usecs;

	status = 0;

	अगर (qh->dev_speed == USB_SPEED_HIGH || qh->करो_split) अणु
		/*
		 * High speed mode
		 * Max periodic usecs is 80% x 125 usec = 100 usec
		 */
		max_claimed_usecs = 100 - qh->host_us;
	पूर्ण अन्यथा अणु
		/*
		 * Full speed mode
		 * Max periodic usecs is 90% x 1000 usec = 900 usec
		 */
		max_claimed_usecs = 900 - qh->host_us;
	पूर्ण

	अगर (hsotg->periodic_usecs > max_claimed_usecs) अणु
		dev_err(hsotg->dev,
			"%s: already claimed usecs %d, required usecs %d\n",
			__func__, hsotg->periodic_usecs, qh->host_us);
		status = -ENOSPC;
	पूर्ण

	वापस status;
पूर्ण

/**
 * pmap_schedule() - Schedule समय in a periodic biपंचांगap (pmap).
 *
 * @map:             The biपंचांगap representing the schedule; will be updated
 *                   upon success.
 * @bits_per_period: The schedule represents several periods.  This is how many
 *                   bits are in each period.  It's assumed that the beginning
 *                   of the schedule will repeat after its end.
 * @periods_in_map:  The number of periods in the schedule.
 * @num_bits:        The number of bits we need per period we want to reserve
 *                   in this function call.
 * @पूर्णांकerval:        How often we need to be scheduled क्रम the reservation this
 *                   समय.  1 means every period.  2 means every other period.
 *                   ...you get the picture?
 * @start:           The bit number to start at.  Normally 0.  Must be within
 *                   the पूर्णांकerval or we वापस failure right away.
 * @only_one_period: Normally we'll allow picking a start anywhere within the
 *                   first पूर्णांकerval, since we can still make all repetition
 *                   requirements by करोing that.  However, अगर you pass true
 *                   here then we'll return failure if we can't fit within
 *                   the period that "start" is in.
 *
 * The idea here is that we want to schedule समय क्रम repeating events that all
 * want the same resource.  The resource is भागided पूर्णांकo fixed-sized periods
 * and the events want to repeat every "interval" periods.  The schedule
 * granularity is one bit.
 *
 * To keep things "simple", we'll represent our schedule with a biपंचांगap that
 * contains a fixed number of periods.  This माला_लो rid of a lot of complनिकासy
 * but करोes mean that we need to handle things specially (and non-ideally) अगर
 * the number of the periods in the schedule करोesn't match well with the
 * पूर्णांकervals that we're trying to schedule.
 *
 * Here's an explanation of the scheme we'll implement, assuming 8 periods.
 * - If पूर्णांकerval is 1, we need to take up space in each of the 8
 *   periods we're scheduling.  Easy.
 * - If पूर्णांकerval is 2, we need to take up space in half of the
 *   periods.  Again, easy.
 * - If पूर्णांकerval is 3, we actually need to fall back to पूर्णांकerval 1.
 *   Why?  Because we might need समय in any period.  AKA क्रम the
 *   first 8 periods, we'll be in slot 0, 3, 6.  Then we'll be
 *   in slot 1, 4, 7.  Then we'll be in 2, 5.  Then we'll be back to
 *   0, 3, and 6.  Since we could be in any frame we need to reserve
 *   क्रम all of them.  Sucks, but that's what you gotta करो.  Note that
 *   अगर we were instead scheduling 8 * 3 = 24 we'd करो much better, but
 *   then we need more memory and समय to करो scheduling.
 * - If पूर्णांकerval is 4, easy.
 * - If पूर्णांकerval is 5, we again need पूर्णांकerval 1.  The schedule will be
 *   0, 5, 2, 7, 4, 1, 6, 3, 0
 * - If पूर्णांकerval is 6, we need पूर्णांकerval 2.  0, 6, 4, 2.
 * - If पूर्णांकerval is 7, we need पूर्णांकerval 1.
 * - If पूर्णांकerval is 8, we need पूर्णांकerval 8.
 *
 * If you करो the math, you'll see that we need to pretend that पूर्णांकerval is
 * equal to the greatest_common_भागisor(पूर्णांकerval, periods_in_map).
 *
 * Note that at the moment this function tends to front-pack the schedule.
 * In some हालs that's really non-ideal (it's hard to schedule things that
 * need to repeat every period).  In other हालs it's perfect (you can easily
 * schedule bigger, less often repeating things).
 *
 * Here's the algorithm in action (8 periods, 5 bits per period):
 *  |**   |     |**   |     |**   |     |**   |     |   OK 2 bits, पूर्णांकv 2 at 0
 *  |*****|  ***|*****|  ***|*****|  ***|*****|  ***|   OK 3 bits, पूर्णांकv 3 at 2
 *  |*****|* ***|*****|  ***|*****|* ***|*****|  ***|   OK 1 bits, पूर्णांकv 4 at 5
 *  |**   |*    |**   |     |**   |*    |**   |     | Remv 3 bits, पूर्णांकv 3 at 2
 *  |***  |*    |***  |     |***  |*    |***  |     |   OK 1 bits, पूर्णांकv 6 at 2
 *  |**** |*  * |**** |   * |**** |*  * |**** |   * |   OK 1 bits, पूर्णांकv 1 at 3
 *  |**** |**** |**** | *** |**** |**** |**** | *** |   OK 2 bits, पूर्णांकv 2 at 6
 *  |*****|*****|*****| ****|*****|*****|*****| ****|   OK 1 bits, पूर्णांकv 1 at 4
 *  |*****|*****|*****| ****|*****|*****|*****| ****| FAIL 1 bits, पूर्णांकv 1
 *  |  ***|*****|  ***| ****|  ***|*****|  ***| ****| Remv 2 bits, पूर्णांकv 2 at 0
 *  |  ***| ****|  ***| ****|  ***| ****|  ***| ****| Remv 1 bits, पूर्णांकv 4 at 5
 *  |   **| ****|   **| ****|   **| ****|   **| ****| Remv 1 bits, पूर्णांकv 6 at 2
 *  |    *| ** *|    *| ** *|    *| ** *|    *| ** *| Remv 1 bits, पूर्णांकv 1 at 3
 *  |    *|    *|    *|    *|    *|    *|    *|    *| Remv 2 bits, पूर्णांकv 2 at 6
 *  |     |     |     |     |     |     |     |     | Remv 1 bits, पूर्णांकv 1 at 4
 *  |**   |     |**   |     |**   |     |**   |     |   OK 2 bits, पूर्णांकv 2 at 0
 *  |***  |     |**   |     |***  |     |**   |     |   OK 1 bits, पूर्णांकv 4 at 2
 *  |*****|     |** **|     |*****|     |** **|     |   OK 2 bits, पूर्णांकv 2 at 3
 *  |*****|*    |** **|     |*****|*    |** **|     |   OK 1 bits, पूर्णांकv 4 at 5
 *  |*****|***  |** **| **  |*****|***  |** **| **  |   OK 2 bits, पूर्णांकv 2 at 6
 *  |*****|*****|** **| ****|*****|*****|** **| ****|   OK 2 bits, पूर्णांकv 2 at 8
 *  |*****|*****|*****| ****|*****|*****|*****| ****|   OK 1 bits, पूर्णांकv 4 at 12
 *
 * This function is pretty generic and could be easily असलtracted अगर anything
 * needed similar scheduling.
 *
 * Returns either -ENOSPC or a >= 0 start bit which should be passed to the
 * unschedule routine.  The map biपंचांगap will be updated on a non-error result.
 */
अटल पूर्णांक pmap_schedule(अचिन्हित दीर्घ *map, पूर्णांक bits_per_period,
			 पूर्णांक periods_in_map, पूर्णांक num_bits,
			 पूर्णांक पूर्णांकerval, पूर्णांक start, bool only_one_period)
अणु
	पूर्णांक पूर्णांकerval_bits;
	पूर्णांक to_reserve;
	पूर्णांक first_end;
	पूर्णांक i;

	अगर (num_bits > bits_per_period)
		वापस -ENOSPC;

	/* Adjust पूर्णांकerval as per description */
	पूर्णांकerval = gcd(पूर्णांकerval, periods_in_map);

	पूर्णांकerval_bits = bits_per_period * पूर्णांकerval;
	to_reserve = periods_in_map / पूर्णांकerval;

	/* If start has gotten us past पूर्णांकerval then we can't schedule */
	अगर (start >= पूर्णांकerval_bits)
		वापस -ENOSPC;

	अगर (only_one_period)
		/* Must fit within same period as start; end at begin of next */
		first_end = (start / bits_per_period + 1) * bits_per_period;
	अन्यथा
		/* Can fit anywhere in the first पूर्णांकerval */
		first_end = पूर्णांकerval_bits;

	/*
	 * We'll try to pick the first repetition, then see अगर that समय
	 * is मुक्त क्रम each of the subsequent repetitions.  If it's not
	 * we'll adjust the start समय क्रम the next search of the first
	 * repetition.
	 */
	जबतक (start + num_bits <= first_end) अणु
		पूर्णांक end;

		/* Need to stay within this period */
		end = (start / bits_per_period + 1) * bits_per_period;

		/* Look क्रम num_bits us in this microframe starting at start */
		start = biपंचांगap_find_next_zero_area(map, end, start, num_bits,
						   0);

		/*
		 * We should get start >= end अगर we fail.  We might be
		 * able to check the next microframe depending on the
		 * पूर्णांकerval, so जारी on (start alपढ़ोy updated).
		 */
		अगर (start >= end) अणु
			start = end;
			जारी;
		पूर्ण

		/* At this poपूर्णांक we have a valid poपूर्णांक क्रम first one */
		क्रम (i = 1; i < to_reserve; i++) अणु
			पूर्णांक ith_start = start + पूर्णांकerval_bits * i;
			पूर्णांक ith_end = end + पूर्णांकerval_bits * i;
			पूर्णांक ret;

			/* Use this as a dumb "check if bits are 0" */
			ret = biपंचांगap_find_next_zero_area(
				map, ith_start + num_bits, ith_start, num_bits,
				0);

			/* We got the right place, जारी checking */
			अगर (ret == ith_start)
				जारी;

			/* Move start up क्रम next समय and निकास क्रम loop */
			ith_start = biपंचांगap_find_next_zero_area(
				map, ith_end, ith_start, num_bits, 0);
			अगर (ith_start >= ith_end)
				/* Need a जबतक new period next समय */
				start = end;
			अन्यथा
				start = ith_start - पूर्णांकerval_bits * i;
			अवरोध;
		पूर्ण

		/* If didn't निकास the क्रम loop with a अवरोध, we have success */
		अगर (i == to_reserve)
			अवरोध;
	पूर्ण

	अगर (start + num_bits > first_end)
		वापस -ENOSPC;

	क्रम (i = 0; i < to_reserve; i++) अणु
		पूर्णांक ith_start = start + पूर्णांकerval_bits * i;

		biपंचांगap_set(map, ith_start, num_bits);
	पूर्ण

	वापस start;
पूर्ण

/**
 * pmap_unschedule() - Unकरो work करोne by pmap_schedule()
 *
 * @map:             See pmap_schedule().
 * @bits_per_period: See pmap_schedule().
 * @periods_in_map:  See pmap_schedule().
 * @num_bits:        The number of bits that was passed to schedule.
 * @पूर्णांकerval:        The पूर्णांकerval that was passed to schedule.
 * @start:           The वापस value from pmap_schedule().
 */
अटल व्योम pmap_unschedule(अचिन्हित दीर्घ *map, पूर्णांक bits_per_period,
			    पूर्णांक periods_in_map, पूर्णांक num_bits,
			    पूर्णांक पूर्णांकerval, पूर्णांक start)
अणु
	पूर्णांक पूर्णांकerval_bits;
	पूर्णांक to_release;
	पूर्णांक i;

	/* Adjust पूर्णांकerval as per description in pmap_schedule() */
	पूर्णांकerval = gcd(पूर्णांकerval, periods_in_map);

	पूर्णांकerval_bits = bits_per_period * पूर्णांकerval;
	to_release = periods_in_map / पूर्णांकerval;

	क्रम (i = 0; i < to_release; i++) अणु
		पूर्णांक ith_start = start + पूर्णांकerval_bits * i;

		biपंचांगap_clear(map, ith_start, num_bits);
	पूर्ण
पूर्ण

/**
 * dwc2_get_ls_map() - Get the map used क्रम the given qh
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:    QH क्रम the periodic transfer.
 *
 * We'll always get the periodic map out of our TT.  Note that even if we're
 * running the host straight in low speed / full speed mode it appears as अगर
 * a TT is allocated क्रम us, so we'll use it.  If that ever changes we can
 * add logic here to get a map out of "hsotg" अगर !qh->करो_split.
 *
 * Returns: the map or शून्य अगर a map couldn't be found.
 */
अटल अचिन्हित दीर्घ *dwc2_get_ls_map(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_qh *qh)
अणु
	अचिन्हित दीर्घ *map;

	/* Don't expect to be missing a TT and be करोing low speed scheduling */
	अगर (WARN_ON(!qh->dwc_tt))
		वापस शून्य;

	/* Get the map and adjust अगर this is a multi_tt hub */
	map = qh->dwc_tt->periodic_biपंचांगaps;
	अगर (qh->dwc_tt->usb_tt->multi)
		map += DWC2_ELEMENTS_PER_LS_BITMAP * (qh->ttport - 1);

	वापस map;
पूर्ण

#अगर_घोषित DWC2_PRINT_SCHEDULE
/*
 * cat_म_लिखो() - A म_लिखो() + म_जोड़ो() helper
 *
 * This is useful क्रम concatenating a bunch of strings where each string is
 * स्थिरructed using म_लिखो.
 *
 * @buf:   The destination buffer; will be updated to poपूर्णांक after the prपूर्णांकed
 *         data.
 * @size:  The number of bytes in the buffer (includes space क्रम '\0').
 * @fmt:   The क्रमmat क्रम म_लिखो.
 * @...:   The args क्रम म_लिखो.
 */
अटल __म_लिखो(3, 4)
व्योम cat_म_लिखो(अक्षर **buf, माप_प्रकार *size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	अगर (*size == 0)
		वापस;

	बहु_शुरू(args, fmt);
	i = vsnम_लिखो(*buf, *size, fmt, args);
	बहु_पूर्ण(args);

	अगर (i >= *size) अणु
		(*buf)[*size - 1] = '\0';
		*buf += *size;
		*size = 0;
	पूर्ण अन्यथा अणु
		*buf += i;
		*size -= i;
	पूर्ण
पूर्ण

/*
 * pmap_prपूर्णांक() - Prपूर्णांक the given periodic map
 *
 * Will attempt to prपूर्णांक out the periodic schedule.
 *
 * @map:             See pmap_schedule().
 * @bits_per_period: See pmap_schedule().
 * @periods_in_map:  See pmap_schedule().
 * @period_name:     The name of 1 period, like "uFrame"
 * @units:           The name of the units, like "us".
 * @prपूर्णांक_fn:        The function to call क्रम prपूर्णांकing.
 * @prपूर्णांक_data:      Opaque data to pass to the prपूर्णांक function.
 */
अटल व्योम pmap_prपूर्णांक(अचिन्हित दीर्घ *map, पूर्णांक bits_per_period,
		       पूर्णांक periods_in_map, स्थिर अक्षर *period_name,
		       स्थिर अक्षर *units,
		       व्योम (*prपूर्णांक_fn)(स्थिर अक्षर *str, व्योम *data),
		       व्योम *prपूर्णांक_data)
अणु
	पूर्णांक period;

	क्रम (period = 0; period < periods_in_map; period++) अणु
		अक्षर पंचांगp[64];
		अक्षर *buf = पंचांगp;
		माप_प्रकार buf_size = माप(पंचांगp);
		पूर्णांक period_start = period * bits_per_period;
		पूर्णांक period_end = period_start + bits_per_period;
		पूर्णांक start = 0;
		पूर्णांक count = 0;
		bool prपूर्णांकed = false;
		पूर्णांक i;

		क्रम (i = period_start; i < period_end + 1; i++) अणु
			/* Handle हाल when ith bit is set */
			अगर (i < period_end &&
			    biपंचांगap_find_next_zero_area(map, i + 1,
						       i, 1, 0) != i) अणु
				अगर (count == 0)
					start = i - period_start;
				count++;
				जारी;
			पूर्ण

			/* ith bit isn't set; don't care अगर count == 0 */
			अगर (count == 0)
				जारी;

			अगर (!prपूर्णांकed)
				cat_म_लिखो(&buf, &buf_size, "%s %d: ",
					   period_name, period);
			अन्यथा
				cat_म_लिखो(&buf, &buf_size, ", ");
			prपूर्णांकed = true;

			cat_म_लिखो(&buf, &buf_size, "%d %s -%3d %s", start,
				   units, start + count - 1, units);
			count = 0;
		पूर्ण

		अगर (prपूर्णांकed)
			prपूर्णांक_fn(पंचांगp, prपूर्णांक_data);
	पूर्ण
पूर्ण

काष्ठा dwc2_qh_prपूर्णांक_data अणु
	काष्ठा dwc2_hsotg *hsotg;
	काष्ठा dwc2_qh *qh;
पूर्ण;

/**
 * dwc2_qh_prपूर्णांक() - Helper function क्रम dwc2_qh_schedule_prपूर्णांक()
 *
 * @str:  The string to prपूर्णांक
 * @data: A poपूर्णांकer to a काष्ठा dwc2_qh_prपूर्णांक_data
 */
अटल व्योम dwc2_qh_prपूर्णांक(स्थिर अक्षर *str, व्योम *data)
अणु
	काष्ठा dwc2_qh_prपूर्णांक_data *prपूर्णांक_data = data;

	dwc2_sch_dbg(prपूर्णांक_data->hsotg, "QH=%p ...%s\n", prपूर्णांक_data->qh, str);
पूर्ण

/**
 * dwc2_qh_schedule_prपूर्णांक() - Prपूर्णांक the periodic schedule
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:    QH to prपूर्णांक.
 */
अटल व्योम dwc2_qh_schedule_prपूर्णांक(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_qh *qh)
अणु
	काष्ठा dwc2_qh_prपूर्णांक_data prपूर्णांक_data = अणु hsotg, qh पूर्ण;
	पूर्णांक i;

	/*
	 * The prपूर्णांकing functions are quite slow and inefficient.
	 * If we करोn't have tracing turned on, don't run unless the special
	 * define is turned on.
	 */

	अगर (qh->schedule_low_speed) अणु
		अचिन्हित दीर्घ *map = dwc2_get_ls_map(hsotg, qh);

		dwc2_sch_dbg(hsotg, "QH=%p LS/FS trans: %d=>%d us @ %d us",
			     qh, qh->device_us,
			     DWC2_ROUND_US_TO_SLICE(qh->device_us),
			     DWC2_US_PER_SLICE * qh->ls_start_schedule_slice);

		अगर (map) अणु
			dwc2_sch_dbg(hsotg,
				     "QH=%p Whole low/full speed map %p now:\n",
				     qh, map);
			pmap_prपूर्णांक(map, DWC2_LS_PERIODIC_SLICES_PER_FRAME,
				   DWC2_LS_SCHEDULE_FRAMES, "Frame ", "slices",
				   dwc2_qh_prपूर्णांक, &prपूर्णांक_data);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < qh->num_hs_transfers; i++) अणु
		काष्ठा dwc2_hs_transfer_समय *trans_समय = qh->hs_transfers + i;
		पूर्णांक uframe = trans_समय->start_schedule_us /
			     DWC2_HS_PERIODIC_US_PER_UFRAME;
		पूर्णांक rel_us = trans_समय->start_schedule_us %
			     DWC2_HS_PERIODIC_US_PER_UFRAME;

		dwc2_sch_dbg(hsotg,
			     "QH=%p HS trans #%d: %d us @ uFrame %d + %d us\n",
			     qh, i, trans_समय->duration_us, uframe, rel_us);
	पूर्ण
	अगर (qh->num_hs_transfers) अणु
		dwc2_sch_dbg(hsotg, "QH=%p Whole high speed map now:\n", qh);
		pmap_prपूर्णांक(hsotg->hs_periodic_biपंचांगap,
			   DWC2_HS_PERIODIC_US_PER_UFRAME,
			   DWC2_HS_SCHEDULE_UFRAMES, "uFrame", "us",
			   dwc2_qh_prपूर्णांक, &prपूर्णांक_data);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dwc2_qh_schedule_prपूर्णांक(काष्ठा dwc2_hsotg *hsotg,
					  काष्ठा dwc2_qh *qh) अणुपूर्ण;
#पूर्ण_अगर

/**
 * dwc2_ls_pmap_schedule() - Schedule a low speed QH
 *
 * @hsotg:        The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:           QH क्रम the periodic transfer.
 * @search_slice: We'll start trying to schedule at the passed slice.
 *                Remember that slices are the units of the low speed
 *                schedule (think 25us or so).
 *
 * Wraps pmap_schedule() with the right parameters क्रम low speed scheduling.
 *
 * Normally we schedule low speed devices on the map associated with the TT.
 *
 * Returns: 0 क्रम success or an error code.
 */
अटल पूर्णांक dwc2_ls_pmap_schedule(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
				 पूर्णांक search_slice)
अणु
	पूर्णांक slices = DIV_ROUND_UP(qh->device_us, DWC2_US_PER_SLICE);
	अचिन्हित दीर्घ *map = dwc2_get_ls_map(hsotg, qh);
	पूर्णांक slice;

	अगर (!map)
		वापस -EINVAL;

	/*
	 * Schedule on the proper low speed map with our low speed scheduling
	 * parameters.  Note that we use the "device_interval" here since
	 * we want the low speed पूर्णांकerval and the only way we'd be in this
	 * function is अगर the device is low speed.
	 *
	 * If we happen to be करोing low speed and high speed scheduling क्रम the
	 * same transaction (AKA we have a split) we always करो low speed first.
	 * That means we can always pass "false" क्रम only_one_period (that
	 * parameters is only useful when we're trying to get one schedule to
	 * match what we alपढ़ोy planned in the other schedule).
	 */
	slice = pmap_schedule(map, DWC2_LS_PERIODIC_SLICES_PER_FRAME,
			      DWC2_LS_SCHEDULE_FRAMES, slices,
			      qh->device_पूर्णांकerval, search_slice, false);

	अगर (slice < 0)
		वापस slice;

	qh->ls_start_schedule_slice = slice;
	वापस 0;
पूर्ण

/**
 * dwc2_ls_pmap_unschedule() - Unकरो work करोne by dwc2_ls_pmap_schedule()
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल व्योम dwc2_ls_pmap_unschedule(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक slices = DIV_ROUND_UP(qh->device_us, DWC2_US_PER_SLICE);
	अचिन्हित दीर्घ *map = dwc2_get_ls_map(hsotg, qh);

	/* Schedule should have failed, so no worries about no error code */
	अगर (!map)
		वापस;

	pmap_unschedule(map, DWC2_LS_PERIODIC_SLICES_PER_FRAME,
			DWC2_LS_SCHEDULE_FRAMES, slices, qh->device_पूर्णांकerval,
			qh->ls_start_schedule_slice);
पूर्ण

/**
 * dwc2_hs_pmap_schedule - Schedule in the मुख्य high speed schedule
 *
 * This will schedule something on the मुख्य dwc2 schedule.
 *
 * We'll start looking in qh->hs_transfers[index].start_schedule_us.  We'll
 * update this with the result upon success.  We also use the duration from
 * the same काष्ठाure.
 *
 * @hsotg:           The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:              QH क्रम the periodic transfer.
 * @only_one_period: If true we will limit ourselves to just looking at
 *                   one period (aka one 100us chunk).  This is used अगर we have
 *                   alपढ़ोy scheduled something on the low speed schedule and
 *                   need to find something that matches on the high speed one.
 * @index:           The index पूर्णांकo qh->hs_transfers that we're working with.
 *
 * Returns: 0 क्रम success or an error code.  Upon success the
 *          dwc2_hs_transfer_समय specअगरied by "index" will be updated.
 */
अटल पूर्णांक dwc2_hs_pmap_schedule(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
				 bool only_one_period, पूर्णांक index)
अणु
	काष्ठा dwc2_hs_transfer_समय *trans_समय = qh->hs_transfers + index;
	पूर्णांक us;

	us = pmap_schedule(hsotg->hs_periodic_biपंचांगap,
			   DWC2_HS_PERIODIC_US_PER_UFRAME,
			   DWC2_HS_SCHEDULE_UFRAMES, trans_समय->duration_us,
			   qh->host_पूर्णांकerval, trans_समय->start_schedule_us,
			   only_one_period);

	अगर (us < 0)
		वापस us;

	trans_समय->start_schedule_us = us;
	वापस 0;
पूर्ण

/**
 * dwc2_ls_pmap_unschedule() - Unकरो work करोne by dwc2_hs_pmap_schedule()
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 * @index:       Transfer index
 */
अटल व्योम dwc2_hs_pmap_unschedule(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh, पूर्णांक index)
अणु
	काष्ठा dwc2_hs_transfer_समय *trans_समय = qh->hs_transfers + index;

	pmap_unschedule(hsotg->hs_periodic_biपंचांगap,
			DWC2_HS_PERIODIC_US_PER_UFRAME,
			DWC2_HS_SCHEDULE_UFRAMES, trans_समय->duration_us,
			qh->host_पूर्णांकerval, trans_समय->start_schedule_us);
पूर्ण

/**
 * dwc2_uframe_schedule_split - Schedule a QH क्रम a periodic split xfer.
 *
 * This is the most complicated thing in USB.  We have to find matching समय
 * in both the global high speed schedule क्रम the port and the low speed
 * schedule क्रम the TT associated with the given device.
 *
 * Being here means that the host must be running in high speed mode and the
 * device is in low or full speed mode (and behind a hub).
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल पूर्णांक dwc2_uframe_schedule_split(काष्ठा dwc2_hsotg *hsotg,
				      काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक bytecount = qh->maxp_mult * qh->maxp;
	पूर्णांक ls_search_slice;
	पूर्णांक err = 0;
	पूर्णांक host_पूर्णांकerval_in_sched;

	/*
	 * The पूर्णांकerval (how often to repeat) in the actual host schedule.
	 * See pmap_schedule() क्रम gcd() explanation.
	 */
	host_पूर्णांकerval_in_sched = gcd(qh->host_पूर्णांकerval,
				     DWC2_HS_SCHEDULE_UFRAMES);

	/*
	 * We always try to find space in the low speed schedule first, then
	 * try to find high speed समय that matches.  If we करोn't, we'll bump
	 * up the place we start searching in the low speed schedule and try
	 * again.  To start we'll look right at the beginning of the low speed
	 * schedule.
	 *
	 * Note that this will tend to front-load the high speed schedule.
	 * We may eventually want to try to aव्योम this by either considering
	 * both schedules together or करोing some sort of round robin.
	 */
	ls_search_slice = 0;

	जबतक (ls_search_slice < DWC2_LS_SCHEDULE_SLICES) अणु
		पूर्णांक start_s_uframe;
		पूर्णांक ssplit_s_uframe;
		पूर्णांक second_s_uframe;
		पूर्णांक rel_uframe;
		पूर्णांक first_count;
		पूर्णांक middle_count;
		पूर्णांक end_count;
		पूर्णांक first_data_bytes;
		पूर्णांक other_data_bytes;
		पूर्णांक i;

		अगर (qh->schedule_low_speed) अणु
			err = dwc2_ls_pmap_schedule(hsotg, qh, ls_search_slice);

			/*
			 * If we got an error here there's no other magic we
			 * can करो, so bail.  All the looping above is only
			 * helpful to reकरो things अगर we got a low speed slot
			 * and then couldn't find a matching high speed slot.
			 */
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			/* Must be missing the tt काष्ठाure?  Why? */
			WARN_ON_ONCE(1);
		पूर्ण

		/*
		 * This will give us a number 0 - 7 अगर
		 * DWC2_LS_SCHEDULE_FRAMES == 1, or 0 - 15 अगर == 2, or ...
		 */
		start_s_uframe = qh->ls_start_schedule_slice /
				 DWC2_SLICES_PER_UFRAME;

		/* Get a number that's always 0 - 7 */
		rel_uframe = (start_s_uframe % 8);

		/*
		 * If we were going to start in uframe 7 then we would need to
		 * issue a start split in uframe 6, which spec says is not OK.
		 * Move on to the next full frame (assuming there is one).
		 *
		 * See 11.18.4 Host Split Transaction Scheduling Requirements
		 * bullet 1.
		 */
		अगर (rel_uframe == 7) अणु
			अगर (qh->schedule_low_speed)
				dwc2_ls_pmap_unschedule(hsotg, qh);
			ls_search_slice =
				(qh->ls_start_schedule_slice /
				 DWC2_LS_PERIODIC_SLICES_PER_FRAME + 1) *
				DWC2_LS_PERIODIC_SLICES_PER_FRAME;
			जारी;
		पूर्ण

		/*
		 * For ISOC in:
		 * - start split            (frame -1)
		 * - complete split w/ data (frame +1)
		 * - complete split w/ data (frame +2)
		 * - ...
		 * - complete split w/ data (frame +num_data_packets)
		 * - complete split w/ data (frame +num_data_packets+1)
		 * - complete split w/ data (frame +num_data_packets+2, max 8)
		 *   ...though अगर frame was "0" then max is 7...
		 *
		 * For ISOC out we might need to करो:
		 * - start split w/ data    (frame -1)
		 * - start split w/ data    (frame +0)
		 * - ...
		 * - start split w/ data    (frame +num_data_packets-2)
		 *
		 * For INTERRUPT in we might need to करो:
		 * - start split            (frame -1)
		 * - complete split w/ data (frame +1)
		 * - complete split w/ data (frame +2)
		 * - complete split w/ data (frame +3, max 8)
		 *
		 * For INTERRUPT out we might need to करो:
		 * - start split w/ data    (frame -1)
		 * - complete split         (frame +1)
		 * - complete split         (frame +2)
		 * - complete split         (frame +3, max 8)
		 *
		 * Start adjusting!
		 */
		ssplit_s_uframe = (start_s_uframe +
				   host_पूर्णांकerval_in_sched - 1) %
				  host_पूर्णांकerval_in_sched;
		अगर (qh->ep_type == USB_ENDPOINT_XFER_ISOC && !qh->ep_is_in)
			second_s_uframe = start_s_uframe;
		अन्यथा
			second_s_uframe = start_s_uframe + 1;

		/* First data transfer might not be all 188 bytes. */
		first_data_bytes = 188 -
			DIV_ROUND_UP(188 * (qh->ls_start_schedule_slice %
					    DWC2_SLICES_PER_UFRAME),
				     DWC2_SLICES_PER_UFRAME);
		अगर (first_data_bytes > bytecount)
			first_data_bytes = bytecount;
		other_data_bytes = bytecount - first_data_bytes;

		/*
		 * For now, skip OUT xfers where first xfer is partial
		 *
		 * Main dwc2 code assumes:
		 * - INT transfers never get split in two.
		 * - ISOC transfers can always transfer 188 bytes the first
		 *   समय.
		 *
		 * Until that code is fixed, try again अगर the first transfer
		 * couldn't transfer everything.
		 *
		 * This code can be हटाओd अगर/when the rest of dwc2 handles
		 * the above हालs.  Until it's fixed we just won't be able
		 * to schedule quite as tightly.
		 */
		अगर (!qh->ep_is_in &&
		    (first_data_bytes != min_t(पूर्णांक, 188, bytecount))) अणु
			dwc2_sch_dbg(hsotg,
				     "QH=%p avoiding broken 1st xfer (%d, %d)\n",
				     qh, first_data_bytes, bytecount);
			अगर (qh->schedule_low_speed)
				dwc2_ls_pmap_unschedule(hsotg, qh);
			ls_search_slice = (start_s_uframe + 1) *
				DWC2_SLICES_PER_UFRAME;
			जारी;
		पूर्ण

		/* Start by assuming transfers क्रम the bytes */
		qh->num_hs_transfers = 1 + DIV_ROUND_UP(other_data_bytes, 188);

		/*
		 * Everything except ISOC OUT has extra transfers.  Rules are
		 * complicated.  See 11.18.4 Host Split Transaction Scheduling
		 * Requirements bullet 3.
		 */
		अगर (qh->ep_type == USB_ENDPOINT_XFER_INT) अणु
			अगर (rel_uframe == 6)
				qh->num_hs_transfers += 2;
			अन्यथा
				qh->num_hs_transfers += 3;

			अगर (qh->ep_is_in) अणु
				/*
				 * First is start split, middle/end is data.
				 * Allocate full data bytes क्रम all data.
				 */
				first_count = 4;
				middle_count = bytecount;
				end_count = bytecount;
			पूर्ण अन्यथा अणु
				/*
				 * First is data, middle/end is complete.
				 * First transfer and second can have data.
				 * Rest should just have complete split.
				 */
				first_count = first_data_bytes;
				middle_count = max_t(पूर्णांक, 4, other_data_bytes);
				end_count = 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (qh->ep_is_in) अणु
				पूर्णांक last;

				/* Account क्रम the start split */
				qh->num_hs_transfers++;

				/* Calculate "L" value from spec */
				last = rel_uframe + qh->num_hs_transfers + 1;

				/* Start with basic हाल */
				अगर (last <= 6)
					qh->num_hs_transfers += 2;
				अन्यथा
					qh->num_hs_transfers += 1;

				/* Adjust करोwnwards */
				अगर (last >= 6 && rel_uframe == 0)
					qh->num_hs_transfers--;

				/* 1st = start; rest can contain data */
				first_count = 4;
				middle_count = min_t(पूर्णांक, 188, bytecount);
				end_count = middle_count;
			पूर्ण अन्यथा अणु
				/* All contain data, last might be smaller */
				first_count = first_data_bytes;
				middle_count = min_t(पूर्णांक, 188,
						     other_data_bytes);
				end_count = other_data_bytes % 188;
			पूर्ण
		पूर्ण

		/* Assign durations per uFrame */
		qh->hs_transfers[0].duration_us = HS_USECS_ISO(first_count);
		क्रम (i = 1; i < qh->num_hs_transfers - 1; i++)
			qh->hs_transfers[i].duration_us =
				HS_USECS_ISO(middle_count);
		अगर (qh->num_hs_transfers > 1)
			qh->hs_transfers[qh->num_hs_transfers - 1].duration_us =
				HS_USECS_ISO(end_count);

		/*
		 * Assign start us.  The call below to dwc2_hs_pmap_schedule()
		 * will start with these numbers but may adjust within the same
		 * microframe.
		 */
		qh->hs_transfers[0].start_schedule_us =
			ssplit_s_uframe * DWC2_HS_PERIODIC_US_PER_UFRAME;
		क्रम (i = 1; i < qh->num_hs_transfers; i++)
			qh->hs_transfers[i].start_schedule_us =
				((second_s_uframe + i - 1) %
				 DWC2_HS_SCHEDULE_UFRAMES) *
				DWC2_HS_PERIODIC_US_PER_UFRAME;

		/* Try to schedule with filled in hs_transfers above */
		क्रम (i = 0; i < qh->num_hs_transfers; i++) अणु
			err = dwc2_hs_pmap_schedule(hsotg, qh, true, i);
			अगर (err)
				अवरोध;
		पूर्ण

		/* If we scheduled all w/out अवरोधing out then we're all good */
		अगर (i == qh->num_hs_transfers)
			अवरोध;

		क्रम (; i >= 0; i--)
			dwc2_hs_pmap_unschedule(hsotg, qh, i);

		अगर (qh->schedule_low_speed)
			dwc2_ls_pmap_unschedule(hsotg, qh);

		/* Try again starting in the next microframe */
		ls_search_slice = (start_s_uframe + 1) * DWC2_SLICES_PER_UFRAME;
	पूर्ण

	अगर (ls_search_slice >= DWC2_LS_SCHEDULE_SLICES)
		वापस -ENOSPC;

	वापस 0;
पूर्ण

/**
 * dwc2_uframe_schedule_hs - Schedule a QH क्रम a periodic high speed xfer.
 *
 * Basically this just wraps dwc2_hs_pmap_schedule() to provide a clean
 * पूर्णांकerface.
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल पूर्णांक dwc2_uframe_schedule_hs(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	/* In non-split host and device समय are the same */
	WARN_ON(qh->host_us != qh->device_us);
	WARN_ON(qh->host_पूर्णांकerval != qh->device_पूर्णांकerval);
	WARN_ON(qh->num_hs_transfers != 1);

	/* We'll have one transfer; init start to 0 beक्रमe calling scheduler */
	qh->hs_transfers[0].start_schedule_us = 0;
	qh->hs_transfers[0].duration_us = qh->host_us;

	वापस dwc2_hs_pmap_schedule(hsotg, qh, false, 0);
पूर्ण

/**
 * dwc2_uframe_schedule_ls - Schedule a QH क्रम a periodic low/full speed xfer.
 *
 * Basically this just wraps dwc2_ls_pmap_schedule() to provide a clean
 * पूर्णांकerface.
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल पूर्णांक dwc2_uframe_schedule_ls(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	/* In non-split host and device समय are the same */
	WARN_ON(qh->host_us != qh->device_us);
	WARN_ON(qh->host_पूर्णांकerval != qh->device_पूर्णांकerval);
	WARN_ON(!qh->schedule_low_speed);

	/* Run on the मुख्य low speed schedule (no split = no hub = no TT) */
	वापस dwc2_ls_pmap_schedule(hsotg, qh, 0);
पूर्ण

/**
 * dwc2_uframe_schedule - Schedule a QH क्रम a periodic xfer.
 *
 * Calls one of the 3 sub-function depending on what type of transfer this QH
 * is क्रम.  Also adds some prपूर्णांकing.
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल पूर्णांक dwc2_uframe_schedule(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक ret;

	अगर (qh->dev_speed == USB_SPEED_HIGH)
		ret = dwc2_uframe_schedule_hs(hsotg, qh);
	अन्यथा अगर (!qh->करो_split)
		ret = dwc2_uframe_schedule_ls(hsotg, qh);
	अन्यथा
		ret = dwc2_uframe_schedule_split(hsotg, qh);

	अगर (ret)
		dwc2_sch_dbg(hsotg, "QH=%p Failed to schedule %d\n", qh, ret);
	अन्यथा
		dwc2_qh_schedule_prपूर्णांक(hsotg, qh);

	वापस ret;
पूर्ण

/**
 * dwc2_uframe_unschedule - Unकरोes dwc2_uframe_schedule().
 *
 * @hsotg:       The HCD state काष्ठाure क्रम the DWC OTG controller.
 * @qh:          QH क्रम the periodic transfer.
 */
अटल व्योम dwc2_uframe_unschedule(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < qh->num_hs_transfers; i++)
		dwc2_hs_pmap_unschedule(hsotg, qh, i);

	अगर (qh->schedule_low_speed)
		dwc2_ls_pmap_unschedule(hsotg, qh);

	dwc2_sch_dbg(hsotg, "QH=%p Unscheduled\n", qh);
पूर्ण

/**
 * dwc2_pick_first_frame() - Choose 1st frame क्रम qh that's alपढ़ोy scheduled
 *
 * Takes a qh that has alपढ़ोy been scheduled (which means we know we have the
 * bandwdith reserved क्रम us) and set the next_active_frame and the
 * start_active_frame.
 *
 * This is expected to be called on qh's that weren't previously actively
 * running.  It just picks the next frame that we can fit पूर्णांकo without any
 * thought about the past.
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH क्रम a periodic endpoपूर्णांक
 *
 */
अटल व्योम dwc2_pick_first_frame(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	u16 frame_number;
	u16 earliest_frame;
	u16 next_active_frame;
	u16 relative_frame;
	u16 पूर्णांकerval;

	/*
	 * Use the real frame number rather than the cached value as of the
	 * last SOF to give us a little extra slop.
	 */
	frame_number = dwc2_hcd_get_frame_number(hsotg);

	/*
	 * We wouldn't want to start any earlier than the next frame just in
	 * हाल the frame number ticks as we're करोing this calculation.
	 *
	 * NOTE: अगर we could quantअगरy how दीर्घ till we actually get scheduled
	 * we might be able to aव्योम the "+ 1" by looking at the upper part of
	 * HFNUM (the FRREM field).  For now we'll just use the + 1 though.
	 */
	earliest_frame = dwc2_frame_num_inc(frame_number, 1);
	next_active_frame = earliest_frame;

	/* Get the "no microframe schduler" out of the way... */
	अगर (!hsotg->params.uframe_sched) अणु
		अगर (qh->करो_split)
			/* Splits are active at microframe 0 minus 1 */
			next_active_frame |= 0x7;
		जाओ निकास;
	पूर्ण

	अगर (qh->dev_speed == USB_SPEED_HIGH || qh->करो_split) अणु
		/*
		 * We're either at high speed or we're करोing a split (which
		 * means we're talking high speed to a hub).  In any हाल
		 * the first frame should be based on when the first scheduled
		 * event is.
		 */
		WARN_ON(qh->num_hs_transfers < 1);

		relative_frame = qh->hs_transfers[0].start_schedule_us /
				 DWC2_HS_PERIODIC_US_PER_UFRAME;

		/* Adjust पूर्णांकerval as per high speed schedule */
		पूर्णांकerval = gcd(qh->host_पूर्णांकerval, DWC2_HS_SCHEDULE_UFRAMES);

	पूर्ण अन्यथा अणु
		/*
		 * Low or full speed directly on dwc2.  Just about the same
		 * as high speed but on a dअगरferent schedule and with slightly
		 * dअगरferent adjusपंचांगents.  Note that this works because when
		 * the host and device are both low speed then frames in the
		 * controller tick at low speed.
		 */
		relative_frame = qh->ls_start_schedule_slice /
				 DWC2_LS_PERIODIC_SLICES_PER_FRAME;
		पूर्णांकerval = gcd(qh->host_पूर्णांकerval, DWC2_LS_SCHEDULE_FRAMES);
	पूर्ण

	/* Scheduler messed up अगर frame is past पूर्णांकerval */
	WARN_ON(relative_frame >= पूर्णांकerval);

	/*
	 * We know पूर्णांकerval must भागide (HFNUM_MAX_FRNUM + 1) now that we've
	 * करोne the gcd(), so it's safe to move to the beginning of the current
	 * पूर्णांकerval like this.
	 *
	 * After this we might be beक्रमe earliest_frame, but करोn't worry,
	 * we'll fix it...
	 */
	next_active_frame = (next_active_frame / पूर्णांकerval) * पूर्णांकerval;

	/*
	 * Actually choose to start at the frame number we've been
	 * scheduled क्रम.
	 */
	next_active_frame = dwc2_frame_num_inc(next_active_frame,
					       relative_frame);

	/*
	 * We actually need 1 frame beक्रमe since the next_active_frame is
	 * the frame number we'll be put on the ready list and we won't be on
	 * the bus until 1 frame later.
	 */
	next_active_frame = dwc2_frame_num_dec(next_active_frame, 1);

	/*
	 * By now we might actually be beक्रमe the earliest_frame.  Let's move
	 * up पूर्णांकervals until we're not.
	 */
	जबतक (dwc2_frame_num_gt(earliest_frame, next_active_frame))
		next_active_frame = dwc2_frame_num_inc(next_active_frame,
						       पूर्णांकerval);

निकास:
	qh->next_active_frame = next_active_frame;
	qh->start_active_frame = next_active_frame;

	dwc2_sch_vdbg(hsotg, "QH=%p First fn=%04x nxt=%04x\n",
		      qh, frame_number, qh->next_active_frame);
पूर्ण

/**
 * dwc2_करो_reserve() - Make a periodic reservation
 *
 * Try to allocate space in the periodic schedule.  Depending on parameters
 * this might use the microframe scheduler or the dumb scheduler.
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH क्रम the periodic transfer.
 *
 * Returns: 0 upon success; error upon failure.
 */
अटल पूर्णांक dwc2_करो_reserve(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक status;

	अगर (hsotg->params.uframe_sched) अणु
		status = dwc2_uframe_schedule(hsotg, qh);
	पूर्ण अन्यथा अणु
		status = dwc2_periodic_channel_available(hsotg);
		अगर (status) अणु
			dev_info(hsotg->dev,
				 "%s: No host channel available for periodic transfer\n",
				 __func__);
			वापस status;
		पूर्ण

		status = dwc2_check_periodic_bandwidth(hsotg, qh);
	पूर्ण

	अगर (status) अणु
		dev_dbg(hsotg->dev,
			"%s: Insufficient periodic bandwidth for periodic transfer\n",
			__func__);
		वापस status;
	पूर्ण

	अगर (!hsotg->params.uframe_sched)
		/* Reserve periodic channel */
		hsotg->periodic_channels++;

	/* Update claimed usecs per (micro)frame */
	hsotg->periodic_usecs += qh->host_us;

	dwc2_pick_first_frame(hsotg, qh);

	वापस 0;
पूर्ण

/**
 * dwc2_करो_unreserve() - Actually release the periodic reservation
 *
 * This function actually releases the periodic bandwidth that was reserved
 * by the given qh.
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH क्रम the periodic transfer.
 */
अटल व्योम dwc2_करो_unreserve(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	निश्चित_spin_locked(&hsotg->lock);

	WARN_ON(!qh->unreserve_pending);

	/* No more unreserve pending--we're करोing it */
	qh->unreserve_pending = false;

	अगर (WARN_ON(!list_empty(&qh->qh_list_entry)))
		list_del_init(&qh->qh_list_entry);

	/* Update claimed usecs per (micro)frame */
	hsotg->periodic_usecs -= qh->host_us;

	अगर (hsotg->params.uframe_sched) अणु
		dwc2_uframe_unschedule(hsotg, qh);
	पूर्ण अन्यथा अणु
		/* Release periodic channel reservation */
		hsotg->periodic_channels--;
	पूर्ण
पूर्ण

/**
 * dwc2_unreserve_समयr_fn() - Timer function to release periodic reservation
 *
 * According to the kernel करोc क्रम usb_submit_urb() (specअगरically the part about
 * "Reserved Bandwidth Transfers"), we need to keep a reservation active as
 * दीर्घ as a device driver keeps submitting.  Since we're using HCD_BH to give
 * back the URB we need to give the driver a little bit of समय beक्रमe we
 * release the reservation.  This worker is called after the appropriate
 * delay.
 *
 * @t: Address to a qh unreserve_work.
 */
अटल व्योम dwc2_unreserve_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा dwc2_qh *qh = from_समयr(qh, t, unreserve_समयr);
	काष्ठा dwc2_hsotg *hsotg = qh->hsotg;
	अचिन्हित दीर्घ flags;

	/*
	 * Wait क्रम the lock, or क्रम us to be scheduled again.  We
	 * could be scheduled again अगर:
	 * - We started executing but didn't get the lock yet.
	 * - A new reservation came in, but cancel didn't take effect
	 *   because we alपढ़ोy started executing.
	 * - The समयr has been kicked again.
	 * In that हाल cancel and रुको क्रम the next call.
	 */
	जबतक (!spin_trylock_irqsave(&hsotg->lock, flags)) अणु
		अगर (समयr_pending(&qh->unreserve_समयr))
			वापस;
	पूर्ण

	/*
	 * Might be no more unreserve pending अगर:
	 * - We started executing but didn't get the lock yet.
	 * - A new reservation came in, but cancel didn't take effect
	 *   because we alपढ़ोy started executing.
	 *
	 * We can't put this in the loop above because unreserve_pending needs
	 * to be accessed under lock, so we can only check it once we got the
	 * lock.
	 */
	अगर (qh->unreserve_pending)
		dwc2_करो_unreserve(hsotg, qh);

	spin_unlock_irqrestore(&hsotg->lock, flags);
पूर्ण

/**
 * dwc2_check_max_xfer_size() - Checks that the max transfer size allowed in a
 * host channel is large enough to handle the maximum data transfer in a single
 * (micro)frame क्रम a periodic transfer
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH क्रम a periodic endpoपूर्णांक
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
अटल पूर्णांक dwc2_check_max_xfer_size(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh)
अणु
	u32 max_xfer_size;
	u32 max_channel_xfer_size;
	पूर्णांक status = 0;

	max_xfer_size = qh->maxp * qh->maxp_mult;
	max_channel_xfer_size = hsotg->params.max_transfer_size;

	अगर (max_xfer_size > max_channel_xfer_size) अणु
		dev_err(hsotg->dev,
			"%s: Periodic xfer length %d > max xfer length for channel %d\n",
			__func__, max_xfer_size, max_channel_xfer_size);
		status = -ENOSPC;
	पूर्ण

	वापस status;
पूर्ण

/**
 * dwc2_schedule_periodic() - Schedules an पूर्णांकerrupt or isochronous transfer in
 * the periodic schedule
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    QH क्रम the periodic transfer. The QH should alपढ़ोy contain the
 *         scheduling inक्रमmation.
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
अटल पूर्णांक dwc2_schedule_periodic(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक status;

	status = dwc2_check_max_xfer_size(hsotg, qh);
	अगर (status) अणु
		dev_dbg(hsotg->dev,
			"%s: Channel max transfer size too small for periodic transfer\n",
			__func__);
		वापस status;
	पूर्ण

	/* Cancel pending unreserve; अगर canceled OK, unreserve was pending */
	अगर (del_समयr(&qh->unreserve_समयr))
		WARN_ON(!qh->unreserve_pending);

	/*
	 * Only need to reserve अगर there's not an unreserve pending, since अगर an
	 * unreserve is pending then by definition our old reservation is still
	 * valid.  Unreserve might still be pending even अगर we didn't cancel अगर
	 * dwc2_unreserve_समयr_fn() alपढ़ोy started.  Code in the समयr handles
	 * that हाल.
	 */
	अगर (!qh->unreserve_pending) अणु
		status = dwc2_करो_reserve(hsotg, qh);
		अगर (status)
			वापस status;
	पूर्ण अन्यथा अणु
		/*
		 * It might have been a जबतक, so make sure that frame_number
		 * is still good.  Note: we could also try to use the similar
		 * dwc2_next_periodic_start() but that schedules much more
		 * tightly and we might need to hurry and queue things up.
		 */
		अगर (dwc2_frame_num_le(qh->next_active_frame,
				      hsotg->frame_number))
			dwc2_pick_first_frame(hsotg, qh);
	पूर्ण

	qh->unreserve_pending = 0;

	अगर (hsotg->params.dma_desc_enable)
		/* Don't rely on SOF and start in पढ़ोy schedule */
		list_add_tail(&qh->qh_list_entry, &hsotg->periodic_sched_पढ़ोy);
	अन्यथा
		/* Always start in inactive schedule */
		list_add_tail(&qh->qh_list_entry,
			      &hsotg->periodic_sched_inactive);

	वापस 0;
पूर्ण

/**
 * dwc2_deschedule_periodic() - Removes an पूर्णांकerrupt or isochronous transfer
 * from the periodic schedule
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:	   QH क्रम the periodic transfer
 */
अटल व्योम dwc2_deschedule_periodic(काष्ठा dwc2_hsotg *hsotg,
				     काष्ठा dwc2_qh *qh)
अणु
	bool did_modअगरy;

	निश्चित_spin_locked(&hsotg->lock);

	/*
	 * Schedule the unreserve to happen in a little bit.  Cases here:
	 * - Unreserve worker might be sitting there रुकोing to grab the lock.
	 *   In this हाल it will notice it's been schedule again and will
	 *   quit.
	 * - Unreserve worker might not be scheduled.
	 *
	 * We should never alपढ़ोy be scheduled since dwc2_schedule_periodic()
	 * should have canceled the scheduled unreserve समयr (hence the
	 * warning on did_modअगरy).
	 *
	 * We add + 1 to the समयr to guarantee that at least 1 jअगरfy has
	 * passed (otherwise अगर the jअगरfy counter might tick right after we
	 * पढ़ो it and we'll get no delay).
	 */
	did_modअगरy = mod_समयr(&qh->unreserve_समयr,
			       jअगरfies + DWC2_UNRESERVE_DELAY + 1);
	WARN_ON(did_modअगरy);
	qh->unreserve_pending = 1;

	list_del_init(&qh->qh_list_entry);
पूर्ण

/**
 * dwc2_रुको_समयr_fn() - Timer function to re-queue after रुकोing
 *
 * As per the spec, a NAK indicates that "a function is temporarily unable to
 * transmit or receive data, but will eventually be able to करो so without need
 * of host पूर्णांकervention".
 *
 * That means that when we encounter a NAK we're supposed to retry.
 *
 * ...but अगर we retry right away (from the पूर्णांकerrupt handler that saw the NAK)
 * then we can end up with an पूर्णांकerrupt storm (अगर the other side keeps NAKing
 * us) because on slow enough CPUs it could take us दीर्घer to get out of the
 * पूर्णांकerrupt routine than it takes क्रम the device to send another NAK.  That
 * leads to a स्थिरant stream of NAK पूर्णांकerrupts and the CPU locks.
 *
 * ...so instead of retrying right away in the हाल of a NAK we'll set a समयr
 * to retry some समय later.  This function handles that समयr and moves the
 * qh back to the "inactive" list, then queues transactions.
 *
 * @t: Poपूर्णांकer to रुको_समयr in a qh.
 *
 * Return: HRTIMER_NORESTART to not स्वतःmatically restart this समयr.
 */
अटल क्रमागत hrसमयr_restart dwc2_रुको_समयr_fn(काष्ठा hrसमयr *t)
अणु
	काष्ठा dwc2_qh *qh = container_of(t, काष्ठा dwc2_qh, रुको_समयr);
	काष्ठा dwc2_hsotg *hsotg = qh->hsotg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsotg->lock, flags);

	/*
	 * We'll set रुको_समयr_cancel to true अगर we want to cancel this
	 * operation in dwc2_hcd_qh_unlink().
	 */
	अगर (!qh->रुको_समयr_cancel) अणु
		क्रमागत dwc2_transaction_type tr_type;

		qh->want_रुको = false;

		list_move(&qh->qh_list_entry,
			  &hsotg->non_periodic_sched_inactive);

		tr_type = dwc2_hcd_select_transactions(hsotg);
		अगर (tr_type != DWC2_TRANSACTION_NONE)
			dwc2_hcd_queue_transactions(hsotg, tr_type);
	पूर्ण

	spin_unlock_irqrestore(&hsotg->lock, flags);
	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * dwc2_qh_init() - Initializes a QH काष्ठाure
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    The QH to init
 * @urb:   Holds the inक्रमmation about the device/endpoपूर्णांक needed to initialize
 *         the QH
 * @mem_flags: Flags क्रम allocating memory.
 */
अटल व्योम dwc2_qh_init(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			 काष्ठा dwc2_hcd_urb *urb, gfp_t mem_flags)
अणु
	पूर्णांक dev_speed = dwc2_host_get_speed(hsotg, urb->priv);
	u8 ep_type = dwc2_hcd_get_pipe_type(&urb->pipe_info);
	bool ep_is_in = !!dwc2_hcd_is_pipe_in(&urb->pipe_info);
	bool ep_is_isoc = (ep_type == USB_ENDPOINT_XFER_ISOC);
	bool ep_is_पूर्णांक = (ep_type == USB_ENDPOINT_XFER_INT);
	u32 hprt = dwc2_पढ़ोl(hsotg, HPRT0);
	u32 prtspd = (hprt & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;
	bool करो_split = (prtspd == HPRT0_SPD_HIGH_SPEED &&
			 dev_speed != USB_SPEED_HIGH);
	पूर्णांक maxp = dwc2_hcd_get_maxp(&urb->pipe_info);
	पूर्णांक maxp_mult = dwc2_hcd_get_maxp_mult(&urb->pipe_info);
	पूर्णांक bytecount = maxp_mult * maxp;
	अक्षर *speed, *type;

	/* Initialize QH */
	qh->hsotg = hsotg;
	समयr_setup(&qh->unreserve_समयr, dwc2_unreserve_समयr_fn, 0);
	hrसमयr_init(&qh->रुको_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	qh->रुको_समयr.function = &dwc2_रुको_समयr_fn;
	qh->ep_type = ep_type;
	qh->ep_is_in = ep_is_in;

	qh->data_toggle = DWC2_HC_PID_DATA0;
	qh->maxp = maxp;
	qh->maxp_mult = maxp_mult;
	INIT_LIST_HEAD(&qh->qtd_list);
	INIT_LIST_HEAD(&qh->qh_list_entry);

	qh->करो_split = करो_split;
	qh->dev_speed = dev_speed;

	अगर (ep_is_पूर्णांक || ep_is_isoc) अणु
		/* Compute scheduling parameters once and save them */
		पूर्णांक host_speed = करो_split ? USB_SPEED_HIGH : dev_speed;
		काष्ठा dwc2_tt *dwc_tt = dwc2_host_get_tt_info(hsotg, urb->priv,
							       mem_flags,
							       &qh->ttport);
		पूर्णांक device_ns;

		qh->dwc_tt = dwc_tt;

		qh->host_us = NS_TO_US(usb_calc_bus_समय(host_speed, ep_is_in,
				       ep_is_isoc, bytecount));
		device_ns = usb_calc_bus_समय(dev_speed, ep_is_in,
					      ep_is_isoc, bytecount);

		अगर (करो_split && dwc_tt)
			device_ns += dwc_tt->usb_tt->think_समय;
		qh->device_us = NS_TO_US(device_ns);

		qh->device_पूर्णांकerval = urb->पूर्णांकerval;
		qh->host_पूर्णांकerval = urb->पूर्णांकerval * (करो_split ? 8 : 1);

		/*
		 * Schedule low speed अगर we're running the host in low or
		 * full speed OR अगर we've got a "TT" to deal with to access this
		 * device.
		 */
		qh->schedule_low_speed = prtspd != HPRT0_SPD_HIGH_SPEED ||
					 dwc_tt;

		अगर (करो_split) अणु
			/* We won't know num transfers until we schedule */
			qh->num_hs_transfers = -1;
		पूर्ण अन्यथा अगर (dev_speed == USB_SPEED_HIGH) अणु
			qh->num_hs_transfers = 1;
		पूर्ण अन्यथा अणु
			qh->num_hs_transfers = 0;
		पूर्ण

		/* We'll schedule later when we have something to करो */
	पूर्ण

	चयन (dev_speed) अणु
	हाल USB_SPEED_LOW:
		speed = "low";
		अवरोध;
	हाल USB_SPEED_FULL:
		speed = "full";
		अवरोध;
	हाल USB_SPEED_HIGH:
		speed = "high";
		अवरोध;
	शेष:
		speed = "?";
		अवरोध;
	पूर्ण

	चयन (qh->ep_type) अणु
	हाल USB_ENDPOINT_XFER_ISOC:
		type = "isochronous";
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		type = "interrupt";
		अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:
		type = "control";
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		type = "bulk";
		अवरोध;
	शेष:
		type = "?";
		अवरोध;
	पूर्ण

	dwc2_sch_dbg(hsotg, "QH=%p Init %s, %s speed, %d bytes:\n", qh, type,
		     speed, bytecount);
	dwc2_sch_dbg(hsotg, "QH=%p ...addr=%d, ep=%d, %s\n", qh,
		     dwc2_hcd_get_dev_addr(&urb->pipe_info),
		     dwc2_hcd_get_ep_num(&urb->pipe_info),
		     ep_is_in ? "IN" : "OUT");
	अगर (ep_is_पूर्णांक || ep_is_isoc) अणु
		dwc2_sch_dbg(hsotg,
			     "QH=%p ...duration: host=%d us, device=%d us\n",
			     qh, qh->host_us, qh->device_us);
		dwc2_sch_dbg(hsotg, "QH=%p ...interval: host=%d, device=%d\n",
			     qh, qh->host_पूर्णांकerval, qh->device_पूर्णांकerval);
		अगर (qh->schedule_low_speed)
			dwc2_sch_dbg(hsotg, "QH=%p ...low speed schedule=%p\n",
				     qh, dwc2_get_ls_map(hsotg, qh));
	पूर्ण
पूर्ण

/**
 * dwc2_hcd_qh_create() - Allocates and initializes a QH
 *
 * @hsotg:        The HCD state काष्ठाure क्रम the DWC OTG controller
 * @urb:          Holds the inक्रमmation about the device/endpoपूर्णांक needed
 *                to initialize the QH
 * @mem_flags:   Flags क्रम allocating memory.
 *
 * Return: Poपूर्णांकer to the newly allocated QH, or शून्य on error
 */
काष्ठा dwc2_qh *dwc2_hcd_qh_create(काष्ठा dwc2_hsotg *hsotg,
				   काष्ठा dwc2_hcd_urb *urb,
					  gfp_t mem_flags)
अणु
	काष्ठा dwc2_qh *qh;

	अगर (!urb->priv)
		वापस शून्य;

	/* Allocate memory */
	qh = kzalloc(माप(*qh), mem_flags);
	अगर (!qh)
		वापस शून्य;

	dwc2_qh_init(hsotg, qh, urb, mem_flags);

	अगर (hsotg->params.dma_desc_enable &&
	    dwc2_hcd_qh_init_ddma(hsotg, qh, mem_flags) < 0) अणु
		dwc2_hcd_qh_मुक्त(hsotg, qh);
		वापस शून्य;
	पूर्ण

	वापस qh;
पूर्ण

/**
 * dwc2_hcd_qh_मुक्त() - Frees the QH
 *
 * @hsotg: HCD instance
 * @qh:    The QH to मुक्त
 *
 * QH should alपढ़ोy be हटाओd from the list. QTD list should alपढ़ोy be empty
 * अगर called from URB Dequeue.
 *
 * Must NOT be called with पूर्णांकerrupt disabled or spinlock held
 */
व्योम dwc2_hcd_qh_मुक्त(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	/* Make sure any unreserve work is finished. */
	अगर (del_समयr_sync(&qh->unreserve_समयr)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_करो_unreserve(hsotg, qh);
		spin_unlock_irqrestore(&hsotg->lock, flags);
	पूर्ण

	/*
	 * We करोn't have the lock so we can safely रुको until the रुको समयr
	 * finishes.  Of course, at this poपूर्णांक in समय we'd better have set
	 * रुको_समयr_active to false so अगर this समयr was still pending it
	 * won't करो anything anyway, but we want it to finish beक्रमe we मुक्त
	 * memory.
	 */
	hrसमयr_cancel(&qh->रुको_समयr);

	dwc2_host_put_tt_info(hsotg, qh->dwc_tt);

	अगर (qh->desc_list)
		dwc2_hcd_qh_मुक्त_ddma(hsotg, qh);
	अन्यथा अगर (hsotg->unaligned_cache && qh->dw_align_buf)
		kmem_cache_मुक्त(hsotg->unaligned_cache, qh->dw_align_buf);

	kमुक्त(qh);
पूर्ण

/**
 * dwc2_hcd_qh_add() - Adds a QH to either the non periodic or periodic
 * schedule अगर it is not alपढ़ोy in the schedule. If the QH is alपढ़ोy in
 * the schedule, no action is taken.
 *
 * @hsotg: The HCD state काष्ठाure क्रम the DWC OTG controller
 * @qh:    The QH to add
 *
 * Return: 0 अगर successful, negative error code otherwise
 */
पूर्णांक dwc2_hcd_qh_add(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक status;
	u32 पूर्णांकr_mask;
	kसमय_प्रकार delay;

	अगर (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	अगर (!list_empty(&qh->qh_list_entry))
		/* QH alपढ़ोy in a schedule */
		वापस 0;

	/* Add the new QH to the appropriate schedule */
	अगर (dwc2_qh_is_non_per(qh)) अणु
		/* Schedule right away */
		qh->start_active_frame = hsotg->frame_number;
		qh->next_active_frame = qh->start_active_frame;

		अगर (qh->want_रुको) अणु
			list_add_tail(&qh->qh_list_entry,
				      &hsotg->non_periodic_sched_रुकोing);
			qh->रुको_समयr_cancel = false;
			delay = kसमय_set(0, DWC2_RETRY_WAIT_DELAY);
			hrसमयr_start(&qh->रुको_समयr, delay, HRTIMER_MODE_REL);
		पूर्ण अन्यथा अणु
			list_add_tail(&qh->qh_list_entry,
				      &hsotg->non_periodic_sched_inactive);
		पूर्ण
		वापस 0;
	पूर्ण

	status = dwc2_schedule_periodic(hsotg, qh);
	अगर (status)
		वापस status;
	अगर (!hsotg->periodic_qh_count) अणु
		पूर्णांकr_mask = dwc2_पढ़ोl(hsotg, GINTMSK);
		पूर्णांकr_mask |= GINTSTS_SOF;
		dwc2_ग_लिखोl(hsotg, पूर्णांकr_mask, GINTMSK);
	पूर्ण
	hsotg->periodic_qh_count++;

	वापस 0;
पूर्ण

/**
 * dwc2_hcd_qh_unlink() - Removes a QH from either the non-periodic or periodic
 * schedule. Memory is not मुक्तd.
 *
 * @hsotg: The HCD state काष्ठाure
 * @qh:    QH to हटाओ from schedule
 */
व्योम dwc2_hcd_qh_unlink(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh)
अणु
	u32 पूर्णांकr_mask;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	/* If the रुको_समयr is pending, this will stop it from acting */
	qh->रुको_समयr_cancel = true;

	अगर (list_empty(&qh->qh_list_entry))
		/* QH is not in a schedule */
		वापस;

	अगर (dwc2_qh_is_non_per(qh)) अणु
		अगर (hsotg->non_periodic_qh_ptr == &qh->qh_list_entry)
			hsotg->non_periodic_qh_ptr =
					hsotg->non_periodic_qh_ptr->next;
		list_del_init(&qh->qh_list_entry);
		वापस;
	पूर्ण

	dwc2_deschedule_periodic(hsotg, qh);
	hsotg->periodic_qh_count--;
	अगर (!hsotg->periodic_qh_count &&
	    !hsotg->params.dma_desc_enable) अणु
		पूर्णांकr_mask = dwc2_पढ़ोl(hsotg, GINTMSK);
		पूर्णांकr_mask &= ~GINTSTS_SOF;
		dwc2_ग_लिखोl(hsotg, पूर्णांकr_mask, GINTMSK);
	पूर्ण
पूर्ण

/**
 * dwc2_next_क्रम_periodic_split() - Set next_active_frame midway thru a split.
 *
 * This is called क्रम setting next_active_frame क्रम periodic splits क्रम all but
 * the first packet of the split.  Confusing?  I thought so...
 *
 * Periodic splits are single low/full speed transfers that we end up splitting
 * up पूर्णांकo several high speed transfers.  They always fit पूर्णांकo one full (1 ms)
 * frame but might be split over several microframes (125 us each).  We to put
 * each of the parts on a very specअगरic high speed frame.
 *
 * This function figures out where the next active uFrame needs to be.
 *
 * @hsotg:        The HCD state काष्ठाure
 * @qh:           QH क्रम the periodic transfer.
 * @frame_number: The current frame number.
 *
 * Return: number missed by (or 0 अगर we didn't miss).
 */
अटल पूर्णांक dwc2_next_क्रम_periodic_split(काष्ठा dwc2_hsotg *hsotg,
					काष्ठा dwc2_qh *qh, u16 frame_number)
अणु
	u16 old_frame = qh->next_active_frame;
	u16 prev_frame_number = dwc2_frame_num_dec(frame_number, 1);
	पूर्णांक missed = 0;
	u16 incr;

	/*
	 * See dwc2_uframe_schedule_split() क्रम split scheduling.
	 *
	 * Basically: increment 1 normally, but 2 right after the start split
	 * (except क्रम ISOC out).
	 */
	अगर (old_frame == qh->start_active_frame &&
	    !(qh->ep_type == USB_ENDPOINT_XFER_ISOC && !qh->ep_is_in))
		incr = 2;
	अन्यथा
		incr = 1;

	qh->next_active_frame = dwc2_frame_num_inc(old_frame, incr);

	/*
	 * Note that it's OK क्रम frame_number to be 1 frame past
	 * next_active_frame.  Remember that next_active_frame is supposed to
	 * be 1 frame _beक्रमe_ when we want to be scheduled.  If we're 1 frame
	 * past it just means schedule ASAP.
	 *
	 * It's _not_ OK, however, if we're more than one frame past.
	 */
	अगर (dwc2_frame_num_gt(prev_frame_number, qh->next_active_frame)) अणु
		/*
		 * OOPS, we missed.  That's actually pretty bad since
		 * the hub will be unhappy; try ASAP I guess.
		 */
		missed = dwc2_frame_num_dec(prev_frame_number,
					    qh->next_active_frame);
		qh->next_active_frame = frame_number;
	पूर्ण

	वापस missed;
पूर्ण

/**
 * dwc2_next_periodic_start() - Set next_active_frame क्रम next transfer start
 *
 * This is called क्रम setting next_active_frame क्रम a periodic transfer क्रम
 * all हालs other than midway through a periodic split.  This will also update
 * start_active_frame.
 *
 * Since we _always_ keep start_active_frame as the start of the previous
 * transfer this is normally pretty easy: we just add our पूर्णांकerval to
 * start_active_frame and we've got our answer.
 *
 * The tricks come पूर्णांकo play अगर we miss.  In that हाल we'll look क्रम the next
 * slot we can fit पूर्णांकo.
 *
 * @hsotg:        The HCD state काष्ठाure
 * @qh:           QH क्रम the periodic transfer.
 * @frame_number: The current frame number.
 *
 * Return: number missed by (or 0 अगर we didn't miss).
 */
अटल पूर्णांक dwc2_next_periodic_start(काष्ठा dwc2_hsotg *hsotg,
				    काष्ठा dwc2_qh *qh, u16 frame_number)
अणु
	पूर्णांक missed = 0;
	u16 पूर्णांकerval = qh->host_पूर्णांकerval;
	u16 prev_frame_number = dwc2_frame_num_dec(frame_number, 1);

	qh->start_active_frame = dwc2_frame_num_inc(qh->start_active_frame,
						    पूर्णांकerval);

	/*
	 * The dwc2_frame_num_gt() function used below won't work terribly well
	 * with अगर we just incremented by a really large पूर्णांकervals since the
	 * frame counter only goes to 0x3fff.  It's terribly unlikely that we
	 * will have missed in this हाल anyway.  Just go to निकास.  If we want
	 * to try to करो better we'll need to keep track of a bigger counter
	 * somewhere in the driver and handle overflows.
	 */
	अगर (पूर्णांकerval >= 0x1000)
		जाओ निकास;

	/*
	 * Test क्रम misses, which is when it's too late to schedule.
	 *
	 * A few things to note:
	 * - We compare against prev_frame_number since start_active_frame
	 *   and next_active_frame are always 1 frame beक्रमe we want things
	 *   to be active and we assume we can still get scheduled in the
	 *   current frame number.
	 * - It's possible क्रम start_active_frame (now incremented) to be
	 *   next_active_frame अगर we got an EO MISS (even_odd miss) which
	 *   basically means that we detected there wasn't enough समय क्रम
	 *   the last packet and dwc2_hc_set_even_odd_frame() rescheduled us
	 *   at the last second.  We want to make sure we करोn't schedule
	 *   another transfer क्रम the same frame.  My test webcam करोesn't seem
	 *   terribly upset by missing a transfer but really करोesn't like when
	 *   we करो two transfers in the same frame.
	 * - Some misses are expected.  Specअगरically, in order to work
	 *   perfectly dwc2 really needs quite spectacular पूर्णांकerrupt latency
	 *   requirements.  It needs to be able to handle its पूर्णांकerrupts
	 *   completely within 125 us of them being निश्चितed. That not only
	 *   means that the dwc2 पूर्णांकerrupt handler needs to be fast but it
	 *   means that nothing अन्यथा in the प्रणाली has to block dwc2 क्रम a दीर्घ
	 *   समय.  We can help with the dwc2 parts of this, but it's hard to
	 *   guarantee that a प्रणाली will have पूर्णांकerrupt latency < 125 us, so
	 *   we have to be robust to some misses.
	 */
	अगर (qh->start_active_frame == qh->next_active_frame ||
	    dwc2_frame_num_gt(prev_frame_number, qh->start_active_frame)) अणु
		u16 ideal_start = qh->start_active_frame;
		पूर्णांक periods_in_map;

		/*
		 * Adjust पूर्णांकerval as per gcd with map size.
		 * See pmap_schedule() क्रम more details here.
		 */
		अगर (qh->करो_split || qh->dev_speed == USB_SPEED_HIGH)
			periods_in_map = DWC2_HS_SCHEDULE_UFRAMES;
		अन्यथा
			periods_in_map = DWC2_LS_SCHEDULE_FRAMES;
		पूर्णांकerval = gcd(पूर्णांकerval, periods_in_map);

		करो अणु
			qh->start_active_frame = dwc2_frame_num_inc(
				qh->start_active_frame, पूर्णांकerval);
		पूर्ण जबतक (dwc2_frame_num_gt(prev_frame_number,
					   qh->start_active_frame));

		missed = dwc2_frame_num_dec(qh->start_active_frame,
					    ideal_start);
	पूर्ण

निकास:
	qh->next_active_frame = qh->start_active_frame;

	वापस missed;
पूर्ण

/*
 * Deactivates a QH. For non-periodic QHs, हटाओs the QH from the active
 * non-periodic schedule. The QH is added to the inactive non-periodic
 * schedule अगर any QTDs are still attached to the QH.
 *
 * For periodic QHs, the QH is हटाओd from the periodic queued schedule. If
 * there are any QTDs still attached to the QH, the QH is added to either the
 * periodic inactive schedule or the periodic पढ़ोy schedule and its next
 * scheduled frame is calculated. The QH is placed in the पढ़ोy schedule अगर
 * the scheduled frame has been reached alपढ़ोy. Otherwise it's placed in the
 * inactive schedule. If there are no QTDs attached to the QH, the QH is
 * completely हटाओd from the periodic schedule.
 */
व्योम dwc2_hcd_qh_deactivate(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qh *qh,
			    पूर्णांक sched_next_periodic_split)
अणु
	u16 old_frame = qh->next_active_frame;
	u16 frame_number;
	पूर्णांक missed;

	अगर (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	अगर (dwc2_qh_is_non_per(qh)) अणु
		dwc2_hcd_qh_unlink(hsotg, qh);
		अगर (!list_empty(&qh->qtd_list))
			/* Add back to inactive/रुकोing non-periodic schedule */
			dwc2_hcd_qh_add(hsotg, qh);
		वापस;
	पूर्ण

	/*
	 * Use the real frame number rather than the cached value as of the
	 * last SOF just to get us a little बंदr to reality.  Note that
	 * means we करोn't actually know if we've alपढ़ोy handled the SOF
	 * पूर्णांकerrupt क्रम this frame.
	 */
	frame_number = dwc2_hcd_get_frame_number(hsotg);

	अगर (sched_next_periodic_split)
		missed = dwc2_next_क्रम_periodic_split(hsotg, qh, frame_number);
	अन्यथा
		missed = dwc2_next_periodic_start(hsotg, qh, frame_number);

	dwc2_sch_vdbg(hsotg,
		      "QH=%p next(%d) fn=%04x, sch=%04x=>%04x (%+d) miss=%d %s\n",
		     qh, sched_next_periodic_split, frame_number, old_frame,
		     qh->next_active_frame,
		     dwc2_frame_num_dec(qh->next_active_frame, old_frame),
		missed, missed ? "MISS" : "");

	अगर (list_empty(&qh->qtd_list)) अणु
		dwc2_hcd_qh_unlink(hsotg, qh);
		वापस;
	पूर्ण

	/*
	 * Remove from periodic_sched_queued and move to
	 * appropriate queue
	 *
	 * Note: we purposely use the frame_number from the "hsotg" काष्ठाure
	 * since we know SOF पूर्णांकerrupt will handle future frames.
	 */
	अगर (dwc2_frame_num_le(qh->next_active_frame, hsotg->frame_number))
		list_move_tail(&qh->qh_list_entry,
			       &hsotg->periodic_sched_पढ़ोy);
	अन्यथा
		list_move_tail(&qh->qh_list_entry,
			       &hsotg->periodic_sched_inactive);
पूर्ण

/**
 * dwc2_hcd_qtd_init() - Initializes a QTD काष्ठाure
 *
 * @qtd: The QTD to initialize
 * @urb: The associated URB
 */
व्योम dwc2_hcd_qtd_init(काष्ठा dwc2_qtd *qtd, काष्ठा dwc2_hcd_urb *urb)
अणु
	qtd->urb = urb;
	अगर (dwc2_hcd_get_pipe_type(&urb->pipe_info) ==
			USB_ENDPOINT_XFER_CONTROL) अणु
		/*
		 * The only समय the QTD data toggle is used is on the data
		 * phase of control transfers. This phase always starts with
		 * DATA1.
		 */
		qtd->data_toggle = DWC2_HC_PID_DATA1;
		qtd->control_phase = DWC2_CONTROL_SETUP;
	पूर्ण

	/* Start split */
	qtd->complete_split = 0;
	qtd->isoc_split_pos = DWC2_HCSPLT_XACTPOS_ALL;
	qtd->isoc_split_offset = 0;
	qtd->in_process = 0;

	/* Store the qtd ptr in the urb to reference the QTD */
	urb->qtd = qtd;
पूर्ण

/**
 * dwc2_hcd_qtd_add() - Adds a QTD to the QTD-list of a QH
 *			Caller must hold driver lock.
 *
 * @hsotg:        The DWC HCD काष्ठाure
 * @qtd:          The QTD to add
 * @qh:           Queue head to add qtd to
 *
 * Return: 0 अगर successful, negative error code otherwise
 *
 * If the QH to which the QTD is added is not currently scheduled, it is placed
 * पूर्णांकo the proper schedule based on its EP type.
 */
पूर्णांक dwc2_hcd_qtd_add(काष्ठा dwc2_hsotg *hsotg, काष्ठा dwc2_qtd *qtd,
		     काष्ठा dwc2_qh *qh)
अणु
	पूर्णांक retval;

	अगर (unlikely(!qh)) अणु
		dev_err(hsotg->dev, "%s: Invalid QH\n", __func__);
		retval = -EINVAL;
		जाओ fail;
	पूर्ण

	retval = dwc2_hcd_qh_add(hsotg, qh);
	अगर (retval)
		जाओ fail;

	qtd->qh = qh;
	list_add_tail(&qtd->qtd_list_entry, &qh->qtd_list);

	वापस 0;
fail:
	वापस retval;
पूर्ण
