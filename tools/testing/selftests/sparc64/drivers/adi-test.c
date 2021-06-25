<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * selftest क्रम sparc64's privileged ADI driver
 *
 * Author: Tom Hromatka <tom.hromatka@oracle.com>
 */
#समावेश <linux/kernel.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#समावेश "../../kselftest.h"

#घोषणा DEBUG_LEVEL_1_BIT	(0x0001)
#घोषणा DEBUG_LEVEL_2_BIT	(0x0002)
#घोषणा DEBUG_LEVEL_3_BIT	(0x0004)
#घोषणा DEBUG_LEVEL_4_BIT	(0x0008)
#घोषणा DEBUG_TIMING_BIT	(0x1000)

#अगर_अघोषित ARRAY_SIZE
# define ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

/* bit mask of enabled bits to prपूर्णांक */
#घोषणा DEBUG 0x0001

#घोषणा DEBUG_PRINT_L1(...)	debug_prपूर्णांक(DEBUG_LEVEL_1_BIT, __VA_ARGS__)
#घोषणा DEBUG_PRINT_L2(...)	debug_prपूर्णांक(DEBUG_LEVEL_2_BIT, __VA_ARGS__)
#घोषणा DEBUG_PRINT_L3(...)	debug_prपूर्णांक(DEBUG_LEVEL_3_BIT, __VA_ARGS__)
#घोषणा DEBUG_PRINT_L4(...)	debug_prपूर्णांक(DEBUG_LEVEL_4_BIT, __VA_ARGS__)
#घोषणा DEBUG_PRINT_T(...)	debug_prपूर्णांक(DEBUG_TIMING_BIT, __VA_ARGS__)

अटल व्योम debug_prपूर्णांक(पूर्णांक level, स्थिर अक्षर *s, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, s);

	अगर (DEBUG & level)
		भख_लिखो(मानक_निकास, s, args);
	बहु_पूर्ण(args);
पूर्ण

#अगर_अघोषित min
#घोषणा min(x, y) ((x) < (y) ? x : y)
#पूर्ण_अगर

#घोषणा RETURN_FROM_TEST(_ret) \
	करो अणु \
		DEBUG_PRINT_L1( \
			"\tTest %s returned %d\n", __func__, _ret); \
		वापस _ret; \
	पूर्ण जबतक (0)

#घोषणा ADI_BLKSZ	64
#घोषणा ADI_MAX_VERSION	15

#घोषणा TEST_STEP_FAILURE(_ret) \
	करो अणु \
		ख_लिखो(मानक_त्रुटि, "\tTest step failure: %d at %s:%d\n", \
			_ret, __func__, __LINE__); \
		जाओ out; \
	पूर्ण जबतक (0)

#घोषणा RDTICK(_x) \
	यंत्र अस्थिर(" rd %%tick, %0\n" : "=r" (_x))

अटल पूर्णांक अक्रमom_version(व्योम)
अणु
	दीर्घ tick;

	RDTICK(tick);

	वापस tick % (ADI_MAX_VERSION + 1);
पूर्ण

#घोषणा MAX_RANGES_SUPPORTED	5
अटल स्थिर अक्षर प्रणाली_ram_str[] = "System RAM\n";
अटल पूर्णांक range_count;
अटल अचिन्हित दीर्घ दीर्घ पूर्णांक start_addr[MAX_RANGES_SUPPORTED];
अटल अचिन्हित दीर्घ दीर्घ पूर्णांक   end_addr[MAX_RANGES_SUPPORTED];

काष्ठा stats अणु
	अक्षर		name[16];
	अचिन्हित दीर्घ	total;
	अचिन्हित दीर्घ	count;
	अचिन्हित दीर्घ	bytes;
पूर्ण;

अटल काष्ठा stats पढ़ो_stats = अणु
	.name = "read", .total = 0, .count = 0, .bytes = 0पूर्ण;
अटल काष्ठा stats pपढ़ो_stats = अणु
	.name = "pread", .total = 0, .count = 0, .bytes = 0पूर्ण;
अटल काष्ठा stats ग_लिखो_stats = अणु
	.name = "write", .total = 0, .count = 0, .bytes = 0पूर्ण;
अटल काष्ठा stats pग_लिखो_stats = अणु
	.name = "pwrite", .total = 0, .count = 0, .bytes = 0पूर्ण;
अटल काष्ठा stats seek_stats = अणु
	.name = "seek", .total = 0, .count = 0, .bytes = 0पूर्ण;

अटल व्योम update_stats(काष्ठा stats * स्थिर ustats,
			 अचिन्हित दीर्घ measurement, अचिन्हित दीर्घ bytes)
