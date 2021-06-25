<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/****************************************************************************/
/*
 *  linux/fs/binfmt_flat.c
 *
 *	Copyright (C) 2000-2003 David McCullough <davidm@snapgear.com>
 *	Copyright (C) 2002 Greg Ungerer <gerg@snapgear.com>
 *	Copyright (C) 2002 SnapGear, by Paul Dale <pauli@snapgear.com>
 *	Copyright (C) 2000, 2001 Lineo, by David McCullough <davidm@lineo.com>
 *  based heavily on:
 *
 *  linux/fs/binfmt_aout.c:
 *      Copyright (C) 1991, 1992, 1996  Linus Torvalds
 *  linux/fs/binfmt_flat.c क्रम 2.0 kernel
 *	    Copyright (C) 1998  Kenneth Albanowski <kjahds@kjahds.com>
 *	JAN/99 -- coded full program relocation (gerg@snapgear.com)
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/slab.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/personality.h>
#समावेश <linux/init.h>
#समावेश <linux/flat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/flat.h>

#अगर_अघोषित flat_get_relocate_addr
#घोषणा flat_get_relocate_addr(rel)	(rel)
#पूर्ण_अगर

/****************************************************************************/

/*
 * User data (data section and bss) needs to be aligned.
 * We pick 0x20 here because it is the max value elf2flt has always
 * used in producing FLAT files, and because it seems to be large
 * enough to make all the gcc alignment related tests happy.
 */
#घोषणा FLAT_DATA_ALIGN	(0x20)

/*
 * User data (stack) also needs to be aligned.
 * Here we can be a bit looser than the data sections since this
 * needs to only meet arch ABI requirements.
 */
#घोषणा FLAT_STACK_ALIGN	max_t(अचिन्हित दीर्घ, माप(व्योम *), ARCH_SLAB_MINALIGN)

#घोषणा RELOC_FAILED 0xff00ff01		/* Relocation incorrect somewhere */
#घोषणा UNLOADED_LIB 0x7ff000ff		/* Placeholder क्रम unused library */

#अगर_घोषित CONFIG_BINFMT_SHARED_FLAT
#घोषणा	MAX_SHARED_LIBS			(4)
#अन्यथा
#घोषणा	MAX_SHARED_LIBS			(1)
#पूर्ण_अगर

#अगर_घोषित CONFIG_BINFMT_FLAT_NO_DATA_START_OFFSET
#घोषणा DATA_START_OFFSET_WORDS		(0)
#अन्यथा
#घोषणा DATA_START_OFFSET_WORDS		(MAX_SHARED_LIBS)
#पूर्ण_अगर

काष्ठा lib_info अणु
	काष्ठा अणु
		अचिन्हित दीर्घ start_code;		/* Start of text segment */
		अचिन्हित दीर्घ start_data;		/* Start of data segment */
		अचिन्हित दीर्घ start_brk;		/* End of data segment */
		अचिन्हित दीर्घ text_len;			/* Length of text segment */
		अचिन्हित दीर्घ entry;			/* Start address क्रम this module */
		अचिन्हित दीर्घ build_date;		/* When this one was compiled */
		bool loaded;				/* Has this library been loaded? */
	पूर्ण lib_list[MAX_SHARED_LIBS];
पूर्ण;

#अगर_घोषित CONFIG_BINFMT_SHARED_FLAT
अटल पूर्णांक load_flat_shared_library(पूर्णांक id, काष्ठा lib_info *p);
#पूर्ण_अगर

अटल पूर्णांक load_flat_binary(काष्ठा linux_binprm *);
अटल पूर्णांक flat_core_dump(काष्ठा coredump_params *cprm);

अटल काष्ठा linux_binfmt flat_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_flat_binary,
	.core_dump	= flat_core_dump,
	.min_coredump	= PAGE_SIZE
पूर्ण;

/****************************************************************************/
/*
 * Routine ग_लिखोs a core dump image in the current directory.
 * Currently only a stub-function.
 */

अटल पूर्णांक flat_core_dump(काष्ठा coredump_params *cprm)
अणु
	pr_warn("Process %s:%d received signr %d and should have core dumped\n",
		current->comm, current->pid, cprm->siginfo->si_signo);
	वापस 1;
पूर्ण

/****************************************************************************/
/*
 * create_flat_tables() parses the env- and arg-strings in new user
 * memory and creates the poपूर्णांकer tables from them, and माला_दो their
 * addresses on the "stack", recording the new stack poपूर्णांकer value.
 */

