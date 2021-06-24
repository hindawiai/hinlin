<शैली गुरु>
/*
 * Alignment access counters and corresponding user-space पूर्णांकerfaces.
 *
 * Copyright (C) 2009 ST Microelectronics
 * Copyright (C) 2009 - 2010 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/alignment.h>
#समावेश <यंत्र/processor.h>

अटल अचिन्हित दीर्घ se_user;
अटल अचिन्हित दीर्घ se_sys;
अटल अचिन्हित दीर्घ se_half;
अटल अचिन्हित दीर्घ se_word;
अटल अचिन्हित दीर्घ se_dword;
अटल अचिन्हित दीर्घ se_multi;
/* bitfield: 1: warn 2: fixup 4: संकेत -> combinations 2|4 && 1|2|4 are not
   valid! */
अटल पूर्णांक se_usermode = UM_WARN | UM_FIXUP;
/* 0: no warning 1: prपूर्णांक a warning message, disabled by शेष */
अटल पूर्णांक se_kernmode_warn;

core_param(alignment, se_usermode, पूर्णांक, 0600);

व्योम inc_unaligned_byte_access(व्योम)
अणु
	se_half++;
पूर्ण

व्योम inc_unaligned_word_access(व्योम)
अणु
	se_word++;
पूर्ण

व्योम inc_unaligned_dword_access(व्योम)
अणु
	se_dword++;
पूर्ण

व्योम inc_unaligned_multi_access(व्योम)
अणु
	se_multi++;
पूर्ण

व्योम inc_unaligned_user_access(व्योम)
अणु
	se_user++;
पूर्ण

व्योम inc_unaligned_kernel_access(व्योम)
अणु
	se_sys++;
पूर्ण

/*
 * This शेषs to the global policy which can be set from the command
 * line, जबतक processes can overload their preferences via prctl().
 */
अचिन्हित पूर्णांक unaligned_user_action(व्योम)
अणु
	अचिन्हित पूर्णांक action = se_usermode;

	अगर (current->thपढ़ो.flags & SH_THREAD_UAC_SIGBUS) अणु
		action &= ~UM_FIXUP;
		action |= UM_SIGNAL;
	पूर्ण

	अगर (current->thपढ़ो.flags & SH_THREAD_UAC_NOPRINT)
		action &= ~UM_WARN;

	वापस action;
पूर्ण

पूर्णांक get_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr)
अणु
	वापस put_user(tsk->thपढ़ो.flags & SH_THREAD_UAC_MASK,
			(अचिन्हित पूर्णांक __user *)addr);
पूर्ण

पूर्णांक set_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val)
अणु
	tsk->thपढ़ो.flags = (tsk->thपढ़ो.flags & ~SH_THREAD_UAC_MASK) |
			    (val & SH_THREAD_UAC_MASK);
	वापस 0;
पूर्ण

व्योम unaligned_fixups_notअगरy(काष्ठा task_काष्ठा *tsk, insn_माप_प्रकार insn,
			     काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs) && (se_usermode & UM_WARN))
		pr_notice_ratelimited("Fixing up unaligned userspace access "
			  "in \"%s\" pid=%d pc=0x%p ins=0x%04hx\n",
			  tsk->comm, task_pid_nr(tsk),
			  (व्योम *)inकाष्ठाion_poपूर्णांकer(regs), insn);
	अन्यथा अगर (se_kernmode_warn)
		pr_notice_ratelimited("Fixing up unaligned kernel access "
			  "in \"%s\" pid=%d pc=0x%p ins=0x%04hx\n",
			  tsk->comm, task_pid_nr(tsk),
			  (व्योम *)inकाष्ठाion_poपूर्णांकer(regs), insn);
पूर्ण

अटल स्थिर अक्षर *se_usermode_action[] = अणु
	"ignored",
	"warn",
	"fixup",
	"fixup+warn",
	"signal",
	"signal+warn"
पूर्ण;

अटल पूर्णांक alignment_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "User:\t\t%lu\n", se_user);
	seq_म_लिखो(m, "System:\t\t%lu\n", se_sys);
	seq_म_लिखो(m, "Half:\t\t%lu\n", se_half);
	seq_म_लिखो(m, "Word:\t\t%lu\n", se_word);
	seq_म_लिखो(m, "DWord:\t\t%lu\n", se_dword);
	seq_म_लिखो(m, "Multi:\t\t%lu\n", se_multi);
	seq_म_लिखो(m, "User faults:\t%i (%s)\n", se_usermode,
			se_usermode_action[se_usermode]);
	seq_म_लिखो(m, "Kernel faults:\t%i (fixup%s)\n", se_kernmode_warn,
			se_kernmode_warn ? "+warn" : "");
	वापस 0;
पूर्ण

अटल पूर्णांक alignment_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, alignment_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार alignment_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक *data = PDE_DATA(file_inode(file));
	अक्षर mode;

	अगर (count > 0) अणु
		अगर (get_user(mode, buffer))
			वापस -EFAULT;
		अगर (mode >= '0' && mode <= '5')
			*data = mode - '0';
	पूर्ण
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops alignment_proc_ops = अणु
	.proc_खोलो	= alignment_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= alignment_proc_ग_लिखो,
पूर्ण;

/*
 * This needs to be करोne after sysctl_init, otherwise sys/ will be
 * overwritten.  Actually, this shouldn't be in sys/ at all since
 * it isn't a sysctl, and it doesn't contain sysctl inक्रमmation.
 * We now locate it in /proc/cpu/alignment instead.
 */
अटल पूर्णांक __init alignment_init(व्योम)
अणु
	काष्ठा proc_dir_entry *dir, *res;

	dir = proc_सूची_गढ़ो("cpu", शून्य);
	अगर (!dir)
		वापस -ENOMEM;

	res = proc_create_data("alignment", S_IWUSR | S_IRUGO, dir,
			       &alignment_proc_ops, &se_usermode);
	अगर (!res)
		वापस -ENOMEM;

        res = proc_create_data("kernel_alignment", S_IWUSR | S_IRUGO, dir,
			       &alignment_proc_ops, &se_kernmode_warn);
        अगर (!res)
                वापस -ENOMEM;

	वापस 0;
पूर्ण
fs_initcall(alignment_init);
