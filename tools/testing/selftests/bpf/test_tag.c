<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <प्रकार.स>
#समावेश <समय.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sched.h>
#समावेश <सीमा.स>
#समावेश <निश्चित.स>

#समावेश <sys/socket.h>

#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_alg.h>

#समावेश <bpf/bpf.h>

#समावेश "../../../include/linux/filter.h"
#समावेश "bpf_rlimit.h"

अटल काष्ठा bpf_insn prog[BPF_MAXINSNS];

अटल व्योम bpf_gen_imm_prog(अचिन्हित पूर्णांक insns, पूर्णांक fd_map)
अणु
	पूर्णांक i;

	बेक्रम(समय(शून्य));
	क्रम (i = 0; i < insns; i++)
		prog[i] = BPF_ALU64_IMM(BPF_MOV, i % BPF_REG_10, अक्रम());
	prog[i - 1] = BPF_EXIT_INSN();
पूर्ण

अटल व्योम bpf_gen_map_prog(अचिन्हित पूर्णांक insns, पूर्णांक fd_map)
अणु
	पूर्णांक i, j = 0;

	क्रम (i = 0; i + 1 < insns; i += 2) अणु
		काष्ठा bpf_insn पंचांगp[] = अणु
			BPF_LD_MAP_FD(j++ % BPF_REG_10, fd_map)
		पूर्ण;

		स_नकल(&prog[i], पंचांगp, माप(पंचांगp));
	पूर्ण
	अगर (insns % 2 == 0)
		prog[insns - 2] = BPF_ALU64_IMM(BPF_MOV, i % BPF_REG_10, 42);
	prog[insns - 1] = BPF_EXIT_INSN();
पूर्ण

अटल पूर्णांक bpf_try_load_prog(पूर्णांक insns, पूर्णांक fd_map,
			     व्योम (*bpf_filler)(अचिन्हित पूर्णांक insns,
						पूर्णांक fd_map))
अणु
	पूर्णांक fd_prog;

	bpf_filler(insns, fd_map);
	fd_prog = bpf_load_program(BPF_PROG_TYPE_SCHED_CLS, prog, insns, "", 0,
				   शून्य, 0);
	निश्चित(fd_prog > 0);
	अगर (fd_map > 0)
		bpf_filler(insns, 0);
	वापस fd_prog;
पूर्ण

अटल पूर्णांक __hex2bin(अक्षर ch)
अणु
	अगर ((ch >= '0') && (ch <= '9'))
		वापस ch - '0';
	ch = छोटे(ch);
	अगर ((ch >= 'a') && (ch <= 'f'))
		वापस ch - 'a' + 10;
	वापस -1;
पूर्ण

अटल पूर्णांक hex2bin(uपूर्णांक8_t *dst, स्थिर अक्षर *src, माप_प्रकार count)
अणु
	जबतक (count--) अणु
		पूर्णांक hi = __hex2bin(*src++);
		पूर्णांक lo = __hex2bin(*src++);

		अगर ((hi < 0) || (lo < 0))
			वापस -1;
		*dst++ = (hi << 4) | lo;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tag_from_fdinfo(पूर्णांक fd_prog, uपूर्णांक8_t *tag, uपूर्णांक32_t len)
अणु
	स्थिर पूर्णांक prefix_len = माप("prog_tag:\t") - 1;
	अक्षर buff[256];
	पूर्णांक ret = -1;
	खाता *fp;

	snम_लिखो(buff, माप(buff), "/proc/%d/fdinfo/%d", getpid(),
		 fd_prog);
	fp = ख_खोलो(buff, "r");
	निश्चित(fp);

	जबतक (ख_माला_लो(buff, माप(buff), fp)) अणु
		अगर (म_भेदन(buff, "prog_tag:\t", prefix_len))
			जारी;
		ret = hex2bin(tag, buff + prefix_len, len);
		अवरोध;
	पूर्ण

	ख_बंद(fp);
	निश्चित(!ret);
पूर्ण

अटल व्योम tag_from_alg(पूर्णांक insns, uपूर्णांक8_t *tag, uपूर्णांक32_t len)
अणु
	अटल स्थिर काष्ठा sockaddr_alg alg = अणु
		.salg_family	= AF_ALG,
		.salg_type	= "hash",
		.salg_name	= "sha1",
	पूर्ण;
	पूर्णांक fd_base, fd_alg, ret;
	sमाप_प्रकार size;

	fd_base = socket(AF_ALG, SOCK_SEQPACKET, 0);
	निश्चित(fd_base > 0);

	ret = bind(fd_base, (काष्ठा sockaddr *)&alg, माप(alg));
	निश्चित(!ret);

	fd_alg = accept(fd_base, शून्य, 0);
	निश्चित(fd_alg > 0);

	insns *= माप(काष्ठा bpf_insn);
	size = ग_लिखो(fd_alg, prog, insns);
	निश्चित(size == insns);

	size = पढ़ो(fd_alg, tag, len);
	निश्चित(size == len);

	बंद(fd_alg);
	बंद(fd_base);
पूर्ण

अटल व्योम tag_dump(स्थिर अक्षर *prefix, uपूर्णांक8_t *tag, uपूर्णांक32_t len)
अणु
	पूर्णांक i;

	म_लिखो("%s", prefix);
	क्रम (i = 0; i < len; i++)
		म_लिखो("%02x", tag[i]);
	म_लिखो("\n");
पूर्ण

अटल व्योम tag_निकास_report(पूर्णांक insns, पूर्णांक fd_map, uपूर्णांक8_t *ftag,
			    uपूर्णांक8_t *atag, uपूर्णांक32_t len)
अणु
	म_लिखो("Program tag mismatch for %d insns%s!\n", insns,
	       fd_map < 0 ? "" : " with map");

	tag_dump("  fdinfo result: ", ftag, len);
	tag_dump("  af_alg result: ", atag, len);
	निकास(1);
पूर्ण

अटल व्योम करो_test(uपूर्णांक32_t *tests, पूर्णांक start_insns, पूर्णांक fd_map,
		    व्योम (*bpf_filler)(अचिन्हित पूर्णांक insns, पूर्णांक fd))
अणु
	पूर्णांक i, fd_prog;

	क्रम (i = start_insns; i <= BPF_MAXINSNS; i++) अणु
		uपूर्णांक8_t ftag[8], atag[माप(ftag)];

		fd_prog = bpf_try_load_prog(i, fd_map, bpf_filler);
		tag_from_fdinfo(fd_prog, ftag, माप(ftag));
		tag_from_alg(i, atag, माप(atag));
		अगर (स_भेद(ftag, atag, माप(ftag)))
			tag_निकास_report(i, fd_map, ftag, atag, माप(ftag));

		बंद(fd_prog);
		sched_yield();
		(*tests)++;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	uपूर्णांक32_t tests = 0;
	पूर्णांक i, fd_map;

	fd_map = bpf_create_map(BPF_MAP_TYPE_HASH, माप(पूर्णांक),
				माप(पूर्णांक), 1, BPF_F_NO_PREALLOC);
	निश्चित(fd_map > 0);

	क्रम (i = 0; i < 5; i++) अणु
		करो_test(&tests, 2, -1,     bpf_gen_imm_prog);
		करो_test(&tests, 3, fd_map, bpf_gen_map_prog);
	पूर्ण

	म_लिखो("test_tag: OK (%u tests)\n", tests);
	बंद(fd_map);
	वापस 0;
पूर्ण