अटल पूर्णांक create_flat_tables(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ arg_start)
अणु
	अक्षर __user *p;
	अचिन्हित दीर्घ __user *sp;
	दीर्घ i, len;

	p = (अक्षर __user *)arg_start;
	sp = (अचिन्हित दीर्घ __user *)current->mm->start_stack;

	sp -= bprm->envc + 1;
	sp -= bprm->argc + 1;
	अगर (IS_ENABLED(CONFIG_BINFMT_FLAT_ARGVP_ENVP_ON_STACK))
		sp -= 2; /* argvp + envp */
	sp -= 1;  /* &argc */

	current->mm->start_stack = (अचिन्हित दीर्घ)sp & -FLAT_STACK_ALIGN;
	sp = (अचिन्हित दीर्घ __user *)current->mm->start_stack;

	अगर (put_user(bprm->argc, sp++))
		वापस -EFAULT;
	अगर (IS_ENABLED(CONFIG_BINFMT_FLAT_ARGVP_ENVP_ON_STACK)) अणु
		अचिन्हित दीर्घ argv, envp;
		argv = (अचिन्हित दीर्घ)(sp + 2);
		envp = (अचिन्हित दीर्घ)(sp + 2 + bprm->argc + 1);
		अगर (put_user(argv, sp++) || put_user(envp, sp++))
			वापस -EFAULT;
	पूर्ण

	current->mm->arg_start = (अचिन्हित दीर्घ)p;
	क्रम (i = bprm->argc; i > 0; i--) अणु
		अगर (put_user((अचिन्हित दीर्घ)p, sp++))
			वापस -EFAULT;
		len = strnlen_user(p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(0, sp++))
		वापस -EFAULT;
	current->mm->arg_end = (अचिन्हित दीर्घ)p;

	current->mm->env_start = (अचिन्हित दीर्घ) p;
	क्रम (i = bprm->envc; i > 0; i--) अणु
		अगर (put_user((अचिन्हित दीर्घ)p, sp++))
			वापस -EFAULT;
		len = strnlen_user(p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(0, sp++))
		वापस -EFAULT;
	current->mm->env_end = (अचिन्हित दीर्घ)p;

	वापस 0;
पूर्ण

/****************************************************************************/

#अगर_घोषित CONFIG_BINFMT_ZFLAT

#समावेश <linux/zlib.h>

#घोषणा Lबफ_मानE	4000

/* gzip flag byte */
#घोषणा ASCII_FLAG   0x01 /* bit 0 set: file probably ASCII text */
#घोषणा CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#घोषणा EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#घोषणा ORIG_NAME    0x08 /* bit 3 set: original file name present */
#घोषणा COMMENT      0x10 /* bit 4 set: file comment present */
#घोषणा ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#घोषणा RESERVED     0xC0 /* bit 6,7:   reserved */

अटल पूर्णांक decompress_exec(काष्ठा linux_binprm *bprm, loff_t fpos, अक्षर *dst,
		दीर्घ len, पूर्णांक fd)
अणु
	अचिन्हित अक्षर *buf;
	z_stream strm;
	पूर्णांक ret, retval;

	pr_debug("decompress_exec(offset=%llx,buf=%p,len=%lx)\n", fpos, dst, len);

	स_रखो(&strm, 0, माप(strm));
	strm.workspace = kदो_स्मृति(zlib_inflate_workspacesize(), GFP_KERNEL);
	अगर (!strm.workspace)
		वापस -ENOMEM;

	buf = kदो_स्मृति(Lबफ_मानE, GFP_KERNEL);
	अगर (!buf) अणु
		retval = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* Read in first chunk of data and parse gzip header. */
	ret = kernel_पढ़ो(bprm->file, buf, Lबफ_मानE, &fpos);

	strm.next_in = buf;
	strm.avail_in = ret;
	strm.total_in = 0;

	retval = -ENOEXEC;

	/* Check minimum size -- gzip header */
	अगर (ret < 10) अणु
		pr_debug("file too small?\n");
		जाओ out_मुक्त_buf;
	पूर्ण

	/* Check gzip magic number */
	अगर ((buf[0] != 037) || ((buf[1] != 0213) && (buf[1] != 0236))) अणु
		pr_debug("unknown compression magic?\n");
		जाओ out_मुक्त_buf;
	पूर्ण

	/* Check gzip method */
	अगर (buf[2] != 8) अणु
		pr_debug("unknown compression method?\n");
		जाओ out_मुक्त_buf;
	पूर्ण
	/* Check gzip flags */
	अगर ((buf[3] & ENCRYPTED) || (buf[3] & CONTINUATION) ||
	    (buf[3] & RESERVED)) अणु
		pr_debug("unknown flags?\n");
		जाओ out_मुक्त_buf;
	पूर्ण

	ret = 10;
	अगर (buf[3] & EXTRA_FIELD) अणु
		ret += 2 + buf[10] + (buf[11] << 8);
		अगर (unlikely(ret >= Lबफ_मानE)) अणु
			pr_debug("buffer overflow (EXTRA)?\n");
			जाओ out_मुक्त_buf;
		पूर्ण
	पूर्ण
	अगर (buf[3] & ORIG_NAME) अणु
		जबतक (ret < Lबफ_मानE && buf[ret++] != 0)
			;
		अगर (unlikely(ret == Lबफ_मानE)) अणु
			pr_debug("buffer overflow (ORIG_NAME)?\n");
			जाओ out_मुक्त_buf;
		पूर्ण
	पूर्ण
	अगर (buf[3] & COMMENT) अणु
		जबतक (ret < Lबफ_मानE && buf[ret++] != 0)
			;
		अगर (unlikely(ret == Lबफ_मानE)) अणु
			pr_debug("buffer overflow (COMMENT)?\n");
			जाओ out_मुक्त_buf;
		पूर्ण
	पूर्ण

	strm.next_in += ret;
	strm.avail_in -= ret;

	strm.next_out = dst;
	strm.avail_out = len;
	strm.total_out = 0;

	अगर (zlib_inflateInit2(&strm, -MAX_WBITS) != Z_OK) अणु
		pr_debug("zlib init failed?\n");
		जाओ out_मुक्त_buf;
	पूर्ण

	जबतक ((ret = zlib_inflate(&strm, Z_NO_FLUSH)) == Z_OK) अणु
		ret = kernel_पढ़ो(bprm->file, buf, Lबफ_मानE, &fpos);
		अगर (ret <= 0)
			अवरोध;
		len -= ret;

		strm.next_in = buf;
		strm.avail_in = ret;
		strm.total_in = 0;
	पूर्ण

	अगर (ret < 0) अणु
		pr_debug("decompression failed (%d), %s\n",
			ret, strm.msg);
		जाओ out_zlib;
	पूर्ण

	retval = 0;
