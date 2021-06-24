<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * srm_env.c - Access to SRM environment
 *             variables through linux' procfs
 *
 * (C) 2001,2002,2006 by Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *
 * This driver is a modअगरied version of Erik Mouw's example proc
 * पूर्णांकerface, so: thank you, Erik! He can be reached via email at
 * <J.A.K.Mouw@its.tudelft.nl>. It is based on an idea
 * provided by DEC^WCompaq^WIntel's "Jumpstart" CD. They
 * included a patch like this as well. Thanks क्रम idea!
 */

#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/console.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/machvec.h>

#घोषणा BASE_सूची	"srm_environment"	/* Subdir in /proc/		*/
#घोषणा NAMED_सूची	"named_variables"	/* Subdir क्रम known variables	*/
#घोषणा NUMBERED_सूची	"numbered_variables"	/* Subdir क्रम all variables	*/
#घोषणा VERSION		"0.0.6"			/* Module version		*/
#घोषणा NAME		"srm_env"		/* Module name			*/

MODULE_AUTHOR("Jan-Benedict Glaw <jbglaw@lug-owl.de>");
MODULE_DESCRIPTION("Accessing Alpha SRM environment through procfs interface");
MODULE_LICENSE("GPL");

प्रकार काष्ठा _srm_env अणु
	अक्षर			*name;
	अचिन्हित दीर्घ		id;
पूर्ण srm_env_t;

अटल काष्ठा proc_dir_entry	*base_dir;
अटल काष्ठा proc_dir_entry	*named_dir;
अटल काष्ठा proc_dir_entry	*numbered_dir;

अटल srm_env_t	srm_named_entries[] = अणु
	अणु "auto_action",	ENV_AUTO_ACTION		पूर्ण,
	अणु "boot_dev",		ENV_BOOT_DEV		पूर्ण,
	अणु "bootdef_dev",	ENV_BOOTDEF_DEV		पूर्ण,
	अणु "booted_dev",		ENV_BOOTED_DEV		पूर्ण,
	अणु "boot_file",		ENV_BOOT_खाता		पूर्ण,
	अणु "booted_file",	ENV_BOOTED_खाता		पूर्ण,
	अणु "boot_osflags",	ENV_BOOT_OSFLAGS	पूर्ण,
	अणु "booted_osflags",	ENV_BOOTED_OSFLAGS	पूर्ण,
	अणु "boot_reset",		ENV_BOOT_RESET		पूर्ण,
	अणु "dump_dev",		ENV_DUMP_DEV		पूर्ण,
	अणु "enable_audit",	ENV_ENABLE_AUDIT	पूर्ण,
	अणु "license",		ENV_LICENSE		पूर्ण,
	अणु "char_set",		ENV_CHAR_SET		पूर्ण,
	अणु "language",		ENV_LANGUAGE		पूर्ण,
	अणु "tty_dev",		ENV_TTY_DEV		पूर्ण,
	अणु शून्य,			0			पूर्ण,
पूर्ण;

अटल पूर्णांक srm_env_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ	ret;
	अचिन्हित दीर्घ	id = (अचिन्हित दीर्घ)m->निजी;
	अक्षर		*page;

	page = (अक्षर *)__get_मुक्त_page(GFP_USER);
	अगर (!page)
		वापस -ENOMEM;

	ret = callback_दो_पर्या(id, page, PAGE_SIZE);

	अगर ((ret >> 61) == 0) अणु
		seq_ग_लिखो(m, page, ret);
		ret = 0;
	पूर्ण अन्यथा
		ret = -EFAULT;
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस ret;
पूर्ण

अटल पूर्णांक srm_env_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, srm_env_proc_show, PDE_DATA(inode));
पूर्ण

अटल sमाप_प्रकार srm_env_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ	id = (अचिन्हित दीर्घ)PDE_DATA(file_inode(file));
	अक्षर		*buf = (अक्षर *) __get_मुक्त_page(GFP_USER);
	अचिन्हित दीर्घ	ret1, ret2;

	अगर (!buf)
		वापस -ENOMEM;

	res = -EINVAL;
	अगर (count >= PAGE_SIZE)
		जाओ out;

	res = -EFAULT;
	अगर (copy_from_user(buf, buffer, count))
		जाओ out;
	buf[count] = '\0';

	ret1 = callback_setenv(id, buf, count);
	अगर ((ret1 >> 61) == 0) अणु
		करो
			ret2 = callback_save_env();
		जबतक((ret2 >> 61) == 1);
		res = (पूर्णांक) ret1;
	पूर्ण

 out:
	मुक्त_page((अचिन्हित दीर्घ)buf);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा proc_ops srm_env_proc_ops = अणु
	.proc_खोलो	= srm_env_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= srm_env_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init
srm_env_init(व्योम)
अणु
	srm_env_t	*entry;
	अचिन्हित दीर्घ	var_num;

	/*
	 * Check प्रणाली
	 */
	अगर (!alpha_using_srm) अणु
		prपूर्णांकk(KERN_INFO "%s: This Alpha system doesn't "
				"know about SRM (or you've booted "
				"SRM->MILO->Linux, which gets "
				"misdetected)...\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Create base directory
	 */
	base_dir = proc_सूची_गढ़ो(BASE_सूची, शून्य);
	अगर (!base_dir) अणु
		prपूर्णांकk(KERN_ERR "Couldn't create base dir /proc/%s\n",
				BASE_सूची);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Create per-name subdirectory
	 */
	named_dir = proc_सूची_गढ़ो(NAMED_सूची, base_dir);
	अगर (!named_dir) अणु
		prपूर्णांकk(KERN_ERR "Couldn't create dir /proc/%s/%s\n",
				BASE_सूची, NAMED_सूची);
		जाओ cleanup;
	पूर्ण

	/*
	 * Create per-number subdirectory
	 */
	numbered_dir = proc_सूची_गढ़ो(NUMBERED_सूची, base_dir);
	अगर (!numbered_dir) अणु
		prपूर्णांकk(KERN_ERR "Couldn't create dir /proc/%s/%s\n",
				BASE_सूची, NUMBERED_सूची);
		जाओ cleanup;

	पूर्ण

	/*
	 * Create all named nodes
	 */
	entry = srm_named_entries;
	जबतक (entry->name && entry->id) अणु
		अगर (!proc_create_data(entry->name, 0644, named_dir,
			     &srm_env_proc_ops, (व्योम *)entry->id))
			जाओ cleanup;
		entry++;
	पूर्ण

	/*
	 * Create all numbered nodes
	 */
	क्रम (var_num = 0; var_num <= 255; var_num++) अणु
		अक्षर name[4];
		प्र_लिखो(name, "%ld", var_num);
		अगर (!proc_create_data(name, 0644, numbered_dir,
			     &srm_env_proc_ops, (व्योम *)var_num))
			जाओ cleanup;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: version %s loaded successfully\n", NAME,
			VERSION);

	वापस 0;

cleanup:
	हटाओ_proc_subtree(BASE_सूची, शून्य);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास
srm_env_निकास(व्योम)
अणु
	हटाओ_proc_subtree(BASE_सूची, शून्य);
	prपूर्णांकk(KERN_INFO "%s: unloaded successfully\n", NAME);
पूर्ण

module_init(srm_env_init);
module_निकास(srm_env_निकास);
