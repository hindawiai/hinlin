<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * Copyright 2020 IBM Corp.
 *
 * Author: Bulent Abali <abali@us.ibm.com>
 *
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <मानक_निवेशt.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/fcntl.h>
#समावेश <sys/mman.h>
#समावेश <endian.h>
#समावेश <bits/endian.h>
#समावेश <sys/ioctl.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश "vas-api.h"
#समावेश "nx.h"
#समावेश "copy-paste.h"
#समावेश "nxu.h"
#समावेश "nx_dbg.h"
#समावेश <sys/platक्रमm/ppc.h>

#घोषणा barrier()
#घोषणा hwsync()    (अणु यंत्र अस्थिर("sync" ::: "memory"); पूर्ण)

#अगर_अघोषित NX_NO_CPU_PRI
#घोषणा cpu_pri_शेष()  (अणु यंत्र अस्थिर ("or 2, 2, 2"); पूर्ण)
#घोषणा cpu_pri_low()      (अणु यंत्र अस्थिर ("or 31, 31, 31"); पूर्ण)
#अन्यथा
#घोषणा cpu_pri_शेष()
#घोषणा cpu_pri_low()
#पूर्ण_अगर

व्योम *nx_fault_storage_address;

काष्ठा nx_handle अणु
	पूर्णांक fd;
	पूर्णांक function;
	व्योम *paste_addr;
पूर्ण;