out_zlib:
	zlib_inflateEnd(&strm);
out_मुक्त_buf:
	kमुक्त(buf);
out_मुक्त:
	kमुक्त(strm.workspace);
	वापस retval;
पूर्ण

#पूर्ण_अगर /* CONFIG_BINFMT_ZFLAT */

/****************************************************************************/

अटल अचिन्हित दीर्घ
calc_reloc(अचिन्हित दीर्घ r, काष्ठा lib_info *p, पूर्णांक curid, पूर्णांक पूर्णांकernalp)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक id;
	अचिन्हित दीर्घ start_brk;
	अचिन्हित दीर्घ start_data;
	अचिन्हित दीर्घ text_len;
	अचिन्हित दीर्घ start_code;

#अगर_घोषित CONFIG_BINFMT_SHARED_FLAT
	अगर (r == 0)
		id = curid;	/* Relocs of 0 are always self referring */
	अन्यथा अणु
		id = (r >> 24) & 0xff;	/* Find ID क्रम this reloc */
		r &= 0x00ffffff;	/* Trim ID off here */
	पूर्ण
	अगर (id >= MAX_SHARED_LIBS) अणु
		pr_err("reference 0x%lx to shared library %d", r, id);
		जाओ failed;
	पूर्ण
	अगर (curid != id) अणु
		अगर (पूर्णांकernalp) अणु
			pr_err("reloc address 0x%lx not in same module "
			       "(%d != %d)", r, curid, id);
			जाओ failed;
		पूर्ण अन्यथा अगर (!p->lib_list[id].loaded &&
			   load_flat_shared_library(id, p) < 0) अणु
			pr_err("failed to load library %d", id);
			जाओ failed;
		पूर्ण
		/* Check versioning inक्रमmation (i.e. समय stamps) */
		अगर (p->lib_list[id].build_date && p->lib_list[curid].build_date &&
				p->lib_list[curid].build_date < p->lib_list[id].build_date) अणु
			pr_err("library %d is younger than %d", id, curid);
			जाओ failed;
		पूर्ण
	पूर्ण
#अन्यथा
	id = 0;
#पूर्ण_अगर

	start_brk = p->lib_list[id].start_brk;
	start_data = p->lib_list[id].start_data;
	start_code = p->lib_list[id].start_code;
	text_len = p->lib_list[id].text_len;

	अगर (r > start_brk - start_data + text_len) अणु
		pr_err("reloc outside program 0x%lx (0 - 0x%lx/0x%lx)",
		       r, start_brk-start_data+text_len, text_len);
		जाओ failed;
	पूर्ण

	अगर (r < text_len)			/* In text segment */
		addr = r + start_code;
	अन्यथा					/* In data segment */
		addr = r - text_len + start_data;

	/* Range checked alपढ़ोy above so करोing the range tests is redundant...*/
	वापस addr;

failed:
	pr_cont(", killing %s!\n", current->comm);
	send_sig(संक_अंश, current, 0);

	वापस RELOC_FAILED;
पूर्ण

/****************************************************************************/

#अगर_घोषित CONFIG_BINFMT_FLAT_OLD
अटल व्योम old_reloc(अचिन्हित दीर्घ rl)
अणु
	अटल स्थिर अक्षर *segment[] = अणु "TEXT", "DATA", "BSS", "*UNKNOWN*" पूर्ण;
	flat_v2_reloc_t	r;
	अचिन्हित दीर्घ __user *ptr;
	अचिन्हित दीर्घ val;

	r.value = rl;
#अगर defined(CONFIG_COLDFIRE)
	ptr = (अचिन्हित दीर्घ __user *)(current->mm->start_code + r.reloc.offset);
