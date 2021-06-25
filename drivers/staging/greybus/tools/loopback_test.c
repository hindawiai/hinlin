<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 * Loopback test application
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <poll.h>
#समावेश <sys/types.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <dirent.h>
#समावेश <संकेत.स>

#घोषणा MAX_NUM_DEVICES 10
#घोषणा MAX_SYSFS_PREFIX 0x80
#घोषणा MAX_SYSFS_PATH	0x200
#घोषणा CSV_MAX_LINE	0x1000
#घोषणा SYSFS_MAX_INT	0x20
#घोषणा MAX_STR_LEN	255
#घोषणा DEFAULT_ASYNC_TIMEOUT 200000

काष्ठा dict अणु
	अक्षर *name;
	पूर्णांक type;
पूर्ण;

अटल काष्ठा dict dict[] = अणु
	अणु"ping", 2पूर्ण,
	अणु"transfer", 3पूर्ण,
	अणु"sink", 4पूर्ण,
	अणुशून्य,पूर्ण		/* list termination */
पूर्ण;

काष्ठा loopback_results अणु
	भग्न latency_avg;
	uपूर्णांक32_t latency_max;
	uपूर्णांक32_t latency_min;
	uपूर्णांक32_t latency_jitter;

	भग्न request_avg;
	uपूर्णांक32_t request_max;
	uपूर्णांक32_t request_min;
	uपूर्णांक32_t request_jitter;

	भग्न throughput_avg;
	uपूर्णांक32_t throughput_max;
	uपूर्णांक32_t throughput_min;
	uपूर्णांक32_t throughput_jitter;

	भग्न apbridge_unipro_latency_avg;
	uपूर्णांक32_t apbridge_unipro_latency_max;
	uपूर्णांक32_t apbridge_unipro_latency_min;
	uपूर्णांक32_t apbridge_unipro_latency_jitter;

	भग्न gbphy_firmware_latency_avg;
	uपूर्णांक32_t gbphy_firmware_latency_max;
	uपूर्णांक32_t gbphy_firmware_latency_min;
	uपूर्णांक32_t gbphy_firmware_latency_jitter;

	uपूर्णांक32_t error;
पूर्ण;

काष्ठा loopback_device अणु
	अक्षर name[MAX_STR_LEN];
	अक्षर sysfs_entry[MAX_SYSFS_PATH];
	अक्षर debugfs_entry[MAX_SYSFS_PATH];
	काष्ठा loopback_results results;
पूर्ण;

काष्ठा loopback_test अणु
	पूर्णांक verbose;
	पूर्णांक debug;
	पूर्णांक raw_data_dump;
	पूर्णांक porcelain;
	पूर्णांक mask;
	पूर्णांक size;
	पूर्णांक iteration_max;
	पूर्णांक aggregate_output;
	पूर्णांक test_id;
	पूर्णांक device_count;
	पूर्णांक list_devices;
	पूर्णांक use_async;
	पूर्णांक async_समयout;
	पूर्णांक async_outstanding_operations;
	पूर्णांक us_रुको;
	पूर्णांक file_output;
	पूर्णांक stop_all;
	पूर्णांक poll_count;
	अक्षर test_name[MAX_STR_LEN];
	अक्षर sysfs_prefix[MAX_SYSFS_PREFIX];
	अक्षर debugfs_prefix[MAX_SYSFS_PREFIX];
	काष्ठा बारpec poll_समयout;
	काष्ठा loopback_device devices[MAX_NUM_DEVICES];
	काष्ठा loopback_results aggregate_results;
	काष्ठा pollfd fds[MAX_NUM_DEVICES];
पूर्ण;

काष्ठा loopback_test t;

/* Helper macros to calculate the aggregate results क्रम all devices */
अटल अंतरभूत पूर्णांक device_enabled(काष्ठा loopback_test *t, पूर्णांक dev_idx);

#घोषणा GET_MAX(field)							\
अटल पूर्णांक get_##field##_aggregate(काष्ठा loopback_test *t)		\
अणु									\
	uपूर्णांक32_t max = 0;						\
	पूर्णांक i;								\
	क्रम (i = 0; i < t->device_count; i++) अणु				\
		अगर (!device_enabled(t, i))				\
			जारी;					\
		अगर (t->devices[i].results.field > max)			\
			max = t->devices[i].results.field;		\
	पूर्ण								\
	वापस max;							\
