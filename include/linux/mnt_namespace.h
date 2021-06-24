<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NAMESPACE_H_
#घोषणा _NAMESPACE_H_
#अगर_घोषित __KERNEL__

काष्ठा mnt_namespace;
काष्ठा fs_काष्ठा;
काष्ठा user_namespace;
काष्ठा ns_common;

बाह्य काष्ठा mnt_namespace *copy_mnt_ns(अचिन्हित दीर्घ, काष्ठा mnt_namespace *,
		काष्ठा user_namespace *, काष्ठा fs_काष्ठा *);
बाह्य व्योम put_mnt_ns(काष्ठा mnt_namespace *ns);
बाह्य काष्ठा ns_common *from_mnt_ns(काष्ठा mnt_namespace *);

बाह्य स्थिर काष्ठा file_operations proc_mounts_operations;
बाह्य स्थिर काष्ठा file_operations proc_mountinfo_operations;
बाह्य स्थिर काष्ठा file_operations proc_mountstats_operations;

#पूर्ण_अगर
#पूर्ण_अगर