#अन्यथा
	ptr = (अचिन्हित दीर्घ __user *)(current->mm->start_data + r.reloc.offset);
#पूर्ण_अगर
	get_user(val, ptr);

	pr_debug("Relocation of variable at DATASEG+%x "
		 "(address %p, currently %lx) into segment %s\n",
		 r.reloc.offset, ptr, val, segment[r.reloc.type]);

	चयन (r.reloc.type) अणु
	हाल OLD_FLAT_RELOC_TYPE_TEXT:
		val += current->mm->start_code;
		अवरोध;
	हाल OLD_FLAT_RELOC_TYPE_DATA:
		val += current->mm->start_data;
		अवरोध;
	हाल OLD_FLAT_RELOC_TYPE_BSS:
		val += current->mm->end_data;
		अवरोध;
	शेष:
		pr_err("Unknown relocation type=%x\n", r.reloc.type);
		अवरोध;
	पूर्ण
	put_user(val, ptr);

	pr_debug("Relocation became %lx\n", val);
पूर्ण
#पूर्ण_अगर /* CONFIG_BINFMT_FLAT_OLD */

/****************************************************************************/

अटल पूर्णांक load_flat_file(काष्ठा linux_binprm *bprm,
		काष्ठा lib_info *libinfo, पूर्णांक id, अचिन्हित दीर्घ *extra_stack)
अणु
	काष्ठा flat_hdr *hdr;
	अचिन्हित दीर्घ textpos, datapos, realdatastart;
	u32 text_len, data_len, bss_len, stack_len, full_data, flags;
	अचिन्हित दीर्घ len, memp, memp_size, extra, rlim;
	__be32 __user *reloc;
	u32 __user *rp;
	पूर्णांक i, rev, relocs;
	loff_t fpos;
	अचिन्हित दीर्घ start_code, end_code;
	sमाप_प्रकार result;
	पूर्णांक ret;

	hdr = ((काष्ठा flat_hdr *) bprm->buf);		/* exec-header */

	text_len  = ntohl(hdr->data_start);
	data_len  = ntohl(hdr->data_end) - ntohl(hdr->data_start);
	bss_len   = ntohl(hdr->bss_end) - ntohl(hdr->data_end);
	stack_len = ntohl(hdr->stack_size);
	अगर (extra_stack) अणु
		stack_len += *extra_stack;
		*extra_stack = stack_len;
	पूर्ण
	relocs    = ntohl(hdr->reloc_count);
	flags     = ntohl(hdr->flags);
	rev       = ntohl(hdr->rev);
	full_data = data_len + relocs * माप(अचिन्हित दीर्घ);

	अगर (म_भेदन(hdr->magic, "bFLT", 4)) अणु
		/*
		 * Previously, here was a prपूर्णांकk to tell people
		 *   "BINFMT_FLAT: bad header magic".
		 * But क्रम the kernel which also use ELF FD-PIC क्रमmat, this
		 * error message is confusing.
		 * because a lot of people करो not manage to produce good
		 */
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण

	अगर (flags & FLAT_FLAG_KTRACE)
		pr_info("Loading file: %s\n", bprm->filename);

#अगर_घोषित CONFIG_BINFMT_FLAT_OLD
	अगर (rev != FLAT_VERSION && rev != OLD_FLAT_VERSION) अणु
		pr_err("bad flat file version 0x%x (supported 0x%lx and 0x%lx)\n",
		       rev, FLAT_VERSION, OLD_FLAT_VERSION);
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण

	/* Don't allow old क्रमmat executables to use shared libraries */
	अगर (rev == OLD_FLAT_VERSION && id != 0) अणु
		pr_err("shared libraries are not available before rev 0x%lx\n",
		       FLAT_VERSION);
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण

	/*
	 * fix up the flags क्रम the older क्रमmat,  there were all kinds
	 * of endian hacks,  this only works क्रम the simple हालs
	 */
	अगर (rev == OLD_FLAT_VERSION &&
	   (flags || IS_ENABLED(CONFIG_BINFMT_FLAT_OLD_ALWAYS_RAM)))
		flags = FLAT_FLAG_RAM;

#अन्यथा /* CONFIG_BINFMT_FLAT_OLD */
	अगर (rev != FLAT_VERSION) अणु
		pr_err("bad flat file version 0x%x (supported 0x%lx)\n",
		       rev, FLAT_VERSION);
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण
#पूर्ण_अगर /* !CONFIG_BINFMT_FLAT_OLD */

	/*
	 * Make sure the header params are sane.
	 * 28 bits (256 MB) is way more than reasonable in this हाल.
	 * If some top bits are set we have probable binary corruption.
	*/
	अगर ((text_len | data_len | bss_len | stack_len | full_data) >> 28) अणु
		pr_err("bad header\n");
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण

