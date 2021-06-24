<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Memory Protection Keys management
 * Copyright (c) 2015, Intel Corporation.
 */
#समावेश <linux/debugfs.h>		/* debugfs_create_u32()		*/
#समावेश <linux/mm_types.h>             /* mm_काष्ठा, vma, etc...       */
#समावेश <linux/pkeys.h>                /* PKEY_*                       */
#समावेश <uapi/यंत्र-generic/mman-common.h>

#समावेश <यंत्र/cpufeature.h>             /* boot_cpu_has, ...            */
#समावेश <यंत्र/mmu_context.h>            /* vma_pkey()                   */
#समावेश <यंत्र/fpu/पूर्णांकernal.h>		/* init_fpstate			*/

पूर्णांक __execute_only_pkey(काष्ठा mm_काष्ठा *mm)
अणु
	bool need_to_set_mm_pkey = false;
	पूर्णांक execute_only_pkey = mm->context.execute_only_pkey;
	पूर्णांक ret;

	/* Do we need to assign a pkey क्रम mm's execute-only maps? */
	अगर (execute_only_pkey == -1) अणु
		/* Go allocate one to use, which might fail */
		execute_only_pkey = mm_pkey_alloc(mm);
		अगर (execute_only_pkey < 0)
			वापस -1;
		need_to_set_mm_pkey = true;
	पूर्ण

	/*
	 * We करो not want to go through the relatively costly
	 * dance to set PKRU अगर we करो not need to.  Check it
	 * first and assume that अगर the execute-only pkey is
	 * ग_लिखो-disabled that we करो not have to set it
	 * ourselves.
	 */
	अगर (!need_to_set_mm_pkey &&
	    !__pkru_allows_पढ़ो(पढ़ो_pkru(), execute_only_pkey)) अणु
		वापस execute_only_pkey;
	पूर्ण

	/*
	 * Set up PKRU so that it denies access क्रम everything
	 * other than execution.
	 */
	ret = arch_set_user_pkey_access(current, execute_only_pkey,
			PKEY_DISABLE_ACCESS);
	/*
	 * If the PKRU-set operation failed somehow, just वापस
	 * 0 and effectively disable execute-only support.
	 */
	अगर (ret) अणु
		mm_set_pkey_मुक्त(mm, execute_only_pkey);
		वापस -1;
	पूर्ण

	/* We got one, store it and use it from here on out */
	अगर (need_to_set_mm_pkey)
		mm->context.execute_only_pkey = execute_only_pkey;
	वापस execute_only_pkey;
पूर्ण

