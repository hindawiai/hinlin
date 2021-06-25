<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/*
 * Based on:
 *
 * Minimal BPF JIT image disassembler
 *
 * Disassembles BPF JIT compiler emitted opcodes back to यंत्र insn's क्रम
 * debugging or verअगरication purposes.
 *
 * Copyright 2013 Daniel Borkmann <daniel@iogearbox.net>
 * Licensed under the GNU General Public License, version 2.0 (GPLv2)
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <bfd.h>
#समावेश <dis-यंत्र.h>
#समावेश <sys/स्थिति.स>
#समावेश <सीमा.स>
#समावेश <bpf/libbpf.h>

#समावेश "json_writer.h"
#समावेश "main.h"

अटल व्योम get_exec_path(अक्षर *tpath, माप_प्रकार size)
अणु
	स्थिर अक्षर *path = "/proc/self/exe";
	sमाप_प्रकार len;

	len = पढ़ोlink(path, tpath, size - 1);
	निश्चित(len > 0);
	tpath[len] = 0;
पूर्ण

अटल पूर्णांक oper_count;
अटल पूर्णांक ख_लिखो_json(व्योम *out, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *s;

	बहु_शुरू(ap, fmt);
	अगर (vaप्र_लिखो(&s, fmt, ap) < 0)
		वापस -1;
	बहु_पूर्ण(ap);

	अगर (!oper_count) अणु
		पूर्णांक i;

		/* Strip trailing spaces */
		i = म_माप(s) - 1;
		जबतक (s[i] == ' ')
			s[i--] = '\0';

		jsonw_string_field(json_wtr, "operation", s);
		jsonw_name(json_wtr, "operands");
		jsonw_start_array(json_wtr);
		oper_count++;
	पूर्ण अन्यथा अगर (!म_भेद(fmt, ",")) अणु
		   /* Skip */
	पूर्ण अन्यथा अणु
		jsonw_string(json_wtr, s);
		oper_count++;
	पूर्ण
	मुक्त(s);
	वापस 0;
पूर्ण

व्योम disयंत्र_prपूर्णांक_insn(अचिन्हित अक्षर *image, sमाप_प्रकार len, पूर्णांक opcodes,
		       स्थिर अक्षर *arch, स्थिर अक्षर *disassembler_options,
		       स्थिर काष्ठा btf *btf,
		       स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
		       __u64 func_ksym, अचिन्हित पूर्णांक func_idx,
		       bool linum)
अणु
	स्थिर काष्ठा bpf_line_info *linfo = शून्य;
	disassembler_ftype disassemble;
	काष्ठा disassemble_info info;
	अचिन्हित पूर्णांक nr_skip = 0;
	पूर्णांक count, i, pc = 0;
	अक्षर tpath[PATH_MAX];
	bfd *bfdf;

	अगर (!len)
		वापस;

	स_रखो(tpath, 0, माप(tpath));
	get_exec_path(tpath, माप(tpath));

	bfdf = bfd_खोलोr(tpath, शून्य);
	निश्चित(bfdf);
	निश्चित(bfd_check_क्रमmat(bfdf, bfd_object));

	अगर (json_output)
		init_disassemble_info(&info, मानक_निकास,
				      (ख_लिखो_ftype) ख_लिखो_json);
	अन्यथा
		init_disassemble_info(&info, मानक_निकास,
				      (ख_लिखो_ftype) ख_लिखो);

	/* Update architecture info क्रम offload. */
	अगर (arch) अणु
		स्थिर bfd_arch_info_type *inf = bfd_scan_arch(arch);

		अगर (inf) अणु
			bfdf->arch_info = inf;
		पूर्ण अन्यथा अणु
			p_err("No libbfd support for %s", arch);
			वापस;
		पूर्ण
	पूर्ण

	info.arch = bfd_get_arch(bfdf);
	info.mach = bfd_get_mach(bfdf);
	अगर (disassembler_options)
		info.disassembler_options = disassembler_options;
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

	अगर (json_output)
		jsonw_start_array(json_wtr);
	करो अणु
		अगर (prog_linfo) अणु
			linfo = bpf_prog_linfo__lfind_addr_func(prog_linfo,
								func_ksym + pc,
								func_idx,
								nr_skip);
			अगर (linfo)
				nr_skip++;
		पूर्ण

		अगर (json_output) अणु
			jsonw_start_object(json_wtr);
			oper_count = 0;
			अगर (linfo)
				btf_dump_linfo_json(btf, linfo, linum);
			jsonw_name(json_wtr, "pc");
			jsonw_म_लिखो(json_wtr, "\"0x%x\"", pc);
		पूर्ण अन्यथा अणु
			अगर (linfo)
				btf_dump_linfo_plain(btf, linfo, "; ",
						     linum);
			म_लिखो("%4x:\t", pc);
		पूर्ण

		count = disassemble(pc, &info);
		अगर (json_output) अणु
			/* Opeअक्रम array, was started in ख_लिखो_json. Beक्रमe
			 * that, make sure we have a _null_ value अगर no opeअक्रम
			 * other than operation code was present.
			 */
			अगर (oper_count == 1)
				jsonw_null(json_wtr);
			jsonw_end_array(json_wtr);
		पूर्ण

		अगर (opcodes) अणु
			अगर (json_output) अणु
				jsonw_name(json_wtr, "opcodes");
				jsonw_start_array(json_wtr);
				क्रम (i = 0; i < count; ++i)
					jsonw_म_लिखो(json_wtr, "\"0x%02hhx\"",
						     (uपूर्णांक8_t)image[pc + i]);
				jsonw_end_array(json_wtr);
			पूर्ण अन्यथा अणु
				म_लिखो("\n\t");
				क्रम (i = 0; i < count; ++i)
					म_लिखो("%02x ",
					       (uपूर्णांक8_t)image[pc + i]);
			पूर्ण
		पूर्ण
		अगर (json_output)
			jsonw_end_object(json_wtr);
		अन्यथा
			म_लिखो("\n");

		pc += count;
	पूर्ण जबतक (count > 0 && pc < len);
	अगर (json_output)
		jsonw_end_array(json_wtr);

	bfd_बंद(bfdf);
पूर्ण

पूर्णांक disयंत्र_init(व्योम)
अणु
	bfd_init();
	वापस 0;
पूर्ण
