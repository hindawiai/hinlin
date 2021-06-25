<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* net/aपंचांग/resources.h - ATM-related resources */

/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित NET_ATM_RESOURCES_H
#घोषणा NET_ATM_RESOURCES_H

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/mutex.h>


बाह्य काष्ठा list_head aपंचांग_devs;
बाह्य काष्ठा mutex aपंचांग_dev_mutex;

पूर्णांक aपंचांग_getnames(व्योम __user *buf, पूर्णांक __user *iobuf_len);
पूर्णांक aपंचांग_dev_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *buf, पूर्णांक __user *sioc_len,
		  पूर्णांक number, पूर्णांक compat);

#अगर_घोषित CONFIG_PROC_FS

#समावेश <linux/proc_fs.h>

व्योम *aपंचांग_dev_seq_start(काष्ठा seq_file *seq, loff_t *pos);
व्योम aपंचांग_dev_seq_stop(काष्ठा seq_file *seq, व्योम *v);
व्योम *aपंचांग_dev_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);


पूर्णांक aपंचांग_proc_dev_रेजिस्टर(काष्ठा aपंचांग_dev *dev);
व्योम aपंचांग_proc_dev_deरेजिस्टर(काष्ठा aपंचांग_dev *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक aपंचांग_proc_dev_रेजिस्टर(काष्ठा aपंचांग_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aपंचांग_proc_dev_deरेजिस्टर(काष्ठा aपंचांग_dev *dev)
अणु
	/* nothing */
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

पूर्णांक aपंचांग_रेजिस्टर_sysfs(काष्ठा aपंचांग_dev *adev, काष्ठा device *parent);
व्योम aपंचांग_unरेजिस्टर_sysfs(काष्ठा aपंचांग_dev *adev);
#पूर्ण_अगर