पूर्ण									\

#घोषणा GET_MIN(field)							\
अटल पूर्णांक get_##field##_aggregate(काष्ठा loopback_test *t)		\
अणु									\
	uपूर्णांक32_t min = ~0;						\
	पूर्णांक i;								\
	क्रम (i = 0; i < t->device_count; i++) अणु				\
		अगर (!device_enabled(t, i))				\
			जारी;					\
		अगर (t->devices[i].results.field < min)			\
			min = t->devices[i].results.field;		\
	पूर्ण								\
	वापस min;							\
पूर्ण									\

#घोषणा GET_AVG(field)							\
अटल पूर्णांक get_##field##_aggregate(काष्ठा loopback_test *t)		\
अणु									\
	uपूर्णांक32_t val = 0;						\
	uपूर्णांक32_t count = 0;						\
	पूर्णांक i;								\
	क्रम (i = 0; i < t->device_count; i++) अणु				\
		अगर (!device_enabled(t, i))				\
			जारी;					\
		count++;						\
		val += t->devices[i].results.field;			\
	पूर्ण								\
	अगर (count)							\
		val /= count;						\
	वापस val;							\
पूर्ण									\

GET_MAX(throughput_max);
GET_MAX(request_max);
GET_MAX(latency_max);
GET_MAX(apbridge_unipro_latency_max);
GET_MAX(gbphy_firmware_latency_max);
GET_MIN(throughput_min);
GET_MIN(request_min);
GET_MIN(latency_min);
GET_MIN(apbridge_unipro_latency_min);
GET_MIN(gbphy_firmware_latency_min);
GET_AVG(throughput_avg);
GET_AVG(request_avg);
GET_AVG(latency_avg);
GET_AVG(apbridge_unipro_latency_avg);
GET_AVG(gbphy_firmware_latency_avg);

व्योम पात(व्योम)
अणु
	_निकास(1);
पूर्ण

व्योम usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: loopback_test TEST [SIZE] ITERATIONS [SYSPATH] [DBGPATH]\n\n"
	"  Run TEST for a number of ITERATIONS with operation data SIZE bytes\n"
	"  TEST may be \'ping\' \'transfer\' or \'sink\'\n"
	"  SIZE indicates the size of transfer <= greybus max payload bytes\n"
	"  ITERATIONS indicates the number of times to execute TEST at SIZE bytes\n"
	"             Note if ITERATIONS is set to zero then this utility will\n"
	"             initiate an infinite (non terminating) test and exit\n"
	"             without logging any metrics data\n"
	"  SYSPATH indicates the sysfs path for the loopback greybus entries e.g.\n"
	"          /sys/bus/greybus/devices\n"
	"  DBGPATH indicates the debugfs path for the loopback greybus entries e.g.\n"
	"          /sys/kernel/debug/gb_loopback/\n"
	" Mandatory arguments\n"
	"   -t     must be one of the test names - sink, transfer or ping\n"
	"   -i     iteration count - the number of iterations to run the test over\n"
	" Optional arguments\n"
	"   -S     sysfs location - location for greybus 'endo' entries default /sys/bus/greybus/devices/\n"
	"   -D     debugfs location - location for loopback debugfs entries default /sys/kernel/debug/gb_loopback/\n"
	"   -s     size of data packet to send during test - defaults to zero\n"
	"   -m     mask - a bit mask of connections to include example: -m 8 = 4th connection -m 9 = 1st and 4th connection etc\n"
	"                 default is zero which means broadcast to all connections\n"
	"   -v     verbose output\n"
	"   -d     debug output\n"
	"   -r     raw data output - when specified the full list of latency values are included in the output CSV\n"
	"   -p     porcelain - when specified printout is in a user-friendly non-CSV format. This option suppresses writing to CSV file\n"
	"   -a     aggregate - show aggregation of all enabled devices\n"
	"   -l     list found loopback devices and exit\n"
	"   -x     Async - Enable async transfers\n"
	"   -o     Async Timeout - Timeout in uSec for async operations\n"
	"   -O     Poll loop time out in seconds(max time a test is expected to last, default: 30sec)\n"
	"   -c     Max number of outstanding operations for async operations\n"
	"   -w     Wait in uSec between operations\n"
	"   -z     Enable output to a CSV file (incompatible with -p)\n"
	"   -f     When starting new loopback test, stop currently running tests on all devices\n"
	"Examples:\n"
	"  Send 10000 transfers with a packet size of 128 bytes to all active connections\n"
	"  loopback_test -t transfer -s 128 -i 10000 -S /sys/bus/greybus/devices/ -D /sys/kernel/debug/gb_loopback/\n"
	"  loopback_test -t transfer -s 128 -i 10000 -m 0\n"
	"  Send 10000 transfers with a packet size of 128 bytes to connection 1 and 4\n"
	"  loopback_test -t transfer -s 128 -i 10000 -m 9\n"
	"  loopback_test -t ping -s 0 128 -i -S /sys/bus/greybus/devices/ -D /sys/kernel/debug/gb_loopback/\n"
	"  loopback_test -t sink -s 2030 -i 32768 -S /sys/bus/greybus/devices/ -D /sys/kernel/debug/gb_loopback/\n");
	पात();
