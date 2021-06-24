<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* P9 gunzip sample code क्रम demonstrating the P9 NX hardware
 * पूर्णांकerface.  Not पूर्णांकended क्रम productive uses or क्रम perक्रमmance or
 * compression ratio measurements.  Note also that /dev/crypto/gzip,
 * VAS and skiboot support are required
 *
 * Copyright 2020 IBM Corp.
 *
 * Author: Bulent Abali <abali@us.ibm.com>
 *
 * https://github.com/libnxz/घातer-gzip क्रम zlib api and other utils
 * Definitions of acronyms used here.  See
 * P9 NX Gzip Accelerator User's Manual क्रम details:
 * https://github.com/libnxz/घातer-gzip/blob/develop/करोc/घातer_nx_gzip_um.pdf
 *
 * adler/crc: 32 bit checksums appended to stream tail
 * ce:       completion extension
 * cpb:      coprocessor parameter block (metadata)
 * crb:      coprocessor request block (command)
 * csb:      coprocessor status block (status)
 * dht:      dynamic huffman table
 * dde:      data descriptor element (address, length)
 * ddl:      list of ddes
 * dh/fh:    dynamic and fixed huffman types
 * fc:       coprocessor function code
 * histlen:  history/dictionary length
 * history:  sliding winकरोw of up to 32KB of data
 * lzcount:  Deflate LZ symbol counts
 * rembytecnt: reमुख्यing byte count
 * sfbt:     source final block type; last block's type during decomp
 * spbc:     source processed byte count
 * subc:     source unprocessed bit count
 * tebc:     target ending bit count; valid bits in the last byte
 * tpbc:     target processed byte count
 * vas:      भव accelerator चयन; the user mode पूर्णांकerface
 */

#घोषणा _ISOC11_SOURCE	// For aligned_alloc()
#घोषणा _DEFAULT_SOURCE	// For endian.h

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
#समावेश "nxu.h"
#समावेश "nx.h"
#समावेश "crb.h"

पूर्णांक nx_dbg;
खाता *nx_gzip_log;

#घोषणा NX_MIN(X, Y) (((X) < (Y))?(X):(Y))
#घोषणा NX_MAX(X, Y) (((X) > (Y))?(X):(Y))

#घोषणा GETINPC(X) ख_अक्षर_लो(X)
#घोषणा FNAME_MAX 1024

/* fअगरo queue management */
#घोषणा fअगरo_used_bytes(used) (used)
#घोषणा fअगरo_मुक्त_bytes(used, len) ((len)-(used))
/* amount of मुक्त bytes in the first and last parts */
#घोषणा fअगरo_मुक्त_first_bytes(cur, used, len)  ((((cur)+(used)) <= (len)) \
						  ? (len)-((cur)+(used)) : 0)
#घोषणा fअगरo_मुक्त_last_bytes(cur, used, len)   ((((cur)+(used)) <= (len)) \
						  ? (cur) : (len)-(used))
/* amount of used bytes in the first and last parts */
#घोषणा fअगरo_used_first_bytes(cur, used, len)  ((((cur)+(used)) <= (len)) \
						  ? (used) : (len)-(cur))
#घोषणा fअगरo_used_last_bytes(cur, used, len)   ((((cur)+(used)) <= (len)) \
						  ? 0 : ((used)+(cur))-(len))
/* first and last मुक्त parts start here */
#घोषणा fअगरo_मुक्त_first_offset(cur, used)      ((cur)+(used))
#घोषणा fअगरo_मुक्त_last_offset(cur, used, len)  \
					   fअगरo_used_last_bytes(cur, used, len)
/* first and last used parts start here */
#घोषणा fअगरo_used_first_offset(cur)            (cur)
#घोषणा fअगरo_used_last_offset(cur)             (0)

स्थिर पूर्णांक fअगरo_in_len = 1<<24;
स्थिर पूर्णांक fअगरo_out_len = 1<<24;
स्थिर पूर्णांक page_sz = 1<<16;
स्थिर पूर्णांक line_sz = 1<<7;
स्थिर पूर्णांक winकरोw_max = 1<<15;

/*
 * Adds an (address, len) pair to the list of ddes (ddl) and updates
 * the base dde.  ddl[0] is the only dde in a direct dde which
 * contains a single (addr,len) pair.  For more pairs, ddl[0] becomes
 * the indirect (base) dde that poपूर्णांकs to a list of direct ddes.
 * See Section 6.4 of the NX-gzip user manual क्रम DDE description.
 * Addr=शून्य, len=0 clears the ddl[0].  Returns the total number of
 * bytes in ddl.  Caller is responsible क्रम allocting the array of
 * nx_dde_t *ddl.  If N addresses are required in the scatter-gather
 * list, the ddl array must have N+1 entries minimum.
 */
अटल अंतरभूत uपूर्णांक32_t nx_append_dde(काष्ठा nx_dde_t *ddl, व्योम *addr,
					uपूर्णांक32_t len)