#अगर_अघोषित CONFIG_BINFMT_ZFLAT
	अगर (flags & (FLAT_FLAG_GZIP|FLAT_FLAG_GZDATA)) अणु
		pr_err("Support for ZFLAT executables is not enabled.\n");
		ret = -ENOEXEC;
		जाओ err;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Check initial limits. This aव्योमs letting people circumvent
	 * size limits imposed on them by creating programs with large
	 * arrays in the data or bss.
	 */
	rlim = rlimit(RLIMIT_DATA);
	अगर (rlim >= RLIM_अनन्त)
		rlim = ~0;
	अगर (data_len + bss_len > rlim) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Flush all traces of the currently running executable */
	अगर (id == 0) अणु
		ret = begin_new_exec(bprm);
		अगर (ret)
			जाओ err;

		/* OK, This is the poपूर्णांक of no वापस */
		set_personality(PER_LINUX_32BIT);
		setup_new_exec(bprm);
	पूर्ण

	/*
	 * calculate the extra space we need to map in
	 */
	extra = max_t(अचिन्हित दीर्घ, bss_len + stack_len,
			relocs * माप(अचिन्हित दीर्घ));

	/*
	 * there are a couple of हालs here,  the separate code/data
	 * हाल,  and then the fully copied to RAM हाल which lumps
	 * it all together.
	 */
	अगर (!IS_ENABLED(CONFIG_MMU) && !(flags & (FLAT_FLAG_RAM|FLAT_FLAG_GZIP))) अणु
		/*
		 * this should give us a ROM ptr,  but अगर it करोesn't we don't
		 * really care
		 */
		pr_debug("ROM mapping of file (we hope)\n");

		textpos = vm_mmap(bprm->file, 0, text_len, PROT_READ|PROT_EXEC,
				  MAP_PRIVATE|MAP_EXECUTABLE, 0);
		अगर (!textpos || IS_ERR_VALUE(textpos)) अणु
			ret = textpos;
			अगर (!textpos)
				ret = -ENOMEM;
			pr_err("Unable to mmap process text, errno %d\n", ret);
			जाओ err;
		पूर्ण

		len = data_len + extra +
			DATA_START_OFFSET_WORDS * माप(अचिन्हित दीर्घ);
		len = PAGE_ALIGN(len);
		realdatastart = vm_mmap(शून्य, 0, len,
			PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE, 0);

		अगर (realdatastart == 0 || IS_ERR_VALUE(realdatastart)) अणु
			ret = realdatastart;
			अगर (!realdatastart)
				ret = -ENOMEM;
			pr_err("Unable to allocate RAM for process data, "
			       "errno %d\n", ret);
			vm_munmap(textpos, text_len);
			जाओ err;
		पूर्ण
		datapos = ALIGN(realdatastart +
				DATA_START_OFFSET_WORDS * माप(अचिन्हित दीर्घ),
				FLAT_DATA_ALIGN);

		pr_debug("Allocated data+bss+stack (%u bytes): %lx\n",
			 data_len + bss_len + stack_len, datapos);

		fpos = ntohl(hdr->data_start);
#अगर_घोषित CONFIG_BINFMT_ZFLAT
		अगर (flags & FLAT_FLAG_GZDATA) अणु
			result = decompress_exec(bprm, fpos, (अक्षर *)datapos,
						 full_data, 0);
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			result = पढ़ो_code(bprm->file, datapos, fpos,
					full_data);
		पूर्ण
		अगर (IS_ERR_VALUE(result)) अणु
			ret = result;
			pr_err("Unable to read data+bss, errno %d\n", ret);
			vm_munmap(textpos, text_len);
			vm_munmap(realdatastart, len);
			जाओ err;
		पूर्ण

		reloc = (__be32 __user *)
			(datapos + (ntohl(hdr->reloc_start) - text_len));
		memp = realdatastart;
		memp_size = len;
	पूर्ण अन्यथा अणु

		len = text_len + data_len + extra +
			DATA_START_OFFSET_WORDS * माप(u32);
		len = PAGE_ALIGN(len);
		textpos = vm_mmap(शून्य, 0, len,
			PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE, 0);

		अगर (!textpos || IS_ERR_VALUE(textpos)) अणु
			ret = textpos;
			अगर (!textpos)
				ret = -ENOMEM;
			pr_err("Unable to allocate RAM for process text/data, "
			       "errno %d\n", ret);
			जाओ err;
		पूर्ण

		realdatastart = textpos + ntohl(hdr->data_start);
		datapos = ALIGN(realdatastart +
				DATA_START_OFFSET_WORDS * माप(u32),
				FLAT_DATA_ALIGN);

		reloc = (__be32 __user *)
			(datapos + (ntohl(hdr->reloc_start) - text_len));
		memp = textpos;
		memp_size = len;
#अगर_घोषित CONFIG_BINFMT_ZFLAT
		/*
		 * load it all in and treat it like a RAM load from now on
		 */
		अगर (flags & FLAT_FLAG_GZIP) अणु
