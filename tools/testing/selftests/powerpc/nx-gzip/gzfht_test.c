<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* P9 gzip sample code क्रम demonstrating the P9 NX hardware पूर्णांकerface.
 * Not पूर्णांकended क्रम productive uses or क्रम perक्रमmance or compression
 * ratio measurements.  For simplicity of demonstration, this sample
 * code compresses in to fixed Huffman blocks only (Deflate btype=1)
 * and has very simple memory management.  Dynamic Huffman blocks
 * (Deflate btype=2) are more involved as detailed in the user guide.
 * Note also that /dev/crypto/gzip, VAS and skiboot support are
 * required.
 *
 * Copyright 2020 IBM Corp.
 *
 * https://github.com/libnxz/घातer-gzip क्रम zlib api and other utils
 *
 * Author: Bulent Abali <abali@us.ibm.com>
 *
 * Definitions of acronyms used here. See
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

पूर्णांक nx_dbg;
खाता *nx_gzip_log;

#घोषणा NX_MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#घोषणा FNAME_MAX 1024
#घोषणा FEXT ".nx.gz"

/*
 * LZ counts वापसed in the user supplied nx_gzip_crb_cpb_t काष्ठाure.
 */
अटल पूर्णांक compress_fht_sample(अक्षर *src, uपूर्णांक32_t srclen, अक्षर *dst,
				uपूर्णांक32_t dstlen, पूर्णांक with_count,
				काष्ठा nx_gzip_crb_cpb_t *cmdp, व्योम *handle)
अणु
	uपूर्णांक32_t fc;

	निश्चित(!!cmdp);

	put32(cmdp->crb, gzip_fc, 0);  /* clear */
	fc = (with_count) ? GZIP_FC_COMPRESS_RESUME_FHT_COUNT :
			    GZIP_FC_COMPRESS_RESUME_FHT;
	putnn(cmdp->crb, gzip_fc, fc);
	putnn(cmdp->cpb, in_histlen, 0); /* resuming with no history */
	स_रखो((व्योम *) &cmdp->crb.csb, 0, माप(cmdp->crb.csb));

	/* Section 6.6 programming notes; spbc may be in two dअगरferent
	 * places depending on FC.
	 */
	अगर (!with_count)
		put32(cmdp->cpb, out_spbc_comp, 0);
	अन्यथा
		put32(cmdp->cpb, out_spbc_comp_with_count, 0);

	/* Figure 6-3 6-4; CSB location */
	put64(cmdp->crb, csb_address, 0);
	put64(cmdp->crb, csb_address,
	      (uपूर्णांक64_t) &cmdp->crb.csb & csb_address_mask);

	/* Source direct dde (scatter-gather list) */
	clear_dde(cmdp->crb.source_dde);
	putnn(cmdp->crb.source_dde, dde_count, 0);
	put32(cmdp->crb.source_dde, ddebc, srclen);
	put64(cmdp->crb.source_dde, ddead, (uपूर्णांक64_t) src);

	/* Target direct dde (scatter-gather list) */
	clear_dde(cmdp->crb.target_dde);
	putnn(cmdp->crb.target_dde, dde_count, 0);
	put32(cmdp->crb.target_dde, ddebc, dstlen);
	put64(cmdp->crb.target_dde, ddead, (uपूर्णांक64_t) dst);

	/* Submit the crb, the job descriptor, to the accelerator */
	वापस nxu_submit_job(cmdp, handle);
पूर्ण

/*
 * Prepares a blank no filename no बारtamp gzip header and वापसs
 * the number of bytes written to buf.
 * Gzip specअगरication at https://tools.ietf.org/hपंचांगl/rfc1952
 */