अणु
	uपूर्णांक32_t ddecnt;
	uपूर्णांक32_t bytes;

	अगर (addr == शून्य && len == 0) अणु
		clearp_dde(ddl);
		वापस 0;
	पूर्ण

	NXPRT(ख_लिखो(मानक_त्रुटि, "%d: %s addr %p len %x\n", __LINE__, addr,
			__func__, len));

	/* Number of ddes in the dde list ; == 0 when it is a direct dde */
	ddecnt = getpnn(ddl, dde_count);
	bytes = getp32(ddl, ddebc);

	अगर (ddecnt == 0 && bytes == 0) अणु
		/* First dde is unused; make it a direct dde */
		bytes = len;
		putp32(ddl, ddebc, bytes);
		putp64(ddl, ddead, (uपूर्णांक64_t) addr);
	पूर्ण अन्यथा अगर (ddecnt == 0) अणु
		/* Converting direct to indirect dde
		 * ddl[0] becomes head dde of ddl
		 * copy direct to indirect first.
		 */
		ddl[1] = ddl[0];

		/* Add the new dde next */
		clear_dde(ddl[2]);
		put32(ddl[2], ddebc, len);
		put64(ddl[2], ddead, (uपूर्णांक64_t) addr);

		/* Ddl head poपूर्णांकs to 2 direct ddes */
		ddecnt = 2;
		putpnn(ddl, dde_count, ddecnt);
		bytes = bytes + len;
		putp32(ddl, ddebc, bytes);
		/* Poपूर्णांकer to the first direct dde */
		putp64(ddl, ddead, (uपूर्णांक64_t) &ddl[1]);
	पूर्ण अन्यथा अणु
		/* Append a dde to an existing indirect ddl */
		++ddecnt;
		clear_dde(ddl[ddecnt]);
		put64(ddl[ddecnt], ddead, (uपूर्णांक64_t) addr);
		put32(ddl[ddecnt], ddebc, len);

		putpnn(ddl, dde_count, ddecnt);
		bytes = bytes + len;
		putp32(ddl, ddebc, bytes); /* byte sum of all dde */
	पूर्ण
	वापस bytes;
पूर्ण

/*
 * Touch specअगरied number of pages represented in number bytes
 * beginning from the first buffer in a dde list.
 * Do not touch the pages past buf_sz-th byte's page.
 *
 * Set buf_sz = 0 to touch all pages described by the ddep.
 */
अटल पूर्णांक nx_touch_pages_dde(काष्ठा nx_dde_t *ddep, दीर्घ buf_sz, दीर्घ page_sz,
				पूर्णांक wr)
अणु
	uपूर्णांक32_t indirect_count;
	uपूर्णांक32_t buf_len;
	दीर्घ total;
	uपूर्णांक64_t buf_addr;
	काष्ठा nx_dde_t *dde_list;
	पूर्णांक i;

	निश्चित(!!ddep);

	indirect_count = getpnn(ddep, dde_count);

	NXPRT(ख_लिखो(मानक_त्रुटि, "%s dde_count %d request len ", __func__,
			indirect_count));
	NXPRT(ख_लिखो(मानक_त्रुटि, "0x%lx\n", buf_sz));

	अगर (indirect_count == 0) अणु
		/* Direct dde */
		buf_len = getp32(ddep, ddebc);
		buf_addr = getp64(ddep, ddead);

		NXPRT(ख_लिखो(मानक_त्रुटि, "touch direct ddebc 0x%x ddead %p\n",
				buf_len, (व्योम *)buf_addr));

		अगर (buf_sz == 0)
			nxu_touch_pages((व्योम *)buf_addr, buf_len, page_sz, wr);
		अन्यथा
			nxu_touch_pages((व्योम *)buf_addr, NX_MIN(buf_len,
					buf_sz), page_sz, wr);

		वापस ERR_NX_OK;
	पूर्ण

	/* Indirect dde */
	अगर (indirect_count > MAX_DDE_COUNT)
		वापस ERR_NX_EXCESSIVE_DDE;

	/* First address of the list */
	dde_list = (काष्ठा nx_dde_t *) getp64(ddep, ddead);

	अगर (buf_sz == 0)
		buf_sz = getp32(ddep, ddebc);

	total = 0;
	क्रम (i = 0; i < indirect_count; i++) अणु
		buf_len = get32(dde_list[i], ddebc);
		buf_addr = get64(dde_list[i], ddead);
		total += buf_len;

		NXPRT(ख_लिखो(मानक_त्रुटि, "touch loop len 0x%x ddead %p total ",
				buf_len, (व्योम *)buf_addr));
		NXPRT(ख_लिखो(मानक_त्रुटि, "0x%lx\n", total));

		/* Touching fewer pages than encoded in the ddebc */
		अगर (total > buf_sz) अणु
			buf_len = NX_MIN(buf_len, total - buf_sz);
			nxu_touch_pages((व्योम *)buf_addr, buf_len, page_sz, wr);
			NXPRT(ख_लिखो(मानक_त्रुटि, "touch loop break len 0x%x ",
				      buf_len));
			NXPRT(ख_लिखो(मानक_त्रुटि, "ddead %p\n", (व्योम *)buf_addr));
			अवरोध;
		पूर्ण
		nxu_touch_pages((व्योम *)buf_addr, buf_len, page_sz, wr);
	पूर्ण
	वापस ERR_NX_OK;
