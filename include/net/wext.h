<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_WEXT_H
#घोषणा __NET_WEXT_H

#समावेश <net/iw_handler.h>

काष्ठा net;

#अगर_घोषित CONFIG_WEXT_CORE
पूर्णांक wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
		      व्योम __user *arg);
पूर्णांक compat_wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg);

काष्ठा iw_statistics *get_wireless_stats(काष्ठा net_device *dev);
पूर्णांक call_commit_handler(काष्ठा net_device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
				    व्योम __user *arg)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक compat_wext_handle_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
					   अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_WEXT_PROC
पूर्णांक wext_proc_init(काष्ठा net *net);
व्योम wext_proc_निकास(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक wext_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम wext_proc_निकास(काष्ठा net *net)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_WEXT_PRIV
पूर्णांक ioctl_निजी_call(काष्ठा net_device *dev, काष्ठा iwreq *iwr,
		       अचिन्हित पूर्णांक cmd, काष्ठा iw_request_info *info,
		       iw_handler handler);
पूर्णांक compat_निजी_call(काष्ठा net_device *dev, काष्ठा iwreq *iwr,
			अचिन्हित पूर्णांक cmd, काष्ठा iw_request_info *info,
			iw_handler handler);
पूर्णांक iw_handler_get_निजी(काष्ठा net_device *		dev,
			   काष्ठा iw_request_info *	info,
			   जोड़ iwreq_data *		wrqu,
			   अक्षर *			extra);
#अन्यथा
#घोषणा ioctl_निजी_call शून्य
#घोषणा compat_निजी_call शून्य
#पूर्ण_अगर


#पूर्ण_अगर /* __NET_WEXT_H */
