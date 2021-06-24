<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Minimal BPF debugger
 *
 * Minimal BPF debugger that mimics the kernel's engine (w/o extensions)
 * and allows क्रम single stepping through selected packets from a pcap
 * with a provided user filter in order to facilitate verअगरication of a
 * BPF program. Besides others, this is useful to verअगरy BPF programs
 * beक्रमe attaching to a live प्रणाली, and can be used in socket filters,
 * cls_bpf, xt_bpf, team driver and e.g. PTP code; in particular when a
 * single more complex BPF program is being used. Reasons क्रम a more
 * complex BPF program are likely primarily to optimize execution समय
 * क्रम making a verdict when multiple simple BPF programs are combined
 * पूर्णांकo one in order to prevent parsing same headers multiple बार.
 *
 * More on how to debug BPF opcodes see Documentation/networking/filter.rst
 * which is the मुख्य करोcument on BPF. Mini howto क्रम getting started:
 *
 *  1) `./bpf_dbg` to enter the shell (shell cmds denoted with '>'):
 *  2) > load bpf 6,40 0 0 12,21 0 3 20... (output from `bpf_यंत्र` or
 *     `tcpdump -iem1 -ddd port 22 | tr '\n' ','` to load as filter)
 *  3) > load pcap foo.pcap
 *  4) > run <n>/disassemble/dump/quit (self-explanatory)
 *  5) > अवरोधpoपूर्णांक 2 (sets bp at loaded BPF insns 2, करो `run` then;
 *       multiple bps can be set, of course, a call to `अवरोधpoपूर्णांक`
 *       w/o args shows currently loaded bps, `अवरोधpoपूर्णांक reset` क्रम
 *       resetting all अवरोधpoपूर्णांकs)
 *  6) > select 3 (`run` etc will start from the 3rd packet in the pcap)
 *  7) > step [-<n>, +<n>] (perक्रमms single stepping through the BPF)
 *
 * Copyright 2013 Daniel Borkmann <borkmann@redhat.com>
 */

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <प्रकार.स>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <समलाँघ.स>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_packet.h>
#समावेश <पढ़ोline/पढ़ोline.h>
#समावेश <पढ़ोline/history.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <arpa/inet.h>
#समावेश <net/ethernet.h>

#घोषणा TCPDUMP_MAGIC	0xa1b2c3d4

#घोषणा BPF_LDX_B	(BPF_LDX | BPF_B)
#घोषणा BPF_LDX_W	(BPF_LDX | BPF_W)
#घोषणा BPF_JMP_JA	(BPF_JMP | BPF_JA)
#घोषणा BPF_JMP_JEQ	(BPF_JMP | BPF_JEQ)
#घोषणा BPF_JMP_JGT	(BPF_JMP | BPF_JGT)
#घोषणा BPF_JMP_JGE	(BPF_JMP | BPF_JGE)
#घोषणा BPF_JMP_JSET	(BPF_JMP | BPF_JSET)
#घोषणा BPF_ALU_ADD	(BPF_ALU | BPF_ADD)
#घोषणा BPF_ALU_SUB	(BPF_ALU | BPF_SUB)
#घोषणा BPF_ALU_MUL	(BPF_ALU | BPF_MUL)
#घोषणा BPF_ALU_DIV	(BPF_ALU | BPF_DIV)
#घोषणा BPF_ALU_MOD	(BPF_ALU | BPF_MOD)
#घोषणा BPF_ALU_NEG	(BPF_ALU | BPF_NEG)
#घोषणा BPF_ALU_AND	(BPF_ALU | BPF_AND)
#घोषणा BPF_ALU_OR	(BPF_ALU | BPF_OR)
#घोषणा BPF_ALU_XOR	(BPF_ALU | BPF_XOR)
#घोषणा BPF_ALU_LSH	(BPF_ALU | BPF_LSH)
#घोषणा BPF_ALU_RSH	(BPF_ALU | BPF_RSH)
#घोषणा BPF_MISC_TAX	(BPF_MISC | BPF_TAX)
#घोषणा BPF_MISC_TXA	(BPF_MISC | BPF_TXA)
#घोषणा BPF_LD_B	(BPF_LD | BPF_B)
#घोषणा BPF_LD_H	(BPF_LD | BPF_H)
#घोषणा BPF_LD_W	(BPF_LD | BPF_W)

#अगर_अघोषित array_size
# define array_size(x)	(माप(x) / माप((x)[0]))
#पूर्ण_अगर

#अगर_अघोषित __check_क्रमmat_म_लिखो
# define __check_क्रमmat_म_लिखो(pos_fmtstr, pos_fmtargs) \
	__attribute__ ((क्रमmat (म_लिखो, (pos_fmtstr), (pos_fmtargs))))
#पूर्ण_अगर

क्रमागत अणु
	CMD_OK,
	CMD_ERR,
	CMD_EX,
पूर्ण;

काष्ठा shell_cmd अणु
	स्थिर अक्षर *name;
	पूर्णांक (*func)(अक्षर *args);
पूर्ण;

काष्ठा pcap_filehdr अणु
	uपूर्णांक32_t magic;
	uपूर्णांक16_t version_major;
	uपूर्णांक16_t version_minor;
	पूर्णांक32_t  thiszone;
	uपूर्णांक32_t sigfigs;
	uपूर्णांक32_t snaplen;
	uपूर्णांक32_t linktype;
पूर्ण;

काष्ठा pcap_समयval अणु
	पूर्णांक32_t tv_sec;
	पूर्णांक32_t tv_usec;
पूर्ण;

काष्ठा pcap_pkthdr अणु
	काष्ठा pcap_समयval ts;
	uपूर्णांक32_t caplen;
	uपूर्णांक32_t len;
पूर्ण;

काष्ठा bpf_regs अणु
	uपूर्णांक32_t A;
	uपूर्णांक32_t X;
	uपूर्णांक32_t M[BPF_MEMWORDS];
	uपूर्णांक32_t R;
	bool     Rs;
	uपूर्णांक16_t Pc;
पूर्ण;