पूर्ण

/*
 * Src and dst buffers are supplied in scatter gather lists.
 * NX function code and other parameters supplied in cmdp.
 */
अटल पूर्णांक nx_submit_job(काष्ठा nx_dde_t *src, काष्ठा nx_dde_t *dst,
			 काष्ठा nx_gzip_crb_cpb_t *cmdp, व्योम *handle)
अणु
	uपूर्णांक64_t csbaddr;

	स_रखो((व्योम *)&cmdp->crb.csb, 0, माप(cmdp->crb.csb));

	cmdp->crb.source_dde = *src;
	cmdp->crb.target_dde = *dst;

	/* Status, output byte count in tpbc */
	csbaddr = ((uपूर्णांक64_t) &cmdp->crb.csb) & csb_address_mask;
	put64(cmdp->crb, csb_address, csbaddr);

	/* NX reports input bytes in spbc; cleared */
	cmdp->cpb.out_spbc_comp_wrap = 0;
	cmdp->cpb.out_spbc_comp_with_count = 0;
	cmdp->cpb.out_spbc_decomp = 0;

	/* Clear output */
	put32(cmdp->cpb, out_crc, INIT_CRC);
	put32(cmdp->cpb, out_adler, INIT_ADLER);

	/* Submit the crb, the job descriptor, to the accelerator. */
	वापस nxu_submit_job(cmdp, handle);
पूर्ण

पूर्णांक decompress_file(पूर्णांक argc, अक्षर **argv, व्योम *devhandle)
अणु
	खाता *inpf = शून्य;
	खाता *outf = शून्य;

	पूर्णांक c, expect, i, cc, rc = 0;
	अक्षर gzfname[FNAME_MAX];

	/* Queuing, file ops, byte counting */
	अक्षर *fअगरo_in, *fअगरo_out;
	पूर्णांक used_in, cur_in, used_out, cur_out, पढ़ो_sz, n;
	पूर्णांक first_मुक्त, last_मुक्त, first_used, last_used;
	पूर्णांक first_offset, last_offset;
	पूर्णांक ग_लिखो_sz, मुक्त_space, source_sz;
	पूर्णांक source_sz_estimate, target_sz_estimate;
	uपूर्णांक64_t last_comp_ratio = 0; /* 1000 max */
	uपूर्णांक64_t total_out = 0;
	पूर्णांक is_final, is_eof;

	/* nx hardware */
	पूर्णांक sfbt, subc, spbc, tpbc, nx_ce, fc, resuming = 0;
	पूर्णांक history_len = 0;
	काष्ठा nx_gzip_crb_cpb_t cmd, *cmdp;
	काष्ठा nx_dde_t *ddl_in;
	काष्ठा nx_dde_t dde_in[6] __aligned(128);
	काष्ठा nx_dde_t *ddl_out;
	काष्ठा nx_dde_t dde_out[6] __aligned(128);
	पूर्णांक pgfault_retries;

	/* when using mmap'ed files */
	off_t input_file_offset;

	अगर (argc > 2) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s <fname> or stdin\n", argv[0]);
		ख_लिखो(मानक_त्रुटि, "    writes to stdout or <fname>.nx.gunzip\n");
		वापस -1;
	पूर्ण

	अगर (argc == 1) अणु
		inpf = मानक_निवेश;
		outf = मानक_निकास;
	पूर्ण अन्यथा अगर (argc == 2) अणु
		अक्षर w[1024];
		अक्षर *wp;

		inpf = ख_खोलो(argv[1], "r");
		अगर (inpf == शून्य) अणु
			लिखो_त्रुटि(argv[1]);
			वापस -1;
		पूर्ण

		/* Make a new file name to ग_लिखो to.  Ignoring '.gz' */
		wp = (शून्य != (wp = म_खोजप(argv[1], '/'))) ? (wp+1) : argv[1];
		म_नकल(w, wp);
		म_जोड़ो(w, ".nx.gunzip");

		outf = ख_खोलो(w, "w");
		अगर (outf == शून्य) अणु
			लिखो_त्रुटि(w);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Decode the gzip header */
	c = GETINPC(inpf); expect = 0x1f; /* ID1 */
	अगर (c != expect)
		जाओ err1;

	c = GETINPC(inpf); expect = 0x8b; /* ID2 */
	अगर (c != expect)
		जाओ err1;

	c = GETINPC(inpf); expect = 0x08; /* CM */
	अगर (c != expect)
		जाओ err1;

	पूर्णांक flg = GETINPC(inpf); /* FLG */

	अगर (flg & 0xE0 || flg & 0x4 || flg == खातापूर्ण)
		जाओ err2;

	ख_लिखो(मानक_त्रुटि, "gzHeader FLG %x\n", flg);

	/* Read 6 bytes; ignoring the MTIME, XFL, OS fields in this
	 * sample code.
	 */
	क्रम (i = 0; i < 6; i++) अणु
		अक्षर पंचांगp[10];

		पंचांगp[i] = GETINPC(inpf);
		अगर (पंचांगp[i] == खातापूर्ण)
			जाओ err3;
		ख_लिखो(मानक_त्रुटि, "%02x ", पंचांगp[i]);
		अगर (i == 5)
			ख_लिखो(मानक_त्रुटि, "\n");
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "gzHeader MTIME, XFL, OS ignored\n");

	/* FNAME */
	अगर (flg & 0x8) अणु
		पूर्णांक k = 0;

		करो अणु
			c = GETINPC(inpf);
			अगर (c == खातापूर्ण || k >= FNAME_MAX)
				जाओ err3;
			gzfname[k++] = c;
		पूर्ण जबतक (c);
		ख_लिखो(मानक_त्रुटि, "gzHeader FNAME: %s\n", gzfname);
	पूर्ण

	/* FHCRC */
	अगर (flg & 0x2) अणु
		c = GETINPC(inpf);
		अगर (c == खातापूर्ण)
			जाओ err3;
		c = GETINPC(inpf);
		अगर (c == खातापूर्ण)
			जाओ err3;
		ख_लिखो(मानक_त्रुटि, "gzHeader FHCRC: ignored\n");
	पूर्ण

	used_in = cur_in = used_out = cur_out = 0;
	is_final = is_eof = 0;

	/* Allocate one page larger to prevent page faults due to NX
	 * overfetching.
	 * Either करो this (अक्षर*)(uपूर्णांकptr_t)aligned_alloc or use
	 * -std=c11 flag to make the पूर्णांक-to-poपूर्णांकer warning go away.
	 */
	निश्चित((fअगरo_in  = (अक्षर *)(uपूर्णांकptr_t)aligned_alloc(line_sz,
				   fअगरo_in_len + page_sz)) != शून्य);
	निश्चित((fअगरo_out = (अक्षर *)(uपूर्णांकptr_t)aligned_alloc(line_sz,
				   fअगरo_out_len + page_sz + line_sz)) != शून्य);
	/* Leave unused space due to history rounding rules */
	fअगरo_out = fअगरo_out + line_sz;
	nxu_touch_pages(fअगरo_out, fअगरo_out_len, page_sz, 1);

	ddl_in  = &dde_in[0];
	ddl_out = &dde_out[0];
	cmdp = &cmd;
	स_रखो(&cmdp->crb, 0, माप(cmdp->crb));

