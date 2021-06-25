<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

/* Copied from mm.h */
#घोषणा VM_READ		0x00000001
#घोषणा VM_WRITE	0x00000002
#घोषणा VM_EXEC		0x00000004
#घोषणा VM_MAYSHARE	0x00000080

/* Copied from kdev_t.h */
#घोषणा MINORBITS	20
#घोषणा MINORMASK	((1U << MINORBITS) - 1)
#घोषणा MAJOR(dev)	((अचिन्हित पूर्णांक) ((dev) >> MINORBITS))
#घोषणा MINOR(dev)	((अचिन्हित पूर्णांक) ((dev) & MINORMASK))

#घोषणा D_PATH_BUF_SIZE 1024
अक्षर d_path_buf[D_PATH_BUF_SIZE] = अणुपूर्ण;
__u32 pid = 0;

SEC("iter/task_vma") पूर्णांक proc_maps(काष्ठा bpf_iter__task_vma *ctx)
अणु
	काष्ठा vm_area_काष्ठा *vma = ctx->vma;
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा task_काष्ठा *task = ctx->task;
	काष्ठा file *file;
	अक्षर perm_str[] = "----";

	अगर (task == (व्योम *)0 || vma == (व्योम *)0)
		वापस 0;

	file = vma->vm_file;
	अगर (task->tgid != pid)
		वापस 0;
	perm_str[0] = (vma->vm_flags & VM_READ) ? 'r' : '-';
	perm_str[1] = (vma->vm_flags & VM_WRITE) ? 'w' : '-';
	perm_str[2] = (vma->vm_flags & VM_EXEC) ? 'x' : '-';
	perm_str[3] = (vma->vm_flags & VM_MAYSHARE) ? 's' : 'p';
	BPF_SEQ_PRINTF(seq, "%08llx-%08llx %s ", vma->vm_start, vma->vm_end, perm_str);

	अगर (file) अणु
		__u32 dev = file->f_inode->i_sb->s_dev;

		bpf_d_path(&file->f_path, d_path_buf, D_PATH_BUF_SIZE);

		BPF_SEQ_PRINTF(seq, "%08llx ", vma->vm_pgoff << 12);
		BPF_SEQ_PRINTF(seq, "%02x:%02x %u", MAJOR(dev), MINOR(dev),
			       file->f_inode->i_ino);
		BPF_SEQ_PRINTF(seq, "\t%s\n", d_path_buf);
	पूर्ण अन्यथा अणु
		BPF_SEQ_PRINTF(seq, "%08llx 00:00 0\n", 0ULL);
	पूर्ण
	वापस 0;
पूर्ण