पूर्ण

अटल अंतरभूत पूर्णांक device_enabled(काष्ठा loopback_test *t, पूर्णांक dev_idx)
अणु
	अगर (!t->mask || (t->mask & (1 << dev_idx)))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम show_loopback_devices(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;

	अगर (t->device_count == 0) अणु
		म_लिखो("No loopback devices.\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < t->device_count; i++)
		म_लिखो("device[%d] = %s\n", i, t->devices[i].name);

पूर्ण

पूर्णांक खोलो_sysfs(स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node, पूर्णांक flags)
अणु
	पूर्णांक fd;
	अक्षर path[MAX_SYSFS_PATH];

	snम_लिखो(path, माप(path), "%s%s", sys_pfx, node);
	fd = खोलो(path, flags);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "unable to open %s\n", path);
		पात();
	पूर्ण
	वापस fd;
पूर्ण

पूर्णांक पढ़ो_sysfs_पूर्णांक_fd(पूर्णांक fd, स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node)
अणु
	अक्षर buf[SYSFS_MAX_INT];

	अगर (पढ़ो(fd, buf, माप(buf)) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "unable to read from %s%s %s\n", sys_pfx, node,
			म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		पात();
	पूर्ण
	वापस म_से_प(buf);
पूर्ण

भग्न पढ़ो_sysfs_भग्न_fd(पूर्णांक fd, स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node)
अणु
	अक्षर buf[SYSFS_MAX_INT];

	अगर (पढ़ो(fd, buf, माप(buf)) < 0) अणु

		ख_लिखो(मानक_त्रुटि, "unable to read from %s%s %s\n", sys_pfx, node,
			म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		पात();
	पूर्ण
	वापस म_से_भ(buf);
पूर्ण

पूर्णांक पढ़ो_sysfs_पूर्णांक(स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node)
अणु
	पूर्णांक fd, val;

	fd = खोलो_sysfs(sys_pfx, node, O_RDONLY);
	val = पढ़ो_sysfs_पूर्णांक_fd(fd, sys_pfx, node);
	बंद(fd);
	वापस val;
पूर्ण

भग्न पढ़ो_sysfs_भग्न(स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node)
अणु
	पूर्णांक fd;
	भग्न val;

	fd = खोलो_sysfs(sys_pfx, node, O_RDONLY);
	val = पढ़ो_sysfs_भग्न_fd(fd, sys_pfx, node);
	बंद(fd);
	वापस val;
पूर्ण

व्योम ग_लिखो_sysfs_val(स्थिर अक्षर *sys_pfx, स्थिर अक्षर *node, पूर्णांक val)
अणु
	पूर्णांक fd, len;
	अक्षर buf[SYSFS_MAX_INT];

	fd = खोलो_sysfs(sys_pfx, node, O_RDWR);
	len = snम_लिखो(buf, माप(buf), "%d", val);
	अगर (ग_लिखो(fd, buf, len) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "unable to write to %s%s %s\n", sys_pfx, node,
			म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		पात();
	पूर्ण
	बंद(fd);
पूर्ण

अटल पूर्णांक get_results(काष्ठा loopback_test *t)
अणु
	काष्ठा loopback_device *d;
	काष्ठा loopback_results *r;
	पूर्णांक i;

	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		d = &t->devices[i];
		r = &d->results;

		r->error = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "error");
		r->request_min = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "requests_per_second_min");
		r->request_max = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "requests_per_second_max");
		r->request_avg = पढ़ो_sysfs_भग्न(d->sysfs_entry, "requests_per_second_avg");

		r->latency_min = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "latency_min");
		r->latency_max = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "latency_max");
		r->latency_avg = पढ़ो_sysfs_भग्न(d->sysfs_entry, "latency_avg");

		r->throughput_min = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "throughput_min");
		r->throughput_max = पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "throughput_max");
		r->throughput_avg = पढ़ो_sysfs_भग्न(d->sysfs_entry, "throughput_avg");

		r->apbridge_unipro_latency_min =
			पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "apbridge_unipro_latency_min");
		r->apbridge_unipro_latency_max =
			पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "apbridge_unipro_latency_max");
		r->apbridge_unipro_latency_avg =
			पढ़ो_sysfs_भग्न(d->sysfs_entry, "apbridge_unipro_latency_avg");

		r->gbphy_firmware_latency_min =
			पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "gbphy_firmware_latency_min");
		r->gbphy_firmware_latency_max =
			पढ़ो_sysfs_पूर्णांक(d->sysfs_entry, "gbphy_firmware_latency_max");
		r->gbphy_firmware_latency_avg =
			पढ़ो_sysfs_भग्न(d->sysfs_entry, "gbphy_firmware_latency_avg");

		r->request_jitter = r->request_max - r->request_min;
		r->latency_jitter = r->latency_max - r->latency_min;
		r->throughput_jitter = r->throughput_max - r->throughput_min;
		r->apbridge_unipro_latency_jitter =
			r->apbridge_unipro_latency_max - r->apbridge_unipro_latency_min;
		r->gbphy_firmware_latency_jitter =
			r->gbphy_firmware_latency_max - r->gbphy_firmware_latency_min;

	पूर्ण

	/*calculate the aggregate results of all enabled devices */
	अगर (t->aggregate_output) अणु
		r = &t->aggregate_results;

		r->request_min = get_request_min_aggregate(t);
		r->request_max = get_request_max_aggregate(t);
		r->request_avg = get_request_avg_aggregate(t);

		r->latency_min = get_latency_min_aggregate(t);
		r->latency_max = get_latency_max_aggregate(t);
		r->latency_avg = get_latency_avg_aggregate(t);

		r->throughput_min = get_throughput_min_aggregate(t);
		r->throughput_max = get_throughput_max_aggregate(t);
		r->throughput_avg = get_throughput_avg_aggregate(t);

		r->apbridge_unipro_latency_min =
			get_apbridge_unipro_latency_min_aggregate(t);
		r->apbridge_unipro_latency_max =
			get_apbridge_unipro_latency_max_aggregate(t);
		r->apbridge_unipro_latency_avg =
			get_apbridge_unipro_latency_avg_aggregate(t);

		r->gbphy_firmware_latency_min =
			get_gbphy_firmware_latency_min_aggregate(t);
		r->gbphy_firmware_latency_max =
			get_gbphy_firmware_latency_max_aggregate(t);
		r->gbphy_firmware_latency_avg =
			get_gbphy_firmware_latency_avg_aggregate(t);

		r->request_jitter = r->request_max - r->request_min;
		r->latency_jitter = r->latency_max - r->latency_min;
		r->throughput_jitter = r->throughput_max - r->throughput_min;
		r->apbridge_unipro_latency_jitter =
			r->apbridge_unipro_latency_max - r->apbridge_unipro_latency_min;
		r->gbphy_firmware_latency_jitter =
			r->gbphy_firmware_latency_max - r->gbphy_firmware_latency_min;

	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक क्रमmat_output(काष्ठा loopback_test *t,
		  काष्ठा loopback_results *r,
		  स्थिर अक्षर *dev_name,
		  अक्षर *buf, पूर्णांक buf_len,
		  काष्ठा पंचांग *पंचांग)