पढ़ो_state:

	/* Read from .gz file */

	NXPRT(ख_लिखो(मानक_त्रुटि, "read_state:\n"));

	अगर (is_eof != 0)
		जाओ ग_लिखो_state;

	/* We पढ़ो in to fअगरo_in in two steps: first: पढ़ो in to from
	 * cur_in to the end of the buffer.  last: अगर मुक्त space wrapped
	 * around, पढ़ो from fअगरo_in offset 0 to offset cur_in.
	 */

	/* Reset fअगरo head to reduce unnecessary wrap arounds */
	cur_in = (used_in == 0) ? 0 : cur_in;

	/* Free space total is reduced by a gap */
	मुक्त_space = NX_MAX(0, fअगरo_मुक्त_bytes(used_in, fअगरo_in_len)
			    - line_sz);

	/* Free space may wrap around as first and last */
	first_मुक्त = fअगरo_मुक्त_first_bytes(cur_in, used_in, fअगरo_in_len);
	last_मुक्त  = fअगरo_मुक्त_last_bytes(cur_in, used_in, fअगरo_in_len);

	/* Start offsets of the मुक्त memory */
	first_offset = fअगरo_मुक्त_first_offset(cur_in, used_in);
	last_offset  = fअगरo_मुक्त_last_offset(cur_in, used_in, fअगरo_in_len);

	/* Reduce पढ़ो_sz because of the line_sz gap */
	पढ़ो_sz = NX_MIN(मुक्त_space, first_मुक्त);
	n = 0;
	अगर (पढ़ो_sz > 0) अणु
		/* Read in to offset cur_in + used_in */
		n = ख_पढ़ो(fअगरo_in + first_offset, 1, पढ़ो_sz, inpf);
		used_in = used_in + n;
		मुक्त_space = मुक्त_space - n;
		निश्चित(n <= पढ़ो_sz);
		अगर (n != पढ़ो_sz) अणु
			/* Either खातापूर्ण or error; निकास the पढ़ो loop */
			is_eof = 1;
			जाओ ग_लिखो_state;
		पूर्ण
	पूर्ण

	/* If मुक्त space wrapped around */
	अगर (last_मुक्त > 0) अणु
		/* Reduce पढ़ो_sz because of the line_sz gap */
		पढ़ो_sz = NX_MIN(मुक्त_space, last_मुक्त);
		n = 0;
		अगर (पढ़ो_sz > 0) अणु
			n = ख_पढ़ो(fअगरo_in + last_offset, 1, पढ़ो_sz, inpf);
			used_in = used_in + n;       /* Increase used space */
			मुक्त_space = मुक्त_space - n; /* Decrease मुक्त space */
			निश्चित(n <= पढ़ो_sz);
			अगर (n != पढ़ो_sz) अणु
				/* Either खातापूर्ण or error; निकास the पढ़ो loop */
				is_eof = 1;
				जाओ ग_लिखो_state;
			पूर्ण
		पूर्ण
	पूर्ण

	/* At this poपूर्णांक we have used_in bytes in fअगरo_in with the
	 * data head starting at cur_in and possibly wrapping around.
	 */

