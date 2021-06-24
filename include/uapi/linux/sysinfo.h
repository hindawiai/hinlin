<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_SYSINFO_H
#घोषणा _LINUX_SYSINFO_H

#समावेश <linux/types.h>

#घोषणा SI_LOAD_SHIFT	16
काष्ठा sysinfo अणु
	__kernel_दीर्घ_t upसमय;		/* Seconds since boot */
	__kernel_uदीर्घ_t loads[3];	/* 1, 5, and 15 minute load averages */
	__kernel_uदीर्घ_t totalram;	/* Total usable मुख्य memory size */
	__kernel_uदीर्घ_t मुक्तram;	/* Available memory size */
	__kernel_uदीर्घ_t sharedram;	/* Amount of shared memory */
	__kernel_uदीर्घ_t bufferram;	/* Memory used by buffers */
	__kernel_uदीर्घ_t totalswap;	/* Total swap space size */
	__kernel_uदीर्घ_t मुक्तswap;	/* swap space still available */
	__u16 procs;		   	/* Number of current processes */
	__u16 pad;		   	/* Explicit padding क्रम m68k */
	__kernel_uदीर्घ_t totalhigh;	/* Total high memory size */
	__kernel_uदीर्घ_t मुक्तhigh;	/* Available high memory size */
	__u32 mem_unit;			/* Memory unit size in bytes */
	अक्षर _f[20-2*माप(__kernel_uदीर्घ_t)-माप(__u32)];	/* Padding: libc5 uses this.. */
पूर्ण;

#पूर्ण_अगर /* _LINUX_SYSINFO_H */
