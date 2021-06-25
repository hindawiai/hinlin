<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/binfmt_em86.c
 *
 *  Based on linux/fs/binfmt_script.c
 *  Copyright (C) 1996  Martin von Lथघwis
 *  original #!-checking implemented by tytso.
 *
 *  em86 changes Copyright (C) 1997  Jim Paradis
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/binfmts.h>
#समावेश <linux/elf.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/त्रुटिसं.स>


#घोषणा EM86_INTERP	"/usr/bin/em86"
#घोषणा EM86_I_NAME	"em86"

अटल पूर्णांक load_em86(काष्ठा linux_binprm *bprm)
अणु
	स्थिर अक्षर *i_name, *i_arg;
	अक्षर *पूर्णांकerp;
	काष्ठा file * file;
	पूर्णांक retval;
	काष्ठा elfhdr	elf_ex;

	/* Make sure this is a Linux/Intel ELF executable... */
	elf_ex = *((काष्ठा elfhdr *)bprm->buf);

	अगर (स_भेद(elf_ex.e_ident, ELFMAG, SELFMAG) != 0)
		वापस  -ENOEXEC;

	/* First of all, some simple consistency checks */
	अगर ((elf_ex.e_type != ET_EXEC && elf_ex.e_type != ET_DYN) ||
		(!((elf_ex.e_machine == EM_386) || (elf_ex.e_machine == EM_486))) ||
		!bprm->file->f_op->mmap) अणु
			वापस -ENOEXEC;
	पूर्ण

	/* Need to be able to load the file after exec */
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		वापस -ENOENT;

	/* Unlike in the script हाल, we करोn't have to करो any hairy
	 * parsing to find our पूर्णांकerpreter... it's hardcoded!
	 */
	पूर्णांकerp = EM86_INTERP;
	i_name = EM86_I_NAME;
	i_arg = शून्य;		/* We reserve the right to add an arg later */

	/*
	 * Splice in (1) the पूर्णांकerpreter's name क्रम argv[0]
	 *           (2) (optional) argument to पूर्णांकerpreter
	 *           (3) filename of emulated file (replace argv[0])
	 *
	 * This is करोne in reverse order, because of how the
	 * user environment and arguments are stored.
	 */
	हटाओ_arg_zero(bprm);
	retval = copy_string_kernel(bprm->filename, bprm);
	अगर (retval < 0) वापस retval; 
	bprm->argc++;
	अगर (i_arg) अणु
		retval = copy_string_kernel(i_arg, bprm);
		अगर (retval < 0) वापस retval; 
		bprm->argc++;
	पूर्ण
	retval = copy_string_kernel(i_name, bprm);
	अगर (retval < 0)	वापस retval;
	bprm->argc++;

	/*
	 * OK, now restart the process with the पूर्णांकerpreter's inode.
	 * Note that we use खोलो_exec() as the name is now in kernel
	 * space, and we करोn't need to copy it.
	 */
	file = खोलो_exec(पूर्णांकerp);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	bprm->पूर्णांकerpreter = file;
	वापस 0;
पूर्ण

अटल काष्ठा linux_binfmt em86_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_em86,
पूर्ण;

अटल पूर्णांक __init init_em86_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&em86_क्रमmat);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_em86_binfmt(व्योम)
अणु
	unरेजिस्टर_binfmt(&em86_क्रमmat);
पूर्ण

core_initcall(init_em86_binfmt);
module_निकास(निकास_em86_binfmt);
MODULE_LICENSE("GPL");