ग_लिखो_state:

	/* Write decompressed data to output file */

	NXPRT(ख_लिखो(मानक_त्रुटि, "write_state:\n"));

	अगर (used_out == 0)
		जाओ decomp_state;

	/* If fअगरo_out has data रुकोing, ग_लिखो it out to the file to
	 * make मुक्त target space क्रम the accelerator used bytes in
	 * the first and last parts of fअगरo_out.
	 */

	first_used = fअगरo_used_first_bytes(cur_out, used_out, fअगरo_out_len);
	last_used  = fअगरo_used_last_bytes(cur_out, used_out, fअगरo_out_len);

	ग_लिखो_sz = first_used;

	n = 0;
	अगर (ग_लिखो_sz > 0) अणु
		n = ख_डालो(fअगरo_out + cur_out, 1, ग_लिखो_sz, outf);
		used_out = used_out - n;
		/* Move head of the fअगरo */
		cur_out = (cur_out + n) % fअगरo_out_len;
		निश्चित(n <= ग_लिखो_sz);
		अगर (n != ग_लिखो_sz) अणु
			ख_लिखो(मानक_त्रुटि, "error: write\n");
			rc = -1;
			जाओ err5;
		पूर्ण
	पूर्ण

	अगर (last_used > 0) अणु /* If more data available in the last part */
		ग_लिखो_sz = last_used; /* Keep it here क्रम later */
		n = 0;
		अगर (ग_लिखो_sz > 0) अणु
			n = ख_डालो(fअगरo_out, 1, ग_लिखो_sz, outf);
			used_out = used_out - n;
			cur_out = (cur_out + n) % fअगरo_out_len;
			निश्चित(n <= ग_लिखो_sz);
			अगर (n != ग_लिखो_sz) अणु
				ख_लिखो(मानक_त्रुटि, "error: write\n");
				rc = -1;
				जाओ err5;
			पूर्ण
		पूर्ण
	पूर्ण

decomp_state:

	/* NX decompresses input data */

	NXPRT(ख_लिखो(मानक_त्रुटि, "decomp_state:\n"));

	अगर (is_final)
		जाओ finish_state;

	/* Address/len lists */
	clearp_dde(ddl_in);
	clearp_dde(ddl_out);

	/* FC, CRC, HistLen, Table 6-6 */
	अगर (resuming) अणु
		/* Resuming a partially decompressed input.
		 * The key to resume is supplying the 32KB
		 * dictionary (history) to NX, which is basically
		 * the last 32KB of output produced.
		 */
		fc = GZIP_FC_DECOMPRESS_RESUME;

		cmdp->cpb.in_crc   = cmdp->cpb.out_crc;
		cmdp->cpb.in_adler = cmdp->cpb.out_adler;

		/* Round up the history size to quadword.  Section 2.10 */
		history_len = (history_len + 15) / 16;
		putnn(cmdp->cpb, in_histlen, history_len);
		history_len = history_len * 16; /* bytes */

		अगर (history_len > 0) अणु
			/* Chain in the history buffer to the DDE list */
			अगर (cur_out >= history_len) अणु
				nx_append_dde(ddl_in, fअगरo_out
					      + (cur_out - history_len),
					      history_len);
			पूर्ण अन्यथा अणु
				nx_append_dde(ddl_in, fअगरo_out
					      + ((fअगरo_out_len + cur_out)
					      - history_len),
					      history_len - cur_out);
				/* Up to 32KB history wraps around fअगरo_out */
				nx_append_dde(ddl_in, fअगरo_out, cur_out);
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अणु
		/* First decompress job */
		fc = GZIP_FC_DECOMPRESS;

		history_len = 0;
		/* Writing 0 clears out subc as well */
		cmdp->cpb.in_histlen = 0;
		total_out = 0;

		put32(cmdp->cpb, in_crc, INIT_CRC);
		put32(cmdp->cpb, in_adler, INIT_ADLER);
		put32(cmdp->cpb, out_crc, INIT_CRC);
		put32(cmdp->cpb, out_adler, INIT_ADLER);

		/* Assuming 10% compression ratio initially; use the
		 * most recently measured compression ratio as a
		 * heuristic to estimate the input and output
		 * sizes.  If we give too much input, the target buffer
		 * overflows and NX cycles are wasted, and then we
		 * must retry with smaller input size.  1000 is 100%.
		 */
		last_comp_ratio = 100UL;
	पूर्ण
	cmdp->crb.gzip_fc = 0;
	putnn(cmdp->crb, gzip_fc, fc);

	/*
	 * NX source buffers
	 */
	first_used = fअगरo_used_first_bytes(cur_in, used_in, fअगरo_in_len);
	last_used = fअगरo_used_last_bytes(cur_in, used_in, fअगरo_in_len);

	अगर (first_used > 0)
		nx_append_dde(ddl_in, fअगरo_in + cur_in, first_used);

	अगर (last_used > 0)
		nx_append_dde(ddl_in, fअगरo_in, last_used);

	/*
	 * NX target buffers
	 */
	first_मुक्त = fअगरo_मुक्त_first_bytes(cur_out, used_out, fअगरo_out_len);
	last_मुक्त = fअगरo_मुक्त_last_bytes(cur_out, used_out, fअगरo_out_len);

	/* Reduce output मुक्त space amount not to overग_लिखो the history */
	पूर्णांक target_max = NX_MAX(0, fअगरo_मुक्त_bytes(used_out, fअगरo_out_len)
				- (1<<16));

	NXPRT(ख_लिखो(मानक_त्रुटि, "target_max %d (0x%x)\n", target_max,
		      target_max));

	first_मुक्त = NX_MIN(target_max, first_मुक्त);
	अगर (first_मुक्त > 0) अणु
		first_offset = fअगरo_मुक्त_first_offset(cur_out, used_out);
		nx_append_dde(ddl_out, fअगरo_out + first_offset, first_मुक्त);
	पूर्ण

	अगर (last_मुक्त > 0) अणु
		last_मुक्त = NX_MIN(target_max - first_मुक्त, last_मुक्त);
		अगर (last_मुक्त > 0) अणु
			last_offset = fअगरo_मुक्त_last_offset(cur_out, used_out,
							    fअगरo_out_len);
			nx_append_dde(ddl_out, fअगरo_out + last_offset,
				      last_मुक्त);
		पूर्ण
	पूर्ण

	/* Target buffer size is used to limit the source data size
	 * based on previous measurements of compression ratio.
	 */

	/* source_sz includes history */
	source_sz = getp32(ddl_in, ddebc);
	निश्चित(source_sz > history_len);
	source_sz = source_sz - history_len;

	/* Estimating how much source is needed to 3/4 fill a
	 * target_max size target buffer.  If we overshoot, then NX
	 * must repeat the job with smaller input and we waste
	 * bandwidth.  If we undershoot then we use more NX calls than
	 * necessary.
	 */

	source_sz_estimate = ((uपूर्णांक64_t)target_max * last_comp_ratio * 3UL)
				/ 4000;

	अगर (source_sz_estimate < source_sz) अणु
		/* Target might be small, thereक्रमe limiting the
		 * source data.
		 */
		source_sz = source_sz_estimate;
		target_sz_estimate = target_max;
	पूर्ण अन्यथा अणु
		/* Source file might be small, thereक्रमe limiting target
		 * touch pages to a smaller value to save processor cycles.
		 */
		target_sz_estimate = ((uपूर्णांक64_t)source_sz * 1000UL)
					/ (last_comp_ratio + 1);
		target_sz_estimate = NX_MIN(2 * target_sz_estimate,
					    target_max);
	पूर्ण

	source_sz = source_sz + history_len;

	/* Some NX condition codes require submitting the NX job again.
	 * Kernel करोesn't handle NX page faults. Expects user code to
	 * touch pages.
	 */
	pgfault_retries = NX_MAX_FAULTS;

