<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX__AIO_H
#घोषणा __LINUX__AIO_H

#समावेश <linux/aio_abi.h>

काष्ठा kioctx;
काष्ठा kiocb;
काष्ठा mm_काष्ठा;

प्रकार पूर्णांक (kiocb_cancel_fn)(काष्ठा kiocb *);

/* prototypes */
#अगर_घोषित CONFIG_AIO
बाह्य व्योम निकास_aio(काष्ठा mm_काष्ठा *mm);
व्योम kiocb_set_cancel_fn(काष्ठा kiocb *req, kiocb_cancel_fn *cancel);
#अन्यथा
अटल अंतरभूत व्योम निकास_aio(काष्ठा mm_काष्ठा *mm) अणु पूर्ण
अटल अंतरभूत व्योम kiocb_set_cancel_fn(काष्ठा kiocb *req,
				       kiocb_cancel_fn *cancel) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_AIO */

/* क्रम sysctl: */
बाह्य अचिन्हित दीर्घ aio_nr;
बाह्य अचिन्हित दीर्घ aio_max_nr;

#पूर्ण_अगर /* __LINUX__AIO_H */
