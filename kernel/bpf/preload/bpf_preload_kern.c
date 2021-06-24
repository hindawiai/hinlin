<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pid.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched/संकेत.स>
#समावेश "bpf_preload.h"

बाह्य अक्षर bpf_preload_umd_start;
बाह्य अक्षर bpf_preload_umd_end;

अटल पूर्णांक preload(काष्ठा bpf_preload_info *obj);
अटल पूर्णांक finish(व्योम);

अटल काष्ठा bpf_preload_ops umd_ops = अणु
	.info.driver_name = "bpf_preload",
	.preload = preload,
	.finish = finish,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक preload(काष्ठा bpf_preload_info *obj)
अणु
	पूर्णांक magic = BPF_PRELOAD_START;
	loff_t pos = 0;
	पूर्णांक i, err;
	sमाप_प्रकार n;

	err = विभाजन_usermode_driver(&umd_ops.info);
	अगर (err)
		वापस err;

	/* send the start magic to let UMD proceed with loading BPF progs */
	n = kernel_ग_लिखो(umd_ops.info.pipe_to_umh,
			 &magic, माप(magic), &pos);
	अगर (n != माप(magic))
		वापस -EPIPE;

	/* receive bpf_link IDs and names from UMD */
	pos = 0;
	क्रम (i = 0; i < BPF_PRELOAD_LINKS; i++) अणु
		n = kernel_पढ़ो(umd_ops.info.pipe_from_umh,
				&obj[i], माप(*obj), &pos);
		अगर (n != माप(*obj))
			वापस -EPIPE;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक finish(व्योम)
अणु
	पूर्णांक magic = BPF_PRELOAD_END;
	काष्ठा pid *tgid;
	loff_t pos = 0;
	sमाप_प्रकार n;

	/* send the last magic to UMD. It will करो a normal निकास. */
	n = kernel_ग_लिखो(umd_ops.info.pipe_to_umh,
			 &magic, माप(magic), &pos);
	अगर (n != माप(magic))
		वापस -EPIPE;

	tgid = umd_ops.info.tgid;
	अगर (tgid) अणु
		रुको_event(tgid->रुको_pidfd, thपढ़ो_group_निकासed(tgid));
		umd_cleanup_helper(&umd_ops.info);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init load_umd(व्योम)
अणु
	पूर्णांक err;

	err = umd_load_blob(&umd_ops.info, &bpf_preload_umd_start,
			    &bpf_preload_umd_end - &bpf_preload_umd_start);
	अगर (err)
		वापस err;
	bpf_preload_ops = &umd_ops;
	वापस err;
पूर्ण

अटल व्योम __निकास fini_umd(व्योम)
अणु
	काष्ठा pid *tgid;

	bpf_preload_ops = शून्य;

	/* समाप्त UMD in हाल it's still there due to earlier error */
	tgid = umd_ops.info.tgid;
	अगर (tgid) अणु
		समाप्त_pid(tgid, SIGKILL, 1);

		रुको_event(tgid->रुको_pidfd, thपढ़ो_group_निकासed(tgid));
		umd_cleanup_helper(&umd_ops.info);
	पूर्ण
	umd_unload_blob(&umd_ops.info);
पूर्ण
late_initcall(load_umd);
module_निकास(fini_umd);
MODULE_LICENSE("GPL");
