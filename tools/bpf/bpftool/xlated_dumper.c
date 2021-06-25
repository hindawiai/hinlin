<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#घोषणा _GNU_SOURCE
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <bpf/libbpf.h>

#समावेश "disasm.h"
#समावेश "json_writer.h"
#समावेश "main.h"
#समावेश "xlated_dumper.h"

अटल पूर्णांक kernel_syms_cmp(स्थिर व्योम *sym_a, स्थिर व्योम *sym_b)
अणु
	वापस ((काष्ठा kernel_sym *)sym_a)->address -
	       ((काष्ठा kernel_sym *)sym_b)->address;
पूर्ण

व्योम kernel_syms_load(काष्ठा dump_data *dd)
अणु
	काष्ठा kernel_sym *sym;
	अक्षर buff[256];
	व्योम *पंचांगp, *address;
	खाता *fp;

	fp = ख_खोलो("/proc/kallsyms", "r");
	अगर (!fp)
		वापस;

	जबतक (ख_माला_लो(buff, माप(buff), fp)) अणु
		पंचांगp = पुनः_स्मृतिarray(dd->sym_mapping, dd->sym_count + 1,
				   माप(*dd->sym_mapping));
		अगर (!पंचांगp) अणु
out:
			मुक्त(dd->sym_mapping);
			dd->sym_mapping = शून्य;
			ख_बंद(fp);
			वापस;
		पूर्ण
		dd->sym_mapping = पंचांगp;
		sym = &dd->sym_mapping[dd->sym_count];
		अगर (माला_पूछो(buff, "%p %*c %s", &address, sym->name) != 2)
			जारी;
		sym->address = (अचिन्हित दीर्घ)address;
		अगर (!म_भेद(sym->name, "__bpf_call_base")) अणु
			dd->address_call_base = sym->address;
			/* sysctl kernel.kptr_restrict was set */
			अगर (!sym->address)
				जाओ out;
		पूर्ण
		अगर (sym->address)
			dd->sym_count++;
	पूर्ण

	ख_बंद(fp);

	क्विक(dd->sym_mapping, dd->sym_count,
	      माप(*dd->sym_mapping), kernel_syms_cmp);
पूर्ण

व्योम kernel_syms_destroy(काष्ठा dump_data *dd)
अणु
	मुक्त(dd->sym_mapping);
पूर्ण

काष्ठा kernel_sym *kernel_syms_search(काष्ठा dump_data *dd,
				      अचिन्हित दीर्घ key)
अणु
	काष्ठा kernel_sym sym = अणु
		.address = key,
	पूर्ण;

	वापस dd->sym_mapping ?
	       द्वा_खोज(&sym, dd->sym_mapping, dd->sym_count,
		       माप(*dd->sym_mapping), kernel_syms_cmp) : शून्य;
पूर्ण

अटल व्योम __म_लिखो(2, 3) prपूर्णांक_insn(व्योम *निजी_data, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	भ_लिखो(fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल व्योम __म_लिखो(2, 3)
prपूर्णांक_insn_क्रम_graph(व्योम *निजी_data, स्थिर अक्षर *fmt, ...)
अणु
	अक्षर buf[64], *p;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	p = buf;
	जबतक (*p != '\0') अणु
		अगर (*p == '\n') अणु
			स_हटाओ(p + 3, p, म_माप(buf) + 1 - (p - buf));
			/* Align each inकाष्ठाion dump row left. */
			*p++ = '\\';
			*p++ = 'l';
			/* Output multiline concatenation. */
			*p++ = '\\';
		पूर्ण अन्यथा अगर (*p == '<' || *p == '>' || *p == '|' || *p == '&') अणु
			स_हटाओ(p + 1, p, म_माप(buf) + 1 - (p - buf));
			/* Escape special अक्षरacter. */
			*p++ = '\\';
		पूर्ण

		p++;
	पूर्ण

	म_लिखो("%s", buf);
पूर्ण

अटल व्योम __म_लिखो(2, 3)
prपूर्णांक_insn_json(व्योम *निजी_data, स्थिर अक्षर *fmt, ...)
अणु
	अचिन्हित पूर्णांक l = म_माप(fmt);
	अक्षर chomped_fmt[l];
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	अगर (l > 0) अणु
		म_नकलन(chomped_fmt, fmt, l - 1);
		chomped_fmt[l - 1] = '\0';
	पूर्ण
	jsonw_भ_लिखो_enquote(json_wtr, chomped_fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल स्थिर अक्षर *prपूर्णांक_call_pcrel(काष्ठा dump_data *dd,
				    काष्ठा kernel_sym *sym,
				    अचिन्हित दीर्घ address,
				    स्थिर काष्ठा bpf_insn *insn)
अणु
	अगर (!dd->nr_jited_ksyms)
		/* Do not show address क्रम पूर्णांकerpreted programs */
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			"%+d", insn->off);
	अन्यथा अगर (sym)
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "%+d#%s", insn->off, sym->name);
	अन्यथा
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "%+d#0x%lx", insn->off, address);
	वापस dd->scratch_buff;