#अगर_अघोषित CONFIG_MMU
			result = decompress_exec(bprm, माप(काष्ठा flat_hdr),
					 (((अक्षर *)textpos) + माप(काष्ठा flat_hdr)),
					 (text_len + full_data
						  - माप(काष्ठा flat_hdr)),
					 0);
			स_हटाओ((व्योम *) datapos, (व्योम *) realdatastart,
					full_data);
#अन्यथा
			/*
			 * This is used on MMU प्रणालीs मुख्यly क्रम testing.
			 * Let's use a kernel buffer to simplअगरy things.
			 */
			दीर्घ unz_text_len = text_len - माप(काष्ठा flat_hdr);
			दीर्घ unz_len = unz_text_len + full_data;
			अक्षर *unz_data = vदो_स्मृति(unz_len);
			अगर (!unz_data) अणु
				result = -ENOMEM;
			पूर्ण अन्यथा अणु
				result = decompress_exec(bprm, माप(काष्ठा flat_hdr),
							 unz_data, unz_len, 0);
				अगर (result == 0 &&
				    (copy_to_user((व्योम __user *)textpos + माप(काष्ठा flat_hdr),
						  unz_data, unz_text_len) ||
				     copy_to_user((व्योम __user *)datapos,
						  unz_data + unz_text_len, full_data)))
					result = -EFAULT;
				vमुक्त(unz_data);
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (flags & FLAT_FLAG_GZDATA) अणु
			result = पढ़ो_code(bprm->file, textpos, 0, text_len);
			अगर (!IS_ERR_VALUE(result)) अणु
#अगर_अघोषित CONFIG_MMU
				result = decompress_exec(bprm, text_len, (अक्षर *) datapos,
						 full_data, 0);
#अन्यथा
				अक्षर *unz_data = vदो_स्मृति(full_data);
				अगर (!unz_data) अणु
					result = -ENOMEM;
				पूर्ण अन्यथा अणु
					result = decompress_exec(bprm, text_len,
						       unz_data, full_data, 0);
					अगर (result == 0 &&
					    copy_to_user((व्योम __user *)datapos,
							 unz_data, full_data))
						result = -EFAULT;
					vमुक्त(unz_data);
				पूर्ण
#पूर्ण_अगर
			पूर्ण
		पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_BINFMT_ZFLAT */
		अणु
			result = पढ़ो_code(bprm->file, textpos, 0, text_len);
			अगर (!IS_ERR_VALUE(result))
				result = पढ़ो_code(bprm->file, datapos,
						   ntohl(hdr->data_start),
						   full_data);
		पूर्ण
		अगर (IS_ERR_VALUE(result)) अणु
			ret = result;
			pr_err("Unable to read code+data+bss, errno %d\n", ret);
			vm_munmap(textpos, text_len + data_len + extra +
				  DATA_START_OFFSET_WORDS * माप(u32));
			जाओ err;
		पूर्ण
	पूर्ण

	start_code = textpos + माप(काष्ठा flat_hdr);
	end_code = textpos + text_len;
	text_len -= माप(काष्ठा flat_hdr); /* the real code len */

	/* The मुख्य program needs a little extra setup in the task काष्ठाure */
	अगर (id == 0) अणु
		current->mm->start_code = start_code;
		current->mm->end_code = end_code;
		current->mm->start_data = datapos;
		current->mm->end_data = datapos + data_len;
		/*
		 * set up the brk stuff, uses any slack left in data/bss/stack
		 * allocation.  We put the brk after the bss (between the bss
		 * and stack) like other platक्रमms.
		 * Userspace code relies on the stack poपूर्णांकer starting out at
		 * an address right at the end of a page.
		 */
		current->mm->start_brk = datapos + data_len + bss_len;
		current->mm->brk = (current->mm->start_brk + 3) & ~3;
#अगर_अघोषित CONFIG_MMU
		current->mm->context.end_brk = memp + memp_size - stack_len;
