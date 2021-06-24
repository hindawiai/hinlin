<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2018 Google Inc.
 * Author: Eric Dumazet (edumazet@google.com)
 *
 * Reference program demonstrating tcp mmap() usage,
 * and SO_RCVLOWAT hपूर्णांकs क्रम receiver.
 *
 * Note : NIC with header split is needed to use mmap() on TCP :
 * Each incoming frame must be a multiple of PAGE_SIZE bytes of TCP payload.
 *
 * How to use on loopback पूर्णांकerface :
 *
 *  अगरconfig lo mtu 61512  # 15*4096 + 40 (ipv6 header) + 32 (TCP with TS option header)
 *  tcp_mmap -s -z &
 *  tcp_mmap -H ::1 -z
 *
 *  Or leave शेष lo mtu, but use -M option to set TCP_MAXSEG option to (4096 + 12)
 *      (4096 : page size on x86, 12: TCP TS option length)
 *  tcp_mmap -s -z -M $((4096+12)) &
 *  tcp_mmap -H ::1 -z -M $((4096+12))
 *
 * Note: -z option on sender uses MSG_ZEROCOPY, which क्रमces a copy when packets go through loopback पूर्णांकerface.
 *       We might use sendfile() instead, but really this test program is about mmap(), क्रम receivers ;)
 *
 * $ ./tcp_mmap -s &                                 # Without mmap()
 * $ क्रम i in अणु1..4पूर्ण; करो ./tcp_mmap -H ::1 -z ; करोne
 * received 32768 MB (0 % mmap'ed) in 14.1157 s, 19.4732 Gbit
 *   cpu usage user:0.057 sys:7.815, 240.234 usec per MB, 65531 c-चयनes
 * received 32768 MB (0 % mmap'ed) in 14.6833 s, 18.7204 Gbit
 *  cpu usage user:0.043 sys:8.103, 248.596 usec per MB, 65524 c-चयनes
 * received 32768 MB (0 % mmap'ed) in 11.143 s, 24.6682 Gbit
 *   cpu usage user:0.044 sys:6.576, 202.026 usec per MB, 65519 c-चयनes
 * received 32768 MB (0 % mmap'ed) in 14.9056 s, 18.4413 Gbit
 *   cpu usage user:0.036 sys:8.193, 251.129 usec per MB, 65530 c-चयनes
 * $ समाप्त %1   # समाप्त tcp_mmap server
 *
 * $ ./tcp_mmap -s -z &                              # With mmap()
 * $ क्रम i in अणु1..4पूर्ण; करो ./tcp_mmap -H ::1 -z ; करोne
 * received 32768 MB (99.9939 % mmap'ed) in 6.73792 s, 40.7956 Gbit
 *   cpu usage user:0.045 sys:2.827, 87.6465 usec per MB, 65532 c-चयनes
 * received 32768 MB (99.9939 % mmap'ed) in 7.26732 s, 37.8238 Gbit
 *   cpu usage user:0.037 sys:3.087, 95.3369 usec per MB, 65532 c-चयनes
 * received 32768 MB (99.9939 % mmap'ed) in 7.61661 s, 36.0893 Gbit
 *   cpu usage user:0.046 sys:3.559, 110.016 usec per MB, 65529 c-चयनes
 * received 32768 MB (99.9939 % mmap'ed) in 7.43764 s, 36.9577 Gbit
 *   cpu usage user:0.035 sys:3.467, 106.873 usec per MB, 65530 c-चयनes
 */
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <sys/types.h>
#समावेश <fcntl.h>
#समावेश <error.h>
#समावेश <sys/socket.h>
#समावेश <sys/mman.h>
#समावेश <sys/resource.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <netinet/in.h>
#समावेश <arpa/inet.h>
#समावेश <poll.h>
#समावेश <linux/tcp.h>
#समावेश <निश्चित.स>

#अगर_अघोषित MSG_ZEROCOPY
#घोषणा MSG_ZEROCOPY    0x4000000
#पूर्ण_अगर

#घोषणा खाता_SZ (1ULL << 35)
अटल पूर्णांक cfg_family = AF_INET6;
अटल socklen_t cfg_alen = माप(काष्ठा sockaddr_in6);
अटल पूर्णांक cfg_port = 8787;

अटल पूर्णांक rcvbuf; /* Default: स्वतःtuning.  Can be set with -r <पूर्णांकeger> option */
अटल पूर्णांक sndbuf; /* Default: स्वतःtuning.  Can be set with -w <पूर्णांकeger> option */
अटल पूर्णांक zflg; /* zero copy option. (MSG_ZEROCOPY क्रम sender, mmap() क्रम receiver */
अटल पूर्णांक xflg; /* hash received data (simple xor) (-h option) */
अटल पूर्णांक keepflag; /* -k option: receiver shall keep all received file in memory (no munmap() calls) */

अटल माप_प्रकार chunk_size  = 512*1024;

अटल माप_प्रकार map_align;

अचिन्हित दीर्घ htotal;

अटल अंतरभूत व्योम prefetch(स्थिर व्योम *x)
अणु
#अगर defined(__x86_64__)
	यंत्र अस्थिर("prefetcht0 %P0" : : "m" (*(स्थिर अक्षर *)x));
#पूर्ण_अगर
पूर्ण

व्योम hash_zone(व्योम *zone, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित दीर्घ temp = htotal;

	जबतक (length >= 8*माप(दीर्घ)) अणु
		prefetch(zone + 384);
		temp ^= *(अचिन्हित दीर्घ *)zone;
		temp ^= *(अचिन्हित दीर्घ *)(zone + माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 2*माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 3*माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 4*माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 5*माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 6*माप(दीर्घ));
		temp ^= *(अचिन्हित दीर्घ *)(zone + 7*माप(दीर्घ));
		zone += 8*माप(दीर्घ);
		length -= 8*माप(दीर्घ);
	पूर्ण
	जबतक (length >= 1) अणु
		temp ^= *(अचिन्हित अक्षर *)zone;
		zone += 1;
		length--;
	पूर्ण
	htotal = temp;
पूर्ण

#घोषणा ALIGN_UP(x, align_to)	(((x) + ((align_to)-1)) & ~((align_to)-1))
#घोषणा ALIGN_PTR_UP(p, ptr_align_to)	((typeof(p))ALIGN_UP((अचिन्हित दीर्घ)(p), ptr_align_to))


अटल व्योम *mmap_large_buffer(माप_प्रकार need, माप_प्रकार *allocated)
अणु
	व्योम *buffer;
	माप_प्रकार sz;

	/* Attempt to use huge pages अगर possible. */
	sz = ALIGN_UP(need, map_align);
	buffer = mmap(शून्य, sz, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);

	अगर (buffer == (व्योम *)-1) अणु
		sz = need;
		buffer = mmap(शून्य, sz, PROT_READ | PROT_WRITE,
			      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		अगर (buffer != (व्योम *)-1)
			ख_लिखो(मानक_त्रुटि, "MAP_HUGETLB attempt failed, look at /sys/kernel/mm/hugepages for optimal performance\n");
	पूर्ण
	*allocated = sz;
	वापस buffer;
पूर्ण

व्योम *child_thपढ़ो(व्योम *arg)
अणु
	अचिन्हित दीर्घ total_mmap = 0, total = 0;
	काष्ठा tcp_zerocopy_receive zc;
	अचिन्हित दीर्घ delta_usec;
	पूर्णांक flags = MAP_SHARED;
	काष्ठा समयval t0, t1;
	अक्षर *buffer = शून्य;
	व्योम *raddr = शून्य;
	व्योम *addr = शून्य;
	द्विगुन throughput;
	काष्ठा rusage ru;
	माप_प्रकार buffer_sz;
	पूर्णांक lu, fd;

	fd = (पूर्णांक)(अचिन्हित दीर्घ)arg;

	समय_लोofday(&t0, शून्य);

	fcntl(fd, F_SETFL, O_NDELAY);
	buffer = mmap_large_buffer(chunk_size, &buffer_sz);
	अगर (buffer == (व्योम *)-1) अणु
		लिखो_त्रुटि("mmap");
		जाओ error;
	पूर्ण
	अगर (zflg) अणु
		raddr = mmap(शून्य, chunk_size + map_align, PROT_READ, flags, fd, 0);
		अगर (raddr == (व्योम *)-1) अणु
			लिखो_त्रुटि("mmap");
			zflg = 0;
		पूर्ण अन्यथा अणु
			addr = ALIGN_PTR_UP(raddr, map_align);
		पूर्ण
	पूर्ण
	जबतक (1) अणु
		काष्ठा pollfd pfd = अणु .fd = fd, .events = POLLIN, पूर्ण;
		पूर्णांक sub;

		poll(&pfd, 1, 10000);
		अगर (zflg) अणु
			socklen_t zc_len = माप(zc);
			पूर्णांक res;

			स_रखो(&zc, 0, माप(zc));
			zc.address = (__u64)((अचिन्हित दीर्घ)addr);
			zc.length = chunk_size;

			res = माला_लोockopt(fd, IPPROTO_TCP, TCP_ZEROCOPY_RECEIVE,
					 &zc, &zc_len);
			अगर (res == -1)
				अवरोध;

			अगर (zc.length) अणु
				निश्चित(zc.length <= chunk_size);
				total_mmap += zc.length;
				अगर (xflg)
					hash_zone(addr, zc.length);
				/* It is more efficient to unmap the pages right now,
				 * instead of करोing this in next TCP_ZEROCOPY_RECEIVE.
				 */
				madvise(addr, zc.length, MADV_DONTNEED);
				total += zc.length;
			पूर्ण
			अगर (zc.recv_skip_hपूर्णांक) अणु
				निश्चित(zc.recv_skip_hपूर्णांक <= chunk_size);
				lu = पढ़ो(fd, buffer, zc.recv_skip_hपूर्णांक);
				अगर (lu > 0) अणु
					अगर (xflg)
						hash_zone(buffer, lu);
					total += lu;
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण
		sub = 0;
		जबतक (sub < chunk_size) अणु
			lu = पढ़ो(fd, buffer + sub, chunk_size - sub);
			अगर (lu == 0)
				जाओ end;
			अगर (lu < 0)
				अवरोध;
			अगर (xflg)
				hash_zone(buffer + sub, lu);
			total += lu;
			sub += lu;
		पूर्ण
	पूर्ण
end:
	समय_लोofday(&t1, शून्य);
	delta_usec = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;

	throughput = 0;
	अगर (delta_usec)
		throughput = total * 8.0 / (द्विगुन)delta_usec / 1000.0;
	getrusage(RUSAGE_THREAD, &ru);
	अगर (total > 1024*1024) अणु
		अचिन्हित दीर्घ total_usec;
		अचिन्हित दीर्घ mb = total >> 20;
		total_usec = 1000000*ru.ru_uसमय.tv_sec + ru.ru_uसमय.tv_usec +
			     1000000*ru.ru_sसमय.tv_sec + ru.ru_sसमय.tv_usec;
		म_लिखो("received %lg MB (%lg %% mmap'ed) in %lg s, %lg Gbit\n"
		       "  cpu usage user:%lg sys:%lg, %lg usec per MB, %lu c-switches\n",
				total / (1024.0 * 1024.0),
				100.0*total_mmap/total,
				(द्विगुन)delta_usec / 1000000.0,
				throughput,
				(द्विगुन)ru.ru_uसमय.tv_sec + (द्विगुन)ru.ru_uसमय.tv_usec / 1000000.0,
				(द्विगुन)ru.ru_sसमय.tv_sec + (द्विगुन)ru.ru_sसमय.tv_usec / 1000000.0,
				(द्विगुन)total_usec/mb,
				ru.ru_nvcsw);
	पूर्ण
error:
	munmap(buffer, buffer_sz);
	बंद(fd);
	अगर (zflg)
		munmap(raddr, chunk_size + map_align);
	pthपढ़ो_निकास(0);
पूर्ण

अटल व्योम apply_rcvsnd_buf(पूर्णांक fd)
अणु
	अगर (rcvbuf && setsockopt(fd, SOL_SOCKET,
				 SO_RCVBUF, &rcvbuf, माप(rcvbuf)) == -1) अणु
		लिखो_त्रुटि("setsockopt SO_RCVBUF");
	पूर्ण

	अगर (sndbuf && setsockopt(fd, SOL_SOCKET,
				 SO_SNDBUF, &sndbuf, माप(sndbuf)) == -1) अणु
		लिखो_त्रुटि("setsockopt SO_SNDBUF");
	पूर्ण
पूर्ण


अटल व्योम setup_sockaddr(पूर्णांक करोमुख्य, स्थिर अक्षर *str_addr,
			   काष्ठा sockaddr_storage *sockaddr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (व्योम *) sockaddr;
	काष्ठा sockaddr_in *addr4 = (व्योम *) sockaddr;

	चयन (करोमुख्य) अणु
	हाल PF_INET:
		स_रखो(addr4, 0, माप(*addr4));
		addr4->sin_family = AF_INET;
		addr4->sin_port = htons(cfg_port);
		अगर (str_addr &&
		    inet_pton(AF_INET, str_addr, &(addr4->sin_addr)) != 1)
			error(1, 0, "ipv4 parse error: %s", str_addr);
		अवरोध;
	हाल PF_INET6:
		स_रखो(addr6, 0, माप(*addr6));
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = htons(cfg_port);
		अगर (str_addr &&
		    inet_pton(AF_INET6, str_addr, &(addr6->sin6_addr)) != 1)
			error(1, 0, "ipv6 parse error: %s", str_addr);
		अवरोध;
	शेष:
		error(1, 0, "illegal domain");
	पूर्ण
पूर्ण

अटल व्योम करो_accept(पूर्णांक fdlisten)
अणु
	pthपढ़ो_attr_t attr;
	पूर्णांक rcvlowat;

	pthपढ़ो_attr_init(&attr);
	pthपढ़ो_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	rcvlowat = chunk_size;
	अगर (setsockopt(fdlisten, SOL_SOCKET, SO_RCVLOWAT,
		       &rcvlowat, माप(rcvlowat)) == -1) अणु
		लिखो_त्रुटि("setsockopt SO_RCVLOWAT");
	पूर्ण

	apply_rcvsnd_buf(fdlisten);

	जबतक (1) अणु
		काष्ठा sockaddr_in addr;
		socklen_t addrlen = माप(addr);
		pthपढ़ो_t th;
		पूर्णांक fd, res;

		fd = accept(fdlisten, (काष्ठा sockaddr *)&addr, &addrlen);
		अगर (fd == -1) अणु
			लिखो_त्रुटि("accept");
			जारी;
		पूर्ण
		res = pthपढ़ो_create(&th, &attr, child_thपढ़ो,
				     (व्योम *)(अचिन्हित दीर्घ)fd);
		अगर (res) अणु
			त्रुटि_सं = res;
			लिखो_त्रुटि("pthread_create");
			बंद(fd);
		पूर्ण
	पूर्ण
पूर्ण

/* Each thपढ़ो should reserve a big enough vma to aव्योम
 * spinlock collisions in ptl locks.
 * This size is 2MB on x86_64, and is exported in /proc/meminfo.
 */
अटल अचिन्हित दीर्घ शेष_huge_page_size(व्योम)
अणु
	खाता *f = ख_खोलो("/proc/meminfo", "r");
	अचिन्हित दीर्घ hps = 0;
	माप_प्रकार linelen = 0;
	अक्षर *line = शून्य;

	अगर (!f)
		वापस 0;
	जबतक (getline(&line, &linelen, f) > 0) अणु
		अगर (माला_पूछो(line, "Hugepagesize:       %lu kB", &hps) == 1) अणु
			hps <<= 10;
			अवरोध;
		पूर्ण
	पूर्ण
	मुक्त(line);
	ख_बंद(f);
	वापस hps;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा sockaddr_storage listenaddr, addr;
	अचिन्हित पूर्णांक max_pacing_rate = 0;
	uपूर्णांक64_t total = 0;
	अक्षर *host = शून्य;
	पूर्णांक fd, c, on = 1;
	माप_प्रकार buffer_sz;
	अक्षर *buffer;
	पूर्णांक sflg = 0;
	पूर्णांक mss = 0;

	जबतक ((c = getopt(argc, argv, "46p:svr:w:H:zxkP:M:C:a:")) != -1) अणु
		चयन (c) अणु
		हाल '4':
			cfg_family = PF_INET;
			cfg_alen = माप(काष्ठा sockaddr_in);
			अवरोध;
		हाल '6':
			cfg_family = PF_INET6;
			cfg_alen = माप(काष्ठा sockaddr_in6);
			अवरोध;
		हाल 'p':
			cfg_port = म_से_प(optarg);
			अवरोध;
		हाल 'H':
			host = optarg;
			अवरोध;
		हाल 's': /* server : listen क्रम incoming connections */
			sflg++;
			अवरोध;
		हाल 'r':
			rcvbuf = म_से_प(optarg);
			अवरोध;
		हाल 'w':
			sndbuf = म_से_प(optarg);
			अवरोध;
		हाल 'z':
			zflg = 1;
			अवरोध;
		हाल 'M':
			mss = म_से_प(optarg);
			अवरोध;
		हाल 'x':
			xflg = 1;
			अवरोध;
		हाल 'k':
			keepflag = 1;
			अवरोध;
		हाल 'P':
			max_pacing_rate = म_से_प(optarg) ;
			अवरोध;
		हाल 'C':
			chunk_size = म_से_द(optarg);
			अवरोध;
		हाल 'a':
			map_align = म_से_द(optarg);
			अवरोध;
		शेष:
			निकास(1);
		पूर्ण
	पूर्ण
	अगर (!map_align) अणु
		map_align = शेष_huge_page_size();
		/* अगर really /proc/meminfo is not helping,
		 * we use the शेष x86_64 hugepagesize.
		 */
		अगर (!map_align)
			map_align = 2*1024*1024;
	पूर्ण
	अगर (sflg) अणु
		पूर्णांक fdlisten = socket(cfg_family, SOCK_STREAM, 0);

		अगर (fdlisten == -1) अणु
			लिखो_त्रुटि("socket");
			निकास(1);
		पूर्ण
		apply_rcvsnd_buf(fdlisten);
		setsockopt(fdlisten, SOL_SOCKET, SO_REUSEADDR, &on, माप(on));

		setup_sockaddr(cfg_family, host, &listenaddr);

		अगर (mss &&
		    setsockopt(fdlisten, IPPROTO_TCP, TCP_MAXSEG,
			       &mss, माप(mss)) == -1) अणु
			लिखो_त्रुटि("setsockopt TCP_MAXSEG");
			निकास(1);
		पूर्ण
		अगर (bind(fdlisten, (स्थिर काष्ठा sockaddr *)&listenaddr, cfg_alen) == -1) अणु
			लिखो_त्रुटि("bind");
			निकास(1);
		पूर्ण
		अगर (listen(fdlisten, 128) == -1) अणु
			लिखो_त्रुटि("listen");
			निकास(1);
		पूर्ण
		करो_accept(fdlisten);
	पूर्ण

	buffer = mmap_large_buffer(chunk_size, &buffer_sz);
	अगर (buffer == (अक्षर *)-1) अणु
		लिखो_त्रुटि("mmap");
		निकास(1);
	पूर्ण

	fd = socket(cfg_family, SOCK_STREAM, 0);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("socket");
		निकास(1);
	पूर्ण
	apply_rcvsnd_buf(fd);

	setup_sockaddr(cfg_family, host, &addr);

	अगर (mss &&
	    setsockopt(fd, IPPROTO_TCP, TCP_MAXSEG, &mss, माप(mss)) == -1) अणु
		लिखो_त्रुटि("setsockopt TCP_MAXSEG");
		निकास(1);
	पूर्ण
	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)&addr, cfg_alen) == -1) अणु
		लिखो_त्रुटि("connect");
		निकास(1);
	पूर्ण
	अगर (max_pacing_rate &&
	    setsockopt(fd, SOL_SOCKET, SO_MAX_PACING_RATE,
		       &max_pacing_rate, माप(max_pacing_rate)) == -1)
		लिखो_त्रुटि("setsockopt SO_MAX_PACING_RATE");

	अगर (zflg && setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY,
			       &on, माप(on)) == -1) अणु
		लिखो_त्रुटि("setsockopt SO_ZEROCOPY, (-z option disabled)");
		zflg = 0;
	पूर्ण
	जबतक (total < खाता_SZ) अणु
		पूर्णांक64_t wr = खाता_SZ - total;

		अगर (wr > chunk_size)
			wr = chunk_size;
		/* Note : we just want to fill the pipe with 0 bytes */
		wr = send(fd, buffer, (माप_प्रकार)wr, zflg ? MSG_ZEROCOPY : 0);
		अगर (wr <= 0)
			अवरोध;
		total += wr;
	पूर्ण
	बंद(fd);
	munmap(buffer, buffer_sz);
	वापस 0;
पूर्ण
