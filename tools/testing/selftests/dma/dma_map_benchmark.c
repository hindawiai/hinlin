<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 HiSilicon Limited.
 */

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <linux/types.h>

#घोषणा NSEC_PER_MSEC	1000000L

#घोषणा DMA_MAP_BENCHMARK	_IOWR('d', 1, काष्ठा map_benchmark)
#घोषणा DMA_MAP_MAX_THREADS	1024
#घोषणा DMA_MAP_MAX_SECONDS     300
#घोषणा DMA_MAP_MAX_TRANS_DELAY	(10 * NSEC_PER_MSEC)

#घोषणा DMA_MAP_BIसूचीECTIONAL	0
#घोषणा DMA_MAP_TO_DEVICE	1
#घोषणा DMA_MAP_FROM_DEVICE	2

अटल अक्षर *directions[] = अणु
	"BIDIRECTIONAL",
	"TO_DEVICE",
	"FROM_DEVICE",
पूर्ण;

काष्ठा map_benchmark अणु
	__u64 avg_map_100ns; /* average map latency in 100ns */
	__u64 map_stddev; /* standard deviation of map latency */
	__u64 avg_unmap_100ns; /* as above */
	__u64 unmap_stddev;
	__u32 thपढ़ोs; /* how many thपढ़ोs will करो map/unmap in parallel */
	__u32 seconds; /* how दीर्घ the test will last */
	__s32 node; /* which numa node this benchmark will run on */
	__u32 dma_bits; /* DMA addressing capability */
	__u32 dma_dir; /* DMA data direction */
	__u32 dma_trans_ns; /* समय क्रम DMA transmission in ns */
	__u32 granule; /* how many PAGE_SIZE will करो map/unmap once a समय */
	__u8 expansion[76];	/* For future use */
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा map_benchmark map;
	पूर्णांक fd, opt;
	/* शेष single thपढ़ो, run 20 seconds on NUMA_NO_NODE */
	पूर्णांक thपढ़ोs = 1, seconds = 20, node = -1;
	/* शेष dma mask 32bit, bidirectional DMA */
	पूर्णांक bits = 32, xdelay = 0, dir = DMA_MAP_BIसूचीECTIONAL;
	/* शेष granule 1 PAGESIZE */
	पूर्णांक granule = 1;

	पूर्णांक cmd = DMA_MAP_BENCHMARK;
	अक्षर *p;

	जबतक ((opt = getopt(argc, argv, "t:s:n:b:d:x:g:")) != -1) अणु
		चयन (opt) अणु
		हाल 't':
			thपढ़ोs = म_से_प(optarg);
			अवरोध;
		हाल 's':
			seconds = म_से_प(optarg);
			अवरोध;
		हाल 'n':
			node = म_से_प(optarg);
			अवरोध;
		हाल 'b':
			bits = म_से_प(optarg);
			अवरोध;
		हाल 'd':
			dir = म_से_प(optarg);
			अवरोध;
		हाल 'x':
			xdelay = म_से_प(optarg);
			अवरोध;
		हाल 'g':
			granule = म_से_प(optarg);
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (thपढ़ोs <= 0 || thपढ़ोs > DMA_MAP_MAX_THREADS) अणु
		ख_लिखो(मानक_त्रुटि, "invalid number of threads, must be in 1-%d\n",
			DMA_MAP_MAX_THREADS);
		निकास(1);
	पूर्ण

	अगर (seconds <= 0 || seconds > DMA_MAP_MAX_SECONDS) अणु
		ख_लिखो(मानक_त्रुटि, "invalid number of seconds, must be in 1-%d\n",
			DMA_MAP_MAX_SECONDS);
		निकास(1);
	पूर्ण

	अगर (xdelay < 0 || xdelay > DMA_MAP_MAX_TRANS_DELAY) अणु
		ख_लिखो(मानक_त्रुटि, "invalid transmit delay, must be in 0-%ld\n",
			DMA_MAP_MAX_TRANS_DELAY);
		निकास(1);
	पूर्ण

	/* suppose the mininum DMA zone is 1MB in the world */
	अगर (bits < 20 || bits > 64) अणु
		ख_लिखो(मानक_त्रुटि, "invalid dma mask bit, must be in 20-64\n");
		निकास(1);
	पूर्ण

	अगर (dir != DMA_MAP_BIसूचीECTIONAL && dir != DMA_MAP_TO_DEVICE &&
			dir != DMA_MAP_FROM_DEVICE) अणु
		ख_लिखो(मानक_त्रुटि, "invalid dma direction\n");
		निकास(1);
	पूर्ण

	अगर (granule < 1 || granule > 1024) अणु
		ख_लिखो(मानक_त्रुटि, "invalid granule size\n");
		निकास(1);
	पूर्ण

	fd = खोलो("/sys/kernel/debug/dma_map_benchmark", O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("open");
		निकास(1);
	पूर्ण

	स_रखो(&map, 0, माप(map));
	map.seconds = seconds;
	map.thपढ़ोs = thपढ़ोs;
	map.node = node;
	map.dma_bits = bits;
	map.dma_dir = dir;
	map.dma_trans_ns = xdelay;
	map.granule = granule;

	अगर (ioctl(fd, cmd, &map)) अणु
		लिखो_त्रुटि("ioctl");
		निकास(1);
	पूर्ण

	म_लिखो("dma mapping benchmark: threads:%d seconds:%d node:%d dir:%s granule: %d\n",
			thपढ़ोs, seconds, node, dir[directions], granule);
	म_लिखो("average map latency(us):%.1f standard deviation:%.1f\n",
			map.avg_map_100ns/10.0, map.map_stddev/10.0);
	म_लिखो("average unmap latency(us):%.1f standard deviation:%.1f\n",
			map.avg_unmap_100ns/10.0, map.unmap_stddev/10.0);

	वापस 0;
पूर्ण
