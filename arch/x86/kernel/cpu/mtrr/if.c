<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/capability.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>

#घोषणा LINE_SIZE 80

#समावेश <यंत्र/mtrr.h>

#समावेश "mtrr.h"

#घोषणा खाता_FCOUNT(f) (((काष्ठा seq_file *)((f)->निजी_data))->निजी)

अटल स्थिर अक्षर *स्थिर mtrr_strings[MTRR_NUM_TYPES] =
अणु
	"uncachable",		/* 0 */
	"write-combining",	/* 1 */
	"?",			/* 2 */
	"?",			/* 3 */
	"write-through",	/* 4 */
	"write-protect",	/* 5 */
	"write-back",		/* 6 */
पूर्ण;

स्थिर अक्षर *mtrr_attrib_to_str(पूर्णांक x)
अणु
	वापस (x <= 6) ? mtrr_strings[x] : "?";
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल पूर्णांक
mtrr_file_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
	      अचिन्हित पूर्णांक type, bool increment, काष्ठा file *file, पूर्णांक page)
अणु
	अचिन्हित पूर्णांक *fcount = खाता_FCOUNT(file);
	पूर्णांक reg, max;

	max = num_var_ranges;
	अगर (fcount == शून्य) अणु
		fcount = kसुस्मृति(max, माप(*fcount), GFP_KERNEL);
		अगर (!fcount)
			वापस -ENOMEM;
		खाता_FCOUNT(file) = fcount;
	पूर्ण
	अगर (!page) अणु
		अगर ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1)))
			वापस -EINVAL;
		base >>= PAGE_SHIFT;
		size >>= PAGE_SHIFT;
	पूर्ण
	reg = mtrr_add_page(base, size, type, true);
	अगर (reg >= 0)
		++fcount[reg];
	वापस reg;
पूर्ण

अटल पूर्णांक
mtrr_file_del(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
	      काष्ठा file *file, पूर्णांक page)
अणु
	अचिन्हित पूर्णांक *fcount = खाता_FCOUNT(file);
	पूर्णांक reg;

	अगर (!page) अणु
		अगर ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1)))
			वापस -EINVAL;
		base >>= PAGE_SHIFT;
		size >>= PAGE_SHIFT;
	पूर्ण
	reg = mtrr_del_page(-1, base, size);
	अगर (reg < 0)
		वापस reg;
	अगर (fcount == शून्य)
		वापस reg;
	अगर (fcount[reg] < 1)
		वापस -EINVAL;
	--fcount[reg];
	वापस reg;
पूर्ण

/*
 * seq_file can seek but we ignore it.
 *
 * Format of control line:
 *    "base=%Lx size=%Lx type=%s" or "disable=%d"
 */
अटल sमाप_प्रकार
mtrr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t * ppos)
अणु
	पूर्णांक i, err;
	अचिन्हित दीर्घ reg;
	अचिन्हित दीर्घ दीर्घ base, size;
	अक्षर *ptr;
	अक्षर line[LINE_SIZE];
	पूर्णांक length;
	माप_प्रकार linelen;

	स_रखो(line, 0, LINE_SIZE);

	len = min_t(माप_प्रकार, len, LINE_SIZE - 1);
	length = म_नकलन_from_user(line, buf, len);
	अगर (length < 0)
		वापस length;

	linelen = म_माप(line);
	ptr = line + linelen - 1;
	अगर (linelen && *ptr == '\n')
		*ptr = '\0';

	अगर (!म_भेदन(line, "disable=", 8)) अणु
		reg = simple_म_से_अदीर्घ(line + 8, &ptr, 0);
		err = mtrr_del_page(reg, 0, 0);
		अगर (err < 0)
			वापस err;
		वापस len;
	पूर्ण

	अगर (म_भेदन(line, "base=", 5))
		वापस -EINVAL;

	base = simple_म_से_अदीर्घl(line + 5, &ptr, 0);
	ptr = skip_spaces(ptr);

	अगर (म_भेदन(ptr, "size=", 5))
		वापस -EINVAL;

	size = simple_म_से_अदीर्घl(ptr + 5, &ptr, 0);
	अगर ((base & 0xfff) || (size & 0xfff))
		वापस -EINVAL;
	ptr = skip_spaces(ptr);

	अगर (म_भेदन(ptr, "type=", 5))
		वापस -EINVAL;
	ptr = skip_spaces(ptr + 5);

	i = match_string(mtrr_strings, MTRR_NUM_TYPES, ptr);
	अगर (i < 0)
		वापस i;

	base >>= PAGE_SHIFT;
	size >>= PAGE_SHIFT;
	err = mtrr_add_page((अचिन्हित दीर्घ)base, (अचिन्हित दीर्घ)size, i, true);
	अगर (err < 0)
		वापस err;
	वापस len;
पूर्ण

