<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Minimal BPF JIT image disassembler
 *
 * Disassembles BPF JIT compiler emitted opcodes back to यंत्र insn's क्रम
 * debugging or verअगरication purposes.
 *
 * To get the disassembly of the JIT code, करो the following:
 *
 *  1) `echo 2 > /proc/sys/net/core/bpf_jit_enable`
 *  2) Load a BPF filter (e.g. `tcpdump -p -n -s 0 -i eth1 host 192.168.20.0/24`)
 *  3) Run e.g. `bpf_jit_disयंत्र -o` to पढ़ो out the last JIT code
 *
 * Copyright 2013 Daniel Borkmann <borkmann@redhat.com>
 */

#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <bfd.h>
#समावेश <dis-यंत्र.h>
#समावेश <regex.h>
#समावेश <fcntl.h>
#समावेश <sys/klog.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <सीमा.स>

#घोषणा CMD_ACTION_SIZE_BUFFER		10
#घोषणा CMD_ACTION_READ_ALL		3

अटल व्योम get_exec_path(अक्षर *tpath, माप_प्रकार size)
अणु
	अक्षर *path;
	sमाप_प्रकार len;

	snम_लिखो(tpath, size, "/proc/%d/exe", (पूर्णांक) getpid());
	tpath[size - 1] = 0;

	path = strdup(tpath);
	निश्चित(path);

	len = पढ़ोlink(path, tpath, size);
	tpath[len] = 0;

	मुक्त(path);
पूर्ण

अटल व्योम get_यंत्र_insns(uपूर्णांक8_t *image, माप_प्रकार len, पूर्णांक opcodes)
अणु
	पूर्णांक count, i, pc = 0;
	अक्षर tpath[PATH_MAX];
	काष्ठा disassemble_info info;
	disassembler_ftype disassemble;
	bfd *bfdf;

	स_रखो(tpath, 0, माप(tpath));
	get_exec_path(tpath, माप(tpath));

	bfdf = bfd_खोलोr(tpath, शून्य);
	निश्चित(bfdf);
	निश्चित(bfd_check_क्रमmat(bfdf, bfd_object));

	init_disassemble_info(&info, मानक_निकास, (ख_लिखो_ftype) ख_लिखो);
	info.arch = bfd_get_arch(bfdf);
	info.mach = bfd_get_mach(bfdf);
	info.buffer = image;
	info.buffer_length = len;

	disassemble_init_क्रम_target(&info);

#अगर_घोषित DISASM_FOUR_ARGS_SIGNATURE
	disassemble = disassembler(info.arch,
				   bfd_big_endian(bfdf),
				   info.mach,
				   bfdf);
#अन्यथा
	disassemble = disassembler(bfdf);
#पूर्ण_अगर
	निश्चित(disassemble);

	करो अणु
		म_लिखो("%4x:\t", pc);

		count = disassemble(pc, &info);

		अगर (opcodes) अणु
			म_लिखो("\n\t");
			क्रम (i = 0; i < count; ++i)
				म_लिखो("%02x ", (uपूर्णांक8_t) image[pc + i]);
		पूर्ण
		म_लिखो("\n");

		pc += count;
	पूर्ण जबतक(count > 0 && pc < len);

	bfd_बंद(bfdf);
पूर्ण

अटल अक्षर *get_klog_buff(अचिन्हित पूर्णांक *klen)
अणु
	पूर्णांक ret, len;
	अक्षर *buff;

	len = klogctl(CMD_ACTION_SIZE_BUFFER, शून्य, 0);
	अगर (len < 0)
		वापस शून्य;

	buff = दो_स्मृति(len);
	अगर (!buff)
		वापस शून्य;

	ret = klogctl(CMD_ACTION_READ_ALL, buff, len);
	अगर (ret < 0) अणु
		मुक्त(buff);
		वापस शून्य;
	पूर्ण

	*klen = ret;
	वापस buff;
पूर्ण

अटल अक्षर *get_flog_buff(स्थिर अक्षर *file, अचिन्हित पूर्णांक *klen)
अणु
	पूर्णांक fd, ret, len;
	काष्ठा stat fi;
	अक्षर *buff;

	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0)
		वापस शून्य;

	ret = ख_स्थिति(fd, &fi);
	अगर (ret < 0 || !S_ISREG(fi.st_mode))
		जाओ out;

	len = fi.st_size + 1;
	buff = दो_स्मृति(len);
	अगर (!buff)
		जाओ out;

	स_रखो(buff, 0, len);
	ret = पढ़ो(fd, buff, len - 1);
	अगर (ret <= 0)
		जाओ out_मुक्त;

	बंद(fd);
	*klen = ret;
	वापस buff;
out_मुक्त:
	मुक्त(buff);
out:
	बंद(fd);
	वापस शून्य;
पूर्ण

अटल अक्षर *get_log_buff(स्थिर अक्षर *file, अचिन्हित पूर्णांक *klen)
अणु
	वापस file ? get_flog_buff(file, klen) : get_klog_buff(klen);
पूर्ण

अटल व्योम put_log_buff(अक्षर *buff)
अणु
	मुक्त(buff);
पूर्ण

अटल uपूर्णांक8_t *get_last_jit_image(अक्षर *haystack, माप_प्रकार hlen,
				   अचिन्हित पूर्णांक *ilen)
