<शैली गुरु>
/* valid adjसमयx test
 *              by: John Stultz <john.stultz@linaro.org>
 *              (C) Copyright Linaro 2015
 *              Licensed under the GPLv2
 *
 *  This test validates adjसमयx पूर्णांकerface with valid
 *  and invalid test data.
 *
 *  Usage: valid-adjसमयx
 *
 *  To build:
 *	$ gcc valid-adjसमयx.c -o valid-adjसमयx -lrt
 *
 *   This program is मुक्त software: you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 */



#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000LL
#घोषणा USEC_PER_SEC 1000000LL

#घोषणा ADJ_SETOFFSET 0x0100

#समावेश <sys/syscall.h>
अटल पूर्णांक घड़ी_adjसमय(घड़ीid_t id, काष्ठा समयx *tx)
अणु
	वापस syscall(__NR_घड़ी_adjसमय, id, tx);
पूर्ण


/* clear NTP समय_status & समय_state */
पूर्णांक clear_समय_state(व्योम)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret;

	tx.modes = ADJ_STATUS;
	tx.status = 0;
	ret = adjसमयx(&tx);
	वापस ret;
पूर्ण

#घोषणा NUM_FREQ_VALID 32
#घोषणा NUM_FREQ_OUTOFRANGE 4
#घोषणा NUM_FREQ_INVALID 2

दीर्घ valid_freq[NUM_FREQ_VALID] = अणु
	-499<<16,
	-450<<16,
	-400<<16,
	-350<<16,
	-300<<16,
	-250<<16,
	-200<<16,
	-150<<16,
	-100<<16,
	-75<<16,
	-50<<16,
	-25<<16,
	-10<<16,
	-5<<16,
	-1<<16,
	-1000,
	1<<16,
	5<<16,
	10<<16,
	25<<16,
	50<<16,
	75<<16,
	100<<16,
	150<<16,
	200<<16,
	250<<16,
	300<<16,
	350<<16,
	400<<16,
	450<<16,
	499<<16,
पूर्ण;

दीर्घ outofrange_freq[NUM_FREQ_OUTOFRANGE] = अणु
	-1000<<16,
	-550<<16,
	550<<16,
	1000<<16,
पूर्ण;

#घोषणा दीर्घ_उच्च (~0UL>>1)
#घोषणा दीर्घ_न्यून (-दीर्घ_उच्च - 1)

दीर्घ invalid_freq[NUM_FREQ_INVALID] = अणु
	दीर्घ_उच्च,
	दीर्घ_न्यून,
पूर्ण;