अणु
	पूर्णांक len = 0;

	स_रखो(buf, 0x00, buf_len);
	len = snम_लिखो(buf, buf_len, "%u-%u-%u %u:%u:%u",
		       पंचांग->पंचांग_year + 1900, पंचांग->पंचांग_mon + 1, पंचांग->पंचांग_mday,
		       पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);

	अगर (t->porcelain) अणु
		len += snम_लिखो(&buf[len], buf_len - len,
			"\n test:\t\t\t%s\n path:\t\t\t%s\n size:\t\t\t%u\n iterations:\t\t%u\n errors:\t\t%u\n async:\t\t\t%s\n",
			t->test_name,
			dev_name,
			t->size,
			t->iteration_max,
			r->error,
			t->use_async ? "Enabled" : "Disabled");

		len += snम_लिखो(&buf[len], buf_len - len,
			" requests per-sec:\tmin=%u, max=%u, average=%f, jitter=%u\n",
			r->request_min,
			r->request_max,
			r->request_avg,
			r->request_jitter);

		len += snम_लिखो(&buf[len], buf_len - len,
			" ap-throughput B/s:\tmin=%u max=%u average=%f jitter=%u\n",
			r->throughput_min,
			r->throughput_max,
			r->throughput_avg,
			r->throughput_jitter);
		len += snम_लिखो(&buf[len], buf_len - len,
			" ap-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->latency_min,
			r->latency_max,
			r->latency_avg,
			r->latency_jitter);
		len += snम_लिखो(&buf[len], buf_len - len,
			" apbridge-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->apbridge_unipro_latency_min,
			r->apbridge_unipro_latency_max,
			r->apbridge_unipro_latency_avg,
			r->apbridge_unipro_latency_jitter);

		len += snम_लिखो(&buf[len], buf_len - len,
			" gbphy-latency usec:\tmin=%u max=%u average=%f jitter=%u\n",
			r->gbphy_firmware_latency_min,
			r->gbphy_firmware_latency_max,
			r->gbphy_firmware_latency_avg,
			r->gbphy_firmware_latency_jitter);

	पूर्ण अन्यथा अणु
		len += snम_लिखो(&buf[len], buf_len - len, ",%s,%s,%u,%u,%u",
			t->test_name, dev_name, t->size, t->iteration_max,
			r->error);

		len += snम_लिखो(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->request_min,
			r->request_max,
			r->request_avg,
			r->request_jitter);

		len += snम_लिखो(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->latency_min,
			r->latency_max,
			r->latency_avg,
			r->latency_jitter);

		len += snम_लिखो(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->throughput_min,
			r->throughput_max,
			r->throughput_avg,
			r->throughput_jitter);

		len += snम_लिखो(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->apbridge_unipro_latency_min,
			r->apbridge_unipro_latency_max,
			r->apbridge_unipro_latency_avg,
			r->apbridge_unipro_latency_jitter);

		len += snम_लिखो(&buf[len], buf_len - len, ",%u,%u,%f,%u",
			r->gbphy_firmware_latency_min,
			r->gbphy_firmware_latency_max,
			r->gbphy_firmware_latency_avg,
			r->gbphy_firmware_latency_jitter);
	पूर्ण

	म_लिखो("\n%s\n", buf);

	वापस len;
