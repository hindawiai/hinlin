<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/a.out.h>

अटल पूर्णांक load_binary(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा exec *eh = (काष्ठा exec *)bprm->buf;
	अचिन्हित दीर्घ loader;
	काष्ठा file *file;
	पूर्णांक retval;

	अगर (eh->fh.f_magic != 0x183 || (eh->fh.f_flags & 0x3000) != 0x3000)
		वापस -ENOEXEC;

	अगर (bprm->loader)
		वापस -ENOEXEC;

	loader = bprm->vma->vm_end - माप(व्योम *);

	file = खोलो_exec("/sbin/loader");
	retval = PTR_ERR(file);
	अगर (IS_ERR(file))
		वापस retval;

	/* Remember अगर the application is TASO.  */
	bprm->taso = eh->ah.entry < 0x100000000UL;

	bprm->पूर्णांकerpreter = file;
	bprm->loader = loader;
	वापस 0;
पूर्ण

अटल काष्ठा linux_binfmt loader_क्रमmat = अणु
	.load_binary	= load_binary,
पूर्ण;

अटल पूर्णांक __init init_loader_binfmt(व्योम)
अणु
	insert_binfmt(&loader_क्रमmat);
	वापस 0;
पूर्ण
arch_initcall(init_loader_binfmt);