पूर्ण

अटल स्थिर अक्षर *prपूर्णांक_call_helper(काष्ठा dump_data *dd,
				     काष्ठा kernel_sym *sym,
				     अचिन्हित दीर्घ address)
अणु
	अगर (sym)
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "%s", sym->name);
	अन्यथा
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "0x%lx", address);
	वापस dd->scratch_buff;
पूर्ण

अटल स्थिर अक्षर *prपूर्णांक_call(व्योम *निजी_data,
			      स्थिर काष्ठा bpf_insn *insn)
अणु
	काष्ठा dump_data *dd = निजी_data;
	अचिन्हित दीर्घ address = dd->address_call_base + insn->imm;
	काष्ठा kernel_sym *sym;

	अगर (insn->src_reg == BPF_PSEUDO_CALL &&
	    (__u32) insn->imm < dd->nr_jited_ksyms && dd->jited_ksyms)
		address = dd->jited_ksyms[insn->imm];

	sym = kernel_syms_search(dd, address);
	अगर (insn->src_reg == BPF_PSEUDO_CALL)
		वापस prपूर्णांक_call_pcrel(dd, sym, address, insn);
	अन्यथा
		वापस prपूर्णांक_call_helper(dd, sym, address);
पूर्ण

अटल स्थिर अक्षर *prपूर्णांक_imm(व्योम *निजी_data,
			     स्थिर काष्ठा bpf_insn *insn,
			     __u64 full_imm)
अणु
	काष्ठा dump_data *dd = निजी_data;

	अगर (insn->src_reg == BPF_PSEUDO_MAP_FD)
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "map[id:%u]", insn->imm);
	अन्यथा अगर (insn->src_reg == BPF_PSEUDO_MAP_VALUE)
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "map[id:%u][0]+%u", insn->imm, (insn + 1)->imm);
	अन्यथा अगर (insn->src_reg == BPF_PSEUDO_FUNC)
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "subprog[%+d]", insn->imm);
	अन्यथा
		snम_लिखो(dd->scratch_buff, माप(dd->scratch_buff),
			 "0x%llx", (अचिन्हित दीर्घ दीर्घ)full_imm);
	वापस dd->scratch_buff;
पूर्ण

व्योम dump_xlated_json(काष्ठा dump_data *dd, व्योम *buf, अचिन्हित पूर्णांक len,
		      bool opcodes, bool linum)
अणु
	स्थिर काष्ठा bpf_prog_linfo *prog_linfo = dd->prog_linfo;
	स्थिर काष्ठा bpf_insn_cbs cbs = अणु
		.cb_prपूर्णांक	= prपूर्णांक_insn_json,
		.cb_call	= prपूर्णांक_call,
		.cb_imm		= prपूर्णांक_imm,
		.निजी_data	= dd,
	पूर्ण;
	काष्ठा bpf_func_info *record;
	काष्ठा bpf_insn *insn = buf;
	काष्ठा btf *btf = dd->btf;
	bool द्विगुन_insn = false;
	अचिन्हित पूर्णांक nr_skip = 0;
	अक्षर func_sig[1024];
	अचिन्हित पूर्णांक i;

	jsonw_start_array(json_wtr);
	record = dd->func_info;
	क्रम (i = 0; i < len / माप(*insn); i++) अणु
		अगर (द्विगुन_insn) अणु
			द्विगुन_insn = false;
			जारी;
		पूर्ण
		द्विगुन_insn = insn[i].code == (BPF_LD | BPF_IMM | BPF_DW);

		jsonw_start_object(json_wtr);

		अगर (btf && record) अणु
			अगर (record->insn_off == i) अणु
				btf_dumper_type_only(btf, record->type_id,
						     func_sig,
						     माप(func_sig));
				अगर (func_sig[0] != '\0') अणु
					jsonw_name(json_wtr, "proto");
					jsonw_string(json_wtr, func_sig);
				पूर्ण
				record = (व्योम *)record + dd->finfo_rec_size;
			पूर्ण
		पूर्ण

		अगर (prog_linfo) अणु
			स्थिर काष्ठा bpf_line_info *linfo;

			linfo = bpf_prog_linfo__lfind(prog_linfo, i, nr_skip);
			अगर (linfo) अणु
				btf_dump_linfo_json(btf, linfo, linum);
				nr_skip++;
			पूर्ण
		पूर्ण

		jsonw_name(json_wtr, "disasm");
		prपूर्णांक_bpf_insn(&cbs, insn + i, true);

		अगर (opcodes) अणु
			jsonw_name(json_wtr, "opcodes");
			jsonw_start_object(json_wtr);

			jsonw_name(json_wtr, "code");
			jsonw_म_लिखो(json_wtr, "\"0x%02hhx\"", insn[i].code);

			jsonw_name(json_wtr, "src_reg");
			jsonw_म_लिखो(json_wtr, "\"0x%hhx\"", insn[i].src_reg);

			jsonw_name(json_wtr, "dst_reg");
			jsonw_म_लिखो(json_wtr, "\"0x%hhx\"", insn[i].dst_reg);

			jsonw_name(json_wtr, "off");
			prपूर्णांक_hex_data_json((uपूर्णांक8_t *)(&insn[i].off), 2);

			jsonw_name(json_wtr, "imm");
			अगर (द्विगुन_insn && i < len - 1)
				prपूर्णांक_hex_data_json((uपूर्णांक8_t *)(&insn[i].imm),
						    12);
			अन्यथा
				prपूर्णांक_hex_data_json((uपूर्णांक8_t *)(&insn[i].imm),
						    4);
			jsonw_end_object(json_wtr);
		पूर्ण
		jsonw_end_object(json_wtr);
	पूर्ण
	jsonw_end_array(json_wtr);
