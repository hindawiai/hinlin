<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TYPES_H
#घोषणा _LINUX_TYPES_H

#घोषणा __EXPORTED_HEADERS__
#समावेश <uapi/linux/types.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा DECLARE_BITMAP(name,bits) \
	अचिन्हित दीर्घ name[BITS_TO_LONGS(bits)]

प्रकार u32 __kernel_dev_t;

प्रकार __kernel_fd_set		fd_set;
प्रकार __kernel_dev_t		dev_t;
प्रकार __kernel_uदीर्घ_t	ino_t;
प्रकार __kernel_mode_t		mode_t;
प्रकार अचिन्हित लघु		umode_t;
प्रकार u32			nlink_t;
प्रकार __kernel_off_t		off_t;
प्रकार __kernel_pid_t		pid_t;
प्रकार __kernel_daddr_t	daddr_t;
प्रकार __kernel_key_t		key_t;
प्रकार __kernel_suseconds_t	suseconds_t;
प्रकार __kernel_समयr_t	समयr_t;
प्रकार __kernel_घड़ीid_t	घड़ीid_t;
प्रकार __kernel_mqd_t		mqd_t;

प्रकार _Bool			bool;

प्रकार __kernel_uid32_t	uid_t;
प्रकार __kernel_gid32_t	gid_t;
प्रकार __kernel_uid16_t        uid16_t;
प्रकार __kernel_gid16_t        gid16_t;

प्रकार अचिन्हित दीर्घ		uपूर्णांकptr_t;

#अगर_घोषित CONFIG_HAVE_UID16
/* This is defined by include/यंत्र-अणुarchपूर्ण/posix_types.h */
प्रकार __kernel_old_uid_t	old_uid_t;
प्रकार __kernel_old_gid_t	old_gid_t;
#पूर्ण_अगर /* CONFIG_UID16 */

#अगर defined(__GNUC__)
प्रकार __kernel_loff_t		loff_t;
#पूर्ण_अगर

/*
 * The following प्रकारs are also रक्षित by inभागidual अगरdefs क्रम
 * historical reasons:
 */
#अगर_अघोषित _SIZE_T
#घोषणा _SIZE_T
प्रकार __kernel_माप_प्रकार		माप_प्रकार;
#पूर्ण_अगर

#अगर_अघोषित _SSIZE_T
#घोषणा _SSIZE_T
प्रकार __kernel_sमाप_प्रकार	sमाप_प्रकार;
#पूर्ण_अगर

#अगर_अघोषित _PTRDIFF_T
#घोषणा _PTRDIFF_T
प्रकार __kernel_सूचक_भेद_प्रकार	सूचक_भेद_प्रकार;
#पूर्ण_अगर

#अगर_अघोषित _CLOCK_T
#घोषणा _CLOCK_T
प्रकार __kernel_घड़ी_प्रकार	घड़ी_प्रकार;
#पूर्ण_अगर

#अगर_अघोषित _CADDR_T
#घोषणा _CADDR_T
प्रकार __kernel_caddr_t	caddr_t;
#पूर्ण_अगर

/* bsd */
प्रकार अचिन्हित अक्षर		u_अक्षर;
प्रकार अचिन्हित लघु		u_लघु;
प्रकार अचिन्हित पूर्णांक		u_पूर्णांक;
प्रकार अचिन्हित दीर्घ		u_दीर्घ;

/* sysv */
प्रकार अचिन्हित अक्षर		unअक्षर;
प्रकार अचिन्हित लघु		uलघु;
प्रकार अचिन्हित पूर्णांक		uपूर्णांक;
प्रकार अचिन्हित दीर्घ		uदीर्घ;

#अगर_अघोषित __BIT_TYPES_DEFINED__
#घोषणा __BIT_TYPES_DEFINED__

प्रकार u8			u_पूर्णांक8_t;
प्रकार s8			पूर्णांक8_t;
प्रकार u16			u_पूर्णांक16_t;
प्रकार s16			पूर्णांक16_t;
प्रकार u32			u_पूर्णांक32_t;
प्रकार s32			पूर्णांक32_t;

#पूर्ण_अगर /* !(__BIT_TYPES_DEFINED__) */

प्रकार u8			uपूर्णांक8_t;
प्रकार u16			uपूर्णांक16_t;
प्रकार u32			uपूर्णांक32_t;

#अगर defined(__GNUC__)
प्रकार u64			uपूर्णांक64_t;
प्रकार u64			u_पूर्णांक64_t;
प्रकार s64			पूर्णांक64_t;
#पूर्ण_अगर

/* this is a special 64bit data type that is 8-byte aligned */
#घोषणा aligned_u64		__aligned_u64
#घोषणा aligned_be64		__aligned_be64
#घोषणा aligned_le64		__aligned_le64