restart_nx:

	putp32(ddl_in, ddebc, source_sz);

	/* Fault in pages */
	nxu_touch_pages(cmdp, माप(काष्ठा nx_gzip_crb_cpb_t), page_sz, 1);
	nx_touch_pages_dde(ddl_in, 0, page_sz, 0);
	nx_touch_pages_dde(ddl_out, target_sz_estimate, page_sz, 1);

	/* Send job to NX */
	cc = nx_submit_job(ddl_in, ddl_out, cmdp, devhandle);

	चयन (cc) अणु

	हाल ERR_NX_AT_FAULT:

		/* We touched the pages ahead of समय.  In the most common हाल
		 * we shouldn't be here.  But may be some pages were paged out.
		 * Kernel should have placed the faulting address to fsaddr.
		 */
		NXPRT(ख_लिखो(मानक_त्रुटि, "ERR_NX_AT_FAULT %p\n",
			      (व्योम *)cmdp->crb.csb.fsaddr));

		अगर (pgfault_retries == NX_MAX_FAULTS) अणु
			/* Try once with exact number of pages */
			--pgfault_retries;
			जाओ restart_nx;
		पूर्ण अन्यथा अगर (pgfault_retries > 0) अणु
			/* If still faulting try fewer input pages
			 * assuming memory outage
			 */
			अगर (source_sz > page_sz)
				source_sz = NX_MAX(source_sz / 2, page_sz);
			--pgfault_retries;
			जाओ restart_nx;
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "cannot make progress; too many ");
			ख_लिखो(मानक_त्रुटि, "page fault retries cc= %d\n", cc);
			rc = -1;
			जाओ err5;
		पूर्ण

	हाल ERR_NX_DATA_LENGTH:

		NXPRT(ख_लिखो(मानक_त्रुटि, "ERR_NX_DATA_LENGTH; "));
		NXPRT(ख_लिखो(मानक_त्रुटि, "stream may have trailing data\n"));

		/* Not an error in the most common हाल; it just says
		 * there is trailing data that we must examine.
		 *
		 * CC=3 CE(1)=0 CE(0)=1 indicates partial completion
		 * Fig.6-7 and Table 6-8.
		 */
		nx_ce = get_csb_ce_ms3b(cmdp->crb.csb);

		अगर (!csb_ce_termination(nx_ce) &&
		    csb_ce_partial_completion(nx_ce)) अणु
			/* Check CPB क्रम more inक्रमmation
			 * spbc and tpbc are valid
			 */
			sfbt = getnn(cmdp->cpb, out_sfbt); /* Table 6-4 */
			subc = getnn(cmdp->cpb, out_subc); /* Table 6-4 */
			spbc = get32(cmdp->cpb, out_spbc_decomp);
			tpbc = get32(cmdp->crb.csb, tpbc);
			निश्चित(target_max >= tpbc);

			जाओ ok_cc3; /* not an error */
		पूर्ण अन्यथा अणु
			/* History length error when CE(1)=1 CE(0)=0. */
			rc = -1;
			ख_लिखो(मानक_त्रुटि, "history length error cc= %d\n", cc);
			जाओ err5;
		पूर्ण

	हाल ERR_NX_TARGET_SPACE:

		/* Target buffer not large enough; retry smaller input
		 * data; give at least 1 byte.  SPBC/TPBC are not valid.
		 */
		निश्चित(source_sz > history_len);
		source_sz = ((source_sz - history_len + 2) / 2) + history_len;
		NXPRT(ख_लिखो(मानक_त्रुटि, "ERR_NX_TARGET_SPACE; retry with "));
		NXPRT(ख_लिखो(मानक_त्रुटि, "smaller input data src %d hist %d\n",
			      source_sz, history_len));
		जाओ restart_nx;

	हाल ERR_NX_OK:

		/* This should not happen क्रम gzip क्रमmatted data;
		 * we need trailing crc and isize
		 */
		ख_लिखो(मानक_त्रुटि, "ERR_NX_OK\n");
		spbc = get32(cmdp->cpb, out_spbc_decomp);
		tpbc = get32(cmdp->crb.csb, tpbc);
		निश्चित(target_max >= tpbc);
		निश्चित(spbc >= history_len);
		source_sz = spbc - history_len;
		जाओ offsets_state;

	शेष:
		ख_लिखो(मानक_त्रुटि, "error: cc= %d\n", cc);
		rc = -1;
		जाओ err5;
	पूर्ण