पूर्ण

व्योम dump_xlated_plain(काष्ठा dump_data *dd, व्योम *buf, अचिन्हित पूर्णांक len,
		       bool opcodes, bool linum)
अणु
	स्थिर काष्ठा bpf_prog_linfo *prog_linfo = dd->prog_linfo;
	स्थिर काष्ठा bpf_insn_cbs cbs = अणु
		.cb_prपूर्णांक	= prपूर्णांक_insn,
		.cb_call	= prपूर्णांक_call,
		.cb_imm		= prपूर्णांक_imm,
		.निजी_data	= dd,
	पूर्ण;
	काष्ठा bpf_func_info *record;
	काष्ठा bpf_insn *insn = buf;
	काष्ठा btf *btf = dd->btf;
	अचिन्हित पूर्णांक nr_skip = 0;
	bool द्विगुन_insn = false;
	अक्षर func_sig[1024];
	अचिन्हित पूर्णांक i;

	record = dd->func_info;
	क्रम (i = 0; i < len / माप(*insn); i++) अणु
		अगर (द्विगुन_insn) अणु
			द्विगुन_insn = false;
			जारी;
		पूर्ण

		अगर (btf && record) अणु
			अगर (record->insn_off == i) अणु
				btf_dumper_type_only(btf, record->type_id,
						     func_sig,
						     माप(func_sig));
				अगर (func_sig[0] != '\0')
					म_लिखो("%s:\n", func_sig);
				record = (व्योम *)record + dd->finfo_rec_size;
			पूर्ण
		पूर्ण

		अगर (prog_linfo) अणु
			स्थिर काष्ठा bpf_line_info *linfo;

			linfo = bpf_prog_linfo__lfind(prog_linfo, i, nr_skip);
			अगर (linfo) अणु
				btf_dump_linfo_plain(btf, linfo, "; ",
						     linum);
				nr_skip++;
			पूर्ण
		पूर्ण

		द्विगुन_insn = insn[i].code == (BPF_LD | BPF_IMM | BPF_DW);

		म_लिखो("% 4d: ", i);
		prपूर्णांक_bpf_insn(&cbs, insn + i, true);

		अगर (opcodes) अणु
			म_लिखो("       ");
			fprपूर्णांक_hex(मानक_निकास, insn + i, 8, " ");
			अगर (द्विगुन_insn && i < len - 1) अणु
				म_लिखो(" ");
				fprपूर्णांक_hex(मानक_निकास, insn + i + 1, 8, " ");
			पूर्ण
			म_लिखो("\n");
		पूर्ण
	पूर्ण
पूर्ण

व्योम dump_xlated_क्रम_graph(काष्ठा dump_data *dd, व्योम *buf_start, व्योम *buf_end,
			   अचिन्हित पूर्णांक start_idx)
अणु
	स्थिर काष्ठा bpf_insn_cbs cbs = अणु
		.cb_prपूर्णांक	= prपूर्णांक_insn_क्रम_graph,
		.cb_call	= prपूर्णांक_call,
		.cb_imm		= prपूर्णांक_imm,
		.निजी_data	= dd,
	पूर्ण;
	काष्ठा bpf_insn *insn_start = buf_start;
	काष्ठा bpf_insn *insn_end = buf_end;
	काष्ठा bpf_insn *cur = insn_start;

	क्रम (; cur <= insn_end; cur++) अणु
		म_लिखो("% 4d: ", (पूर्णांक)(cur - insn_start + start_idx));
		prपूर्णांक_bpf_insn(&cbs, cur, true);
		अगर (cur != insn_end)
			म_लिखो(" | ");
	पूर्ण
पूर्ण