पूर्ण

अटल पूर्णांक log_results(काष्ठा loopback_test *t)
अणु
	पूर्णांक fd, i, len, ret;
	काष्ठा पंचांग पंचांग;
	समय_प्रकार local_समय;
	अक्षर file_name[MAX_SYSFS_PATH];
	अक्षर data[CSV_MAX_LINE];

	local_समय = समय(शून्य);
	पंचांग = *स_स्थानीय(&local_समय);

	/*
	 * file name will test_name_size_iteration_max.csv
	 * every समय the same test with the same parameters is run we will then
	 * append to the same CSV with datestamp - representing each test
	 * dataset.
	 */
	अगर (t->file_output && !t->porcelain) अणु
		snम_लिखो(file_name, माप(file_name), "%s_%d_%d.csv",
			 t->test_name, t->size, t->iteration_max);

		fd = खोलो(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		अगर (fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "unable to open %s for appendation\n", file_name);
			पात();
		पूर्ण

	पूर्ण
	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		len = क्रमmat_output(t, &t->devices[i].results,
				    t->devices[i].name,
				    data, माप(data), &पंचांग);
		अगर (t->file_output && !t->porcelain) अणु
			ret = ग_लिखो(fd, data, len);
			अगर (ret == -1)
				ख_लिखो(मानक_त्रुटि, "unable to write %d bytes to csv.\n", len);
		पूर्ण

	पूर्ण


	अगर (t->aggregate_output) अणु
		len = क्रमmat_output(t, &t->aggregate_results, "aggregate",
				    data, माप(data), &पंचांग);
		अगर (t->file_output && !t->porcelain) अणु
			ret = ग_लिखो(fd, data, len);
			अगर (ret == -1)
				ख_लिखो(मानक_त्रुटि, "unable to write %d bytes to csv.\n", len);
		पूर्ण
	पूर्ण

	अगर (t->file_output && !t->porcelain)
		बंद(fd);

	वापस 0;
पूर्ण

पूर्णांक is_loopback_device(स्थिर अक्षर *path, स्थिर अक्षर *node)
अणु
	अक्षर file[MAX_SYSFS_PATH];

	snम_लिखो(file, MAX_SYSFS_PATH, "%s%s/iteration_count", path, node);
	अगर (access(file, F_OK) == 0)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक find_loopback_devices(काष्ठा loopback_test *t)
अणु
	काष्ठा dirent **namelist;
	पूर्णांक i, n, ret;
	अचिन्हित पूर्णांक dev_id;
	काष्ठा loopback_device *d;

	n = scandir(t->sysfs_prefix, &namelist, शून्य, alphasort);
	अगर (n < 0) अणु
		लिखो_त्रुटि("scandir");
		ret = -ENODEV;
		जाओ baddir;
	पूर्ण

	/* Don't include '.' and '..' */
	अगर (n <= 2) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		ret = माला_पूछो(namelist[i]->d_name, "gb_loopback%u", &dev_id);
		अगर (ret != 1)
			जारी;

		अगर (!is_loopback_device(t->sysfs_prefix, namelist[i]->d_name))
			जारी;

		अगर (t->device_count == MAX_NUM_DEVICES) अणु
			ख_लिखो(मानक_त्रुटि, "max number of devices reached!\n");
			अवरोध;
		पूर्ण

		d = &t->devices[t->device_count++];
		snम_लिखो(d->name, MAX_STR_LEN, "gb_loopback%u", dev_id);

		snम_लिखो(d->sysfs_entry, MAX_SYSFS_PATH, "%s%s/",
			 t->sysfs_prefix, d->name);

		snम_लिखो(d->debugfs_entry, MAX_SYSFS_PATH, "%sraw_latency_%s",
			 t->debugfs_prefix, d->name);

		अगर (t->debug)
			म_लिखो("add %s %s\n", d->sysfs_entry, d->debugfs_entry);
	पूर्ण

	ret = 0;
करोne:
	क्रम (i = 0; i < n; i++)
		मुक्त(namelist[i]);
	मुक्त(namelist);
baddir:
	वापस ret;
पूर्ण

अटल पूर्णांक खोलो_poll_files(काष्ठा loopback_test *t)
अणु
	काष्ठा loopback_device *dev;
	अक्षर buf[MAX_SYSFS_PATH + MAX_STR_LEN];
	अक्षर dummy;
	पूर्णांक fds_idx = 0;
	पूर्णांक i;

	क्रम (i = 0; i < t->device_count; i++) अणु
		dev = &t->devices[i];

		अगर (!device_enabled(t, i))
			जारी;

		snम_लिखो(buf, माप(buf), "%s%s", dev->sysfs_entry, "iteration_count");
		t->fds[fds_idx].fd = खोलो(buf, O_RDONLY);
		अगर (t->fds[fds_idx].fd < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Error opening poll file!\n");
			जाओ err;
		पूर्ण
		पढ़ो(t->fds[fds_idx].fd, &dummy, 1);
		t->fds[fds_idx].events = POLLERR | POLLPRI;
		t->fds[fds_idx].revents = 0;
		fds_idx++;
	पूर्ण

	t->poll_count = fds_idx;

	वापस 0;

err:
	क्रम (i = 0; i < fds_idx; i++)
		बंद(t->fds[i].fd);

	वापस -1;
पूर्ण

अटल पूर्णांक बंद_poll_files(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < t->poll_count; i++)
		बंद(t->fds[i].fd);

	वापस 0;
पूर्ण
अटल पूर्णांक is_complete(काष्ठा loopback_test *t)
अणु
	पूर्णांक iteration_count;
	पूर्णांक i;

	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		iteration_count = पढ़ो_sysfs_पूर्णांक(t->devices[i].sysfs_entry,
						 "iteration_count");

		/* at least one device did not finish yet */
		अगर (iteration_count != t->iteration_max)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम stop_tests(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;
		ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "type", 0);
	पूर्ण
पूर्ण

अटल व्योम handler(पूर्णांक sig) अणु /* करो nothing */  पूर्ण

अटल पूर्णांक रुको_क्रम_complete(काष्ठा loopback_test *t)
अणु
	पूर्णांक number_of_events = 0;
	अक्षर dummy;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा बारpec *ts = शून्य;
	काष्ठा sigaction sa;
	sigset_t mask_old, mask;

	sigemptyset(&mask);
	sigemptyset(&mask_old);
	sigaddset(&mask, संक_विघ्न);
	sigprocmask(SIG_BLOCK, &mask, &mask_old);

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(संक_विघ्न, &sa, शून्य) == -1) अणु
		ख_लिखो(मानक_त्रुटि, "sigaction error\n");
		वापस -1;
	पूर्ण

	अगर (t->poll_समयout.tv_sec != 0)
		ts = &t->poll_समयout;

	जबतक (1) अणु

		ret = ppoll(t->fds, t->poll_count, ts, &mask_old);
		अगर (ret <= 0) अणु
			stop_tests(t);
			ख_लिखो(मानक_त्रुटि, "Poll exit with errno %d\n", त्रुटि_सं);
			वापस -1;
		पूर्ण

		क्रम (i = 0; i < t->poll_count; i++) अणु
			अगर (t->fds[i].revents & POLLPRI) अणु
				/* Dummy पढ़ो to clear the event */
				पढ़ो(t->fds[i].fd, &dummy, 1);
				number_of_events++;
			पूर्ण
		पूर्ण

		अगर (number_of_events == t->poll_count)
			अवरोध;
	पूर्ण

	अगर (!is_complete(t)) अणु
		ख_लिखो(मानक_त्रुटि, "Iteration count did not finish!\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम prepare_devices(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;

	/*
	 * Cancel any running tests on enabled devices. If
	 * stop_all option is given, stop test on all devices.
	 */
	क्रम (i = 0; i < t->device_count; i++)
		अगर (t->stop_all || device_enabled(t, i))
			ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "type", 0);


	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "us_wait",
				t->us_रुको);

		/* Set operation size */
		ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "size", t->size);

		/* Set iterations */
		ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "iteration_max",
				t->iteration_max);

		अगर (t->use_async) अणु
			ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "async", 1);
			ग_लिखो_sysfs_val(t->devices[i].sysfs_entry,
					"timeout", t->async_समयout);
			ग_लिखो_sysfs_val(t->devices[i].sysfs_entry,
					"outstanding_operations_max",
					t->async_outstanding_operations);
		पूर्ण अन्यथा अणु
			ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "async", 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक start(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;

	/* the test starts by writing test_id to the type file. */
	क्रम (i = 0; i < t->device_count; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		ग_लिखो_sysfs_val(t->devices[i].sysfs_entry, "type", t->test_id);
	पूर्ण

	वापस 0;
पूर्ण


व्योम loopback_run(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; dict[i].name != शून्य; i++) अणु
		अगर (म_माला(dict[i].name, t->test_name))
			t->test_id = dict[i].type;
	पूर्ण
	अगर (!t->test_id) अणु
		ख_लिखो(मानक_त्रुटि, "invalid test %s\n", t->test_name);
		usage();
		वापस;
	पूर्ण

	prepare_devices(t);

	ret = खोलो_poll_files(t);
	अगर (ret)
		जाओ err;

	start(t);

	ret = रुको_क्रम_complete(t);
	बंद_poll_files(t);
	अगर (ret)
		जाओ err;


	get_results(t);

	log_results(t);

	वापस;

err:
	म_लिखो("Error running test\n");
	वापस;
पूर्ण

अटल पूर्णांक sanity_check(काष्ठा loopback_test *t)
अणु
	पूर्णांक i;

	अगर (t->device_count == 0) अणु
		ख_लिखो(मानक_त्रुटि, "No loopback devices found\n");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < MAX_NUM_DEVICES; i++) अणु
		अगर (!device_enabled(t, i))
			जारी;

		अगर (t->mask && !म_भेद(t->devices[i].name, "")) अणु
			ख_लिखो(मानक_त्रुटि, "Bad device mask %x\n", (1 << i));
			वापस -1;
		पूर्ण

	पूर्ण


	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक o, ret;
	अक्षर *sysfs_prefix = "/sys/class/gb_loopback/";
	अक्षर *debugfs_prefix = "/sys/kernel/debug/gb_loopback/";

	स_रखो(&t, 0, माप(t));

	जबतक ((o = getopt(argc, argv,
			   "t:s:i:S:D:m:v::d::r::p::a::l::x::o:O:c:w:z::f::")) != -1) अणु
		चयन (o) अणु
		हाल 't':
			snम_लिखो(t.test_name, MAX_STR_LEN, "%s", optarg);
			अवरोध;
		हाल 's':
			t.size = म_से_प(optarg);
			अवरोध;
		हाल 'i':
			t.iteration_max = म_से_प(optarg);
			अवरोध;
		हाल 'S':
			snम_लिखो(t.sysfs_prefix, MAX_SYSFS_PREFIX, "%s", optarg);
			अवरोध;
		हाल 'D':
			snम_लिखो(t.debugfs_prefix, MAX_SYSFS_PREFIX, "%s", optarg);
			अवरोध;
		हाल 'm':
			t.mask = म_से_द(optarg);
			अवरोध;
		हाल 'v':
			t.verbose = 1;
			अवरोध;
		हाल 'd':
			t.debug = 1;
			अवरोध;
		हाल 'r':
			t.raw_data_dump = 1;
			अवरोध;
		हाल 'p':
			t.porcelain = 1;
			अवरोध;
		हाल 'a':
			t.aggregate_output = 1;
			अवरोध;
		हाल 'l':
			t.list_devices = 1;
			अवरोध;
		हाल 'x':
			t.use_async = 1;
			अवरोध;
		हाल 'o':
			t.async_समयout = म_से_प(optarg);
			अवरोध;
		हाल 'O':
			t.poll_समयout.tv_sec = म_से_प(optarg);
			अवरोध;
		हाल 'c':
			t.async_outstanding_operations = म_से_प(optarg);
			अवरोध;
		हाल 'w':
			t.us_रुको = म_से_प(optarg);
			अवरोध;
		हाल 'z':
			t.file_output = 1;
			अवरोध;
		हाल 'f':
			t.stop_all = 1;
			अवरोध;
		शेष:
			usage();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!म_भेद(t.sysfs_prefix, ""))
		snम_लिखो(t.sysfs_prefix, MAX_SYSFS_PREFIX, "%s", sysfs_prefix);

	अगर (!म_भेद(t.debugfs_prefix, ""))
		snम_लिखो(t.debugfs_prefix, MAX_SYSFS_PREFIX, "%s", debugfs_prefix);

	ret = find_loopback_devices(&t);
	अगर (ret)
		वापस ret;
	ret = sanity_check(&t);
	अगर (ret)
		वापस ret;

	अगर (t.list_devices) अणु
		show_loopback_devices(&t);
		वापस 0;
	पूर्ण

	अगर (t.test_name[0] == '\0' || t.iteration_max == 0)
		usage();

	अगर (t.async_समयout == 0)
		t.async_समयout = DEFAULT_ASYNC_TIMEOUT;

	loopback_run(&t);

	वापस 0;
पूर्ण