अटल काष्ठा sock_filter bpf_image[BPF_MAXINSNS + 1];
अटल अचिन्हित पूर्णांक bpf_prog_len;

अटल पूर्णांक bpf_अवरोधpoपूर्णांकs[64];
अटल काष्ठा bpf_regs bpf_regs[BPF_MAXINSNS + 1];
अटल काष्ठा bpf_regs bpf_curr;
अटल अचिन्हित पूर्णांक bpf_regs_len;

अटल पूर्णांक pcap_fd = -1;
अटल अचिन्हित पूर्णांक pcap_packet;
अटल माप_प्रकार pcap_map_size;
अटल अक्षर *pcap_ptr_बहु_शुरू, *pcap_ptr_va_curr;

अटल स्थिर अक्षर * स्थिर op_table[] = अणु
	[BPF_ST]	= "st",
	[BPF_STX]	= "stx",
	[BPF_LD_B]	= "ldb",
	[BPF_LD_H]	= "ldh",
	[BPF_LD_W]	= "ld",
	[BPF_LDX]	= "ldx",
	[BPF_LDX_B]	= "ldxb",
	[BPF_JMP_JA]	= "ja",
	[BPF_JMP_JEQ]	= "jeq",
	[BPF_JMP_JGT]	= "jgt",
	[BPF_JMP_JGE]	= "jge",
	[BPF_JMP_JSET]	= "jset",
	[BPF_ALU_ADD]	= "add",
	[BPF_ALU_SUB]	= "sub",
	[BPF_ALU_MUL]	= "mul",
	[BPF_ALU_DIV]	= "div",
	[BPF_ALU_MOD]	= "mod",
	[BPF_ALU_NEG]	= "neg",
	[BPF_ALU_AND]	= "and",
	[BPF_ALU_OR]	= "or",
	[BPF_ALU_XOR]	= "xor",
	[BPF_ALU_LSH]	= "lsh",
	[BPF_ALU_RSH]	= "rsh",
	[BPF_MISC_TAX]	= "tax",
	[BPF_MISC_TXA]	= "txa",
	[BPF_RET]	= "ret",
पूर्ण;

अटल __check_क्रमmat_म_लिखो(1, 2) पूर्णांक rl_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची vl;

	बहु_शुरू(vl, fmt);
	ret = भख_लिखो(rl_outstream, fmt, vl);
	बहु_पूर्ण(vl);

	वापस ret;
पूर्ण

अटल पूर्णांक matches(स्थिर अक्षर *cmd, स्थिर अक्षर *pattern)
अणु
	पूर्णांक len = म_माप(cmd);

	अगर (len > म_माप(pattern))
		वापस -1;

	वापस स_भेद(pattern, cmd, len);
पूर्ण