अटल दीर्घ
mtrr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ __arg)
अणु
	पूर्णांक err = 0;
	mtrr_type type;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ size;
	काष्ठा mtrr_sentry sentry;
	काष्ठा mtrr_gentry gentry;
	व्योम __user *arg = (व्योम __user *) __arg;

	स_रखो(&gentry, 0, माप(gentry));

	चयन (cmd) अणु
	हाल MTRRIOC_ADD_ENTRY:
	हाल MTRRIOC_SET_ENTRY:
	हाल MTRRIOC_DEL_ENTRY:
	हाल MTRRIOC_KILL_ENTRY:
	हाल MTRRIOC_ADD_PAGE_ENTRY:
	हाल MTRRIOC_SET_PAGE_ENTRY:
	हाल MTRRIOC_DEL_PAGE_ENTRY:
	हाल MTRRIOC_KILL_PAGE_ENTRY:
		अगर (copy_from_user(&sentry, arg, माप(sentry)))
			वापस -EFAULT;
		अवरोध;
	हाल MTRRIOC_GET_ENTRY:
	हाल MTRRIOC_GET_PAGE_ENTRY:
		अगर (copy_from_user(&gentry, arg, माप(gentry)))
			वापस -EFAULT;
		अवरोध;
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_ADD_ENTRY:
	हाल MTRRIOC32_SET_ENTRY:
	हाल MTRRIOC32_DEL_ENTRY:
	हाल MTRRIOC32_KILL_ENTRY:
	हाल MTRRIOC32_ADD_PAGE_ENTRY:
	हाल MTRRIOC32_SET_PAGE_ENTRY:
	हाल MTRRIOC32_DEL_PAGE_ENTRY:
	हाल MTRRIOC32_KILL_PAGE_ENTRY: अणु
		काष्ठा mtrr_sentry32 __user *s32;

		s32 = (काष्ठा mtrr_sentry32 __user *)__arg;
		err = get_user(sentry.base, &s32->base);
		err |= get_user(sentry.size, &s32->size);
		err |= get_user(sentry.type, &s32->type);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण
	हाल MTRRIOC32_GET_ENTRY:
	हाल MTRRIOC32_GET_PAGE_ENTRY: अणु
		काष्ठा mtrr_gentry32 __user *g32;

		g32 = (काष्ठा mtrr_gentry32 __user *)__arg;
		err = get_user(gentry.regnum, &g32->regnum);
		err |= get_user(gentry.base, &g32->base);
		err |= get_user(gentry.size, &g32->size);
		err |= get_user(gentry.type, &g32->type);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	चयन (cmd) अणु
	शेष:
		वापस -ENOTTY;
	हाल MTRRIOC_ADD_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_ADD_ENTRY:
#पूर्ण_अगर
		err =
		    mtrr_file_add(sentry.base, sentry.size, sentry.type, true,
				  file, 0);
		अवरोध;
	हाल MTRRIOC_SET_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_SET_ENTRY:
#पूर्ण_अगर
		err = mtrr_add(sentry.base, sentry.size, sentry.type, false);
		अवरोध;
	हाल MTRRIOC_DEL_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_DEL_ENTRY:
#पूर्ण_अगर
		err = mtrr_file_del(sentry.base, sentry.size, file, 0);
		अवरोध;
	हाल MTRRIOC_KILL_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_KILL_ENTRY:
#पूर्ण_अगर
		err = mtrr_del(-1, sentry.base, sentry.size);
		अवरोध;
	हाल MTRRIOC_GET_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_GET_ENTRY:
#पूर्ण_अगर
		अगर (gentry.regnum >= num_var_ranges)
			वापस -EINVAL;
		mtrr_अगर->get(gentry.regnum, &base, &size, &type);

		/* Hide entries that go above 4GB */
		अगर (base + size - 1 >= (1UL << (8 * माप(gentry.size) - PAGE_SHIFT))
		    || size >= (1UL << (8 * माप(gentry.size) - PAGE_SHIFT)))
			gentry.base = gentry.size = gentry.type = 0;
		अन्यथा अणु
			gentry.base = base << PAGE_SHIFT;
			gentry.size = size << PAGE_SHIFT;
			gentry.type = type;
		पूर्ण

		अवरोध;
	हाल MTRRIOC_ADD_PAGE_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_ADD_PAGE_ENTRY:
#पूर्ण_अगर
		err =
		    mtrr_file_add(sentry.base, sentry.size, sentry.type, true,
				  file, 1);
		अवरोध;
	हाल MTRRIOC_SET_PAGE_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_SET_PAGE_ENTRY:
#पूर्ण_अगर
		err =
		    mtrr_add_page(sentry.base, sentry.size, sentry.type, false);
		अवरोध;
	हाल MTRRIOC_DEL_PAGE_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_DEL_PAGE_ENTRY:
#पूर्ण_अगर
		err = mtrr_file_del(sentry.base, sentry.size, file, 1);
		अवरोध;
	हाल MTRRIOC_KILL_PAGE_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_KILL_PAGE_ENTRY:
#पूर्ण_अगर
		err = mtrr_del_page(-1, sentry.base, sentry.size);
		अवरोध;
	हाल MTRRIOC_GET_PAGE_ENTRY:
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_GET_PAGE_ENTRY:
#पूर्ण_अगर
		अगर (gentry.regnum >= num_var_ranges)
			वापस -EINVAL;
		mtrr_अगर->get(gentry.regnum, &base, &size, &type);
		/* Hide entries that would overflow */
		अगर (size != (__typeof__(gentry.size))size)
			gentry.base = gentry.size = gentry.type = 0;
		अन्यथा अणु
			gentry.base = base;
			gentry.size = size;
			gentry.type = type;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	चयन (cmd) अणु
	हाल MTRRIOC_GET_ENTRY:
	हाल MTRRIOC_GET_PAGE_ENTRY:
		अगर (copy_to_user(arg, &gentry, माप(gentry)))
			err = -EFAULT;
		अवरोध;
#अगर_घोषित CONFIG_COMPAT
	हाल MTRRIOC32_GET_ENTRY:
	हाल MTRRIOC32_GET_PAGE_ENTRY: अणु
		काष्ठा mtrr_gentry32 __user *g32;

		g32 = (काष्ठा mtrr_gentry32 __user *)__arg;
		err = put_user(gentry.base, &g32->base);
		err |= put_user(gentry.size, &g32->size);
		err |= put_user(gentry.regnum, &g32->regnum);
		err |= put_user(gentry.type, &g32->type);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mtrr_बंद(काष्ठा inode *ino, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक *fcount = खाता_FCOUNT(file);
	पूर्णांक i, max;

	अगर (fcount != शून्य) अणु
		max = num_var_ranges;
		क्रम (i = 0; i < max; ++i) अणु
			जबतक (fcount[i] > 0) अणु
				mtrr_del(i, 0, 0);
				--fcount[i];
			पूर्ण
		पूर्ण
		kमुक्त(fcount);
		खाता_FCOUNT(file) = शून्य;
	पूर्ण
	वापस single_release(ino, file);
पूर्ण

अटल पूर्णांक mtrr_seq_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	अक्षर factor;
	पूर्णांक i, max;
	mtrr_type type;
	अचिन्हित दीर्घ base, size;

	max = num_var_ranges;
	क्रम (i = 0; i < max; i++) अणु
		mtrr_अगर->get(i, &base, &size, &type);
		अगर (size == 0) अणु
			mtrr_usage_table[i] = 0;
			जारी;
		पूर्ण
		अगर (size < (0x100000 >> PAGE_SHIFT)) अणु
			/* less than 1MB */
			factor = 'K';
			size <<= PAGE_SHIFT - 10;
		पूर्ण अन्यथा अणु
			factor = 'M';
			size >>= 20 - PAGE_SHIFT;
		पूर्ण
		/* Base can be > 32bit */
		seq_म_लिखो(seq, "reg%02i: base=0x%06lx000 (%5luMB), size=%5lu%cB, count=%d: %s\n",
			   i, base, base >> (20 - PAGE_SHIFT),
			   size, factor,
			   mtrr_usage_table[i], mtrr_attrib_to_str(type));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mtrr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!mtrr_अगर)
		वापस -EIO;
	अगर (!mtrr_अगर->get)
		वापस -ENXIO;
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	वापस single_खोलो(file, mtrr_seq_show, शून्य);
पूर्ण

अटल स्थिर काष्ठा proc_ops mtrr_proc_ops = अणु
	.proc_खोलो		= mtrr_खोलो,
	.proc_पढ़ो		= seq_पढ़ो,
	.proc_lseek		= seq_lseek,
	.proc_ग_लिखो		= mtrr_ग_लिखो,
	.proc_ioctl		= mtrr_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.proc_compat_ioctl	= mtrr_ioctl,
#पूर्ण_अगर
	.proc_release		= mtrr_बंद,
पूर्ण;

अटल पूर्णांक __init mtrr_अगर_init(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	अगर ((!cpu_has(c, X86_FEATURE_MTRR)) &&
	    (!cpu_has(c, X86_FEATURE_K6_MTRR)) &&
	    (!cpu_has(c, X86_FEATURE_CYRIX_ARR)) &&
	    (!cpu_has(c, X86_FEATURE_CENTAUR_MCR)))
		वापस -ENODEV;

	proc_create("mtrr", S_IWUSR | S_IRUGO, शून्य, &mtrr_proc_ops);
	वापस 0;
पूर्ण
arch_initcall(mtrr_अगर_init);
#पूर्ण_अगर			/*  CONFIG_PROC_FS  */
