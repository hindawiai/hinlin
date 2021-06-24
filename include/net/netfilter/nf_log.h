<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_LOG_H
#घोषणा _NF_LOG_H

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_log.h>

/* Log tcp sequence, tcp options, ip options and uid owning local socket */
#घोषणा NF_LOG_DEFAULT_MASK	0x0f

/* This flag indicates that copy_len field in nf_loginfo is set */
#घोषणा NF_LOG_F_COPY_LEN	0x1

क्रमागत nf_log_type अणु
	NF_LOG_TYPE_LOG		= 0,
	NF_LOG_TYPE_ULOG,
	NF_LOG_TYPE_MAX
पूर्ण;

काष्ठा nf_loginfo अणु
	u_पूर्णांक8_t type;
	जोड़ अणु
		काष्ठा अणु
			/* copy_len will be used अगरf you set
			 * NF_LOG_F_COPY_LEN in flags
			 */
			u_पूर्णांक32_t copy_len;
			u_पूर्णांक16_t group;
			u_पूर्णांक16_t qthreshold;
			u_पूर्णांक16_t flags;
		पूर्ण ulog;
		काष्ठा अणु
			u_पूर्णांक8_t level;
			u_पूर्णांक8_t logflags;
		पूर्ण log;
	पूर्ण u;
पूर्ण;

प्रकार व्योम nf_logfn(काष्ठा net *net,
		      u_पूर्णांक8_t pf,
		      अचिन्हित पूर्णांक hooknum,
		      स्थिर काष्ठा sk_buff *skb,
		      स्थिर काष्ठा net_device *in,
		      स्थिर काष्ठा net_device *out,
		      स्थिर काष्ठा nf_loginfo *li,
		      स्थिर अक्षर *prefix);

काष्ठा nf_logger अणु
	अक्षर			*name;
	क्रमागत nf_log_type	type;
	nf_logfn 		*logfn;
	काष्ठा module		*me;
पूर्ण;

/* sysctl_nf_log_all_netns - allow LOG target in all network namespaces */
बाह्य पूर्णांक sysctl_nf_log_all_netns;

/* Function to रेजिस्टर/unरेजिस्टर log function. */
पूर्णांक nf_log_रेजिस्टर(u_पूर्णांक8_t pf, काष्ठा nf_logger *logger);
व्योम nf_log_unरेजिस्टर(काष्ठा nf_logger *logger);

पूर्णांक nf_log_set(काष्ठा net *net, u_पूर्णांक8_t pf, स्थिर काष्ठा nf_logger *logger);
व्योम nf_log_unset(काष्ठा net *net, स्थिर काष्ठा nf_logger *logger);

पूर्णांक nf_log_bind_pf(काष्ठा net *net, u_पूर्णांक8_t pf,
		   स्थिर काष्ठा nf_logger *logger);
व्योम nf_log_unbind_pf(काष्ठा net *net, u_पूर्णांक8_t pf);

पूर्णांक nf_logger_find_get(पूर्णांक pf, क्रमागत nf_log_type type);
व्योम nf_logger_put(पूर्णांक pf, क्रमागत nf_log_type type);

#घोषणा MODULE_ALIAS_NF_LOGGER(family, type) \
	MODULE_ALIAS("nf-logger-" __stringअगरy(family) "-" __stringअगरy(type))

/* Calls the रेजिस्टरed backend logging function */
__म_लिखो(8, 9)
व्योम nf_log_packet(काष्ठा net *net,
		   u_पूर्णांक8_t pf,
		   अचिन्हित पूर्णांक hooknum,
		   स्थिर काष्ठा sk_buff *skb,
		   स्थिर काष्ठा net_device *in,
		   स्थिर काष्ठा net_device *out,
		   स्थिर काष्ठा nf_loginfo *li,
		   स्थिर अक्षर *fmt, ...);

__म_लिखो(8, 9)
व्योम nf_log_trace(काष्ठा net *net,
		  u_पूर्णांक8_t pf,
		  अचिन्हित पूर्णांक hooknum,
		  स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा net_device *in,
		  स्थिर काष्ठा net_device *out,
		  स्थिर काष्ठा nf_loginfo *li,
		  स्थिर अक्षर *fmt, ...);

काष्ठा nf_log_buf;

काष्ठा nf_log_buf *nf_log_buf_खोलो(व्योम);
__म_लिखो(2, 3) पूर्णांक nf_log_buf_add(काष्ठा nf_log_buf *m, स्थिर अक्षर *f, ...);
व्योम nf_log_buf_बंद(काष्ठा nf_log_buf *m);
#पूर्ण_अगर /* _NF_LOG_H */
