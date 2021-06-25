<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SYSTBLS_H
#घोषणा _SYSTBLS_H

#समावेश <linux/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/utrap.h>

यंत्रlinkage दीर्घ sys_getpagesize(व्योम);
यंत्रlinkage दीर्घ sys_sparc_pipe(व्योम);
यंत्रlinkage दीर्घ sys_nis_syscall(व्योम);
यंत्रlinkage दीर्घ sys_getकरोमुख्यname(अक्षर __user *name, पूर्णांक len);
व्योम करो_rt_sigवापस(काष्ठा pt_regs *regs);
यंत्रlinkage दीर्घ sys_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			 अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			 अचिन्हित दीर्घ fd, अचिन्हित दीर्घ off);
यंत्रlinkage व्योम sparc_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SPARC32
यंत्रlinkage दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			  अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			  अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff);
दीर्घ sys_sparc_remap_file_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			    अचिन्हित दीर्घ prot, अचिन्हित दीर्घ pgoff,
			    अचिन्हित दीर्घ flags);

#पूर्ण_अगर /* CONFIG_SPARC32 */

#अगर_घोषित CONFIG_SPARC64
यंत्रlinkage दीर्घ sys_sparc_ipc(अचिन्हित पूर्णांक call, पूर्णांक first,
			      अचिन्हित दीर्घ second,
			      अचिन्हित दीर्घ third,
			      व्योम __user *ptr, दीर्घ fअगरth);
यंत्रlinkage दीर्घ sparc64_personality(अचिन्हित दीर्घ personality);
यंत्रlinkage दीर्घ sys64_munmap(अचिन्हित दीर्घ addr, माप_प्रकार len);
यंत्रlinkage अचिन्हित दीर्घ sys64_mremap(अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ old_len,
				      अचिन्हित दीर्घ new_len,
				      अचिन्हित दीर्घ flags,
				      अचिन्हित दीर्घ new_addr);
यंत्रlinkage दीर्घ sys_utrap_install(utrap_entry_t type,
				  utrap_handler_t new_p,
				  utrap_handler_t new_d,
				  utrap_handler_t __user *old_p,
				  utrap_handler_t __user *old_d);
यंत्रlinkage दीर्घ sys_memory_ordering(अचिन्हित दीर्घ model);
यंत्रlinkage व्योम sparc64_set_context(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम sparc64_get_context(काष्ठा pt_regs *regs);
यंत्रlinkage दीर्घ compat_sys_truncate64(स्थिर अक्षर __user * path,
				 u32 high,
				 u32 low);
यंत्रlinkage दीर्घ compat_sys_ftruncate64(अचिन्हित पूर्णांक fd,
				  u32 high,
				  u32 low);
काष्ठा compat_stat64;
यंत्रlinkage दीर्घ compat_sys_stat64(स्थिर अक्षर __user * filename,
				  काष्ठा compat_stat64 __user *statbuf);
यंत्रlinkage दीर्घ compat_sys_lstat64(स्थिर अक्षर __user * filename,
				   काष्ठा compat_stat64 __user *statbuf);
यंत्रlinkage दीर्घ compat_sys_ख_स्थिति64(अचिन्हित पूर्णांक fd,
				   काष्ठा compat_stat64 __user * statbuf);
यंत्रlinkage दीर्घ compat_sys_ख_स्थितिat64(अचिन्हित पूर्णांक dfd,
				     स्थिर अक्षर __user *filename,
				     काष्ठा compat_stat64 __user * statbuf, पूर्णांक flag);
यंत्रlinkage दीर्घ compat_sys_pपढ़ो64(अचिन्हित पूर्णांक fd,
					अक्षर __user *ubuf,
					compat_माप_प्रकार count,
					u32 poshi,
					u32 poslo);
यंत्रlinkage दीर्घ compat_sys_pग_लिखो64(अचिन्हित पूर्णांक fd,
					 अक्षर __user *ubuf,
					 compat_माप_प्रकार count,
					 u32 poshi,
					 u32 poslo);
यंत्रlinkage दीर्घ compat_sys_पढ़ोahead(पूर्णांक fd,
				     अचिन्हित offhi,
				     अचिन्हित offlo,
				     compat_माप_प्रकार count);
दीर्घ compat_sys_fadvise64(पूर्णांक fd,
			  अचिन्हित offhi,
			  अचिन्हित offlo,
			  compat_माप_प्रकार len, पूर्णांक advice);
दीर्घ compat_sys_fadvise64_64(पूर्णांक fd,
			     अचिन्हित offhi, अचिन्हित offlo,
			     अचिन्हित lenhi, अचिन्हित lenlo,
			     पूर्णांक advice);
दीर्घ compat_sys_sync_file_range(अचिन्हित पूर्णांक fd,
			   अचिन्हित off_high, अचिन्हित off_low,
			   अचिन्हित nb_high, अचिन्हित nb_low,
			   अचिन्हित पूर्णांक flags);
यंत्रlinkage दीर्घ compat_sys_fallocate(पूर्णांक fd, पूर्णांक mode, u32 offhi, u32 offlo,
				     u32 lenhi, u32 lenlo);
यंत्रlinkage दीर्घ compat_sys_ख_स्थिति64(अचिन्हित पूर्णांक fd,
				   काष्ठा compat_stat64 __user * statbuf);
यंत्रlinkage दीर्घ compat_sys_ख_स्थितिat64(अचिन्हित पूर्णांक dfd,
				     स्थिर अक्षर __user *filename,
				     काष्ठा compat_stat64 __user * statbuf,
				     पूर्णांक flag);
#पूर्ण_अगर /* CONFIG_SPARC64 */
#पूर्ण_अगर /* _SYSTBLS_H */