पूर्णांक gzip_header_blank(अक्षर *buf)
अणु
	पूर्णांक i = 0;

	buf[i++] = 0x1f; /* ID1 */
	buf[i++] = 0x8b; /* ID2 */
	buf[i++] = 0x08; /* CM  */
	buf[i++] = 0x00; /* FLG */
	buf[i++] = 0x00; /* MTIME */
	buf[i++] = 0x00; /* MTIME */
	buf[i++] = 0x00; /* MTIME */
	buf[i++] = 0x00; /* MTIME */
	buf[i++] = 0x04; /* XFL 4=fastest */
	buf[i++] = 0x03; /* OS UNIX */

	वापस i;
पूर्ण

/* Caller must मुक्त the allocated buffer वापस nonzero on error. */
पूर्णांक पढ़ो_alloc_input_file(अक्षर *fname, अक्षर **buf, माप_प्रकार *bufsize)
अणु
	काष्ठा stat statbuf;
	खाता *fp;
	अक्षर *p;
	माप_प्रकार num_bytes;

	अगर (stat(fname, &statbuf)) अणु
		लिखो_त्रुटि(fname);
		वापस(-1);
	पूर्ण
	fp = ख_खोलो(fname, "r");
	अगर (fp == शून्य) अणु
		लिखो_त्रुटि(fname);
		वापस(-1);
	पूर्ण
	निश्चित(शून्य != (p = (अक्षर *) दो_स्मृति(statbuf.st_size)));
	num_bytes = ख_पढ़ो(p, 1, statbuf.st_size, fp);
	अगर (ख_त्रुटि(fp) || (num_bytes != statbuf.st_size)) अणु
		लिखो_त्रुटि(fname);
		वापस(-1);
	पूर्ण
	*buf = p;
	*bufsize = num_bytes;
	वापस 0;
पूर्ण

/* Returns nonzero on error */
पूर्णांक ग_लिखो_output_file(अक्षर *fname, अक्षर *buf, माप_प्रकार bufsize)
अणु
	खाता *fp;
	माप_प्रकार num_bytes;

	fp = ख_खोलो(fname, "w");
	अगर (fp == शून्य) अणु
		लिखो_त्रुटि(fname);
		वापस(-1);
	पूर्ण
	num_bytes = ख_डालो(buf, 1, bufsize, fp);
	अगर (ख_त्रुटि(fp) || (num_bytes != bufsize)) अणु
		लिखो_त्रुटि(fname);
		वापस(-1);
	पूर्ण
	ख_बंद(fp);
	वापस 0;
पूर्ण

/*
 * Z_SYNC_FLUSH as described in zlib.h.
 * Returns number of appended bytes
 */
पूर्णांक append_sync_flush(अक्षर *buf, पूर्णांक tebc, पूर्णांक final)
अणु
	uपूर्णांक64_t flush;
	पूर्णांक shअगरt = (tebc & 0x7);

	अगर (tebc > 0) अणु
		/* Last byte is partially full */
		buf = buf - 1;
		*buf = *buf & (अचिन्हित अक्षर) ((1<<tebc)-1);
	पूर्ण अन्यथा
		*buf = 0;
	flush = ((0x1ULL & final) << shअगरt) | *buf;
	shअगरt = shअगरt + 3; /* BFINAL and BTYPE written */
	shअगरt = (shअगरt <= 8) ? 8 : 16;
	flush |= (0xFFFF0000ULL) << shअगरt; /* Zero length block */
	shअगरt = shअगरt + 32;
	जबतक (shअगरt > 0) अणु
		*buf++ = (अचिन्हित अक्षर) (flush & 0xffULL);
		flush = flush >> 8;
		shअगरt = shअगरt - 8;
	पूर्ण
	वापस(((tebc > 5) || (tebc == 0)) ? 5 : 4);
पूर्ण

/*
 * Final deflate block bit.  This call assumes the block
 * beginning is byte aligned.
 */
अटल व्योम set_bfinal(व्योम *buf, पूर्णांक bfinal)
अणु
	अक्षर *b = buf;

	अगर (bfinal)
		*b = *b | (अचिन्हित अक्षर) 0x01;
	अन्यथा
		*b = *b & (अचिन्हित अक्षर) 0xfe;