#पूर्ण_अगर
	पूर्ण

	अगर (flags & FLAT_FLAG_KTRACE) अणु
		pr_info("Mapping is %lx, Entry point is %x, data_start is %x\n",
			textpos, 0x00ffffff&ntohl(hdr->entry), ntohl(hdr->data_start));
		pr_info("%s %s: TEXT=%lx-%lx DATA=%lx-%lx BSS=%lx-%lx\n",
			id ? "Lib" : "Load", bprm->filename,
			start_code, end_code, datapos, datapos + data_len,
			datapos + data_len, (datapos + data_len + bss_len + 3) & ~3);
	पूर्ण

	/* Store the current module values पूर्णांकo the global library काष्ठाure */
	libinfo->lib_list[id].start_code = start_code;
	libinfo->lib_list[id].start_data = datapos;
	libinfo->lib_list[id].start_brk = datapos + data_len + bss_len;
	libinfo->lib_list[id].text_len = text_len;
	libinfo->lib_list[id].loaded = 1;
	libinfo->lib_list[id].entry = (0x00ffffff & ntohl(hdr->entry)) + textpos;
	libinfo->lib_list[id].build_date = ntohl(hdr->build_date);

	/*
	 * We just load the allocations पूर्णांकo some temporary memory to
	 * help simplअगरy all this mumbo jumbo
	 *
	 * We've got two dअगरferent sections of relocation entries.
	 * The first is the GOT which resides at the beginning of the data segment
	 * and is terminated with a -1.  This one can be relocated in place.
	 * The second is the extra relocation entries tacked after the image's
	 * data segment. These require a little more processing as the entry is
	 * really an offset पूर्णांकo the image which contains an offset पूर्णांकo the
	 * image.
	 */
	अगर (flags & FLAT_FLAG_GOTPIC) अणु
		क्रम (rp = (u32 __user *)datapos; ; rp++) अणु
			u32 addr, rp_val;
			अगर (get_user(rp_val, rp))
				वापस -EFAULT;
			अगर (rp_val == 0xffffffff)
				अवरोध;
			अगर (rp_val) अणु
				addr = calc_reloc(rp_val, libinfo, id, 0);
				अगर (addr == RELOC_FAILED) अणु
					ret = -ENOEXEC;
					जाओ err;
				पूर्ण
				अगर (put_user(addr, rp))
					वापस -EFAULT;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Now run through the relocation entries.
	 * We've got to be careful here as C++ produces relocatable zero
	 * entries in the स्थिरructor and deकाष्ठाor tables which are then
	 * tested क्रम being not zero (which will always occur unless we're
	 * based from address zero).  This causes an endless loop as __start
	 * is at zero.  The solution used is to not relocate zero addresses.
	 * This has the negative side effect of not allowing a global data
	 * reference to be अटलally initialised to _stext (I've moved
	 * __start to address 4 so that is okay).
	 */
	अगर (rev > OLD_FLAT_VERSION) अणु
		क्रम (i = 0; i < relocs; i++) अणु
			u32 addr, relval;
			__be32 पंचांगp;

			/*
			 * Get the address of the poपूर्णांकer to be
			 * relocated (of course, the address has to be
			 * relocated first).
			 */
			अगर (get_user(पंचांगp, reloc + i))
				वापस -EFAULT;
			relval = ntohl(पंचांगp);
			addr = flat_get_relocate_addr(relval);
			rp = (u32 __user *)calc_reloc(addr, libinfo, id, 1);
			अगर (rp == (u32 __user *)RELOC_FAILED) अणु
				ret = -ENOEXEC;
				जाओ err;
			पूर्ण

			/* Get the poपूर्णांकer's value.  */
			ret = flat_get_addr_from_rp(rp, relval, flags, &addr);
			अगर (unlikely(ret))
				जाओ err;

			अगर (addr != 0) अणु
				/*
				 * Do the relocation.  PIC relocs in the data section are
				 * alपढ़ोy in target order
				 */
				अगर ((flags & FLAT_FLAG_GOTPIC) == 0) अणु
					/*
					 * Meh, the same value can have a dअगरferent
					 * byte order based on a flag..
					 */
					addr = ntohl((__क्रमce __be32)addr);
				पूर्ण
				addr = calc_reloc(addr, libinfo, id, 0);
				अगर (addr == RELOC_FAILED) अणु
					ret = -ENOEXEC;
					जाओ err;
				पूर्ण

				/* Write back the relocated poपूर्णांकer.  */
				ret = flat_put_addr_at_rp(rp, addr, relval);
				अगर (unlikely(ret))
					जाओ err;
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_BINFMT_FLAT_OLD
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < relocs; i++) अणु
			__be32 relval;
			अगर (get_user(relval, reloc + i))
				वापस -EFAULT;
			old_reloc(ntohl(relval));
		पूर्ण
#पूर्ण_अगर /* CONFIG_BINFMT_FLAT_OLD */
	पूर्ण

	flush_icache_user_range(start_code, end_code);

	/* zero the BSS,  BRK and stack areas */
	अगर (clear_user((व्योम __user *)(datapos + data_len), bss_len +
		       (memp + memp_size - stack_len -		/* end brk */
		       libinfo->lib_list[id].start_brk) +	/* start brk */
		       stack_len))
		वापस -EFAULT;

	वापस 0;
err:
	वापस ret;
पूर्ण


/****************************************************************************/
#अगर_घोषित CONFIG_BINFMT_SHARED_FLAT

/*
 * Load a shared library पूर्णांकo memory.  The library माला_लो its own data
 * segment (including bss) but not argv/argc/environ.
 */

अटल पूर्णांक load_flat_shared_library(पूर्णांक id, काष्ठा lib_info *libs)
अणु
	/*
	 * This is a fake bprm काष्ठा; only the members "buf", "file" and
	 * "filename" are actually used.
	 */
	काष्ठा linux_binprm bprm;
	पूर्णांक res;
	अक्षर buf[16];
	loff_t pos = 0;

	स_रखो(&bprm, 0, माप(bprm));

	/* Create the file name */
	प्र_लिखो(buf, "/lib/lib%d.so", id);

	/* Open the file up */
	bprm.filename = buf;
	bprm.file = खोलो_exec(bprm.filename);
	res = PTR_ERR(bprm.file);
	अगर (IS_ERR(bprm.file))
		वापस res;

	res = kernel_पढ़ो(bprm.file, bprm.buf, BINPRM_BUF_SIZE, &pos);

	अगर (res >= 0)
		res = load_flat_file(&bprm, libs, id, शून्य);

	allow_ग_लिखो_access(bprm.file);
	fput(bprm.file);

	वापस res;
