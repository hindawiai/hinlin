<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR MIT) */
/******************************************************************************
 * privcmd.h
 *
 * Interface to /proc/xen/privcmd.
 *
 * Copyright (c) 2003-2005, K A Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __LINUX_PUBLIC_PRIVCMD_H__
#घोषणा __LINUX_PUBLIC_PRIVCMD_H__

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <xen/पूर्णांकerface/xen.h>

काष्ठा privcmd_hypercall अणु
	__u64 op;
	__u64 arg[5];
पूर्ण;

काष्ठा privcmd_mmap_entry अणु
	__u64 va;
	/*
	 * This should be a GFN. It's not possible to change the name because
	 * it's exposed to the user-space.
	 */
	__u64 mfn;
	__u64 npages;
पूर्ण;

काष्ठा privcmd_mmap अणु
	पूर्णांक num;
	करोmid_t करोm; /* target करोमुख्य */
	काष्ठा privcmd_mmap_entry __user *entry;
पूर्ण;

काष्ठा privcmd_mmapbatch अणु
	पूर्णांक num;     /* number of pages to populate */
	करोmid_t करोm; /* target करोमुख्य */
	__u64 addr;  /* भव address */
	xen_pfn_t __user *arr; /* array of mfns - or'd with
				  PRIVCMD_MMAPBATCH_*_ERROR on err */
पूर्ण;

#घोषणा PRIVCMD_MMAPBATCH_MFN_ERROR     0xf0000000U
#घोषणा PRIVCMD_MMAPBATCH_PAGED_ERROR   0x80000000U

काष्ठा privcmd_mmapbatch_v2 अणु
	अचिन्हित पूर्णांक num; /* number of pages to populate */
	करोmid_t करोm;      /* target करोमुख्य */
	__u64 addr;       /* भव address */
	स्थिर xen_pfn_t __user *arr; /* array of mfns */
	पूर्णांक __user *err;  /* array of error codes */
पूर्ण;

काष्ठा privcmd_dm_op_buf अणु
	व्योम __user *uptr;
	माप_प्रकार size;
पूर्ण;

काष्ठा privcmd_dm_op अणु
	करोmid_t करोm;
	__u16 num;
	स्थिर काष्ठा privcmd_dm_op_buf __user *ubufs;
पूर्ण;

काष्ठा privcmd_mmap_resource अणु
	करोmid_t करोm;
	__u32 type;
	__u32 id;
	__u32 idx;
	__u64 num;
	__u64 addr;
पूर्ण;

/*
 * @cmd: IOCTL_PRIVCMD_HYPERCALL
 * @arg: &privcmd_hypercall_t
 * Return: Value वापसed from execution of the specअगरied hypercall.
 *
 * @cmd: IOCTL_PRIVCMD_MMAPBATCH_V2
 * @arg: &काष्ठा privcmd_mmapbatch_v2
 * Return: 0 on success (i.e., arg->err contains valid error codes क्रम
 * each frame).  On an error other than a failed frame remap, -1 is
 * वापसed and त्रुटि_सं is set to EINVAL, EFAULT etc.  As an exception,
 * अगर the operation was otherwise successful but any frame failed with
 * -ENOENT, then -1 is वापसed and त्रुटि_सं is set to ENOENT.
 */
#घोषणा IOCTL_PRIVCMD_HYPERCALL					\
	_IOC(_IOC_NONE, 'P', 0, माप(काष्ठा privcmd_hypercall))
#घोषणा IOCTL_PRIVCMD_MMAP					\
	_IOC(_IOC_NONE, 'P', 2, माप(काष्ठा privcmd_mmap))
#घोषणा IOCTL_PRIVCMD_MMAPBATCH					\
	_IOC(_IOC_NONE, 'P', 3, माप(काष्ठा privcmd_mmapbatch))
#घोषणा IOCTL_PRIVCMD_MMAPBATCH_V2				\
	_IOC(_IOC_NONE, 'P', 4, माप(काष्ठा privcmd_mmapbatch_v2))
#घोषणा IOCTL_PRIVCMD_DM_OP					\
	_IOC(_IOC_NONE, 'P', 5, माप(काष्ठा privcmd_dm_op))
#घोषणा IOCTL_PRIVCMD_RESTRICT					\
	_IOC(_IOC_NONE, 'P', 6, माप(करोmid_t))
#घोषणा IOCTL_PRIVCMD_MMAP_RESOURCE				\
	_IOC(_IOC_NONE, 'P', 7, माप(काष्ठा privcmd_mmap_resource))

#पूर्ण_अगर /* __LINUX_PUBLIC_PRIVCMD_H__ */