अटल पूर्णांक खोलो_device_nodes(अक्षर *devname, पूर्णांक pri, काष्ठा nx_handle *handle)
अणु
	पूर्णांक rc, fd;
	व्योम *addr;
	काष्ठा vas_tx_win_खोलो_attr txattr;

	fd = खोलो(devname, O_RDWR);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, " open device name %s\n", devname);
		वापस -त्रुटि_सं;
	पूर्ण

	स_रखो(&txattr, 0, माप(txattr));
	txattr.version = 1;
	txattr.vas_id = pri;
	rc = ioctl(fd, VAS_TX_WIN_OPEN, (अचिन्हित दीर्घ)&txattr);
	अगर (rc < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ioctl() n %d, error %d\n", rc, त्रुटि_सं);
		rc = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	addr = mmap(शून्य, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0ULL);
	अगर (addr == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "mmap() failed, errno %d\n", त्रुटि_सं);
		rc = -त्रुटि_सं;
		जाओ out;
	पूर्ण
	handle->fd = fd;
	handle->paste_addr = (व्योम *)((अक्षर *)addr + 0x400);

	rc = 0;
out:
	बंद(fd);
	वापस rc;
पूर्ण

व्योम *nx_function_begin(पूर्णांक function, पूर्णांक pri)
अणु
	पूर्णांक rc;
	अक्षर *devname = "/dev/crypto/nx-gzip";
	काष्ठा nx_handle *nxhandle;

	अगर (function != NX_FUNC_COMP_GZIP) अणु
		त्रुटि_सं = EINVAL;
		ख_लिखो(मानक_त्रुटि, " NX_FUNC_COMP_GZIP not found\n");
		वापस शून्य;
	पूर्ण


	nxhandle = दो_स्मृति(माप(*nxhandle));
	अगर (!nxhandle) अणु
		त्रुटि_सं = ENOMEM;
		ख_लिखो(मानक_त्रुटि, " No memory\n");
		वापस शून्य;
	पूर्ण

	nxhandle->function = function;
	rc = खोलो_device_nodes(devname, pri, nxhandle);
	अगर (rc < 0) अणु
		त्रुटि_सं = -rc;
		ख_लिखो(मानक_त्रुटि, " open_device_nodes failed\n");
		वापस शून्य;
	पूर्ण

	वापस nxhandle;
पूर्ण

पूर्णांक nx_function_end(व्योम *handle)
अणु
	पूर्णांक rc = 0;
	काष्ठा nx_handle *nxhandle = handle;

	rc = munmap(nxhandle->paste_addr - 0x400, 4096);
	अगर (rc < 0) अणु
		ख_लिखो(मानक_त्रुटि, "munmap() failed, errno %d\n", त्रुटि_सं);
		वापस rc;
	पूर्ण
	बंद(nxhandle->fd);
	मुक्त(nxhandle);

	वापस rc;
पूर्ण

अटल पूर्णांक nx_रुको_क्रम_csb(काष्ठा nx_gzip_crb_cpb_t *cmdp)
अणु
	दीर्घ poll = 0;
	uपूर्णांक64_t t;

	/* Save घातer and let other thपढ़ोs use the h/w. top may show
	 * 100% but only because OS करोesn't know we slowed the this
	 * h/w thपढ़ो जबतक polling. We're letting other thपढ़ोs have
	 * higher throughput on the core.
	 */
	cpu_pri_low();

#घोषणा CSB_MAX_POLL 200000000UL
#घोषणा USLEEP_TH     300000UL

	t = __ppc_get_समयbase();

	जबतक (getnn(cmdp->crb.csb, csb_v) == 0) अणु
		++poll;
		hwsync();

		cpu_pri_low();

		/* usleep(0) takes around 29000 ticks ~60 us.
		 * 300000 is spinning क्रम about 600 us then
		 * start sleeping.
		 */
		अगर ((__ppc_get_समयbase() - t) > USLEEP_TH) अणु
			cpu_pri_शेष();
			usleep(1);
		पूर्ण

		अगर (poll > CSB_MAX_POLL)
			अवरोध;

		/* Fault address from संकेत handler */
		अगर (nx_fault_storage_address) अणु
			cpu_pri_शेष();
			वापस -EAGAIN;
		पूर्ण

	पूर्ण

	cpu_pri_शेष();

	/* hw has updated csb and output buffer */
	hwsync();

	/* Check CSB flags. */
	अगर (getnn(cmdp->crb.csb, csb_v) == 0) अणु
		ख_लिखो(मानक_त्रुटि, "CSB still not valid after %d polls.\n",
			(पूर्णांक) poll);
		prt_err("CSB still not valid after %d polls, giving up.\n",
			(पूर्णांक) poll);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nxu_run_job(काष्ठा nx_gzip_crb_cpb_t *cmdp, व्योम *handle)
अणु
	पूर्णांक i, ret, retries;
	काष्ठा nx_handle *nxhandle = handle;

	निश्चित(handle != शून्य);
	i = 0;
	retries = 5000;
	जबतक (i++ < retries) अणु
		hwsync();
		vas_copy(&cmdp->crb, 0);
		ret = vas_paste(nxhandle->paste_addr, 0);
		hwsync();

		NXPRT(ख_लिखो(मानक_त्रुटि, "Paste attempt %d/%d returns 0x%x\n",
				i, retries, ret));

		अगर ((ret == 2) || (ret == 3)) अणु

			ret = nx_रुको_क्रम_csb(cmdp);
			अगर (!ret) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
				दीर्घ x;

				prt_err("Touching address %p, 0x%lx\n",
					 nx_fault_storage_address,
					 *(दीर्घ *) nx_fault_storage_address);
				x = *(दीर्घ *) nx_fault_storage_address;
				*(दीर्घ *) nx_fault_storage_address = x;
				nx_fault_storage_address = 0;
				जारी;
			पूर्ण अन्यथा अणु
				prt_err("wait_for_csb() returns %d\n", ret);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (i < 10) अणु
				/* spin क्रम few ticks */
#घोषणा SPIN_TH 500UL
				uपूर्णांक64_t fail_spin;

				fail_spin = __ppc_get_समयbase();
				जबतक ((__ppc_get_समयbase() - fail_spin) <
					 SPIN_TH)
					;
			पूर्ण अन्यथा अणु
				/* sleep */
				अचिन्हित पूर्णांक pr = 0;

				अगर (pr++ % 100 == 0) अणु
					prt_err("Paste attempt %d/", i);
					prt_err("%d, failed pid= %d\n", retries,
						getpid());
				पूर्ण
				usleep(1);
			पूर्ण
			जारी;
		पूर्ण
	पूर्ण

out:
	cpu_pri_शेष();

	वापस ret;
पूर्ण

पूर्णांक nxu_submit_job(काष्ठा nx_gzip_crb_cpb_t *cmdp, व्योम *handle)
अणु
	पूर्णांक cc;

	cc = nxu_run_job(cmdp, handle);

	अगर (!cc)
		cc = getnn(cmdp->crb.csb, csb_cc);      /* CC Table 6-8 */

	वापस cc;
पूर्ण


व्योम nxu_sigsegv_handler(पूर्णांक sig, siginfo_t *info, व्योम *ctx)
अणु
	ख_लिखो(मानक_त्रुटि, "%d: Got signal %d si_code %d, si_addr %p\n", getpid(),
		sig, info->si_code, info->si_addr);

	nx_fault_storage_address = info->si_addr;
पूर्ण

/*
 * Fault in pages prior to NX job submission.  wr=1 may be required to
 * touch ग_लिखोable pages.  System zero pages करो not fault-in the page as
 * पूर्णांकended.  Typically set wr=1 क्रम NX target pages and set wr=0 क्रम NX
 * source pages.
 */
पूर्णांक nxu_touch_pages(व्योम *buf, दीर्घ buf_len, दीर्घ page_len, पूर्णांक wr)
अणु
	अक्षर *begin = buf;
	अक्षर *end = (अक्षर *) buf + buf_len - 1;
	अस्थिर अक्षर t;

	निश्चित(buf_len >= 0 && !!buf);

	NXPRT(ख_लिखो(मानक_त्रुटि, "touch %p %p len 0x%lx wr=%d\n", buf,
			(buf + buf_len), buf_len, wr));

	अगर (buf_len <= 0 || buf == शून्य)
		वापस -1;

	करो अणु
		t = *begin;
		अगर (wr)
			*begin = t;
		begin = begin + page_len;
	पूर्ण जबतक (begin < end);

	/* When buf_sz is small or buf tail is in another page */
	t = *end;
	अगर (wr)
		*end = t;

	वापस 0;
पूर्ण
