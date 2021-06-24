<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/io.c
 *
 * Copyright (C) 2018, Google LLC.
 */

#समावेश "test_util.h"

/* Test Write
 *
 * A wrapper क्रम ग_लिखो(2), that स्वतःmatically handles the following
 * special conditions:
 *
 *   + Interrupted प्रणाली call (EINTR)
 *   + Write of less than requested amount
 *   + Non-block वापस (EAGAIN)
 *
 * For each of the above, an additional ग_लिखो is perक्रमmed to स्वतःmatically
 * जारी writing the requested data.
 * There are also many हालs where ग_लिखो(2) can वापस an unexpected
 * error (e.g. EIO).  Such errors cause a TEST_ASSERT failure.
 *
 * Note, क्रम function signature compatibility with ग_लिखो(2), this function
 * वापसs the number of bytes written, but that value will always be equal
 * to the number of requested bytes.  All other conditions in this and
 * future enhancements to this function either स्वतःmatically issue another
 * ग_लिखो(2) or cause a TEST_ASSERT failure.
 *
 * Args:
 *  fd    - Opened file descriptor to file to be written.
 *  count - Number of bytes to ग_लिखो.
 *
 * Output:
 *  buf   - Starting address of data to be written.
 *
 * Return:
 *  On success, number of bytes written.
 *  On failure, a TEST_ASSERT failure is caused.
 */
sमाप_प्रकार test_ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार rc;
	sमाप_प्रकार num_written = 0;
	माप_प्रकार num_left = count;
	स्थिर अक्षर *ptr = buf;

	/* Note: Count of zero is allowed (see "RETURN VALUE" portion of
	 * ग_लिखो(2) manpage क्रम details.
	 */
	TEST_ASSERT(count >= 0, "Unexpected count, count: %li", count);

	करो अणु
		rc = ग_लिखो(fd, ptr, num_left);

		चयन (rc) अणु
		हाल -1:
			TEST_ASSERT(त्रुटि_सं == EAGAIN || त्रुटि_सं == EINTR,
				    "Unexpected write failure,\n"
				    "  rc: %zi errno: %i", rc, त्रुटि_सं);
			जारी;

		हाल 0:
			TEST_FAIL("Unexpected EOF,\n"
				  "  rc: %zi num_written: %zi num_left: %zu",
				  rc, num_written, num_left);
			अवरोध;

		शेष:
			TEST_ASSERT(rc >= 0, "Unexpected ret from write,\n"
				"  rc: %zi errno: %i", rc, त्रुटि_सं);
			num_written += rc;
			num_left -= rc;
			ptr += rc;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (num_written < count);

	वापस num_written;
पूर्ण

/* Test Read
 *
 * A wrapper क्रम पढ़ो(2), that स्वतःmatically handles the following
 * special conditions:
 *
 *   + Interrupted प्रणाली call (EINTR)
 *   + Read of less than requested amount
 *   + Non-block वापस (EAGAIN)
 *
 * For each of the above, an additional पढ़ो is perक्रमmed to स्वतःmatically
 * जारी पढ़ोing the requested data.
 * There are also many हालs where पढ़ो(2) can वापस an unexpected
 * error (e.g. EIO).  Such errors cause a TEST_ASSERT failure.  Note,
 * it is expected that the file खोलोed by fd at the current file position
 * contains at least the number of requested bytes to be पढ़ो.  A TEST_ASSERT
 * failure is produced अगर an End-Of-File condition occurs, beक्रमe all the
 * data is पढ़ो.  It is the callers responsibility to assure that sufficient
 * data exists.
 *
 * Note, क्रम function signature compatibility with पढ़ो(2), this function
 * वापसs the number of bytes पढ़ो, but that value will always be equal
 * to the number of requested bytes.  All other conditions in this and
 * future enhancements to this function either स्वतःmatically issue another
 * पढ़ो(2) or cause a TEST_ASSERT failure.
 *
 * Args:
 *  fd    - Opened file descriptor to file to be पढ़ो.
 *  count - Number of bytes to पढ़ो.
 *
 * Output:
 *  buf   - Starting address of where to ग_लिखो the bytes पढ़ो.
 *
 * Return:
 *  On success, number of bytes पढ़ो.
 *  On failure, a TEST_ASSERT failure is caused.
 */
sमाप_प्रकार test_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार rc;
	sमाप_प्रकार num_पढ़ो = 0;
	माप_प्रकार num_left = count;
	अक्षर *ptr = buf;

	/* Note: Count of zero is allowed (see "If count is zero" portion of
	 * पढ़ो(2) manpage क्रम details.
	 */
	TEST_ASSERT(count >= 0, "Unexpected count, count: %li", count);

	करो अणु
		rc = पढ़ो(fd, ptr, num_left);

		चयन (rc) अणु
		हाल -1:
			TEST_ASSERT(त्रुटि_सं == EAGAIN || त्रुटि_सं == EINTR,
				    "Unexpected read failure,\n"
				    "  rc: %zi errno: %i", rc, त्रुटि_सं);
			अवरोध;

		हाल 0:
			TEST_FAIL("Unexpected EOF,\n"
				  "   rc: %zi num_read: %zi num_left: %zu",
				  rc, num_पढ़ो, num_left);
			अवरोध;

		शेष:
			TEST_ASSERT(rc > 0, "Unexpected ret from read,\n"
				    "  rc: %zi errno: %i", rc, त्रुटि_सं);
			num_पढ़ो += rc;
			num_left -= rc;
			ptr += rc;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (num_पढ़ो < count);

	वापस num_पढ़ो;
पूर्ण
