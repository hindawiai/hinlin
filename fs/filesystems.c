<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/fileप्रणालीs.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  table of configured fileप्रणालीs
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs_parser.h>

/*
 * Handling of fileप्रणाली drivers list.
 * Rules:
 *	Inclusion to/removals from/scanning of list are रक्षित by spinlock.
 *	During the unload module must call unरेजिस्टर_fileप्रणाली().
 *	We can access the fields of list element अगर:
 *		1) spinlock is held or
 *		2) we hold the reference to the module.
 *	The latter can be guaranteed by call of try_module_get(); अगर it
 *	वापसed 0 we must skip the element, otherwise we got the reference.
 *	Once the reference is obtained we can drop the spinlock.
 */

अटल काष्ठा file_प्रणाली_type *file_प्रणालीs;
अटल DEFINE_RWLOCK(file_प्रणालीs_lock);

/* WARNING: This can be used only अगर we _alपढ़ोy_ own a reference */
काष्ठा file_प्रणाली_type *get_fileप्रणाली(काष्ठा file_प्रणाली_type *fs)
अणु
	__module_get(fs->owner);
	वापस fs;
पूर्ण

व्योम put_fileप्रणाली(काष्ठा file_प्रणाली_type *fs)
अणु
	module_put(fs->owner);
पूर्ण

अटल काष्ठा file_प्रणाली_type **find_fileप्रणाली(स्थिर अक्षर *name, अचिन्हित len)
अणु
	काष्ठा file_प्रणाली_type **p;
	क्रम (p = &file_प्रणालीs; *p; p = &(*p)->next)
		अगर (म_भेदन((*p)->name, name, len) == 0 &&
		    !(*p)->name[len])
			अवरोध;
	वापस p;
पूर्ण

/**
 *	रेजिस्टर_fileप्रणाली - रेजिस्टर a new fileप्रणाली
 *	@fs: the file प्रणाली काष्ठाure
 *
 *	Adds the file प्रणाली passed to the list of file प्रणालीs the kernel
 *	is aware of क्रम mount and other syscalls. Returns 0 on success,
 *	or a negative त्रुटि_सं code on an error.
 *
 *	The &काष्ठा file_प्रणाली_type that is passed is linked पूर्णांकo the kernel 
 *	काष्ठाures and must not be मुक्तd until the file प्रणाली has been
 *	unरेजिस्टरed.
 */
 
पूर्णांक रेजिस्टर_fileप्रणाली(काष्ठा file_प्रणाली_type * fs)
अणु
	पूर्णांक res = 0;
	काष्ठा file_प्रणाली_type ** p;

	अगर (fs->parameters &&
	    !fs_validate_description(fs->name, fs->parameters))
		वापस -EINVAL;

	BUG_ON(म_अक्षर(fs->name, '.'));
	अगर (fs->next)
		वापस -EBUSY;
	ग_लिखो_lock(&file_प्रणालीs_lock);
	p = find_fileप्रणाली(fs->name, म_माप(fs->name));
	अगर (*p)
		res = -EBUSY;
	अन्यथा
		*p = fs;
	ग_लिखो_unlock(&file_प्रणालीs_lock);
	वापस res;
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_fileप्रणाली);

/**
 *	unरेजिस्टर_fileप्रणाली - unरेजिस्टर a file प्रणाली
 *	@fs: fileप्रणाली to unरेजिस्टर
 *
 *	Remove a file प्रणाली that was previously successfully रेजिस्टरed
 *	with the kernel. An error is वापसed अगर the file प्रणाली is not found.
 *	Zero is वापसed on a success.
 *	
 *	Once this function has वापसed the &काष्ठा file_प्रणाली_type काष्ठाure
 *	may be मुक्तd or reused.
 */
 
पूर्णांक unरेजिस्टर_fileप्रणाली(काष्ठा file_प्रणाली_type * fs)
अणु
	काष्ठा file_प्रणाली_type ** पंचांगp;

	ग_लिखो_lock(&file_प्रणालीs_lock);
	पंचांगp = &file_प्रणालीs;
	जबतक (*पंचांगp) अणु
		अगर (fs == *पंचांगp) अणु
			*पंचांगp = fs->next;
			fs->next = शून्य;
			ग_लिखो_unlock(&file_प्रणालीs_lock);
			synchronize_rcu();
			वापस 0;
		पूर्ण
		पंचांगp = &(*पंचांगp)->next;
	पूर्ण
	ग_लिखो_unlock(&file_प्रणालीs_lock);

	वापस -EINVAL;
पूर्ण

EXPORT_SYMBOL(unरेजिस्टर_fileप्रणाली);

#अगर_घोषित CONFIG_SYSFS_SYSCALL
अटल पूर्णांक fs_index(स्थिर अक्षर __user * __name)
अणु
	काष्ठा file_प्रणाली_type * पंचांगp;
	काष्ठा filename *name;
	पूर्णांक err, index;

	name = getname(__name);
	err = PTR_ERR(name);
	अगर (IS_ERR(name))
		वापस err;

	err = -EINVAL;
	पढ़ो_lock(&file_प्रणालीs_lock);
	क्रम (पंचांगp=file_प्रणालीs, index=0 ; पंचांगp ; पंचांगp=पंचांगp->next, index++) अणु
		अगर (म_भेद(पंचांगp->name, name->name) == 0) अणु
			err = index;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&file_प्रणालीs_lock);
	putname(name);
	वापस err;