ok_cc3:

	NXPRT(ख_लिखो(मानक_त्रुटि, "cc3: sfbt: %x\n", sfbt));

	निश्चित(spbc > history_len);
	source_sz = spbc - history_len;

	/* Table 6-4: Source Final Block Type (SFBT) describes the
	 * last processed deflate block and clues the software how to
	 * resume the next job.  SUBC indicates how many input bits NX
	 * consumed but did not process.  SPBC indicates how many
	 * bytes of source were given to the accelerator including
	 * history bytes.
	 */

	चयन (sfbt) अणु
		पूर्णांक dhtlen;

	हाल 0x0: /* Deflate final EOB received */

		/* Calculating the checksum start position. */

		source_sz = source_sz - subc / 8;
		is_final = 1;
		अवरोध;

		/* Resume decompression हालs are below. Basically
		 * indicates where NX has suspended and how to resume
		 * the input stream.
		 */

	हाल 0x8: /* Within a literal block; use rembytecount */
	हाल 0x9: /* Within a literal block; use rembytecount; bfinal=1 */

		/* Supply the partially processed source byte again */
		source_sz = source_sz - ((subc + 7) / 8);

		/* SUBC LS 3bits: number of bits in the first source byte need
		 * to be processed.
		 * 000 means all 8 bits;  Table 6-3
		 * Clear subc, histlen, sfbt, rembytecnt, dhtlen
		 */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);
		putnn(cmdp->cpb, in_rembytecnt, getnn(cmdp->cpb,
						      out_rembytecnt));
		अवरोध;

	हाल 0xA: /* Within a FH block; */
	हाल 0xB: /* Within a FH block; bfinal=1 */

		source_sz = source_sz - ((subc + 7) / 8);

		/* Clear subc, histlen, sfbt, rembytecnt, dhtlen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);
		अवरोध;

	हाल 0xC: /* Within a DH block; */
	हाल 0xD: /* Within a DH block; bfinal=1 */

		source_sz = source_sz - ((subc + 7) / 8);

		/* Clear subc, histlen, sfbt, rembytecnt, dhtlen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);

		dhtlen = getnn(cmdp->cpb, out_dhtlen);
		putnn(cmdp->cpb, in_dhtlen, dhtlen);
		निश्चित(dhtlen >= 42);

		/* Round up to a qword */
		dhtlen = (dhtlen + 127) / 128;

		जबतक (dhtlen > 0) अणु /* Copy dht from cpb.out to cpb.in */
			--dhtlen;
			cmdp->cpb.in_dht[dhtlen] = cmdp->cpb.out_dht[dhtlen];
		पूर्ण
		अवरोध;

	हाल 0xE: /* Within a block header; bfinal=0; */
		     /* Also given अगर source data exactly ends (SUBC=0) with
		      * EOB code with BFINAL=0.  Means the next byte will
		      * contain a block header.
		      */
	हाल 0xF: /* within a block header with BFINAL=1. */

		source_sz = source_sz - ((subc + 7) / 8);

		/* Clear subc, histlen, sfbt, rembytecnt, dhtlen */
		cmdp->cpb.in_subc = 0;
		cmdp->cpb.in_sfbt = 0;
		putnn(cmdp->cpb, in_subc, subc % 8);
		putnn(cmdp->cpb, in_sfbt, sfbt);

		/* Engine did not process any data */
		अगर (is_eof && (source_sz == 0))
			is_final = 1;
	पूर्ण