अणु
	ustats->total += measurement;
	ustats->bytes += bytes;
	ustats->count++;
पूर्ण

अटल व्योम prपूर्णांक_ustats(स्थिर काष्ठा stats * स्थिर ustats)
अणु
	DEBUG_PRINT_L1("%s\t%7d\t%7.0f\t%7.0f\n",
		       ustats->name, ustats->count,
		       (भग्न)ustats->total / (भग्न)ustats->count,
		       (भग्न)ustats->bytes / (भग्न)ustats->count);
पूर्ण

अटल व्योम prपूर्णांक_stats(व्योम)
अणु
	DEBUG_PRINT_L1("\nSyscall\tCall\tAvgTime\tAvgSize\n"
		       "\tCount\t(ticks)\t(bytes)\n"
		       "-------------------------------\n");

	prपूर्णांक_ustats(&पढ़ो_stats);
	prपूर्णांक_ustats(&pपढ़ो_stats);
	prपूर्णांक_ustats(&ग_लिखो_stats);
	prपूर्णांक_ustats(&pग_लिखो_stats);
	prपूर्णांक_ustats(&seek_stats);
पूर्ण

अटल पूर्णांक build_memory_map(व्योम)
अणु
	अक्षर line[256];
	खाता *fp;
	पूर्णांक i;

	range_count = 0;

	fp = ख_खोलो("/proc/iomem", "r");
	अगर (!fp) अणु
		ख_लिखो(मानक_त्रुटि, "/proc/iomem: error %d: %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	जबतक (ख_माला_लो(line, माप(line), fp) != 0) अणु
		अगर (म_माला(line, प्रणाली_ram_str)) अणु
			अक्षर *dash, *end_ptr;

			/* Given a line like this:
			 * d0400000-10ffaffff : System RAM
			 * replace the "-" with a space
			 */
			dash = म_माला(line, "-");
			dash[0] = 0x20;

			start_addr[range_count] = म_से_अदीर्घl(line, &end_ptr, 16);
			end_addr[range_count] = म_से_अदीर्घl(end_ptr, शून्य, 16);
			range_count++;
		पूर्ण
	पूर्ण

	ख_बंद(fp);

	DEBUG_PRINT_L1("RAM Ranges\n");
	क्रम (i = 0; i < range_count; i++)
		DEBUG_PRINT_L1("\trange %d: 0x%llx\t- 0x%llx\n",
			       i, start_addr[i], end_addr[i]);

	अगर (range_count == 0) अणु
		ख_लिखो(मानक_त्रुटि, "No valid address ranges found.  Error.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_adi(पूर्णांक fd, अचिन्हित अक्षर *buf, पूर्णांक buf_sz)
अणु
	पूर्णांक ret, bytes_पढ़ो = 0;
	दीर्घ start, end, elapsed_समय = 0;

	करो अणु
		RDTICK(start);
		ret = पढ़ो(fd, buf + bytes_पढ़ो, buf_sz - bytes_पढ़ो);
		RDTICK(end);
		अगर (ret < 0)
			वापस -त्रुटि_सं;

		elapsed_समय += end - start;
		update_stats(&पढ़ो_stats, elapsed_समय, buf_sz);
		bytes_पढ़ो += ret;

	पूर्ण जबतक (bytes_पढ़ो < buf_sz);

	DEBUG_PRINT_T("\tread elapsed timed = %ld\n", elapsed_समय);
	DEBUG_PRINT_L3("\tRead  %d bytes\n", bytes_पढ़ो);

	वापस bytes_पढ़ो;
पूर्ण

अटल पूर्णांक pपढ़ो_adi(पूर्णांक fd, अचिन्हित अक्षर *buf,
		     पूर्णांक buf_sz, अचिन्हित दीर्घ offset)
अणु
	पूर्णांक ret, i, bytes_पढ़ो = 0;
	अचिन्हित दीर्घ cur_offset;
	दीर्घ start, end, elapsed_समय = 0;

	cur_offset = offset;
	करो अणु
		RDTICK(start);
		ret = pपढ़ो(fd, buf + bytes_पढ़ो, buf_sz - bytes_पढ़ो,
			    cur_offset);
		RDTICK(end);
		अगर (ret < 0)
			वापस -त्रुटि_सं;

		elapsed_समय += end - start;
		update_stats(&pपढ़ो_stats, elapsed_समय, buf_sz);
		bytes_पढ़ो += ret;
		cur_offset += ret;

	पूर्ण जबतक (bytes_पढ़ो < buf_sz);

	DEBUG_PRINT_T("\tpread elapsed timed = %ld\n", elapsed_समय);
	DEBUG_PRINT_L3("\tRead  %d bytes starting at offset 0x%lx\n",
		       bytes_पढ़ो, offset);
	क्रम (i = 0; i < bytes_पढ़ो; i++)
		DEBUG_PRINT_L4("\t\t0x%lx\t%d\n", offset + i, buf[i]);

	वापस bytes_पढ़ो;
पूर्ण

अटल पूर्णांक ग_लिखो_adi(पूर्णांक fd, स्थिर अचिन्हित अक्षर * स्थिर buf, पूर्णांक buf_sz)
अणु
	पूर्णांक ret, bytes_written = 0;
	दीर्घ start, end, elapsed_समय = 0;

	करो अणु
		RDTICK(start);
		ret = ग_लिखो(fd, buf + bytes_written, buf_sz - bytes_written);
		RDTICK(end);
		अगर (ret < 0)
			वापस -त्रुटि_सं;

		elapsed_समय += (end - start);
		update_stats(&ग_लिखो_stats, elapsed_समय, buf_sz);
		bytes_written += ret;
	पूर्ण जबतक (bytes_written < buf_sz);

	DEBUG_PRINT_T("\twrite elapsed timed = %ld\n", elapsed_समय);
	DEBUG_PRINT_L3("\tWrote %d of %d bytes\n", bytes_written, buf_sz);

	वापस bytes_written;
पूर्ण

अटल पूर्णांक pग_लिखो_adi(पूर्णांक fd, स्थिर अचिन्हित अक्षर * स्थिर buf,
		      पूर्णांक buf_sz, अचिन्हित दीर्घ offset)
अणु
	पूर्णांक ret, bytes_written = 0;
	अचिन्हित दीर्घ cur_offset;
	दीर्घ start, end, elapsed_समय = 0;

	cur_offset = offset;

	करो अणु
		RDTICK(start);
		ret = pग_लिखो(fd, buf + bytes_written,
			     buf_sz - bytes_written, cur_offset);
		RDTICK(end);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "pwrite(): error %d: %s\n",
				त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			वापस -त्रुटि_सं;
		पूर्ण

		elapsed_समय += (end - start);
		update_stats(&pग_लिखो_stats, elapsed_समय, buf_sz);
		bytes_written += ret;
		cur_offset += ret;

	पूर्ण जबतक (bytes_written < buf_sz);

	DEBUG_PRINT_T("\tpwrite elapsed timed = %ld\n", elapsed_समय);
	DEBUG_PRINT_L3("\tWrote %d of %d bytes starting at address 0x%lx\n",
		       bytes_written, buf_sz, offset);

	वापस bytes_written;
पूर्ण

अटल off_t seek_adi(पूर्णांक fd, off_t offset, पूर्णांक whence)
अणु
	दीर्घ start, end;
	off_t ret;

	RDTICK(start);
	ret = lseek(fd, offset, whence);
	RDTICK(end);
	DEBUG_PRINT_L2("\tlseek ret = 0x%llx\n", ret);
	अगर (ret < 0)
		जाओ out;

	DEBUG_PRINT_T("\tlseek elapsed timed = %ld\n", end - start);
	update_stats(&seek_stats, end - start, 0);

out:
	(व्योम)lseek(fd, 0, अंत_से);
	वापस ret;
पूर्ण

अटल पूर्णांक test0_prpw_aligned_1byte(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		(end_addr[range_count - 1] - 0x1000) & ~(ADI_BLKSZ - 1);
	अचिन्हित अक्षर version[1], expected_version;
	loff_t offset;
	पूर्णांक ret;

	version[0] = अक्रमom_version();
	expected_version = version[0];

	offset = paddr / ADI_BLKSZ;

	ret = pग_लिखो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	ret = pपढ़ो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	अगर (expected_version != version[0]) अणु
		DEBUG_PRINT_L2("\tExpected version %d but read version %d\n",
			       expected_version, version[0]);
		TEST_STEP_FAILURE(-expected_version);
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

#घोषणा TEST1_VERSION_SZ	4096
अटल पूर्णांक test1_prpw_aligned_4096bytes(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		(end_addr[range_count - 1] - 0x6000) & ~(ADI_BLKSZ - 1);
	अचिन्हित अक्षर version[TEST1_VERSION_SZ],
		expected_version[TEST1_VERSION_SZ];
	loff_t offset;
	पूर्णांक ret, i;

	क्रम (i = 0; i < TEST1_VERSION_SZ; i++) अणु
		version[i] = अक्रमom_version();
		expected_version[i] = version[i];
	पूर्ण

	offset = paddr / ADI_BLKSZ;

	ret = pग_लिखो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	ret = pपढ़ो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	क्रम (i = 0; i < TEST1_VERSION_SZ; i++) अणु
		अगर (expected_version[i] != version[i]) अणु
			DEBUG_PRINT_L2(
				"\tExpected version %d but read version %d\n",
				expected_version, version[0]);
			TEST_STEP_FAILURE(-expected_version[i]);
		पूर्ण
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

#घोषणा TEST2_VERSION_SZ	10327
अटल पूर्णांक test2_prpw_aligned_10327bytes(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		(start_addr[0] + 0x6000) & ~(ADI_BLKSZ - 1);
	अचिन्हित अक्षर version[TEST2_VERSION_SZ],
		expected_version[TEST2_VERSION_SZ];
	loff_t offset;
	पूर्णांक ret, i;

	क्रम (i = 0; i < TEST2_VERSION_SZ; i++) अणु
		version[i] = अक्रमom_version();
		expected_version[i] = version[i];
	पूर्ण

	offset = paddr / ADI_BLKSZ;

	ret = pग_लिखो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	ret = pपढ़ो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	क्रम (i = 0; i < TEST2_VERSION_SZ; i++) अणु
		अगर (expected_version[i] != version[i]) अणु
			DEBUG_PRINT_L2(
				"\tExpected version %d but read version %d\n",
				expected_version, version[0]);
			TEST_STEP_FAILURE(-expected_version[i]);
		पूर्ण
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

#घोषणा TEST3_VERSION_SZ	12541
अटल पूर्णांक test3_prpw_unaligned_12541bytes(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		((start_addr[0] + 0xC000) & ~(ADI_BLKSZ - 1)) + 17;
	अचिन्हित अक्षर version[TEST3_VERSION_SZ],
		expected_version[TEST3_VERSION_SZ];
	loff_t offset;
	पूर्णांक ret, i;

	क्रम (i = 0; i < TEST3_VERSION_SZ; i++) अणु
		version[i] = अक्रमom_version();
		expected_version[i] = version[i];
	पूर्ण

	offset = paddr / ADI_BLKSZ;

	ret = pग_लिखो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	ret = pपढ़ो_adi(fd, version, माप(version), offset);
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	क्रम (i = 0; i < TEST3_VERSION_SZ; i++) अणु
		अगर (expected_version[i] != version[i]) अणु
			DEBUG_PRINT_L2(
				"\tExpected version %d but read version %d\n",
				expected_version, version[0]);
			TEST_STEP_FAILURE(-expected_version[i]);
		पूर्ण
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

अटल पूर्णांक test4_lseek(पूर्णांक fd)
अणु
#घोषणा	OFFSET_ADD	(0x100)
#घोषणा OFFSET_SUBTRACT	(0xFFFFFFF000000000)

	off_t offset_out, offset_in;
	पूर्णांक ret;


	offset_in = 0x123456789abcdef0;
	offset_out = seek_adi(fd, offset_in, शुरू_से);
	अगर (offset_out != offset_in) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	/* seek to the current offset.  this should वापस EINVAL */
	offset_out = seek_adi(fd, offset_in, शुरू_से);
	अगर (offset_out < 0 && त्रुटि_सं == EINVAL)
		DEBUG_PRINT_L2(
			"\tSEEK_SET failed as designed. Not an error\n");
	अन्यथा अणु
		ret = -2;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	offset_out = seek_adi(fd, 0, प्रस्तुत_से);
	अगर (offset_out != offset_in) अणु
		ret = -3;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	offset_out = seek_adi(fd, OFFSET_ADD, प्रस्तुत_से);
	अगर (offset_out != (offset_in + OFFSET_ADD)) अणु
		ret = -4;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	offset_out = seek_adi(fd, OFFSET_SUBTRACT, प्रस्तुत_से);
	अगर (offset_out != (offset_in + OFFSET_ADD + OFFSET_SUBTRACT)) अणु
		ret = -5;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

अटल पूर्णांक test5_rw_aligned_1byte(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		(end_addr[range_count - 1] - 0xF000) & ~(ADI_BLKSZ - 1);
	अचिन्हित अक्षर version, expected_version;
	loff_t offset;
	off_t oret;
	पूर्णांक ret;

	offset = paddr / ADI_BLKSZ;
	version = expected_version = अक्रमom_version();

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = ग_लिखो_adi(fd, &version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = पढ़ो_adi(fd, &version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	अगर (expected_version != version) अणु
		DEBUG_PRINT_L2("\tExpected version %d but read version %d\n",
			       expected_version, version);
		TEST_STEP_FAILURE(-expected_version);
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

#घोषणा TEST6_VERSION_SZ        9434
अटल पूर्णांक test6_rw_aligned_9434bytes(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
		(end_addr[range_count - 1] - 0x5F000) & ~(ADI_BLKSZ - 1);
	अचिन्हित अक्षर version[TEST6_VERSION_SZ],
		      expected_version[TEST6_VERSION_SZ];
	loff_t offset;
	off_t oret;
	पूर्णांक ret, i;

	offset = paddr / ADI_BLKSZ;
	क्रम (i = 0; i < TEST6_VERSION_SZ; i++)
		version[i] = expected_version[i] = अक्रमom_version();

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = ग_लिखो_adi(fd, version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	स_रखो(version, 0, TEST6_VERSION_SZ);

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = पढ़ो_adi(fd, version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	क्रम (i = 0; i < TEST6_VERSION_SZ; i++) अणु
		अगर (expected_version[i] != version[i]) अणु
			DEBUG_PRINT_L2(
				"\tExpected version %d but read version %d\n",
				expected_version[i], version[i]);
			TEST_STEP_FAILURE(-expected_version[i]);
		पूर्ण
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

#घोषणा TEST7_VERSION_SZ        14963
अटल पूर्णांक test7_rw_aligned_14963bytes(पूर्णांक fd)
अणु
	/* somewhat arbitrarily chosen address */
	अचिन्हित दीर्घ paddr =
	  ((start_addr[range_count - 1] + 0xF000) & ~(ADI_BLKSZ - 1)) + 39;
	अचिन्हित अक्षर version[TEST7_VERSION_SZ],
		      expected_version[TEST7_VERSION_SZ];
	loff_t offset;
	off_t oret;
	पूर्णांक ret, i;

	offset = paddr / ADI_BLKSZ;
	क्रम (i = 0; i < TEST7_VERSION_SZ; i++) अणु
		version[i] = अक्रमom_version();
		expected_version[i] = version[i];
	पूर्ण

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = ग_लिखो_adi(fd, version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	स_रखो(version, 0, TEST7_VERSION_SZ);

	oret = seek_adi(fd, offset, शुरू_से);
	अगर (oret != offset) अणु
		ret = -1;
		TEST_STEP_FAILURE(ret);
	पूर्ण

	ret = पढ़ो_adi(fd, version, माप(version));
	अगर (ret != माप(version))
		TEST_STEP_FAILURE(ret);

	क्रम (i = 0; i < TEST7_VERSION_SZ; i++) अणु
		अगर (expected_version[i] != version[i]) अणु
			DEBUG_PRINT_L2(
				"\tExpected version %d but read version %d\n",
				expected_version[i], version[i]);
			TEST_STEP_FAILURE(-expected_version[i]);
		पूर्ण

		paddr += ADI_BLKSZ;
	पूर्ण

	ret = 0;
out:
	RETURN_FROM_TEST(ret);
पूर्ण

अटल पूर्णांक (*tests[])(पूर्णांक fd) = अणु
	test0_prpw_aligned_1byte,
	test1_prpw_aligned_4096bytes,
	test2_prpw_aligned_10327bytes,
	test3_prpw_unaligned_12541bytes,
	test4_lseek,
	test5_rw_aligned_1byte,
	test6_rw_aligned_9434bytes,
	test7_rw_aligned_14963bytes,
पूर्ण;
#घोषणा TEST_COUNT	ARRAY_SIZE(tests)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक fd, ret, test;

	ret = build_memory_map();
	अगर (ret < 0)
		वापस ret;

	fd = खोलो("/dev/adi", O_RDWR);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "open: error %d: %s\n",
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस -त्रुटि_सं;
	पूर्ण

	क्रम (test = 0; test < TEST_COUNT; test++) अणु
		DEBUG_PRINT_L1("Running test #%d\n", test);

		ret = (*tests[test])(fd);
		अगर (ret != 0)
			ksft_test_result_fail("Test #%d failed: error %d\n",
					      test, ret);
		अन्यथा
			ksft_test_result_pass("Test #%d passed\n", test);
	पूर्ण

	prपूर्णांक_stats();
	बंद(fd);

	अगर (ksft_get_fail_cnt() > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();

	/* it's impossible to get here, but the compiler throws a warning
	 * about control reaching the end of non-व्योम function.  bah.
	 */
	वापस 0;
पूर्ण
