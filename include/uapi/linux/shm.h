<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SHM_H_
#घोषणा _UAPI_LINUX_SHM_H_

#समावेश <linux/ipc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र-generic/hugetlb_encode.h>
#अगर_अघोषित __KERNEL__
#समावेश <unistd.h>
#पूर्ण_अगर

/*
 * SHMMNI, SHMMAX and SHMALL are शेष upper limits which can be
 * modअगरied by sysctl. The SHMMAX and SHMALL values have been chosen to
 * be as large possible without facilitating scenarios where userspace
 * causes overflows when adjusting the limits via operations of the क्रमm
 * "retrieve current limit; add X; update limit". It is thereक्रमe not
 * advised to make SHMMAX and SHMALL any larger. These limits are
 * suitable क्रम both 32 and 64-bit प्रणालीs.
 */
#घोषणा SHMMIN 1			 /* min shared seg size (bytes) */
#घोषणा SHMMNI 4096			 /* max num of segs प्रणाली wide */
#घोषणा SHMMAX (अच_दीर्घ_उच्च - (1UL << 24)) /* max shared seg size (bytes) */
#घोषणा SHMALL (अच_दीर्घ_उच्च - (1UL << 24)) /* max shm प्रणाली wide (pages) */
#घोषणा SHMSEG SHMMNI			 /* max shared segs per process */

/* Obsolete, used only क्रम backwards compatibility and libc5 compiles */
काष्ठा shmid_ds अणु
	काष्ठा ipc_perm		shm_perm;	/* operation perms */
	पूर्णांक			shm_segsz;	/* size of segment (bytes) */
	__kernel_old_समय_प्रकार	shm_aसमय;	/* last attach समय */
	__kernel_old_समय_प्रकार	shm_dसमय;	/* last detach समय */
	__kernel_old_समय_प्रकार	shm_स_समय;	/* last change समय */
	__kernel_ipc_pid_t	shm_cpid;	/* pid of creator */
	__kernel_ipc_pid_t	shm_lpid;	/* pid of last चालक */
	अचिन्हित लघु		shm_nattch;	/* no. of current attaches */
	अचिन्हित लघु 		shm_unused;	/* compatibility */
	व्योम 			*shm_unused2;	/* ditto - used by DIPC */
	व्योम			*shm_unused3;	/* unused */
पूर्ण;

/* Include the definition of shmid64_ds and shminfo64 */
#समावेश <यंत्र/shmbuf.h>

/*
 * shmget() shmflg values.
 */
/* The bottom nine bits are the same as खोलो(2) mode flags */
#घोषणा SHM_R		0400	/* or S_IRUGO from <linux/स्थिति.स> */
#घोषणा SHM_W		0200	/* or S_IWUGO from <linux/स्थिति.स> */
/* Bits 9 & 10 are IPC_CREAT and IPC_EXCL */
#घोषणा SHM_HUGETLB	04000	/* segment will use huge TLB pages */
#घोषणा SHM_NORESERVE	010000	/* करोn't check क्रम reservations */

/*
 * Huge page size encoding when SHM_HUGETLB is specअगरied, and a huge page
 * size other than the शेष is desired.  See hugetlb_encode.h
 */
#घोषणा SHM_HUGE_SHIFT	HUGETLB_FLAG_ENCODE_SHIFT
#घोषणा SHM_HUGE_MASK	HUGETLB_FLAG_ENCODE_MASK

#घोषणा SHM_HUGE_64KB	HUGETLB_FLAG_ENCODE_64KB
#घोषणा SHM_HUGE_512KB	HUGETLB_FLAG_ENCODE_512KB
#घोषणा SHM_HUGE_1MB	HUGETLB_FLAG_ENCODE_1MB
#घोषणा SHM_HUGE_2MB	HUGETLB_FLAG_ENCODE_2MB
#घोषणा SHM_HUGE_8MB	HUGETLB_FLAG_ENCODE_8MB
#घोषणा SHM_HUGE_16MB	HUGETLB_FLAG_ENCODE_16MB
#घोषणा SHM_HUGE_32MB	HUGETLB_FLAG_ENCODE_32MB
#घोषणा SHM_HUGE_256MB	HUGETLB_FLAG_ENCODE_256MB
#घोषणा SHM_HUGE_512MB	HUGETLB_FLAG_ENCODE_512MB
#घोषणा SHM_HUGE_1GB	HUGETLB_FLAG_ENCODE_1GB
#घोषणा SHM_HUGE_2GB	HUGETLB_FLAG_ENCODE_2GB
#घोषणा SHM_HUGE_16GB	HUGETLB_FLAG_ENCODE_16GB

/*
 * shmat() shmflg values
 */
#घोषणा	SHM_RDONLY	010000	/* पढ़ो-only access */
#घोषणा	SHM_RND		020000	/* round attach address to SHMLBA boundary */
#घोषणा	SHM_REMAP	040000	/* take-over region on attach */
#घोषणा	SHM_EXEC	0100000	/* execution access */

/* super user shmctl commands */
#घोषणा SHM_LOCK 	11
#घोषणा SHM_UNLOCK 	12

/* ipcs ctl commands */
#घोषणा SHM_STAT	13
#घोषणा SHM_INFO	14
#घोषणा SHM_STAT_ANY    15

/* Obsolete, used only क्रम backwards compatibility */
काष्ठा	shminfo अणु
	पूर्णांक shmmax;
	पूर्णांक shmmin;
	पूर्णांक shmmni;
	पूर्णांक shmseg;
	पूर्णांक shmall;
पूर्ण;

काष्ठा shm_info अणु
	पूर्णांक used_ids;
	__kernel_uदीर्घ_t shm_tot;	/* total allocated shm */
	__kernel_uदीर्घ_t shm_rss;	/* total resident shm */
	__kernel_uदीर्घ_t shm_swp;	/* total swapped shm */
	__kernel_uदीर्घ_t swap_attempts;
	__kernel_uदीर्घ_t swap_successes;
पूर्ण;


#पूर्ण_अगर /* _UAPI_LINUX_SHM_H_ */
