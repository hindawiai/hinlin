<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2018 Facebook */

#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <linux/err.h>
#समावेश <linux/bpf.h>
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"

काष्ठा bpf_prog_linfo अणु
	व्योम *raw_linfo;
	व्योम *raw_jited_linfo;
	__u32 *nr_jited_linfo_per_func;
	__u32 *jited_linfo_func_idx;
	__u32 nr_linfo;
	__u32 nr_jited_func;
	__u32 rec_size;
	__u32 jited_rec_size;
पूर्ण;

अटल पूर्णांक dissect_jited_func(काष्ठा bpf_prog_linfo *prog_linfo,
			      स्थिर __u64 *ksym_func, स्थिर __u32 *ksym_len)
अणु
	__u32 nr_jited_func, nr_linfo;
	स्थिर व्योम *raw_jited_linfo;
	स्थिर __u64 *jited_linfo;
	__u64 last_jited_linfo;
	/*
	 * Index to raw_jited_linfo:
	 *      i: Index क्रम searching the next ksym_func
	 * prev_i: Index to the last found ksym_func
	 */
	__u32 i, prev_i;
	__u32 f; /* Index to ksym_func */

	raw_jited_linfo = prog_linfo->raw_jited_linfo;
	jited_linfo = raw_jited_linfo;
	अगर (ksym_func[0] != *jited_linfo)
		जाओ errout;

	prog_linfo->jited_linfo_func_idx[0] = 0;
	nr_jited_func = prog_linfo->nr_jited_func;
	nr_linfo = prog_linfo->nr_linfo;

	क्रम (prev_i = 0, i = 1, f = 1;
	     i < nr_linfo && f < nr_jited_func;
	     i++) अणु
		raw_jited_linfo += prog_linfo->jited_rec_size;
		last_jited_linfo = *jited_linfo;
		jited_linfo = raw_jited_linfo;

		अगर (ksym_func[f] == *jited_linfo) अणु
			prog_linfo->jited_linfo_func_idx[f] = i;

			/* Sanity check */
			अगर (last_jited_linfo - ksym_func[f - 1] + 1 >
			    ksym_len[f - 1])
				जाओ errout;

			prog_linfo->nr_jited_linfo_per_func[f - 1] =
				i - prev_i;
			prev_i = i;

			/*
			 * The ksym_func[f] is found in jited_linfo.
			 * Look क्रम the next one.
			 */
			f++;
		पूर्ण अन्यथा अगर (*jited_linfo <= last_jited_linfo) अणु
			/* Ensure the addr is increasing _within_ a func */
			जाओ errout;
		पूर्ण
	पूर्ण

	अगर (f != nr_jited_func)
		जाओ errout;

	prog_linfo->nr_jited_linfo_per_func[nr_jited_func - 1] =
		nr_linfo - prev_i;

	वापस 0;

errout:
	वापस -EINVAL;
पूर्ण

व्योम bpf_prog_linfo__मुक्त(काष्ठा bpf_prog_linfo *prog_linfo)
अणु
	अगर (!prog_linfo)
		वापस;

	मुक्त(prog_linfo->raw_linfo);
	मुक्त(prog_linfo->raw_jited_linfo);
	मुक्त(prog_linfo->nr_jited_linfo_per_func);
	मुक्त(prog_linfo->jited_linfo_func_idx);
	मुक्त(prog_linfo);
पूर्ण