offsets_state:

	/* Adjust the source and target buffer offsets and lengths  */

	NXPRT(ख_लिखो(मानक_त्रुटि, "offsets_state:\n"));

	/* Delete input data from fअगरo_in */
	used_in = used_in - source_sz;
	cur_in = (cur_in + source_sz) % fअगरo_in_len;
	input_file_offset = input_file_offset + source_sz;

	/* Add output data to fअगरo_out */
	used_out = used_out + tpbc;

	निश्चित(used_out <= fअगरo_out_len);

	total_out = total_out + tpbc;

	/* Deflate history is 32KB max.  No need to supply more
	 * than 32KB on a resume.
	 */
	history_len = (total_out > winकरोw_max) ? winकरोw_max : total_out;

	/* To estimate expected expansion in the next NX job; 500 means 50%.
	 * Deflate best हाल is around 1 to 1000.
	 */
	last_comp_ratio = (1000UL * ((uपूर्णांक64_t)source_sz + 1))
			  / ((uपूर्णांक64_t)tpbc + 1);
	last_comp_ratio = NX_MAX(NX_MIN(1000UL, last_comp_ratio), 1);
	NXPRT(ख_लिखो(मानक_त्रुटि, "comp_ratio %ld source_sz %d spbc %d tpbc %d\n",
		      last_comp_ratio, source_sz, spbc, tpbc));

	resuming = 1;

finish_state:

	NXPRT(ख_लिखो(मानक_त्रुटि, "finish_state:\n"));

	अगर (is_final) अणु
		अगर (used_out)
			जाओ ग_लिखो_state; /* More data to ग_लिखो out */
		अन्यथा अगर (used_in < 8) अणु
			/* Need at least 8 more bytes containing gzip crc
			 * and isize.
			 */
			rc = -1;
			जाओ err4;
		पूर्ण अन्यथा अणु
			/* Compare checksums and निकास */
			पूर्णांक i;
			अचिन्हित अक्षर tail[8];
			uपूर्णांक32_t cksum, isize;

			क्रम (i = 0; i < 8; i++)
				tail[i] = fअगरo_in[(cur_in + i) % fअगरo_in_len];
			ख_लिखो(मानक_त्रुटि, "computed checksum %08x isize %08x\n",
				cmdp->cpb.out_crc, (uपूर्णांक32_t) (total_out
				% (1ULL<<32)));
			cksum = ((uपूर्णांक32_t) tail[0] | (uपूर्णांक32_t) tail[1]<<8
				 | (uपूर्णांक32_t) tail[2]<<16
				 | (uपूर्णांक32_t) tail[3]<<24);
			isize = ((uपूर्णांक32_t) tail[4] | (uपूर्णांक32_t) tail[5]<<8
				 | (uपूर्णांक32_t) tail[6]<<16
				 | (uपूर्णांक32_t) tail[7]<<24);
			ख_लिखो(मानक_त्रुटि, "stored   checksum %08x isize %08x\n",
				cksum, isize);

			अगर (cksum == cmdp->cpb.out_crc && isize == (uपूर्णांक32_t)
			    (total_out % (1ULL<<32))) अणु
				rc = 0;	जाओ ok1;
			पूर्ण अन्यथा अणु
				rc = -1; जाओ err4;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		जाओ पढ़ो_state;

	वापस -1;

err1:
	ख_लिखो(मानक_त्रुटि, "error: not a gzip file, expect %x, read %x\n",
		expect, c);
	वापस -1;

err2:
	ख_लिखो(मानक_त्रुटि, "error: the FLG byte is wrong or not being handled\n");
	वापस -1;

err3:
	ख_लिखो(मानक_त्रुटि, "error: gzip header\n");
	वापस -1;

err4:
	ख_लिखो(मानक_त्रुटि, "error: checksum missing or mismatch\n");

err5:
ok1:
	ख_लिखो(मानक_त्रुटि, "decomp is complete: fclose\n");
	ख_बंद(outf);

	वापस rc;
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक rc;
	काष्ठा sigaction act;
	व्योम *handle;

	nx_dbg = 0;
	nx_gzip_log = शून्य;
	act.sa_handler = 0;
	act.sa_sigaction = nxu_sigsegv_handler;
	act.sa_flags = SA_SIGINFO;
	act.sa_restorer = 0;
	sigemptyset(&act.sa_mask);
	sigaction(संक_अंश, &act, शून्य);

	handle = nx_function_begin(NX_FUNC_COMP_GZIP, 0);
	अगर (!handle) अणु
		ख_लिखो(मानक_त्रुटि, "Unable to init NX, errno %d\n", त्रुटि_सं);
		निकास(-1);
	पूर्ण

	rc = decompress_file(argc, argv, handle);

	nx_function_end(handle);

	वापस rc;
पूर्ण