पूर्णांक validate_freq(व्योम)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret, pass = 0;
	पूर्णांक i;

	clear_समय_state();

	स_रखो(&tx, 0, माप(काष्ठा समयx));
	/* Set the leap second insert flag */

	म_लिखो("Testing ADJ_FREQ... ");
	ख_साफ(मानक_निकास);
	क्रम (i = 0; i < NUM_FREQ_VALID; i++) अणु
		tx.modes = ADJ_FREQUENCY;
		tx.freq = valid_freq[i];

		ret = adjसमयx(&tx);
		अगर (ret < 0) अणु
			म_लिखो("[FAIL]\n");
			म_लिखो("Error: adjtimex(ADJ_FREQ, %ld - %ld ppm\n",
				valid_freq[i], valid_freq[i]>>16);
			pass = -1;
			जाओ out;
		पूर्ण
		tx.modes = 0;
		ret = adjसमयx(&tx);
		अगर (tx.freq != valid_freq[i]) अणु
			म_लिखो("Warning: freq value %ld not what we set it (%ld)!\n",
					tx.freq, valid_freq[i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < NUM_FREQ_OUTOFRANGE; i++) अणु
		tx.modes = ADJ_FREQUENCY;
		tx.freq = outofrange_freq[i];

		ret = adjसमयx(&tx);
		अगर (ret < 0) अणु
			म_लिखो("[FAIL]\n");
			म_लिखो("Error: adjtimex(ADJ_FREQ, %ld - %ld ppm\n",
				outofrange_freq[i], outofrange_freq[i]>>16);
			pass = -1;
			जाओ out;
		पूर्ण
		tx.modes = 0;
		ret = adjसमयx(&tx);
		अगर (tx.freq == outofrange_freq[i]) अणु
			म_लिखो("[FAIL]\n");
			म_लिखो("ERROR: out of range value %ld actually set!\n",
					tx.freq);
			pass = -1;
			जाओ out;
		पूर्ण
	पूर्ण


	अगर (माप(दीर्घ) == 8) अणु /* this हाल only applies to 64bit प्रणालीs */
		क्रम (i = 0; i < NUM_FREQ_INVALID; i++) अणु
			tx.modes = ADJ_FREQUENCY;
			tx.freq = invalid_freq[i];
			ret = adjसमयx(&tx);
			अगर (ret >= 0) अणु
				म_लिखो("[FAIL]\n");
				म_लिखो("Error: No failure on invalid ADJ_FREQUENCY %ld\n",
					invalid_freq[i]);
				pass = -1;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	म_लिखो("[OK]\n");
out:
	/* reset freq to zero */
	tx.modes = ADJ_FREQUENCY;
	tx.freq = 0;
	ret = adjसमयx(&tx);

	वापस pass;
पूर्ण


पूर्णांक set_offset(दीर्घ दीर्घ offset, पूर्णांक use_nano)
अणु
	काष्ठा समयx पंचांगx = अणुपूर्ण;
	पूर्णांक ret;

	पंचांगx.modes = ADJ_SETOFFSET;
	अगर (use_nano) अणु
		पंचांगx.modes |= ADJ_न_अंकO;

		पंचांगx.समय.tv_sec = offset / NSEC_PER_SEC;
		पंचांगx.समय.tv_usec = offset % NSEC_PER_SEC;

		अगर (offset < 0 && पंचांगx.समय.tv_usec) अणु
			पंचांगx.समय.tv_sec -= 1;
			पंचांगx.समय.tv_usec += NSEC_PER_SEC;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगx.समय.tv_sec = offset / USEC_PER_SEC;
		पंचांगx.समय.tv_usec = offset % USEC_PER_SEC;

		अगर (offset < 0 && पंचांगx.समय.tv_usec) अणु
			पंचांगx.समय.tv_sec -= 1;
			पंचांगx.समय.tv_usec += USEC_PER_SEC;
		पूर्ण
	पूर्ण

	ret = घड़ी_adjसमय(CLOCK_REALTIME, &पंचांगx);
	अगर (ret < 0) अणु
		म_लिखो("(sec: %ld  usec: %ld) ", पंचांगx.समय.tv_sec, पंचांगx.समय.tv_usec);
		म_लिखो("[FAIL]\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक set_bad_offset(दीर्घ sec, दीर्घ usec, पूर्णांक use_nano)
अणु
	काष्ठा समयx पंचांगx = अणुपूर्ण;
	पूर्णांक ret;

	पंचांगx.modes = ADJ_SETOFFSET;
	अगर (use_nano)
		पंचांगx.modes |= ADJ_न_अंकO;

	पंचांगx.समय.tv_sec = sec;
	पंचांगx.समय.tv_usec = usec;
	ret = घड़ी_adjसमय(CLOCK_REALTIME, &पंचांगx);
	अगर (ret >= 0) अणु
		म_लिखो("Invalid (sec: %ld  usec: %ld) did not fail! ", पंचांगx.समय.tv_sec, पंचांगx.समय.tv_usec);
		म_लिखो("[FAIL]\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक validate_set_offset(व्योम)
अणु
	म_लिखो("Testing ADJ_SETOFFSET... ");
	ख_साफ(मानक_निकास);

	/* Test valid values */
	अगर (set_offset(NSEC_PER_SEC - 1, 1))
		वापस -1;

	अगर (set_offset(-NSEC_PER_SEC + 1, 1))
		वापस -1;

	अगर (set_offset(-NSEC_PER_SEC - 1, 1))
		वापस -1;

	अगर (set_offset(5 * NSEC_PER_SEC, 1))
		वापस -1;

	अगर (set_offset(-5 * NSEC_PER_SEC, 1))
		वापस -1;

	अगर (set_offset(5 * NSEC_PER_SEC + NSEC_PER_SEC / 2, 1))
		वापस -1;

	अगर (set_offset(-5 * NSEC_PER_SEC - NSEC_PER_SEC / 2, 1))
		वापस -1;

	अगर (set_offset(USEC_PER_SEC - 1, 0))
		वापस -1;

	अगर (set_offset(-USEC_PER_SEC + 1, 0))
		वापस -1;

	अगर (set_offset(-USEC_PER_SEC - 1, 0))
		वापस -1;

	अगर (set_offset(5 * USEC_PER_SEC, 0))
		वापस -1;

	अगर (set_offset(-5 * USEC_PER_SEC, 0))
		वापस -1;

	अगर (set_offset(5 * USEC_PER_SEC + USEC_PER_SEC / 2, 0))
		वापस -1;

	अगर (set_offset(-5 * USEC_PER_SEC - USEC_PER_SEC / 2, 0))
		वापस -1;

	/* Test invalid values */
	अगर (set_bad_offset(0, -1, 1))
		वापस -1;
	अगर (set_bad_offset(0, -1, 0))
		वापस -1;
	अगर (set_bad_offset(0, 2 * NSEC_PER_SEC, 1))
		वापस -1;
	अगर (set_bad_offset(0, 2 * USEC_PER_SEC, 0))
		वापस -1;
	अगर (set_bad_offset(0, NSEC_PER_SEC, 1))
		वापस -1;
	अगर (set_bad_offset(0, USEC_PER_SEC, 0))
		वापस -1;
	अगर (set_bad_offset(0, -NSEC_PER_SEC, 1))
		वापस -1;
	अगर (set_bad_offset(0, -USEC_PER_SEC, 0))
		वापस -1;

	म_लिखो("[OK]\n");
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (validate_freq())
		वापस ksft_निकास_fail();

	अगर (validate_set_offset())
		वापस ksft_निकास_fail();

	वापस ksft_निकास_pass();
पूर्ण