काष्ठा bpf_prog_linfo *bpf_prog_linfo__new(स्थिर काष्ठा bpf_prog_info *info)
अणु
	काष्ठा bpf_prog_linfo *prog_linfo;
	__u32 nr_linfo, nr_jited_func;
	__u64 data_sz;

	nr_linfo = info->nr_line_info;

	अगर (!nr_linfo)
		वापस शून्य;

	/*
	 * The min size that bpf_prog_linfo has to access क्रम
	 * searching purpose.
	 */
	अगर (info->line_info_rec_size <
	    दुरत्व(काष्ठा bpf_line_info, file_name_off))
		वापस शून्य;

	prog_linfo = सुस्मृति(1, माप(*prog_linfo));
	अगर (!prog_linfo)
		वापस शून्य;

	/* Copy xlated line_info */
	prog_linfo->nr_linfo = nr_linfo;
	prog_linfo->rec_size = info->line_info_rec_size;
	data_sz = (__u64)nr_linfo * prog_linfo->rec_size;
	prog_linfo->raw_linfo = दो_स्मृति(data_sz);
	अगर (!prog_linfo->raw_linfo)
		जाओ err_मुक्त;
	स_नकल(prog_linfo->raw_linfo, (व्योम *)(दीर्घ)info->line_info, data_sz);

	nr_jited_func = info->nr_jited_ksyms;
	अगर (!nr_jited_func ||
	    !info->jited_line_info ||
	    info->nr_jited_line_info != nr_linfo ||
	    info->jited_line_info_rec_size < माप(__u64) ||
	    info->nr_jited_func_lens != nr_jited_func ||
	    !info->jited_ksyms ||
	    !info->jited_func_lens)
		/* Not enough info to provide jited_line_info */
		वापस prog_linfo;

	/* Copy jited_line_info */
	prog_linfo->nr_jited_func = nr_jited_func;
	prog_linfo->jited_rec_size = info->jited_line_info_rec_size;
	data_sz = (__u64)nr_linfo * prog_linfo->jited_rec_size;
	prog_linfo->raw_jited_linfo = दो_स्मृति(data_sz);
	अगर (!prog_linfo->raw_jited_linfo)
		जाओ err_मुक्त;
	स_नकल(prog_linfo->raw_jited_linfo,
	       (व्योम *)(दीर्घ)info->jited_line_info, data_sz);

	/* Number of jited_line_info per jited func */
	prog_linfo->nr_jited_linfo_per_func = दो_स्मृति(nr_jited_func *
						     माप(__u32));
	अगर (!prog_linfo->nr_jited_linfo_per_func)
		जाओ err_मुक्त;

	/*
	 * For each jited func,
	 * the start idx to the "linfo" and "jited_linfo" array,
	 */
	prog_linfo->jited_linfo_func_idx = दो_स्मृति(nr_jited_func *
						  माप(__u32));
	अगर (!prog_linfo->jited_linfo_func_idx)
		जाओ err_मुक्त;

	अगर (dissect_jited_func(prog_linfo,
			       (__u64 *)(दीर्घ)info->jited_ksyms,
			       (__u32 *)(दीर्घ)info->jited_func_lens))
		जाओ err_मुक्त;

	वापस prog_linfo;

err_मुक्त:
	bpf_prog_linfo__मुक्त(prog_linfo);
	वापस शून्य;
पूर्ण

स्थिर काष्ठा bpf_line_info *
bpf_prog_linfo__lfind_addr_func(स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
				__u64 addr, __u32 func_idx, __u32 nr_skip)
अणु
	__u32 jited_rec_size, rec_size, nr_linfo, start, i;
	स्थिर व्योम *raw_jited_linfo, *raw_linfo;
	स्थिर __u64 *jited_linfo;

	अगर (func_idx >= prog_linfo->nr_jited_func)
		वापस शून्य;

	nr_linfo = prog_linfo->nr_jited_linfo_per_func[func_idx];
	अगर (nr_skip >= nr_linfo)
		वापस शून्य;

	start = prog_linfo->jited_linfo_func_idx[func_idx] + nr_skip;
	jited_rec_size = prog_linfo->jited_rec_size;
	raw_jited_linfo = prog_linfo->raw_jited_linfo +
		(start * jited_rec_size);
	jited_linfo = raw_jited_linfo;
	अगर (addr < *jited_linfo)
		वापस शून्य;

	nr_linfo -= nr_skip;
	rec_size = prog_linfo->rec_size;
	raw_linfo = prog_linfo->raw_linfo + (start * rec_size);
	क्रम (i = 0; i < nr_linfo; i++) अणु
		अगर (addr < *jited_linfo)
			अवरोध;

		raw_linfo += rec_size;
		raw_jited_linfo += jited_rec_size;
		jited_linfo = raw_jited_linfo;
	पूर्ण

	वापस raw_linfo - rec_size;
पूर्ण

स्थिर काष्ठा bpf_line_info *
bpf_prog_linfo__lfind(स्थिर काष्ठा bpf_prog_linfo *prog_linfo,
		      __u32 insn_off, __u32 nr_skip)
अणु
	स्थिर काष्ठा bpf_line_info *linfo;
	__u32 rec_size, nr_linfo, i;
	स्थिर व्योम *raw_linfo;

	nr_linfo = prog_linfo->nr_linfo;
	अगर (nr_skip >= nr_linfo)
		वापस शून्य;

	rec_size = prog_linfo->rec_size;
	raw_linfo = prog_linfo->raw_linfo + (nr_skip * rec_size);
	linfo = raw_linfo;
	अगर (insn_off < linfo->insn_off)
		वापस शून्य;

	nr_linfo -= nr_skip;
	क्रम (i = 0; i < nr_linfo; i++) अणु
		अगर (insn_off < linfo->insn_off)
			अवरोध;

		raw_linfo += rec_size;
		linfo = raw_linfo;
	पूर्ण

	वापस raw_linfo - rec_size;
पूर्ण