अटल व्योम hex_dump(स्थिर uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	पूर्णांक i;

	rl_म_लिखो("%3u: ", 0);
	क्रम (i = 0; i < len; i++) अणु
		अगर (i && !(i % 16))
			rl_म_लिखो("\n%3u: ", i);
		rl_म_लिखो("%02x ", buf[i]);
	पूर्ण
	rl_म_लिखो("\n");
पूर्ण

अटल bool bpf_prog_loaded(व्योम)
अणु
	अगर (bpf_prog_len == 0)
		rl_म_लिखो("no bpf program loaded!\n");

	वापस bpf_prog_len > 0;
पूर्ण

अटल व्योम bpf_disयंत्र(स्थिर काष्ठा sock_filter f, अचिन्हित पूर्णांक i)
अणु
	स्थिर अक्षर *op, *fmt;
	पूर्णांक val = f.k;
	अक्षर buf[256];

	चयन (f.code) अणु
	हाल BPF_RET | BPF_K:
		op = op_table[BPF_RET];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_RET | BPF_A:
		op = op_table[BPF_RET];
		fmt = "a";
		अवरोध;
	हाल BPF_RET | BPF_X:
		op = op_table[BPF_RET];
		fmt = "x";
		अवरोध;
	हाल BPF_MISC_TAX:
		op = op_table[BPF_MISC_TAX];
		fmt = "";
		अवरोध;
	हाल BPF_MISC_TXA:
		op = op_table[BPF_MISC_TXA];
		fmt = "";
		अवरोध;
	हाल BPF_ST:
		op = op_table[BPF_ST];
		fmt = "M[%d]";
		अवरोध;
	हाल BPF_STX:
		op = op_table[BPF_STX];
		fmt = "M[%d]";
		अवरोध;
	हाल BPF_LD_W | BPF_ABS:
		op = op_table[BPF_LD_W];
		fmt = "[%d]";
		अवरोध;
	हाल BPF_LD_H | BPF_ABS:
		op = op_table[BPF_LD_H];
		fmt = "[%d]";
		अवरोध;
	हाल BPF_LD_B | BPF_ABS:
		op = op_table[BPF_LD_B];
		fmt = "[%d]";
		अवरोध;
	हाल BPF_LD_W | BPF_LEN:
		op = op_table[BPF_LD_W];
		fmt = "#len";
		अवरोध;
	हाल BPF_LD_W | BPF_IND:
		op = op_table[BPF_LD_W];
		fmt = "[x+%d]";
		अवरोध;
	हाल BPF_LD_H | BPF_IND:
		op = op_table[BPF_LD_H];
		fmt = "[x+%d]";
		अवरोध;
	हाल BPF_LD_B | BPF_IND:
		op = op_table[BPF_LD_B];
		fmt = "[x+%d]";
		अवरोध;
	हाल BPF_LD | BPF_IMM:
		op = op_table[BPF_LD_W];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_LDX | BPF_IMM:
		op = op_table[BPF_LDX];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_LDX_B | BPF_MSH:
		op = op_table[BPF_LDX_B];
		fmt = "4*([%d]&0xf)";
		अवरोध;
	हाल BPF_LD | BPF_MEM:
		op = op_table[BPF_LD_W];
		fmt = "M[%d]";
		अवरोध;
	हाल BPF_LDX | BPF_MEM:
		op = op_table[BPF_LDX];
		fmt = "M[%d]";
		अवरोध;
	हाल BPF_JMP_JA:
		op = op_table[BPF_JMP_JA];
		fmt = "%d";
		val = i + 1 + f.k;
		अवरोध;
	हाल BPF_JMP_JGT | BPF_X:
		op = op_table[BPF_JMP_JGT];
		fmt = "x";
		अवरोध;
	हाल BPF_JMP_JGT | BPF_K:
		op = op_table[BPF_JMP_JGT];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_JMP_JGE | BPF_X:
		op = op_table[BPF_JMP_JGE];
		fmt = "x";
		अवरोध;
	हाल BPF_JMP_JGE | BPF_K:
		op = op_table[BPF_JMP_JGE];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_JMP_JEQ | BPF_X:
		op = op_table[BPF_JMP_JEQ];
		fmt = "x";
		अवरोध;
	हाल BPF_JMP_JEQ | BPF_K:
		op = op_table[BPF_JMP_JEQ];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_JMP_JSET | BPF_X:
		op = op_table[BPF_JMP_JSET];
		fmt = "x";
		अवरोध;
	हाल BPF_JMP_JSET | BPF_K:
		op = op_table[BPF_JMP_JSET];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_ALU_NEG:
		op = op_table[BPF_ALU_NEG];
		fmt = "";
		अवरोध;
	हाल BPF_ALU_LSH | BPF_X:
		op = op_table[BPF_ALU_LSH];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_LSH | BPF_K:
		op = op_table[BPF_ALU_LSH];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_RSH | BPF_X:
		op = op_table[BPF_ALU_RSH];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_RSH | BPF_K:
		op = op_table[BPF_ALU_RSH];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_ADD | BPF_X:
		op = op_table[BPF_ALU_ADD];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_ADD | BPF_K:
		op = op_table[BPF_ALU_ADD];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_SUB | BPF_X:
		op = op_table[BPF_ALU_SUB];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_SUB | BPF_K:
		op = op_table[BPF_ALU_SUB];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_MUL | BPF_X:
		op = op_table[BPF_ALU_MUL];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_MUL | BPF_K:
		op = op_table[BPF_ALU_MUL];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_DIV | BPF_X:
		op = op_table[BPF_ALU_DIV];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_DIV | BPF_K:
		op = op_table[BPF_ALU_DIV];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_MOD | BPF_X:
		op = op_table[BPF_ALU_MOD];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_MOD | BPF_K:
		op = op_table[BPF_ALU_MOD];
		fmt = "#%d";
		अवरोध;
	हाल BPF_ALU_AND | BPF_X:
		op = op_table[BPF_ALU_AND];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_AND | BPF_K:
		op = op_table[BPF_ALU_AND];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_ALU_OR | BPF_X:
		op = op_table[BPF_ALU_OR];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_OR | BPF_K:
		op = op_table[BPF_ALU_OR];
		fmt = "#%#x";
		अवरोध;
	हाल BPF_ALU_XOR | BPF_X:
		op = op_table[BPF_ALU_XOR];
		fmt = "x";
		अवरोध;
	हाल BPF_ALU_XOR | BPF_K:
		op = op_table[BPF_ALU_XOR];
		fmt = "#%#x";
		अवरोध;
	शेष:
		op = "nosup";
		fmt = "%#x";
		val = f.code;
		अवरोध;
	पूर्ण

	स_रखो(buf, 0, माप(buf));
	snम_लिखो(buf, माप(buf), fmt, val);
	buf[माप(buf) - 1] = 0;

	अगर ((BPF_CLASS(f.code) == BPF_JMP && BPF_OP(f.code) != BPF_JA))
		rl_म_लिखो("l%d:\t%s %s, l%d, l%d\n", i, op, buf,
			  i + 1 + f.jt, i + 1 + f.jf);
	अन्यथा
		rl_म_लिखो("l%d:\t%s %s\n", i, op, buf);
पूर्ण

अटल व्योम bpf_dump_curr(काष्ठा bpf_regs *r, काष्ठा sock_filter *f)
अणु
	पूर्णांक i, m = 0;

	rl_म_लिखो("pc:       [%u]\n", r->Pc);
	rl_म_लिखो("code:     [%u] jt[%u] jf[%u] k[%u]\n",
		  f->code, f->jt, f->jf, f->k);
	rl_म_लिखो("curr:     ");
	bpf_disयंत्र(*f, r->Pc);

	अगर (f->jt || f->jf) अणु
		rl_म_लिखो("jt:       ");
		bpf_disयंत्र(*(f + f->jt + 1), r->Pc + f->jt + 1);
		rl_म_लिखो("jf:       ");
		bpf_disयंत्र(*(f + f->jf + 1), r->Pc + f->jf + 1);
	पूर्ण

	rl_म_लिखो("A:        [%#08x][%u]\n", r->A, r->A);
	rl_म_लिखो("X:        [%#08x][%u]\n", r->X, r->X);
	अगर (r->Rs)
		rl_म_लिखो("ret:      [%#08x][%u]!\n", r->R, r->R);

	क्रम (i = 0; i < BPF_MEMWORDS; i++) अणु
		अगर (r->M[i]) अणु
			m++;
			rl_म_लिखो("M[%d]: [%#08x][%u]\n", i, r->M[i], r->M[i]);
		पूर्ण
	पूर्ण
	अगर (m == 0)
		rl_म_लिखो("M[0,%d]:  [%#08x][%u]\n", BPF_MEMWORDS - 1, 0, 0);
पूर्ण

अटल व्योम bpf_dump_pkt(uपूर्णांक8_t *pkt, uपूर्णांक32_t pkt_caplen, uपूर्णांक32_t pkt_len)
अणु
	अगर (pkt_caplen != pkt_len)
		rl_म_लिखो("cap: %u, len: %u\n", pkt_caplen, pkt_len);
	अन्यथा
		rl_म_लिखो("len: %u\n", pkt_len);

	hex_dump(pkt, pkt_caplen);
पूर्ण

अटल व्योम bpf_disयंत्र_all(स्थिर काष्ठा sock_filter *f, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		bpf_disयंत्र(f[i], i);
पूर्ण

अटल व्योम bpf_dump_all(स्थिर काष्ठा sock_filter *f, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	rl_म_लिखो("/* { op, jt, jf, k }, */\n");
	क्रम (i = 0; i < len; i++)
		rl_म_लिखो("{ %#04x, %2u, %2u, %#010x },\n",
			  f[i].code, f[i].jt, f[i].jf, f[i].k);
पूर्ण

अटल bool bpf_runnable(काष्ठा sock_filter *f, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक sock, ret, i;
	काष्ठा sock_fprog bpf = अणु
		.filter = f,
		.len = len,
	पूर्ण;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (sock < 0) अणु
		rl_म_लिखो("cannot open socket!\n");
		वापस false;
	पूर्ण
	ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, माप(bpf));
	बंद(sock);
	अगर (ret < 0) अणु
		rl_म_लिखो("program not allowed to run by kernel!\n");
		वापस false;
	पूर्ण
	क्रम (i = 0; i < len; i++) अणु
		अगर (BPF_CLASS(f[i].code) == BPF_LD &&
		    f[i].k > SKF_AD_OFF) अणु
			rl_म_लिखो("extensions currently not supported!\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम bpf_reset_अवरोधpoपूर्णांकs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < array_size(bpf_अवरोधpoपूर्णांकs); i++)
		bpf_अवरोधpoपूर्णांकs[i] = -1;
पूर्ण

अटल व्योम bpf_set_अवरोधpoपूर्णांकs(अचिन्हित पूर्णांक where)
अणु
	पूर्णांक i;
	bool set = false;

	क्रम (i = 0; i < array_size(bpf_अवरोधpoपूर्णांकs); i++) अणु
		अगर (bpf_अवरोधpoपूर्णांकs[i] == (पूर्णांक) where) अणु
			rl_म_लिखो("breakpoint already set!\n");
			set = true;
			अवरोध;
		पूर्ण

		अगर (bpf_अवरोधpoपूर्णांकs[i] == -1 && set == false) अणु
			bpf_अवरोधpoपूर्णांकs[i] = where;
			set = true;
		पूर्ण
	पूर्ण

	अगर (!set)
		rl_म_लिखो("too many breakpoints set, reset first!\n");
पूर्ण

अटल व्योम bpf_dump_अवरोधpoपूर्णांकs(व्योम)
अणु
	पूर्णांक i;

	rl_म_लिखो("breakpoints: ");

	क्रम (i = 0; i < array_size(bpf_अवरोधpoपूर्णांकs); i++) अणु
		अगर (bpf_अवरोधpoपूर्णांकs[i] < 0)
			जारी;
		rl_म_लिखो("%d ", bpf_अवरोधpoपूर्णांकs[i]);
	पूर्ण

	rl_म_लिखो("\n");
पूर्ण

अटल व्योम bpf_reset(व्योम)
अणु
	bpf_regs_len = 0;

	स_रखो(bpf_regs, 0, माप(bpf_regs));
	स_रखो(&bpf_curr, 0, माप(bpf_curr));
पूर्ण

अटल व्योम bpf_safe_regs(व्योम)
अणु
	स_नकल(&bpf_regs[bpf_regs_len++], &bpf_curr, माप(bpf_curr));
पूर्ण

अटल bool bpf_restore_regs(पूर्णांक off)
अणु
	अचिन्हित पूर्णांक index = bpf_regs_len - 1 + off;

	अगर (index == 0) अणु
		bpf_reset();
		वापस true;
	पूर्ण अन्यथा अगर (index < bpf_regs_len) अणु
		स_नकल(&bpf_curr, &bpf_regs[index], माप(bpf_curr));
		bpf_regs_len = index;
		वापस true;
	पूर्ण अन्यथा अणु
		rl_म_लिखो("reached bottom of register history stack!\n");
		वापस false;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t extract_u32(uपूर्णांक8_t *pkt, uपूर्णांक32_t off)
अणु
	uपूर्णांक32_t r;

	स_नकल(&r, &pkt[off], माप(r));

	वापस ntohl(r);
पूर्ण

अटल uपूर्णांक16_t extract_u16(uपूर्णांक8_t *pkt, uपूर्णांक32_t off)
अणु
	uपूर्णांक16_t r;

	स_नकल(&r, &pkt[off], माप(r));

	वापस ntohs(r);
पूर्ण

अटल uपूर्णांक8_t extract_u8(uपूर्णांक8_t *pkt, uपूर्णांक32_t off)
अणु
	वापस pkt[off];
पूर्ण

अटल व्योम set_वापस(काष्ठा bpf_regs *r)
अणु
	r->R = 0;
	r->Rs = true;
पूर्ण

अटल व्योम bpf_single_step(काष्ठा bpf_regs *r, काष्ठा sock_filter *f,
			    uपूर्णांक8_t *pkt, uपूर्णांक32_t pkt_caplen,
			    uपूर्णांक32_t pkt_len)
अणु
	uपूर्णांक32_t K = f->k;
	पूर्णांक d;

	चयन (f->code) अणु
	हाल BPF_RET | BPF_K:
		r->R = K;
		r->Rs = true;
		अवरोध;
	हाल BPF_RET | BPF_A:
		r->R = r->A;
		r->Rs = true;
		अवरोध;
	हाल BPF_RET | BPF_X:
		r->R = r->X;
		r->Rs = true;
		अवरोध;
	हाल BPF_MISC_TAX:
		r->X = r->A;
		अवरोध;
	हाल BPF_MISC_TXA:
		r->A = r->X;
		अवरोध;
	हाल BPF_ST:
		r->M[K] = r->A;
		अवरोध;
	हाल BPF_STX:
		r->M[K] = r->X;
		अवरोध;
	हाल BPF_LD_W | BPF_ABS:
		d = pkt_caplen - K;
		अगर (d >= माप(uपूर्णांक32_t))
			r->A = extract_u32(pkt, K);
		अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LD_H | BPF_ABS:
		d = pkt_caplen - K;
		अगर (d >= माप(uपूर्णांक16_t))
			r->A = extract_u16(pkt, K);
		अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LD_B | BPF_ABS:
		d = pkt_caplen - K;
		अगर (d >= माप(uपूर्णांक8_t))
			r->A = extract_u8(pkt, K);
		अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LD_W | BPF_IND:
		d = pkt_caplen - (r->X + K);
		अगर (d >= माप(uपूर्णांक32_t))
			r->A = extract_u32(pkt, r->X + K);
		अवरोध;
	हाल BPF_LD_H | BPF_IND:
		d = pkt_caplen - (r->X + K);
		अगर (d >= माप(uपूर्णांक16_t))
			r->A = extract_u16(pkt, r->X + K);
		अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LD_B | BPF_IND:
		d = pkt_caplen - (r->X + K);
		अगर (d >= माप(uपूर्णांक8_t))
			r->A = extract_u8(pkt, r->X + K);
		अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LDX_B | BPF_MSH:
		d = pkt_caplen - K;
		अगर (d >= माप(uपूर्णांक8_t)) अणु
			r->X = extract_u8(pkt, K);
			r->X = (r->X & 0xf) << 2;
		पूर्ण अन्यथा
			set_वापस(r);
		अवरोध;
	हाल BPF_LD_W | BPF_LEN:
		r->A = pkt_len;
		अवरोध;
	हाल BPF_LDX_W | BPF_LEN:
		r->A = pkt_len;
		अवरोध;
	हाल BPF_LD | BPF_IMM:
		r->A = K;
		अवरोध;
	हाल BPF_LDX | BPF_IMM:
		r->X = K;
		अवरोध;
	हाल BPF_LD | BPF_MEM:
		r->A = r->M[K];
		अवरोध;
	हाल BPF_LDX | BPF_MEM:
		r->X = r->M[K];
		अवरोध;
	हाल BPF_JMP_JA:
		r->Pc += K;
		अवरोध;
	हाल BPF_JMP_JGT | BPF_X:
		r->Pc += r->A > r->X ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JGT | BPF_K:
		r->Pc += r->A > K ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JGE | BPF_X:
		r->Pc += r->A >= r->X ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JGE | BPF_K:
		r->Pc += r->A >= K ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JEQ | BPF_X:
		r->Pc += r->A == r->X ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JEQ | BPF_K:
		r->Pc += r->A == K ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JSET | BPF_X:
		r->Pc += r->A & r->X ? f->jt : f->jf;
		अवरोध;
	हाल BPF_JMP_JSET | BPF_K:
		r->Pc += r->A & K ? f->jt : f->jf;
		अवरोध;
	हाल BPF_ALU_NEG:
		r->A = -r->A;
		अवरोध;
	हाल BPF_ALU_LSH | BPF_X:
		r->A <<= r->X;
		अवरोध;
	हाल BPF_ALU_LSH | BPF_K:
		r->A <<= K;
		अवरोध;
	हाल BPF_ALU_RSH | BPF_X:
		r->A >>= r->X;
		अवरोध;
	हाल BPF_ALU_RSH | BPF_K:
		r->A >>= K;
		अवरोध;
	हाल BPF_ALU_ADD | BPF_X:
		r->A += r->X;
		अवरोध;
	हाल BPF_ALU_ADD | BPF_K:
		r->A += K;
		अवरोध;
	हाल BPF_ALU_SUB | BPF_X:
		r->A -= r->X;
		अवरोध;
	हाल BPF_ALU_SUB | BPF_K:
		r->A -= K;
		अवरोध;
	हाल BPF_ALU_MUL | BPF_X:
		r->A *= r->X;
		अवरोध;
	हाल BPF_ALU_MUL | BPF_K:
		r->A *= K;
		अवरोध;
	हाल BPF_ALU_DIV | BPF_X:
	हाल BPF_ALU_MOD | BPF_X:
		अगर (r->X == 0) अणु
			set_वापस(r);
			अवरोध;
		पूर्ण
		जाओ करो_भाग;
	हाल BPF_ALU_DIV | BPF_K:
	हाल BPF_ALU_MOD | BPF_K:
		अगर (K == 0) अणु
			set_वापस(r);
			अवरोध;
		पूर्ण
करो_भाग:
		चयन (f->code) अणु
		हाल BPF_ALU_DIV | BPF_X:
			r->A /= r->X;
			अवरोध;
		हाल BPF_ALU_DIV | BPF_K:
			r->A /= K;
			अवरोध;
		हाल BPF_ALU_MOD | BPF_X:
			r->A %= r->X;
			अवरोध;
		हाल BPF_ALU_MOD | BPF_K:
			r->A %= K;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BPF_ALU_AND | BPF_X:
		r->A &= r->X;
		अवरोध;
	हाल BPF_ALU_AND | BPF_K:
		r->A &= K;
		अवरोध;
	हाल BPF_ALU_OR | BPF_X:
		r->A |= r->X;
		अवरोध;
	हाल BPF_ALU_OR | BPF_K:
		r->A |= K;
		अवरोध;
	हाल BPF_ALU_XOR | BPF_X:
		r->A ^= r->X;
		अवरोध;
	हाल BPF_ALU_XOR | BPF_K:
		r->A ^= K;
		अवरोध;
	पूर्ण
पूर्ण

अटल bool bpf_pc_has_अवरोधpoपूर्णांक(uपूर्णांक16_t pc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < array_size(bpf_अवरोधpoपूर्णांकs); i++) अणु
		अगर (bpf_अवरोधpoपूर्णांकs[i] < 0)
			जारी;
		अगर (bpf_अवरोधpoपूर्णांकs[i] == pc)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool bpf_handle_अवरोधpoपूर्णांक(काष्ठा bpf_regs *r, काष्ठा sock_filter *f,
				  uपूर्णांक8_t *pkt, uपूर्णांक32_t pkt_caplen,
				  uपूर्णांक32_t pkt_len)
अणु
	rl_म_लिखो("-- register dump --\n");
	bpf_dump_curr(r, &f[r->Pc]);
	rl_म_लिखो("-- packet dump --\n");
	bpf_dump_pkt(pkt, pkt_caplen, pkt_len);
	rl_म_लिखो("(breakpoint)\n");
	वापस true;
पूर्ण

अटल पूर्णांक bpf_run_all(काष्ठा sock_filter *f, uपूर्णांक16_t bpf_len, uपूर्णांक8_t *pkt,
		       uपूर्णांक32_t pkt_caplen, uपूर्णांक32_t pkt_len)
अणु
	bool stop = false;

	जबतक (bpf_curr.Rs == false && stop == false) अणु
		bpf_safe_regs();

		अगर (bpf_pc_has_अवरोधpoपूर्णांक(bpf_curr.Pc))
			stop = bpf_handle_अवरोधpoपूर्णांक(&bpf_curr, f, pkt,
						     pkt_caplen, pkt_len);

		bpf_single_step(&bpf_curr, &f[bpf_curr.Pc], pkt, pkt_caplen,
				pkt_len);
		bpf_curr.Pc++;
	पूर्ण

	वापस stop ? -1 : bpf_curr.R;
पूर्ण

अटल पूर्णांक bpf_run_stepping(काष्ठा sock_filter *f, uपूर्णांक16_t bpf_len,
			    uपूर्णांक8_t *pkt, uपूर्णांक32_t pkt_caplen,
			    uपूर्णांक32_t pkt_len, पूर्णांक next)
अणु
	bool stop = false;
	पूर्णांक i = 1;

	जबतक (!bpf_curr.Rs && !stop) अणु
		bpf_safe_regs();

		अगर (i++ == next)
			stop = bpf_handle_अवरोधpoपूर्णांक(&bpf_curr, f, pkt,
						     pkt_caplen, pkt_len);

		bpf_single_step(&bpf_curr, &f[bpf_curr.Pc], pkt, pkt_caplen,
				pkt_len);
		bpf_curr.Pc++;
	पूर्ण

	वापस stop ? -1 : bpf_curr.R;
पूर्ण

अटल bool pcap_loaded(व्योम)
अणु
	अगर (pcap_fd < 0)
		rl_म_लिखो("no pcap file loaded!\n");

	वापस pcap_fd >= 0;
पूर्ण

अटल काष्ठा pcap_pkthdr *pcap_curr_pkt(व्योम)
अणु
	वापस (व्योम *) pcap_ptr_va_curr;
पूर्ण

अटल bool pcap_next_pkt(व्योम)
अणु
	काष्ठा pcap_pkthdr *hdr = pcap_curr_pkt();

	अगर (pcap_ptr_va_curr + माप(*hdr) -
	    pcap_ptr_बहु_शुरू >= pcap_map_size)
		वापस false;
	अगर (hdr->caplen == 0 || hdr->len == 0 || hdr->caplen > hdr->len)
		वापस false;
	अगर (pcap_ptr_va_curr + माप(*hdr) + hdr->caplen -
	    pcap_ptr_बहु_शुरू >= pcap_map_size)
		वापस false;

	pcap_ptr_va_curr += (माप(*hdr) + hdr->caplen);
	वापस true;
पूर्ण

अटल व्योम pcap_reset_pkt(व्योम)
अणु
	pcap_ptr_va_curr = pcap_ptr_बहु_शुरू + माप(काष्ठा pcap_filehdr);
पूर्ण

अटल पूर्णांक try_load_pcap(स्थिर अक्षर *file)
अणु
	काष्ठा pcap_filehdr *hdr;
	काष्ठा stat sb;
	पूर्णांक ret;

	pcap_fd = खोलो(file, O_RDONLY);
	अगर (pcap_fd < 0) अणु
		rl_म_लिखो("cannot open pcap [%s]!\n", म_त्रुटि(त्रुटि_सं));
		वापस CMD_ERR;
	पूर्ण

	ret = ख_स्थिति(pcap_fd, &sb);
	अगर (ret < 0) अणु
		rl_म_लिखो("cannot fstat pcap file!\n");
		वापस CMD_ERR;
	पूर्ण

	अगर (!S_ISREG(sb.st_mode)) अणु
		rl_म_लिखो("not a regular pcap file, duh!\n");
		वापस CMD_ERR;
	पूर्ण

	pcap_map_size = sb.st_size;
	अगर (pcap_map_size <= माप(काष्ठा pcap_filehdr)) अणु
		rl_म_लिखो("pcap file too small!\n");
		वापस CMD_ERR;
	पूर्ण

	pcap_ptr_बहु_शुरू = mmap(शून्य, pcap_map_size, PROT_READ,
				 MAP_SHARED | MAP_LOCKED, pcap_fd, 0);
	अगर (pcap_ptr_बहु_शुरू == MAP_FAILED) अणु
		rl_म_लिखो("mmap of file failed!");
		वापस CMD_ERR;
	पूर्ण

	hdr = (व्योम *) pcap_ptr_बहु_शुरू;
	अगर (hdr->magic != TCPDUMP_MAGIC) अणु
		rl_म_लिखो("wrong pcap magic!\n");
		वापस CMD_ERR;
	पूर्ण

	pcap_reset_pkt();

	वापस CMD_OK;

पूर्ण

अटल व्योम try_बंद_pcap(व्योम)
अणु
	अगर (pcap_fd >= 0) अणु
		munmap(pcap_ptr_बहु_शुरू, pcap_map_size);
		बंद(pcap_fd);

		pcap_ptr_बहु_शुरू = pcap_ptr_va_curr = शून्य;
		pcap_map_size = 0;
		pcap_packet = 0;
		pcap_fd = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक cmd_load_bpf(अक्षर *bpf_string)
अणु
	अक्षर sp, *token, separator = ',';
	अचिन्हित लघु bpf_len, i = 0;
	काष्ठा sock_filter पंचांगp;

	bpf_prog_len = 0;
	स_रखो(bpf_image, 0, माप(bpf_image));

	अगर (माला_पूछो(bpf_string, "%hu%c", &bpf_len, &sp) != 2 ||
	    sp != separator || bpf_len > BPF_MAXINSNS || bpf_len == 0) अणु
		rl_म_लिखो("syntax error in head length encoding!\n");
		वापस CMD_ERR;
	पूर्ण

	token = bpf_string;
	जबतक ((token = म_अक्षर(token, separator)) && (++token)[0]) अणु
		अगर (i >= bpf_len) अणु
			rl_म_लिखो("program exceeds encoded length!\n");
			वापस CMD_ERR;
		पूर्ण

		अगर (माला_पूछो(token, "%hu %hhu %hhu %u,",
			   &पंचांगp.code, &पंचांगp.jt, &पंचांगp.jf, &पंचांगp.k) != 4) अणु
			rl_म_लिखो("syntax error at instruction %d!\n", i);
			वापस CMD_ERR;
		पूर्ण

		bpf_image[i].code = पंचांगp.code;
		bpf_image[i].jt = पंचांगp.jt;
		bpf_image[i].jf = पंचांगp.jf;
		bpf_image[i].k = पंचांगp.k;

		i++;
	पूर्ण

	अगर (i != bpf_len) अणु
		rl_म_लिखो("syntax error exceeding encoded length!\n");
		वापस CMD_ERR;
	पूर्ण अन्यथा
		bpf_prog_len = bpf_len;
	अगर (!bpf_runnable(bpf_image, bpf_prog_len))
		bpf_prog_len = 0;

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_load_pcap(अक्षर *file)
अणु
	अक्षर *file_trim, *पंचांगp;

	file_trim = म_मोहर_r(file, " ", &पंचांगp);
	अगर (file_trim == शून्य)
		वापस CMD_ERR;

	try_बंद_pcap();

	वापस try_load_pcap(file_trim);
पूर्ण

अटल पूर्णांक cmd_load(अक्षर *arg)
अणु
	अक्षर *subcmd, *cont = शून्य, *पंचांगp = strdup(arg);
	पूर्णांक ret = CMD_OK;

	subcmd = म_मोहर_r(पंचांगp, " ", &cont);
	अगर (subcmd == शून्य)
		जाओ out;
	अगर (matches(subcmd, "bpf") == 0) अणु
		bpf_reset();
		bpf_reset_अवरोधpoपूर्णांकs();

		अगर (!cont)
			ret = CMD_ERR;
		अन्यथा
			ret = cmd_load_bpf(cont);
	पूर्ण अन्यथा अगर (matches(subcmd, "pcap") == 0) अणु
		ret = cmd_load_pcap(cont);
	पूर्ण अन्यथा अणु
out:
		rl_म_लिखो("bpf <code>:  load bpf code\n");
		rl_म_लिखो("pcap <file>: load pcap file\n");
		ret = CMD_ERR;
	पूर्ण

	मुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक cmd_step(अक्षर *num)
अणु
	काष्ठा pcap_pkthdr *hdr;
	पूर्णांक steps, ret;

	अगर (!bpf_prog_loaded() || !pcap_loaded())
		वापस CMD_ERR;

	steps = म_से_दीर्घ(num, शून्य, 10);
	अगर (steps == 0 || म_माप(num) == 0)
		steps = 1;
	अगर (steps < 0) अणु
		अगर (!bpf_restore_regs(steps))
			वापस CMD_ERR;
		steps = 1;
	पूर्ण

	hdr = pcap_curr_pkt();
	ret = bpf_run_stepping(bpf_image, bpf_prog_len,
			       (uपूर्णांक8_t *) hdr + माप(*hdr),
			       hdr->caplen, hdr->len, steps);
	अगर (ret >= 0 || bpf_curr.Rs) अणु
		bpf_reset();
		अगर (!pcap_next_pkt()) अणु
			rl_म_लिखो("(going back to first packet)\n");
			pcap_reset_pkt();
		पूर्ण अन्यथा अणु
			rl_म_लिखो("(next packet)\n");
		पूर्ण
	पूर्ण

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_select(अक्षर *num)
अणु
	अचिन्हित पूर्णांक which, i;
	bool have_next = true;

	अगर (!pcap_loaded() || म_माप(num) == 0)
		वापस CMD_ERR;

	which = म_से_अदीर्घ(num, शून्य, 10);
	अगर (which == 0) अणु
		rl_म_लिखो("packet count starts with 1, clamping!\n");
		which = 1;
	पूर्ण

	pcap_reset_pkt();
	bpf_reset();

	क्रम (i = 0; i < which && (have_next = pcap_next_pkt()); i++)
		/* noop */;
	अगर (!have_next || pcap_curr_pkt() == शून्य) अणु
		rl_म_लिखो("no packet #%u available!\n", which);
		pcap_reset_pkt();
		वापस CMD_ERR;
	पूर्ण

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_अवरोधpoपूर्णांक(अक्षर *subcmd)
अणु
	अगर (!bpf_prog_loaded())
		वापस CMD_ERR;
	अगर (म_माप(subcmd) == 0)
		bpf_dump_अवरोधpoपूर्णांकs();
	अन्यथा अगर (matches(subcmd, "reset") == 0)
		bpf_reset_अवरोधpoपूर्णांकs();
	अन्यथा अणु
		अचिन्हित पूर्णांक where = म_से_अदीर्घ(subcmd, शून्य, 10);

		अगर (where < bpf_prog_len) अणु
			bpf_set_अवरोधpoपूर्णांकs(where);
			rl_म_लिखो("breakpoint at: ");
			bpf_disयंत्र(bpf_image[where], where);
		पूर्ण
	पूर्ण

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_run(अक्षर *num)
अणु
	अटल uपूर्णांक32_t pass, fail;
	bool has_limit = true;
	पूर्णांक pkts = 0, i = 0;

	अगर (!bpf_prog_loaded() || !pcap_loaded())
		वापस CMD_ERR;

	pkts = म_से_दीर्घ(num, शून्य, 10);
	अगर (pkts == 0 || म_माप(num) == 0)
		has_limit = false;

	करो अणु
		काष्ठा pcap_pkthdr *hdr = pcap_curr_pkt();
		पूर्णांक ret = bpf_run_all(bpf_image, bpf_prog_len,
				      (uपूर्णांक8_t *) hdr + माप(*hdr),
				      hdr->caplen, hdr->len);
		अगर (ret > 0)
			pass++;
		अन्यथा अगर (ret == 0)
			fail++;
		अन्यथा
			वापस CMD_OK;
		bpf_reset();
	पूर्ण जबतक (pcap_next_pkt() && (!has_limit || (++i < pkts)));

	rl_म_लिखो("bpf passes:%u fails:%u\n", pass, fail);

	pcap_reset_pkt();
	bpf_reset();

	pass = fail = 0;
	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_disassemble(अक्षर *line_string)
अणु
	bool single_line = false;
	अचिन्हित दीर्घ line;

	अगर (!bpf_prog_loaded())
		वापस CMD_ERR;
	अगर (म_माप(line_string) > 0 &&
	    (line = म_से_अदीर्घ(line_string, शून्य, 10)) < bpf_prog_len)
		single_line = true;
	अगर (single_line)
		bpf_disयंत्र(bpf_image[line], line);
	अन्यथा
		bpf_disयंत्र_all(bpf_image, bpf_prog_len);

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_dump(अक्षर *करोntcare)
अणु
	अगर (!bpf_prog_loaded())
		वापस CMD_ERR;

	bpf_dump_all(bpf_image, bpf_prog_len);

	वापस CMD_OK;
पूर्ण

अटल पूर्णांक cmd_quit(अक्षर *करोntcare)
अणु
	वापस CMD_EX;
पूर्ण

अटल स्थिर काष्ठा shell_cmd cmds[] = अणु
	अणु .name = "load", .func = cmd_load पूर्ण,
	अणु .name = "select", .func = cmd_select पूर्ण,
	अणु .name = "step", .func = cmd_step पूर्ण,
	अणु .name = "run", .func = cmd_run पूर्ण,
	अणु .name = "breakpoint", .func = cmd_अवरोधpoपूर्णांक पूर्ण,
	अणु .name = "disassemble", .func = cmd_disassemble पूर्ण,
	अणु .name = "dump", .func = cmd_dump पूर्ण,
	अणु .name = "quit", .func = cmd_quit पूर्ण,
पूर्ण;

अटल पूर्णांक execf(अक्षर *arg)
अणु
	अक्षर *cmd, *cont, *पंचांगp = strdup(arg);
	पूर्णांक i, ret = 0, len;

	cmd = म_मोहर_r(पंचांगp, " ", &cont);
	अगर (cmd == शून्य)
		जाओ out;
	len = म_माप(cmd);
	क्रम (i = 0; i < array_size(cmds); i++) अणु
		अगर (len != म_माप(cmds[i].name))
			जारी;
		अगर (म_भेदन(cmds[i].name, cmd, len) == 0) अणु
			ret = cmds[i].func(cont);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	मुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल अक्षर *shell_comp_gen(स्थिर अक्षर *buf, पूर्णांक state)
अणु
	अटल पूर्णांक list_index, len;

	अगर (!state) अणु
		list_index = 0;
		len = म_माप(buf);
	पूर्ण

	क्रम (; list_index < array_size(cmds); ) अणु
		स्थिर अक्षर *name = cmds[list_index].name;

		list_index++;
		अगर (म_भेदन(name, buf, len) == 0)
			वापस strdup(name);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अक्षर **shell_completion(स्थिर अक्षर *buf, पूर्णांक start, पूर्णांक end)
अणु
	अक्षर **matches = शून्य;

	अगर (start == 0)
		matches = rl_completion_matches(buf, shell_comp_gen);

	वापस matches;
पूर्ण

अटल व्योम पूर्णांकr_shell(पूर्णांक sig)
अणु
	अगर (rl_end)
		rl_समाप्त_line(-1, 0);

	rl_crlf();
	rl_refresh_line(0, 0);
	rl_मुक्त_line_state();
पूर्ण

अटल व्योम init_shell(खाता *fin, खाता *fout)
अणु
	अक्षर file[128];

	snम_लिखो(file, माप(file), "%s/.bpf_dbg_history", दो_पर्या("HOME"));
	पढ़ो_history(file);

	rl_instream = fin;
	rl_outstream = fout;

	rl_पढ़ोline_name = "bpf_dbg";
	rl_terminal_name = दो_पर्या("TERM");

	rl_catch_संकेतs = 0;
	rl_catch_sigwinch = 1;

	rl_attempted_completion_function = shell_completion;

	rl_bind_key('\t', rl_complete);

	rl_bind_key_in_map('\t', rl_complete, emacs_meta_keymap);
	rl_bind_key_in_map('\033', rl_complete, emacs_meta_keymap);

	snम_लिखो(file, माप(file), "%s/.bpf_dbg_init", दो_पर्या("HOME"));
	rl_पढ़ो_init_file(file);

	rl_prep_terminal(0);
	rl_set_संकेतs();

	संकेत(संक_विघ्न, पूर्णांकr_shell);
पूर्ण

अटल व्योम निकास_shell(खाता *fin, खाता *fout)
अणु
	अक्षर file[128];

	snम_लिखो(file, माप(file), "%s/.bpf_dbg_history", दो_पर्या("HOME"));
	ग_लिखो_history(file);

	clear_history();
	rl_deprep_terminal();

	try_बंद_pcap();

	अगर (fin != मानक_निवेश)
		ख_बंद(fin);
	अगर (fout != मानक_निकास)
		ख_बंद(fout);
पूर्ण

अटल पूर्णांक run_shell_loop(खाता *fin, खाता *fout)
अणु
	अक्षर *buf;

	init_shell(fin, fout);

	जबतक ((buf = पढ़ोline("> ")) != शून्य) अणु
		पूर्णांक ret = execf(buf);
		अगर (ret == CMD_EX)
			अवरोध;
		अगर (ret == CMD_OK && म_माप(buf) > 0)
			add_history(buf);

		मुक्त(buf);
	पूर्ण

	निकास_shell(fin, fout);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	खाता *fin = शून्य, *fout = शून्य;

	अगर (argc >= 2)
		fin = ख_खोलो(argv[1], "r");
	अगर (argc >= 3)
		fout = ख_खोलो(argv[2], "w");

	वापस run_shell_loop(fin ? : मानक_निवेश, fout ? : मानक_निकास);
पूर्ण