पूर्ण

अटल पूर्णांक fs_name(अचिन्हित पूर्णांक index, अक्षर __user * buf)
अणु
	काष्ठा file_प्रणाली_type * पंचांगp;
	पूर्णांक len, res;

	पढ़ो_lock(&file_प्रणालीs_lock);
	क्रम (पंचांगp = file_प्रणालीs; पंचांगp; पंचांगp = पंचांगp->next, index--)
		अगर (index <= 0 && try_module_get(पंचांगp->owner))
			अवरोध;
	पढ़ो_unlock(&file_प्रणालीs_lock);
	अगर (!पंचांगp)
		वापस -EINVAL;

	/* OK, we got the reference, so we can safely block */
	len = म_माप(पंचांगp->name) + 1;
	res = copy_to_user(buf, पंचांगp->name, len) ? -EFAULT : 0;
	put_fileप्रणाली(पंचांगp);
	वापस res;
पूर्ण

अटल पूर्णांक fs_maxindex(व्योम)
अणु
	काष्ठा file_प्रणाली_type * पंचांगp;
	पूर्णांक index;

	पढ़ो_lock(&file_प्रणालीs_lock);
	क्रम (पंचांगp = file_प्रणालीs, index = 0 ; पंचांगp ; पंचांगp = पंचांगp->next, index++)
		;
	पढ़ो_unlock(&file_प्रणालीs_lock);
	वापस index;
पूर्ण

/*
 * Whee.. Weird sysv syscall. 
 */
SYSCALL_DEFINE3(sysfs, पूर्णांक, option, अचिन्हित दीर्घ, arg1, अचिन्हित दीर्घ, arg2)
अणु
	पूर्णांक retval = -EINVAL;

	चयन (option) अणु
		हाल 1:
			retval = fs_index((स्थिर अक्षर __user *) arg1);
			अवरोध;

		हाल 2:
			retval = fs_name(arg1, (अक्षर __user *) arg2);
			अवरोध;

		हाल 3:
			retval = fs_maxindex();
			अवरोध;
	पूर्ण
	वापस retval;
पूर्ण
#पूर्ण_अगर

पूर्णांक __init get_fileप्रणाली_list(अक्षर *buf)
अणु
	पूर्णांक len = 0;
	काष्ठा file_प्रणाली_type * पंचांगp;

	पढ़ो_lock(&file_प्रणालीs_lock);
	पंचांगp = file_प्रणालीs;
	जबतक (पंचांगp && len < PAGE_SIZE - 80) अणु
		len += प्र_लिखो(buf+len, "%s\t%s\n",
			(पंचांगp->fs_flags & FS_REQUIRES_DEV) ? "" : "nodev",
			पंचांगp->name);
		पंचांगp = पंचांगp->next;
	पूर्ण
	पढ़ो_unlock(&file_प्रणालीs_lock);
	वापस len;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक fileप्रणालीs_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा file_प्रणाली_type * पंचांगp;

	पढ़ो_lock(&file_प्रणालीs_lock);
	पंचांगp = file_प्रणालीs;
	जबतक (पंचांगp) अणु
		seq_म_लिखो(m, "%s\t%s\n",
			(पंचांगp->fs_flags & FS_REQUIRES_DEV) ? "" : "nodev",
			पंचांगp->name);
		पंचांगp = पंचांगp->next;
	पूर्ण
	पढ़ो_unlock(&file_प्रणालीs_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __init proc_fileप्रणालीs_init(व्योम)
अणु
	proc_create_single("filesystems", 0, शून्य, fileप्रणालीs_proc_show);
	वापस 0;
पूर्ण
module_init(proc_fileप्रणालीs_init);
#पूर्ण_अगर

अटल काष्ठा file_प्रणाली_type *__get_fs_type(स्थिर अक्षर *name, पूर्णांक len)
अणु
	काष्ठा file_प्रणाली_type *fs;

	पढ़ो_lock(&file_प्रणालीs_lock);
	fs = *(find_fileप्रणाली(name, len));
	अगर (fs && !try_module_get(fs->owner))
		fs = शून्य;
	पढ़ो_unlock(&file_प्रणालीs_lock);
	वापस fs;
पूर्ण

काष्ठा file_प्रणाली_type *get_fs_type(स्थिर अक्षर *name)
अणु
	काष्ठा file_प्रणाली_type *fs;
	स्थिर अक्षर *करोt = म_अक्षर(name, '.');
	पूर्णांक len = करोt ? करोt - name : म_माप(name);

	fs = __get_fs_type(name, len);
	अगर (!fs && (request_module("fs-%.*s", len, name) == 0)) अणु
		fs = __get_fs_type(name, len);
		अगर (!fs)
			pr_warn_once("request_module fs-%.*s succeeded, but still no fs?\n",
				     len, name);
	पूर्ण

	अगर (करोt && fs && !(fs->fs_flags & FS_HAS_SUBTYPE)) अणु
		put_fileप्रणाली(fs);
		fs = शून्य;
	पूर्ण
	वापस fs;
पूर्ण

EXPORT_SYMBOL(get_fs_type);