अणु
	अक्षर *ptr, *pptr, *पंचांगp;
	off_t off = 0;
	अचिन्हित पूर्णांक proglen;
	पूर्णांक ret, flen, pass, ulen = 0;
	regmatch_t pmatch[1];
	अचिन्हित दीर्घ base;
	regex_t regex;
	uपूर्णांक8_t *image;

	अगर (hlen == 0)
		वापस शून्य;

	ret = regcomp(&regex, "flen=[[:alnum:]]+ proglen=[[:digit:]]+ "
		      "pass=[[:digit:]]+ image=[[:xdigit:]]+", REG_EXTENDED);
	निश्चित(ret == 0);

	ptr = haystack;
	स_रखो(pmatch, 0, माप(pmatch));

	जबतक (1) अणु
		ret = regexec(&regex, ptr, 1, pmatch, 0);
		अगर (ret == 0) अणु
			ptr += pmatch[0].rm_eo;
			off += pmatch[0].rm_eo;
			निश्चित(off < hlen);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	ptr = haystack + off - (pmatch[0].rm_eo - pmatch[0].rm_so);
	ret = माला_पूछो(ptr, "flen=%d proglen=%u pass=%d image=%lx",
		     &flen, &proglen, &pass, &base);
	अगर (ret != 4) अणु
		regमुक्त(&regex);
		वापस शून्य;
	पूर्ण
	अगर (proglen > 1000000) अणु
		म_लिखो("proglen of %d too big, stopping\n", proglen);
		वापस शून्य;
	पूर्ण

	image = दो_स्मृति(proglen);
	अगर (!image) अणु
		म_लिखो("Out of memory\n");
		वापस शून्य;
	पूर्ण
	स_रखो(image, 0, proglen);

	पंचांगp = ptr = haystack + off;
	जबतक ((ptr = म_मोहर(पंचांगp, "\n")) != शून्य && ulen < proglen) अणु
		पंचांगp = शून्य;
		अगर (!म_माला(ptr, "JIT code"))
			जारी;
		pptr = ptr;
		जबतक ((ptr = म_माला(pptr, ":")))
			pptr = ptr + 1;
		ptr = pptr;
		करो अणु
			image[ulen++] = (uपूर्णांक8_t) म_से_अदीर्घ(pptr, &pptr, 16);
			अगर (ptr == pptr) अणु
				ulen--;
				अवरोध;
			पूर्ण
			अगर (ulen >= proglen)
				अवरोध;
			ptr = pptr;
		पूर्ण जबतक (1);
	पूर्ण

	निश्चित(ulen == proglen);
	म_लिखो("%u bytes emitted from JIT compiler (pass:%d, flen:%d)\n",
	       proglen, pass, flen);
	म_लिखो("%lx + <x>:\n", base);

	regमुक्त(&regex);
	*ilen = ulen;
	वापस image;
पूर्ण

अटल व्योम usage(व्योम)
अणु
	म_लिखो("Usage: bpf_jit_disasm [...]\n");
	म_लिखो("       -o          Also display related opcodes (default: off).\n");
	म_लिखो("       -O <file>   Write binary image of code to file, don't disassemble to stdout.\n");
	म_लिखो("       -f <file>   Read last image dump from file or stdin (default: klog).\n");
	म_लिखो("       -h          Display this help.\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक len, klen, opt, opcodes = 0;
	अक्षर *kbuff, *file = शून्य;
	अक्षर *ofile = शून्य;
	पूर्णांक ofd;
	sमाप_प्रकार nr;
	uपूर्णांक8_t *pos;
	uपूर्णांक8_t *image = शून्य;

	जबतक ((opt = getopt(argc, argv, "of:O:")) != -1) अणु
		चयन (opt) अणु
		हाल 'o':
			opcodes = 1;
			अवरोध;
		हाल 'O':
			ofile = optarg;
			अवरोध;
		हाल 'f':
			file = optarg;
			अवरोध;
		शेष:
			usage();
			वापस -1;
		पूर्ण
	पूर्ण

	bfd_init();

	kbuff = get_log_buff(file, &klen);
	अगर (!kbuff) अणु
		ख_लिखो(मानक_त्रुटि, "Could not retrieve log buffer!\n");
		वापस -1;
	पूर्ण

	image = get_last_jit_image(kbuff, klen, &len);
	अगर (!image) अणु
		ख_लिखो(मानक_त्रुटि, "No JIT image found!\n");
		जाओ करोne;
	पूर्ण
	अगर (!ofile) अणु
		get_यंत्र_insns(image, len, opcodes);
		जाओ करोne;
	पूर्ण

	ofd = खोलो(ofile, O_WRONLY | O_CREAT | O_TRUNC, DEFखाताMODE);
	अगर (ofd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Could not open file %s for writing: ", ofile);
		लिखो_त्रुटि(शून्य);
		जाओ करोne;
	पूर्ण
	pos = image;
	करो अणु
		nr = ग_लिखो(ofd, pos, len);
		अगर (nr < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Could not write data to %s: ", ofile);
			लिखो_त्रुटि(शून्य);
			जाओ करोne;
		पूर्ण
		len -= nr;
		pos += nr;
	पूर्ण जबतक (len);
	बंद(ofd);

करोne:
	put_log_buff(kbuff);
	मुक्त(image);
	वापस 0;
पूर्ण