पूर्ण

#पूर्ण_अगर /* CONFIG_BINFMT_SHARED_FLAT */
/****************************************************************************/

/*
 * These are the functions used to load flat style executables and shared
 * libraries.  There is no binary dependent code anywhere अन्यथा.
 */

अटल पूर्णांक load_flat_binary(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा lib_info libinfo;
	काष्ठा pt_regs *regs = current_pt_regs();
	अचिन्हित दीर्घ stack_len = 0;
	अचिन्हित दीर्घ start_addr;
	पूर्णांक res;
	पूर्णांक i, j;

	स_रखो(&libinfo, 0, माप(libinfo));

	/*
	 * We have to add the size of our arguments to our stack size
	 * otherwise it's too easy क्रम users to create stack overflows
	 * by passing in a huge argument list.  And yes,  we have to be
	 * pedantic and include space क्रम the argv/envp array as it may have
	 * a lot of entries.
	 */
#अगर_अघोषित CONFIG_MMU
	stack_len += PAGE_SIZE * MAX_ARG_PAGES - bprm->p; /* the strings */
#पूर्ण_अगर
	stack_len += (bprm->argc + 1) * माप(अक्षर *);   /* the argv array */
	stack_len += (bprm->envc + 1) * माप(अक्षर *);   /* the envp array */
	stack_len = ALIGN(stack_len, FLAT_STACK_ALIGN);

	res = load_flat_file(bprm, &libinfo, 0, &stack_len);
	अगर (res < 0)
		वापस res;

	/* Update data segment poपूर्णांकers क्रम all libraries */
	क्रम (i = 0; i < MAX_SHARED_LIBS; i++) अणु
		अगर (!libinfo.lib_list[i].loaded)
			जारी;
		क्रम (j = 0; j < MAX_SHARED_LIBS; j++) अणु
			अचिन्हित दीर्घ val = libinfo.lib_list[j].loaded ?
				libinfo.lib_list[j].start_data : UNLOADED_LIB;
			अचिन्हित दीर्घ __user *p = (अचिन्हित दीर्घ __user *)
				libinfo.lib_list[i].start_data;
			p -= j + 1;
			अगर (put_user(val, p))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	set_binfmt(&flat_क्रमmat);

#अगर_घोषित CONFIG_MMU
	res = setup_arg_pages(bprm, STACK_TOP, EXSTACK_DEFAULT);
	अगर (!res)
		res = create_flat_tables(bprm, bprm->p);
#अन्यथा
	/* Stash our initial stack poपूर्णांकer पूर्णांकo the mm काष्ठाure */
	current->mm->start_stack =
		((current->mm->context.end_brk + stack_len + 3) & ~3) - 4;
	pr_debug("sp=%lx\n", current->mm->start_stack);

	/* copy the arg pages onto the stack */
	res = transfer_args_to_stack(bprm, &current->mm->start_stack);
	अगर (!res)
		res = create_flat_tables(bprm, current->mm->start_stack);
#पूर्ण_अगर
	अगर (res)
		वापस res;

	/* Fake some वापस addresses to ensure the call chain will
	 * initialise library in order क्रम us.  We are required to call
	 * lib 1 first, then 2, ... and finally the मुख्य program (id 0).
	 */
	start_addr = libinfo.lib_list[0].entry;

#अगर_घोषित CONFIG_BINFMT_SHARED_FLAT
	क्रम (i = MAX_SHARED_LIBS-1; i > 0; i--) अणु
		अगर (libinfo.lib_list[i].loaded) अणु
			/* Push previos first to call address */
			अचिन्हित दीर्घ __user *sp;
			current->mm->start_stack -= माप(अचिन्हित दीर्घ);
			sp = (अचिन्हित दीर्घ __user *)current->mm->start_stack;
			अगर (put_user(start_addr, sp))
				वापस -EFAULT;
			start_addr = libinfo.lib_list[i].entry;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित FLAT_PLAT_INIT
	FLAT_PLAT_INIT(regs);
#पूर्ण_अगर

	finalize_exec(bprm);
	pr_debug("start_thread(regs=0x%p, entry=0x%lx, start_stack=0x%lx)\n",
		 regs, start_addr, current->mm->start_stack);
	start_thपढ़ो(regs, start_addr, current->mm->start_stack);

	वापस 0;
पूर्ण

/****************************************************************************/

अटल पूर्णांक __init init_flat_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&flat_क्रमmat);
	वापस 0;
पूर्ण
core_initcall(init_flat_binfmt);

/****************************************************************************/