अटल अंतरभूत bool vma_is_pkey_exec_only(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Do this check first since the vm_flags should be hot */
	अगर ((vma->vm_flags & VM_ACCESS_FLAGS) != VM_EXEC)
		वापस false;
	अगर (vma_pkey(vma) != vma->vm_mm->context.execute_only_pkey)
		वापस false;

	वापस true;
पूर्ण

/*
 * This is only called क्रम *plain* mprotect calls.
 */
पूर्णांक __arch_override_mprotect_pkey(काष्ठा vm_area_काष्ठा *vma, पूर्णांक prot, पूर्णांक pkey)
अणु
	/*
	 * Is this an mprotect_pkey() call?  If so, never
	 * override the value that came from the user.
	 */
	अगर (pkey != -1)
		वापस pkey;

	/*
	 * The mapping is execute-only.  Go try to get the
	 * execute-only protection key.  If we fail to करो that,
	 * fall through as अगर we करो not have execute-only
	 * support in this mm.
	 */
	अगर (prot == PROT_EXEC) अणु
		pkey = execute_only_pkey(vma->vm_mm);
		अगर (pkey > 0)
			वापस pkey;
	पूर्ण अन्यथा अगर (vma_is_pkey_exec_only(vma)) अणु
		/*
		 * Protections are *not* PROT_EXEC, but the mapping
		 * is using the exec-only pkey.  This mapping was
		 * PROT_EXEC and will no दीर्घer be.  Move back to
		 * the शेष pkey.
		 */
		वापस ARCH_DEFAULT_PKEY;
	पूर्ण

	/*
	 * This is a vanilla, non-pkey mprotect (or we failed to
	 * setup execute-only), inherit the pkey from the VMA we
	 * are working on.
	 */
	वापस vma_pkey(vma);
पूर्ण

#घोषणा PKRU_AD_KEY(pkey)	(PKRU_AD_BIT << ((pkey) * PKRU_BITS_PER_PKEY))

/*
 * Make the शेष PKRU value (at execve() समय) as restrictive
 * as possible.  This ensures that any thपढ़ोs clone()'d early
 * in the process's lअगरeसमय will not accidentally get access
 * to data which is pkey-रक्षित later on.
 */
u32 init_pkru_value = PKRU_AD_KEY( 1) | PKRU_AD_KEY( 2) | PKRU_AD_KEY( 3) |
		      PKRU_AD_KEY( 4) | PKRU_AD_KEY( 5) | PKRU_AD_KEY( 6) |
		      PKRU_AD_KEY( 7) | PKRU_AD_KEY( 8) | PKRU_AD_KEY( 9) |
		      PKRU_AD_KEY(10) | PKRU_AD_KEY(11) | PKRU_AD_KEY(12) |
		      PKRU_AD_KEY(13) | PKRU_AD_KEY(14) | PKRU_AD_KEY(15);

/*
 * Called from the FPU code when creating a fresh set of FPU
 * रेजिस्टरs.  This is called from a very specअगरic context where
 * we know the FPU रेजिस्टरs are safe क्रम use and we can use PKRU
 * directly.
 */
व्योम copy_init_pkru_to_fpregs(व्योम)
अणु
	u32 init_pkru_value_snapshot = READ_ONCE(init_pkru_value);
	/*
	 * Override the PKRU state that came from 'init_fpstate'
	 * with the baseline from the process.
	 */
	ग_लिखो_pkru(init_pkru_value_snapshot);
पूर्ण

अटल sमाप_प्रकार init_pkru_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "0x%x\n", init_pkru_value);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार init_pkru_ग_लिखो_file(काष्ठा file *file,
		 स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pkru_state *pk;
	अक्षर buf[32];
	sमाप_प्रकार len;
	u32 new_init_pkru;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	/* Make the buffer a valid string that we can not overrun */
	buf[len] = '\0';
	अगर (kstrtouपूर्णांक(buf, 0, &new_init_pkru))
		वापस -EINVAL;

	/*
	 * Don't allow insane settings that will blow the प्रणाली
	 * up immediately अगर someone attempts to disable access
	 * or ग_लिखोs to pkey 0.
	 */
	अगर (new_init_pkru & (PKRU_AD_BIT|PKRU_WD_BIT))
		वापस -EINVAL;

	WRITE_ONCE(init_pkru_value, new_init_pkru);
	pk = get_xsave_addr(&init_fpstate.xsave, XFEATURE_PKRU);
	अगर (!pk)
		वापस -EINVAL;
	pk->pkru = new_init_pkru;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_init_pkru = अणु
	.पढ़ो = init_pkru_पढ़ो_file,
	.ग_लिखो = init_pkru_ग_लिखो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक __init create_init_pkru_value(व्योम)
अणु
	debugfs_create_file("init_pkru", S_IRUSR | S_IWUSR,
			arch_debugfs_dir, शून्य, &fops_init_pkru);
	वापस 0;
पूर्ण
late_initcall(create_init_pkru_value);

अटल __init पूर्णांक setup_init_pkru(अक्षर *opt)
अणु
	u32 new_init_pkru;

	अगर (kstrtouपूर्णांक(opt, 0, &new_init_pkru))
		वापस 1;

	WRITE_ONCE(init_pkru_value, new_init_pkru);

	वापस 1;
पूर्ण
__setup("init_pkru=", setup_init_pkru);
