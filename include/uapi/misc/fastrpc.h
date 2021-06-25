<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */

#अगर_अघोषित __QCOM_FASTRPC_H__
#घोषणा __QCOM_FASTRPC_H__

#समावेश <linux/types.h>

#घोषणा FASTRPC_IOCTL_ALLOC_DMA_BUFF	_IOWR('R', 1, काष्ठा fastrpc_alloc_dma_buf)
#घोषणा FASTRPC_IOCTL_FREE_DMA_BUFF	_IOWR('R', 2, __u32)
#घोषणा FASTRPC_IOCTL_INVOKE		_IOWR('R', 3, काष्ठा fastrpc_invoke)
#घोषणा FASTRPC_IOCTL_INIT_ATTACH	_IO('R', 4)
#घोषणा FASTRPC_IOCTL_INIT_CREATE	_IOWR('R', 5, काष्ठा fastrpc_init_create)
#घोषणा FASTRPC_IOCTL_MMAP		_IOWR('R', 6, काष्ठा fastrpc_req_mmap)
#घोषणा FASTRPC_IOCTL_MUNMAP		_IOWR('R', 7, काष्ठा fastrpc_req_munmap)
#घोषणा FASTRPC_IOCTL_INIT_ATTACH_SNS	_IO('R', 8)

काष्ठा fastrpc_invoke_args अणु
	__u64 ptr;
	__u64 length;
	__s32 fd;
	__u32 reserved;
पूर्ण;

काष्ठा fastrpc_invoke अणु
	__u32 handle;
	__u32 sc;
	__u64 args;
पूर्ण;

काष्ठा fastrpc_init_create अणु
	__u32 filelen;	/* elf file length */
	__s32 filefd;	/* fd क्रम the file */
	__u32 attrs;
	__u32 siglen;
	__u64 file;	/* poपूर्णांकer to elf file */
पूर्ण;

काष्ठा fastrpc_alloc_dma_buf अणु
	__s32 fd;	/* fd */
	__u32 flags;	/* flags to map with */
	__u64 size;	/* size */
पूर्ण;

काष्ठा fastrpc_req_mmap अणु
	__s32 fd;
	__u32 flags;	/* flags क्रम dsp to map with */
	__u64 vaddrin;	/* optional भव address */
	__u64 size;	/* size */
	__u64 vaddrout;	/* dsp भव address */
पूर्ण;

काष्ठा fastrpc_req_munmap अणु
	__u64 vaddrout;	/* address to unmap */
	__u64 size;	/* size */
पूर्ण;

#पूर्ण_अगर /* __QCOM_FASTRPC_H__ */