/**
 * The type used क्रम indexing onto a disc or disc partition.
 *
 * Linux always considers sectors to be 512 bytes दीर्घ independently
 * of the devices real block size.
 *
 * blkcnt_t is the type of the inode's block count.
 */
प्रकार u64 sector_t;
प्रकार u64 blkcnt_t;

/*
 * The type of an index पूर्णांकo the pagecache.
 */
#घोषणा pgoff_t अचिन्हित दीर्घ

/*
 * A dma_addr_t can hold any valid DMA address, i.e., any address वापसed
 * by the DMA API.
 *
 * If the DMA API only uses 32-bit addresses, dma_addr_t need only be 32
 * bits wide.  Bus addresses, e.g., PCI BARs, may be wider than 32 bits,
 * but drivers करो memory-mapped I/O to ioremapped kernel भव addresses,
 * so they करोn't care about the size of the actual bus addresses.
 */
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
प्रकार u64 dma_addr_t;
#अन्यथा
प्रकार u32 dma_addr_t;
#पूर्ण_अगर

प्रकार अचिन्हित पूर्णांक __bitwise gfp_t;
प्रकार अचिन्हित पूर्णांक __bitwise slab_flags_t;
प्रकार अचिन्हित पूर्णांक __bitwise भ_शेषe_t;

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
प्रकार u64 phys_addr_t;
#अन्यथा
प्रकार u32 phys_addr_t;
#पूर्ण_अगर

प्रकार phys_addr_t resource_माप_प्रकार;

/*
 * This type is the placeholder क्रम a hardware पूर्णांकerrupt number. It has to be
 * big enough to enबंद whatever representation is used by a given platक्रमm.
 */
प्रकार अचिन्हित दीर्घ irq_hw_number_t;

प्रकार काष्ठा अणु
	पूर्णांक counter;
पूर्ण atomic_t;

#घोषणा ATOMIC_INIT(i) अणु (i) पूर्ण

#अगर_घोषित CONFIG_64BIT
प्रकार काष्ठा अणु
	s64 counter;
पूर्ण atomic64_t;
#पूर्ण_अगर

काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;

काष्ठा hlist_head अणु
	काष्ठा hlist_node *first;
पूर्ण;

काष्ठा hlist_node अणु
	काष्ठा hlist_node *next, **pprev;
पूर्ण;

काष्ठा ustat अणु
	__kernel_daddr_t	f_tमुक्त;
#अगर_घोषित CONFIG_ARCH_32BIT_USTAT_F_TINODE
	अचिन्हित पूर्णांक		f_tinode;
#अन्यथा
	अचिन्हित दीर्घ		f_tinode;
#पूर्ण_अगर
	अक्षर			f_fname[6];
	अक्षर			f_fpack[6];
पूर्ण;

/**
 * काष्ठा callback_head - callback काष्ठाure क्रम use with RCU and task_work
 * @next: next update requests in a list
 * @func: actual update function to call after the grace period.
 *
 * The काष्ठा is aligned to size of poपूर्णांकer. On most architectures it happens
 * naturally due ABI requirements, but some architectures (like CRIS) have
 * weird ABI and we need to ask it explicitly.
 *
 * The alignment is required to guarantee that bit 0 of @next will be
 * clear under normal conditions -- as दीर्घ as we use call_rcu() or
 * call_srcu() to queue the callback.
 *
 * This guarantee is important क्रम few reasons:
 *  - future call_rcu_lazy() will make use of lower bits in the poपूर्णांकer;
 *  - the काष्ठाure shares storage space in काष्ठा page with @compound_head,
 *    which encode PageTail() in bit 0. The guarantee is needed to aव्योम
 *    false-positive PageTail().
 */
काष्ठा callback_head अणु
	काष्ठा callback_head *next;
	व्योम (*func)(काष्ठा callback_head *head);
पूर्ण __attribute__((aligned(माप(व्योम *))));
#घोषणा rcu_head callback_head

प्रकार व्योम (*rcu_callback_t)(काष्ठा rcu_head *head);
प्रकार व्योम (*call_rcu_func_t)(काष्ठा rcu_head *head, rcu_callback_t func);

प्रकार व्योम (*swap_func_t)(व्योम *a, व्योम *b, पूर्णांक size);

प्रकार पूर्णांक (*cmp_r_func_t)(स्थिर व्योम *a, स्थिर व्योम *b, स्थिर व्योम *priv);
प्रकार पूर्णांक (*cmp_func_t)(स्थिर व्योम *a, स्थिर व्योम *b);

#पूर्ण_अगर /*  __ASSEMBLY__ */
#पूर्ण_अगर /* _LINUX_TYPES_H */
