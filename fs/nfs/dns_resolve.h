<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Resolve DNS hostnames पूर्णांकo valid ip addresses
 */
#अगर_अघोषित __LINUX_FS_NFS_DNS_RESOLVE_H
#घोषणा __LINUX_FS_NFS_DNS_RESOLVE_H

#घोषणा NFS_DNS_HOSTNAME_MAXLEN	(128)


#अगर_घोषित CONFIG_NFS_USE_KERNEL_DNS
अटल अंतरभूत पूर्णांक nfs_dns_resolver_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nfs_dns_resolver_destroy(व्योम)
अणुपूर्ण

अटल अंतरभूत पूर्णांक nfs_dns_resolver_cache_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nfs_dns_resolver_cache_destroy(काष्ठा net *net)
अणुपूर्ण
#अन्यथा
बाह्य पूर्णांक nfs_dns_resolver_init(व्योम);
बाह्य व्योम nfs_dns_resolver_destroy(व्योम);
बाह्य पूर्णांक nfs_dns_resolver_cache_init(काष्ठा net *net);
बाह्य व्योम nfs_dns_resolver_cache_destroy(काष्ठा net *net);
#पूर्ण_अगर

बाह्य sमाप_प्रकार nfs_dns_resolve_name(काष्ठा net *net, अक्षर *name,
		माप_प्रकार namelen,	काष्ठा sockaddr *sa, माप_प्रकार salen);

#पूर्ण_अगर