पूर्ण

पूर्णांक compress_file(पूर्णांक argc, अक्षर **argv, व्योम *handle)
अणु
	अक्षर *inbuf, *outbuf, *srcbuf, *dstbuf;
	अक्षर outname[FNAME_MAX];
	uपूर्णांक32_t srclen, dstlen;
	uपूर्णांक32_t flushlen, chunk;
	माप_प्रकार inlen, outlen, dsttotlen, srctotlen;
	uपूर्णांक32_t crc, spbc, tpbc, tebc;
	पूर्णांक lzcounts = 0;
	पूर्णांक cc;
	पूर्णांक num_hdr_bytes;
	काष्ठा nx_gzip_crb_cpb_t *cmdp;
	uपूर्णांक32_t pagelen = 65536;
	पूर्णांक fault_tries = NX_MAX_FAULTS;

	cmdp = (व्योम *)(uपूर्णांकptr_t)
		aligned_alloc(माप(काष्ठा nx_gzip_crb_cpb_t),
			      माप(काष्ठा nx_gzip_crb_cpb_t));

	अगर (argc != 2) अणु
		ख_लिखो(मानक_त्रुटि, "usage: %s <fname>\n", argv[0]);
		निकास(-1);
	पूर्ण
	अगर (पढ़ो_alloc_input_file(argv[1], &inbuf, &inlen))
		निकास(-1);
	ख_लिखो(मानक_त्रुटि, "file %s read, %ld bytes\n", argv[1], inlen);

	/* Generous output buffer क्रम header/trailer */
	outlen = 2 * inlen + 1024;

	निश्चित(शून्य != (outbuf = (अक्षर *)दो_स्मृति(outlen)));
	nxu_touch_pages(outbuf, outlen, pagelen, 1);

	/* Compress piecemeal in smallish chunks */
	chunk = 1<<22;

	/* Write the gzip header to the stream */
	num_hdr_bytes = gzip_header_blank(outbuf);
	dstbuf    = outbuf + num_hdr_bytes;
	outlen    = outlen - num_hdr_bytes;
	dsttotlen = num_hdr_bytes;

	srcbuf    = inbuf;
	srctotlen = 0;

	/* Init the CRB, the coprocessor request block */
	स_रखो(&cmdp->crb, 0, माप(cmdp->crb));

	/* Initial gzip crc32 */
	put32(cmdp->cpb, in_crc, 0);

	जबतक (inlen > 0) अणु

		/* Submit chunk size source data per job */
		srclen = NX_MIN(chunk, inlen);
		/* Supply large target in हाल data expands */
		dstlen = NX_MIN(2*srclen, outlen);

		/* Page faults are handled by the user code */

		/* Fault-in pages; an improved code wouldn't touch so
		 * many pages but would try to estimate the
		 * compression ratio and adjust both the src and dst
		 * touch amounts.
		 */
		nxu_touch_pages(cmdp, माप(काष्ठा nx_gzip_crb_cpb_t), pagelen,
				1);
		nxu_touch_pages(srcbuf, srclen, pagelen, 0);
		nxu_touch_pages(dstbuf, dstlen, pagelen, 1);

		cc = compress_fht_sample(
			srcbuf, srclen,
			dstbuf, dstlen,
			lzcounts, cmdp, handle);

		अगर (cc != ERR_NX_OK && cc != ERR_NX_TPBC_GT_SPBC &&
		    cc != ERR_NX_AT_FAULT) अणु
			ख_लिखो(मानक_त्रुटि, "nx error: cc= %d\n", cc);
			निकास(-1);
		पूर्ण

		/* Page faults are handled by the user code */
		अगर (cc == ERR_NX_AT_FAULT) अणु
			NXPRT(ख_लिखो(मानक_त्रुटि, "page fault: cc= %d, ", cc));
			NXPRT(ख_लिखो(मानक_त्रुटि, "try= %d, fsa= %08llx\n",
				  fault_tries,
				  (अचिन्हित दीर्घ दीर्घ) cmdp->crb.csb.fsaddr));
			fault_tries--;
			अगर (fault_tries > 0) अणु
				जारी;
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि, "error: cannot progress; ");
				ख_लिखो(मानक_त्रुटि, "too many faults\n");
				निकास(-1);
			पूर्ण
		पूर्ण

		fault_tries = NX_MAX_FAULTS; /* Reset क्रम the next chunk */

		inlen     = inlen - srclen;
		srcbuf    = srcbuf + srclen;
		srctotlen = srctotlen + srclen;

		/* Two possible locations क्रम spbc depending on the function
		 * code.
		 */
		spbc = (!lzcounts) ? get32(cmdp->cpb, out_spbc_comp) :
			get32(cmdp->cpb, out_spbc_comp_with_count);
		निश्चित(spbc == srclen);

		/* Target byte count */
		tpbc = get32(cmdp->crb.csb, tpbc);
		/* Target ending bit count */
		tebc = getnn(cmdp->cpb, out_tebc);
		NXPRT(ख_लिखो(मानक_त्रुटि, "compressed chunk %d ", spbc));
		NXPRT(ख_लिखो(मानक_त्रुटि, "to %d bytes, tebc= %d\n", tpbc, tebc));

		अगर (inlen > 0) अणु /* More chunks to go */
			set_bfinal(dstbuf, 0);
			dstbuf    = dstbuf + tpbc;
			dsttotlen = dsttotlen + tpbc;
			outlen    = outlen - tpbc;
			/* Round up to the next byte with a flush
			 * block; करो not set the BFINAqL bit.
			 */
			flushlen  = append_sync_flush(dstbuf, tebc, 0);
			dsttotlen = dsttotlen + flushlen;
			outlen    = outlen - flushlen;
			dstbuf    = dstbuf + flushlen;
			NXPRT(ख_लिखो(मानक_त्रुटि, "added sync_flush %d bytes\n",
					flushlen));
		पूर्ण अन्यथा अणु  /* Done */
			/* Set the BFINAL bit of the last block per Deflate
			 * specअगरication.
			 */
			set_bfinal(dstbuf, 1);
			dstbuf    = dstbuf + tpbc;
			dsttotlen = dsttotlen + tpbc;
			outlen    = outlen - tpbc;
		पूर्ण

		/* Resuming crc32 क्रम the next chunk */
		crc = get32(cmdp->cpb, out_crc);
		put32(cmdp->cpb, in_crc, crc);
		crc = be32toh(crc);
	पूर्ण

	/* Append crc32 and ISIZE to the end */
	स_नकल(dstbuf, &crc, 4);
	स_नकल(dstbuf+4, &srctotlen, 4);
	dsttotlen = dsttotlen + 8;
	outlen    = outlen - 8;

	निश्चित(FNAME_MAX > (म_माप(argv[1]) + म_माप(FEXT)));
	म_नकल(outname, argv[1]);
	म_जोड़ो(outname, FEXT);
	अगर (ग_लिखो_output_file(outname, outbuf, dsttotlen)) अणु
		ख_लिखो(मानक_त्रुटि, "write error: %s\n", outname);
		निकास(-1);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "compressed %ld to %ld bytes total, ", srctotlen,
		dsttotlen);
	ख_लिखो(मानक_त्रुटि, "crc32 checksum = %08x\n", crc);

	अगर (inbuf != शून्य)
		मुक्त(inbuf);

	अगर (outbuf != शून्य)
		मुक्त(outbuf);

	वापस 0;
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

	rc = compress_file(argc, argv, handle);

	nx_function_end(handle);

	वापस rc;
पूर्ण
